<?php
include "dbconfig.php";

$driver = mysqli_real_escape_string($con,$_POST['driver']);
$shipmentList = mysqli_real_escape_string($con,$_POST['shipmentList']);

if ($driver != "" && $shipmentList != "" ){


$sql_query = "update wedeliver.vehicles set status='assigned' where id=$driver";

$loop = mysqli_query($con,$sql_query);

$sql_query = "update wedeliver.shipment set status='assigned' where id in ($shipmentList)";
$loop = mysqli_query($con,$sql_query);

}
?>
