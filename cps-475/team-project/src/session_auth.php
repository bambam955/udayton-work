<?php
// Keep the session cookie scoped to the app root so the new public/ layout
// and deployed document root share the same browser session.
function start_secure_session()
{
    $lifetime = 15 * 60;

    if (session_status() !== PHP_SESSION_ACTIVE) {
        session_set_cookie_params(array(
            "lifetime" => $lifetime,
            "path" => "/",
            "domain" => "",
            "secure" => TRUE,
            "httponly" => TRUE,
            "samesite" => "Strict",
        ));
        session_start();
    }

    if (!isset($_SESSION["last_regenerated_at"])) {
        $_SESSION["last_regenerated_at"] = time();
    }
}

function destroy_session()
{
    if (session_status() !== PHP_SESSION_ACTIVE) {
        return;
    }

    // Delete both the server-side session and the browser cookie.
    $_SESSION = [];

    if (ini_get("session.use_cookies")) {
        $params = session_get_cookie_params();
        setcookie(
            session_name(),
            "",
            time() - 42000,
            $params["path"],
            $params["domain"],
            $params["secure"],
            $params["httponly"]
        );
    }

    session_destroy();
}

function redirect_with_alert($message, $target)
{
    echo "<script>alert(" . json_encode($message) . "); window.location = " . json_encode($target) . ";</script>";
    exit();
}

function require_authenticated_session()
{
    enforce_authenticated_session();
}

function require_admin_session()
{
    enforce_authenticated_session();

    // Admin-only pages can call this helper without repeating the same session checks.
    if (!isset($_SESSION["role"])) {
        destroy_session();
        redirect_with_alert("You do not have permission to access this page.", "login.php");
    }

    if ($_SESSION["role"] === "admin") {
        return;
    }

    // Logged-in non-admin users should fall back to the normal home page.
    if ($_SESSION["role"] === "user") {
        header("Location: index.php");
        exit();
    }

    // Treat any unexpected role value as a compromised session state.
    destroy_session();
    redirect_with_alert("You do not have permission to access this page.", "login.php");
}

function enforce_authenticated_session()
{
    start_secure_session();

    if (!isset($_SESSION["logged"]) || $_SESSION["logged"] != TRUE) {
        destroy_session();
        redirect_with_alert("You have to login first!", "login.php");
    }

    if (!isset($_SESSION["browser"]) || $_SESSION["browser"] != $_SERVER["HTTP_USER_AGENT"]) {
        destroy_session();
        redirect_with_alert("Session hijacking attack is detected!", "login.php");
    }

    rotate_session_id_if_needed();
}

function rotate_session_id_if_needed()
{
    $rotation_interval_seconds = 5 * 60;
    if (!isset($_SESSION["last_regenerated_at"])) {
        $_SESSION["last_regenerated_at"] = time();
        return;
    }

    if ((time() - (int)$_SESSION["last_regenerated_at"]) >= $rotation_interval_seconds) {
        session_regenerate_id(TRUE);
        $_SESSION["last_regenerated_at"] = time();
    }
}

function get_csrf_token()
{
    start_secure_session();

    if (!isset($_SESSION["csrf_token"])) {
        $_SESSION["csrf_token"] = bin2hex(random_bytes(32));
    }

    return $_SESSION["csrf_token"];
}

function require_valid_csrf_token_from_post()
{
    start_secure_session();

    $submitted_token = isset($_POST["csrf_token"]) ? (string)$_POST["csrf_token"] : "";
    if (!isset($_SESSION["csrf_token"]) || !hash_equals($_SESSION["csrf_token"], $submitted_token)) {
        destroy_session();
        redirect_with_alert("Invalid CSRF token.", "login.php");
    }
}
