import $ from 'jquery';

// Fetch a safe random joke and render it in the widget.
export async function fetchJoke() {
  const jokeContent = $('#joke-content');

  // Disable button to avoid request spam while current call is in flight.
  $('#joke-refresh').prop('disabled', true);
  jokeContent.html('<span class="text-gray-400 dark:text-gray-500">Loading...</span>');

  try {
    const response = await fetch('https://v2.jokeapi.dev/joke/Any?safe-mode');
    const data = await response.json();

    if (data.error) {
      jokeContent.html('<span class="text-gray-400 dark:text-gray-500">Could not load joke</span>');
      return;
    }

    // JokeAPI may return either a single-line joke or setup/delivery pair.
    if (data.type === 'single') {
      jokeContent.text(data.joke);
    } else {
      jokeContent.html(`<p class="mb-2">${data.setup}</p><p class="font-medium text-primary-500 dark:text-primary-400">${data.delivery}</p>`);
    }
  } catch (error) {
    jokeContent.html('<span class="text-gray-400 dark:text-gray-500">Could not load joke</span>');
  } finally {
    $('#joke-refresh').prop('disabled', false);
  }
}

// Public initializer for the joke widget:
// 1) load immediately, 2) manual refresh button, 3) automatic refresh every 30s.
export function setupJokeWidget() {
  fetchJoke();
  $('#joke-refresh').on('click', fetchJoke);
  setInterval(fetchJoke, 30000);
}
