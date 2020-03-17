<?php
echo "called";
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
$depotid = mysqli_real_escape_string($con,$_POST['depot']);
$timeslots = mysqli_real_escape_string($con,$_POST['timeslots']);
$capacity = mysqli_real_escape_string($con,$_POST['capacity']);
$vehiclenumber= mysqli_real_escape_string($con,$_POST['vehiclenumber']);
$vtype= mysqli_real_escape_string($con,$_POST['vtype']);
$depotid=(int)$depotid;

session_start();
$uname=$_SESSION['uname'];


$str_arr = explode ("-", $timeslots);  
$str_start = explode (":", $str_arr[0]);
$sta = $str_start[0];
$stb = $str_start[1];
$str_start = explode (":", $str_arr[1]);
$eta = $str_start[0];
$etb = $str_start[1];



$sql = "INSERT INTO wedeliver.vehicles VALUES (NULL,'$country','$postal','$locality','$add','$lat','$long',$sta,$stb,$eta,$etb,$depotid,'$uname','$capacity',now(),'$vehiclenumber','$vtype','available')";
$sql_update ="UPDATE wedeliver.depot set totalVehicles=totalVehicles+1 where id=$depotid";



if(mysqli_query($con, $sql)){
$sql_query = "select max(id) as cnt from wedeliver.vehicles";
$result = mysqli_query($con,$sql_update);
$result = mysqli_query($con,$sql_query);
$row = mysqli_fetch_array($result);
$count = $row['cnt'];
    

    echo "<script>
	alert('Registeration succesfull.Vehicle ID is : $count');
	window.location.href='driverDashboard.php';
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

