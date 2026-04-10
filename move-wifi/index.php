<?php

date_default_timezone_set('Europe/Moscow');
$datd = date("Y-m-d");
$datt = date("H:i:s");

//printf("123<br/>");
//$arg = "";
//if ( !empty($_GET["dat"]) ){
//	$arg = $_GET["dat"];
//}
//printf("dat:[$arg]<br/>\n");

$name = "move";
$name1 = $name;
if ( $name1 != "" )
	$name1 += "-";
//$pth = "/var/www"

$pth = realpath(dirname(__FILE__)) . "/";
$logsh = $name1 . $datd . ".log";
$log = $pth . $logsh;
printf("logfile: $logsh<br/>\n");

if ( !file_exists($log) ){
	$file = fopen($log, "w+");
	fclose($file);
}

$str = file_get_contents($log);
printf("Data:<br/><br/>");
printf("<pre>\n");
printf("%s", $str);
printf("</pre><br/>");


?>
