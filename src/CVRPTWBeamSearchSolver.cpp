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

struct NodeDetails
{
    vector<int> visited;
    vector<int> notVisited;
    float dist;

};
vector<int> beamSearch(vector<int> route,int beamWidth);

vector<vector<int>> Kmeans(vector<vector<float>> nodeList, int k, vector<int> demand, int maxCapacity);
double getDistanceBetweenTwoNodes(vector<float> x, vector<float> y)
{
    float dx = x[0] - y[0];
    float dy = x[1] - y[1];
    double distance = sqrt(pow(dx, 2) + pow(dy, 2));
    return distance;
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

int main(int argc, char *argv[])
{
       
    CVRPTW cvrptw = readFileWithTimeWindows("c101");
    printf("\n File read successfully");
    cvrptw.printCVRPInstance();
    //return 0;

    cout << " \n Reading File:-" << argv[1] << endl;
    vector<vector<int>> data = readFile(argv[1]);
    CVRPInput input = CVRPInput(data);
    vector<CVRPVehicleOutput> output;
    int dimension = cvrptw.getNumberOfNodes(); //.getDimension();
    int capacity = cvrptw.getmaximumCapacity();
    vector<CVRPTWNode> nodeList = cvrptw.getNodeList();
    vector<int> demand;
    for (int i = 0; i <= dimension; i++)
        demand.push_back(nodeList[i].getNodeDemand());

    vector<vector<float>> customerCordinates;
    for (int i = 1; i <= dimension; i++)
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

    for (int i = 1; i <= dimension; i++)
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
            float time = 0;
            vector<int> route;
            time = nodeList[0].getNodeBeginTime() + nodeList[0].getNodeServiceTime();
            time = time + distanceTable[0][node.i];
            if (nodeList[node.i].getNodeBeginTime() >= time)
                time = time + nodeList[node.i].getNodeServiceTime();
            time = time + distanceTable[node.i][node.j];

            if (nodeList[node.j].getNodeBeginTime() >= time)
                time = time + nodeList[node.i].getNodeServiceTime();

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
                    routeOfJ.insert(routeOfJ.begin(), node.i);
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
                    routeOfi.insert(routeOfi.begin(), node.j);
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

            else if (routeOfi[routeOfi.size() - 2] == node.i && routeOfj[1] == node.j && (getRouteCapacity(demand, routeOfi) + getRouteCapacity(demand, routeOfj)) <= capacity)

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
    for (int i = 1; i < dimension; i++)
    {

        if (routeNumber[i] == -1)
        {

            vector<int> route;
            route.push_back(0);
            route.push_back(i);
            route.push_back(0);
            routes[currentRoute] = route;
            currentRoute++;
        }
    }
    cout << "\n Now printing routes ";
    cout << endl;
    double total = 0;
    double optimiZedtotal = 0;
    int rr = 0;
    //cout<<"hello";
    int countOfRoutes = 0;

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
        vector<int> tempRoute(cr.begin(), cr.end());

        cout << " \nCapacity this route:- " << getRouteCapacity(demand, tempRoute);

        cout << " \nCost of this route:- " << calculateRouteCost(tempRoute, distanceTable) << "\n";
    }

    cout << "\n Total opt cost of the route is: " << optimiZedtotal;
    cout << "\n Total vechicles used: " << countOfRoutes;

 cout << "\n Total Number of routes found are :-" << countOfRoutes;

    int maxRoutes =countOfRoutes;


    cout<<"\n Now rnning k means....";
   vector<vector<int>> result= Kmeans(customerCordinates, maxRoutes, demand, capacity);
    cout<<"\n Result of K means is :-";
    for(int i=0;i<result.size();i++)
    {
        cout<<endl;
        result[i].insert(result[i].begin(),0);
        result[i].push_back(0);
      
        printRoute(result[i]);
         cout<<"\n Capacity of route is "<<getRouteCapacity(demand,result[i]);
    }

    //Result contains k means solution
     
}

// implementation of k means
vector<vector<int>> Kmeans(vector<vector<float>> nodeList, int k, vector<int> demand, int maxCapacity)
{
    srand(time(0)); // set seed
    vector<vector<float>> meanList;
    int totalSize = nodeList.size();
    std::vector<int>::iterator it;
    vector<int> currentAssignment;
    vector<int> tempAssignment;
    for (int i = 0; i < nodeList.size(); i++)
    {
        currentAssignment.push_back(-1);
        tempAssignment.push_back(-1);
    }
    vector<vector<int>> final_routes;
    
    bool found = false;
    bool move;
    int itr=1;
    while (found == false)
    {
       
        move = true;

        // generated k random means
        int currentMeanGenerated=0;
        vector<int> meanLocationUsed;

        while(currentMeanGenerated<k)
        {
            int r = rand() % totalSize;
           // cout<<"\n generated "<<r;
            vector<float> mean = nodeList[r];
            it = std::find(meanLocationUsed.begin(), meanLocationUsed.end(), r);
            if (it == meanLocationUsed.end())
            {
                meanList.push_back(mean);
                meanLocationUsed.push_back(r);
                currentMeanGenerated++;
            }
        }

        //initialize the current assignment
        for (int i = 0; i < nodeList.size(); i++)
        {
            double cur_distance = FLT_MAX;
            for (int j = 0; j < meanList.size(); j++)
            {
                double newDistance = getDistanceBetweenTwoNodes(meanList[j], nodeList[i]);
                if (newDistance < cur_distance)
                {
                    cur_distance=newDistance;
                    currentAssignment[i] = j;
                }
            }
        }
        cout<<"\n Details of Before Iteration1 :-";
        cout<<"\n Means are: ";
        for(int i=0;i<k;i++)
        {
            cout<<"\n";
            cout<<""<<meanList[i][0]<<" "<<meanList[i][1];
        }
        cout<<"\n Current assignment are :";
        for(int i=0;i<nodeList.size();i++)
        {
            cout<<" "<<currentAssignment[i];
        }
        int move1=1;
        while (move == true)
        {
            cout<<"\n running move itr"<<move1;
            
            vector<vector<float>> newMeanList;
            vector<float> sumx;
            vector<int> countx;
            vector<float> sumy;
            vector<int> county;
            for (int i = 0; i < k; i++)
            {
                sumx.push_back(0);
                sumy.push_back(0);
                countx.push_back(0);
                county.push_back(0);
            }
            for (int i = 0; i < nodeList.size(); i++)
            {
                int currentCluster = currentAssignment[i];
                sumx[currentCluster] += nodeList[i][0];
                sumy[currentCluster] += nodeList[i][1];
                countx[currentCluster] += 1;
                county[currentCluster] += 1;
            }
            cout<<"\n Move and other calcaultion are don";
            for (int i = 0; i < k; i++)
            {
                vector<float> res;
                float temp = sumx[i] / countx[i];
                res.push_back(temp);
                temp = sumy[i] / county[i];
                res.push_back(temp);

                newMeanList.push_back(res);
            }
            cout<<"\n sums rae calcaulated";
            bool movement = false;
            cout<<"\n size is "<<nodeList.size();
            meanList.clear();
            meanList=newMeanList;
            for (int i = 0; i < nodeList.size(); i++)
            {
              //  cout<<"\n making new assignment for node "<<i;
                double cur_distance = FLT_MAX;

                for (int j = 0; j < meanList.size(); j++)
                {
                   // cur_distance = FLT_MAX;
                    double newDistance = getDistanceBetweenTwoNodes(meanList[j], nodeList[i]);
                    if (newDistance < cur_distance)
                    {
                        cur_distance=newDistance;
                        tempAssignment[i] = j;
                    }
                
                }

                      if (currentAssignment[i] != tempAssignment[i])
                    {
                        cout<<"\n yes a movement has happended";
                        movement = true;
                    }
              
            }
            cout<<"\n rounf completef;";
            move1++;
            currentAssignment=tempAssignment;
            cout<<"\n prinitn updated details now:-";
            for(int i=0;i<nodeList.size();i++)
            {
                cout<<" "<<currentAssignment[i];
            }

            cout<<"\n assignment done";
            if (movement == false)
            {
                cout<<"\n making it false";
                move = false;
            }
            cout<<"\n status updated";
            if(move==true)
            cout<<"truel";
            else
            {
                cout<<"false";
            }
                
            cout<<"\n curretn set of iteration completed";    
        }

        //return final_routes;
    cout<<" came out";
            vector<vector<int>> result_routes(k);

        for (int i = 0; i < nodeList.size(); i++)
            result_routes[tempAssignment[i]].push_back(i);

        bool checkCapacity = true;
        for (int i = 0; i < k; i++)
            if ((getRouteCapacity(demand, result_routes[i])) > maxCapacity)
                checkCapacity = false;

        if (checkCapacity == true)
        {
            final_routes = result_routes;
            found = true;
        }


        meanList.clear();
        for (int i = 0; i < nodeList.size(); i++)
        {
            currentAssignment.push_back(-1);
            tempAssignment.push_back(-1);
        }

    }
    return final_routes;
}

vector<int> beamSearch(vector<int> route,int beamWidth,CVRPTW tw,
    double distanceTable[300][300])
{
    int tot=route.size()-1;
    struct NodeDetails n0,nstar;
    n0.visited.push_back(0);
    for(int i=1;i<route.size()-1;i++)
    {
        n0.notVisited.push_back(route[i]);
    }
    n0.dist=0;
    vector<struct NodeDetails>b,boff;
    b.push_back(n0);
    int l=0;
    nstar=n0;
    nstar.dist=FLT_MAX;
    while(b.size!=0)
    {
        //brach from each node

        for(auto itr=b.begin();itr!=b.end();itr++)
        {
            struct NodeDetails temp=*itr;
            int last=temp.visited[temp.visited.size()-1];

            for(auto r=temp.notVisited.begin();r!=temp.notVisited.end();r++)
            {
                    bool flag=false;
                    float cost=distanceTable[last][*r]+temp.dist;
                    if(cost<=tw.getNodeList()[*r].getNodeBeginTime())
                    {
                        cost=tw.getNodeList()[*r].getNodeBeginTime();
                        flag=true;
                    }
                    else
                    {
                        if(cost+tw.getNodeList()[*r].getNodeServiceTime<=
                        tw.getNodeList()[*r].getNodeEndTime())
                        {
                        flag=true;
                        }
                    }
                    if(flag==true)
                    {
                        std::vector<int>::iterator it; 
                        struct NodeDetails child;
                        child.visited=temp.visited;
                        child.visited.push_back(*r);
                        vector<int> not_vis(temp.notVisited.begin(),temp.notVisited.end());
                        it = std::find (not_vis.begin(), not_vis.end(),*r); 
                        not_vis.erase(it);
                        child.notVisited=not_vis;
                        child.dist=temp.dist+distanceTable[last][*r]+tw.getNodeList()[*r].getNodeServiceTime();
                        boff.push_back(child);


                    }


            }


        }
    }
}