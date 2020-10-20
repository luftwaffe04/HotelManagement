<?php
	include_once './dbinfo.php';
	$dbconn = IsConnectDB($db);

	function IsConnectDB($db)
	{
		$conn = mysqli_connect($db['host'], $db['user'], $db['pass'], $db['name'], $db['port']);
		mysqli_set_charset($conn, "utf8");

		if(mysqli_connect_errno()) {
			echo "Failed to connect to MariaDB : ".mysqli_connect_error();
			exit;
		}
		else {
			return $conn;
		}
	}
?>
