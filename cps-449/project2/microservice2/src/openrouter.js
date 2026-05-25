const {
  OPENROUTER_URL,
  OPENROUTER_API_KEY,
  OPENROUTER_MODEL,
  CHAT_REQUEST_TIMEOUT_MS,
} = require('./config');

function assertApiKey() {
  if (!OPENROUTER_API_KEY) {
    throw new Error('Server is missing OPENROUTER_API_KEY.');
  }
}

function buildBody(messages) {
  return {
    model: OPENROUTER_MODEL,
    messages,
    temperature: 0.35,
  };
}

function buildHeaders() {
  return {
    'Content-Type': 'application/json',
    Authorization: `Bearer ${OPENROUTER_API_KEY}`,
  };
}

async function requestChatCompletion(messages) {
  assertApiKey();

  const controller = new AbortController();
  const timer = setTimeout(() => controller.abort(), CHAT_REQUEST_TIMEOUT_MS);

  try {
    const response = await fetch(OPENROUTER_URL, {
      method: 'POST',
      headers: buildHeaders(),
      body: JSON.stringify(buildBody(messages)),
      signal: controller.signal,
    });

    const data = await response.json().catch(() => ({}));
    return { response, data };
  } finally {
    clearTimeout(timer);
  }
}

module.exports = {
  requestChatCompletion,
};
