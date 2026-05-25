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

list($post_body, $post_error) = validate_post_body(isset($_POST["post_body"]) ? $_POST["post_body"] : null);
if ($post_error !== null) {
    header("Location: edit-post.php?post_id=" . urlencode((string)$post_id) . "&error=" . urlencode($post_error));
    exit();
}

if (!update_post_if_owner($post_id, $_SESSION["username"], $post_body)) {
    header("Location: index.php?error=" . urlencode("You cannot edit another user's post."));
    exit();
}

header("Location: index.php?status=" . urlencode("Post updated successfully."));
exit();
?>
