<?php

date_default_timezone_set('Europe/Moscow');
$datd = date("Y-m-d");
$datt = date("H-i-s");

//printf("123<br/>");
$arg = "";
if ( !empty($_GET["dat"]) ){
	$arg = $_GET["dat"];
}
printf("dat:[$arg]<br/>\n");

//$pth = "/var/www"

$pth = realpath(dirname(__FILE__)) . "/dat/";
$log = $pth . $datd . ".log";
printf("logfile: $log<br/>\n");

$fo = fopen($log, "at+");
if ( $fo ){
	fwrite($fo, "$datt: $arg\n");
	fclose($fo);
}

?>
