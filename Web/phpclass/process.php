<?php
	include_once './dbconnect.php';
	$prevPage = $_SERVER['HTTP_REFERER']; // 이전 페이지 정보 저장
	// 데이터 저장
	$roomno = $_POST['rno'];
	$chkin = date("Y-m-d", strtotime($_POST['chkin']));
	$chkout = date("Y-m-d", strtotime($_POST['chkout']));
	$person = $_POST['pers'];
	$name = $_POST['name'];
	$passwd = $_POST['passwd'];
	$telephone = $_POST['telep'];

	// sql 쿼리 실행
	$sql = "update reserve set reserve_state = '1', name = '".$name."', password=HEX(AES_ENCRYPT('".$passwd."', '".$name."')), chkin = '".$chkin."', chkout = '".$chkout."', crew = '".$person."', telephone = '".$telephone."' where room_id = '".$roomno."';";
	mysqli_query($dbconn, $sql);

	header('location:'.$prevPage); // 이전 페이지로 돌아가기
?>
