<?php

date_default_timezone_set('Europe/Moscow');
$datd = date("Y-m-d");
$datt = date("H:i:s");

$name = "wet";
if ( $name != "" )
	$name .= "-";

//printf("123<br/>");
//$arg = "";
//if ( !empty($_GET["dat"]) ){
//	$arg = $_GET["dat"];
//}
//printf("dat:[$arg]<br/>\n");

//$pth = "/var/www"

$pth = realpath(dirname(__FILE__)) . "/";
$logsh = $name . $datd . ".log";
$log = $pth . $logsh;
printf("logfile: $logsh<br/>\n");

if ( !file_exists($log) ){
	$file = fopen($log, "w+");
	fclose($file);
	chmod($log, 0660);
}

$str = file_get_contents($log);
printf("Data:<br/><br/>");
printf("<pre>\n");
printf("%s", $str);
printf("</pre><br/>");


?>
