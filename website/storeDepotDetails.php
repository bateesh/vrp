<?php

if($_SERVER["REQUEST_METHOD"] == "POST"){

  try
  {

include "dbconfig.php";
$country = mysqli_real_escape_string($con,$_POST['country']);
$postal = mysqli_real_escape_string($con,$_POST['postalCode']);
$add = mysqli_real_escape_string($con,$_POST['add']);
$locality = mysqli_real_escape_string($con,$_POST['locality']);
$lat = mysqli_real_escape_string($con,$_POST['lat']);
$long = mysqli_real_escape_string($con,$_POST['long']);
$sta = mysqli_real_escape_string($con,$_POST['sta']);
$stb = mysqli_real_escape_string($con,$_POST['stb']);
$eta = mysqli_real_escape_string($con,$_POST['eta']);
$etb = mysqli_real_escape_string($con,$_POST['etb']);
$twc = mysqli_real_escape_string($con,$_POST['twc']);
$sta=(int)$sta;
$stb=(int)$stb;
$eta=(int)$eta;
$etb=(int)$etb;
$twc=(int)$twc;

session_start();
$uname=$_SESSION['uname'];



$sql = "INSERT INTO wedeliver.depot VALUES (NULL,'$country','$postal','$locality','$add','$lat','$long',$sta,$stb,$eta,$etb,$twc,0,'$uname',now())";


if(mysqli_query($con, $sql)){
$sql_query = "select max(id) as cnt from wedeliver.depot";
$result = mysqli_query($con,$sql_query);
$row = mysqli_fetch_array($result);
$count = $row['cnt'];
    

    echo "<script>
	alert('Registeration succesfull.Depot ID is : $count');
	window.location.href='adminDashboard.php';
	</script>";
} 
else{
    echo "ERROR: Could not able to execute $sql. " . mysqli_error($con);
}

   }
   catch (Exception $e) {
            echo 'Caught exception: ',  $e->getMessage(), "\n";
   }
}
?>

