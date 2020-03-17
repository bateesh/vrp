<?php

session_start();

?>

<!DOCTYPE html>
<html>
<head>


<meta name="viewport" content="width=device-width, initial-scale=1">

<style>

body {font-family: Arial, Helvetica, sans-serif;}

/* Full-width input fields */
input[type=text], input[type=password] {
  width: 100%;
  padding: 12px 20px;
  margin: 8px 0;
  display: inline-block;
  border: 1px solid #ccc;
  box-sizing: border-box;
}

/* Set a style for all buttons */
button {
  background-color: #4CAF50;
  color: white;
  padding: 14px 20px;
  margin: 8px 0;
  border: none;
  cursor: pointer;
  width: 100%;
}
.button1 {
  background-color: #4CAF50;
  border: none;
  color: white;
  padding: 10px 25px;
  text-align: center;
  text-decoration: none;
  display: inline-block;
  font-size: 13px;
  margin: 2px 3px;
  cursor: pointer;
}

            #userlist{ 


height:100%;
		overflow-y: scroll;
 overflow: auto;
  white-space: nowrap;
            } 

div:empty {
   display: none;
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

.big {
  font-size: 1.2em;
}

.small {
  font-size: .7em;
}

.square {
  width: .7em;
  height: .7em;
  margin: .5em;
  display: inline-block;
}

/* Custom dropdown */
.custom-dropdown {
  position: relative;
  display: inline-block;
  vertical-align: middle;
  margin: 10px; /* demo only */
}

.custom-dropdown select {
  background-color: #1abc9c;
  color: #fff;
  font-size: inherit;
  padding: .5em;
  padding-right: 2.5em;	
  border: 0;
  margin: 0;
  border-radius: 3px;
  text-indent: 0.01px;
  text-overflow: '';
  /*Hiding the select arrow for firefox*/
  -moz-appearance: none;
  /*Hiding the select arrow for chrome*/
  -webkit-appearance:none;
  /*Hiding the select arrow default implementation*/
  appearance: none;
}

button:hover {
  opacity: 0.8;
}

/* Extra styles for the cancel button */
.cancelbtn {
  width: auto;
  padding: 10px 18px;
  background-color: #f44336;
}

/* Center the image and position the close button */
.imgcontainer {
  text-align: center;
  margin: 24px 0 12px 0;
  position: relative;
}

img.avatar {
  width: 40%;
  border-radius: 50%;
}

.container {
  padding: 16px;
}

span.psw {
  float: right;
  padding-top: 16px;
}

/* The Modal (background) */
.modal {
  display: none; /* Hidden by default */
  position: fixed; /* Stay in place */
  z-index: 1; /* Sit on top */
  left: 0;
  top: 0;
  width: 100%; /* Full width */
  height: 100%; /* Full height */
  overflow: auto; /* Enable scroll if needed */
  background-color: rgb(0,0,0); /* Fallback color */
  background-color: rgba(0,0,0,0.4); /* Black w/ opacity */
  padding-top: 60px;
}

/* Modal Content/Box */
.modal-content {
  background-color: #fefefe;
  margin: 5% auto 15% auto; /* 5% from the top, 15% from the bottom and centered */
  border: 1px solid #888;
  width: 80%; /* Could be more or less, depending on screen size */
}

/* The Close Button (x) */
.close {
  position: absolute;
  right: 25px;
  top: 0;
  color: #000;
  font-size: 35px;
  font-weight: bold;
}

.close:hover,
.close:focus {
  color: red;
  cursor: pointer;
}

/* Add Zoom Animation */
.animate {
  -webkit-animation: animatezoom 0.6s;
  animation: animatezoom 0.6s
}

@-webkit-keyframes animatezoom {
  from {-webkit-transform: scale(0)} 
  to {-webkit-transform: scale(1)}
}
  
@keyframes animatezoom {
  from {transform: scale(0)} 
  to {transform: scale(1)}
}

/* Change styles for span and cancel button on extra small screens */
@media screen and (max-width: 300px) {
  span.psw {
     display: block;
     float: none;
  }
  .cancelbtn {
     width: 100%;
  }
}

#depots {
  font-family: "Trebuchet MS", Arial, Helvetica, sans-serif;
  border-collapse: collapse;
  width: 100%;
}

#depots td, #depots th {
  border: 1px solid #ddd;
  padding: 8px;
}

#depots tr:nth-child(even){background-color: #f2f2f2;}

#depots tr:hover {background-color: #ddd;}

#depots th {
  padding-top: 12px;
  padding-bottom: 12px;
  text-align: left;
  background-color: #4CAF50;
  color: white;
}

</style>
         <script type='text/javascript'>

	       		


function createVehicle()
{
window.location = "createVehicle.php";
}

</script>
</head>
<body>
<form align="right" name="form1" method="post" action="log_out.php">

  <input class="button1" name="submit2" type="submit"  value="Log out">
  
  </label>
</form>

<h2> <?php

		
                        echo "Welcome User!!!!!  ".$_SESSION['uname'];  
  
                    ?> </h2>

<input type="text" id="myInput" onkeyup="myFunction()" placeholder="Search for pincode.." title="Type in a name">

<div id="userlist"  style="overflow-x:auto;">


   <?php



$link = mysqli_connect("localhost", "test", "test", "wedeliver");
 
// Check connection
if($link === false){
    die("ERROR: Could not connect. " . mysqli_connect_error());
}
 $name=$_SESSION['uname'];
// Attempt select query execution
$sql = "SELECT * FROM wedeliver.vehicles where uname='$name'";
if($result = mysqli_query($link, $sql)){
    if(mysqli_num_rows($result) > 0){

        echo "<table id='depots'>";
            echo "<tr>";
                echo "<th>id</th>";
                echo "<th>country</th>";
                echo "<th>postal</th>";
                echo "<th>locality</th>";
echo "<th>address</th>";
echo "<th>lat</th>";
echo "<th>long</th>";
echo "<th>TimeSlot</th>";
echo "<th>DepotId</th>";
echo "<th>User</th>";
echo "<th>Capacity</th>";
echo "<th>LastUpdated</th>";
echo "<th>Vehicle Number</th>";
echo "<th>Vehicle Type</th>";
echo "<th>Status</th>";

            echo "</tr>";
        while($row = mysqli_fetch_array($result)){
            echo "<tr>";
 echo "<tr class='userlistoutput'>";
                echo "<td>" . $row[0] . "</td>";
                echo "<td>" . $row[1] . "</td>";
                echo "<td>" . $row[2] . "</td>";
                echo "<td>" . $row[3] . "</td>";
echo "<td>" . $row[4] . "</td>";
echo "<td>" . $row[5] . "</td>";
echo "<td>" . $row[6] . "</td>";



$a=$row[7];
$b=$row[8];
$c=$row[9];
$d=$row[10];
$data=$a.$b.":".$c.$d;
echo "<td>" . $a . "</td>";
echo "<td>" . $row[11] . "</td>";
echo "<td>" . $row[12] . "</td>";
echo "<td>" . $row[13] . "</td>";
echo "<td>" . $row[14] . "</td>";
echo "<td>" . $row[15] . "</td>";
echo "<td>" . $row[16] . "</td>";
echo "<td>" . $row[17] . "</td>";
            echo "</tr>";
        }
        echo "</table>";
        // Free result set
        mysqli_free_result($result);
    } else{
        echo "No Vehicles Registered";
    }
} else{
    echo "ERROR: Could not able to execute $sql. " . mysqli_error($link);
}
 
// Close connection
mysqli_close($link);
   echo "</div>";
   mysqli_close ($con);
?>



<button onclick="createVehicle()" style="width:auto;float:right;" >Register New vehicle</button>




<script>
// Get the modal
var modal = document.getElementById('id01');

// When the user clicks anywhere outside of the modal, close it
window.onclick = function(event) {
    if (event.target == modal) {
        modal.style.display = "none";
    }
}


function myFunction() {
  var input, filter, table, tr, td, i, txtValue;
  input = document.getElementById("myInput");
  filter = input.value.toUpperCase();
  table = document.getElementById("depots");
  tr = table.getElementsByTagName("tr");
  for (i = 0; i < tr.length; i++) {
    td = tr[i].getElementsByTagName("td")[2];
    if (td) {
      txtValue = td.textContent || td.innerText;
      if (txtValue.toUpperCase().indexOf(filter) > -1) {
        tr[i].style.display = "";
      } else {
        tr[i].style.display = "none";
      }
    }       
  }
}






</script>

</body>
</html>


