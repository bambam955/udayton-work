import $ from 'jquery';
import { marked } from 'marked';
import DOMPurify from 'dompurify';

import {
  clearSessionId,
  clearSessionBootstrap,
  getSessionId,
  isSessionBootstrapped,
  setSessionBootstrapped,
  setSessionId,
} from './chat/session';
import { buildSeededUserMessage } from './chat/context';
import { resetConversation, sendMessage } from './chat/api';

// Configure Markdown parser for assistant responses.
marked.setOptions({ gfm: true, breaks: true });

// Render model output as safe HTML while leaving user input as plain text.
function renderAssistantMarkdown(text) {
  const rawHtml = marked.parse(text);
  return DOMPurify.sanitize(rawHtml);
}

function appendMessage(role, text) {
  const className = role === 'user' ? 'chat-question' : 'chat-answer';
  const label = role === 'user' ? 'You' : 'AI';
  const row = $('<div>').addClass(`chat-row ${className}`);
  row.append($('<span>').addClass('chat-label').text(`${label}: `));

  if (role === 'assistant') {
    row.append($('<div>').addClass('markdown-content inline-block').html(renderAssistantMarkdown(text)));
  } else {
    row.append($('<span>').text(text));
  }

  $('#chat-log').append(row);
  $('#chat-log').scrollTop($('#chat-log')[0].scrollHeight);
}

function setLoading(isLoading) {
  $('#chat-loading').toggleClass('hidden', !isLoading);
}

function clearChatLog() {
  $('#chat-log').empty();
}

// Keep local state aligned with server session id and clear stale bootstrap flags on session rotation.
function applySessionFromServerResponse(responseBody) {
  const previousSessionId = getSessionId();

  // Keep service-issued id if it changes after reset.
  if (responseBody?.sessionId) {
    if (previousSessionId && previousSessionId !== responseBody.sessionId) {
      clearSessionBootstrap(previousSessionId);
    }

    setSessionId(responseBody.sessionId);
    return responseBody.sessionId;
  }

  if (!getSessionId()) {
    clearSessionId();
  }

  return getSessionId();
}

export function setupChat() {
  $('#chat-form').on('submit', async (event) => {
    event.preventDefault();

    const question = $('#chat-input').val().trim();
    if (!question) {
      return;
    }

    appendMessage('user', question);
    $('#chat-input').val('');
    setLoading(true);

    // First turn after reset should include system context from the page sections.
    // Later turns only send raw user text to keep payloads small and stable.
    const shouldSeedContext = !isSessionBootstrapped();
    const messagePayload = shouldSeedContext ? buildSeededUserMessage(question) : question;

    try {
      const response = await sendMessage(messagePayload);
      const sessionId = applySessionFromServerResponse(response);

      // Remember that this session already sent context so follow-ups use compact payload.
      if (shouldSeedContext) {
        setSessionBootstrapped(sessionId);
      }
      appendMessage('assistant', response.answer);
    } catch (error) {
      appendMessage('assistant', `Error: ${error.message}`);
    } finally {
      setLoading(false);
    }
  });

  $('#chat-reset').on('click', async () => {
    const currentSessionId = getSessionId();

    // Remove bootstrap marker before round-trip so next successful response re-seeds context.
    if (currentSessionId) {
      clearSessionBootstrap(currentSessionId);
    }

    const hadConversation = Boolean(currentSessionId);
    clearChatLog();
    setLoading(true);

    try {
      const response = await resetConversation();
      applySessionFromServerResponse(response);
      if (!hadConversation) {
        appendMessage('assistant', 'Conversation already clear.');
      } else if (response?.message) {
        appendMessage('assistant', response.message);
      } else {
        appendMessage('assistant', 'Conversation reset.');
      }
    } catch (error) {
      appendMessage('assistant', `Error: ${error.message}`);
    } finally {
      setLoading(false);
    }
  });
}
