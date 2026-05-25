import $ from 'jquery';

// Base URL for the deployed microservice.
const API_BASE_URL = 'https://cps449-mooreb26-microservice1.azurewebsites.net';

// Shared class tokens for different response states.
const SUCCESS_CLASSES = 'border-primary-300 bg-primary-50 dark:border-primary-700 dark:bg-gray-900';
const BASE_TEXT_CLASSES = 'text-gray-700 dark:text-gray-300';
const ERROR_CLASSES = 'text-red-400 dark:text-red-300';

// Display the result panel only after a submission produces output.
// Keeps one render path for both error and success states.
function showResult($result) {
  $result.removeClass('hidden');
}

// Render plain text status/error messages in a consistent style.
// Used for client validation errors and transport-level request failures.
function setResultText($result, text, tone = 'normal') {
  showResult($result);
  $result
    .removeClass(`${SUCCESS_CLASSES} ${ERROR_CLASSES} ${BASE_TEXT_CLASSES}`)
    .empty()
    .addClass(tone === 'error' ? ERROR_CLASSES : BASE_TEXT_CLASSES)
    .removeClass('hidden')
    .text(text);
}

// Render success output as a highlighted result block with heading and summary message.
// The backend can return a concise recommendation plus structured metadata for display.
function setResultSuccess($result, payload) {
  const { honors, status, gpa, credits, deltaToNextHonors } = payload;

  // Header keeps the result quick to scan.
  const $title = $('<p>')
    .addClass('text-lg font-bold leading-tight text-primary-600 dark:text-primary-300')
    .text(`Latin Honors Result: ${honors}`);

  // Status is preserved from backend academic standing logic.
  const $status = $('<p>')
    .addClass('mt-1 text-sm text-gray-600 dark:text-gray-300')
    .text(`Status: ${status}`);

  // Keep the raw input-derived values visible for transparency.
  const $meta = $('<p>')
    .addClass('mt-1 text-sm text-gray-600 dark:text-gray-300')
    .text(`GPA: ${gpa} | Credits: ${credits}`);

  // Show the nearest achievable target when a student is on track to move up a tier.
  const $goal = $('<p>')
    .addClass('mt-1 text-sm text-gray-600 dark:text-gray-300');

  if (deltaToNextHonors) {
    $goal.text(`Next target: ${deltaToNextHonors.nextTier} (raise GPA by ${deltaToNextHonors.gpaIncrease}).`);
  }

  $result
    .empty()
    .removeClass('text-red-400 dark:text-red-300 text-gray-700 dark:text-gray-300')
    .addClass('border-primary-300 bg-primary-50 dark:border-primary-700 dark:bg-gray-900')
    .removeClass('hidden')
    .append($title, $status, $meta);

  if (deltaToNextHonors) {
    $result.append($goal);
  }
}

// Validate gpa and credit-hour input before contacting the service.
function parseInputs(rawGpa, rawCredits) {
  // Normalize before numeric parsing so blank strings and accidental whitespace don't leak.
  const trimmedGpa = String(rawGpa || '').trim();
  const trimmedCredits = String(rawCredits || '').trim();

  if (!trimmedGpa) {
    return { valid: false, error: 'Please enter your GPA.' };
  }

  if (!trimmedCredits) {
    return { valid: false, error: 'Please enter total earned credit hours.' };
  }

  const gpa = Number(trimmedGpa);
  const creditHours = Number(trimmedCredits);

  if (!Number.isFinite(gpa) || Number.isNaN(gpa)) {
    return { valid: false, error: 'GPA must be a number.' };
  }

  if (gpa < 0 || gpa > 4) {
    return { valid: false, error: 'GPA must be between 0 and 4.' };
  }

  if (!Number.isInteger(creditHours) || creditHours < 0) {
    return { valid: false, error: 'Credit hours must be a non-negative whole number.' };
  }

  return { valid: true, gpa, creditHours };
}

// Fetch honors data from the POST endpoint and normalize transport/payload failures.
// Request body intentionally uses `creditHours` to match the microservice schema.
async function fetchHonors(gpa, creditHours) {
  const response = await fetch(`${API_BASE_URL}/honors`, {
    method: 'POST',
    headers: {
      'Content-Type': 'application/json'
    },
    body: JSON.stringify({ gpa, creditHours })
  });

  const data = await response.json();

  if (!response.ok || data?.error) {
    throw new Error(data?.error || `Unable to load honors result (${response.status}).`);
  }

  if (!data || !data.honors) {
    throw new Error('Unexpected response from honors service.');
  }

  return data;
}

// Wire the honors form: validate, call microservice, and render result state.
// Keeps behavior aligned with other widgets: prevent submit spamming while request is active.
export function setupHonorsWidget() {
  const $form = $('#honors-form');
  const $gpaInput = $('#honors-gpa');
  const $creditInput = $('#honors-credits');
  const $submit = $('#honors-submit');
  const $result = $('#honors-result');

  if (!$form.length) {
    return;
  }

  $form.on('submit', async (event) => {
    event.preventDefault();
    const { valid, gpa, creditHours, error } = parseInputs($gpaInput.val(), $creditInput.val());

    if (!valid) {
      setResultText($result, error, 'error');
      return;
    }

    $submit.prop('disabled', true);
    // Render immediate feedback while waiting for network.
    $result
      .removeClass('border-primary-300 bg-primary-50 dark:border-primary-700 dark:bg-gray-900')
      .removeClass('text-red-400 dark:text-red-300')
      .removeClass('hidden')
      .addClass('text-gray-500 dark:text-gray-400')
      .text('Calculating honors...');

    try {
      const data = await fetchHonors(gpa, creditHours);
      setResultSuccess($result, data);
    } catch (err) {
      setResultText($result, err.message || 'Unable to fetch honors result.', 'error');
    } finally {
      // Always restore interactivity even if the request fails or succeeds.
      $submit.prop('disabled', false);
    }
  });
}
