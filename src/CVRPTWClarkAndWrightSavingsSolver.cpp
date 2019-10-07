/*************************************
Filename :- CRVPClarkeWriteSolver.cpp
Author :- Bateesh Dhingra
Date :- 15th Jul 2019
Description :- Solving CVRP using clark and wright savings algorithms
***********************************/
#include "utility.h"

#include "CVRPVehicleOutput.h"


#include "CVRPInput.h"
#include "TSPSolver.h"
struct SavingsNode
{
	int i;
	int j;
	double savings;
};
void printRouteCodes(int dimension, vector<int> routeNumber)
{
	cout << "\n Route Codes \n";
	for (int ii = 1; ii <= dimension; ii++)
		cout << " " << routeNumber[ii];
}

// Compares two intervals according to staring times.
bool comparater(SavingsNode i1, SavingsNode i2)
{
	return (i1.savings > i2.savings);
}



int main(int argc, char *argv[])
{

	CVRPTW cvrptw=readFileWithTimeWindows(argv[1]);
	printf("\n File read successfully");
	cvrptw.printCVRPInstance();
	//return 0;




	cout<<" \n Reading File:-"<<argv[1]<<endl;
	vector<vector<int>> data = readFile(argv[1]);
	CVRPInput input = CVRPInput(data);
	vector<CVRPVehicleOutput> output;
	int dimension = cvrptw.getNumberOfNodes();//.getDimension();
	int capacity = cvrptw.getmaximumCapacity();
	vector<CVRPTWNode> nodeList=cvrptw.getNodeList();
	vector<int> demand ;
	for(int i=0;i<=dimension;i++)
		demand.push_back(nodeList[i].getNodeDemand());

	vector<vector<float>> customerCordinates;
	for(int i=1;i<=dimension;i++)
	{
		vector<float> temp;
		temp.push_back(nodeList[i].getNodeXCordinate());
		temp.push_back(nodeList[i].getNodeYCordinate());
		customerCordinates.push_back(temp);
	}
	cout << "\nDimension : " << dimension << endl;
	cout << "\nCapacity :" << capacity << endl;
	
	vector<float> depotLocation;
	depotLocation.push_back(nodeList[0].getNodeXCordinate());
	depotLocation.push_back(nodeList[0].getNodeYCordinate());
	
	float p1 = depotLocation[0];
	float p2 = depotLocation[1];

	vector<SavingsNode> savings;

	double distanceTable[300][300];
	getDistanceTableTW(cvrptw, distanceTable);


	for (int i = 1; i <=dimension; i++)
		for (int j = i + 1; j <= dimension; j++)
		{

			double s = distanceTable[0][i] + distanceTable[0][j] - distanceTable[i][j];

			struct SavingsNode temp;
			temp.i = i;
			temp.j = j;
			temp.savings = s;
			savings.push_back(temp);
		}
	sort(savings.begin(), savings.end(), comparater);

	vector<vector<int>> routes(dimension);
	vector<int> routeNumber;

	for (int i = 0; i <= dimension; i++)
	{
		routeNumber.push_back(-1);
	}
	int currentRoute = 0;

	for (auto itr = savings.begin(); itr != savings.end(); itr++)
	{

		SavingsNode node = *itr;

		int routei = routeNumber[node.i];

		int routej = routeNumber[node.j];
		int yy;

		if (routei == -1 && routej == -1)
		{
			float time=0;
			vector<int> route;
			time=nodeList[0].getNodeBeginTime()+nodeList[0].getNodeServiceTime();
			time=time+distanceTable[0][node.i];
			if(nodeList[node.i].getNodeBeginTime()>=time)
				time=time+nodeList[node.i].getNodeServiceTime();
			time=time+distanceTable[node.i][node.j];

			if(nodeList[node.j].getNodeBeginTime()>=time)
				time=time+nodeList[node.i].getNodeServiceTime();
			


			route.push_back(0);
			route.push_back(node.i);
			route.push_back(node.j);
			route.push_back(0);
			int capacityOfRoute = getRouteCapacity(demand, route);
			if (capacityOfRoute <= capacity)
			{
				routes[currentRoute] = route;

				routeNumber[node.i] = currentRoute;
				routeNumber[node.j] = currentRoute;
				currentRoute++;
			}
		}
		else if (routei == -1 || routej == -1)
		{
			if (routei == -1)
			{
				vector<int> routeOfJ = routes[routeNumber[node.j]];
				if (routeOfJ[1] == node.j && (demand[node.i] + getRouteCapacity(demand, routeOfJ)) <= capacity)
				{
					routeOfJ.insert(routeOfJ.begin(),node.i);
					routeOfJ[0] = 0;
					routeOfJ[1] = node.i;
					int rnumber = routeNumber[node.j];
					routes[rnumber] = routeOfJ;
					routeNumber[node.j] = rnumber;
					routeNumber[node.i] = rnumber;
				}
				else if ((routeOfJ[routeOfJ.size() - 1 - 1] == node.j) && demand[node.i] + getRouteCapacity(demand, routeOfJ) <= capacity)
				{
					routeOfJ.push_back(node.i);
					routeOfJ[routeOfJ.size() - 1] = 0;
					routeOfJ[routeOfJ.size() - 2] = node.i;
					int rnumber = routeNumber[node.j];
					routes[rnumber] = routeOfJ;
					routeNumber[node.j] = rnumber;
					routeNumber[node.i] = rnumber;

				}
			}
			else
			{
				vector<int> routeOfi = routes[routeNumber[node.i]];
				if (routeOfi[1] == node.i && demand[node.j] + getRouteCapacity(demand, routeOfi) <= capacity)
				{
					routeOfi.insert(routeOfi.begin(),node.j);
					routeOfi[0] = 0;
					routeOfi[1] = node.j;
					int rnumber = routeNumber[node.i];
					routes[rnumber] = routeOfi;
					routeNumber[node.j] = rnumber;
					routeNumber[node.i] = rnumber;
				}

				else if ((routeOfi[routeOfi.size() - 1 - 1] == node.i) && demand[node.j] + getRouteCapacity(demand, routeOfi) <= capacity)
				{

					routeOfi.push_back(node.j);
					routeOfi[routeOfi.size() - 1] = 0;
					routeOfi[routeOfi.size() - 2] = node.j;
					int rnumber = routeNumber[node.i];
					routes[rnumber] = routeOfi;
					routeNumber[node.j] = rnumber;
					routeNumber[node.i] = rnumber;
				}
			}
		}

		else if (routei != routej)
		{
			vector<int> routeOfi = routes[routei];
			vector<int> routeOfj = routes[routej];
			if (routeOfi[1] == node.i && routeOfj[routeOfj.size() - 2] == node.j && 
			getRouteCapacity(demand, routeOfi) + getRouteCapacity(demand, routeOfj) <= capacity)

			{
				routeOfj.pop_back();
				routeOfi.erase(routeOfi.begin());
				

				for (auto itr = routeOfi.begin(); itr != routeOfi.end(); itr++)
				{
					routeOfj.push_back(*itr);
					routeNumber[*itr] = routej;
				}
				int rnumber = routeNumber[node.j];
				routes[rnumber] = routeOfj;
				routeNumber[node.j] = rnumber;
				routeNumber[node.i] = rnumber;
				routes[routei].clear();

			}

			else if (routeOfi[routeOfi.size() - 2] == node.i && routeOfj[1] == node.j 
			&& (getRouteCapacity(demand, routeOfi) + getRouteCapacity(demand, routeOfj)) <= capacity)

			{
				routeOfi.pop_back();
				routeOfj.erase(routeOfj.begin());
				
				for (auto itr = routeOfj.begin(); itr != routeOfj.end(); itr++)
				{
					routeOfi.push_back(*itr);
					routeNumber[*itr] = routei;
				}
				int rnumber = routeNumber[node.i];
				routes[rnumber] = routeOfi;
				routeNumber[node.j] = rnumber;
				routeNumber[node.i] = rnumber;
				routes[routej].clear();

			}
		}
	}
for(int i=1;i<dimension;i++)
{

	if(routeNumber[i]==-1)
	{

		vector<int> route;
		route.push_back(0);
		route.push_back(i);
		route.push_back(0);
		routes[currentRoute]=route;
		currentRoute++;

	}
}
	cout << "\n Now printing routes ";
	cout << endl;
	double total = 0;
	double optimiZedtotal = 0;
	int rr = 0;
//cout<<"hello";
int countOfRoutes=0;

	for (auto i = routes.begin(); i != routes.end(); i++)
	{
		vector<int> cr = *i;
		if (cr.size() == 0)
		{
		//	routes.erase(i);
			continue;
		}
		countOfRoutes++;
		total += calculateRouteCost(cr, distanceTable);
		
		cout << endl;
		
		cout << " Route " << rr << " : ";

		
		rr++;
		vector<int> tempRoute(cr.begin(),cr.end());
	
		cout<<" \nCapacity this route:- "<<getRouteCapacity(demand,tempRoute);
		
		cout<<" \nCost of this route:- "<<calculateRouteCost(tempRoute, distanceTable)<<"\n";
	
	}

	//printRouteCodes(dimension, routeNumber);
	//cout << "\n Total cost of the route is " << total;
	cout << "\n Total opt cost of the route is: " << optimiZedtotal;
	cout<<"\n Total vechicles used: "<<countOfRoutes;

}
