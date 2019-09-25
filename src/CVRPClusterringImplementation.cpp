/*************************************
Filename :- CRVPClarkeWriteSolver.cpp
Author :- Bateesh Dhingra
Date :- 15th Jul 2019
Description :- Solving CVRP using clark and wright savings algorithms
***********************************/
#include "utility.h"
#include <stdlib.h>     /* srand, rand */

#include "CVRPVehicleOutput.h"
#include "CVRPInput.h"
#include "TSPSolver.h"
vector<vector<int>> updateCenteroid(vector<vector<int>> clusterCenteroid,
									vector<vector<int>> nodeCentroid, vector<vector<int>> custmerCordinates);
vector<vector<int>> checkCapacityConstrain(int capacity, vector<int> demand,
										   vector<vector<int>> prevNodeCentroid, double distanceTable[300][300]);
vector<int> getNearestCentroidLocation(vector<int> location,vector<vector<int>> clusterCenteroid);

// A hash function used to hash a pair of any kind 
struct hash_pair { 
    template <class T1, class T2> 
    size_t operator()(const pair<T1, T2>& p) const
    { 
        auto hash1 = hash<T1>{}(p.first); 
        auto hash2 = hash<T2>{}(p.second); 
        return hash1 ^ hash2; 
    } 
}; 
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
//for (auto j = cr.begin(); j != cr.end(); j++)
//		{
//			cout << " " << *j;
//		}
		vector<int> tempRoute(cr.begin(),cr.end());
		tempRoute.erase(tempRoute.begin());
		tempRoute.pop_back();
	//	cout<<"\n Now update route for tsp is";
	//	  for (auto j = tempRoute.begin(); j != tempRoute.end(); j++)
	//	{
	//		cout << " " << *j;
	//	}
		int capacityHandled=0;
		

		vector<vector<int>> tspInput=input.convertRouteToCordinateList(tempRoute);
		TSPSolver tsp(tspInput,depotLocation);
	
		for(auto itr=tempRoute.begin();itr!=tempRoute.end();itr++)
		capacityHandled=capacityHandled+demand[*itr];
		
	//	cout<<" Calling TSP now";
	    vector<vector<int>> tspOutput=tsp.solveTSP();
	//	cout<<" Called TSP now";
		vector<int> optimizedRoute=input.convertCordinateListToRoute(tspOutput);
		optimizedRoute.push_back(0);
		optimizedRoute.insert(optimizedRoute.begin(),0);
		
	//cout<<" optimized route after tsp is ";
	//	printRoute(optimizedRoute);
		cout<<" \nCapacity this route:- "<<capacityHandled<<"\n";
		
		cout<<" \nCost of this route:- "<<calculateRouteCost(optimizedRoute, distanceTable)<<"\n";
		optimiZedtotal += calculateRouteCost(optimizedRoute, distanceTable);
		calculateRouteCost	(optimizedRoute, distanceTable);

	
	}

	//printRouteCodes(dimension, routeNumber);
	//cout << "\n Total cost of the route is " << total;
	cout << "\n Total opt cost of the route is: " << optimiZedtotal;
   	cout<<"\n Total vechicles used: "<<countOfRoutes;
//Implementaion of new Clusterring  algorithm
    cout << "**************************************Now running clusterring algorithm";
	bool found = false;
    bool move;
    int clusterSize = countOfRoutes;
    int totalNodes = dimension - 1;
    while (found == false)
    {
        move = true;
        srand(time(NULL));
        vector<vector<int>> clusterCenteroid;
        for (int i = 0; i < clusterSize; i++)
        {
            while (true)
            {
                int centroid = (rand() % totalNodes);
				bool c1=false;
				int x=customerCordinates[centroid][0];
				int y=customerCordinates[centroid][1];
				for(auto itr=clusterCenteroid.begin();itr!=clusterCenteroid.end();itr++)
				{
					vector<int> d=*itr;
					if(d[0]==x && d[1]==y)
					c1=true;
				}
                if (c1==false)
                {
					vector<int> d=customerCordinates[centroid];
                    clusterCenteroid.push_back(d);
                    break;
                }
            }
			
        }

		cout<<"\nThe cluster node selected are:-\n";
		for (int i = 0; i < clusterSize; i++)
		{
			cout<<" "<<clusterCenteroid[i][0]<<" , "<<clusterCenteroid[i][1];
		}
		//for(int i=0;i<clusterCenteroid.size();i++)
		//cout<<" "<<clusterCenteroid[i];
		cout<<endl;
		vector<vector<int>> prevNodeCentroid;
        for (int i = 0; i <= totalNodes - 1; i++)
        {
            vector<int> location = customerCordinates[i];
            vector<int> shortestCentroid = getNearestCentroidLocation(location, clusterCenteroid);
			prevNodeCentroid.push_back(shortestCentroid);
			
			cout<<"\n Nearest details check for "<<location[0]<<" "<<location[1];
			cout<<"\n now got nearest"<<shortestCentroid[0]<<" "<<shortestCentroid[1];
			

        }
		cout<<" \n All nodes allcoated to shortest cluster\n";

        while (move == true)
        {
			int yy;
		// /cin>>yy;
        
			cout<<"\n Now start new iteration";
			bool check=false;
			cout<<"\n initialized bool";
			vector<vector<int>> newCentroid;
			cout<<"\n Declaration done";
			cout<<"\n now updating the cluster centroids..";
								for (int i = 0; i < clusterSize; i++)
		{
			cout<<" "<<clusterCenteroid[i][0]<<" , "<<clusterCenteroid[i][1];
		}

            vector<vector<int>> centroidList = updateCenteroid(clusterCenteroid,prevNodeCentroid,customerCordinates);
			cout<<"\n Updation doen succesfully the cluster centroids..";
					for (int i = 0; i < clusterSize; i++)
		{
			cout<<" "<<centroidList[i][0]<<" , "<<centroidList[i][1];
		}
		cout<<"\n continue...\n";
			
            for (int i = 0; i <= totalNodes - 1; i++)
            {
                vector<int> location = customerCordinates[i];
				cout<<"\n getting nearest for customer "<<location[0]<<" "<<location[1];
                vector<int> shortestCentroid  = getNearestCentroidLocation(location, centroidList);
				
				cout<<"\n now got nearest"<<shortestCentroid[0]<<" "<<shortestCentroid[1];
				newCentroid.push_back(shortestCentroid);
				if(newCentroid[i][0]!=prevNodeCentroid[i][0] 
				 || newCentroid[i][1]!=prevNodeCentroid[i][1] )
				 {
					 check=true;
				 }


            }

			cout<<"\n One iteration of loop again done\n";
			cout<<"\n value of check is "<<check;
			prevNodeCentroid=newCentroid;
			clusterCenteroid=centroidList;

            if (check==false)
                move = false;

        }
		cout<<" \n Found one iteration... NOw checing the capcity lkeft yout";
		int yy;
		cin>>yy;
		if(checkCapacityConstrain(capacity,demand,prevNodeCentroid,distanceTable).size()>0)
        found=true;
    }
}

vector<vector<int>> updateCenteroid(vector<vector<int>> clusterCenteroid, 
						vector<vector<int>> nodeCentroid, vector<vector<int>> custmerCordinates)
{
	cout<<"\n start x allocaton";
	vector<int> temp;
	int y1;
	vector<vector<int>> x;
	vector<vector<int>> y;
	 for(int i=0;i<clusterCenteroid.size();i++)
	{
	x.push_back(temp);
	y.push_back(temp);
	}
	cout<<"\n done x allocaton";
	cout<<" \n szie of x and y "<<x.size()<<" "<<y.size();
	int count =0;
	for(int i=0;i<custmerCordinates.size();i++)
	{
		vector<int> clusterid=nodeCentroid[i];
				int j;
			for( j=0;j<clusterCenteroid.size();j++)
			{
				if(clusterid[0]==clusterCenteroid[j][0] &&
				   clusterid[1]==clusterCenteroid[j][1] )
				   break;
			}

		vector<int> data=custmerCordinates[i];
		x[j].push_back(data[0]);
		y[j].push_back(data[1]);

	}
	for(int i=0;i<x.size();i++)
	{	
		vector<int> sum;

		int totx=0;
		int toty=0;
		for(int j=0;j<x[i].size();j++)
		{
		totx+=x[i][j];
		toty+=y[i][j];
		}
		totx=totx/x.size();
		toty=toty/y.size();
		sum.push_back(totx);
		sum.push_back(toty);
		cout<<"\n updating to "<<totx<<" "<<toty;
		clusterCenteroid[i]=sum;
	}
	return clusterCenteroid;
}
vector<int> getNearestCentroidLocation(vector<int> location,vector<vector<int>> clusterCenteroid)
{

	cout<<"\n input list is:-";
	for(auto itr=clusterCenteroid.begin();itr!=clusterCenteroid.end();itr++)
	{
		vector<int> d=*itr;
	cout<<" "<<d[0]<<" "<<d[1];
	}
int x=location[0];
int y=location[1];
int px=clusterCenteroid[0][0];
int py=clusterCenteroid[0][1];
int dx,dy;
dx=x-px;
dy=y-py;
int a,b;
a=px;
b=py;
float min=sqrt(pow(dx, 2) + pow(dy, 2));
cout<<"\n min is "<<min;

for(auto itr=clusterCenteroid.begin()+1;itr!=clusterCenteroid.end();itr++)
{
	vector<int> d=*itr;
	int px1=d[0];
	int py1=d[1];
	dx=x-px1;
	dy=y-py1;

	float distance=	sqrt(pow(dx, 2) + pow(dy, 2));
	cout<<" found distance as "<<distance;
	if(distance<min)
	{
		a=px1;
		b=py1;
		cout<<"\n min updated...";
	}
}
vector<int> shortest;
shortest.push_back(a);
shortest.push_back(b);
return shortest;
}

vector<vector<int>> checkCapacityConstrain(int capacity,vector<int> demand,
vector<vector<int>> prevNodeCentroid,double distanceTable[300][300])
{
	cout<<" Size if demand list is "<<demand.size();

  auto p1 = demand.begin() + 1;
  auto p2 = demand.end();

  vector<int> filterDemand = vector<int>(p1, p2);
  unordered_map<pair<int, int>,vector<int>,hash_pair> umap;

  for(int i=0;i<prevNodeCentroid.size();i++)
  {
	  vector<int> centroid=prevNodeCentroid[i];
	  pair<int, int> p1(centroid[0],centroid[1]);
	  umap[p1].push_back(i);
  }
  vector<vector<int>> routes;
  vector<vector<int>> route1;
  for(auto itr=umap.begin();itr!=umap.end();itr++)
  {
	  routes.push_back(itr->second);

  }

bool flag=true;
for(auto itr=routes.begin();itr!=routes.end();itr++)
{
	if(calculateRouteCost(*itr,distanceTable)>capacity)
	flag=false;

}
if(flag==false)
return route1;
return routes;
}