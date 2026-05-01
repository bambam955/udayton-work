import $ from 'jquery';

// Toggle visibility of the email link and keep button text in sync with current state.
export function setupEmailToggle() {
  $('#email-toggle').on('click', () => {
    $('#email-link').toggleClass('hidden');
    const showing = !$('#email-link').hasClass('hidden');
    $('#email-toggle').text(showing ? 'Hide Email' : 'Show Email');
  });
}
