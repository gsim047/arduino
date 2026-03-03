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
	$buf = "";
	foreach ( $_REQUEST as $key => $value ){
		printf("$key:[$value]<br/>\n");
		$buf = $buf . "$key:[$value] ";
	}
	fwrite($fo, "$datt ip:[$adr] $buf\n");
//	fwrite($fo, "tm=$datt ip=$adr vcc=$arg\n");
	fclose($fo);
}

printf("<br/><br/><br/>");

$cfg = $pth . "esp.cfg";
printf("cfgfile: $cfg<br/>\n");

$cfgip = $pth . $adr . ".cfg";
printf("ipfile: $cfgip<br/>\n");

$str = file_get_contents($cfg) . "\n" . file_get_contents($cfgip);

printf("Cfg:<br/>-[--<br/>");
printf("<pre>\n");
printf("%s", $str);
printf("</pre><br/>-]--<br/>");

?>
