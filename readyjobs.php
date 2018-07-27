<?php
  $servername = "localhost";
  $username = "benjie";
  $password = "n0p@55w0RD";
  $dbname = "stringServer";

  // Create connection
  $conn = mysqli_connect($servername, $username, $password,$dbname);

  // Check connection
  if (!$conn) {
    die("Connection failed: " . mysqli_connect_error());
  }
  echo "Connected successfully<br/>";

  $myfile = fopen('/var/www/html/stringServer/ready_jobs.txt','r+') or die ('Unable to open readyjobs');

  //output one line until end-of-file
  while(!feof($myfile)) {
    $data = fgets($myfile);
    $datum = explode(",",$data);

    $sql = "INSERT INTO processed_jobs VALUES (0,$datum[0],'$datum[1]','$datum[2]','$datum[3]')";

    //query the database
    if (mysqli_query($conn, $sql)) {
    echo "New record created successfully<br/>";
    } else {
      echo "Error: " . $sql . "<br>" . mysqli_error($conn);
    }
  }

  ftruncate($myfile,0);
  fclose($myfile);

  $blacklist = fopen('/var/www/html/stringServer/blacklist.txt','r+') or die ('Unable to open blacklist');
  //output one line until end-of-file
  while(!feof($blacklist)) {
    $data = fgets($blacklist);
    $datum = explode(",",$data);

    $sql = "INSERT INTO blacklist VALUES (0,$datum[0],'$datum[1]')";

    //query the database
    if (mysqli_query($conn, $sql)) {
    echo "New record created successfully<br/>";
    } else {
      echo "Error: " . $sql . "<br>" . mysqli_error($conn);
    }
  }


  mysqli_close($conn);
  ftruncate($blacklist,0);
  fclose($blacklist);

?>
