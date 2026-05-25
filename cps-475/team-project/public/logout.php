<?php
require_once __DIR__ . "/../src/session_auth.php";
require_once __DIR__ . "/../src/page_header.php";

start_secure_session();
require_valid_csrf_token_from_post();
destroy_session();
render_page_header("Logout");
?>

<p class="helper-text">You have been logged out.</p>

<div class="actions">
	<a class="button" href="login.php">Login again</a>
</div>
<?php render_page_footer(); ?>
