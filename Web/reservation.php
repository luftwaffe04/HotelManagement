<!DOCTYPE html>
<html>
<head>
	<meta charset="UTF-8">
	<title>HaHa Hotel</title>
	<meta name="viewport" content="width=device-width,initial-scale=1.0,minimum-scale=1.0,maximum-scale=1.0,user-scalable=no">

	<link rel="stylesheet" type="text/css" href="./css/common.css">
	<link rel="stylesheet" type="text/css" href="./css/include.css">
	<link rel="stylesheet" type="text/css" href="./css/reservation_media.css">
	<link rel="stylesheet" type="text/css" href="./css/reservation.css">
	<link rel="stylesheet" type="text/css" href="./css/find.css">

	<script src="./js/jquery-3.5.1.min.js"></script>
	<script src="./js/jquery-ui.min.js"></script>
	<script src="./js/reservation.js"></script>
	<script src="./js/find.js"></script>
</head>
<body>
	<?php
		include_once 'header.php';
	?>


	<div class="wrap">
		<section id="reserve">
			<div class="hotelroom">
				<section>
					<p id="101" class="unchked">101</p>
					<p id="102" class="unchked">102</p>
					<p id="103" class="unchked">103</p>
					<p id="104" class="unchked">104</p>
					<p id="105" class="unchked">105</p>
				</section>
				<section>
					<p id="201" class="unchked">201</p>
					<p id="202" class="unchked">202</p>
					<p id="203" class="unchked">203</p>
					<p id="204" class="unchked">204</p>
					<p id="205" class="unchked">205</p>
				</section>
				<section>
					<p id="301" class="unchked">301</p>
					<p id="302" class="unchked">302</p>
					<p id="303" class="unchked">303</p>
					<p id="304" class="unchked">304</p>
					<p id="305" class="unchked">305</p>
				</section>
			</div>



			<form id="before">
				<section>
					<label for="hotel">Select Hotel</label>
					<input type="text" id="hotel" value="Seoul Haha Hotel" readonly>
				</section>

				<section>
					<label for="chkin">Check In</label>
					<input type="date" id="in_date">
				</section>

				<section>
					<label for="chkout">Check Out</label>
					<input type="date" id="out_date">
				</section>
			</form>



			<div class="roomdetail">
				<section>
					<p>Room</p>
					<section id="room1">
						<p>Personnel</p>
						<span class="plus">+</span>
						<span class="person">0</span>
						<span class="minus">-</span>
					</section>
				</section>

				<p class="submit">Submit</p>
			</div>



			<div class="aftersubmit">
				<div>
					<h2>Reservation Details</h2>
					<form method="post" action="./phpclass/process.php">
						<section class="rno">
							<label>Room No : </label>
							<input type="text" id="rno" name="rno" value="" readonly>
						</section>
						<section class="chkin">
							<label>Check In Time : </label>
							<input type="text" id="chkin" name="chkin" value="" readonly>
						</section>
						<section class="chkout">
							<label>Check Out Time : </label>
							<input type="text" id="chkout" name="chkout" value="" readonly>
						</section>
						<section class="pers">
							<label>Personnel : </label>
							<input type="text" id="pers" name="pers" value="" readonly>
						</section>
						<section class="rname">
							<label>Reservation name : </label>
							<input type="text" id="name" name="name" value="" />
						</section>
						<section class="passwd">
							<label>Password : </label>
							<input type="password" id="passwd" name="passwd" value="" />
						</section>
						<section class="telep">
							<label>Telephone : </label>
							<input type="tel" id="telep" name="telep" value="">
						</section>
						<input type="submit" id="submit" value="Submit">
						<input type="button" id="cancel" value="X">
					</form>
				</div>
			</div>
		</section>
	</div>



	<?php
		include_once 'find.php';
		include_once 'footer.php';
	?>
</body>
</html>
