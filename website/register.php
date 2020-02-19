<?php
// Include config file

 
// Define variables and initialize with empty values
$username = $password = $confirm_password = "";
$username_err = $password_err = $confirm_password_err = "";
 echo "hello username is :";
echo $_POST["name"];
echo $_POST["phone"];
echo "use is :";
echo $_POST["users"];
echo $_POST["email"];
echo $_POST["psw"];
// Processing form data when form is submitted
if($_SERVER["REQUEST_METHOD"] == "POST"){


$myFile = "users.json";
   $arr_data = array(); // create empty array

  try
  {
	   //Get form data
	   $formdata = array(
	      'name'=> $_POST['name'],
	      'contact'=> $_POST['phone'],
	      'email'=>$_POST['email'],
	      'pwd'=> $_POST['psw'],
	      'role'=> $_POST['users']
	   );



if(filesize($myFile)) {
echo "File is empty";
	   //Get data from existing json file
	   $jsondata = file_get_contents($myFile);

	   // converts json data into array
	   $arr_data = json_decode($jsondata, true);

	   // Push user data to array
	   array_push($arr_data,$formdata);
	   $jsondata = json_encode($arr_data, JSON_PRETTY_PRINT);
//write json data into data.json file
	   if(file_put_contents($myFile, $jsondata)) {
	        echo 'Data successfully saved';
	    }
	   else 
	        echo "error in storing data";



}
else
{

echo "File is not empty";

	   // Push user data to array
	   array_push($arr_data,$formdata);
	   $jsondata = json_encode($arr_data, JSON_PRETTY_PRINT);
//write json data into data.json file
	   if(file_put_contents($myFile, $jsondata)) {
	        echo 'Data successfully saved';
	    }
	   else 
	        echo "error in storing data";
	  
	   


}
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
</head>
<body>

<form action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]); ?>" method="post">
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
    <label for="email"><b>Email</b></label>
    <input type="text" placeholder="Enter Email" name="email" required>



    <label for="psw"><b>Password</b></label>
    <input type="password" placeholder="Enter Password" name="psw" required>

    <label for="psw-repeat"><b>Repeat Password</b></label>
    <input type="password" placeholder="Repeat Password" name="psw-repeat" required>
    <hr>
    <p>By creating an account you agree to our <a href="#">Terms & Privacy</a>.</p>

    <button type="submit" class="registerbtn">Register</button>
  </div>
  
</form>

</body>
</html>


