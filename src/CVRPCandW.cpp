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
	cout<<" \n Reading File:-"<<argv[1]<<endl;
	vector<vector<int>> data = readFile(argv[1]);
	CVRPInput input = CVRPInput(data);
	vector<CVRPVehicleOutput> output;
	int dimension = input.getDimension();
	int capacity = input.getCapacity();
	vector<int> demand = input.getDemandList();
	vector<vector<int>> customerCordinates = input.getCustomerCordinates();
	cout << "\nDimension : " << dimension << endl;
	cout << "\nCapacity :" << capacity << endl;
	/* for (auto itr = customerCordinates.begin(); itr != customerCordinates.end(); itr++)
	{
		vector<int> data = *itr;
		cout << " " << data[0] << " " << data[1];
	}
	cout << " ehck demand";
	int cap=0;
	for (auto itr = demand.begin(); itr != demand.end(); itr++)
	{
		cout << " " << *itr << endl;
		cap+=*itr;
	}
*/
	//cout<<" \n Total demand is "<<cap;
	
	//cout << "a";
	vector<int> depotLocation = input.getDepotCord();
	//cout << "b";

	int p1 = depotLocation[0];
	int p2 = depotLocation[1];
	//cout << " depot is " << p1 << " " << p2;
	vector<SavingsNode> savings;

	double distanceTable[300][300];
	//cout<<"\n anc";
	getDistanceTable(data, distanceTable);
	for (int i = 1; i < dimension; i++)
		for (int j = i + 1; j < dimension; j++)
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
	//	cout << " \nProcessing Saving node " << endl;
	//	cout << " :" << node.i;
	//	cout << " :" << node.j;
	//	cout << " :" << node.savings;
		int yy;

		if (routei == -1 && routej == -1)
		{
///		cout << "\n Both are not in any route so add in enw route ";
			vector<int> route;
			route.push_back(0);
			route.push_back(node.i);
			route.push_back(node.j);
			route.push_back(0);
			int capacityOfRoute = getRouteCapacity(demand, route);
			if (capacityOfRoute <= capacity)
			{
//				cout << "\n capacity constraint satisfied";
				routes[currentRoute] = route;

			//	capacity[currentRoute]=capacityOfRoute;
				//printRoute(route);

				routeNumber[node.i] = currentRoute;
				routeNumber[node.j] = currentRoute;
				currentRoute++;
				//	  cin>>yy;
//				printRouteCodes(dimension, routeNumber);
			}
		}
		else if (routei == -1 || routej == -1)
		{
//			cout << "\n At least one of them is laready there and other is not ";
			if (routei == -1)
			{
//				cout << " hello 1";
//				cout << " " << routei << " is not there ";
				vector<int> routeOfJ = routes[routeNumber[node.j]];
				if (routeOfJ[1] == node.j && (demand[node.i] + getRouteCapacity(demand, routeOfJ)) <= capacity)
				{
//					cout << " \n and " << routej << " is extreme ";
//					cout << " \n current route of j is ";
//	printRoute(routes[routej]);
					//routeOfJ.push_front(node.i);
					routeOfJ.insert(routeOfJ.begin(),node.i);
					routeOfJ[0] = 0;
					routeOfJ[1] = node.i;
					int rnumber = routeNumber[node.j];
					routes[rnumber] = routeOfJ;
					routeNumber[node.j] = rnumber;
					routeNumber[node.i] = rnumber;
//					cout << " \n new route of merge with j ";
//					printRoute(routes[routej]);
					//        cin>>yy;
					//printRouteCodes(dimension, routeNumber);
				}
				else if ((routeOfJ[routeOfJ.size() - 1 - 1] == node.j) && demand[node.i] + getRouteCapacity(demand, routeOfJ) <= capacity)
				{
//					cout << " hello 2";
//					cout << " " << routei << " is not there ";
//					cout << " \n and " << routej << " is extreme ";
//					cout << " \n current route of j is ";
//					printRoute(routes[routej]);
					routeOfJ.push_back(node.i);
					//routeOfJ.insert(routeOfJ.begin(),node.i);
					routeOfJ[routeOfJ.size() - 1] = 0;
					routeOfJ[routeOfJ.size() - 2] = node.i;
					int rnumber = routeNumber[node.j];
					routes[rnumber] = routeOfJ;
					routeNumber[node.j] = rnumber;
					routeNumber[node.i] = rnumber;

//					cout << " \n new route of merge with j ";
//					printRoute(routes[routej]);
					//      cin>>yy;
//					printRouteCodes(dimension, routeNumber);
				}
			}
			else
			{
//				cout << " hello 3";
//				cout << " " << routej << " is not there ";
				vector<int> routeOfi = routes[routeNumber[node.i]];
				if (routeOfi[1] == node.i && demand[node.j] + getRouteCapacity(demand, routeOfi) <= capacity)
				{
//					cout << " hello 4";
//					cout << " " << routej << " is not there ";
//					cout << " \n and " << routei << " is extreme ";
//					cout << " \n current route of i is ";
//					printRoute(routes[routei]);
					//routeOfi.push_front(node.j);
					routeOfi.insert(routeOfi.begin(),node.j);
					routeOfi[0] = 0;
					routeOfi[1] = node.j;
					int rnumber = routeNumber[node.i];
					routes[rnumber] = routeOfi;
					routeNumber[node.j] = rnumber;
					routeNumber[node.i] = rnumber;
//					cout << " \n new route of merge with i ";
//					printRoute(routes[routei]);
//					printRouteCodes(dimension, routeNumber);
					//    cin>>yy;
				}

				else if ((routeOfi[routeOfi.size() - 1 - 1] == node.i) && demand[node.j] + getRouteCapacity(demand, routeOfi) <= capacity)
				{
//					cout << " hello 5";
//					cout << " " << routej << " is not there ";
//					cout << " \n and " << routei << " is extreme ";
//					cout << " \n current route of i is ";
//					printRoute(routes[routei]);

					routeOfi.push_back(node.j);
					routeOfi[routeOfi.size() - 1] = 0;
					routeOfi[routeOfi.size() - 2] = node.j;
					int rnumber = routeNumber[node.i];
					routes[rnumber] = routeOfi;
					routeNumber[node.j] = rnumber;
					routeNumber[node.i] = rnumber;
//					cout << " \n new route of merge with i ";
//					printRoute(routes[routei]);
//					printRouteCodes(dimension, routeNumber);
					// 		        cin>>yy;
				}
			}
		}

		else if (routei != routej)
		{
//			cout << " hello 6";

			vector<int> routeOfi = routes[routei];
			vector<int> routeOfj = routes[routej];
			if (routeOfi[1] == node.i && routeOfj[routeOfj.size() - 2] == node.j && 
			getRouteCapacity(demand, routeOfi) + getRouteCapacity(demand, routeOfj) <= capacity)

			{
//				cout << " \nyes 1 caught";
//				cout << "\n before merge ";
//				printRoute(routeOfi);
//				printRoute(routeOfj);

				routeOfj.pop_back();
				//routeOfj.pop_back();
				//routeOfi.pop_front();
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

//				cout << " \n after merge in j";
//				printRoute(routeOfj);
//				printRouteCodes(dimension, routeNumber);

				// cin>>yy;
			}

			else if (routeOfi[routeOfi.size() - 2] == node.i && routeOfj[1] == node.j 
			&& (getRouteCapacity(demand, routeOfi) + getRouteCapacity(demand, routeOfj)) <= capacity)

			{
//				cout << " hello 7";
//				cout << " \nyes 1 caught";
//				cout << "\n before merge ";
				//cout<<" \n capcity of following route is "<<getRouteCapacity
//				printRoute(routeOfi);
//				printRoute(routeOfj);
				//routeOfi.pop_back();
				//routeOfj.pop_front();
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

//				cout << " \n after merge in i";
//				printRoute(routeOfi);
//				printRouteCodes(dimension, routeNumber);
				//cin>>yy;
			}
		}
	}
//cout<<"hello 10";
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
		tempRoute.erase(tempRoute.begin());
		tempRoute.pop_back();
		int capacityHandled=0;
		

		//vector<vector<int>> tspInputnput.convertRouteToCordinateList(tempRoute);
		//TSPSolver tsp(tspInput,depotLocation);
	
		for(auto itr=tempRoute.begin();itr!=tempRoute.end();itr++)
		capacityHandled=capacityHandled+demand[*itr];
		
	//	cout<<" Calling TSP now";
	    //vector<vector<int>> tspOutput=tsp.solveTSP();
	//	cout<<" Called TSP now";
		vector<int> optimizedRoute=tempRoute;//input.convertCordinateListToRoute(tspOutput);
		optimizedRoute.push_back(0);
		optimizedRoute.insert(optimizedRoute.begin(),0);
		
	//cout<<" optimized route after tsp is ";
	//	printRoute(optimizedRoute);
		cout<<" \nCapacity this route:- "<<capacityHandled<<"\n";
		
		cout<<" \nCost of this route:- "<<calculateRouteCost(optimizedRoute, distanceTable)<<"\n";
		optimiZedtotal += calculateRouteCost(optimizedRoute, distanceTable);
		calculateRouteCost	(optimizedRoute, distanceTable);
	printRoute(optimizedRoute);
	
	}

	//printRouteCodes(dimension, routeNumber);
	//cout << "\n Total cost of the route is " << total;
	cout << "\n Total opt cost of the route is: " << optimiZedtotal;
	cout<<"\n Total vechicles used: "<<countOfRoutes;

}
