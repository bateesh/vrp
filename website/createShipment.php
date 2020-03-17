
<?php

                        session_start();
?>

<!DOCTYPE html>
<html>
<head>
<script src="https://ajax.googleapis.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
<meta name="viewport" content="width=device-width, initial-scale=1">
<style>
body {
  font-family: Arial, Helvetica, sans-serif;
  background-color: black;
}

* {
  box-sizing: border-box;
}

/* Add padding to containers */
.container {
  padding: 16px;
  background-color: white;
}
#spinner{
  visibility: hidden;
  width: 80px;
  height: 80px;

  border: 2px solid #f3f3f3;
  border-top:3px solid #f25a41;
  border-radius: 100%;

  position: absolute;
  top:0;
  bottom:0;
  left:0;
  right: 0;
  margin: auto;

  animation: spin 1s infinite linear;
}

@keyframes spin {
  from {
      transform: rotate(0deg);
  } to {
      transform: rotate(360deg);
  }
}

#spinner.show {
  visibility: visible;
}
/* Full-width input fields */
input[type=text], input[type=password],input[type=select] {
  width: 100%;
  padding: 15px;
  margin: 5px 0 22px 0;
  display: inline-block;
  border: none;
  background: #f1f1f1;
}

input[type=text]:focus, input[type=password]:focus {
  background-color: #ddd;
  outline: none;
}

/* Overwrite default styles of hr */
hr {
  border: 1px solid #f1f1f1;
  margin-bottom: 25px;
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
      
/* Set a style for the submit button */
.registerbtn {
  background-color: #4CAF50;
  color: white;
  padding: 16px 20px;
  margin: 8px 0;
  border: none;
  cursor: pointer;
  width: 100%;
  opacity: 0.9;
}
.button {
  background-color: #4CAF50;
  border: none;
  color: white;
  padding: 15px 32px;
  text-align: center;
  text-decoration: none;
  display: inline-block;
  font-size: 16px;
  margin: 4px 2px;
  cursor: pointer;
}
.registerbtn:hover {
  opacity: 1;
}

/* Add a blue text color to links */
a {
  color: dodgerblue;
}

/* Set a grey background color and center the text of the "sign in" section */
.signin {
  background-color: #f1f1f1;
  text-align: center;
}
</style>







<script type='text/javascript'>


function getCurrentDistance(lata,longa,latb,longb)
{
console.log("received input is :"+lata+","+longa);
console.log("received input is :"+latb+","+longb);
var url="https://dev.virtualearth.net/REST/v1/Routes/DistanceMatrix?origins="+latb+","+longb+"&destinations="+lata+","+longa+"&travelMode=driving&key=AmO_vP4NG4zymCmPclwTKC48ItEhs9Rxh1txZW_dzzCT7ttVaXQayptHOfe7n09A";


//var url="http://dev.virtualearth.net/REST/v1/Locations/"+country+"/"+postalCode+"/"+locality+"/"+add+"?key=AmO_vP4NG4zymCmPclwTKC48ItEhs9Rxh1txZW_dzzCT7ttVaXQayptHOfe7n09A";
console.log("Sending on URL "+url);

		var resfinal;
var xhr = new XMLHttpRequest();
			xhr.open("GET", url, false);
			xhr.setRequestHeader("Content-Type", "application/json");
			xhr.onreadystatechange = function () {
			if (xhr.readyState === 4 && xhr.status === 200) {
		        var json = JSON.parse(xhr.responseText);
			console.log('Received response for record numner');
		        console.log(json);
			console.log("now populate lat long");

			var res=json.resourceSets[0].resources[0].results[0].travelDistance;
			console.log('return here'+res);
			resfinal=res;
			}
			if (xhr.readyState === 4 && xhr.status === 400) {
		        
			alert("Unable to connect to Bing maps for lat,long.Please try after sometime");
	resfinal= 99999;
		        
			}
			};
			xhr.send();

return resfinal;
		


}

function startLoader()
{
console.log('try to start');
document.getElementById("loader").style.display = "block";


console.log('Scuess');
}




function getDepotId()
{
console.log('stare');
//startLoader();	
$('#loader').show();

populateLatLong();
var latElement = document.getElementById("lat");
var longElement = document.getElementById("long");
var lata=latElement.value;
var longa=longElement.value;

var x=document.getElementById('postalCode').value;
var http = new XMLHttpRequest();
var url = 'getnearbyDepotsByLatLong.php?postal='+x;

http.open('GET', url, false);

//Send the proper header information along with the request
http.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');

http.onreadystatechange = function() {//Call a function when the state changes.
    if(http.readyState == 4 && http.status == 200) {

  console.log(' see result : '+http.responseText);
   var json = JSON.parse(http.responseText);

   var lat=json.lat;
   var long=json.long;
   var depotid=json.id;	
  console.log(' lat : '+lat);
  console.log(' long : '+long);
  console.log(' id : '+depotid);


var depotarray = depotid.split(',');
var latarray = lat.split(',');
var longarray = long.split(',');
var bestdistance=99999;
var curdistance=-1;
var bestdepot=-1;



                
for(i=1;i<=depotarray.length;i++)
{
curdistance=getCurrentDistance(lata,longa,latarray[i-1],longarray[i-1]);
console.log('return is :'+curdistance);
if(curdistance<bestdistance && curdistance>0){

bestdistance=curdistance;
bestdepot=depotarray[i-1];
console.log("Updating best depot to : "+depot);
}

}
console.log("final dis"+bestdistance);
console.log("final bestdepot"+bestdepot);
document.getElementById("depot").value = bestdepot;


    }
}
http.send();



$('#loader').hide();
console.log('done');

populateTimeWindows();

}

function populatetimeslots() {
console.log("called");
var x = document.getElementById("timeslots");
var sta=parseInt(document.getElementById("sta").value);
var eta=parseInt(document.getElementById("eta").value);
var twc=parseInt(document.getElementById("twc").value);
var itr=(eta-sta)/twc;
console.log("data 1 is :"+sta);
console.log("data 2 is :"+eta);
console.log("data 3 is :"+twc);
console.log("data 4 is :"+itr);


 var i, L = x.options.length - 1;
   for(i = L; i >= 0; i--) {
      x.remove(i);
   }



for (i = 1; i <=twc; i++) {
	var xx = sta+":"+(sta+itr);

  var option = document.createElement("option");
  option.text = xx;
  sta=sta+itr;
  x.add(option);
  
}
}


function  populateLatLong(){


console.log("working on it.....");
var country = document.getElementById("country").value;
var add = document.getElementById("add").value;
var locality = document.getElementById("locality").value;
var postalCode = document.getElementById("postalCode").value;
console.log(" Senging Geolocation request to Bing Maps ");
var url="http://dev.virtualearth.net/REST/v1/Locations/"+country+"/"+postalCode+"/"+locality+"/"+add+"?key=AmO_vP4NG4zymCmPclwTKC48ItEhs9Rxh1txZW_dzzCT7ttVaXQayptHOfe7n09A";
console.log("Sending on URL "+url);

	 var latElement = document.getElementById("lat");
		var longElement = document.getElementById("long");

if (latElement.value.length != 0 && longElement.value.length !=0)
      { 

         return true; 
      }  	
		
var xhr = new XMLHttpRequest();
//			var url = "url?data=" + encodeURIComponent(JSON.stringify({"email": "hey@mail.com", "password": "101010"}));
			xhr.open("GET", url, false);
			xhr.setRequestHeader("Content-Type", "application/json");
			xhr.onreadystatechange = function () {
			if (xhr.readyState === 4 && xhr.status === 200) {
		        var json = JSON.parse(xhr.responseText);
			console.log('Received response for record numner');
		        console.log(json);
			console.log("now populate lat long");
			 latElement = document.getElementById("lat");
		 longElement = document.getElementById("long");
			var lat=json.resourceSets[0].resources[0].geocodePoints[0].coordinates[0];
			var long=json.resourceSets[0].resources[0].geocodePoints[0].coordinates[1];
			latElement.value=lat;
			longElement.value=long;
			
			return  true;						
			}
			if (xhr.readyState === 4 && xhr.status === 400) {
		        
			alert("Unable to connect to Bing maps for lat,long.Please try after sometime");
			return false;
		        
			}
			};
			xhr.send();


		

}


function populateTimeWindows()
{
var select = document.getElementById("timeslots");
var length = select.options.length;
for (i = length-1; i >= 0; i--) {
  select.options[i] = null;
}


var x=document.getElementById('depot').value;
var http = new XMLHttpRequest();
var url = 'getTimeSlotsforDepot.php?depotid='+x;
var params = 'orem=ipsum&name=binny';
http.open('GET', url, false);

//Send the proper header information along with the request
http.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');

http.onreadystatechange = function() {//Call a function when the state changes.
    if(http.readyState == 4 && http.status == 200) {
      //  alert(http.responseText);
   var json = JSON.parse(http.responseText);

   var tot=json.totalwindows;
   var ret=json.result;
    var depottime = ret.split(',');

for (i = 1; i <=tot; i++) {
	var xx = depottime[i-1];


var x = document.getElementById("timeslots");
  var option = document.createElement("option");
  option.text = xx;
  x.add(option);
  
}

    }
}
http.send(params);
 



}
	       		
		</script>
</head>
<body>
<div class="centered">
    <div id="loader" class="spinner loading" style='display: none;'	 >
      <div class="loading-text">Auto-assigning ...</div>
    </div>

  </div>



<form align="right" name="form1" method="post" action="log_out.php">

  
  <input class="button" name="submit2" type="submit"  value="Log out">
  

  </label>
</form>


<form action="./storeShipmentDetails.php" method="post" onsubmit="return populateLatLong()">
  <div class="container">
     <h3> 
                    <?php session_start();echo "Welecome User : ".$_SESSION['uname'];  
  
                    ?> 
                </h3> 
	
    <h1>Shipment Registeration</h1>
    <p>Please fill in this form to register shipment request</p>
    <hr>

    <label for="country"><b>Country</b></label>
    <input type="text" placeholder="Enter Country" name="country" id="country" required>

    <label for="postalCode"><b>PostalCode</b></label>
    <input type="text" placeholder="Enter PostalCode" name="postalCode" id="postalCode" required>

    <label for="locality"><b>Locality</b></label>
    <input type="text" placeholder="Enter Locality" name="locality" id="locality" required>



    <label for="add"><b>AddressLine</b></label>
    <input type="text" placeholder="Enter Address Line" name="add" id="add" required>

    <label for="capacity"><b>Demand</b></label>
    <input type="text" placeholder="Capacity" name="capacity" id="capacity" required>


        <label for="depot"><b>Select Depot to register a vehicle</b></label>

	<select name="depot" id="depot" onchange="populateTimeWindows()"><b></b>
<?php
include "dbconfig.php";



$loop = mysqli_query($con,"select id from wedeliver.depot")
   or die (mysqli_error());

while ($row = mysqli_fetch_array($loop))
{
echo '<option   value="'.$row[0].'">'.$row[0].'</option>';

}
echo "</select>";
?>

 <button type="button"  onclick="getDepotId()">Click to auto assign shipment </button>
<br>
<br>

  
 <b>Please Enter Operating hours for Depot</b>

<select name="timeslots" id="timeslots"><b></b>
</select>

<br>
<br>
	
   
    <hr>
    <p>By creating an account you agree to our <a href="#">Terms & Privacy</a>.</p>

    <button type="submit" class="registerbtn">Register</button>
    <input type="text" name="lat" id="lat">

    <input type="text" name="long" id="long">


  </div>
  
</form>

</body>
</html>


