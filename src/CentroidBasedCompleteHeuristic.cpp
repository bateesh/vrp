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
int ax;
int ay;
struct SavingsNode
{
	int i;
	int j;
	double savings;
};
struct Node
{
    int data;
    struct Node *next;
};
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


vector<double> getCentroid(vector<vector<int>> route);
bool doClusterAdjustment(vector<vector<int>> &routes,
vector<vector<double>> &centroid,vector<vector<int>> customerCordinates,CVRPInput input,vector<int> demand,int capacity);
vector<int> generateTSPApproxRoute(vector<int> route,CVRPInput input,double distanceTable[300][300]);
vector<vector<int>> run2OptHeuristic(vector<int> demand,vector<int> depotLocation,vector<vector<int>> routes,CVRPInput input,double distanceTable[300][300]);

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

bool comp(vector<int> i1, vector<int> i2)
{
	int dx=i1[0]-ax;
	int dy=i1[1]-ay;
	 double distance1 = sqrt(pow(dx, 2) + pow(dy, 2));
	 dx=i2[0]-ax;
	 dy=i2[1]-ay;
	 double distance2 = sqrt(pow(dx, 2) + pow(dy, 2));
	 return distance1>distance2;
	 
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

	int p1 = depotLocation[0];
	int p2 = depotLocation[1];
	ax=p1;
	ay=p2;
	//cout << " depot is " << p1 << " " << p2;
	vector<SavingsNode> savings;

	double distanceTable[300][300];
	//cout<<"\n anc";
	getDistanceTable(data, distanceTable);
    vector<vector<int>> t=customerCordinates;
    sort(t.begin(),t.end(),comp);
	vector<int> result=input.convertCordinateListToRoute(t);
    vector<bool> visited(dimension,false);
    int countOfAssignedNodes=0;
    vector<vector<double>> clusterNodes;
    vector<vector<int>> routes;
    int currentCapacity=0;
    int v=0;
    vector<double> clusterCentroid;
    
    while (countOfAssignedNodes<dimension-1)
    {   
        cout<<"\n A new vechile done..."<<v;
        v++;
        currentCapacity=0;
        vector<int> r;
        double a,b;    
        int itr;
        for(itr=1;itr<=dimension-1;itr++)
        {
            if(visited[itr]==false)
            {
                double a1=(double)customerCordinates[itr-1][0];
                double b1=(double)customerCordinates[itr-1][1];
                vector<double> temp;
                temp.push_back(a1);
                temp.push_back(b1);
                
                clusterNodes.push_back(temp);
                visited[itr]=true;
                r.push_back(itr);
                currentCapacity+=demand[itr];
                countOfAssignedNodes++;
        //    /     clusterCentroid.push_back(temp);
                a=customerCordinates[itr-1][0];
                b=customerCordinates[itr-1][1];
                cout<<"\nFound cluster "<<v<<" head node "<<itr<<" cor_"<<customerCordinates[itr-1][0]<<customerCordinates[itr-1][1];


                break;
            }
        }
        cout<<"\n as of now capacity is "<<currentCapacity;

        while(countOfAssignedNodes<dimension-1 && currentCapacity<capacity)
        {
            cout<<"\n finidn nearest now";
            int x=-1;

            for(int itr=1;itr<=dimension-1;itr++)
        {
            if(visited[itr]==false)
            {
                if(x==-1)
                {
                        x=itr;
                }
                else
                {
                    int dx,dy;
                    int x1=customerCordinates[x-1][0];
                    int y1=customerCordinates[x-1][1];
                    int x2=customerCordinates[itr-1][0];
                    int y2=customerCordinates[itr-1][1];
                    dx=x1-a;
                    dy=y1-b;
                    double distance1 = sqrt(pow(dx, 2) + pow(dy, 2));
                    dx=x2-a;
                    dy=y2-b;
                    double distance2 = sqrt(pow(dx, 2) + pow(dy, 2));
                    if(distance1>distance2)
                    {
                        cout<<"\n  setting to "<<x2<<" "<<y2;
                        x=itr;
                    }
                }
                
            }
        }

        cout<<" \n the nearest found is "<<x;
        if(currentCapacity+demand[x]<capacity)
        {
            r.push_back(x);
            visited[x]=true;

            currentCapacity+=demand[x];
            cout<<" \n capcity now is"<<currentCapacity;
            countOfAssignedNodes++;
            cout<<"\n nodes allocated til are "<<countOfAssignedNodes;
            vector<double> newCentroid=getCentroid(input.convertRouteToCordinateList(r));
            clusterNodes[v-1]=newCentroid;
            a=newCentroid[0];
             
        b=newCentroid[1];
        cout<<"\n updating of centroid done!!!!";
        }
        else
        {
            break;

        }
        }

routes.push_back(r);

    }

    cout<<"Initlia solution done with vehiceles as:"<<v;
    cout<<"\n now let us pritn routes:";
    float cost=0;
    for(auto itr=routes.begin();itr!=routes.end();itr++)
    {
        (*itr).insert((*itr).begin(),0);
        (*itr).push_back(0);
        vector<int> r=*itr;
        cout<<"\n cost is "<<calculateRouteCost(r, distanceTable);
        cost+=calculateRouteCost(r, distanceTable);
            cout<<"\n capacity is "<<getRouteCapacity(demand,*itr);
        cout<<"\n";

        for(auto a=r.begin();a!=r.end();a++)
            {cout<<" "<<*a;
           
            }
    }

    cout<<"\n Initial clusterring solution is costing"<<cost;

 cost=0;
    for(auto itr=routes.begin();itr!=routes.end();itr++)
    {

        vector<int> temp_route=generateTSPApproxRoute(*itr,input,distanceTable);
        if(calculateRouteCost(temp_route, distanceTable)<calculateRouteCost(*itr, distanceTable))
        {
            cout<<"\n one updation doen!!!!";
        (*itr)=temp_route;
        }
        cost+=calculateRouteCost(*itr, distanceTable);
    }


cout<<"\n Now before running 2 opt the result cost is "<<cost;
    vector<vector<int>> newRoutes=run2OptHeuristic(demand, depotLocation,routes,input,distanceTable);
    float newCost=0;
     for(auto itr=routes.begin();itr!=routes.end();itr++)
    {
                newCost+=calculateRouteCost(*itr, distanceTable);

    }

if(newCost<cost)
routes=newRoutes;
cost=0;
    for(auto itr=routes.begin();itr!=routes.end();itr++)
    {
        vector<int> r=*itr;
        cout<<"\n cost is "<<calculateRouteCost(r, distanceTable);
        cost+=calculateRouteCost(r, distanceTable);
            cout<<"\n capacity is "<<getRouteCapacity(demand,*itr);
        cout<<"\n";

        for(auto a=r.begin();a!=r.end();a++)
            {cout<<" "<<*a;
           
            }
    }

    cout<<"\n As of now the TSP iteratin has been completed...";

float minCost=cost;
vector<vector<int>> minRoutes=routes;

    for(auto itr=routes.begin();itr!=routes.end();itr++)
{
    (*itr).erase((*itr).begin());
    (*itr).pop_back();
}
bool result1= doClusterAdjustment(routes,clusterNodes,customerCordinates,input,demand,capacity);
while(result1)
{
for(auto itr=routes.begin();itr!=routes.end();itr++)
{
    (*itr).insert((*itr).begin(),0);
    (*itr).push_back(0);
}

    for(auto itr=routes.begin();itr!=routes.end();itr++)
    {

        vector<int> temp_route=generateTSPApproxRoute(*itr,input,distanceTable);
        if(calculateRouteCost(temp_route, distanceTable)<calculateRouteCost(*itr, distanceTable))
        {
            cout<<"\n one updation doen!!!!";
        (*itr)=temp_route;
        }
        cost+=calculateRouteCost(*itr, distanceTable);
    }


cout<<"\n Now before running 2 opt the result cost is "<<cost;
    vector<vector<int>> newRoutes=run2OptHeuristic(demand, depotLocation,routes,input,distanceTable);



    cost=0;
    for(auto itr=routes.begin();itr!=routes.end();itr++)
    {
        vector<int> r=*itr;
        cout<<"\n cost is "<<calculateRouteCost(r, distanceTable);
        cost+=calculateRouteCost(r, distanceTable);
            cout<<"\n capacity is "<<getRouteCapacity(demand,*itr);
        cout<<"\n";

        for(auto a=r.begin();a!=r.end();a++)
            {cout<<" "<<*a;
           
            }
    }
if(cost<minCost)
{
minCost=cost;
minRoutes=routes;
}
    for(auto itr=routes.begin();itr!=routes.end();itr++)
{
    (*itr).erase((*itr).begin());
    (*itr).pop_back();
}
result1= doClusterAdjustment(routes,clusterNodes,customerCordinates,input,demand,capacity);

cout<<"Number of routes are :-"<<routes.size();
}





cout<<"\n Hurray min COst found as :"<<minCost;

cout<<"\n Now see the final tours:-";

for(auto itr=minRoutes.begin();itr!=minRoutes.end();itr++)
{
    vector<int> r=*itr;
    cout<<"\n";
    for(int i=0;i<r.size();i++)
    cout<<" "<<r[i];
}
routes=minRoutes;


	cout << "\n Now printing routes ";
	cout << endl;
	double total = 0;
	double optimiZedtotal = 0;
	int rr = 0;
//cout<<"hello";
int countOfRoutes=0;
vector<vector<int>> first_result;

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
		first_result.push_back(optimizedRoute);
		cout<<" \nCost of this route:- "<<calculateRouteCost(optimizedRoute, distanceTable)<<"\n";
		optimiZedtotal += calculateRouteCost(optimizedRoute, distanceTable);
		calculateRouteCost	(optimizedRoute, distanceTable);

    }




cout<<"\n ONe result done succes!!!";
for(auto itr=first_result.begin();itr!=first_result.end();itr++)
{
    cout<<"\n";
    vector<int> x=*itr;
     for(auto a=x.begin();a!=x.end();a++)
     cout<<" "<<*a;
}


	int vechicleCount=first_result.size();
	cout<<"\n total vehicls"<<vechicleCount;
	  srand (time(NULL));
	int firstTour=rand()%vechicleCount;//generate random number 0 to size-1;
	int secondTour=rand()%vechicleCount;//generate random number 0 to size-1;
	int improvement=0;

	while(improvement<dimension*20)
	{

		int firstTour=rand()%vechicleCount;//generate random number 0 to size-1;
	int secondTour=rand()%vechicleCount;//generate random number 0 to size-1;
	while(secondTour==firstTour)
	{
		 secondTour=rand()%vechicleCount;
	}
	cout<<" \n selected "<<firstTour<<" "<<secondTour;
	
		int firstTourSize=first_result[firstTour].size();
		int secondTourSize=first_result[secondTour].size();
		int firstTourlocation=(rand()%(firstTourSize-2))+1;
		int secondTourlocation=(rand()%(secondTourSize-2))+1;

		cout<<"\n index in fist tour "<<firstTourlocation;
		cout<<"\n index in second tour "<<secondTourlocation;
		vector<int> temp1=first_result[firstTour];
		vector<int> temp2=first_result[secondTour];
		int k=temp1[firstTourlocation];
		temp1[firstTourlocation]=temp2[secondTourlocation];
		temp2[secondTourlocation]=k;
		cout<<"\n earlier tours";
		printRoute(first_result[firstTour]);
		cout<<" \n its cost is "<<calculateRouteCost(first_result[firstTour],distanceTable);
		cout<<endl;
		printRoute(first_result[secondTour]);
		cout<<" \n its cost is "<<calculateRouteCost(first_result[secondTour],distanceTable);
		cout<<"\n new tours";
		printRoute(temp1);
		cout<<" \n its cost is "<<calculateRouteCost(temp1,distanceTable);
		
		cout<<endl;
		printRoute(temp2);
		cout<<" \n its cost is "<<calculateRouteCost(temp2,distanceTable);
		
		if((calculateRouteCost(temp1,distanceTable)+calculateRouteCost(temp2,distanceTable))
		<(calculateRouteCost(first_result[firstTour],distanceTable)+
		calculateRouteCost(first_result[secondTour],distanceTable)))
		{

			if(getRouteCapacity(demand,temp1)<capacity && getRouteCapacity(demand,temp2)<capacity  )
			{
		first_result[firstTour]=temp1;
		first_result[secondTour]=temp2;
		improvement=0;
		cout<<"\n yes improvement found";
			}
		}
		else
		{cout<<"\n No improvement";
		cout<<" set improvment ";
			improvement++;
			cout<<improvement;
		}

	}
	
	//printRouteCodes(dimension, routerunTSNumber);
	//cout << "\n Total cost of the route is " << total;
	cout << "\n Total opt cost of the route is: " << optimiZedtotal;
	cout<<"\n Total vechicles used: "<<countOfRoutes;
cout<<"\n lets see final";
		optimiZedtotal=0;
		for(auto itr=first_result.begin();itr!=first_result.end();itr++)
		{
			vector<int> data=*itr;
			printRoute(data);
			cout<<" \n cap is"<<getRouteCapacity(demand,data);
			optimiZedtotal+=calculateRouteCost(data,distanceTable);
		}
cout << "\n Total opt cost of the route is: " << optimiZedtotal;
	cout<<"\n Total vechicles used: "<<countOfRoutes;


















    //cout<<"\n Total cost is :"<<cost;

}
vector<double> getCentroid(vector<vector<int>> route)
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
vector<double> result;
xavg=xsum/d.size();
yavg=ysum/d.size();
result.push_back(xavg);
result.push_back(yavg);
return result;

}

vector<int> generateTSPApproxRoute(vector<int> route,CVRPInput input,double distanceTable[300][300])
{ 
cout<<"\n called:";
cout<<endl;
cout<<" COst of the tour is "<<calculateRouteCost(route,distanceTable);
route.pop_back();
for(auto itr=route.begin();itr!=route.end();itr++)
{
    cout<<" "<<*itr;
}
int v=route.size();

vector<vector<int>> tspInput=input.convertRouteToCordinateList(route);

	float cost[v][v] ;
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

	return optimizedRoute;// 0; 
}

vector<vector<int>> run2OptHeuristic(vector<int> demand,vector<int> depotLocation ,vector<vector<int>> routes,CVRPInput input,double distanceTable[300][300])
{

    vector<vector<int>> optRoutes; 
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
        optRoutes.push_back(optimizedRoute);
		cout<<endl;
	
	}

	//printRouteCodes(dimension, routeNumber);
	//cout << "\n Total cost of the route is " << total;
	cout << "\n Total opt cost of the route is: " << optimiZedtotal;
	cout<<"\n Total vechicles used: "<<countOfRoutes;

    return  optRoutes;

}


bool doClusterAdjustment(vector<vector<int>> &routes,
vector<vector<double>> &centroid,vector<vector<int>> customerCordinates,CVRPInput input,vector<int> demand,int capacity)
{
    bool flag=false;
vector<vector<int>> centroidRoutes=routes;
vector<vector<double>> gc=centroid;
// get centroid of all routes
/* for(auto itr=routes.begin();itr!=routes.end();itr++)
{

vector<int> r=*itr;
if(r.size()==0)
continue;
vector<float> result=getCentroid(input.convertRouteToCordinateList(r));
gc.push_back(result);
centroidRoutes.push_back(r);
}*/
int i=0,j=0;
for(i = 0;i<gc.size();i++)
{
    cout<<" \n now running this on cluster:\n";
    printRoute(centroidRoutes[i]);
int vk=0;
while(vk<centroidRoutes[i].size())
{
    cout<<"\n checking for node "<<vk;
for( j = 0;j<gc.size();j++)
{
    if(i!=j)
    {
        int nodeNumber=centroidRoutes[i][vk];
        vector<int> data=customerCordinates[nodeNumber-1];
        int px=data[0];
        int py=data[1];
        vector<double> g1=gc[i];
        vector<double> g2=gc[j];
        double d1=sqrt(pow( (px-g1[0]) , 2) + pow((py-g1[1]), 2));
        double d2=sqrt(pow( (px-g2[0]) , 2) + pow((py-g2[1]), 2));
        if(d2<d1 && getRouteCapacity(demand,centroidRoutes[j])+demand[nodeNumber]<capacity)
        {
            cout<<" \n earlier i route is :    ";
            printRoute(centroidRoutes[i]);
            cout<<" \n earlier j route is :    ";
            printRoute(centroidRoutes[j]);
            
            cout<<" \n node "<<nodeNumber<<" from cluster "<<i <<" to "<<j;
            //centroidRoutes[j].pop_back();
            centroidRoutes[j].push_back(nodeNumber);
            //centroidRoutes[j].push_back(0);
            centroidRoutes[i][vk]=-1;
            cout<<" \n Yes.Centroid movement done!!!!";

            cout<<"\n updated route";
            cout<<" \n  i route is :    ";
            printRoute(centroidRoutes[i]);
            cout<<" \n  j route is :    ";
            printRoute(centroidRoutes[j]);
            
            flag=true;
            break;
        }
        
        gc[i]=getCentroid(input.convertRouteToCordinateList(centroidRoutes[i]));
        gc[j]=getCentroid(input.convertRouteToCordinateList(centroidRoutes[j]));
    }
    
}
    std::vector<int>::iterator it; 
     it = std::find (centroidRoutes[i].begin(), centroidRoutes[i].end(), -1); 
     if (it != centroidRoutes[i].end()) 
    {
        centroidRoutes[i].erase(it);
        cout<<"\n here bro route";
            cout<<" \n  i route is :    ";
            printRoute(centroidRoutes[i]);
            cout<<" \n  j route is :    ";
            printRoute(centroidRoutes[j]);
            
    } 
    else
        vk++;



}

}

if(flag)
{
    routes=centroidRoutes;
    centroid=gc;
}
    return flag;
}
