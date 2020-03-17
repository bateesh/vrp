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
echo $_POST["add"];
echo $_POST["locality"];

// Processing form data when form is submitted
if($_SERVER["REQUEST_METHOD"] == "POST"){

	
   $myfile = "drivers.json";
   $file_name = $_POST["depot"].".json";	
echo "file is ";
echo $file_name;

   $my = fopen($myfile, "a");





   $arr_data = array(); // create empty array
   $arr_data1 = array();
  try
  {
	   //Get form data
	   $formdata = array(
	      'country'=> $_POST['country'],
	      'postalCode'=> $_POST['postalCode'],
	      'depot'=>$_POST['depot'],
	      'addressline'=> $_POST['add'],
	      
	      'locality'=> $_POST['locality']
	   );

	  

if(filesize($myfile)) {
           $jsondata = file_get_contents($myfile);

	   // converts json data into array
	   $arr_data = json_decode($jsondata, true);

	   // Push user data to array
	   array_push($arr_data,$formdata);
	   $jsondata = json_encode($arr_data, JSON_PRETTY_PRINT);
//write json data into data.json file
	   if(file_put_contents($myfile, $jsondata)) {
	        echo 'Data successfully saved';
	    }
	   else 
	        echo "error in storing data";

}
else
{
        //   $jsondata = file_get_contents($myFile);

	   // converts json data into array
	   $arr_data[0] = $formdata;

	   // Push user data to array
//	   array_push($arr_data,$formdata);
	   $jsondata = json_encode($arr_data, JSON_PRETTY_PRINT);
//write json data into data.json file
	   if(file_put_contents($myfile, $jsondata)) {
	        echo 'Data successfully saved';
	    }
	   else 
	        echo "error in storing data";

}

	   

echo "File is not empty";
	   //Get data from existing json file
	   $jsondata1 = file_get_contents($file_name);

	   // converts json data into array
	   $arr_data1 = json_decode($jsondata1, true);

 	 $value1=$arr_data1["totalvehicles"]; 
	 $value1=$value1+1; 	
$arr_data1["totalvehicles"]=$value1;
	   // Push user data to array
	  // array_push($arr_data,$formdata);
	   $jsondata1 = json_encode($arr_data1, JSON_PRETTY_PRINT);
//write json data into data.json file
	   if(file_put_contents($file_name, $jsondata1)) {
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

		var val=parseInt(data.total);
for (i = 1; i <=val; i++) {
	var xx = "depot_"+i;


var x = document.getElementById("depot");
  var option = document.createElement("option");
  option.text = xx;
  x.add(option);
  
}



    });
	       		
		</script>
</head>
<body>

<form action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]); ?>" method="post">
  <div class="container">
    <h1>Register Vehicle</h1>
    <p>Please fill in this form to register your vehicle at Depot.</p>
    <hr>

    <label for="country"><b>Country</b></label>
    <input type="text" placeholder="Enter Country" name="country" required>

    <label for="postalCode"><b>PostalCode</b></label>
    <input type="text" placeholder="Enter PostalCode" name="postalCode" required>

    <label for="locality"><b>Locality</b></label>
    <input type="text" placeholder="Enter Locality" name="locality" required>


    <label for="depot"><b>Select Depot to register a vehicle</b></label>
	<select name="depot" id="depot"><b></b>



</select>

<br>
<br>


    <label for="add"><b>AddressLine</b></label>
    <input type="text" placeholder="Enter Address Line" name="add" required>


    <hr>
    <p>By registering vehicle you agree to our <a href="#">Terms & Privacy</a>.</p>

    <button type="submit" class="registerbtn">Click to Register</button>
  </div>
  
</form>

</body>
</html>


