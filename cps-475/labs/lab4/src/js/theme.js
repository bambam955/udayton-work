import $ from 'jquery';

// Keep the sun/moon icon state in sync with the current `dark` class on <html>.
function updateThemeIcons() {
  const isDark = document.documentElement.classList.contains('dark');
  $('#theme-toggle-light-icon').toggleClass('hidden', isDark);
  $('#theme-toggle-dark-icon').toggleClass('hidden', !isDark);
}

// Initialize click behavior for theme toggle and persist choice in localStorage.
export function setupThemeToggle() {
  // Ensure icons match page state on first render.
  updateThemeIcons();

  $('#theme-toggle').on('click', () => {
    // Tailwind dark mode is class-based, so we toggle on the root element.
    document.documentElement.classList.toggle('dark');

    // Persist user preference across page reloads.
    const theme = document.documentElement.classList.contains('dark') ? 'dark' : 'light';
    localStorage.setItem('color-theme', theme);

    // Refresh icon visibility after class change.
    updateThemeIcons();
  });
}
