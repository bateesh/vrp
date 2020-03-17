<?php
include "dbconfig.php";

$depotid = mysqli_real_escape_string($con,$_GET['depotid']);

if ($depotid != "" ){

$loop = mysqli_query($con,"select starthour,startmin,endhour,endmin,totalwindows from wedeliver.depot where id=$depotid");
$row = mysqli_fetch_array($loop);
$red = "";	
$a=1;
$b=$row[4];
//echo "<script>alert($b)</script>";
$s=$row[0];
$itr=$row[2]-$row[0];
$itr=$itr/$b;
//echo "<script>alert($s)</script>";
while ($a <= $b)
{
if($a>1)
{
$red=$red.",";
}
$red=$red.$s.":".$row[1]."-".($s+$itr).":".$row[1];
$s=$s+$itr;
$a=($a+1);
}

$ret['responseCode'] = 1;
$ret['result'] = $red;
$ret['totalwindows'] = $b;
echo json_encode($ret);
}
?>
