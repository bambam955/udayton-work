<?php
require_once __DIR__ . "/../src/database.php";
require_once __DIR__ . "/../src/credential_validation.php";
require_once __DIR__ . "/../src/page_header.php";
require_once __DIR__ . "/../src/session_auth.php";

start_secure_session();
require_valid_csrf_token_from_post();

list($username, $password, $validation_error) = validate_credential_pair(
    isset($_POST["username"]) ? $_POST["username"] : null,
    isset($_POST["password"]) ? $_POST["password"] : null,
    isset($_POST["repassword"]) ? $_POST["repassword"] : null
);

if ($validation_error !== null) {
    render_page_header("Sign Up");
    echo '<p class="status status-error">Error: ' . htmlspecialchars($validation_error, ENT_QUOTES, "UTF-8") . '</p>';
    echo '<div class="actions"><a class="button" href="signup.php">Back to sign up</a></div>';
    render_page_footer();
    exit();
}

render_page_header("Sign Up");
if (addnewuser($username, $password, "user")) {
    echo '<p class="status status-success">The new user has been added.</p>';
} else {
    echo '<p class="status status-error">Error: Cannot add the new user.</p>';
}
?>

<div class="actions">
	<a class="button" href="login.php">Login</a>
</div>
<?php render_page_footer(); ?>
