<?php
// Include config file

 
// Define variables and initialize with empty values
$username = $password = $confirm_password = "";
$username_err = $password_err = $confirm_password_err = "";
 echo "hello username is :";
echo $_POST["country"];
echo $_POST["postalCode"];
echo "use is :";
echo $_POST["depot"];
echo $_POST["demand"];
echo $_POST["add"];
echo $_POST["totalRequest"];
echo $_POST["totalCapacity"];
echo $_POST["depotID"];
echo $_POST["locality"];

// Processing form data when form is submitted
if($_SERVER["REQUEST_METHOD"] == "POST"){

	
   $myFile = "masterDepot.json";
   $file_name = $_POST["depotID"].".json";	
echo "file is ";
echo $file_name;
   $myfile1 = fopen($file_name, "w");

   $arr_data = array(); // create empty array

  try
  {
	   //Get form data
	   $formdata_locations = array(
	      'country'=> $_POST['country'],
	      'postalCode'=> $_POST['postalCode'],
	      'depot'=>$_POST['depot'],
	      'demand'=> $_POST['demand'],
	      'addressline'=> $_POST['add'],
	      
	      'locality'=> $_POST['locality']
	   );

	   //Get form data
	   $formdata = array(
	      'locations'=> $formdata_locations,
	      'total'=>$_POST['totalRequest'],
	     'totalvehicles'=>"0",
	      'capacity'=> $_POST['totalCapacity']
	      
	   );

$tes=array();
$tes[0]=$formdata_locations;
$myObj->total = $_POST['totalRequest'];
$myObj->totalvehicles = 0;
$myObj->capacity = $_POST['totalCapacity'];
$myObj->locations=$tes;

$myJSON = json_encode($myObj);



echo "File is not empty";
	   //Get data from existing json file
	   $jsondata = file_get_contents($myFile);

	   // converts json data into array
	   $arr_data = json_decode($jsondata, true);

 	 $value=$arr_data["total"]; 
	 $value=$value+1; 	
$arr_data["total"]=$value;
	   // Push user data to array
	  // array_push($arr_data,$formdata);
	   $jsondata = json_encode($arr_data, JSON_PRETTY_PRINT);
//write json data into data.json file
	   if(file_put_contents($myFile, $jsondata)) {
	        echo 'Data successfully saved';
	    }
	   else 
	        echo "error in storing data";




	  
	   // converts json data into array
	  // $arr_data1 =  array();

	   // Push user data to array
	 //  array_push($arr_data1,$formdata);
	  // $jsondata = json_encode($arr_data1, JSON_PRETTY_PRINT);
//write json data into data.json file
	   if(file_put_contents($file_name, $myJSON)) {
	        echo 'Data successfully saved';
	    }
	   else 
	        echo "error in storing data";
	    




echo "<script>
alert('Registeration succesfull');
window.location.href='adminlogin.php';
</script>";	   
   }
   catch (Exception $e) {
            echo 'Caught exception: ',  $e->getMessage(), "\n";
   }
}




?>
 

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


<script type='text/javascript'>
     

			var mydata;
		fetch("./masterDepot.json").
		then(function(resp){

		return resp.json()}).
		then(function(data){
		mydata = data;
console.log('3');
		console.log(data);

		var val=parseInt(data.total)+1;
	document.getElementById("depotID").value = "depot_"+val;
    });
	       		
		</script>
</head>
<body>

<form action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]); ?>" method="post">
  <div class="container">
    <h1>Register</h1>
    <p>Please fill in this form to create register your vehicle at Depot.</p>
    <hr>

    <label for="country"><b>Country</b></label>
    <input type="text" placeholder="Enter Country" name="country" required>

    <label for="postalCode"><b>PostalCode</b></label>
    <input type="text" placeholder="Enter PostalCode" name="postalCode" required>

    <label for="locality"><b>Locality</b></label>
    <input type="text" placeholder="Enter Locality" name="locality" required>


    <label for="depot"><b>Depot</b></label>
	<select name="depot"><b></b>
  <option value="true">true</option>
  <option value="false">false</option>


</select>

<br>
<br>
    <label for="demand"><b>Demand</b></label>
    <input type="text" placeholder="Enter Demand" name="demand" value="0" required>



    <label for="add"><b>AddressLine</b></label>
    <input type="text" placeholder="Enter Address Line" name="add" required>

    <label for="totalRequest"><b>Total Requests</b></label>
    <input type="text" placeholder="Enter Total Request" name="totalRequest" value="1" required>

    <label for="capacity"><b>Total Capacity</b></label>
    <input type="text" placeholder="Enter Total Capacity" name="totalCapacity" required>

    <label for="depotID"><b>Depot ID</b></label>
    <input type="text" placeholder="Enter depot ID" name="depotID" id="depotID" required>


    <hr>
    <p>By creating an account you agree to our <a href="#">Terms & Privacy</a>.</p>

    <button type="submit" class="registerbtn">Register</button>
  </div>
  
</form>

</body>
</html>


