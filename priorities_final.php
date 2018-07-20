<?php 
	
time_sleep_until(time() + 60);
function priority () {
	$list = fopen('busylist.txt', 'r') or die ("Unable to open file!");

	while (!feof($list)) {
		$data = fgets($list);
		$infoArray = explode(",", $data);

		$strings = array();
		array_push($strings, $infoArray[2]);
		uasort($strings, function($a, $b){
			return strlen($b) <=> strlen($a)
		});

		$funName = array();
		array_push($funName, $infoArray[3]);

		for ($i = 0; $i <= count($strings); $i++) {
			if ($strings[0] == $strings[$i]){
				$priorities = fopen('priorities.txt', 'w+') or die ('Unable to open file!');
				$num = 1 \n;
				fwrite('priorities.txt', $num);
				fclose('priorities.txt');
			}
			else if ($funName[$i] == 'replace') {
				fopen('priorities', 'w') or die ('Unable to open file!');
				$num = 2\n;
				fwrite('priorities.txt', $num);
				fclose('priorities.txt');
			}
			else {
				fopen('priorities.txt', 'w');
				$num = 3\n;
				fwrite('priorities.txt', $num);
				fclose('priorities.txt');
			}
		}
	}
}

?>