<?php

	include_once("fn.php");

//	$t = get_string("t");
//	$h = get_string("h");
	$ip = get_string("ip");
//	$set = get_string("set");
//	$get = get_string("get");

	$dt = loadProfile();

	if ( strlen($ip) > 0 ){
//		$dt['t'] = floatval($t) - 3.5;
//		$dt['h'] = floatval($h);
//		$ip = $dt['ip'];
		$dt['ip'] = $ip;
		saveProfile($dt);
	}else{
		$ip = $dt['ip'];
//		$dt = loadProfile();
	}

//	echo "\n".$ip."\n";

	$title = "DHT22";
	$header = "Датчик температуры и влажности";
// --------------------------------------------

	showHeader($title, $header);

	$ti = $dt['t'];
	$hi = $dt['h'];

	if ( strlen($ip) > 0 ){
		if ( ($s = file_get_contents("http://".$ip)) !== false ){
//			echo "\n".$s."\n";
			if ( ($pos = strpos($s, "Temperature = ")) !== false ){
				$pos2 = strpos($s, ";", $pos + 14);
				$ti = floatval(trim(substr($s, $pos + 14, $pos2 - $pos - 15)));
			}
			if ( ($pos = strpos($s, "Humidity = ")) !== false ){
				$pos2 = strpos($s, ";", $pos + 11);
				$hi = floatval(trim(substr($s, $pos + 11, $pos2 - $pos - 12)));
			}
			$dt['t'] = $ti;
			$dt['h'] = $hi;
			saveProfile($dt);
		}
	}

//	$ip = $dt['ip'];

	echo "DHT22 (<a href='http://$ip'>$ip</a>) data:<br>";
	echo "T=$ti<br>";
	echo "H=$hi<br>";
	echo date("Y-m-d H:i:s", $dt['date'])."<br>";

//	phpinfo();
	header("Refresh: 10;");

	showEnd();

?>
