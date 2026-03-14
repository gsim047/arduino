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

$mac = "";
//$pth = "/var/www"

$pth = realpath(dirname(__FILE__)) . "/"; //"/esp/";
$log = $pth . $datd . ".log";
printf("logfile: $log<br/>\n");

//if ( !file_exists($log) ){
//	$f = fopen($log, "wt");
//	fclose($f);
//}

$fo = fopen($log, "at+");
if ( $fo ){
	$buf = "";
	foreach ( $_REQUEST as $key => $value ){
		printf("$key:[$value]<br/>\n");
		$buf = $buf . "$key:[$value] ";
		if ( $key == "mac" ){
			$mac = $value;
		}
	}
	fwrite($fo, "$datt ip:[$adr] $buf\n");
//	fwrite($fo, "tm=$datt ip=$adr vcc=$arg\n");
	fclose($fo);
}

printf("<br/><br/><br/>");

$cfg = $pth . "esp.cfg";
printf("cfgfile: $cfg<br/>\n");

if ( !file_exists($cfg) ){
	$f = fopen($cfg, "wt");
	fclose($f);
}

$cfgip = $pth . $adr . ".cfg";
printf("ipfile: $cfgip<br/>\n");

if ( !file_exists($cfgip) ){
	$f = fopen($cfgip, "wt");
	fclose($f);
}

$str = file_get_contents($cfg) . "\ndate=" . $datd . "\ntime=" . $datt . "\n" . file_get_contents($cfgip);
if ( $mac != "" ){
	$cfgmac = $pth . $mac . ".cfg";
	printf("macfile: $cfgmac<br/>\n");
	if ( !file_exists($cfgmac) ){
		$f = fopen($cfgmac, "wt");
		fclose($f);
	}
	$str = $str . "\n" . file_get_contents($cfgmac);
}

printf("Cfg:<br/>-[--<br/>");
printf("<pre>\n");
printf("%s", $str);
printf("</pre><br/>-]--<br/>");

?>
