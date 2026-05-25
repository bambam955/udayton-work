<?php
require_once __DIR__ . "/../src/page_header.php";
require_once __DIR__ . "/../src/credential_validation.php";
require_once __DIR__ . "/../src/session_auth.php";

$csrf_token = get_csrf_token();
render_page_header("Login");
?>
	<form action="login-submit.php" method="POST" class="form login">
		<input type="hidden" name="csrf_token" value="<?php echo htmlspecialchars($csrf_token, ENT_QUOTES, "UTF-8"); ?>" />
		<div class="field">
			<label for="login-username">Username</label>
			<input
				id="login-username"
				type="text"
				class="text_field"
				name="username"
				required
				minlength="3"
				maxlength="50"
				pattern="<?php echo USERNAME_PATTERN; ?>"
				title="Please enter a valid email as username"
				placeholder="Your email address"
				onchange="this.setCustomValidity(this.validity.patternMismatch ? this.title : '')"
				autocomplete="username"
			/>
		</div>

		<div class="field">
			<label for="login-password">Password</label>
			<input
				id="login-password"
				type="password"
				class="text_field"
				name="password"
				required
				maxlength="100"
				autocomplete="current-password"
			/>
		</div>

		<button class="button" type="submit">Login</button>
	</form>
	<p><a href="signup.php">Need an account? Sign up</a></p>
<?php render_page_footer(); ?>
