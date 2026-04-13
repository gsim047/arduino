<?php


date_default_timezone_set('Europe/Moscow');
$datd = date("Y-m-d");
$datt = date("H:i:s");

$name = "wet";
$name0 = $name;
if ( $name != "" )
	$name .= "-";
else
	$name0 = "esp";

$adr = $_SERVER['REMOTE_ADDR'];

//printf("123<br/>");
$arg = "";
if ( !empty($_GET["dat"]) ){
	$arg = $_GET["dat"];
}
//printf("vcc:[$arg]<br/>\n");


$pth = realpath(dirname(__FILE__)) . "/"; //"/esp/";
$logsh = $name . $datd . ".log";
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

$cfg = $pth . $name0 . ".cfg";  // esp.cfg
//printf("cfgfile: $cfg<br/>\n");
if ( !file_exists($cfg) ){
	$file = fopen($cfg, "w+");
	fclose($file);
	chmod($cfg, 0660);
}
$str = file_get_contents($cfg) . "\n"; // read esp.cfg


// add date & time
$str .= "\ndate=" . $datd . "\ntime=" . $datt . "\n";


$cfgip = $pth . "ip-" . $adr . ".cfg";
//printf("ipfile: $cfgip<br/>\n");
if ( !file_exists($cfgip) ){
	$file = fopen($cfgip, "w+");
	fclose($file);
	chmod($cfgip, 0660);
}
$str .= file_get_contents($cfgip) . "\n"; // read ip-.cfg


if ( $mac != "" ){
	$cfgmac = $pth . "mac-" . $mac . ".cfg";
	//printf("ipfile: $cfgip<br/>\n");
	if ( !file_exists($cfgmac) ){
		$file = fopen($cfgmac, "w+");
		fwrite($file, "# ip=$adr\n\n");
		fclose($file);
		chmod($cfgmac, 0660);
	}

	$str .= file_get_contents($cfgmac) . "\n";
}

printf("Cfg:<br/>-[--<br/>");
printf("<pre>\n");
printf("%s", $str);
printf("</pre><br/>-]--<br/>");

?>
