<!DOCTYPE html>
<html>

<head>
<meta name="viewport" content="width=device-width, initial-scale=1">
<style>
html, body {
    height:100%;
} 




body {
        background-color: white;
        background-image: url('adminbg.jpeg');
        background-size: auto 100%;
        background-repeat: no-repeat;
        background-position: left top;
        height: 100%;
  text-align: center;
  font-family: Arial, Helvetica;
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
/*Hiding the select arrow for IE10*/
.custom-dropdown select::-ms-expand {
    display: none;
}

.custom-dropdown::before,
.custom-dropdown::after {
  content: "";
  position: absolute;
  pointer-events: none;
}

.custom-dropdown::after { /*  Custom dropdown arrow */
  content: "\25BC";
  height: 1em;
  font-size: .625em;
  line-height: 1;
  right: 1.2em;
  top: 50%;
  margin-top: -.5em;
}

.custom-dropdown::before { /*  Custom dropdown arrow cover */
  width: 2em;
  right: 0;
  top: 0;
  bottom: 0;
  border-radius: 0 3px 3px 0;
  background-color: rgba(0,0,0,.2);
}

.custom-dropdown::after {
  color: rgba(0,0,0,.6);
}

.custom-dropdown select[disabled] {
  color: rgba(0,0,0,.25);
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

</style>
</head>
<body >


<h2> <?php
                        session_start();

                        echo "Welcome Admin!!!!! : ".$_SESSION['uname'];  

  
                    ?> </h2>
<form action="./showAllPending.php" id="showall" method="post">

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
  <input type="submit"  class="button" value="View Pending parcels for Depot" >
</form>


<form action="./createDepot.php" id="createDepot" method="post">
  <input type="submit"  class="button" value="Click here to create new Depot">
</form>
<br>







</body>
<script type="text/javascript" language="javascript">
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
	       		

 function TestOnTextChange()
{
console.log('called./');
  var y = document.getElementById("depot").value;
var names = 'Harry,John,Clark,Peter,Rohn,Alice';
var nameArr = names.split(',');
console.log(nameArr);
console.log(''+y);
var nameArr = y.split(',');



for (index = 0; index < nameArr.length; index++) { 
    console.log(nameArr[index]); 
var val=nameArr[index];
var x = document.getElementById("mylist");
  var option = document.createElement("option");
  option.text = val;
  x.add(option);
} 
  
}
</script>



</html>


