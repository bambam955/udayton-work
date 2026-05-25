<?php
require_once __DIR__ . "/../src/page_header.php";
require_once __DIR__ . "/../src/credential_validation.php";
require_once __DIR__ . "/../src/session_auth.php";

$csrf_token = get_csrf_token();
render_page_header("Sign Up");
?>
	<p class="helper-text">Username must be a valid email address and <?php echo PASSWORD_REQUIREMENT_MESSAGE; ?></p>

	<form action="signup-submit.php" method="POST" class="form login">
		<input type="hidden" name="csrf_token" value="<?php echo htmlspecialchars($csrf_token, ENT_QUOTES, "UTF-8"); ?>" />
		<div class="field">
			<label for="signup-username">Username</label>
			<input
				id="signup-username"
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
			<label for="signup-password">Password</label>
			<input
				id="signup-password"
				type="password"
				class="text_field"
				name="password"
				required
				minlength="8"
				maxlength="100"
				pattern="<?php echo PASSWORD_HTML_PATTERN; ?>"
				title="<?php echo PASSWORD_REQUIREMENT_MESSAGE; ?>"
				autocomplete="new-password"
				oninput="document.getElementsByName('repassword')[0].setCustomValidity(document.getElementsByName('repassword')[0].value !== this.value ? 'Passwords do not match.' : '')"
			/>
		</div>

		<div class="field">
			<label for="signup-repassword">Re-type Password</label>
			<input
				id="signup-repassword"
				type="password"
				class="text_field"
				name="repassword"
				required
				minlength="8"
				maxlength="100"
				pattern="<?php echo PASSWORD_HTML_PATTERN; ?>"
				title="<?php echo PASSWORD_REQUIREMENT_MESSAGE; ?>"
				autocomplete="new-password"
				oninput="this.setCustomValidity(this.value !== document.getElementsByName('password')[0].value ? 'Passwords do not match.' : '')"
			/>
		</div>

		<button class="button" type="submit">Sign Up</button>
	</form>
	<p><a href="login.php">Already have an account? Login</a></p>
<?php render_page_footer(); ?>
