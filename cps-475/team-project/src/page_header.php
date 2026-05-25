<?php
// Shared page chrome for the public-facing pages.
function render_page_header($page_purpose, $show_team_members = TRUE)
{
    $page_purpose = htmlspecialchars($page_purpose, ENT_QUOTES, "UTF-8");
    ?>
<!DOCTYPE html>
<html lang="en">

<head>
	<meta charset="utf-8">
	<meta name="viewport" content="width=device-width, initial-scale=1">
	<title>MiniFacebook | SecAD</title>
	<link rel="stylesheet" href="styles.css">
</head>

<body>
	<main class="page-shell">
		<section class="card">
			<header class="page-header">
				<p class="eyebrow"><small>MiniFacebook | SecAD</small></p>
				<h1><?php echo $page_purpose; ?></h1>
			</header>
<?php if ($show_team_members) : ?>
	<!-- Keep the team attribution consistent across all public pages. -->
			<div class="team-block">
				<h2>By TEAM 2</h2>
				<p>Bennett Moore, [mooreb26@udayton.edu]</p>
				<p>Thomas Pruett, [pruettt1@udayton.edu]</p>
				<p>Alex Testa, [testaa2@udayton.edu]</p>
			</div>
<?php endif; ?>
<?php
}

function render_page_footer()
{
    ?>
		</section>
	</main>
</body>

</html>
<?php
}
