<?php
require_once __DIR__ . "/../src/database.php";
require_once __DIR__ . "/../src/credential_validation.php";
require_once __DIR__ . "/../src/session_auth.php";
require_once __DIR__ . "/../src/page_header.php";

require_authenticated_session();

list($post_id, $post_id_error) = validate_post_id(isset($_GET["post_id"]) ? $_GET["post_id"] : null);
if ($post_id_error !== null) {
    header("Location: index.php?error=" . urlencode($post_id_error));
    exit();
}

$post = get_post_by_id($post_id);
if ($post === FALSE || $post === null) {
    header("Location: index.php?error=" . urlencode("Post not found."));
    exit();
}

if ($post["username"] !== $_SESSION["username"]) {
    header("Location: index.php?error=" . urlencode("You cannot edit another user's post."));
    exit();
}

$csrf_token = get_csrf_token();
render_page_header("Edit My Post");
?>
	<form action="edit-post-submit.php" method="POST" class="form login">
		<input type="hidden" name="csrf_token" value="<?php echo htmlspecialchars($csrf_token, ENT_QUOTES, "UTF-8"); ?>" />
		<input type="hidden" name="post_id" value="<?php echo (int)$post["id"]; ?>" />
		<div class="field">
			<label for="edit-post-body">Post content</label>
			<textarea id="edit-post-body" name="post_body" required minlength="1" maxlength="2000" rows="6"><?php echo htmlspecialchars($post["body"], ENT_QUOTES, "UTF-8"); ?></textarea>
		</div>
		<button class="button" type="submit">Save Changes</button>
	</form>

	<div class="actions">
		<a class="button button-secondary" href="index.php">Back to Feed</a>
	</div>
<?php render_page_footer(); ?>
