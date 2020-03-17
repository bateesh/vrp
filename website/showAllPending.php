<?php

session_start();

?>
<!DOCTYPE html>
<html>
    <head>

        <title>adddefaultpushpinHTML</title>
<meta charset="utf-8" /> 
    <meta name="viewport"
          content="width=device-width, initial-scale=1.0" /> 
    <meta http-equiv="X-UA-Compatible" content="ie=edge" /> 
        <meta http-equiv='Content-Type' content='text/html; charset=utf-8'/>
        <style type='text/css'>body{margin:0;padding:0;overflow:hidden;font-family:'Segoe UI',Helvetica,Arial,Sans-Serif}</style>
    </head>
<h2>
Showing Pending Requests
</h2>
    <body>
<div class="centered">
    <div id="loader" class="spinner loading">
      <div class="loading-text">Loading ...</div>
    </div>

  </div>

<script> 
        document.onreadystatechange = function() { 
            if (document.readyState !== "complete") { 
                document.querySelector( 
                  "body").style.visibility = "hidden"; 
                document.querySelector( 
                  "#loader").style.visibility = "visible"; 
            } else { 
                document.querySelector( 
                  "#loader").style.display = "none"; 
                document.querySelector( 
                  "body").style.visibility = "visible"; 
            } 
        }; 
    </script> 
 <style>  
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
label { width: 200px; float: left; margin: 0 20px 0 0; }
span { display: block; margin: 0 0 3px; font-size: 1.2em; font-weight: bold; }
input { width: 200px; border: 1px solid #000; padding: 5px; }
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
             
#buttondiv{ 
                float:right;  


                height:100px; 

            } 
             
             
            h1{ 
                color:green; 
                text-align:center; 
            } 
        </style>  
         <form class="modal-content animate" action="/BingeMapsnew.php" method="post">


  <label for="depotid">
    <span>Depot ID</span>
    <input type="text" id="depotid" />
  </label>
  <label for="timeslots">
    <span>Time Slots</span>
    <input type="text" id="timeslots" />
  </label>
   
  </form>
<br>
<br>
<br>
<br>
        <div class="wrapper">

        <div id='myMap'></div>
        
        <div id='printoutPanel'></div>
	<div id='buttondiv'>

<form  name="form1" method="post" action="BingeMapsnew.php">

  
  
    <input type="text" id="did" name="did" />

    <input type="text" id="tms" name="tms"/>
  </label>
      <button type="submit" class="button">Allocate Pending Requests</button>
</form>

</div>



        
	
         <script type='text/javascript'>



		var mydata;
		var addressStr='';
		var demand='';
	var addressStr1='';
            function loadMapScenario() {
			console.log('1');
var depot,timeslots;
depot = '<?=$_POST['depot']?>';
timeslots = '<?=$_POST['timeslots']?>';
document.getElementById("depotid").value = depot;

document.getElementById("timeslots").value = timeslots;

document.getElementById("did").value = depot;

document.getElementById("tms").value = timeslots;



console.log(' depotid is : '+depot);
console.log(' timwlosts is :'+timeslots);






var str_arr = timeslots.split ("-");  
var str_start = str_arr[0].split(":");
var sta = str_start[0];
var stb = str_start[1];
var str_start = str_arr[1].split(":");
var eta = str_start[0];
var etb = str_start[1];
console.log(' depotid is : '+depot);
console.log(' sta is :'+sta);
console.log(' stb is : '+stb);
console.log(' eta is :'+eta);
console.log(' etb is : '+etb);
var depotlat,depotlong;
var h = new XMLHttpRequest();

var url = 'getlatLongByDepotId.php?depot='+depot;
h.open('GET', url, false);

//Send the proper header information along with the request
h.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');

h.onreadystatechange = function() {//Call a function when the state changes.
    if(h.readyState == 4 && h.status == 200) {

  console.log(' see result : '+h.responseText);
   var json = JSON.parse(h.responseText);

 depotlat=json.lat;
 depotlong=json.long;
    }
}
h.send();



var map = new Microsoft.Maps.Map(document.getElementById('myMap'), {
    /* No need to set credentials if already passed in URL */
    center: new Microsoft.Maps.Location(depotlat, depotlong),
    zoom: 12
});





















var http = new XMLHttpRequest();
var lat,long,address,locality,postal,locality,country,demand;
var url = 'getPendingShipmentsByDepotId.php?depot='+depot+'&sta='+sta+'&stb='+stb+'&eta='+eta+'&etb='+etb;
http.open('GET', url, false);

//Send the proper header information along with the request
http.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');

http.onreadystatechange = function() {//Call a function when the state changes.
    if(http.readyState == 4 && http.status == 200) {

  console.log(' see result : '+http.responseText);
   var json = JSON.parse(http.responseText);

 lat=json.lat;
  long=json.long;
  address=json.address;	
 locality=json.locality;
	 postal=json.postal;
	 country=json.country;	
 demand=json.demand;
    }
}
http.send();
console.log("\n now staring");
 lat=lat.split(",");
  long=long.split(",");
  address=address.split(",");	
 locality=locality.split(",");
	 postal=postal.split(",");
	 country=country.split(",");	
 demand=demand.split(",");


var n = lat.length;
var pushpin,addressStr,addressStr1;
 var loc1 = new Microsoft.Maps.Location(depotlat,depotlong);
 pushpin = new Microsoft.Maps.Pushpin(loc1, { color: 'blue' });
 map.entities.push(pushpin);
for(i=0;i<n;i++){



 var loc = new Microsoft.Maps.Location(lat[i],long[i]);

if (i==0 )
{
addressStr=''+lat[i]+','+long[i];
addressStr1=''+(i+1)+"Address :"+address[i]+','+"Locality :"+locality[i]+','+"Postal :"+postal[i]+','+"Country :"+country[i]+','+"Demand :"+demand[i]+','+"Lat :"+lat[i]+','+"Long :"+long[i]+'<br>'+'<br>';

 pushpin = new Microsoft.Maps.Pushpin(loc, { color: 'red' });

}
else 
{
addressStr=addressStr+','+lat[i]+','+long[i];
addressStr1=addressStr1+''+(i+1)+"Address :"+address[i]+','+"Locality :"+locality[i]+','+"Postal :"+postal[i]+','+"Country :"+country[i]+','+"Demand :"+demand[i]+','+"Lat :"+lat[i]+','+"Long :"+long[i]+'<br>'+'<br>';

pushpin = new Microsoft.Maps.Pushpin(loc, { color: 'red' });

}
// pushpin = new Microsoft.Maps.Pushpin(loc, { color: 'blue' });
                map.entities.push(pushpin);


}

document.getElementById('printoutPanel').innerHTML =addressStr1;
			
}
        </script>
        <script type='text/javascript' src='https://www.bing.com/api/maps/mapcontrol?key=AmO_vP4NG4zymCmPclwTKC48ItEhs9Rxh1txZW_dzzCT7ttVaXQayptHOfe7n09A&callback=loadMapScenario' async defer></script>
    </body>

</html>

