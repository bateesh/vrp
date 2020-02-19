<?php
$myObj->name = "John";
$myObj->age = 30;
$myObj->city = "New York";
//$myArr = array("John", "Mary", "Peter", "Sally");
//$myObj->arr = array("John", "Mary", "Peter", "Sally");

$formdata_locations = array(
	      'country'=> "test",
	      'postalCode'=> "test"
	   );

$myJSON = json_encode($formdata_locations);
$tes=array();
$tes[0]=$formdata_locations;

echo $myJSON;
echo "\n";

$myObj->locations = $tes;
$myJSON = json_encode($myObj);

echo $myJSON;
?>
