<?php

date_default_timezone_set('Europe/Moscow');
$datd = date("Y-m-d");
$datt = date("H:i:s");

$adr = $_SERVER['REMOTE_ADDR'];

//printf("123<br/>");
$arg = "";
if ( !empty($_GET["dat"]) ){
	$arg = $_GET["dat"];
}
printf("vcc:[$arg]<br/>\n");

//$pth = "/var/www"

$pth = realpath(dirname(__FILE__)) . "/"; //"/esp/";
$log = $pth . $datd . ".log";
printf("logfile: $log<br/>\n");

$fo = fopen($log, "at+");
if ( $fo ){
	fwrite($fo, "tm=$datt ip=$adr vcc=$arg\n");
	fclose($fo);
}

?>
