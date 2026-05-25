<?php
require_once __DIR__ . "/../src/database.php";
require_once __DIR__ . "/../src/session_auth.php";
require_once __DIR__ . "/../src/page_header.php";

require_authenticated_session();

$posts = get_posts_with_comments();
$csrf_token = get_csrf_token();
$status_message = isset($_GET["status"]) ? (string)$_GET["status"] : "";
$error_message = isset($_GET["error"]) ? (string)$_GET["error"] : "";

render_page_header("Home");
?>
	<p class="helper-text">You are signed in as <?php echo htmlspecialchars($_SESSION["username"], ENT_QUOTES, "UTF-8"); ?>.</p>

<?php if ($status_message !== "") : ?>
	<p class="status status-success"><?php echo htmlspecialchars($status_message, ENT_QUOTES, "UTF-8"); ?></p>
<?php endif; ?>
<?php if ($error_message !== "") : ?>
	<p class="status status-error"><?php echo htmlspecialchars($error_message, ENT_QUOTES, "UTF-8"); ?></p>
<?php endif; ?>

	<section class="feed-section">
		<h2>Create a new post</h2>
		<form action="add-post-submit.php" method="POST" class="form login">
			<input type="hidden" name="csrf_token" value="<?php echo htmlspecialchars($csrf_token, ENT_QUOTES, "UTF-8"); ?>" />
			<div class="field">
				<label for="new-post-body">Post</label>
				<textarea id="new-post-body" name="post_body" required minlength="1" maxlength="2000" rows="4" placeholder="Share something..."></textarea>
			</div>
			<button class="button" type="submit">Add Post</button>
		</form>
	</section>

	<section class="feed-section">
		<h2>Global feed</h2>
<?php if ($posts === FALSE) : ?>
		<p class="status status-error">Unable to load posts.</p>
<?php elseif (empty($posts)) : ?>
		<p class="helper-text">No posts yet.</p>
<?php else : ?>
<?php foreach ($posts as $post) : ?>
		<article class="post-card">
			<header class="post-header">
				<p class="post-meta">
					<strong><?php echo htmlspecialchars($post["username"], ENT_QUOTES, "UTF-8"); ?></strong>
					<span>posted at <?php echo htmlspecialchars($post["created_at"], ENT_QUOTES, "UTF-8"); ?></span>
				</p>
<?php if ($post["username"] === $_SESSION["username"]) : ?>
				<a class="button button-secondary" href="edit-post.php?post_id=<?php echo (int)$post["id"]; ?>">Edit My Post</a>
<?php endif; ?>
			</header>
			<p class="post-body"><?php echo nl2br(htmlspecialchars($post["body"], ENT_QUOTES, "UTF-8")); ?></p>

			<section class="comments">
				<h3>Comments</h3>
<?php if (empty($post["comments"])) : ?>
				<p class="helper-text">No comments yet.</p>
<?php else : ?>
<?php foreach ($post["comments"] as $comment) : ?>
				<div class="comment-card">
					<p class="comment-meta"><strong><?php echo htmlspecialchars($comment["username"], ENT_QUOTES, "UTF-8"); ?></strong> at <?php echo htmlspecialchars($comment["created_at"], ENT_QUOTES, "UTF-8"); ?></p>
					<p><?php echo nl2br(htmlspecialchars($comment["body"], ENT_QUOTES, "UTF-8")); ?></p>
				</div>
<?php endforeach; ?>
<?php endif; ?>

				<form action="add-comment-submit.php" method="POST" class="form login">
					<input type="hidden" name="csrf_token" value="<?php echo htmlspecialchars($csrf_token, ENT_QUOTES, "UTF-8"); ?>" />
					<input type="hidden" name="post_id" value="<?php echo (int)$post["id"]; ?>" />
					<div class="field">
						<label for="comment-<?php echo (int)$post["id"]; ?>">Add comment</label>
						<textarea id="comment-<?php echo (int)$post["id"]; ?>" name="comment_body" required minlength="1" maxlength="1000" rows="3" placeholder="Write a comment..."></textarea>
					</div>
					<button class="button button-secondary" type="submit">Add Comment</button>
				</form>
			</section>
		</article>
<?php endforeach; ?>
<?php endif; ?>
	</section>

	<div class="actions">
		<a class="button button-secondary" href="change-password.php">Change Password</a>
		<form action="logout.php" method="POST" class="inline-form">
			<input type="hidden" name="csrf_token" value="<?php echo htmlspecialchars($csrf_token, ENT_QUOTES, "UTF-8"); ?>" />
			<button class="button" type="submit">Logout</button>
		</form>
	</div>
<?php render_page_footer(); ?>
