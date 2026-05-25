const crypto = require('crypto');
const {
  CHAT_SESSION_TTL_MS,
  CHAT_SESSION_MAX_MESSAGES,
} = require('./config');

// In-memory session cache keyed by sessionId for assignment scope.
const sessions = new Map();

function now() {
  return Date.now();
}

// Avoid leaking crypto state between modules by always creating IDs through crypto.randomUUID().
function newSessionId() {
  return crypto.randomUUID();
}

// Touch both updatedAt and expiresAt every time the session is used.
function touch(session) {
  session.updatedAt = now();
  session.expiresAt = now() + CHAT_SESSION_TTL_MS;
}

function isExpired(session) {
  return session.expiresAt <= now();
}

// Keep history bounded to reduce memory and request size when sessions are long-lived.
function trimHistory(messages) {
  const maxMessages = Math.max(0, CHAT_SESSION_MAX_MESSAGES);
  if (messages.length <= maxMessages) {
    return messages;
  }

  return messages.slice(messages.length - maxMessages);
}

// New sessions start empty; state lives only in memory until server restart.
function createSession() {
  const session = {
    id: newSessionId(),
    messages: [],
    updatedAt: now(),
    expiresAt: now() + CHAT_SESSION_TTL_MS,
  };
  sessions.set(session.id, session);
  return session;
}

// Session id travels in a custom header so message body stays a single required field.
function getSessionFromHeader(req) {
  return (req.get('x-chat-session-id') || '').trim();
}

// If a referenced session is missing or expired, discard it and force recreation.
function getSessionById(sessionId) {
  if (!sessionId) {
    return null;
  }

  const session = sessions.get(sessionId);
  if (!session) {
    return null;
  }

  if (isExpired(session)) {
    sessions.delete(sessionId);
    return null;
  }

  touch(session);
  return session;
}

// Reuse a valid inbound session when possible; otherwise create a fresh one.
function getOrCreateSession(req) {
  const sessionId = getSessionFromHeader(req);
  const existingSession = getSessionById(sessionId);
  return existingSession || createSession();
}

// Standard append path for non-bootstrap turn flow.
function appendTurn(session, userMessage, assistantMessage) {
  session.messages.push({ role: 'user', content: userMessage });
  session.messages.push({ role: 'assistant', content: assistantMessage });
  session.messages = trimHistory(session.messages);
  touch(session);
}

// Seeded bootstrap path replaces the full message list (plus assistant reply) for first turn.
function replaceHistory(session, messages, assistantMessage) {
  if (!Array.isArray(messages)) {
    return;
  }

  const normalizedMessages = [];
  for (const message of messages) {
    normalizedMessages.push(message);
  }
  normalizedMessages.push({ role: 'assistant', content: assistantMessage });
  session.messages = trimHistory(normalizedMessages);
  touch(session);
}

// Reset both removes old cache entry and starts a clean session immediately.
function resetSession(req) {
  const sessionId = getSessionFromHeader(req);
  if (sessionId) {
    sessions.delete(sessionId);
  }

  return createSession();
}

// Cleanup loop removes stale sessions to prevent unbounded memory growth.
function pruneExpiredSessions() {
  const cutoff = now();
  for (const [sessionId, session] of sessions.entries()) {
    if (session.expiresAt <= cutoff) {
      sessions.delete(sessionId);
    }
  }
}

module.exports = {
  getOrCreateSession,
  appendTurn,
  replaceHistory,
  resetSession,
  pruneExpiredSessions,
};
