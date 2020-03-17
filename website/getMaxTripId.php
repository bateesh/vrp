<?php
include "dbconfig.php";


$loop = mysqli_query($con,"SELECT COALESCE(MAX(id), 0) FROM  from wedeliver.trips");
$row = mysqli_fetch_array($loop)
$ret['id'] = $row[0];
echo json_encode($ret);

?>
