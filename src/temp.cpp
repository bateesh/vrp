/*************************************
Filename :- CRVPClarkeWriteSolver.cpp
Author :- Bateesh Dhingra
Date :- 18th Jul 2019
Description :- Solving CVRP using clark and wright savings algorithms
***********************************/
#include "utility.h"

#include "CVRPVehicleOutput.h"

#include "CVRPInput.h"
#include "TSPSolver.h"

struct polarAngle
{
    int cutomerNumber;
    double angle;
};

bool comparater(polarAngle i1, polarAngle i2)
{
	return (i1.angle < i2.angle);
}

int main(int argc, char *argv[])
{cout<<" calling";
    vector<vector<int>> data = readFile("data1.txt");
    cout<<" called";
    CVRPInput input = CVRPInput(data);
    vector<CVRPVehicleOutput> output;
    int dimension = input.getDimension();
    int capacity = input.getCapacity();
    vector<int> demand = input.getDemandList();
    vector<vector<int>> customerCordinates = input.getCustomerCordinates();
    cout << " DIMENSION " << dimension << endl;
    cout << " CAPCCITY " << capacity << endl;
    cout << " cusotmer or ";
    	double distanceTable[300][300];
	getDistanceTable(data, distanceTable);
    double total=0;
   // for (auto itr = customerCordinates.begin(); itr != customerCordinates.end(); itr++)
    vector<int> route1;//0 37 34 19 30 40 11 27 26 23 0
    route1.push_back(0);
    route1.push_back(37);
    route1.push_back(34);
    route1.push_back(19);
    route1.push_back(30);
    route1.push_back(40);
    route1.push_back(11);
    route1.push_back(27);
    route1.push_back(26);
    route1.push_back(23);
    route1.push_back(0);
    
    total += calculateRouteCost(route1, distanceTable);
    cout<<" \n COst of route 1 is: "<<total<<endl;
    // 29 43 13 7 28 23 
        vector<int> route2;// 0 22 42 16 4 36 39 12 25 2 15 9 0 

    route2.push_back(0);

    route2.push_back(22);
    route2.push_back(42);
    route2.push_back(4);
    route2.push_back(16);
    //route2.push_back(4);
    route2.push_back(36);
    route2.push_back(39);

    route2.push_back(12);
    route2.push_back(2);
    route2.push_back(25);
    route2.push_back(9);
    route2.push_back(15);
    
    
    route2.push_back(0);

    double total2=calculateRouteCost(route2, distanceTable);
        total += total2;
        cout<<" \n Cost of route 2 is "<<total2;
  vector<int> route3;// 0 13 17 18 43 29 0 

  route3.push_back(0);

    route3.push_back(13);
    route3.push_back(17);
    route3.push_back(18);
    route3.push_back(43);
    route3.push_back(29);
    route3.push_back(0);

double total3=calculateRouteCost(route3, distanceTable);
        total += total3;
        cout<<" \n Cost of route 3 is "<<total3;  
          vector<int> route4;// 0 1 44 6 24 0 
 
          route4.push_back(0);

    route4.push_back(1);
    route4.push_back(44);
    route4.push_back(6);
    route4.push_back(24);
    route4.push_back(0);
    
        double total4=calculateRouteCost(route4, distanceTable);
        total += total4;
        cout<<" \n Cost of route 4 is "<<total4;

        vector<int> route5;//  0 7 28 32 20 5 21 33 41 8 10 3 0 

        route5.push_back(0);

    route5.push_back(7);
    route5.push_back(28);
    route5.push_back(32);
    route5.push_back(20);
    route5.push_back(5);
    route5.push_back(21);
    route5.push_back(33);
    route5.push_back(41);
    route5.push_back(8);
    route5.push_back(10);
    route5.push_back(3);
    route5.push_back(0);
    //route5.push_back(33);



       double total5=calculateRouteCost(route5, distanceTable);
        total += total5;
        cout<<" \n Cost of route 5 is "<<total5;


  vector<int> route6;//  0 38 31 35 14 0
 
  route6.push_back(0);

    route6.push_back(38);
    route6.push_back(31);
    route6.push_back(35);
    route6.push_back(14);
    route6.push_back(0);
    
    
double total6=calculateRouteCost(route6, distanceTable);
        total += total6;
        cout<<" \n Cost of route 6 is \n"<<total6;
        cout<<"Total cost "<<total;
}