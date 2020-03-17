<!DOCTYPE html>
<html>
    <head>
        <title>WeDeliver</title>
<meta charset="utf-8" /> 
    <meta name="viewport"
          content="width=device-width, initial-scale=1.0" /> 
    <meta http-equiv="X-UA-Compatible" content="ie=edge" /> 
       <script type='text/javascript' src="https://ajax.googleapis.com/ajax/libs/jquery/3.1.1/jquery.min.js"></script>
        <script>
            $(document).ready(function(){
            $('#driversList').change(function(){
                //Selected value
                var inputValue = $(this).val();
                alert("value in js "+inputValue);
		loadMapScenario2(inputValue);

                //Ajax for calling php function
                $.post('submit.php', { dropdownValue: inputValue }, function(data){
                    alert('ajax completed. Response:  '+data);
                    //do after submission operation in DOM
                });
            });
        });
        </script>

        <meta http-equiv='Content-Type' content='text/html; charset=utf-8'/>
          <style> 

  #myMap { 
                float:left;  

                width:75%; 
                height:100px; 
            }  
            #myMap { 
                float:left;  

                width:75%; 
                height:600px; 
            } 
            #printoutPanel{ 
                float:left;  

                width:25%; 
                height:600px; 
		overflow-y: scroll;
            } 
             
            h1{ 
                color:green; 
                text-align:center; 
            } 
.hidden {
display:none;
}
.visible {
display:block;
position:absolute;
top:0;left:0;
}

.centered {
  text-align: center;
}

.loading-text {
  width: 90px;
  position: absolute;
  top: calc(50% - 15px);
  left: calc(50% - 45px);
  text-align: center;
}

.spinner.loading {
  
  padding: 50px;
  text-align: center;
}
.spinner.loading:before {
  content: "";
  height: 90px;
  width: 90px;
  margin: -15px auto auto -15px;
  position: absolute;
  top: calc(50% - 45px);
  left: calc(50% - 45px);
  border-width: 8px;
  border-style: solid;
  border-color: #2180c0 #ccc #ccc;
  border-radius: 100%;
  animation: rotation .7s infinite linear;
}

          
       @keyframes rotation {
  from {
    transform: rotate(0deg);
  }
  to {
    transform: rotate(359deg);
  }
}
          
        .center { 
            position: absolute; 
            top: 0; 
            bottom: 0; 
            left: 0; 
            right: 0; 
            margin: auto; 
        } 



        </style>  
    </head>
    <body>
<div id="disp" class="hidden">
<h2>
Display Driver Routes
</h2>
</div>


<select id="driversList" class="hidden">
</select>

<div class="centered">
    <div id="loader" class="spinner loading">
      <div class="loading-text">Loading ...</div>
    </div>

  </div>
<script> 
        document.onreadystatechange = function() { 
            if (document.readyState !== "complete") { 
                 document.querySelector( 
                  "body").style.visibility = "hidden"; 
                document.querySelector( 
                  "#loader").style.visibility = "visible"; 
               
            } else { 
var x = document.getElementById("driversList");
                document.querySelector( 
                  "#loader").style.display = "none"; 
                document.querySelector( 
                  "body").style.visibility = "visible"; 
x.style.display = "block"; 
x.style.visibility="visible";
var x = document.getElementById("disp");
x.style.display = "block"; 
x.style.visibility="visible";
console.log("now starting....");
var firstOption=$(driversList).find("option:first-child").val();
console.log("first option is "+firstOption);
		loadMapScenario2(firstOption);











var http = new XMLHttpRequest();
var url = 'getMaxTripId.php';
http.open('GET', url, false);
var id;

//Send the proper header information along with the request
http.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');

http.onreadystatechange = function() {//Call a function when the state changes.
    if(http.readyState == 4 && http.status == 200) {
      //  alert(http.responseText);
   var json = JSON.parse(http.responseText);

   var res=json.id;
  id=res;


    }
}
http.send();
console.log('new trip id is',id);


document.getElementById("disp").innerHTML = "<h2> Details for Drivers </h2>";

fetch("./result.json").
		then(function(resp){

		return resp.json()}).
		then(function(data){
		


console.log(" reading here received data is ");
console.log(data);
var dList=data.result.driverList+'';
var dl=dList.split(",");
console.log('len is '+dl.length);

for(i=0;i<dl.length;i++)
{
console.log('runnign '+i);
var curDriver=dl[i];
var cd=curDriver.split("_");
var currentDriver=cd[1];
console.log('running for driver'+currentDriver);
var ship=data.result[curDriver].shipmentList;


var http = new XMLHttpRequest();
var url = 'updateStatusOfAssignedShipmentsAndDrivers.php';
var params = 'driver='+currentDriver+"&shipmentList="+ship;
console.log("shipment list is"+ship);
http.open('POST', url, false);

//Send the proper header information along with the request
http.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');

http.onreadystatechange = function() {//Call a function when the state changes.
    if(http.readyState == 4 && http.status == 200) {
      console.log("success for "+params);
}
}

http.send(params);
}
});
           } 
        }; 
    </script> 
<div class="wrapper">

<div id="displayDetails">

</div>
        <div id='myMap'></div>
        
        <div id='printoutPanel'></div>
</div>

<?php
$style = "";
$style = "style='display:none;'";
echo $style;
echo "My first PHP script!";
echo "depot id is ".$_POST["did"];
echo "time ".$_POST["tms"];
$str_arr = explode (",", $_POST["name"]);  
print_r($str_arr); 
$total=count($str_arr);
echo "received demand is \n";

$str_demand = explode (",", $_POST["demand"]);  
print_r($str_demand); 
$totaldemand=count($str_demand);

$dimension=$total/2;
$capacity=$_POST["capacity"];

$myfile = fopen("input1.vrp", "w") or die("Unable to open file!");
$txt = "DIMENSION : ";
$did=$_POST["did"];
$tms=$_POST["tms"];
fwrite($myfile, $txt);
$str_arr = explode ("-", $tms);  
$str_start = explode (":", $str_arr[0]);
$sta = $str_start[0];
$stb = $str_start[1];
$str_start = explode (":", $str_arr[1]);
$eta = $str_start[0];
$etb = $str_start[1];

include "dbconfig.php";
echo "did ".$did;
echo "sta".$sta;
echo "stb".$stb;
echo "eta".$eta;
echo "etb".$etb;

$depotid=$_POST["did"];
$i=0;
$j=0;
$vehicleCapacity=array();
$lat=array();
$long=array();
$demand=array();
$vehicleID=array();
$shipmentID=array();
$query_vehicles="select id,capacity from wedeliver.vehicles where depotid=$did and status='available' and starthour>=$sta and startmin>=$stb and endhour<=$eta and endmin<=$etb";
$query_shipment="select id,lat,lon,demand from wedeliver.shipment where depotid=$did and status='created' and starthour>=$sta and startmin>=$stb and endhour<=$eta and endmin<=$etb";
$query_depotlatLong="select lat,lon from wedeliver.depot where id=$did";
echo $myquery;
$loop = mysqli_query($con,$query_vehicles);
while ($row = mysqli_fetch_array($loop))
{

$vehicleCapacity[$i]=$row[1];
$vehicleID[$i]=$row[0];
$i++;
}



$loop = mysqli_query($con,$query_shipment);
while ($row = mysqli_fetch_array($loop))
{

$lat[$j]=$row[1];
$long[$j]=$row[2];
$demand[$j]=$row[3];
$shipmentID[$j]=$row[0];

$j++;
}
$j++;

$loop = mysqli_query($con,$query_depotlatLong);
$row = mysqli_fetch_array($loop);
$depotlat=$row[0];
$depotlong=$row[1];
echo "rsults : ".$depotlat.$depotlong;



fwrite($myfile, $j);
fwrite($myfile, "\n");
$txt = "Capacity : 30\n";
fwrite($myfile, $txt);
$txt = "Vehicles : $i\n";
fwrite($myfile, $txt);
$txt = "Vehicle_Capacity_Section \n";
fwrite($myfile, $txt);
for ($k = 0; $k < $i; $k++) {
$t=($k+1);
$txt="$t $vehicleID[$k] $vehicleCapacity[$k]\n";
fwrite($myfile, $txt);
}
$txt = "NODE_COORD_SECTION \n";
fwrite($myfile, $txt);
$txt = "1 $depotlat $depotlong\n";
fwrite($myfile, $txt);
$t=2;
$j--;
for ($k = 0; $k < $j; $k++) {

$txt="$t $lat[$k] $long[$k]\n";
fwrite($myfile, $txt);
$t++;
}

$txt = "DEMAND_SECTION \n";
fwrite($myfile, $txt);
$txt = "1 0\n";
fwrite($myfile, $txt);
$t=2;
for ($k = 0; $k < $j; $k++) {

$txt="$t $demand[$k]\n";
fwrite($myfile, $txt);
$t++;
}

$txt = "SHIPMENT_ID_SECTION \n";
fwrite($myfile, $txt);
$txt = "1 $did\n";
fwrite($myfile, $txt);
$t=2;
for ($k = 0; $k < $j; $k++) {

$txt="$t $shipmentID[$k]\n";
fwrite($myfile, $txt);
$t++;
}


fclose($myfile);
echo exec('/home/nsnuser/Documents/Bateesh_MTP/vrp/CVRPClarkeAndWrightSavingsSolver input1.vrp');


?>


<script type='text/javascript'>
     function loadMapScenario2(input) {
document.getElementById("displayDetails").innerHTML = "Details for Driver "+input;

			var mydata;
console.log('2');
		fetch("./result.json").
		then(function(resp){

		return resp.json()}).
		then(function(data){
		mydata = data;
console.log('3');
		console.log(data);

		var val=data.result[input];
	console.log('input is is:'+input);
var totalList=data.result[input].total;
console.log(' yes tota ois '+val);



console.log('4');
		console.log(mydata);
	       		
		

console.log('5');
		console.log(mydata);

                var map = new Microsoft.Maps.Map(document.getElementById('myMap'), {
                    /* No need to set credentials if already passed in URL */
                    center: new Microsoft.Maps.Location(47.606209, -122.332071),
                    zoom: 12
                });
                Microsoft.Maps.loadModule('Microsoft.Maps.Directions', function () {
                    var directionsManager = new Microsoft.Maps.Directions.DirectionsManager(map);
                    // Set Route Mode to driving
                    directionsManager.setRequestOptions({ routeMode: Microsoft.Maps.Directions.RouteMode.driving });
		for(i=1;i<=totalList;i++)
{
                    var wp= new Microsoft.Maps.Directions.Waypoint({ address: ''+i, location: new Microsoft.Maps.Location(data.result[input][i][0], data.result[input][i][1]) });
                    directionsManager.addWaypoint(wp);

}

//                    var waypoint1 = new Microsoft.Maps.Directions.Waypoint({ address: 'Redmond', location: new Microsoft.Maps.Location(47.67683029174805, -122.1099624633789) });
  //                  var waypoint2 = new Microsoft.Maps.Directions.Waypoint({ address: 'Seattle', location: new Microsoft.Maps.Location(47.59977722167969, -122.33458709716797) });
//var waypoint3 = new Microsoft.Maps.Directions.Waypoint({ address: 'Seattle2', location: new Microsoft.Maps.Location(47.89977722167969, -123.33458709716797) });
  //                  directionsManager.addWaypoint(waypoint1);
    //                directionsManager.addWaypoint(waypoint2);
	//	 directionsManager.addWaypoint(waypoint3);
                    // Set the element in which the itinerary will be rendered
                    directionsManager.setRenderOptions({ itineraryContainer: document.getElementById('printoutPanel') });
                    directionsManager.calculateDirections();
		

                });
});
console.log('7');
                
            }

        </script>

        <script type='text/javascript'>

            function loadMapScenario() {

			var mydata;
console.log('2');
		fetch("./result.json").
		then(function(resp){

		return resp.json()}).
		then(function(data){
		mydata = data;
console.log('3');
		console.log(data);

		var total=data.result.totalDrivers;
console.log('tota ois '+total);
var driverid=data.result.driverList+'';
console.log("see"+driverid);

var drivers = driverid.split(',');


for (i = 1; i <= total; i++) {
//var str="Driver_"+i;
//var driverid=data.result.driver.driverList;
var title=drivers[i-1];
 var x = document.getElementById("driversList");
  var option = document.createElement("option");
  option.text = title;
  x.add(option);

}

console.log('4');
		console.log(mydata);
	       		
		});

console.log('5');
		console.log(mydata);

                var map = new Microsoft.Maps.Map(document.getElementById('myMap'), {
                    /* No need to set credentials if already passed in URL */
                    center: new Microsoft.Maps.Location(47.606209, -122.332071),
                    zoom: 12
                });
                Microsoft.Maps.loadModule('Microsoft.Maps.Directions', function () {
                    var directionsManager = new Microsoft.Maps.Directions.DirectionsManager(map);
                    // Set Route Mode to driving
                    directionsManager.setRequestOptions({ routeMode: Microsoft.Maps.Directions.RouteMode.driving });
                    var waypoint1 = new Microsoft.Maps.Directions.Waypoint({ address: 'Redmond', location: new Microsoft.Maps.Location(47.67683029174805, -122.1099624633789) });
                    var waypoint2 = new Microsoft.Maps.Directions.Waypoint({ address: 'Seattle', location: new Microsoft.Maps.Location(47.59977722167969, -122.33458709716797) });
var waypoint3 = new Microsoft.Maps.Directions.Waypoint({ address: 'Seattle2', location: new Microsoft.Maps.Location(47.89977722167969, -123.33458709716797) });
                    directionsManager.addWaypoint(waypoint1);
                    directionsManager.addWaypoint(waypoint2);
		 directionsManager.addWaypoint(waypoint3);
                    // Set the element in which the itinerary will be rendered
                    directionsManager.setRenderOptions({ itineraryContainer: document.getElementById('printoutPanel') });
                    directionsManager.calculateDirections();
		

                });
console.log('7');
                
            }
       
        </script>
        <script type='text/javascript' src='https://www.bing.com/api/maps/mapcontrol?key=AmO_vP4NG4zymCmPclwTKC48ItEhs9Rxh1txZW_dzzCT7ttVaXQayptHOfe7n09A&callback=loadMapScenario' async defer></script>
    </body>
</html>
