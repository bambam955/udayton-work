<?php
require_once __DIR__ . "/../src/database.php";
require_once __DIR__ . "/../src/credential_validation.php";
require_once __DIR__ . "/../src/session_auth.php";

start_secure_session();
require_valid_csrf_token_from_post();

list($username, $password, $validation_error) = validate_login_credential_pair(
    isset($_POST["username"]) ? $_POST["username"] : null,
    isset($_POST["password"]) ? $_POST["password"] : null
);

if ($validation_error !== null) {
    destroy_session();
    redirect_with_alert($validation_error, "login.php");
}

$role = securechecklogin($username, $password);
if ($role !== FALSE) {
    session_regenerate_id(true);
    $_SESSION["last_regenerated_at"] = time();
    $_SESSION["logged"] = TRUE;
    $_SESSION["username"] = $username;
    $_SESSION["role"] = $role;
    $_SESSION["browser"] = $_SERVER["HTTP_USER_AGENT"];
    $redirect_target = ($role === "admin") ? "admin.php" : "index.php";
    header("Location: " . $redirect_target);
    exit();
}

destroy_session();
redirect_with_alert("Invalid username/password", "login.php");

function securechecklogin($username, $password)
{
    global $mysqli;

    $prepared_sql = "SELECT role FROM users WHERE username= ? AND password=md5(?)";
    if (!$stmt = $mysqli->prepare($prepared_sql)) {
        echo "Prepared Statement Error";
        exit();
    }

    $stmt->bind_param("ss", $username, $password);

    if (!$stmt->execute()) {
        echo "Execute Error";
        exit();
    }

    if (!$stmt->store_result()) {
        echo "Store result Error";
        exit();
    }

    if ($stmt->num_rows != 1) {
        return FALSE;
    }

    $stmt->bind_result($role);
    if (!$stmt->fetch()) {
        return FALSE;
    }

    return $role;
}
?>
