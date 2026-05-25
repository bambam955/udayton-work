var shown = false;
function showHideEmail() {
    if (shown) {
        document.getElementById('email').innerHTML = "Show my email";
        shown = false;
    } else {
        var myEmail = "<a href='mailto:mooreb26" + "@" + "udayton.edu'>mooreb26" + "@" + "udayton.edu</a>";
        document.getElementById('email').innerHTML = myEmail;
        shown = true;
    }
}