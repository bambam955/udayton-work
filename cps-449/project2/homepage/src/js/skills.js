import $ from 'jquery';
import { animate } from 'animejs';

// Filter skill chips by user input and lightly animate visible matches.
export function setupSkillsFilter() {
  $('#skills-filter').on('input', function onFilter() {
    // Normalize search query for case-insensitive matching.
    const value = $(this).val().toLowerCase().trim();

    $('.skill-item').each(function onEachSkill() {
      // Each skill chip stores searchable terms in `data-skill`.
      const skillText = $(this).data('skill').toLowerCase();
      const isMatch = value === '' || skillText.includes(value);
      $(this).toggle(isMatch);

      // Subtle scale animation helps users notice newly matched items.
      if (isMatch) {
        animate(this, {
          scale: [0.95, 1],
          duration: 200,
          ease: 'outQuad',
        });
      }
    });
  });
}
