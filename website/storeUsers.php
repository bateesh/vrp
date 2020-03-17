<?php
// Processing form data when form is submitted
if($_SERVER["REQUEST_METHOD"] == "POST"){



  try
  {
include "dbconfig.php";
$username = mysqli_real_escape_string($con,$_POST['name']);
$contact = mysqli_real_escape_string($con,$_POST['phone']);
$password = mysqli_real_escape_string($con,$_POST['psw']);
$email = mysqli_real_escape_string($con,$_POST['email']);
$role = mysqli_real_escape_string($con,$_POST['users']);
$country = mysqli_real_escape_string($con,$_POST['country']);
$postal = mysqli_real_escape_string($con,$_POST['postalCode']);
$add = mysqli_real_escape_string($con,$_POST['add']);
$locality = mysqli_real_escape_string($con,$_POST['locality']);
$lat = mysqli_real_escape_string($con,$_POST['lat']);
$long = mysqli_real_escape_string($con,$_POST['long']);


$sql = "INSERT INTO wedeliver.users VALUES ('$username','$contact','$email','$password','$role','$country','$postal','$locality','$add','$lat','$long')";
//$result = mysqli_query($con,$sql_query);
if(mysqli_query($con, $sql)){
    echo "<script>
	alert('Registeration succesfull');
	window.location.href='adminlogin.php';
	</script>";

} 
else{
    echo "ERROR: Could not able to execute $sql. " . mysqli_error($con);
}

echo "<script>
alert('Registeration succesfull');
window.location.href='adminlogin.php';
</script>";

	   
   }
   catch (Exception $e) {
            echo 'Caught exception: ',  $e->getMessage(), "\n";
   }
}



?>
 

