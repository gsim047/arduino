<?php

date_default_timezone_set('Europe/Moscow');
$datd = date("Y-m-d");
$datt = date("H:i:s");

$name = "move";
$name1 = $name;
//$pth = "/var/www"
if ( $name1 != "" )
	$name1 += "-";


$adr = $_SERVER['REMOTE_ADDR'];

//printf("123<br/>");
$arg = "";
if ( !empty($_GET["dat"]) ){
	$arg = $_GET["dat"];
}
printf("vcc:[$arg]<br/>\n");

$pth = realpath(dirname(__FILE__)) . "/"; //"/esp/";
$logsh = $name1 . $datd . ".log";
$log = $pth . $logsh;
printf("logfile: $logsh<br/>\n");

$mac = "";

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

$cfg = $pth . $name . ".cfg";
//printf("cfgfile: $cfg<br/>\n");
if ( !file_exists($cfg) ){
	$file = fopen($cfg, "w+");
	fclose($file);
}

$cfgip = $pth . "ip-" . $adr . ".cfg";
//printf("ipfile: $cfgip<br/>\n");
if ( !file_exists($cfgip) ){
	$file = fopen($cfgip, "w+");
	fclose($file);
}

$str = file_get_contents($cfg) . "\ndate=" . $datd . "\ntime=" . $datt . "\n" . file_get_contents($cfgip);

if ( $mac != "" ){
	$cfgmac = $pth . "mac-" . $mac . ".cfg";
	//printf("ipfile: $cfgip<br/>\n");
	if ( !file_exists($cfgmac) ){
		$file = fopen($cfgmac, "w+");
		fwrite($file, "# ip=$adr\n\n");
		fclose($file);
	}

	$str = $str . "\n" . file_get_contents($cfgmac);
}

printf("Cfg:<br/>-[--<br/>");
printf("<pre>\n");
printf("%s", $str);
printf("</pre><br/>-]--<br/>");

?>
