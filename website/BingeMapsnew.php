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
		loadMapScenario2("Driver_1");
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
echo $_POST["capacity"];
echo $_POST["name"];
$str_arr = explode (",", $_POST["name"]);  
print_r($str_arr); 
$total=count($str_arr);
for ($x = 0; $x < $total; $x++) {
    echo "The number is: $str_arr[$x] <br>";

}
echo "received demand is \n";

$str_demand = explode (",", $_POST["demand"]);  
print_r($str_demand); 
$totaldemand=count($str_demand);
for ($x = 0; $x < $totaldemand; $x++) {
    echo "The number is: $str_demand[$x] <br>";

}

$dimension=$total/2;
$capacity=$_POST["capacity"];

$myfile = fopen("input.vrp", "w") or die("Unable to open file!");
$txt = "DIMENSION : $dimension\n";

fwrite($myfile, $txt);
$txt = "Capacity : $capacity\n";
fwrite($myfile, $txt);
$txt = "NODE_COORD_SECTION\n";
fwrite($myfile, $txt);
$c=1;
for ($x = 0; $x < $total; $x=$x+2) {
$y=$x+1;
$txt = "$c $str_arr[$x] $str_arr[$y]\n";
fwrite($myfile, $txt);
$c=$c+1;
}


$txt = "DEMAND_SECTION\n";
fwrite($myfile, $txt);
$c=1;
for ($x = 0; $x < $totaldemand; $x=$x+1) {
$txt = "$c $str_demand[$x]\n";
fwrite($myfile, $txt);
$c=$c+1;
}

fclose($myfile);
echo exec('/home/nsnuser/Documents/Bateesh_MTP/vrp/CVRPClarkeAndWrightSavingsSolver input.vrp');


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
                    var wp= new Microsoft.Maps.Directions.Waypoint({ address: 'Redmond', location: new Microsoft.Maps.Location(data.result[input][i][0], data.result[input][i][1]) });
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
document.getElementById("loading").className="visible";var hide=function(){document.getElementById("loading").className="hidden"};var oldLoad=window.onload;var newLoad=oldLoad?function(){hide.call(this);oldLoad.call(this)}:hide;window.onload=newLoad; 

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
for (i = 1; i <= total; i++) {

var title="Driver_"+i;
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
