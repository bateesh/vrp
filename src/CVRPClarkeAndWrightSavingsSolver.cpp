/*************************************
Filename :- CRVPClarkeWriteSolver.cpp
Author :- Bateesh Dhingra
Date :- 15th Jul 2019
Description :- Solving CVRP using clark and wright savings algorithms
***********************************/
#include "utility.h"
#define  mpitr multimap<double,vector<int>>::iterator
#include "CVRPVehicleOutput.h"

#include "CVRPInput.h"
#include "TSPSolver.h"
#include <jsoncpp/json/writer.h>
#include <iostream>
#include <fstream>
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
void printMap(multimap<double,vector<int>> mp)

{
	cout<<"\n";
	for(auto itr=mp.begin();itr!=mp.end();itr++)
	{
		cout<<" Capacity : "<<itr->first;
		cout<<",Route : ";
		for(auto t=itr->second.begin();t!=itr->second.end();t++)
		{
			
			cout<<"\t"<<*t;
		}
		cout<<endl;
	}
}

// Compares two intervals according to staring times.
bool comparater(SavingsNode i1, SavingsNode i2)
{
	return (i1.savings > i2.savings);
}

void convertResultToJson(vector<vector<int>> routes,CVRPInput input)
{
    Json::Value event;   
    Json::Value vec(Json::arrayValue);
   // vec.append(Json::Value(1));
    //vec.append(Json::Value(2));
    //vec.append(Json::Value(3));
	vector<vector<double>> cord=input.getAllCordinates();
	vector<double> demand=input.getDemandList();
	Json::Value driversList(Json::arrayValue);
	
	int jj=0;
	
	for(int i=0,j=0;i<routes.size();i++)
	{
		double cap=0;
		int driverId=(int)input.getVechicleID()[i];

		string driver="Driver_"+to_string(driverId);
		
		vector<int> currentRoute=routes[i];
		if(currentRoute.size()==0)
		continue;
		jj++;
		Json::Value shipmentsOfDriver(Json::arrayValue);

		for(int j=0;j<currentRoute.size();j++)
		{
			//vec.append(Json::Value(currentRoute[i]));
			cap+=demand[currentRoute[j]];

			Json::Value vec(Json::arrayValue);
			double shipment=input.getShipmentID()[currentRoute[j]];
			shipmentsOfDriver.append(Json::Value(shipment));
   
			double a=cord[currentRoute[j]][0];
			double b=cord[currentRoute[j]][1];
			vec.append(Json::Value(a));
			vec.append(Json::Value(b));
			event["result"][driver][to_string(j+1)]=vec;
		}
		event["result"][driver]["capacity"]=cap;
		event["result"][driver]["total"]=to_string(currentRoute.size());
		event["result"][driver]["shipmentList"]=shipmentsOfDriver;
		event["result"][driver]["driverID"]=to_string(driverId);
		driversList.append(Json::Value(driver));
	}
    event["result"]["totalDrivers"] = to_string(jj);
	event["result"]["driverList"] = driversList;


    //event["competitors"]["away"]["code"] = 89223;
    //event["competitors"]["away"]["name"] = "Aston Villa";
    //event["competitors"]["away"]["code"]=vec;

    std::cout << event << std::endl;


	std::ofstream file_id;
    file_id.open("result.json");

    //Json::Value value_obj;
    //populate 'value_obj' with the objects, arrays etc.

    //Json::StyledWriter styledWriter;
    file_id << event;

    file_id.close();
}

int main(int argc, char *argv[])
{
	cout<<" \n Reading File:-"<<argv[1]<<endl;
	vector<vector<double>> data = readFile(argv[1]);
	
	CVRPInput input = CVRPInput(data);
	vector<CVRPVehicleOutput> output;
	double dimension = input.getDimension();
	double capacity = input.getCapacity();
	vector<double> demand = input.getDemandList();
	vector<vector<double>> customerCordinates = input.getCustomerCordinates();
	double v=input.getVehicles();
	cout << "\nDimension : " << dimension << endl;
	cout << "\nCapacity :" << capacity << endl;
	cout << "\nVechile count :" << v << endl;
	cout<<"\n chk capacity";
	vector<double> vehicleCapacity=input.getVechilesCapacity();
  	multimap<double,vector<int>>  mp;
	

for (auto itr = vehicleCapacity.begin(); itr != vehicleCapacity .end(); itr++)
	{
		double data = *itr;
		vector<int> vc;
        mp.insert(pair <double, vector<int>> (data, vc)); 

		
		cout<<"\n data : "<<data;
		cout << " " << data;
		cout<<endl;
	}
	 for (auto itr = customerCordinates.begin(); itr != customerCordinates.end(); itr++)
	{
		vector<double> data = *itr;
		cout << " " << data[0] << " " << data[1];
		cout<<endl;
	}
	cout << " ehck demand";
	double cap=0;
	for (auto itr = demand.begin(); itr != demand.end(); itr++)
	{
		cout << " " << *itr << endl;
		cap+=*itr;
	}

	//cout<<" \n Total demand is "<<cap;
	
	//cout << "a";
	vector<double> depotLocation = input.getDepotCord();
	//cout << "b";

	double p1 = depotLocation[0];
	double p2 = depotLocation[1];
	//cout << " depot is " << p1 << " " << p2;
	vector<SavingsNode> savings;

	double distanceTable[300][300];
	//cout<<"\n anc";
	getLiveDistanceTable(data, distanceTable);
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

	vector<vector<int>> routes(v);
	for(int i=0;i<v;i++)
	{
		vector<int> tt;
		routes[i]=tt;
	}

	//multimap<double,vector<double>>::iterator ptr = mp.end(); 


	vector<multimap<double,vector<int>>::iterator> routeNumber;

	for (int i = 0; i <= dimension; i++)
	{
		routeNumber.push_back(mp.end());
	}
	int currentRoute = 0;
cout<<"\n Intial maps is";printMap(mp);
	for (auto itr = savings.begin(); itr != savings.end(); itr++)
	{

		SavingsNode node = *itr;

		mpitr routei = routeNumber[node.i];

		mpitr routej = routeNumber[node.j];
		cout << " \nProcessing Saving node " << endl;
		cout << " :" << node.i;
		cout << " :" << node.j;
		cout << " :" << node.savings;
		int yy;

		if (routei == mp.end() && routej == mp.end())
		{
///		cout << "\n Both are not in any route so add in enw route ";
cout<<"\n here 1";
//cin>>yy;
			vector<int> route;
			route.push_back(0);
			route.push_back(node.i);
			route.push_back(node.j);
			route.push_back(0);
			int capacityOfRoute = getRouteCapacity(demand, route);
			mpitr ptr=mp.lower_bound(capacityOfRoute);
			
            for(auto itr=ptr;itr!=mp.end();itr++)
			{

				vector<int> vehicleRoute=(itr)->second;
				if(vehicleRoute.size()==0)
				{
				vehicleRoute=route;
				itr->second=vehicleRoute;
				//routes[currentRoute] = route;
				routeNumber[node.i] = itr;
				routeNumber[node.j] = itr;
				//currentRoute++;
				

					break;
				}
			}

			/*if (capacityOfRoute <= capacity)
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
			}*/
		}
		else if (routei == mp.end() || routej == mp.end())
		{
			cout<<"\n here 2";
//cin>>yy;

//			cout << "\n At least one of them is laready there and other is not ";
			if (routei == mp.end())
			{
//				cout << " hello 1";
//				cout << " " << routei << " is not there ";
				vector<int> routeOfJ = routeNumber[node.j]->second;
				if (routeOfJ[1] == node.j)
				{
//					cout << " \n and " << routej << " is extreme ";
//					cout << " \n current route of j is ";
//	printRoute(routes[routej]);
					//routeOfJ.push_front(node.i);


					double newCapacity=getRouteCapacity(demand, routeOfJ)+ (demand[node.i]);
			    	mpitr ptr=mp.lower_bound(newCapacity);
						cout<<"\n new req capacity is "<<newCapacity;
				cout<<"\n best retreived is "<<ptr->first;
            
                   for(auto itr=ptr;itr!=mp.end();itr++)
				{

					vector<int> vehicleRoute=(itr)->second;
				if(vehicleRoute.size()==0)
				{





					routeNumber[node.j]->second.clear();		
					routeOfJ.insert(routeOfJ.begin(),node.i);
					routeOfJ[0] = 0;
					routeOfJ[1] = node.i;
					//int rnumber = routeNumber[node.j];
					//routes[rnumber] = routeOfJ;
					//routeNumber[node.j] = itr;
					//routeNumber[node.i] = itr;
					itr->second=routeOfJ;
					for(auto y=routeOfJ.begin();y!=routeOfJ.end();y++)
					{
						routeNumber[*y]=itr;
					}
					break;
//				
				

				}
				}


				/*	routeOfJ.insert(routeOfJ.begin(),node.i);
					routeOfJ[0] = 0;
					routeOfJ[1] = node.i;
					int rnumber = routeNumber[node.j];
					routes[rnumber] = routeOfJ;
					routeNumber[node.j] = rnumber;
					routeNumber[node.i] = rnumber;
//					cout << " \n new route of merge with j ";*/
//					printRoute(routes[routej]);
					//        cin>>yy;
					//printRouteCodes(dimension, routeNumber);
				}
				else if ((routeOfJ[routeOfJ.size() - 1 - 1] == node.j))
				{
					cout<<"\n here 3";
//cin>>yy;

//					cout << " hello 2";
//					cout << " " << routei << " is not there ";
//					cout << " \n and " << routej << " is extreme ";
//					cout << " \n current route of j is ";
//					printRoute(routes[routej]);


					double updatedCapacity= demand[node.i] + getRouteCapacity(demand, routeOfJ);

					mpitr ptr=mp.lower_bound(updatedCapacity);
						cout<<"\n 1. new req capacity is "<<updatedCapacity;
				cout<<"\n best retreived is "<<ptr->first;
            
                   for(auto itr=ptr;itr!=mp.end();itr++)
				{

					vector<int> vehicleRoute=(itr)->second;
				if(vehicleRoute.size()==0)
				{   
					routeNumber[node.j]->second.clear();		

					routeOfJ.push_back(node.i);
					//routeOfJ.insert(routeOfJ.begin(),node.i);
					routeOfJ[routeOfJ.size() - 1] = 0;
					routeOfJ[routeOfJ.size() - 2] = node.i;
				//	int rnumber = routeNumber[node.j];
				//	routes[rnumber] = routeOfJ;
					//routeNumber[node.j] = itr;
					//routeNumber[node.i] = itr;
					itr->second=routeOfJ;
for(auto y=routeOfJ.begin();y!=routeOfJ.end();y++)
					{
						routeNumber[*y]=itr;
					}
					break;
				}	
				}
					/*routeOfJ.push_back(node.i);
					//routeOfJ.insert(routeOfJ.begin(),node.i);
					routeOfJ[routeOfJ.size() - 1] = 0;
					routeOfJ[routeOfJ.size() - 2] = node.i;
					int rnumber = routeNumber[node.j];
					routes[rnumber] = routeOfJ;
					routeNumber[node.j] = rnumber;
					routeNumber[node.i] = rnumber;
*/
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
cout<<"\n here 4";
//cin>>yy;

				vector<int> routeOfi = routeNumber[node.i]->second;
				cout<<"\n szie of routefi is"<<routeOfi.size();
				cout<<"\n and route is ";
				for(auto g=routeOfi.begin();g!=routeOfi.end();g++)
				{
					cout<<" "<<*g;
					cout<<endl;
				}
				if (routeOfi[1] == node.i)
				{
//					cout << " hello 4";
//					cout << " " << routej << " is not there ";
//					cout << " \n and " << routei << " is extreme ";
//					cout << " \n current route of i is ";
//					printRoute(routes[routei]);
					//routeOfi.push_front(node.j);
					double newCapacity= demand[node.j] + getRouteCapacity(demand, routeOfi);
				mpitr ptr=mp.lower_bound(newCapacity);
				cout<<"\n2. new req capacity is "<<newCapacity;
				cout<<"\n best retreived is "<<ptr->first;
                   for(auto itr=ptr;itr!=mp.end();itr++)
				{

					vector<int> vehicleRoute=(itr)->second;
				if(vehicleRoute.size()==0)
				{

				   routeNumber[node.i]->second.clear();				

					routeOfi.insert(routeOfi.begin(),node.j);
					routeOfi[0] = 0;
					routeOfi[1] = node.j;
					//int rnumber = routeNumber[node.i];
					//routes[rnumber] = routeOfi;
				//	routeNumber[node.j] = itr;
				//	routeNumber[node.i] = itr;
					cout<<"\n updated route for "<<node.j<<" and "<<node.i;
					itr->second=routeOfi;					

					for(auto y=routeOfi.begin();y!=routeOfi.end();y++)
					{
						routeNumber[*y]=itr;
					}

					break;					
				}
				}



				/*	routeOfi.insert(routeOfi.begin(),node.j);
					routeOfi[0] = 0;
					routeOfi[1] = node.j;
					int rnumber = routeNumber[node.i];
					routes[rnumber] = routeOfi;
					routeNumber[node.j] = rnumber;
					routeNumber[node.i] = rnumber;*/
//					cout << " \n new route of merge with i ";
//					printRoute(routes[routei]);
//					printRouteCodes(dimension, routeNumber);
					//    cin>>yy;
				}

				else if ((routeOfi[routeOfi.size() - 1 - 1] == node.i) )
				{
					cout<<"\n here 5";
//cin>>yy;

//					cout << " hello 5";
//					cout << " " << routej << " is not there ";
//					cout << " \n and " << routei << " is extreme ";
//					cout << " \n current route of i is ";
//					printRoute(routes[routei]);


		            double newCapacity= demand[node.j] + getRouteCapacity(demand, routeOfi);

					cout<<"\n check hee new capacity "<<newCapacity;
				//	double newCapacity= demand[node.j] + getRouteCapacity(demand, routeOfi);
				mpitr ptr=mp.lower_bound(newCapacity);
                   for(auto itr=ptr;itr!=mp.end();itr++)
				{

					vector<int> vehicleRoute=(itr)->second;
				if(vehicleRoute.size()==0)
				{
					
					routeNumber[node.i]->second.clear();				
	
					routeOfi.push_back(node.j);
					routeOfi[routeOfi.size() - 1] = 0;
					routeOfi[routeOfi.size() - 2] = node.j;
					//int rnumber = routeNumber[node.i];
					//routes[rnumber] = routeOfi;
					//routeNumber[node.j] = itr;
					//routeNumber[node.i] = itr;
					itr->second=routeOfi;
					for(auto y=routeOfi.begin();y!=routeOfi.end();y++)
					{
						routeNumber[*y]=itr;
					}
					break;
				}
				}
//					cout << " \n new route of merge with i ";
//					printRoute(routes[routei]);
//					printRouteCodes(dimension, routeNumber);
					// 		        cin>>yy;
				}
			}
		}

		else if (std::distance(mp.begin(),routei) != std::distance(mp.begin(),routej))
		{
//			cout << " hello 6";
cout<<"\n route i is capacity "<<routej->first<<" amd dis is "<<std::distance(mp.begin(),routei)<<" and itr is " ;
cout<<"\n route j is capacity "<<routej->first<<" and dis is "<<std::distance(mp.begin(),routej)<<" and itr is ";
cout<<"\n here 6";
//cin>>yy;

			vector<int> routeOfi = routei->second;
			vector<int> routeOfj = routej->second;
			//cin>>yy;
			cout<<" yes done 1";
			//printRoute(routeOfi);

			cout<<" \n size of i is "<<routeOfi.size();
			for(auto o=routeOfi.begin();o!=routeOfi.end();o++)
			{
				cout<<"\t"<<*o;
			}
			//cin>>yy;
			cout<<" yes done 2";
			cout<<" \n size of i is "<<routeOfj.size();
			cout<<endl;
			//cin>>yy;
			cout<<" yes done 3";
			//printRoute(routeOfj);
			cout<<" \n size of j is "<<routeOfj.size();
			for(auto o=routeOfj.begin();o!=routeOfj.end();o++)
			{
				cout<<"\t"<<*o;
			}
			//cin>>yy;
			
			cout<<" here too";
			//cin>>yy;
			if (routeOfi[1] == node.i && routeOfj[routeOfj.size() - 2] == node.j ) 
			

			{
//				cout << " \nyes 1 caught";
//				cout << "\n before merge ";
//				printRoute(routeOfi);
//				printRoute(routeOfj);

			    double newCapacity=getRouteCapacity(demand, routeOfi) + getRouteCapacity(demand, routeOfj);
				mpitr ptr=mp.lower_bound(newCapacity);
                   for(auto itr=ptr;itr!=mp.end();itr++)
				{

					vector<int> vehicleRoute=(itr)->second;
				if(vehicleRoute.size()==0)
				{
					
				routei->second.clear();
				routej->second.clear();
					routeOfj.pop_back();
				//routeOfj.pop_back();
				//routeOfi.pop_front();
				routeOfi.erase(routeOfi.begin());
				for (auto itr = routeOfi.begin(); itr != routeOfi.end(); itr++)
				{
					routeOfj.push_back(*itr);
					routeNumber[*itr] = routej;
				}
				//int rnumber = routeNumber[node.j];
				//routes[rnumber] = routeOfj;
				//routeNumber[node.j] = itr;
				//routeNumber[node.i] = itr;
				//routes[routei].clear();
				itr->second=routeOfj;
for(auto y=routeOfj.begin();y!=routeOfj.end();y++)
					{
						routeNumber[*y]=itr;
					}
				
					break;
				}
				}

/*				routeOfj.pop_back();
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
				routes[routei].clear();*/

//				cout << " \n after merge in j";
//				printRoute(routeOfj);
//				printRouteCodes(dimension, routeNumber);

				// cin>>yy;
			}

			else if (routeOfi[routeOfi.size() - 2] == node.i && routeOfj[1] == node.j )
			 

			{
//				cout << " hello 7";
//				cout << " \nyes 1 caught";
//				cout << "\n before merge ";
				//cout<<" \n capcity of following route is "<<getRouteCapacity
//				printRoute(routeOfi);
//				printRoute(routeOfj);
				//routeOfi.pop_back();
				//routeOfj.pop_front();
				cout<<"\n here 7";
//cin>>yy;

				double newCapacity=getRouteCapacity(demand, routeOfi) + getRouteCapacity(demand, routeOfj);
				mpitr ptr=mp.lower_bound(newCapacity);
                   for(auto itr=ptr;itr!=mp.end();itr++)
				{

					vector<int> vehicleRoute=(itr)->second;
				if(vehicleRoute.size()==0)
				{
					routei->second.clear();
				routej->second.clear();
				
					routeOfi.pop_back();
				routeOfj.erase(routeOfj.begin());
				
				for (auto itr = routeOfj.begin(); itr != routeOfj.end(); itr++)
				{
					routeOfi.push_back(*itr);
					routeNumber[*itr] = routei;
				}
			//	int rnumber = routeNumber[node.i];
			//	routes[rnumber] = routeOfi;
			//	routeNumber[node.j] = itr;
			//	routeNumber[node.i] = itr;
			//	routes[routej].clear();
			itr->second=routeOfi;
for(auto y=routeOfi.begin();y!=routeOfi.end();y++)
					{
						routeNumber[*y]=itr;
					}
				break;
				}
				}
/*				routeOfi.pop_back();
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
*/
//				cout << " \n after merge in i";
//				printRoute(routeOfi);
//				printRouteCodes(dimension, routeNumber);
				//cin>>yy;
			}
		}

		cout<<"\n Now map is ";printMap(mp);
		//cin>>yy;
	}
//cout<<"hello 10";

cout<<"\n as of noew see routes :";
for(auto itr=mp.begin();itr!=mp.end();itr++)
{
	cout<<" \n details for route : "<<itr->first;
	if(itr->second.size()>0)
	{

		for(auto ptr=itr->second.begin();ptr!=itr->second.end();ptr++)
		{
			cout<<"\n "<<*ptr;

		}
	}
	else
	{
		cout<<"\n alas !! empty";
	}
	

}
mpitr p=mp.begin();
while(p->second.size()>0 && p!=mp.end())
p++;

for(int i=1;i<dimension;i++)
{
	cout<<"\n running for "<<i;
	
	if(p==mp.end())
	break;

	if(routeNumber[i]==mp.end())
	{
		cout<<"\n it is not assigned";
		if(p->second.size()==0)
		{
		cout<<" not assigned "<<i;
		vector<int> route;
		route.push_back(0);
		route.push_back(i);
		route.push_back(0);
		routeNumber[i]=p;
		p->second=route;
		while(p->second.size()>0 && p!=mp.end())
		p++;
		}

	}
}
multimap<double,bool> occupied;
for (auto itr = vehicleCapacity.begin(); itr != vehicleCapacity .end(); itr++)
	{
		
        occupied.insert(pair <double, bool> (*itr,false)); 

	}
	cout<<"\n done!!!!";
	int yy;
//	cin>>yy;

//routes.clear();
cout<<"\n routes size here si "<<routes.size();
printMap(mp);
for (auto it = vehicleCapacity.begin(); it != vehicleCapacity .end(); it++)
	{
		int dist=distance(vehicleCapacity.begin(),it);
		cout<<"\n dist running "<<dist;
		double cap=*it;
				cout<<"\n searching for "<<cap;

		mpitr a=mp.find(cap);
		cout<<"\n done";
		if(a==mp.end())
		{
		cout<<"\n error";
	//	cin>>yy;
		}
		else
		{
			cout<<" \n search success fotr "<<cap;
		//	cin>>yy;
		}
		while(a->second.size()==0 && a->first==cap)
		{
			cout<<"\n enter";
		a++;
		}
		if(a->first!=cap)
		a--;
		cout<<" hjere";
	//	cin>>yy;

		routes[dist]=a->second;
		cout<<" here 2";
		//cin>>yy;
		a->second.clear();


		cout<<"\n curretn set of routes is :";
		for(int i=0;i<v;i++)
		{
			cout<<endl;
			cout<<" Capacity : "<<vehicleCapacity[i]<<" ";
			for(auto pp=routes[i].begin();pp!=routes[i].end();pp++)
			cout<<"\t"<<*pp;
		}
		cout<<"\n current actual is ";
		printMap(mp);

	}

cout<<"\n abov is succes";


	//}

	cout << "\n Now printing routes ";
	vector<vector<int>> finalResult;
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
		finalResult.push_back(cr);
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
		

		vector<vector<double>> tspInput=input.convertRouteToCordinateList(tempRoute);
		TSPSolver tsp(tspInput,depotLocation);
		 cout<<"\n now we have created instacen of TSP successuflly here";
	
		for(auto itr=tempRoute.begin();itr!=tempRoute.end();itr++)
		capacityHandled=capacityHandled+demand[*itr];
		
		cout<<" Calling TSP now";
	    vector<vector<double>> tspOutput=tsp.solveTSP();
		cout<<" Called TSP now";
		vector<int> optimizedRoute=input.convertCordinateListToRoute(tspOutput);
		optimizedRoute.push_back(0);
		optimizedRoute.insert(optimizedRoute.begin(),0);
		
	//cout<<" optimized route after tsp is ";
	//	printRoute(optimizedRoute);
		cout<<" \nCapacity this route:- "<<capacityHandled<<"\n";
		
		cout<<" \nCost of this route:- "<<calculateRouteCost(optimizedRoute, distanceTable)<<"\n";
		optimiZedtotal += calculateRouteCost(optimizedRoute, distanceTable);
		calculateRouteCost	(optimizedRoute, distanceTable);
	printRoute(optimizedRoute);
	finalResult.push_back(optimizedRoute);

	
	}
convertResultToJson(finalResult,input);

	//printRouteCodes(dimension, routeNumber);
	//cout << "\n Total cost of the route is " << total;
	cout << "\n Total opt cost of the route is: " << optimiZedtotal;
	cout<<"\n Total vechicles used: "<<countOfRoutes;
	cout<<"\n size of cordinates are "<<customerCordinates.size();
	cout<<"\n size of demand are "<<demand.size();

}
