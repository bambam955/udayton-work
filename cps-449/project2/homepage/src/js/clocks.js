import $ from 'jquery';
import { animate } from 'animejs';

// Track last rendered angles so hand rotation stays smooth across 360-degree wrap-around.
const handAngles = { hour: 0, minute: 0, second: 0 };

// Animate one clock hand to a target angle while avoiding backward jumps at wrap boundaries.
function animateHand(key, selector, angle) {
  let targetAngle = angle;

  // If new angle appears to go "backward" due to 359 -> 0 transition,
  // add 360 so the hand continues moving forward naturally.
  while (targetAngle < handAngles[key] - 180) {
    targetAngle += 360;
  }
  handAngles[key] = targetAngle;

  // Anime.js drives a short eased transition for visual smoothness.
  animate(selector, {
    rotate: targetAngle,
    duration: 350,
    ease: 'outQuad',
  });
}

// Update the digital clock display using the browser locale time format.
function updateDigitalClock() {
  const now = new Date();
  $('#digital-clock').text(now.toLocaleTimeString());
}

// Compute and animate analog hand positions from current time.
function updateAnalogClock() {
  const now = new Date();
  const seconds = now.getSeconds();

  // Include fractional progression so minute/hour hands move continuously.
  const minutes = now.getMinutes() + seconds / 60;
  const hours = (now.getHours() % 12) + minutes / 60;

  animateHand('second', '#second-hand', seconds * 6);
  animateHand('minute', '#minute-hand', minutes * 6);
  animateHand('hour', '#hour-hand', hours * 30);
}

// Public initializer: render immediately, then keep both clocks updated every second.
export function setupClocks() {
  updateDigitalClock();
  updateAnalogClock();
  setInterval(updateDigitalClock, 1000);
  setInterval(updateAnalogClock, 1000);
}
