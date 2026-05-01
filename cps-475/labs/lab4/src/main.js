import { setupThemeToggle } from './js/theme';
import { setupClocks } from './js/clocks';
import { setupEmailToggle } from './js/email';

// Centralized startup so page behavior is initialized in one predictable place.
function bootstrap() {
  // UI behavior
  setupThemeToggle();
  setupClocks();
  setupEmailToggle();
}

// Execute immediately once this module is loaded by the page.
bootstrap();
