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

            #userlist{ 



                height: 650px;
		overflow-y: scroll;
overflow-x: scroll;
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
function populateTimeWindows()
{
var select = document.getElementById("timeslots");
var length = select.options.length;
for (i = length-1; i > 0; i--) {
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
	       		


function showdepotportal()
{
document.getElementById('id01').style.display='block';
}
function createDepot()
{
window.location = "createDepot.php";
}

</script>
</head>
<body>
<form align="right" name="form1" method="post" action="log_out.php">

  <input class="button1" name="submit2" type="submit"  value="Log out">
  
  </label>
</form>

<h2> <?php

		
                        echo "Welcome Admin!!!!!  ".$_SESSION['uname'];  
  
                    ?> </h2>

<input type="text" id="myInput" onkeyup="myFunction()" placeholder="Search for pincode.." title="Type in a name">

<div id="userlist" >


   <?php



$link = mysqli_connect("localhost", "test", "test", "wedeliver");
 
// Check connection
if($link === false){
    die("ERROR: Could not connect. " . mysqli_connect_error());
}
 
// Attempt select query execution
$sql = "SELECT * FROM wedeliver.depot";
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
echo "<th>TimeSlots</th>";
echo "<th>TotalVehicles</th>";
echo "<th>CreatedBy</th>";
echo "<th>LastUpdated</th>";

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

//echo "<td>" . $row[7] . "</td>";
echo "<td>";
echo "<select><b></b>";
$i=1;
$a=$row[7];
$b=$row[8];
$c=$row[9];
$twc=$c-$a;
$twc=$twc/$row[11];
while($i<=$row[11])
{
$x=$a+$twc;
echo "<option>$a.$b:$x.$b</option>";
$i=$i+1;
$a=$x;
}
echo "</select>";
echo "</td>";
echo "<td>" . $row[12] . "</td>";
echo "<td>" . $row[13] . "</td>";
echo "<td>" . $row[14] . "</td>";

            echo "</tr>";
        }
        echo "</table>";
        // Free result set
        mysqli_free_result($result);
    } else{
        echo "No records matching your query were found.";
    }
} else{
    echo "ERROR: Could not able to execute $sql. " . mysqli_error($link);
}
 
// Close connection
mysqli_close($link);
   echo "</div>";
   mysqli_close ($con);
?>



<button onclick="showdepotportal()" style="width:auto;float:right;" >Show Pending Shipments</button>

<button onclick="createDepot()" style="width:auto;">Register New Depot</button>

<div id="id01" class="modal">
  
  <form class="modal-content animate" action="/showAllPending.php" method="post">
    










<span class="custom-dropdown big">

        <label for="depot"><b>Select Depot to View pending parcels</b></label>

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

<select name="timeslots" id="timeslots"   padding-left="50px"><b></b>
  <option value="Select Time Slots">Select time slots</option>

</select>


</span>
  <input type="submit"  class="button" id="button" value="View Pending parcels for Depot" >










  </form>
</div>

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


