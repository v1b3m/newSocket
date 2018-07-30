<?php
  $con = mysqli_connect("localhost","benjie","n0p@55w0RD","stringServer")
  or die('Unable to connect to database');
  $query = "SELECT * FROM  processed_jobs"; // Values shoud be changed according to the DB
  $data = mysqli_query($con, $query);

  $num = 0;
  $sum = 0;
  while($row = mysqli_fetch_array($data)){
    $num++;
    $sum += $row['processing_duration'];
  }

  $completed = mysqli_num_rows($data);

  $query1 = "SELECT * FROM blacklist";
  $data1 = mysqli_query($con,$query1);

  $failed = mysqli_num_rows($data1);

  $completion = $completed/($completed + $failed)*100;

  $average = $num/$sum;

?>

<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <meta http-equiv="X-UA-Compatible" content="ie=edge">
  <!-- <link rel="stylesheet"
  href="https://stackpath.bootstrapcdn.com/bootstrap/4.1.2/css/bootstrap.min.css"> -->
  <link rel="stylesheet" href="https://fonts.googleapis.com/css?family=Open+Sans:300,300i,400,600">
  <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/font-awesome/4.7.0/css/font-awesome.min.css">
  <link rel="stylesheet" href="css/bootstrap.min.css">
  <link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.0.6/css/all.css">
  <link rel="stylesheet" href="assets/css/animate.css">
  <link rel="stylesheet" href="assets/css/style.css">
  <link rel="stylesheet" href="assets/css/media-queries.css">
  <link rel="stylesheet" href="css/style.css">
  <link rel="shortcut icon" type="image/x-icon" href="favicon.ico" />
  <title>Home</title>
  <script>
window.onload = function () {

var chart = new CanvasJS.Chart("chartContainer", {
	animationEnabled: true,
	exportEnabled: true,
	theme: "light1", // "light1", "light2", "dark1", "dark2"
	title:{
		text: "Simple Column Chart showing average server processing speed"
	},
	data: [{
		type: "line", //change type to bar, line, area, pie, etc
		//indexLabel: "{y}", //Shows y value on all Data Points
		indexLabelFontColor: "#5A5757",
		indexLabelPlacement: "outside",
		dataPoints: [
			{ x: 0, y: 0 },
			{ x: <?php echo $average; ?>, y: 1 },


		]
	}]
});
chart.render();

}
</script>
</head>
<body>
  <div class="container-fluid">
    <nav class="navbar navbar-expand-lg navbar-dark bg-dark">
    <img src="favicon.png" alt="" style="width:50px;height:50px;">
    <a class="navbar-brand" href="#">C-String&trade;</a>
    <button class="navbar-toggler" type="button" data-toggle="collapse" data-target="#navbarSupportedContent" aria-controls="navbarSupportedContent" aria-expanded="false" aria-label="Toggle navigation">
      <span class="navbar-toggler-icon"></span>
    </button>

    <div class="collapse navbar-collapse" id="navbarSupportedContent">
      <ul class="navbar-nav mr-auto">
        <li class="nav-item active">
          <a class="nav-link" href="index.php">Home <span class="sr-only">(current)</span></a>
        </li>
        <li class="nav-item dropdown">
          <a class="nav-link dropdown-toggle" href="#" id="navbarDropdown" role="button" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">
            Job ratings
          </a>
          <div class="dropdown-menu" aria-labelledby="navbarDropdown">
            <a class="dropdown-item" href="highsuccess.php">Highest success rate</a>
            <a class="dropdown-item" href="lowsuccess.php">Lowest success rate</a>
            <!-- <div class="dropdown-divider"></div>
            <a class="dropdown-item" href="#">Something else here</a> -->
          </div>
        </li>
        <li class="nav-item">
          <a class="nav-link" href="waitingjobs.html">Waiting Jobs</a>
        </li>
        <li class="nav-item">
          <a class="nav-link" href="ready_jobs.php">Ready Jobs</a>
        </li>

      </ul>

    </div>
    </nav>
    <br/><br/>
    <div class="text-center">
      <h1>Average server processing</h1>
        <div id="chartContainer" style="height: 300px; width: 100%;"></div>
        <!-- <span class="chart" data-percent="90"></span> -->

      <br/><h5><span><?php echo round($average) .' jobs/s'; ?><i class="fa fa-arrow-circle-up"></i></span>
      <br/><br/>
     <span><?php echo round($completion); ?>% Job completion Accuracy</span></h5>
    </div>
  </div>
  <footer class="foot-color">
    <div class="footer-top">
      <div class="container">
        <div class="row">
          <div class="col-md-4 col-lg-4 footer-about wow fadeInUp">
            <img class="logo-footer" src="assets/img/logo.png" alt="logo-footer" data-at2x="assets/img/logo.png">
            <p>
              We are a young company always looking for new and creative ideas to help you with our products in your everyday work.
            </p>
            <p><a href="#">Our Team</a></p>
                </div>
          <div class="col-md-4 col-lg-4 offset-lg-1 footer-contact wow fadeInDown">
            <h3>Contact</h3>
                <p><i class="fas fa-map-marker-alt"></i> Luwum Street 10, 10136 Kampala Uganda</p>
                <p><i class="fas fa-phone"></i> Phone: +245 703 755 919 </p>
                <p><i class="fas fa-envelope"></i> Email: <a href="mailto:hello@domain.com">vibenjamin6@gmail.com</a></p>
                <p><i class="fab fa-skype"></i> Skype: v1b3m:live</p>
                </div>
                <div class="col-md-4 col-lg-3 footer-social wow fadeInUp">
                  <h3>Follow us</h3>
                  <p>
                    <a href="#"><i class="fab fa-facebook"></i></a>
          <a href="#"><i class="fab fa-twitter"></i></a>
          <a href="https://github.com/v1b3m/newSocket" target="_blank"><i class="fab fa-github-square"></i></a>
          <a href="#"><i class="fab fa-instagram"></i></a>
          <a href="#"><i class="fab fa-pinterest"></i></a>
                  </p>
                </div>
          </div>
      </div>
    </div>
    <div class="footer-bottom">
      <div class="container">
        <div class="row">
            <div class="col-md-5 footer-copyright">
                  <p>&copy;2018 All rights reserved C-String&trade;</p>
                </div>
            <div class="col-md-7 footer-menu">
                  <nav class="navbar navbar-dark navbar-expand-md">
            <button class="navbar-toggler" type="button" data-toggle="collapse" data-target="#navbarNav" aria-controls="navbarNav" aria-expanded="false" aria-label="Toggle navigation">
                <span class="navbar-toggler-icon"></span>
            </button>
            <div class="collapse navbar-collapse" id="navbarNav">
                <ul class="navbar-nav ml-auto">
                    <li class="nav-item">
                        <a class="nav-link scroll-link" href="#top-content">Top</a>
                    </li>
                    <li class="nav-item">
                        <a class="nav-link scroll-link" href="#section-1">Section 1</a>
                    </li>
                    <li class="nav-item">
                        <a class="nav-link scroll-link" href="#section-2">Section 2</a>
                    </li>
                    <li class="nav-item">
                        <a class="nav-link scroll-link" href="#section-3">Section 3</a>
                    </li>
                    <li class="nav-item">
                        <a class="nav-link scroll-link" href="#section-4">Section 4</a>
                    </li>
                </ul>
            </div>
        </nav>
                </div>
          </div>
      </div>
    </div>


</body>

<script type="text/javascript" src="js/jquery-3.3.1.min.js"></script>
<!-- Bootstrap tooltips -->
<script type="text/javascript" src="js/popper.min.js"></script>
<!-- Bootstrap core JavaScript -->
<script type="text/javascript" src="js/bootstrap.min.js"></script>
<!-- MDB core JavaScript -->
<!-- <script type="text/javascript" src="js/mdb.min.js"></script> -->
<!-- <script src="js/jquery.easypiechart.js"></script> -->
<script src="https://canvasjs.com/assets/script/canvasjs.min.js"></script>
<!-- <script>
    $(function () {
        $('.chart').easyPieChart({
            //put options here
        });
    });
</script> -->
</html>
