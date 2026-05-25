import { getSessionId, setSessionId } from './session';

const CHAT_API_URL = (import.meta.env.VITE_CHAT_API_URL || '/chat').replace(/\/$/, '');
const CHAT_RESET_API_URL = `${CHAT_API_URL}/reset`;

// Attach session id as a header; chat message body remains one-field assignment-compatible.
function buildHeaders() {
  const headers = {
    'Content-Type': 'application/json',
  };

  const sessionId = getSessionId();
  if (sessionId) {
    headers['x-chat-session-id'] = sessionId;
  }

  return headers;
}

// Keep fetch parsing resilient to non-JSON failure paths for clearer upstream errors.
async function parseResponse(response) {
  const body = await response.json().catch(() => ({}));
  return { response, body };
}

// Single-message envelope keeps the backend contract simple (`message` only).
function messagePayloadToBody(payload) {
  return { message: payload };
}

// Return shape is `body` so callers can consume session + answer metadata consistently.
export async function sendMessage(messagePayload) {
  const request = await fetch(CHAT_API_URL, {
    method: 'POST',
    headers: buildHeaders(),
    body: JSON.stringify(messagePayloadToBody(messagePayload)),
  });

  const { response, body } = await parseResponse(request);

  if (!response.ok) {
    const message = body?.error || `Chat service request failed with status ${response.status}`;
    throw new Error(message);
  }

  if (body?.sessionId) {
    setSessionId(body.sessionId);
  }

  if (!body?.answer) {
    throw new Error('No answer returned by model');
  }

  return body;
}

export async function resetConversation() {
  const request = await fetch(CHAT_RESET_API_URL, {
    method: 'POST',
    headers: buildHeaders(),
    body: JSON.stringify({}),
  });

  const { response, body } = await parseResponse(request);
  if (!response.ok) {
    const message = body?.error || `Chat reset request failed with status ${response.status}`;
    throw new Error(message);
  }

  return body;
}
