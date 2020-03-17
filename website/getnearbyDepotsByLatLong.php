<?php
include "dbconfig.php";

$postal = mysqli_real_escape_string($con,$_GET['postal']);


if ($postal != "" ){
$loop = mysqli_query($con,"select id,lat,lon from wedeliver.depot where postal='$postal'");

$lat="";
$long="";
$depotid="";


while ($row = mysqli_fetch_array($loop))
{


if(strlen($lat)==0)
{
$lat=$row[1];
$long=$row[2];
$id=$row[0];
}
else
{
$lat=$lat.",".$row[1];
$long=$long.",".$row[2];
$id=$id.",".$row[0];

}

}


$ret['responseCode'] = 1;
$ret['lat'] = $lat;
$ret['long'] = $long;
$ret['id'] = $id;

echo json_encode($ret);
}
?>
