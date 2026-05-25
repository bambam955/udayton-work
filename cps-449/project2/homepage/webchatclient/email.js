var shown = false;

function showHideEmail() {
    if (shown) {
        document.getElementById('email').innerHTML = "Show my email";
        shown = false;
    } else {
        // Build the address in pieces so simple scrapers do not see it directly in the source.
        var myEmail = "<a href='mailto:mooreb26" + "@" + "udayton.edu'>mooreb26" + "@" + "udayton.edu</a>";
        document.getElementById('email').innerHTML = myEmail;
        shown = true;
    }
}

// Module scripts do not expose functions globally, so attach the click handler here.
document.getElementById('email').addEventListener('click', showHideEmail);
