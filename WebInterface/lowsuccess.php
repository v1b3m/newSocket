<?php
 $con = mysqli_connect("localhost","benjie","n0p@55w0RD","stringServer");
 $query = "SELECT * FROM blacklist";
 $data = mysqli_query($con, $query);

 while($row = mysqli_fetch_array($data)){
   $arr[] = $row['userId'];
 }

 $values = array_count_values($arr);
 arsort($values);
 $popular_with_count = array_slice($values,0,10,true);
 $popular = array_keys($popular_with_count);
 $popular_count = array_values($popular_with_count);

 foreach($popular as $i) {
   $query1 = "SELECT * FROM processed_jobs WHERE user_id = $i";
   $data1 = mysqli_query($con,$query1);
   $success_count[] = mysqli_num_rows($data1); 
 }

//  foreach($failedcount as $i)
//  {
//    echo $i." ";
//  }

 for($i=0;$i<10;$i++)
 {
   $average[] = $popular_count[$i]/($success_count[$i]+$popular_count[$i])*100;
 }  
 
?>

<!DOCTYPE html>
<html>

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
  <title>Low Success Rating</title>
</head>

<body>
  <div class="container-fluid">
    <nav class="navbar navbar-expand-lg navbar-dark bg-dark">
    <a class="navbar-brand" href="#">C-String&trade;</a>
    <button class="navbar-toggler" type="button" data-toggle="collapse" data-target="#navbarSupportedContent" aria-controls="navbarSupportedContent" aria-expanded="false" aria-label="Toggle navigation">
      <span class="navbar-toggler-icon"></span>
    </button>

    <div class="collapse navbar-collapse" id="navbarSupportedContent">
      <ul class="navbar-nav mr-auto">
        <li class="nav-item active">
          <a class="nav-link" href="index.html">Home <span class="sr-only">(current)</span></a>
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
          <a class="nav-link" href="ready_jobs.html">Ready Jobs</a>
        </li>
      </ul>

    </div>
    </nav>
    <br>
    <h1>Least Successfull Jobs</h1>
    <br>
    <div class="text-center">
        <table class="table">
          <thead class="thead-dark">
            <tr>
              <th scope="col">#</th>
              <th scope="col">Student Job</th>
              <th scope="col">Failures</th>
              <th scope="col">Successes</th>
              <th scope="col">Percentage</th>
            </tr>
          </thead>
          <tbody>
            <?php
            echo '
            <tr>
              <th scope="row">1</th>
              <td>'.$popular[0].'</td>
              <td>'.$popular_count[0].'</td>
              <td>'.$success_count[0].'</td>
              <td>'.round($average[0]).'%</td>
            </tr>
            <tr>
              <th scope="row">2</th>
              <td>'.$popular[1].'</td>
              <td>'.$popular_count[1].'</td>
              <td>'.$success_count[1].'</td>
              <td>'.round($average[1]).'%</td>
            </tr>
            <tr>
              <th scope="row">3</th>
              <td>'.$arr[2].'</td>
              <td>'.$popular_count[2].'</td>
              <td>'.$success_count[2].'</td>
              <td>'.round($average[2]).'%</td>
            </tr>
            <tr>
              <th scope="row">4</th>
              <td>'.$popular[3].'</td>
              <td>'.$popular_count[3].'</td>
              <td>'.$success_count[3].'</td>
              <td>'.round($average[3]).'%</td>
            </tr>
            <tr>
              <th scope="row">5</th>
              <td>'.$popular[4].'</td>
              <td>'.$popular_count[4].'</td>
              <td>'.$success_count[4].'</td>
              <td>'.round($average[4]).'%</td>
            </tr>
            <tr>
              <th scope="row">6</th>
              <td>'.$popular[5].'</td>
              <td>'.$popular_count[5].'</td>
              <td>'.$success_count[5].'</td>
              <td>'.round($average[5]).'%</td>
            </tr>
            <tr>
              <th scope="row">7</th>
              <td>'.$popular[6].'</td>
              <td>'.$popular_count[6].'</td>
              <td>'.$success_count[6].'</td>
              <td>'.round($average[6]).'%</td>
            </tr>
            <tr>
              <th scope="row">8</th>
              <td>'.$popular[7].'</td>
              <td>'.$popular_count[7].'</td>
              <td>'.$success_count[7].'</td>
              <td>'.round($average[7]).'%</td>
            </tr>
            <tr>
              <th scope="row">9</th>
              <td>'.$popular[8].'</td>
              <td>'.$popular_count[8].'</td>
              <td>'.$success_count[8].'</td>
              <td>'.round(average[8]).'%</td>
            </tr>
            <tr>
              <th scope="row">10</th>
              <td>'.$popular[9].'</td>
              <td>'.$popular_count[9].'</td>
              <td>'.$success_count[9].'</td>
              <td>'.round($average[9]).'%</td>
            </tr>';
            ?>
          </tbody>      
        </table>
        <canvas id="doughnutChart"></canvas>
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
          <a href="#"><i class="fab fa-google-plus-g"></i></a>
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

</html>
