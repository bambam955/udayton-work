// OpenRouter endpoint/model credentials live only in the microservice runtime.
// The browser client should never need these values, which keeps keys out of the UI bundle.
const OPENROUTER_URL = process.env.OPENROUTER_URL || 'https://openrouter.ai/api/v1/chat/completions';
const OPENROUTER_MODEL = process.env.OPENROUTER_MODEL || 'openrouter/free';
const OPENROUTER_API_KEY = process.env.OPENROUTER_API_KEY || '';

// Keep sessions and history size limits configurable for easy assignment grading.
const CHAT_SESSION_TTL_MS = Number(process.env.CHAT_SESSION_TTL_MS || 1000 * 60 * 30);
const CHAT_SESSION_MAX_MESSAGES = Number(process.env.CHAT_SESSION_MAX_MESSAGES || 24);
const CHAT_CLEANUP_INTERVAL_MS = Number(process.env.CHAT_CLEANUP_INTERVAL_MS || 1000 * 60 * 5);
const CHAT_REQUEST_TIMEOUT_MS = Number(process.env.CHAT_REQUEST_TIMEOUT_MS || 20000);

module.exports = {
  OPENROUTER_URL,
  OPENROUTER_MODEL,
  OPENROUTER_API_KEY,
  CHAT_SESSION_TTL_MS,
  CHAT_SESSION_MAX_MESSAGES,
  CHAT_CLEANUP_INTERVAL_MS,
  CHAT_REQUEST_TIMEOUT_MS,
};
