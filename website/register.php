<script type='text/javascript'>



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
</style>
</head>
<body>

<form action="./storeUsers.php" method="post" onsubmit="return populateLatLong()">
  <div class="container">
    <h1>Register</h1>
    <p>Please fill in this form to create an account.</p>
    <hr>

    <label for="name"><b>Username</b></label>
    <input type="text" placeholder="Enter Username" name="name" required>

    <label for="phone"><b>Contact</b></label>
    <input type="text" placeholder="Enter Contact" name="phone" required>

    <label for="users"><b>Role</b></label>
	<select name="users"><b></b>
  <option value="Admin">Admin</option>
  <option value="Customer">Customer</option>
  <option value="Driver">Driver</option>
</select>
<br>
<br>

    <label for="country"><b>Country</b></label>
    <input type="text" placeholder="Enter Country" name="country" id="country" required>

    <label for="postalCode"><b>PostalCode</b></label>
    <input type="text" placeholder="Enter PostalCode" name="postalCode" id="postalCode" required>

    <label for="locality"><b>Locality</b></label>
    <input type="text" placeholder="Enter Locality" name="locality" id="locality" required>



    <label for="add"><b>AddressLine</b></label>
    <input type="text" placeholder="Enter Address Line" name="add" id="add" required>



</select>

<br>
<br>
    <label for="email"><b>Email</b></label>
    <input type="text" placeholder="Enter Email" name="email" required>



    <label for="psw"><b>Password</b></label>
    <input type="password" placeholder="Enter Password" name="psw" required>

    <label for="psw-repeat"><b>Repeat Password</b></label>
    <input type="password" placeholder="Repeat Password" name="psw-repeat" required>
    <hr>
    <p>By creating an account you agree to our <a href="#">Terms & Privacy</a>.</p>

    <button type="submit" class="registerbtn">Register</button>
    <input type="text" name="lat" id="lat">

    <input type="text" name="long" id="long">

  </div>
  
</form>

</body>
</html>


