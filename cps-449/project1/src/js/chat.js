import $ from 'jquery';
import { marked } from 'marked';
import DOMPurify from 'dompurify';

// OpenRouter chat completion endpoint and local environment-backed settings.
const OPENROUTER_URL = 'https://openrouter.ai/api/v1/chat/completions';
const DEFAULT_MODEL = import.meta.env.VITE_OPENROUTER_MODEL || 'meta-llama/llama-3.1-8b-instruct:free';
const ENV_KEY = import.meta.env.VITE_OPENROUTER_API_KEY || '';

// Assignment-required global chat history; keeps conversation context across turns.
window.chatHistory = [];

// Cached text summary of profile sections for prompt grounding.
let profileContext = '';

// Configure Markdown parser for chat rendering.
marked.setOptions({ gfm: true, breaks: true });

// Convert model Markdown output into sanitized HTML before injecting into DOM.
function renderAssistantMarkdown(text) {
  const rawHtml = marked.parse(text);
  return DOMPurify.sanitize(rawHtml);
}

// Append one chat bubble (user or assistant) and keep the log auto-scrolled to the latest message.
function appendMessage(role, text) {
  const className = role === 'user' ? 'chat-question' : 'chat-answer';
  const label = role === 'user' ? 'You' : 'AI';
  const row = $('<div>').addClass(`chat-row ${className}`);
  row.append($('<span>').addClass('chat-label').text(`${label}: `));

  // Assistant responses may contain Markdown lists/headings/code, so render as HTML.
  // User input is always treated as plain text for safety.
  if (role === 'assistant') {
    row.append($('<div>').addClass('markdown-content inline-block').html(renderAssistantMarkdown(text)));
  } else {
    row.append($('<span>').text(text));
  }

  $('#chat-log').append(row);
  $('#chat-log').scrollTop($('#chat-log')[0].scrollHeight);
}

// Show or hide the "Thinking..." indicator around async model requests.
function setLoading(isLoading) {
  $('#chat-loading').toggleClass('hidden', !isLoading);
}

// Read API key from Vite environment.
function currentApiKey() {
  return ENV_KEY;
}

// Build concise context from visible profile sections so answers stay anchored to site content.
function buildProfileContext() {
  const sections = [
    '#about',
    '#experience',
    '#education',
    '#skills',
    '#contact',
  ];

  const contextParts = sections
    .map((selector) => {
      const text = $(selector).text().replace(/\s+/g, ' ').trim();
      return text ? `[${selector}] ${text}` : '';
    })
    .filter(Boolean);

  return contextParts.join('\n');
}

// Execute one OpenRouter chat-completions request and return both transport + payload for error handling.
async function requestWithModel(apiKey, messages, model) {
  const response = await fetch(OPENROUTER_URL, {
    method: 'POST',
    headers: {
      'Content-Type': 'application/json',
      Authorization: `Bearer ${apiKey}`,
    },
    body: JSON.stringify({
      model,
      messages,
      temperature: 0.35,
    }),
  });

  const data = await response.json();
  console.log('OpenRouter raw response:', data);
  return { response, data };
}

// Send one user question, get assistant answer, and update global chat history sequence.
async function requestAiAnswer(question) {
  const apiKey = currentApiKey();
  if (!apiKey) {
    throw new Error('Missing OpenRouter API key in VITE_OPENROUTER_API_KEY.');
  }

  const messages = [
    {
      role: 'system',
      // System instruction constrains answers to this profile context.
      content: `You are a concise career assistant for Bennett Moore.
Use only this profile context when answering:
${profileContext}
If a question is outside this profile context, say you do not have enough information.`,
    },
    ...window.chatHistory,
    { role: 'user', content: question },
  ];

  let { response, data } = await requestWithModel(apiKey, messages, DEFAULT_MODEL);

  if (!response.ok) {
    const msg = data?.error?.message || 'OpenRouter request failed';
    throw new Error(msg);
  }

  const answer = data?.choices?.[0]?.message?.content;
  if (!answer) {
    throw new Error('No answer returned by model');
  }

  window.chatHistory.push({ role: 'user', content: question });
  window.chatHistory.push({ role: 'assistant', content: answer });
  return answer;
}

// Wire chat form submit behavior and initialize profile context at startup.
export function setupChat() {
  // Capture current page content once so prompt grounding is stable.
  profileContext = buildProfileContext();

  $('#chat-form').on('submit', async (event) => {
    event.preventDefault();

    const question = $('#chat-input').val().trim();
    if (!question) {
      return;
    }

    appendMessage('user', question);
    $('#chat-input').val('');
    setLoading(true);

    try {
      const answer = await requestAiAnswer(question);
      appendMessage('assistant', answer);
    } catch (error) {
      appendMessage('assistant', `Error: ${error.message}`);
    } finally {
      setLoading(false);
    }
  });
}
