#include "utility.h"

#include "CVRPVehicleOutput.h"

#include "CVRPInput.h"
#include "TSPSolver.h"



// A utility function to find the vertex with 
// minimum key value, from the set of vertices 
// not yet included in MST 

// Does union of i and j. It returns 
// false if i and j are already in same 
// set. 
// Find set of vertex i 
int find(int i,int parent[]) 
{ 
    while (parent[i] != i) 
        i = parent[i]; 
    return i; 
} 

 void take_union(int i, int j,int parent[]) 
{ 
    int a = find(i,parent); 
    int b = find(j,parent); 
    parent[a] = b; 
}

  vector<float> getCentroid(vector<vector<int>> route);

vector<int> generateTSPApproxRoute(vector<int> r,CVRPInput i,double distanceTable[300][300]);

double get_Distance(vector<int> x,vector<int> y)
{
          
            int px = x[0];
            int py = x[1];
            int dx = y[0];
            int dy = y[1];
            int a = px - dx;
            int b = py - dy;
            double distance = sqrt(pow(a, 2) + pow(b, 2));
            return distance;
}



struct Node
{
    int data;
    struct Node *next;
};
void runDFSPreorder(struct Node * child[],int root,int visited[],int *result,int *i)
{
    struct Node *current=child[root];
    if(visited[root]==0)
    {
        cout<<" "<<root;
        result[*i]=root;
        (*i)=(*i)+1;
        visited[root]=1;
    }
    while(current!=NULL)
    {
        if(visited[current->data]==0)
        runDFSPreorder(child,current->data,visited,result,i);
        current=current->next;
    }

}
// A utility function to print the 
// constructed MST stored in parent[] 
int printMST(int parent[], int graph[5][5]) 
{ 
    int V=5;
	cout<<"Edge \tWeight\n"; 
	for (int i = 1; i < V; i++) 
		cout<<parent[i]<<" - "<<i<<" \t"<<graph[i][parent[i]]<<" \n"; 

    struct Node *child[V];
    for(int i=0;i<V;i++)
    {
        struct Node *temp = NULL;
        child[i]=temp;
    }

    for (int i = 1; i < V; i++) 
    {
        struct Node * front=child[parent[i]];
        struct Node *temp = 
        (struct Node*)malloc(sizeof(struct Node));
        temp->next=front;
        temp->data=i;
        child[parent[i]]=temp;



 struct Node * front1=child[i];
        struct Node *temp1 = (struct Node*)malloc(sizeof(struct Node));
        temp1->next=front1;
        temp1->data=parent[i];
        child[i]=temp1;



        
		
    }

    cout<<"\n printing the adjaceny details";
    for(int i=0;i<V;i++)
    {   cout<< "\n Printing for"<<i<<" : ";
        struct Node *head=child[i];
        while(head!=NULL)
        {
            cout<<" "<<head->data;
            head=head->next;
        }

        cout<<endl;
    }

int visited[V];
for(int i=0;i<V;i++)
{
    visited[i]=0;
}
//runDFSPreorder(child,0,visited);

} 

// Function to construct and print MST for 
// a graph represented using adjacency 
// matrix representation 
/* void primMST(int graph[V][V]) 
{ 
	// Array to store constructed MST 
	int parent[V]; 
	
	// Key values used to pick minimum weight edge in cut 
	int key[V]; 
	
	// To represent set of vertices not yet included in MST 
	bool mstSet[V]; 

	// Initialize all keys as INFINITE 
	for (int i = 0; i < V; i++) 
		key[i] = INT_MAX, mstSet[i] = false; 

	// Always include first 1st vertex in MST. 
	// Make key 0 so that this vertex is picked as first vertex. 
	key[0] = 0; 
	parent[0] = -1; // First node is always root of MST 

	// The MST will have V vertices 
	for (int count = 0; count < V - 1; count++) 
	{ 
		// Pick the minimum key vertex from the 
		// set of vertices not yet included in MST 
		int u = minKey(key, mstSet); 

		// Add the picked vertex to the MST Set 
		mstSet[u] = true; 

		// Update key value and parent index of 
		// the adjacent vertices of the picked vertex. 
		// Consider only those vertices which are not 
		// yet included in MST 
		for (int v = 0; v < V; v++) 

			// graph[u][v] is non zero only for adjacent vertices of m 
			// mstSet[v] is false for vertices not yet included in MST 
			// Update the key only if graph[u][v] is smaller than key[v] 
			if (graph[u][v] && mstSet[v] == false && graph[u][v] < key[v]) 
				parent[v] = u, key[v] = graph[u][v]; 
	} 

	// print the constructed MST 
	printMST(parent, graph); 
} 
*/



/*************************************
Filename :- CRVPClarkeWriteSolver.cpp
Author :- Bateesh Dhingra
Date :- 15th Jul 2019
Description :- Solving CVRP using clark and wright savings algorithms
***********************************/

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
		int yy;

		if (routei == -1 && routej == -1)
		{
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
				vector<int> routeOfi = routes[routeNumber[node.i]];
				if (routeOfi[1] == node.i && demand[node.j] + getRouteCapacity(demand, 
                routeOfi) <= capacity)
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
//			cout << " hello 6";

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
				cout<<"\n Earlier route with cost"<<calculateRouteCost(routeOfj,distanceTable)<<":-";
				printRoute(routeOfj);
				vector<int> temp_route=generateTSPApproxRoute(routeOfj,input,distanceTable);
				if(calculateRouteCost(routeOfj,distanceTable)>calculateRouteCost(temp_route,distanceTable))
				{
                routeOfj=temp_route;
				cout<<"\n updated route with cost"<<calculateRouteCost(routeOfj,distanceTable)<<":-";
				printRoute(routeOfj);
				}

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


				cout<<"\n Earlier route with cost"<<calculateRouteCost(routeOfi,distanceTable)<<":-";
				printRoute(routeOfi);
				vector<int> temp_route1=generateTSPApproxRoute(routeOfi,input,distanceTable);
				if(calculateRouteCost(routeOfi,distanceTable)>calculateRouteCost(temp_route1,distanceTable))
				{
                routeOfi=temp_route1;
				cout<<"\n updated route with cost"<<calculateRouteCost(routeOfi,distanceTable)<<":-";
				printRoute(routeOfi);
				}

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









cout<<"\n Optimizing routes now:-";
vector<vector<int>> centroidRoutes;
vector<vector<float>> gc;
// get centroid of all routes
for(auto itr=routes.begin();itr!=routes.end();itr++)
{

vector<int> r=*itr;
if(r.size()==0)
continue;
vector<float> result=getCentroid(input.convertRouteToCordinateList(r));
gc.push_back(result);
centroidRoutes.push_back(r);
}
for(int i = 0;i<gc.size();i++)
for(int vk=1;vk<centroidRoutes[i].size()-1;vk++)
for(int j = 0;j<gc.size();j++)
{
    if(i!=j)
    {
        int nodeNumber=centroidRoutes[i][vk];
        vector<int> data=customerCordinates[nodeNumber-1];
        int px=data[0];
        int py=data[1];
        vector<float> g1=gc[i];
        vector<float> g2=gc[j];
        float d1=sqrt(pow( (px-g1[0]) , 2) + pow((py-g1[1]), 2));
        float d2=sqrt(pow( (px-g2[0]) , 2) + pow((py-g2[1]), 2));
        if(d2<d1 && getRouteCapacity(demand,centroidRoutes[j])+demand[nodeNumber]<capacity)
        {
            centroidRoutes[j].pop_back();
            centroidRoutes[j].push_back(nodeNumber);
            centroidRoutes[j].push_back(0);
            cout<<" \n Yes.Centroid movement done!!!!";
        }
        
        gc[i]=getCentroid(input.convertRouteToCordinateList(centroidRoutes[i]));
        gc[j]=getCentroid(input.convertRouteToCordinateList(centroidRoutes[j]));
    }
    
}

routes.clear();
routes=centroidRoutes;




















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
		cout<<" \n Route is:-";
		printRoute(optimizedRoute);
		cout<<endl;
	
	}

	//printRouteCodes(dimension, routeNumber);
	//cout << "\n Total cost of the route is " << total;
	cout << "\n Total opt cost of the route is: " << optimiZedtotal;
	cout<<"\n Total vechicles used: "<<countOfRoutes;

}

 vector<int> generateTSPApproxRoute(vector<int> route,CVRPInput input,double distanceTable[300][300])
{ 
cout<<"\n called:";
cout<<endl;
cout<<" \n pre.v COst of the tour is "<<calculateRouteCost(route,distanceTable);
cout<<endl;
route.pop_back();
//string str=
cout<<"\n i ma giving input to k-tsp now:-";
ofstream myfile;
myfile.open ("/home/bateesh/Documents/PastWork/Jithin_Constrained_routing_and_TOPTW-master-4807b847e089524eb2f9e67974891de1288c596b/kpersontsp/input_1");
 unordered_map<int,int> umap; 
       int cc=0;
for(auto itr=route.begin();itr!=route.end();itr++)
{
    cout<<" "<<*itr;
    umap[cc]=*itr;
    cc++;
}
    

int v=route.size();
int count =0;
vector<vector<int>> tspInput=input.convertRouteToCordinateList(route);
cout<<" \n let us check";
for(auto itr=tspInput.begin();itr!=tspInput.end();itr++)
{   vector<int> c=*itr;
    cout<<count<<" "<<c[0]<<" "<<c[1];
    myfile<<count<<" "<<c[0]<<" "<<c[1];
    cout<<endl;
    myfile<<endl;
    count++;

}
myfile.close();
system("/home/bateesh/Documents/PastWork/Jithin_Constrained_routing_and_TOPTW-master-4807b847e089524eb2f9e67974891de1288c596b/kpersontsp/bin/tsp /home/bateesh/Documents/PastWork/Jithin_Constrained_routing_and_TOPTW-master-4807b847e089524eb2f9e67974891de1288c596b/kpersontsp/input_1 1");
cout<<"\n now TSP is done ...let us see output...";						  
cout<<"\n";

  cout<<" Now readinf file";
  ifstream file("result.txt");
  	cout<<" opened file";

 
    string line;
 
    getline(file, line);
    vector < int > p = extract_ints(line);
    cout<<"\n size of ret. data is\n...\n "<<p.size()<<endl;
     for(auto itr=p.begin();itr!=p.end();itr++)
    {
cout<<*itr;
    }
   cout<<".....\n";
    cout<<" zn now i have data from the tsp";
    vector<int> tspApproxRoute;
    for(auto itr=p.begin();itr!=p.end();itr++)
    {
        tspApproxRoute.push_back(umap[*itr]);

    }
    cout<<"\n now see the output route\n";
    for(auto itr=tspApproxRoute.begin();itr!=tspApproxRoute.end();itr++)
    {
cout<<" "<<*itr;
    }
    cout<<" TSP Approx route generated successfully..";
  //getline(file, line);
  cout<<"\n cost od this route is : "<<calculateRouteCost(tspApproxRoute,distanceTable);
return tspApproxRoute;

	/* float cost[v][v] ;
    for(int i=0;i<v;i++)
    for(int j=0;j<v;j++)
    {
     cost[i][j]=get_Distance(tspInput[i],tspInput[j]);
 		
    }

  struct Node *child[v];
    for(int i=0;i<v;i++)
    {
        struct Node *temp = NULL;
        child[i]=temp;
    }

int mincost = 0; // Cost of min MST. 
  int parent[v];
    // Initialize sets of disjoint sets. 
    for (int i = 0; i < v; i++) 
        parent[i] = i; 
  
    // Include minimum weight edges one by one 
    int edge_count = 0; 
    while (edge_count < v - 1) { 
        int min = INT_MAX, a = -1, b = -1; 
        for (int i = 0; i < v; i++) { 
            for (int j = 0; j < v; j++) { 
                if (find(i,parent) != find(j,parent) && cost[i][j] < min) { 
                    min = cost[i][j]; 
                    a = i; 
                    b = j; 
                } 
            } 
        } 
        printf("\n hello");
       take_union(a, b,parent); 
        printf("Edge %d:(%d, %d) cost:%d \n", 
               edge_count++, a, b, min); 

               struct Node * front=child[a];
        struct Node *temp = 
        (struct Node*)malloc(sizeof(struct Node));
        temp->next=front;
        temp->data=b;
        child[a]=temp;



 struct Node * front1=child[b];
        struct Node *temp1 = (struct Node*)malloc(sizeof(struct Node));
        temp1->next=front1;
        temp1->data=a;
        child[b]=temp1;





               
        mincost += min; 
    } 
    printf("\n Minimum cost= %d \n", mincost); 
	cout<<"\n printing the adjaceny details";
    for(int i=0;i<v;i++)
    {   cout<< "\n Printing for"<<i<<" : ";
        struct Node *head=child[i];
        while(head!=NULL)
        {
            cout<<" "<<head->data;
            head=head->next;
        }

        cout<<endl;
    }

    int visited[v];
    for(int i=0;i<v;i++)
    visited[i]=0;
    int result[v+1];
    int i=0;
    printf("\n starting dfs:-");
    runDFSPreorder(child,0,visited,result,&i);
    result[v]=0;
    cout<<"\n pritning left over";
    printf("\n ending dfs:-");
    cout<<"\n Now see complete tour:-";
    for(int i=0;i<v+1;i++)
    cout<<" "<<result[i];

    //int n = sizeof(result) / sizeof(result[0]); 
  
    //vector<int> result(arr, arr + n); 
    vector<vector<int>> res;
    for(int i=0;i<v+1;i++)
{
        res.push_back(tspInput[result[i]]);
}
vector<int> optimizedRoute=input.convertCordinateListToRoute(res);
cout<<"\n otmized route:- ";
	for(int i=0;i<v+1;i++)
{
        cout<<" "<<optimizedRoute[i];
}
cout<<" \n its cost is "<<calculateRouteCost(optimizedRoute,distanceTable);	

	return optimizedRoute;// 0; */
} 

// This code is contributed by rathbhupendra 

vector<float> getCentroid(vector<vector<int>> route)
{
float xsum=0;
float ysum=0;
float xavg;
float yavg;
int count=0;
vector<vector<int>> d=route;
for(auto it=d.begin();it!=d.end();it++)
{
    vector<int> data=(*it);
    xsum+=data[0];
    ysum+=data[1];

}
vector<float> result;
xavg=xsum/d.size();
yavg=ysum/d.size();
result.push_back(xavg);
result.push_back(yavg);
return result;

}