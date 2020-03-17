<?php
include "dbconfig.php";

$depot = mysqli_real_escape_string($con,$_GET['depot']);


if ($depot != "" ){
$loop = mysqli_query($con,"select lat,lon from wedeliver.depot where id='$depot'");


$row = mysqli_fetch_array($loop);
$ret['responseCode'] = 1;
$ret['lat'] = $row[0];
$ret['long'] = $row[1];


echo json_encode($ret);
}
?>
