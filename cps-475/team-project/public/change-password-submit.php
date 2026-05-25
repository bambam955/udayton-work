<?php
require_once __DIR__ . "/../src/database.php";
require_once __DIR__ . "/../src/credential_validation.php";
require_once __DIR__ . "/../src/session_auth.php";
require_once __DIR__ . "/../src/page_header.php";

require_authenticated_session();
require_valid_csrf_token_from_post();

$username = $_SESSION["username"];
list($_ignored_username, $newpassword, $validation_error) = validate_credential_pair(
    $username,
    isset($_POST["newpassword"]) ? $_POST["newpassword"] : null,
    isset($_POST["renewpassword"]) ? $_POST["renewpassword"] : null
);

if ($validation_error !== null) {
    render_page_header("Change Password");
    echo '<p class="status status-error">Error: ' . htmlspecialchars($validation_error, ENT_QUOTES, "UTF-8") . '</p>';
    echo '<div class="actions"><a class="button" href="change-password.php">Back to change password</a></div>';
    render_page_footer();
    exit();
}

render_page_header("Change Password");
if (changepassword($username, $newpassword)) {
    echo '<p class="status status-success">Password changed successfully.</p>';
} else {
    echo '<p class="status status-error">Error occurred while changing password.</p>';
}
?>

<div class="actions">
	<a class="button button-secondary" href="index.php">Home</a>
	<form action="logout.php" method="POST" class="inline-form">
		<input type="hidden" name="csrf_token" value="<?php echo htmlspecialchars(get_csrf_token(), ENT_QUOTES, "UTF-8"); ?>" />
		<button class="button" type="submit">Logout</button>
	</form>
</div>
<?php render_page_footer(); ?>
