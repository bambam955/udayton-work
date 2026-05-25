<?php
require_once __DIR__ . "/../src/session_auth.php";
require_once __DIR__ . "/../src/page_header.php";
require_once __DIR__ . "/../src/credential_validation.php";

require_authenticated_session();
$csrf_token = get_csrf_token();
render_page_header("Change Password");
?>
	<form action="change-password-submit.php" method="POST" class="form login">
		<input type="hidden" name="csrf_token" value="<?php echo htmlspecialchars($csrf_token, ENT_QUOTES, "UTF-8"); ?>" />
		<div class="field">
			<label for="change-newpassword">New Password</label>
			<input
				id="change-newpassword"
				type="password"
				class="text_field"
				name="newpassword"
				required
				minlength="8"
				maxlength="100"
				pattern="<?php echo PASSWORD_HTML_PATTERN; ?>"
				title="<?php echo PASSWORD_REQUIREMENT_MESSAGE; ?>"
				autocomplete="new-password"
				oninput="document.getElementsByName('renewpassword')[0].setCustomValidity(document.getElementsByName('renewpassword')[0].value !== this.value ? 'Passwords do not match.' : '')"
			/>
		</div>

		<div class="field">
			<label for="change-renewpassword">Re-type Password</label>
			<input
				id="change-renewpassword"
				type="password"
				class="text_field"
				name="renewpassword"
				required
				minlength="8"
				maxlength="100"
				pattern="<?php echo PASSWORD_HTML_PATTERN; ?>"
				title="<?php echo PASSWORD_REQUIREMENT_MESSAGE; ?>"
				autocomplete="new-password"
				oninput="this.setCustomValidity(this.value !== document.getElementsByName('newpassword')[0].value ? 'Passwords do not match.' : '')"
			/>
		</div>

		<button class="button" type="submit">Change Password</button>
	</form>
<?php render_page_footer(); ?>
