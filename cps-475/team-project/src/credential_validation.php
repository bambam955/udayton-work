<?php
// Keep credential rules in one place so login, registration, and password
// changes all reject the same bad input.
define("USERNAME_MIN_LENGTH", 3);
define("USERNAME_MAX_LENGTH", 50);
// Keep the raw username regex here so the PHP validator and HTML pattern
// attributes can share the same source string.
define("USERNAME_PATTERN", '^[\w.-]+@[\w-]+(\.[\w-]+)*$');
define("PASSWORD_MIN_LENGTH", 8);
define("PASSWORD_MAX_LENGTH", 100);
define("PASSWORD_HTML_PATTERN", '^(?=.*[a-z])(?=.*[A-Z])(?=.*\d).{8,100}$');
define("PASSWORD_REQUIREMENT_MESSAGE", "Password must include at least one lowercase letter, one uppercase letter, and one number.");
// Require lowercase, uppercase, and numeric characters, with a reasonable
// length cap to match the rest of the app's credential handling.
define("PASSWORD_PATTERN", '/^(?=.*[a-z])(?=.*[A-Z])(?=.*\d).{8,100}$/');
define("POST_MIN_LENGTH", 1);
define("POST_MAX_LENGTH", 2000);
define("COMMENT_MIN_LENGTH", 1);
define("COMMENT_MAX_LENGTH", 1000);

function normalize_username($username)
{
    return trim((string)$username);
}

function validate_username($username)
{
    if ($username === "") {
        return "Username is required.";
    }

    if (strlen($username) < USERNAME_MIN_LENGTH || strlen($username) > USERNAME_MAX_LENGTH) {
        return "Username must be between 3 and 50 characters.";
    }

    if (!preg_match('/' . USERNAME_PATTERN . '/', $username)) {
        return "Username must be a valid email address.";
    }

    return null;
}

function validate_password($password)
{
    if ($password === "") {
        return "Password is required.";
    }

    if (strlen($password) < PASSWORD_MIN_LENGTH || strlen($password) > PASSWORD_MAX_LENGTH) {
        return "Password must be between 8 and 100 characters.";
    }

    if (!preg_match(PASSWORD_PATTERN, $password)) {
        return PASSWORD_REQUIREMENT_MESSAGE;
    }

    return null;
}

function validate_login_password($password)
{
    if ($password === "") {
        return "Password is required.";
    }

    return null;
}

function validate_credential_pair($username, $password, $password_confirmation = null)
{
    $normalized_username = normalize_username($username);
    $normalized_password = (string)$password;

    $error = validate_username($normalized_username);
    if ($error !== null) {
        return array($normalized_username, $normalized_password, $error);
    }

    $error = validate_password($normalized_password);
    if ($error !== null) {
        return array($normalized_username, $normalized_password, $error);
    }

    if ($password_confirmation !== null && $normalized_password !== (string)$password_confirmation) {
        return array($normalized_username, $normalized_password, "Passwords do not match.");
    }

    return array($normalized_username, $normalized_password, null);
}

function validate_login_credential_pair($username, $password)
{
    $normalized_username = normalize_username($username);
    $normalized_password = (string)$password;

    $error = validate_username($normalized_username);
    if ($error !== null) {
        return array($normalized_username, $normalized_password, $error);
    }

    $error = validate_login_password($normalized_password);
    if ($error !== null) {
        return array($normalized_username, $normalized_password, $error);
    }

    return array($normalized_username, $normalized_password, null);
}

function validate_post_body($post_body)
{
    $normalized_post_body = trim((string)$post_body);
    if ($normalized_post_body === "") {
        return array($normalized_post_body, "Post content is required.");
    }

    if (strlen($normalized_post_body) < POST_MIN_LENGTH || strlen($normalized_post_body) > POST_MAX_LENGTH) {
        return array($normalized_post_body, "Post content must be between 1 and 2000 characters.");
    }

    return array($normalized_post_body, null);
}

function validate_comment_body($comment_body)
{
    $normalized_comment_body = trim((string)$comment_body);
    if ($normalized_comment_body === "") {
        return array($normalized_comment_body, "Comment content is required.");
    }

    if (strlen($normalized_comment_body) < COMMENT_MIN_LENGTH || strlen($normalized_comment_body) > COMMENT_MAX_LENGTH) {
        return array($normalized_comment_body, "Comment content must be between 1 and 1000 characters.");
    }

    return array($normalized_comment_body, null);
}

function validate_post_id($post_id)
{
    if (!is_scalar($post_id) || !preg_match('/^\d+$/', (string)$post_id)) {
        return array(null, "Invalid post identifier.");
    }

    $normalized_post_id = (int)$post_id;
    if ($normalized_post_id <= 0) {
        return array(null, "Invalid post identifier.");
    }

    return array($normalized_post_id, null);
}
?>
