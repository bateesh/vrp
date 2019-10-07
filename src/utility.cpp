/*************************************
Filename :- utility.cpp
Author :- Bateesh Dhingra
Date :- 11th Jul 2019
Description :- utility functions implementation declared in utility.h
***********************************/
#include "utility.h"

using namespace std;
  
// extract the first number in a string
int extract_int(const string & term) {
  size_t start_p = term.find_first_of("-0123456789");
  int i;
  istringstream(term.substr(start_p, term.size() - start_p)) >> i;
  return i;
}

// extract all numbers in a string
vector < int > extract_ints(const string & term) {
  // split string term into string vector by spaces
  istringstream ss(term);
  string token;
  vector < int > data;
  while (getline(ss, token, ' '))
    data.push_back(extract_int(token));
  return data;
}
// extract the first number in a string
float extract_float(const string & term) {
  cout<<" \n input term is "<<term;
  size_t start_p = term.find_first_of("-0123456789");
  float i;
  istringstream(term.substr(start_p, term.size() - start_p)) >> i;
  cout<<"\n extraceted float"<<i;
  return i;
}

// extract all numbers in a string
vector < float > extract_floats(const string & term) {
  // split string term into string vector by spaces
  istringstream ss(term);
  string token;
  vector < float > data;
  while (getline(ss, token, ' ')){
    cout<<"\nCurretn token "<<token;
    cout<<" \n pushing"<<token;
    cout<<"\n token size"<<token.size();
    
    data.push_back(extract_float(token));}
    cout<<"\n now returning";
    return data;
}


// read CVRP data file and parse to a vector
// first vector contains dimension and capacity
// next 'dimension' vectors contain locations (x, y)
// then the customer demands (demand)
vector < vector < int > > readFile(const char * path) {
	cout<<" Now readinf file";
  ifstream file(path);
  	cout<<" opened file";

  string line;
  vector < vector < int > > data;

  vector < int > constraint;
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
}



// read CVRPTW data file and return a CVRPTW instance
CVRPTW readFileWithTimeWindows(const char * path) {
	cout<<"\nOpening File for reading.....";
  cout<<" paht is "<<path;
  ifstream file(path);
  cout<<"\nFile opened......";
  //return ;
  vector<CVRPTWNode> list;
  
  string line;
  int maxi;
  vector < int > data;
  // read the first line and second line to get the dimension and capacity
  getline(file, line);

  //printf(" %d %d %d",maximumCapacity,maxNumberOfVehicles,numberOfNodes);
  
  // extract dimension
  data=(extract_ints(line));
  //cout<<"\n size of daa is "<<data.size();
  //for(auto itr=data.begin();itr!=data.end();itr++)
  //cout<<"\n "<<*itr;
  int maxNumberOfVehicles=data[1];
  int numberOfNodes=data[2];
  data.clear();
  getline(file, line);
  // extract capacity
  data=(extract_ints(line));
  //cout<<"\n size of daa is "<<data.size();
  //cout<<"\n "<<data[0]<<" "<<data[1];
  
  int maximumCapacity=data[1];
  //cout<<" Number node are"<<numberOfNodes;
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
int getRouteCapacity(vector < int> demand,vector<int> route)
{
	int total=0;
	for(auto itr=route.begin();itr!=route.end();itr++)
	total=total+demand[*itr];
	return total;
	
}

//getDistanceTable to preprocess all distance between any two customers
void getDistanceTable(vector < vector < int > > d,double distanceTable[300][300]) {

  int dimension = d[0][0];
  auto p1 = d.begin() + 1;
  auto p2 = d.end()-1;

  vector < vector < int > > data =vector < vector < int >> (p1, p2);
   
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
