const path = require('path');

// Prefer dotenv when available, but do not fail startup if it is not installed
// (this keeps the service runnable in environments that already provide env vars
// another way).
try {
  const dotenv = require('dotenv');
  dotenv.config({ path: path.join(__dirname, '.env') });
} catch (_error) {
  // dotenv is optional when environment is injected by the platform or launch script.
}

const app = require('./src/app');

const {
  OPENROUTER_API_KEY,
  CHAT_CLEANUP_INTERVAL_MS,
} = require('./src/config');
const { pruneExpiredSessions } = require('./src/session-store');

const port = process.env.PORT || 8080;

if (!OPENROUTER_API_KEY) {
  // Fail fast so deployment doesn't start without server-side OpenRouter credentials.
  throw new Error('Environment variable OPENROUTER_API_KEY is required for microservice2.');
}

setInterval(pruneExpiredSessions, CHAT_CLEANUP_INTERVAL_MS);

app.listen(port, () => console.log('HTTP server with Express.js listening on port ' + port));
