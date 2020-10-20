<?php
	include_once './dbconnect.php';

	// sql 쿼리 실행
	$sql = "select room_id from reserve where reserve_state = '1';";
	$result = mysqli_query($dbconn, $sql);

	while($row = mysqli_fetch_array($result)) {
		echo $row['room_id'].',';
	}

	echo '_';

	$sql = "select room_id from reserve where reserve_state = '0';";
	$result = mysqli_query($dbconn, $sql);

	while($row = mysqli_fetch_array($result)) {
		echo $row['room_id'].',';
	}
?>
