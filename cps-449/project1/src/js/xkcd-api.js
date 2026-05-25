import $ from 'jquery';

// Fetch and render the latest xkcd comic.
// We intentionally avoid direct browser calls to xkcd because they trigger CORS errors/warnings.
export async function fetchXkcd() {
  const xkcdContent = $('#xkcd-content');
  xkcdContent.html('<span class="text-gray-400 dark:text-gray-500">Loading comic...</span>');

  try {
    const sourceUrl = 'https://xkcd.com/info.0.json';
    const res = await fetch(sourceUrl);
    if (!res.ok) {
      throw new Error('xkcd fetch failed');
    }
    const data = await res.json();

    const html = `
      <h4 class="font-semibold text-gray-800 dark:text-white">${data.safe_title}</h4>
      <img src="${data.img}" alt="${data.alt}" title="${data.alt}" class="w-full rounded border border-gray-200 dark:border-gray-600" loading="lazy">
      <p class="text-xs text-gray-500 dark:text-gray-400">Comic #${data.num}</p>
    `;

    xkcdContent.html(html);
  } catch (error) {
    xkcdContent.html('<span class="text-gray-400 dark:text-gray-500">Could not load xkcd comic</span>');
  }
}
