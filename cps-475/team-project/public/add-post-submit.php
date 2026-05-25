<?php
require_once __DIR__ . "/../src/database.php";
require_once __DIR__ . "/../src/credential_validation.php";
require_once __DIR__ . "/../src/session_auth.php";

require_authenticated_session();
require_valid_csrf_token_from_post();

list($post_body, $post_error) = validate_post_body(isset($_POST["post_body"]) ? $_POST["post_body"] : null);
if ($post_error !== null) {
    header("Location: index.php?error=" . urlencode($post_error));
    exit();
}

if (!add_post($_SESSION["username"], $post_body)) {
    header("Location: index.php?error=" . urlencode("Unable to add post."));
    exit();
}

header("Location: index.php?status=" . urlencode("Post created successfully."));
exit();
?>
