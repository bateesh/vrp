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
#hiddiv{ 
                float:left;  

                width:75%; 
                height:100px; 
		
            } 
             
#buttondiv{ 
                float:left;  

                width:25%; 
                height:100px; 

            } 
             
             
            h1{ 
                color:green; 
                text-align:center; 
            } 
        </style>  
        
        <div class="wrapper">

        <div id='myMap'></div>
        
        <div id='printoutPanel'></div>
	<div id='hiddiv'></div>
	<div id='buttondiv'>


 <form class="modal-content animate" action="/BingeMapsnew.php" method="post">

      Name: <input type="text" id="myText" name="name"><br>
      Capacity: <input type="text" id="myCapacity" name="capacity"><br>
      DemandList: <input type="text" id="myDemand" name="demand"><br>        
      <button type="submit">Login</button>
      	

  </form>


</div>

        
	
         <script type='text/javascript'>
		var mydata;
		var addressStr='';
		var demand='';
	var addressStr1='';
            function loadMapScenario() {
			console.log('1');
var z;
z = '<?=$_POST['carlist']?>';
console.log(' z is : '+z);
	var str=''+'./'+z+'.json';
console.log(' str is :'+str);
		fetch(str).
		then(function(resp){
		return resp.json()}).
		then(function(data){
		mydsata = data;
		console.log(data);
		var total=data.total;
		var capacity=data.capacity;
document.getElementById('myCapacity').value =
                        capacity;

		console.log('total records: '+total);

		
		for (i = 0; i < total; i++) {
		  console.log('Sending request for record number'+i);
		  console.log(data.locations[i].postalCode);	
			var postal=data.locations[i].postalCode;
			var country=data.locations[i].country;
			var locality=data.locations[i].locality;
			var addressline=data.locations[i].addressline;
			var demandi=data.locations[i].demand;
		  console.log('postal code is '+postal);
console.log('addressline code is '+addressline);
console.log('country code is '+country);
console.log('locality code is '+locality);
	
	var url="http://dev.virtualearth.net/REST/v1/Locations/"+country+"/"+postal+"/"+locality+"/"+addressline+"?key=AmO_vP4NG4zymCmPclwTKC48ItEhs9Rxh1txZW_dzzCT7ttVaXQayptHOfe7n09A";
	console.log('Sending get request on url'+url);
			var xhr = new XMLHttpRequest();
//			var url = "url?data=" + encodeURIComponent(JSON.stringify({"email": "hey@mail.com", "password": "101010"}));
			xhr.open("GET", url, false);
			xhr.setRequestHeader("Content-Type", "application/json");
			xhr.onreadystatechange = function () {
			if (xhr.readyState === 4 && xhr.status === 200) {
		        var json = JSON.parse(xhr.responseText);
			console.log('Received response for record numner'+i);
		        console.log(json);
			
			console.log(''+json.resourceSets[0].resources[0].geocodePoints[0].coordinates);
var lat=json.resourceSets[0].resources[0].geocodePoints[0].coordinates[0];
var long=json.resourceSets[0].resources[0].geocodePoints[0].coordinates[1];
       var loc = new Microsoft.Maps.Location(lat,long);

//var pushpin; = new Microsoft.Maps.Pushpin(loc, { color: 'red' });

var depot=data.locations[i].depot;

if (i==0 || depot=="true")
{
addressStr=''+lat+','+long;
addressStr1=addressStr1+''+i+1+"Address :"+addressline+','+"Locality :"+locality+','+"Postal :"+postal+','+"Country :"+country+','+"Demand :"+demandi+','+"Lat :"+lat+','+"Long :"+long+'<br>'+'<br>';
demand=demand+''+demandi;
console.log(' now here i is '+i);
 pushpin = new Microsoft.Maps.Pushpin(loc, { color: 'blue' });

}
else 
{
addressStr=addressStr+','+lat+','+long;
addressStr1=addressStr1+''+i+1+"Address :"+addressline+','+"Locality :"+locality+','+"Postal :"+postal+','+"Country :"+country+','+"Demand :"+demandi+','+"Lat :"+lat+','+"Long :"+long+'<br>'+'<br>';

demand=demand+','+demandi;
console.log(' now here i is non zero '+i);
pushpin = new Microsoft.Maps.Pushpin(loc, { color: 'red' });

}
console.log('Now address string is :'+addressStr);
console.log('Now demand string is :'+demand);


  


console.log('3');
                map.entities.push(pushpin);



	document.getElementById('printoutPanel').innerHTML =
                        addressStr1;
document.getElementById('hiddiv').innerHTML =
                        addressStr;
document.getElementById('myText').value =
                        addressStr;
document.getElementById('myDemand').value =
                        demand;


		        }
			};
			xhr.send();
}





});
console.log('Welcome address string is :'+addressStr);


	

                var map = new Microsoft.Maps.Map(document.getElementById('myMap'), {});
console.log('2');

                
console.log('4');
	
console.log('5');




                
            }
        </script>
        <script type='text/javascript' src='https://www.bing.com/api/maps/mapcontrol?key=AmO_vP4NG4zymCmPclwTKC48ItEhs9Rxh1txZW_dzzCT7ttVaXQayptHOfe7n09A&callback=loadMapScenario' async defer></script>
    </body>

</html>
<?php
foreach ($_POST as $key => $value) {
    echo "Field ".htmlspecialchars($key)." is ".htmlspecialchars($value)."<br>";
}
?>
