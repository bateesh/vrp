<!DOCTYPE html>
<html>
<head>
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
.logoutLblPos{

   position:fixed;
   right:10px;
   top:5px;
}
.button {
  background-color: #4CAF50;
  border: none;
  color: white;
  padding: 10px 25px;
  text-align: center;
  text-decoration: none;
  display: inline-block;
  font-size: 12px;
  margin: 4px 2px;
  cursor: pointer;
}
</style>


<script type='text/javascript'>


function populatetimeslots() {
console.log("called");
var x = document.getElementById("timeslots");
var sta=parseInt(document.getElementById("sta").value);
var stb=parseInt(document.getElementById("stb").value);
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
	var xx = sta+":"+stb+"-"+(sta+itr)+":"+stb;

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
			var latElement = document.getElementById("lat");
			var longElement = document.getElementById("long");
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

	       		
		</script>
</head>
<body>
<form align="right" name="form1" method="post" action="log_out.php">

  
  <input class="button" name="submit2" type="submit"  value="log out">
  

  </label>
</form>


<form action="./storeDepotDetails.php" method="post" onsubmit="return populateLatLong()">
  <div class="container">
         <h2> <?php

			session_start();	
                        echo "Welcome Admin!!!!! : ".$_SESSION['uname'];  
  
                    ?> </h2>

    <h1>Register</h1>
    <p>Please fill in this form to create Depot.</p>
    <hr>

    <label for="country"><b>Country</b></label>
    <input type="text" placeholder="Enter Country" name="country" id="country" required>

    <label for="postalCode"><b>PostalCode</b></label>
    <input type="text" placeholder="Enter PostalCode" name="postalCode" id="postalCode" required>

    <label for="locality"><b>Locality</b></label>
    <input type="text" placeholder="Enter Locality" name="locality" id="locality" required>


    


    <label for="add"><b>AddressLine</b></label>
    <input type="text" placeholder="Enter Address Line" name="add" id="add" required>

  
 <b>Please Enter Operating hours for Depot</b>
<br>
<br>
	
  <b>Start Time</b>
  <input type="number" min="0" max="23" name="sta" id="sta" placeholder="23">:
  <input type="number" min="0" max="59" name="stb" id="stb" placeholder="00">
  <label for="timelabel"><b>


   
  <b>End Time</b>
  <input type="number" min="0" max="23" name="eta" id="eta" placeholder="23">
  <input type="number" min="0" max="59" name="etb" id="etb" placeholder="00">
  <label for="timelabel"><b>


   
<br>
<br>

  <b>Please select number of time windows</b>
  <input type="number" min="1" max="24" name="twc" id="twc" placeholder="00"  onchange="populatetimeslots()">

<br>
<br>
<b>Time slots for Depot</b>
   <select name="timeslots" id="timeslots"><b></b>
</select>


    <hr>
    <p>By creating an account you agree to our <a href="#">Terms & Privacy</a>.</p>

    <button type="submit" class="registerbtn">Register</button>
    <input type="text" name="lat" id="lat">

    <input type="text" name="long" id="long">


  </div>
  
</form>

</body>
</html>
<?php
			session_start();	
			$abc=$_SESSION['uname'];
                        echo "<script>(alert($abc))</script>";  
?>

