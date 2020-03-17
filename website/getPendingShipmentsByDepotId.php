<?php
include "dbconfig.php";

$depot = mysqli_real_escape_string($con,$_GET['depot']);
$sta = mysqli_real_escape_string($con,$_GET['sta']);
$stb = mysqli_real_escape_string($con,$_GET['stb']);
$eta = mysqli_real_escape_string($con,$_GET['eta']);
$etb = mysqli_real_escape_string($con,$_GET['etb']);


if ($depot != "" ){
$sql="select address,postal,locality,country,demand,lat,lon from wedeliver.shipment where depotid=$depot and starthour>=$sta and startmin>=$stb and endhour<=$eta and endmin<=$etb and status='created'";

$loop = mysqli_query($con,$sql);

while ($row = mysqli_fetch_array($loop))
{


if(strlen($lat)==0)
{
$lat=$row[5];
$long=$row[6];
$str0=$row[0];
$str1=$row[1];
$str2=$row[2];
$str3=$row[3];
$str4=$row[4];

}
else
{
$lat=$lat.",".$row[5];
$long=$long.",".$row[6];
$str0=$str0.",".$row[0];
$str1=$str1.",".$row[1];
$str2=$str2.",".$row[2];
$str3=$str3.",".$row[3];
$str4=$str4.",".$row[4];




}

}


$ret['responseCode'] = 1;
$ret['lat'] = $lat;
$ret['long'] = $long;
$ret['address'] = $str0;
$ret['postal'] = $str1;
$ret['locality'] = $str2;
$ret['country'] = $str3;
$ret['demand'] = $str4;


echo json_encode($ret);
}
?>
