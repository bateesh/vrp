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
{
    vector<vector<int>> data = readFile(argv[1]);
    CVRPInput input = CVRPInput(data);
    vector<CVRPVehicleOutput> output;
    int dimension = input.getDimension();
    int capacity = input.getCapacity();
    vector<int> demand = input.getDemandList();
    vector<vector<int>> customerCordinates = input.getCustomerCordinates();
    cout << " DIMENSION " << dimension << endl;
    cout << " CAPCCITY " << capacity << endl;
    cout << " cusotmer or ";
    for (auto itr = customerCordinates.begin(); itr != customerCordinates.end(); itr++)
    {
        vector<int> data = *itr;
        cout << " " << data[0] << " " << data[1];
    }
    cout << " ehck demand";
    for (auto itr = demand.begin(); itr != demand.end(); itr++)
    {
        cout << " " << *itr << endl;
    }
    cout << "a";
    vector<int> depotLocation = input.getDepotCord();
    cout << "b";

    int p1 = depotLocation[0];
    int p2 = depotLocation[1];
    cout << " depot is " << p1 << " " << p2;

    vector<struct polarAngle> angleList;
    for (int i=1;i<dimension;i++)
    {
        struct polarAngle temp;
        int y=(customerCordinates[i-1][1] - depotLocation[1]);
        int x=(customerCordinates[i-1][0] - depotLocation[0]);
        double angle=atan2(y,x);
        temp.angle=angle;
        temp.cutomerNumber=i;
        angleList.push_back(temp);

    }
	sort(angleList.begin(), angleList.end(), comparater);


 int vehicleCount=1;
 int currentCapacity=0;
 vector<vector<int>> routes;
 vector<int> route;
 route.push_back(0);
 
    for(auto itr=angleList.begin();itr!=angleList.end();itr++)
    {
                struct polarAngle temp=*itr;
  /*            cout<<endl;
                cout<< " andgle : "<<temp.angle;
                cout<<" , custoemrNumber "<<temp.cutomerNumber;
                cout<<" cordinate are "<<customerCordinates[temp.cutomerNumber-1][0];
                cout<<" , "<<customerCordinates[temp.cutomerNumber-1][1];*/
                if(currentCapacity+(demand[temp.cutomerNumber])<=capacity)
                {
                currentCapacity+=demand[temp.cutomerNumber];
                route.push_back(temp.cutomerNumber);
                printf(" \n customer %d can be accomodate in vehicle %d",temp.cutomerNumber,vehicleCount);
                }
                else
                {
                    cout<<"\n Starting new vechicle";
                    vector<int> t=route;
                    t.push_back(0);
                    routes.push_back(t);
                    route.clear();
                    route.push_back(0);
                   
                    vehicleCount++;
                    currentCapacity=demand[temp.cutomerNumber];
                    route.push_back(temp.cutomerNumber);

                }
                

    }
     vector<int> t=route;
     t.push_back(0);
                    routes.push_back(t);
                    route.clear();
   cout<<"\n Now printing routes";
   cout<<" size os "<<routes.size();
   double cost=0;
   double distanceTable[300][300];
	getDistanceTable(data, distanceTable);
  for(auto itr=routes.begin();itr!=routes.end();itr++)
  {cout<<endl;
      printRoute(*itr);
      cost+=calculateRouteCost(*itr,distanceTable);
  }
  cout<<" Unoptimed route cost"<<cost;

}