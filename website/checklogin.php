<?php
include "dbconfig.php";

$uname = mysqli_real_escape_string($con,$_POST['username']);
$password = mysqli_real_escape_string($con,$_POST['password']);
$role = mysqli_real_escape_string($con,$_POST['role']);

//$uname = strtolower($uname);
//$password =  strtolower($password);
$role1 = strtolower($role);

if ($uname != "" && $password != "" && $role != ""){

    $sql_query = "select count(*) as cntUser from wedeliver.users where username='".$uname."' and BINARY password='".$password."' and role='".$role."'";
    $result = mysqli_query($con,$sql_query);
    $row = mysqli_fetch_array($result);

    $count = $row['cntUser'];
    $red = "";	

    if($count > 0){
        $_SESSION['uname'] = $uname;
 	if($role1 == 'admin')
	{
	$red="adminDashboard.php";
	}
	elseif($role1 == 'customer')
{
$red='customerDashboard.php';
}
        
	else 
	{
	$red="driverDashboard.php";
	}

        $ret['responseCode'] = 1;
        $ret['redirecturl'] = $red;

    }
   else{
   $ret['responseCode'] = 0;
   $ret['error'] = 'Invalid Credentials!Please try again.';
//        echo 0;
    }
echo json_encode($ret);


}
?>
