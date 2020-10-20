<!DOCTYPE html>
<html>
<head>
	<meta charset="UTF-8">
	<title>HaHa Hotel</title>
	<meta name="viewport" content="width=device-width,initial-scale=1.0,minimum-scale=1.0,maximum-scale=1.0,user-scalable=no">

	<link rel="stylesheet" type="text/css" href="./css/common.css">
	<link rel="stylesheet" type="text/css" href="./css/index_media.css">
	<link rel="stylesheet" type="text/css" href="./css/index.css">
	<link rel="stylesheet" type="text/css" href="./css/find.css">

	<script src="./js/jquery-3.5.1.min.js"></script>
	<script src="./js/jquery-ui.min.js"></script>
	<script src="./js/main.js"></script>
	<script src="./js/find.js"></script>
</head>
<body>
	<div class="wrap">
		<header id="header">
			<h1>
				<a href="./index.php">
					<img src="./img/hotel.svg" alt="Hotel Icon" /> Haha hotel
				</a>
			</h1>
			<nav>
				<ul>
					<li class="findhotel"><a href="">Find Hotel</a></li>
					<li><a href="./reservation.php">Reservation</a></li>
					<li><a href="./introduce.php">Introduce</a></li>
					<li><a href="./faq.php">FAQ</a></li>
				</ul>
			</nav>

			<footer id="footer">
				<address>Contact Us : <span>02-1234-1234</span> <span>Sangong Convential, Sejong Dae-ro 39, Jung-gu, Seoul</span></address>
				<p>Copyright © 2020 HaHa Hotel.co.,Ltd. All rights reserved.</p>
				<address>Contact webmaster for more information. 010-1234-1234</address>
			</footer>
		</header>
	</div>

	<nav class="hamburger">
		<img src="./img/menu.svg" alt="Menu Button" />
	</nav>

	<section id="mainImage"></section>
	<div class="shadow">
		<article>
			<h2>Welcome to <span>The Haha Hotel</span></h2>
			<p><span>The Hotel Haha</span> has been playing a role as a driving force in Korea`s service industry with pride and responsibility as"a face representing Samsung Group" and"a hotel representing Korea" through numerous visits and international events by Gubin.</p>
			<p><span>The Hotel Haha</span> is derived from the name of the Shilla Dynasty, which bloomed the most brilliant culture and arts with a thousand years of history, and opened in March 1979 at the will of the first president.</p>
			<p><span>The Hotel Haha</span> has been captivating the hearts of customers by maintaining its dignity and tradition for a long time with the goal of becoming the"best hospitality company". By joining LHW, it has been transformed into a premium lifestyle space that stands shoulder to shoulder with the world`s best luxury hotels, while adding modernist design elements on the roof of tradition to further enhance the leisure and dignity of life. <span>The Hotel Haha</span> promises to grow into a prestigious global hospitality company that provides differentiated and best values ​​based on ceaseless creative innovation and challenges.</p>
		</article>
	</div>
	<?php
		include_once 'find.php';
	?>
</body>
</html>
