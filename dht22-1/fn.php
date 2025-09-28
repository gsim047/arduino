<?php

//	include_once("info.php");
/*
	$vname = "Beloe.Solntse.Pustyni";
	$vyear = "1969";
	$title = $vname.".".$vyear;
	$video = $title.".RUS.DVDRip.XviD.AC3.-ENGINEER".".mp4";
	$poster = $vname.".jpg";

	$header = "Белое солнце пустыни".", ".$vyear;
	$width = 720;
	$nn = 1;
*/

// строка из _POST/_GET
function get_string($str)
{
	$s = "";
	if ( isset($_POST[$str]) ){
		$s = $_POST[$str];
	}else if ( isset($_GET[$str]) ){
		$s = $_GET[$str];
	}
	return $s;
}


// --------------------------------------------

function mkAI($i, $size = 2)
{
	$ai = "$i"; 
	while ( strlen($ai) < $size ){
		$ai = "0".$ai;
	}
	return $ai;
}


// $i      - номер ролика
// $sz     - размер (в цифрах) числового поля номера ролика в имени файла
// $in     - локальное название ролика
// $video  - имя файла ролика (символами '##' обозначено место номера в имени файла)
// $poster - имя файла обложки ролика (символами '##' обозначено место номера в имени файла)
function mkPlayer($i, $sz, $in, $video, $poster, $width)
{
	echo "<div style='width:".$width."px'>";
	if ( strlen($in) > 0 ){
		echo "$in<br>";
	}

	$ai = mkAI($i, $sz);

	$poster2 = str_replace("##", $ai, $poster);
	$video2 = str_replace("##", $ai, $video);
//echo "<br>poster: $poster / $poster2<br>";
//echo "<br>video:  $video / $video2<br>";

	echo "<video id='player$ai' poster='".$poster2."' playsinline controls>";
	echo "	<source src='".$video2."' type='video/mp4' />";
	echo "</video>";
	echo "</div>";
	echo "<br><br>";
}


function showHeader($title, $header)
{
	echo "<!DOCTYPE html>";
	echo "<html>";
	echo "	<head>";
	echo "		<title>$title</title>";

//	echo '<link rel="stylesheet" href="https://cdn.plyr.io/3.6.2/plyr.css" />';

	echo "	</head>";

	echo "	<body>";
//	echo "	<a href='..'><img src='/back.gif'></a><br>";
	echo "	<h1>$header</h1>";
}


function showEnd()
{
//	echo "<script src='https://cdn.plyr.io/3.6.2/plyr.polyfilled.js'></script>";
//	echo "<script>";
//	echo "	const player = new Plyr('#player');";
//	echo "</script>";

	echo "	</body>";
	echo "</html>";
}


function saveProfile($data)
{
//	logMsg("saveProfile");
	if ( isset($data) ){
//		$chat_id = $user['chat_id'];
		$data['date'] = time();
		$file = "data.json"; //getProfilePath($chat_id);
//		logMsg("saveProfile: $chat_id to [$file]");

		ob_start();
		print_r(json_encode($data));
		$out = ob_get_clean();
		file_put_contents($file, $out);
	}
}// saveProfile


function newProfile($t, $h, $ip)
{
//	logMsg("newProfile $chat_id, $username");
	// art => id, state, number
	$art = array();
	$data = array(
		't' => $t,
		'h' => $h,
		'ip' => $ip,
		'date' => time(),
	);
//	mkdir(__DIR__ . "/$chat_id", 0777);
	return $data;
}// newProfile


function loadProfile()
{
	$file = "data.json"; //getProfilePath($chat_id);
//	logMsg("loadProfile $chat_id, $username [$file]");

	if ( !file_exists($file) ){

		$data = newProfile(0, 0, '127.0.0.1');
//		$user['chat_username'] = $username;
		saveProfile($data);
		chmod($file, 0666);
	}

	$arr = file_get_contents($file);
	return json_decode($arr, true);
}// loadProfile


// --------------------------------------------
?>
