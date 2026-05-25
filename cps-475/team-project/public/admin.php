<?php
require_once __DIR__ . "/../src/database.php";
require_once __DIR__ . "/../src/session_auth.php";
require_once __DIR__ . "/../src/page_header.php";

require_admin_session();

$users = get_all_users();
$csrf_token = get_csrf_token();

render_page_header("Admin Dashboard", FALSE);
?>
	<p class="helper-text">You are signed in as <?php echo htmlspecialchars($_SESSION["username"], ENT_QUOTES, "UTF-8"); ?> with admin access.</p>

	<div class="admin-summary">
		<span class="admin-summary-label">User accounts</span>
		<span class="admin-summary-value">
			<?php
			if ($users === FALSE) {
				echo "Unavailable";
			} else {
				echo count($users);
			}
			?>
		</span>
	</div>

<?php if ($users === FALSE) : ?>
	<p class="status status-error">Error: unable to load the user list.</p>
<?php elseif (empty($users)) : ?>
	<p class="status">No user accounts were found.</p>
<?php else : ?>
	<div class="table-wrap">
		<table class="data-table">
			<thead>
				<tr>
					<th scope="col">Username</th>
					<th scope="col">Role</th>
				</tr>
			</thead>
			<tbody>
<?php foreach ($users as $user) : ?>
				<tr>
					<td><?php echo htmlspecialchars($user["username"], ENT_QUOTES, "UTF-8"); ?></td>
					<td><?php echo htmlspecialchars($user["role"], ENT_QUOTES, "UTF-8"); ?></td>
				</tr>
<?php endforeach; ?>
			</tbody>
		</table>
	</div>
<?php endif; ?>

	<div class="actions">
		<a class="button button-secondary" href="index.php">Home</a>
		<form action="logout.php" method="POST" class="inline-form">
			<input type="hidden" name="csrf_token" value="<?php echo htmlspecialchars($csrf_token, ENT_QUOTES, "UTF-8"); ?>" />
			<button class="button" type="submit">Logout</button>
		</form>
	</div>
<?php render_page_footer(); ?>
