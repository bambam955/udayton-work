import { setupThemeToggle } from './js/theme';
import { setupClocks } from './js/clocks';
import { setupEmailToggle } from './js/email';
import { setupSkillsFilter } from './js/skills';
import { setupJokeWidget } from './js/joke-api';
import { fetchXkcd } from './js/xkcd-api';
import { setupChat } from './js/chat';
import { setupHonorsWidget } from './js/honors-widget';

// Centralized startup so page behavior is initialized in one predictable place.
function bootstrap() {
  // UI behavior
  setupThemeToggle();
  setupClocks();
  setupEmailToggle();
  setupSkillsFilter();

  // External API widgets
  setupJokeWidget();
  fetchXkcd();
  setupHonorsWidget();

  // AI assistant widget
  setupChat();
}

// Execute immediately once this module is loaded by the page.
bootstrap();
