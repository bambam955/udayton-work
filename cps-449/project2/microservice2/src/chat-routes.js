const express = require('express');
const {
  OPENROUTER_MODEL,
} = require('./config');
const {
  getOrCreateSession,
  appendTurn,
  replaceHistory,
  resetSession,
} = require('./session-store');
const { requestChatCompletion } = require('./openrouter');

const router = express.Router();
const ALLOWED_ROLES = new Set(['system', 'user', 'assistant', 'tool']);

// Parse one OpenAI-style message and drop malformed entries early.
function parseSingleMessage(candidate) {
  if (!candidate || typeof candidate !== 'object') {
    return null;
  }

  const role = typeof candidate.role === 'string' ? candidate.role.trim().toLowerCase() : '';
  const content = typeof candidate.content === 'string' ? candidate.content.trim() : '';

  if (!ALLOWED_ROLES.has(role) || !content) {
    return null;
  }

  return { role, content };
}

// Accept only explicit message arrays with at least one user turn.
function parseSeedMessages(rawMessage) {
  if (!rawMessage || typeof rawMessage !== 'object' || Array.isArray(rawMessage)) {
    return null;
  }

  if (!Array.isArray(rawMessage.messages) || rawMessage.messages.length === 0) {
    return null;
  }

  const messages = [];
  for (const candidate of rawMessage.messages) {
    const message = parseSingleMessage(candidate);
    if (!message) {
      return null;
    }
    messages.push(message);
  }

  const hasUser = messages.some((message) => message.role === 'user');
  if (!hasUser) {
    return null;
  }

  return messages;
}

// Allow clients to send stringified payloads without changing the one-field contract.
function parseStringSeed(rawMessage) {
  const trimmed = rawMessage.trim();
  if (!trimmed || (trimmed[0] !== '{' && trimmed[0] !== '[')) {
    return null;
  }

  try {
    const parsed = JSON.parse(trimmed);
    return parseSeedMessages(parsed);
  } catch {
    return null;
  }
}

// Convert inbound request into one internal route shape:
// either a plain text turn, or a seeded message list for first-turn context bootstrapping.
function normalizeIncomingMessage(body) {
  const { message } = body;
  if (typeof message === 'string') {
    const seededFromString = parseStringSeed(message);
    if (seededFromString) {
      return { kind: 'seeded', messages: seededFromString };
    }

    const text = message.trim();
    if (!text) {
      return null;
    }

    return { kind: 'text', message: text };
  }

  if (message && typeof message === 'object') {
    const seededMessages = parseSeedMessages(message);
    if (seededMessages) {
      return { kind: 'seeded', messages: seededMessages };
    }
  }

  return null;
}

// OpenAI-style arrays may include both user and assistant turns; we need the latest user input.
function lastUserMessage(messages) {
  for (let i = messages.length - 1; i >= 0; i--) {
    if (messages[i].role === 'user') {
      return messages[i].content;
    }
  }

  return '';
}

// For standard turns, append to server session history and ask for a continuation.
function buildMessages(session, userMessage) {
  return [...session.messages, { role: 'user', content: userMessage }];
}

// POST /chat accepts only the single required `message` field.
router.post('/chat', async (req, res) => {
  const payload = normalizeIncomingMessage(req.body || {});
  if (!payload) {
    return res.status(400).json({ error: 'Request body must include a non-empty message field.' });
  }

  try {
    const session = getOrCreateSession(req);
    const hasHistory = session.messages.length > 0;

    let messages;
    let userMessage;
    if (payload.kind === 'seeded') {
      // On first request after reset/first visit, allow a seeded context payload from the frontend.
      userMessage = lastUserMessage(payload.messages);
      if (!userMessage) {
        return res.status(400).json({ error: 'Seeded message payload must include at least one user message.' });
      }

      // If a stale client sends seeded payload after session exists, keep existing history and only append user turn.
      messages = hasHistory ? [...session.messages, { role: 'user', content: userMessage }] : payload.messages;
    } else {
      userMessage = payload.message;
      messages = buildMessages(session, userMessage);
    }

    const { response, data } = await requestChatCompletion(messages);

    if (!response.ok) {
      const error = data?.error?.message || `OpenRouter request failed with status ${response.status}`;
      return res.status(502).json({ sessionId: session.id, error });
    }

    const answer = data?.choices?.[0]?.message?.content;
    if (!answer) {
      return res.status(502).json({ sessionId: session.id, error: 'OpenRouter returned no assistant content.' });
    }

    // Fresh bootstrap uses the full provided history.
    if (payload.kind === 'seeded' && !hasHistory) {
      replaceHistory(session, payload.messages, answer);
    } else {
      // Follow-up path stores only the new user turn + model reply.
      appendTurn(session, userMessage, answer);
    }

    return res.json({
      sessionId: session.id,
      answer,
      model: data?.model || OPENROUTER_MODEL,
      usage: data?.usage,
    });
  } catch (error) {
    return res.status(500).json({ error: error.message || 'Chat proxy failed.' });
  }
});

// POST /chat/reset rotates to a brand new empty session and returns its id.
router.post('/chat/reset', (req, res) => {
  const session = resetSession(req);
  return res.json({
    sessionId: session.id,
    message: 'Conversation reset.',
  });
});

module.exports = router;
