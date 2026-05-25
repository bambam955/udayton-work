<?php
require_once __DIR__ . "/../src/database.php";
require_once __DIR__ . "/../src/credential_validation.php";
require_once __DIR__ . "/../src/session_auth.php";

require_authenticated_session();
require_valid_csrf_token_from_post();

list($post_id, $post_id_error) = validate_post_id(isset($_POST["post_id"]) ? $_POST["post_id"] : null);
if ($post_id_error !== null) {
    header("Location: index.php?error=" . urlencode($post_id_error));
    exit();
}

list($comment_body, $comment_error) = validate_comment_body(isset($_POST["comment_body"]) ? $_POST["comment_body"] : null);
if ($comment_error !== null) {
    header("Location: index.php?error=" . urlencode($comment_error));
    exit();
}

if (!add_comment($post_id, $_SESSION["username"], $comment_body)) {
    header("Location: index.php?error=" . urlencode("Unable to add comment."));
    exit();
}

header("Location: index.php?status=" . urlencode("Comment added successfully."));
exit();
?>
