<?php
require_once __DIR__ . "/credential_validation.php";

$mysqli = new mysqli('localhost', 'secad_team2_user', 'secad_team2_pw', 'secad_minifacebook');

if ($mysqli->connect_errno) {
    printf("Database connection failed: %s\n", $mysqli->connect_error);
    exit();
}

function addnewuser($username, $password, $role = "user")
{
    global $mysqli;

    // Defend the database layer even if a caller skips the form/controller checks.
    list($username, $password, $validation_error) = validate_credential_pair($username, $password);
    if ($validation_error !== null) {
        return FALSE;
    }

    // Keep the role assignment server-controlled and limited to the allowed RBAC set.
    if ($role !== "user" && $role !== "admin") {
        return FALSE;
    }

    // New registrations always start with the lowest privilege role unless a
    // trusted caller explicitly seeds admin accounts.
    $prepared_sql = "INSERT INTO users(username, password, role) VALUES (?, md5(?), ?);";

    if (!$stmt = $mysqli->prepare($prepared_sql)) {
        return FALSE;
    }

    $stmt->bind_param("sss", $username, $password, $role);

    if (!$stmt->execute()) {
        return FALSE;
    }

    return TRUE;
}

function changepassword($username, $newpassword)
{
    global $mysqli;

    // Reuse the shared credential rules so direct calls cannot bypass them.
    list($username, $newpassword, $validation_error) = validate_credential_pair($username, $newpassword);
    if ($validation_error !== null) {
        return FALSE;
    }

    $prepared_sql = "UPDATE users SET password=md5(?) WHERE username=?;";

    if (!$stmt = $mysqli->prepare($prepared_sql)) {
        return FALSE;
    }

    $stmt->bind_param("ss", $newpassword, $username);

    if (!$stmt->execute()) {
        return FALSE;
    }

    return TRUE;
}

function get_all_users()
{
    global $mysqli;

    $prepared_sql = "SELECT username, role FROM users ORDER BY username ASC";
    if (!$stmt = $mysqli->prepare($prepared_sql)) {
        return FALSE;
    }

    if (!$stmt->execute()) {
        return FALSE;
    }

    $result = $stmt->get_result();
    if ($result === FALSE) {
        return FALSE;
    }

    $users = array();
    while ($row = $result->fetch_assoc()) {
        $users[] = $row;
    }

    $result->free();

    return $users;
}

function add_post($username, $post_body)
{
    global $mysqli;

    $username = normalize_username($username);
    if (validate_username($username) !== null) {
        return FALSE;
    }
    list($post_body, $post_error) = validate_post_body($post_body);
    if ($post_error !== null) {
        return FALSE;
    }

    $prepared_sql = "INSERT INTO posts (username, body) VALUES (?, ?)";
    if (!$stmt = $mysqli->prepare($prepared_sql)) {
        return FALSE;
    }

    $stmt->bind_param("ss", $username, $post_body);
    return $stmt->execute();
}

function add_comment($post_id, $username, $comment_body)
{
    global $mysqli;

    $username = normalize_username($username);
    if (validate_username($username) !== null) {
        return FALSE;
    }
    list($post_id, $post_id_error) = validate_post_id($post_id);
    if ($post_id_error !== null) {
        return FALSE;
    }
    list($comment_body, $comment_error) = validate_comment_body($comment_body);
    if ($comment_error !== null) {
        return FALSE;
    }

    $prepared_sql = "INSERT INTO comments (post_id, username, body) VALUES (?, ?, ?)";
    if (!$stmt = $mysqli->prepare($prepared_sql)) {
        return FALSE;
    }

    $stmt->bind_param("iss", $post_id, $username, $comment_body);
    return $stmt->execute();
}

function get_post_by_id($post_id)
{
    global $mysqli;

    list($post_id, $post_id_error) = validate_post_id($post_id);
    if ($post_id_error !== null) {
        return FALSE;
    }

    $prepared_sql = "SELECT id, username, body, created_at, updated_at FROM posts WHERE id = ?";
    if (!$stmt = $mysqli->prepare($prepared_sql)) {
        return FALSE;
    }

    $stmt->bind_param("i", $post_id);
    if (!$stmt->execute()) {
        return FALSE;
    }

    $result = $stmt->get_result();
    if ($result === FALSE) {
        return FALSE;
    }

    $post = $result->fetch_assoc();
    $result->free();
    return $post;
}

function update_post_if_owner($post_id, $username, $post_body)
{
    global $mysqli;

    $username = normalize_username($username);
    if (validate_username($username) !== null) {
        return FALSE;
    }
    list($post_id, $post_id_error) = validate_post_id($post_id);
    if ($post_id_error !== null) {
        return FALSE;
    }
    list($post_body, $post_error) = validate_post_body($post_body);
    if ($post_error !== null) {
        return FALSE;
    }

    $prepared_sql = "UPDATE posts SET body = ?, updated_at = CURRENT_TIMESTAMP WHERE id = ? AND username = ?";
    if (!$stmt = $mysqli->prepare($prepared_sql)) {
        return FALSE;
    }

    $stmt->bind_param("sis", $post_body, $post_id, $username);
    if (!$stmt->execute()) {
        return FALSE;
    }

    return $stmt->affected_rows === 1;
}

function get_posts_with_comments()
{
    global $mysqli;

    $prepared_sql = "SELECT p.id AS post_id, p.username AS post_username, p.body AS post_body, p.created_at AS post_created_at, p.updated_at AS post_updated_at, c.id AS comment_id, c.username AS comment_username, c.body AS comment_body, c.created_at AS comment_created_at FROM posts p LEFT JOIN comments c ON c.post_id = p.id ORDER BY p.created_at DESC, c.created_at ASC";
    if (!$stmt = $mysqli->prepare($prepared_sql)) {
        return FALSE;
    }

    if (!$stmt->execute()) {
        return FALSE;
    }

    $result = $stmt->get_result();
    if ($result === FALSE) {
        return FALSE;
    }

    $posts = array();
    while ($row = $result->fetch_assoc()) {
        $post_id = (int)$row["post_id"];
        if (!isset($posts[$post_id])) {
            $posts[$post_id] = array(
                "id" => $post_id,
                "username" => $row["post_username"],
                "body" => $row["post_body"],
                "created_at" => $row["post_created_at"],
                "updated_at" => $row["post_updated_at"],
                "comments" => array(),
            );
        }

        if ($row["comment_id"] !== null) {
            $posts[$post_id]["comments"][] = array(
                "id" => (int)$row["comment_id"],
                "username" => $row["comment_username"],
                "body" => $row["comment_body"],
                "created_at" => $row["comment_created_at"],
            );
        }
    }

    $result->free();
    return array_values($posts);
}
?>
