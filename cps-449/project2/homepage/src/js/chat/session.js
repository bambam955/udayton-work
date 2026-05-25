const CHAT_SESSION_STORAGE_KEY = 'bennett-chat-session-id';
const CHAT_BOOTSTRAPPED_KEY_PREFIX = 'bennett-chat-session-bootstrapped';

// Bootstrap flag key is namespaced by session id so resets can clear per-session seeding state.
function bootstrapStorageKey(sessionId = getSessionId()) {
  if (!sessionId) {
    return '';
  }
  return `${CHAT_BOOTSTRAPPED_KEY_PREFIX}-${sessionId}`;
}

export function getSessionId() {
  return localStorage.getItem(CHAT_SESSION_STORAGE_KEY) || '';
}

// Only overwrite sessionId when the service returns a concrete id.
export function setSessionId(sessionId) {
  if (sessionId) {
    localStorage.setItem(CHAT_SESSION_STORAGE_KEY, sessionId);
  }
}

export function clearSessionId() {
  localStorage.removeItem(CHAT_SESSION_STORAGE_KEY);
}

// Whether this session has already sent the seed context and should use plain message turns.
export function isSessionBootstrapped(sessionId = getSessionId()) {
  const key = bootstrapStorageKey(sessionId);
  if (!key) {
    return false;
  }

  return localStorage.getItem(key) === '1';
}

// Mark session bootstrap done once first answer returns successfully.
export function setSessionBootstrapped(sessionId = getSessionId()) {
  const key = bootstrapStorageKey(sessionId);
  if (!key) {
    return;
  }

  localStorage.setItem(key, '1');
}

// On reset/rotation remove stale bootstrap flag tied to the old session id.
export function clearSessionBootstrap(sessionId = getSessionId()) {
  const key = bootstrapStorageKey(sessionId);
  if (!key) {
    return;
  }

  localStorage.removeItem(key);
}
