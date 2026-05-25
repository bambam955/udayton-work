const PROFILE_SECTION_IDS = ['#about', '#experience', '#education', '#skills', '#contact'];

// Pull visible section text from the page to keep grounding in-page and current.
function readSectionText(selector) {
  const sectionText = document.querySelector(selector)?.textContent || '';
  const compactText = sectionText.replace(/\s+/g, ' ').trim();
  return compactText ? `[${selector}] ${compactText}` : '';
}

// Build an explicit system prompt from stable portfolio sections instead of hardcoding in the service.
function buildProfileContext() {
  const sectionText = PROFILE_SECTION_IDS
    .map((selector) => readSectionText(selector))
    .filter(Boolean)
    .join('\n');

  return `You are a concise career assistant for Bennett Moore.
Use only this profile context when answering:
${sectionText}
If a question is outside this profile context, say you do not have enough information.`;
}

// Returns a seed payload used on the first message of a session.
export function buildSeededUserMessage(question) {
  const contextPrompt = buildProfileContext();

  return {
    messages: [
      { role: 'system', content: contextPrompt },
      { role: 'user', content: question },
    ],
  };
}
