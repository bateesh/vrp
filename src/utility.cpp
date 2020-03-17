/*************************************
Filename :- utility.cpp
Author :- Bateesh Dhingra
Date :- 11th Jul 2019
Description :- utility functions implementation declared in utility.h
***********************************/
#include "utility.h"
#include <curl/curl.h>
#include <jsoncpp/json/json.h>
using namespace std;
  
// extract the first number in a string
int extract_int(const string & term) {
  //cout<<"\n in final extratc ";
  //getchar();
  //cout<<"\n term is "<<term;
  size_t start_p = term.find_first_of("-0123456789");
  int i;
  istringstream(term.substr(start_p, term.size() - start_p)) >> i;
  return i;
}

// extract all numbers in a string
vector < int > extract_ints(const string & term) {
  //cout<<"\n start to extract ints";
  //getchar();
  // split string term into string vector by spaces
  //cout<<"\n term is "<<term;
  //cout<<"\n size is"<<term.size();
  istringstream ss(term);
  string token;
  vector < int > data;
  while (getline(ss, token, ' '))
  {
    //cout<<"\n current token is "<<token;
    //if(token.size()==1  && token[0]==' ')
    //{
      //cout<<"\don not process";
   // continue;
    //}
    //printf("\n see:   %d ",token[0]);
    //cout<<"\n token size is "<<token.size();
    //cout<<"\n token 0 "<<token[0];
    
    data.push_back(extract_int(token));
  }
  return data;
}
// extract the first number in a string
float extract_float(const string & term) {
  //cout<<" \n input term is "<<term;
  size_t start_p = term.find_first_of("-0123456789");
  float i;
  istringstream(term.substr(start_p, term.size() - start_p)) >> i;
  //cout<<"\n extraceted float"<<i;
  return i;
}

// extract all numbers in a string
vector < float > extract_floats(const string & term) {
  // split string term into string vector by spaces
  istringstream ss(term);
  string token;
  vector < float > data;
  while (getline(ss, token, ' ')){
    //cout<<"\nCurretn token "<<token;
    //cout<<" \n pushing"<<token;
    //cout<<"\n token size"<<token.size();
    
    data.push_back(extract_float(token));}
    //cout<<"\n now returning";
    return data;
}
// extract the first number in a string
double extract_double(const string & term) {
  //cout<<" \n input term is "<<term;
  size_t start_p = term.find_first_of("-0123456789");
  double i;
  istringstream(term.substr(start_p, term.size() - start_p)) >> i;
  cout<<"\n extraceted double"<<i;
  return i;
}

// extract all numbers in a string
vector < double > extract_doubles(const string & term) {
  // split string term into string vector by spaces
  istringstream ss(term);
  string token;
  vector < double > data;
  while (getline(ss, token, ' ')){
    cout<<"\nCurretn token "<<token;
    cout<<" \n pushing"<<token;
    cout<<"\n token size"<<token.size();
    
    data.push_back(extract_double(token));}
    cout<<"\n now returning";
    return data;
}

// read CVRP data file and parse to a vector
// first vector contains dimension and capacity
// next 'dimension' vectors contain locations (x, y)
// then the customer demands (demand)
vector < vector < double > > readFile(const char * path) {
	//cout<<" Now readinf file";
  ifstream file(path);
  	//cout<<" opened file";

  string line;
  vector < vector < double > > data;

  vector < double > constraint;
  // read the first line and second line to get the dimension and capacity
  getline(file, line);
  // extract dimension
  constraint.push_back(extract_double(line));
  getline(file, line);
  // extract capacity
  constraint.push_back(extract_double(line));

  getline(file, line);
  // extract capacity
  cout<<"\n current luine is"<<line;
  constraint.push_back(extract_double(line));
    file.ignore(256, '\n');


double vehicleCount=constraint[2];
cout<<"\n here coutn is "<<vehicleCount;
for(int i=0;i<vehicleCount;i++)
{
    getline(file, line);

    vector < double > p = extract_doubles(line);
  // extract capacity
  cout<<"\n size of p is "<<p.size();
  cout<<"\n now here i will purh"<<p[1]<<" "<<p[2];
  constraint.push_back(p[1]);
  constraint.push_back(p[2]);

}

  data.push_back(constraint);

  // ignore the node section start line
  file.ignore(256, '\n');

  // extract locations
  for (int i = 0; i < constraint[0]; ++i) {
    getline(file, line);
    vector < double > p = extract_doubles(line);
    // p[1]: x-coordinate, p[2]: y-coordinate
    // -> p[0]: x, p[1]: y
    p.erase(p.begin());
    data.push_back(p);
  }
  //cout << " in Total number of data is :" << data.size();
  //cout << " capacity is  :" << constraint[0];

  //ignore the demand section start line
  file.ignore(256, '\n');

  vector < double > demand;
  // read the customer demand to the 1D array
  for (int j = 0; j < constraint[0]; ++j) {
    getline(file, line);
    demand.push_back(extract_doubles(line)[1]);
  }
  data.push_back(demand);

  file.ignore(256, '\n');

  vector < double > shipmentID;
  // read the customer demand to the 1D array
  for (int j = 0; j < constraint[0]; ++j) {
    getline(file, line);
    shipmentID.push_back(extract_doubles(line)[1]);
  }
  data.push_back(shipmentID);

  return data;
}

// read CVRP data file and parse to a vector
// first vector contains dimension and capacity
// next 'dimension' vectors contain locations (x, y)
// then the customer demands (demand)
/*vector < vector < double > > readFile_double(const char * path){
	//cout<<" Now readinf file";
  ifstream file(path);
  	//cout<<" opened file";

  string line;
  vector < vector < double > > data;

  vector < double > constraint;
  // read the first line and second line to get the dimension and capacity
  getline(file, line);
  // extract dimension
  constraint.push_back(extract_int(line));
  getline(file, line);
  // extract capacity
  constraint.push_back(extract_int(line));
  data.push_back(constraint);

  // ignore the node section start line
  file.ignore(256, '\n');

  // extract locations
  for (int i = 0; i < constraint[0]; ++i) {
    getline(file, line);
    vector < int > p = extract_ints(line);
    // p[1]: x-coordinate, p[2]: y-coordinate
    // -> p[0]: x, p[1]: y
    p.erase(p.begin());
    data.push_back(p);
  }
  //cout << " in Total number of data is :" << data.size();
  //cout << " capacity is  :" << constraint[0];

  //ignore the demand section start line
  file.ignore(256, '\n');

  vector < int > demand;
  // read the customer demand to the 1D array
  for (int j = 0; j < constraint[0]; ++j) {
    getline(file, line);
    demand.push_back(extract_ints(line)[1]);
  }
  data.push_back(demand);

  return data;
}*/

// read CVRPTW data file and return a CVRPTW instance
CVRPTW readFileWithTimeWindows(const char * path) {
	cout<<"\nOpening File for reading.....";
  cout<<" \nPath is "<<path;
  ifstream file(path);
  
  cout<<"\nFile opened......";
  vector<CVRPTWNode> list;
  
  string line;
  int maxi;
  vector < int > data;
  cout<<"n geti line";
  // read the first line and second line to get the dimension and capacity
  getline(file, line);
cout<<"n processing line "<<line;
  //printf(" %d %d %d",maximumCapacity,maxNumberOfVehicles,numberOfNodes);
  
  // extract dimension
  data=(extract_ints(line));
  
  cout<<"\n size of daa is "<<data.size();
  
  //for(auto itr=data.begin();itr!=data.end();itr++)
  //cout<<"\n "<<*itr;
  int maxNumberOfVehicles=data[1];
  int numberOfNodes=data[2];
  data.clear();
  getline(file, line);
  // extract capacity
  data=(extract_ints(line));
  cout<<"\n size of daa is "<<data.size();
  cout<<"\n "<<data[0]<<" "<<data[1];
  
  int maximumCapacity=data[1];
  cout<<" Number node are"<<numberOfNodes;
  
  for (int i = 0; i <=numberOfNodes; ++i) {

    cout<<" \nProcessing node details"<<i;
    getline(file, line);
    //printf("\nline is ******  %s",line);
    vector < float > nodeDetails = extract_floats(line);

    CVRPTWNode node(int(nodeDetails[0]),nodeDetails[1],nodeDetails[2],
    nodeDetails[3],int(nodeDetails[4]),nodeDetails[8],nodeDetails[9]);
    list.push_back(node);
  }
  CVRPTW cvrptw(maxNumberOfVehicles,numberOfNodes,maximumCapacity,list);
return cvrptw;
  
//  return cvrptw;

}

//getDistance between two points (px,py) and (dx,dy)
double getDistance(int px, int py, int dx, int dy) {
  int a = px - dx;
  int b = py - dy;
  double distance = sqrt(pow(a, 2) + pow(b, 2));
  return distance;
}
double getDistanceByCustomerNumber(vector < vector < int > > data,int c1,int c2)
{
	vector<int> x=data[c1+1];
	vector<int> y=data[c2+1];
	int px=x[0];
	int py=x[1];
	int dx=y[0];
	int dy=y[1];
  int a = px - dx;
  int b = py - dy;
  double distance = sqrt(pow(a, 2) + pow(b, 2));
  return distance;
	
}
void printRoute(vector<int> cr)
{

	cout << endl;
  cout<<" \n now printing with size : "<<cr.size();
	for (auto j = cr.begin(); j != cr.end(); j++)
	{
		cout << " " << *j;
	}
}
double calculateRouteCost(vector<int> route, double distance[300][300])
{
	if (route.size() == 0)
		return 0;
	double cost = 0;
	auto cr = route.begin();
	int prev = *cr;
	cr++;
	while (cr != route.end())
	{
		int curr = *cr;
    //cout<<" \n Adding cost for city :"<<prev<<","<<curr<<" : "<<distance[prev][curr];
		cost += distance[prev][curr];
		prev = curr;
		cr++;
	}
	return cost;
}
double getRouteCapacity(vector < double> demand,vector<int> route)
{
	double total=0;
	for(auto itr=route.begin();itr!=route.end();itr++)
	total=total+demand[*itr];
	return total;
	
}
namespace
{
    size_t callback(
            const char* in,
            size_t size,
            size_t num,
            string* out)
    {
        const size_t totalBytes(size * num);
        out->append(in, totalBytes);
        return totalBytes;
    }
}


double getLiveDistance(vector<double> px,vector<double> dx)
{
  
double distanceTable[2][2];
  string locations="";

  locations+=to_string(px[0]);
  locations+=",";
  locations+=to_string(px[1]);
  locations+=";";
locations+=to_string(dx[0]);
  locations+=",";
  locations+=to_string(dx[1]);
 cout<<"\n locations rae "<<locations;
 cout<<endl; 

  string url="https://dev.virtualearth.net/REST/v1/Routes/DistanceMatrix?origins=";
  url+=locations;
  url+="&";
  url+="destinations=";
  url+=locations;
  url+="&travelMode=driving&key=AmO_vP4NG4zymCmPclwTKC48ItEhs9Rxh1txZW_dzzCT7ttVaXQayptHOfe7n09A";
  /*("https://dev.virtualearth.net/REST/v1/Routes/
  DistanceMatrix?origins=47.6044,-122.3345;47.6731,-122.1185;47.6149,
  -122.1936&destinations=47.6044,-122.3345;47.6731,-122.1185;47.6149,
  -122.1936&travelMode=driving&key=
  AmO_vP4NG4zymCmPclwTKC48ItEhs9Rxh1txZW_dzzCT7ttVaXQayptHOfe7n09A");*/
  cout<<"\n Making Http Request on Url : "<<url;
  cout<<endl;
   CURL* curl = curl_easy_init();

    // Set remote URL.
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

    // Don't bother trying IPv6, which would increase DNS resolution time.
    curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);

    // Don't wait forever, time out after 10 seconds.
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);

    // Follow HTTP redirects if necessary.
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

    // Response information.
    long httpCode(0);
    std::unique_ptr<std::string> httpData(new std::string());

    // Hook up data handling function.
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);

    // Hook up data container (will be passed as the last parameter to the
    // callback handling function).  Can be any pointer type, since it will
    // internally be passed as a void pointer.
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, httpData.get());

    // Run our HTTP GET command, capture the HTTP response code, and clean up.
    curl_easy_perform(curl);
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
    curl_easy_cleanup(curl);

    if (httpCode == 200)
    {
        std::cout << "\nGot successful response from " << url << std::endl;

        // Response looks good - done using Curl now.  Try to parse the results
        // and print them out.
        Json::Value jsonData;
        Json::Value jsonData1;
        Json::Reader jsonReader;

        if (jsonReader.parse(*httpData.get(), jsonData))
        {
            std::cout << "Successfully parsed JSON data" << std::endl;
            std::cout << "\nJSON data received:" << std::endl;
            std::cout << jsonData.toStyledString() << std::endl;
//            const std::string routes(jsonData["routes"][0].asString());

		
 //std::cout<<"\n Npow printing results";
const Json::Value plugins = jsonData["resourceSets"];
const Json::Value plugins_temp = plugins[0]["resources"][0]["results"];
std::cout << plugins_temp.toStyledString() << std::endl;
 //std::cout<<"\n Print results done";

for ( int index = 0; index < plugins_temp.size(); ++index )  // Iterates over the sequence elements.
{
 //std::cout<<"\n started";

            std::cout << plugins_temp[index].toStyledString() << std::endl;
            //const std::Int from_temp();
           // const std::Int to_temp();
	int from=plugins_temp[index]["originIndex"].asInt();
	int to=plugins_temp[index]["destinationIndex"].asInt();
distanceTable[from][to]=plugins_temp[index]["travelDistance"].asDouble();
//std::cout<<"\n setttng "<<from<<" "<<to<<" as "<<" : "<<distanceTable[from][to];
//std::cout<<" " <<plugins[index].asString();
}

std::cout<<"\n Live Distance Matrix From BING maps processed successfully!!!!"<<endl;
for(int i=0;i<2;i++)
{
cout<<endl;
for(int j=0;j<2;j++)
cout<<" "<<distanceTable[i][j];

}
cout<<endl;
//		 std::cout << "\nJSON data received here:" << std::endl;
  //          std::cout << jsonData1.toStyledString() << std::endl;

            
            //std::cout << "\tTime routes: " << routes << std::endl;
        }
        else
        {
            std::cout << "Could not parse HTTP data as JSON" << std::endl;
            std::cout << "HTTP data was:\n" << *httpData.get() << std::endl;
            return -1 ;
        }
    }
    else
    {
        std::cout << "Couldn't GET from " << url << " - exiting" << std::endl;
   //     return 1;
    }

    return distanceTable[0][1];

}
double getLiveDistance(double px, double py, double dx, double dy)
{
  
double distanceTable[2][2];
  string locations="";

  locations+=to_string(px);
  locations+=",";
  locations+=to_string(py);
  locations+=";";
locations+=to_string(dx);
  locations+=",";
  locations+=to_string(dy);
 cout<<"\n locations rae "<<locations;
 cout<<endl; 

  string url="https://dev.virtualearth.net/REST/v1/Routes/DistanceMatrix?origins=";
  url+=locations;
  url+="&";
  url+="destinations=";
  url+=locations;
  url+="&travelMode=driving&key=AmO_vP4NG4zymCmPclwTKC48ItEhs9Rxh1txZW_dzzCT7ttVaXQayptHOfe7n09A";
  /*("https://dev.virtualearth.net/REST/v1/Routes/
  DistanceMatrix?origins=47.6044,-122.3345;47.6731,-122.1185;47.6149,
  -122.1936&destinations=47.6044,-122.3345;47.6731,-122.1185;47.6149,
  -122.1936&travelMode=driving&key=
  AmO_vP4NG4zymCmPclwTKC48ItEhs9Rxh1txZW_dzzCT7ttVaXQayptHOfe7n09A");*/
  cout<<"\n Making Http Request on Url : "<<url;
  cout<<endl;
   CURL* curl = curl_easy_init();

    // Set remote URL.
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

    // Don't bother trying IPv6, which would increase DNS resolution time.
    curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);

    // Don't wait forever, time out after 10 seconds.
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);

    // Follow HTTP redirects if necessary.
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

    // Response information.
    long httpCode(0);
    std::unique_ptr<std::string> httpData(new std::string());

    // Hook up data handling function.
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);

    // Hook up data container (will be passed as the last parameter to the
    // callback handling function).  Can be any pointer type, since it will
    // internally be passed as a void pointer.
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, httpData.get());

    // Run our HTTP GET command, capture the HTTP response code, and clean up.
    curl_easy_perform(curl);
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
    curl_easy_cleanup(curl);

    if (httpCode == 200)
    {
        std::cout << "\nGot successful response from " << url << std::endl;

        // Response looks good - done using Curl now.  Try to parse the results
        // and print them out.
        Json::Value jsonData;
        Json::Value jsonData1;
        Json::Reader jsonReader;

        if (jsonReader.parse(*httpData.get(), jsonData))
        {
            std::cout << "Successfully parsed JSON data" << std::endl;
            std::cout << "\nJSON data received:" << std::endl;
            std::cout << jsonData.toStyledString() << std::endl;
//            const std::string routes(jsonData["routes"][0].asString());

		
 //std::cout<<"\n Npow printing results";
const Json::Value plugins = jsonData["resourceSets"];
const Json::Value plugins_temp = plugins[0]["resources"][0]["results"];
std::cout << plugins_temp.toStyledString() << std::endl;
 //std::cout<<"\n Print results done";

for ( int index = 0; index < plugins_temp.size(); ++index )  // Iterates over the sequence elements.
{
 //std::cout<<"\n started";

            std::cout << plugins_temp[index].toStyledString() << std::endl;
            //const std::Int from_temp();
           // const std::Int to_temp();
	int from=plugins_temp[index]["originIndex"].asInt();
	int to=plugins_temp[index]["destinationIndex"].asInt();
distanceTable[from][to]=plugins_temp[index]["travelDistance"].asDouble();
//std::cout<<"\n setttng "<<from<<" "<<to<<" as "<<" : "<<distanceTable[from][to];
//std::cout<<" " <<plugins[index].asString();
}

std::cout<<"\n Here Live Distance Matrix From BING maps processed successfully!!!!"<<endl;
for(int i=0;i<2;i++)
{
cout<<endl;
for(int j=0;j<2;j++)
cout<<" "<<distanceTable[i][j];

}
cout<<endl;
//		 std::cout << "\nJSON data received here:" << std::endl;
  //          std::cout << jsonData1.toStyledString() << std::endl;

            
            //std::cout << "\tTime routes: " << routes << std::endl;
        }
        else
        {
            std::cout << "Could not parse HTTP data as JSON" << std::endl;
            std::cout << "HTTP data was:\n" << *httpData.get() << std::endl;
            return -1 ;
        }
    }
    else
    {
        std::cout << "Couldn't GET from " << url << " - exiting" << std::endl;
   //     return 1;
    }

    return distanceTable[0][1];

}

void getLiveDistanceTableTSP(vector < vector < double > > d,
double distanceTable[300][300])
{
  double dimension = d.size();
  auto p1 = d.begin();
  auto p2 = d.end();
  //cout<<"\n dimen is "<<dimension<<endl;
  vector < vector < double > > data =vector < vector < double >> (p1, p2);

  string locations="";

for (double i = 0; i < dimension-1; ++i) {
  locations+=to_string(data[i][0]);
  locations+=",";
  locations+=to_string(data[i][1]);
  locations+=";";
}
locations+=to_string(data[dimension-1][0]);
  locations+=",";
  locations+=to_string(data[dimension-1][1]);
 cout<<"\n locations rae "<<locations;
 cout<<endl; 

  string url="https://dev.virtualearth.net/REST/v1/Routes/DistanceMatrix?origins=";
  url+=locations;
  url+="&";
  url+="destinations=";
  url+=locations;
  url+="&travelMode=driving&key=AmO_vP4NG4zymCmPclwTKC48ItEhs9Rxh1txZW_dzzCT7ttVaXQayptHOfe7n09A";
  /*("https://dev.virtualearth.net/REST/v1/Routes/
  DistanceMatrix?origins=47.6044,-122.3345;47.6731,-122.1185;47.6149,
  -122.1936&destinations=47.6044,-122.3345;47.6731,-122.1185;47.6149,
  -122.1936&travelMode=driving&key=
  AmO_vP4NG4zymCmPclwTKC48ItEhs9Rxh1txZW_dzzCT7ttVaXQayptHOfe7n09A");*/
  cout<<"\n Making Http Request on Url : "<<url;
  cout<<endl;
   CURL* curl = curl_easy_init();

    // Set remote URL.
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

    // Don't bother trying IPv6, which would increase DNS resolution time.
    curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);

    // Don't wait forever, time out after 10 seconds.
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);

    // Follow HTTP redirects if necessary.
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

    // Response information.
    long httpCode(0);
    std::unique_ptr<std::string> httpData(new std::string());

    // Hook up data handling function.
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);

    // Hook up data container (will be passed as the last parameter to the
    // callback handling function).  Can be any pointer type, since it will
    // internally be passed as a void pointer.
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, httpData.get());

    // Run our HTTP GET command, capture the HTTP response code, and clean up.
    curl_easy_perform(curl);
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
    curl_easy_cleanup(curl);

    if (httpCode == 200)
    {
        std::cout << "\nGot successful response from " << url << std::endl;

        // Response looks good - done using Curl now.  Try to parse the results
        // and print them out.
        Json::Value jsonData;
        Json::Value jsonData1;
        Json::Reader jsonReader;

        if (jsonReader.parse(*httpData.get(), jsonData))
        {
            std::cout << "Successfully parsed JSON data" << std::endl;
            std::cout << "\nJSON data received:" << std::endl;
            std::cout << jsonData.toStyledString() << std::endl;

            
//            const std::string routes(jsonData["routes"][0].asString());

		
 //std::cout<<"\n Npow printing results";
const Json::Value plugins = jsonData["resourceSets"];
const Json::Value plugins_temp = plugins[0]["resources"][0]["results"];
std::cout << plugins_temp.toStyledString() << std::endl;
 //std::cout<<"\n Print results done";

for ( int index = 0; index < plugins_temp.size(); ++index )  // Iterates over the sequence elements.
{
 //std::cout<<"\n started";

            std::cout << plugins_temp[index].toStyledString() << std::endl;
            //const std::Int from_temp();
           // const std::Int to_temp();
	int from=plugins_temp[index]["originIndex"].asInt();
	int to=plugins_temp[index]["destinationIndex"].asInt();
distanceTable[from][to]=plugins_temp[index]["travelDistance"].asDouble();
//std::cout<<"\n setttng "<<from<<" "<<to<<" as "<<" : "<<distanceTable[from][to];
//std::cout<<" " <<plugins[index].asString();
}

std::cout<<"\n Live Distance Matrix From BING maps processed successfully!!!!"<<endl;
for(int i=0;i<dimension;i++)
{
cout<<endl;
for(int j=0;j<dimension;j++)
cout<<" "<<distanceTable[i][j];

}
cout<<endl;
//		 std::cout << "\nJSON data received here:" << std::endl;
  //          std::cout << jsonData1.toStyledString() << std::endl;

            
            //std::cout << "\tTime routes: " << routes << std::endl;
            std::cout << std::endl;
        }
        else
        {
            std::cout << "Could not parse HTTP data as JSON" << std::endl;
            std::cout << "HTTP data was:\n" << *httpData.get() << std::endl;
            return ;
        }
    }
    else
    {
        std::cout << "Couldn't GET from " << url << " - exiting" << std::endl;
   //     return 1;
    }
cout<<"\n now return..";
    return;
}
//getliveDistance table to communicate with Bing maps and get live distance matrix
void getLiveDistanceTable(vector < vector < double > > d,double distanceTable[300][300])
{
  double dimension = d[0][0];
  auto p1 = d.begin() + 1;
  auto p2 = d.end()-1;
  cout<<"\n dimen is "<<dimension<<endl;
vector < vector < double > > data =vector < vector < double >> (p1, p2);

  string locations="";

for (double i = 0; i < dimension-1; ++i) {
  locations+=to_string(data[i][0]);
  locations+=",";
  locations+=to_string(data[i][1]);
  locations+=";";
}
locations+=to_string(data[dimension-1][0]);
  locations+=",";
  locations+=to_string(data[dimension-1][1]);
 cout<<"\n locations rae "<<locations;
 cout<<endl; 

  string url="https://dev.virtualearth.net/REST/v1/Routes/DistanceMatrix?origins=";
  url+=locations;
  url+="&";
  url+="destinations=";
  url+=locations;
  url+="&travelMode=driving&key=AmO_vP4NG4zymCmPclwTKC48ItEhs9Rxh1txZW_dzzCT7ttVaXQayptHOfe7n09A";
  /*("https://dev.virtualearth.net/REST/v1/Routes/
  DistanceMatrix?origins=47.6044,-122.3345;47.6731,-122.1185;47.6149,
  -122.1936&destinations=47.6044,-122.3345;47.6731,-122.1185;47.6149,
  -122.1936&travelMode=driving&key=
  AmO_vP4NG4zymCmPclwTKC48ItEhs9Rxh1txZW_dzzCT7ttVaXQayptHOfe7n09A");*/
  cout<<"\n Making Http Request on Url : "<<url;
  cout<<endl;
   CURL* curl = curl_easy_init();

    // Set remote URL.
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

    // Don't bother trying IPv6, which would increase DNS resolution time.
    curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);

    // Don't wait forever, time out after 10 seconds.
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);

    // Follow HTTP redirects if necessary.
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

    // Response information.
    long httpCode(0);
    std::unique_ptr<std::string> httpData(new std::string());

    // Hook up data handling function.
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);

    // Hook up data container (will be passed as the last parameter to the
    // callback handling function).  Can be any pointer type, since it will
    // internally be passed as a void pointer.
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, httpData.get());

    // Run our HTTP GET command, capture the HTTP response code, and clean up.
    curl_easy_perform(curl);
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
    curl_easy_cleanup(curl);

    if (httpCode == 200)
    {
        std::cout << "\nGot successful response from " << url << std::endl;

        // Response looks good - done using Curl now.  Try to parse the results
        // and print them out.
        Json::Value jsonData;
        Json::Value jsonData1;
        Json::Reader jsonReader;

        if (jsonReader.parse(*httpData.get(), jsonData))
        {
            std::cout << "Successfully parsed JSON data" << std::endl;
            std::cout << "\nJSON data received:" << std::endl;
            std::cout << jsonData.toStyledString() << std::endl;

            const std::string dateString(jsonData["date"].asString());
            const std::string codes(jsonData["code"].asString());
//            const std::string routes(jsonData["routes"][0].asString());

		
 //std::cout<<"\n Npow printing results";
const Json::Value plugins = jsonData["resourceSets"];
const Json::Value plugins_temp = plugins[0]["resources"][0]["results"];
std::cout << plugins_temp.toStyledString() << std::endl;
 //std::cout<<"\n Print results done";

for ( int index = 0; index < plugins_temp.size(); ++index )  // Iterates over the sequence elements.
{
 //std::cout<<"\n started";

            std::cout << plugins_temp[index].toStyledString() << std::endl;
            //const std::Int from_temp();
           // const std::Int to_temp();
	int from=plugins_temp[index]["originIndex"].asInt();
	int to=plugins_temp[index]["destinationIndex"].asInt();
distanceTable[from][to]=plugins_temp[index]["travelDistance"].asDouble();
//std::cout<<"\n setttng "<<from<<" "<<to<<" as "<<" : "<<distanceTable[from][to];
//std::cout<<" " <<plugins[index].asString();
}

std::cout<<"\n Live Distance Matrix From BING maps processed successfully!!!!"<<endl;
for(int i=0;i<dimension;i++)
{
cout<<endl;
for(int j=0;j<dimension;j++)
cout<<" "<<distanceTable[i][j];

}
cout<<endl;
//		 std::cout << "\nJSON data received here:" << std::endl;
  //          std::cout << jsonData1.toStyledString() << std::endl;

            
            //std::cout << "\tTime routes: " << routes << std::endl;
            std::cout << std::endl;
        }
        else
        {
            std::cout << "Could not parse HTTP data as JSON" << std::endl;
            std::cout << "HTTP data was:\n" << *httpData.get() << std::endl;
            return ;
        }
    }
    else
    {
        std::cout << "Couldn't GET from " << url << " - exiting" << std::endl;
   //     return 1;
    }

    return;
}
//getDistanceTable to preprocess all distance between any two customers
void getDistanceTable(vector < vector < double > > d,double distanceTable[300][300]) {

  double dimension = d[0][0];
  auto p1 = d.begin() + 1;
  auto p2 = d.end()-1;

  vector < vector < double > > data =vector < vector < double >> (p1, p2);
   
  for (int i = 0; i < dimension; ++i) {

    for (int j = i; j < dimension; ++j) {
      int dx = data[j][0] - data[i][0];
    int dy = data[j][1] - data[i][1];
      double distance = sqrt(pow(dx, 2) + pow(dy, 2));10;

    distanceTable[i][j] = distance;
     distanceTable[j][i] = distance;
     //cout<<" \n Setting distance "<<i<<" "<<j<<" as :"<< distance;
     //cout<<" Corresponding points are :"<<data[i][0]<< " ,"<<data[i][1];
    // cout<<endl<<data[j][0]<< " ,"<<data[j][1];
    }
  }
}
//getDistanceTable to preprocess all distance between any two customers
void getDistanceTableTW(CVRPTW cvrptw,double distanceTable[300][300]) {

  int dimension = cvrptw.getNumberOfNodes()+1;
   
  for (int i = 0; i <= dimension; ++i) {

    for (int j = i; j <= dimension; ++j) {

      float dx = cvrptw.getNodeList()[j].getNodeXCordinate() - cvrptw.getNodeList()[i].getNodeXCordinate();
      float dy = cvrptw.getNodeList()[j].getNodeYCordinate() - cvrptw.getNodeList()[i].getNodeYCordinate();    
      double distance = sqrt(pow(dx, 2) + pow(dy, 2));

     
     distanceTable[i][j] = distance;
     distanceTable[j][i] = distance;
    }
  }
}
