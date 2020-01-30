/*************************************
Filename :- CRVPClarkeWriteSolver.cpp
Author :- Bateesh Dhingra
Date :- 15th Jul 2019
Description :- Solving CVRP using clark and wright savings algorithms
***********************************/
#include "utility.h"
#include <time.h>
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
    float begin_time;
    vector<int> voilated;
    bool isFeasible;
    bool isComplete;
};
vector<int> two_opt(vector<int> route, double distanceTable[300][300], CVRPTW tw);

void printNodeDetails(struct NodeDetails a)
{
    cout << "\n Vsiited :  ";
    for (int i = 0; i < a.visited.size(); i++)
        cout << " " << a.visited[i];
    cout << "\n Note Vsiited :  ";
    for (int i = 0; i < a.notVisited.size(); i++)
        cout << " " << a.notVisited[i];
    cout << "\n Voilated Vsiited :  ";
    for (int i = 0; i < a.voilated.size(); i++)
        cout << " " << a.voilated[i];

    cout << "\n Dist :  ";
    cout << " " << a.dist;

    cout << "\n Feasible :  ";
    cout << " " << a.isFeasible;

    cout << "\n Complete :  ";
    cout << " " << a.isComplete;
}

bool sortBeamNodes(NodeDetails a, NodeDetails b)
{
    return a.begin_time < b.begin_time;
}
bool sortNodes(CVRPTWNode a, CVRPTWNode b)
{
    return a.getNodeBeginTime() < b.getNodeBeginTime();
}
struct NodeDetails beamSearch(vector<int> route, int beamWidth, CVRPTW tw,
                              double distanceTable[300][300]);

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

    clock_t t;
    t = clock();

    CVRPTW cvrptw = readFileWithTimeWindows(argv[1]);
    printf("\n File read successfully");
    cvrptw.printCVRPInstance();
    //return 0;

    //cout << " \n Reading File:-" << argv[1] << endl;
    //vector<vector<int>> data = readFile(argv[1]);
    //CVRPInput input = CVRPInput(data);
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
    // cout << endl;
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

        //   cout << endl;

        //cout << " Route " << rr << " : ";

        rr++;
        vector<int> tempRoute(cr.begin(), cr.end());

        //cout << " \nCapacity this route:- " << getRouteCapacity(demand, tempRoute);

        //cout << " \nCost of this route:- " << calculateRouteCost(tempRoute, distanceTable) << "\n";
    }

    //  cout << "\n Total opt cost of the route is: " << optimiZedtotal;
    //cout << "\n Total vechicles used: " << countOfRoutes;

    //cout << "\n Total Number of routes found are :-" << countOfRoutes;

    int maxRoutes = countOfRoutes;

    cout << "\n Now rnning k means....";
    vector<vector<int>> result = Kmeans(customerCordinates, maxRoutes, demand, capacity);
    cout << "\n Result of K means is :-";
    // int beam_width=50;
    for (int i = 0; i < result.size(); i++)
    {
        cout << endl;

        for (int j = 0; j < result[i].size(); j++)
        {
            result[i][j] += 1;
        }
        result[i].insert(result[i].begin(), 0);
        result[i].push_back(0);

        cout << endl;
        printRoute(result[i]);
        cout << "\n Capacity of route is " << getRouteCapacity(demand, result[i]);
    }

    cout << "\n********** K-Means Completed ****************************";
    cout << "\n Processing..Please wait......";
    int beam_width = 50;
    int maxItrWithoutImprovement = 0;
    double cur_cost, prev_cost, best_cost;
    best_cost = cur_cost = prev_cost = FLT_MAX;
    vector<vector<int>> bestSolution;
    for (int i = 0; i < result.size(); i++)
    {
        vector<int> t;
        bestSolution.push_back(t);
    }
    int a = 1;
    double tot_cost = 0;
    bool current_state[result.size()] = {false};
    double bestCost[result.size()] = {FLT_MAX};
    double total_voilations[result.size()] = {0};
    double beam_stable[result.size()] = {0};
    for(int i=0;i<result.size();i++)
    {
        current_state[i]=false;
        bestCost[i]=FLT_MAX;
        total_voilations[i]=0;
        beam_stable[i]=0;
    }
    int max_infeasible_itr = 5;
    int max_feasible_itr = 2;
    cout<<"\n total clusters are "<<result.size();
  //  getchar();
    vector<int> timeWindowsVoilated;
   for (int i = 0; i < result.size(); i++)
    {
        beam_width = 150;
        int cur_infeasible_itr = 0;
        int cur_feasible_itr = 0;
        cout<<"\n starting for cluster "<<i;
       // getchar();
    //    getchar();
        while (cur_feasible_itr < max_feasible_itr && cur_infeasible_itr < max_infeasible_itr)
        {

            // cout << "\n running beam width " << beam_width;
            // cout << "\n Running beam search on cluster" << i << "....";
            //getchar();
            // cout<<"\n input to beam search";
            //printRoute(result[i]);
            struct NodeDetails beamCluster = 
            beamSearch(result[i], beam_width, cvrptw, distanceTable);
            // cout<<"\n got sol is ";
            // printNodeDetails(beamCluster);
        //    getchar();
            vector<int> output = beamCluster.visited;
            vector<int> voilatiom = beamCluster.voilated;
            // cout<<"\n det:";
            //printRoute(output);
           // printRoute(voilatiom);
            if (bestCost[i] == FLT_MAX)
            {
                // cout<<" \n found initial sol";
            //    getchar();
                if (beamCluster.isFeasible == false)
                {
                    // cout<<"\n init details of inf are";
                    // cout<<"\n put put is ";
                    // printRoute(output);
                    // cout<<"\n vilated is ";
                    // printRoute(voilatiom);
                    // output.pop_back();
                    for (int j = 0; j < voilatiom.size(); j++)
                    {
                        output.push_back(voilatiom[j]);
                    }
                    output.push_back(0);
                    // cout<<"\n total is ";
                    // printRoute(output);
                     total_voilations[i] = voilatiom.size();
                    //cout<<" \n it is infeasible";
                 //   getchar();
                
                }
                else
                {
                    // cout<<"\n ini is feasible";
              //    getchar();
                
                }
                
                double current_cost = calculateRouteCost(output, distanceTable);
                bestCost[i] = current_cost;
                bestSolution[i] = output;
                current_state[i] = beamCluster.isFeasible;
                // cout<<"\n set details";
                // cout<<"\n best sol for infi is ";
                // printRoute(bestSolution[i]);
                // cout<<"\n cost os "<<bestCost[i];
            }
            else
            {
                // cout<<" \n already bst cost is "<<bestCost[i];
                // cout<<"\n max is "<<FLT_MAX;
                // cout<<"\n non initial sol";
                // cout<<"\n init is :";
                // printRoute(bestSolution[i]);
                if (beamCluster.isFeasible == true)
                {
                    double current_cost = calculateRouteCost(output, distanceTable);

                    if (current_state[i] == false)
                    {
                        //cout<<"\n update state from false to true";
                        bestCost[i] = current_cost;
                        bestSolution[i] = output;
                        current_state[i] = beamCluster.isFeasible;
                    }
                    else
                    {
                        if (current_cost < bestCost[i] * .98)
                        {
                           // cout<<"\n only impormenet";
                     //    getchar();
                            cur_feasible_itr = 0;
                            bestCost[i] = current_cost;
                            bestSolution[i] = output;
                        }
                        else
                        {
                            cur_feasible_itr++;
                              // cout<<"\n waste feasible itr"<<cur_feasible_itr;
                     //   getchar();
                        }
                    }
                }
                else
                {
                   // cout<<"\n already a sol in there";
                 //   printRoute(bestSolution[i]);
                    if (current_state[i] == false)
                    {
                       // cout<<"\n infeasible sol got";
                       // getchar();
                        if ( voilatiom.size() < total_voilations[i])
                        {
                     //       cout<<"\n but less voi";
                            output.pop_back();
                            for (int j = 0; j < voilatiom.size(); j++)
                            {
                                output.push_back(voilatiom[j]);
                            }
                            output.push_back(0);
                            total_voilations[i] = voilatiom.size();

                            double current_cost = calculateRouteCost(output, distanceTable);

                            bestCost[i] = current_cost;
                            bestSolution[i] = output;
                            cur_infeasible_itr = 0;
                         //   cout<<"\n set in feasible itr to 0";
                         //   getchar();
                        }
                        else if ( voilatiom.size() == total_voilations[i])
                        {
                     //       cout<<"\n but less voi";
                            output.pop_back();
                            for (int j = 0; j < voilatiom.size(); j++)
                            {
                                output.push_back(voilatiom[j]);
                            }
                            output.push_back(0);
                            total_voilations[i] = voilatiom.size();

                            double current_cost = calculateRouteCost(output, distanceTable);
                            if(current_cost<bestCost[i])
                            {        
                            bestCost[i] = current_cost;
                            bestSolution[i] = output;
                            cur_infeasible_itr = 0;
                            }
                            else
                        {
                            cur_infeasible_itr++;
                        }
                        

                         //   cout<<"\n set in feasible itr to 0";
                         //   getchar();
                        }
                        
                        else
                        {  
                           // getchar();
                            cur_infeasible_itr++;
                           //  cout<<"cur_infeasible_itr"<<cur_infeasible_itr;
                        }
                    }
                    else
                    {
                        //getchar();
                        
                        cur_feasible_itr++;
                        //cout<<"cur_feasible_itr"<<cur_feasible_itr;
                    }
                }
            }
            beam_width++;
        }
        cout<<"\n Completed cluster "<<i<<" beam_width "<<beam_width;
      //  getchar();
        cout << " \n Running two opt";
        cout<<"\n current is ";
        printRoute(bestSolution[i]);
        beam_stable[i]=beam_width;
        if (current_state[i] == false)
        {
            cout<<"\n it is a infeasible solution";
            vector<int> res = bestSolution[i];
            vector<int> a;
            vector<int> b;
            int count = 0;
            for (auto itr = res.begin(); itr != res.end(); itr++)
            {
                if (count < total_voilations[i])
                {
                    a.push_back(*itr);
                    count++;
                }
                else
                {
                    b.push_back(*itr);
                }
            }
            vector<int> r = two_opt(a, distanceTable, cvrptw);
            for (auto itr = b.begin(); itr != b.end(); itr++)
            {
                r.push_back(*itr);
            }
            bestSolution[i] = r;
        }
        else
        { 
            cout<<"\nit is a complete solution";
            vector<int> r = two_opt(bestSolution[i], distanceTable, cvrptw);
            bestSolution[i] = r;
        }
    }

    for(int i=0;i<bestSolution.size();i++)
    {
        if(total_voilations[i]!=0)
        {
            int voi=total_voilations[i];

            bestSolution[i].pop_back();
            while(voi!=0)
            {
                timeWindowsVoilated.push_back(bestSolution[i][bestSolution[i].size()-1]);
                bestSolution[i].pop_back();
                voi--;
            }
            bestSolution[i].push_back(0);
        }
    }
    double cost=0;
    int tot_voilations_combined=0;
    cout<<"*************************************************************************";
    for(int i=0;i<bestSolution.size();i++)
    {
        cout<<endl;
        cout<<"\n Route for vehicle "<<i;
        printRoute(bestSolution[i]);
        cout<<" \n Cost of route "<<calculateRouteCost(bestSolution[i],distanceTable);
        cost+=calculateRouteCost(bestSolution[i],distanceTable);
        cout<<"\n capacity of route "<<getRouteCapacity(demand,bestSolution[i]);
        cout<<"\n Clsuter stabilized at "<<beam_stable[i];
    }
    cout<<"\n Adding panelty vechiles...";
    vector<CVRPTWNode> penaltyNodes;
    for(int i=0;i<timeWindowsVoilated.size();i++)
    {
        penaltyNodes.push_back(cvrptw.getNodeList()[timeWindowsVoilated[i]]);
    }
    sort(penaltyNodes.begin(),penaltyNodes.end(),sortNodes);
    int p_v=0;
    int curr_capcity=0;
    vector<vector<int>> pen_route;
    int i_c=0;
    int curr_node=0;
    cout<<"\n fpwwling are penality nodes";
    printRoute(timeWindowsVoilated);
    while(penaltyNodes.empty()==false)
    {
         vector<int> t;
         t.push_back(0);
         float ti=0;
         int prev=0;
         curr_capcity=0;
         cout<<"\n starting a new route";

        for(auto itr=penaltyNodes.begin();itr!=penaltyNodes.end();itr++)
         {
             getchar();
             if(penaltyNodes.empty()==true)
             break;   
             bool time=true;
             bool cap=true;
             curr_node=(*itr).getNodeId();
             cout<<"\n anelty no "<<(*itr).getNodeId();
             if(ti+distanceTable[prev][(*itr).getNodeId()]>(*itr).getNodeEndTime())
             {
                 cout<<"\n time failed";
                 cout<<"\n current ti is "<<ti;
                 cout<<"\n to goto new from "<<prev<<" tp "<<(*itr).getNodeId();
                 cout<<" "<<distanceTable[prev][(*itr).getNodeId()];
                 cout<<"\n total become"<<ti+distanceTable[prev][(*itr).getNodeId()];
                 cout<<" \n node end time is "<<(*itr).getNodeEndTime();
                 time=false;
             }   
             if(curr_capcity+penaltyNodes[curr_node].getNodeDemand()>capacity)
             {                   
                   cap=false;

            }
            if(time && cap)
            {
                cout<<"\n yes can be added"<<(*itr).getNodeId();
             ti=ti+distanceTable[prev][(*itr).getNodeId()];
             if(ti<(*itr).getNodeBeginTime())
             {
                 ti=(*itr).getNodeBeginTime();
             }
             ti+=(*itr).getNodeServiceTime();
             curr_capcity=curr_capcity+penaltyNodes[curr_node].getNodeDemand();
                
                t.push_back((*itr).getNodeId());
                prev=(*itr).getNodeId();
                penaltyNodes.erase(itr);
                itr--;
 cout<<"\n removed from lsit";
                cout<<"\n current list is ";
                cout<<" \n size of "<<penaltyNodes.size();     
             }
         }
         

        t.push_back(0);
        pen_route.push_back(t);
    }

cout<<"\n Printing voilated routes";

for(int i=0;i<pen_route.size();i++)
    {
        cout<<endl;
        cout<<"\n Route for vehicle "<<i;
        printRoute(pen_route[i]);
        cout<<" \n Cost of route "<<calculateRouteCost(pen_route[i],distanceTable);
        cost+=calculateRouteCost(pen_route[i],distanceTable);
    }
    

    cout<<"\n Result";
    cout<<"\n Total Cost : "<<cost;
    cout<<"\n Total Vechiles :"<<bestSolution.size();
    cout<<"\n Total Vechiles Combined:"<<tot_voilations_combined;

return 0;
    while (a < 2)
    {
        a++;
        bool infeasible = false;
        bestSolution.clear();

        tot_cost = 0;
        for (int i = 0; i < result.size(); i++)
        {
            //     cout << endl;
            cout << "\n running beam width " << beam_width;
            cout << "\n Running beam search on cluster" << i << "....";
            struct NodeDetails beamCluster = beamSearch(result[i], beam_width, cvrptw, distanceTable);
            vector<int> output = beamCluster.visited;
            vector<int> voilatiom = beamCluster.voilated;
            if (beamCluster.dist == FLT_MAX)
            {
                infeasible = true;
                //  break;
                cout << "\n unable to process cluster.no feasible solution exists...";
            }
            else
            {
                //arr[i]=true;
                cout << "\n Cluster processed succesfully";
                output = beamCluster.visited;
                cout << "\n Got result for cluster " << i;
                int x = beamCluster.isFeasible ? 1 : 0;
                if (x == 1)
                {
                    cout << "\n yes a complete solutiom";
                    printRoute(output);
                }
                else
                {
                    int voi = 0;
                    cout << "\n a voilated soltiom";
                    printRoute(output);
                    printf("\n");
                    for (auto itr = beamCluster.voilated.begin(); itr != beamCluster.voilated.end(); itr++)
                    {
                        output.push_back(*itr);
                        voi++;
                    }
                    cout << " \n voilation are :" << voi;
                    printRoute(voilatiom);
                }
            }

            //  printRoute(output);
            bestSolution.push_back(output);
            //  cout << "\n Capacity of route is " << getRouteCapacity(demand, result[i]);
            tot_cost += calculateRouteCost(output, distanceTable);
            //cout << "\n cost of route is " << calculateRouteCost(output, distanceTable);
        }
        //cout << "\n The total cost of route is " << tot_cost;
        if (infeasible == false)
        {
            //  cout << "\n for beam wodth " << beam_width << " tot is " << tot_cost << " and rev is " << prev_cost;

            if (best_cost == FLT_MAX)
            {
                best_cost = tot_cost;
                cout << "\n found first feaible";
              //  getchar();
            }
            else if (tot_cost < .98 * best_cost)
            {
                cout << "\n scope of improement";
              //  getchar();
                best_cost = tot_cost;
                maxItrWithoutImprovement = 0;
            }
            else
            {
                cout << "\n incremnt itr" << maxItrWithoutImprovement;

            //    getchar();
                maxItrWithoutImprovement++;
            }
        }
        else
        {
        //    cout << " \n Infeasible";
          //  cout << "\n beam_wodth here is " << beam_width;
           // getchar();
        }
        //

        //Result contains k means solution
        beam_width++;
    }
    double two_result = 0;
    cout << "\n ********************Results stabilized with beam width "
         << beam_width << "*****************" << endl;
    cout << " Cost is " << best_cost;

    for (int i = 0; i < 0; i++)
    {
        cout << endl;

        cout << "\n******** Running 2 opt on clsuter ********" << i;
        vector<int> r = two_opt(bestSolution[i], distanceTable, cvrptw);
        //cout<<" calling cost";

        two_result += calculateRouteCost(r, distanceTable);

        printRoute(r);
    }

    cout << " \nCost of the solution is : " << two_result;
    cout << " \n Beam width : " << beam_width;
    cout << "\n Vechicles used : " << bestSolution.size();
    t = clock() - t;
    double time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds

    printf("\nTime Taken %f seconds to execute : ", time_taken);
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
    int itr = 1;
    while (found == false)
    {

        move = true;

        // generated k random means
        int currentMeanGenerated = 0;
        vector<int> meanLocationUsed;

        while (currentMeanGenerated < k)
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
                    cur_distance = newDistance;
                    currentAssignment[i] = j;
                }
            }
        }
        //cout << "\n Details of Before Iteration1 :-";
        //cout << "\n Means are: ";
        for (int i = 0; i < k; i++)
        {
            //  cout << "\n";
            //cout << "" << meanList[i][0] << " " << meanList[i][1];
        }
        //cout << "\n Current assignment are :";
        for (int i = 0; i < nodeList.size(); i++)
        {
            //  cout << " " << currentAssignment[i];
        }
        int move1 = 1;
        while (move == true)
        {
            //cout << "\n running move itr" << move1;

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
            //cout << "\n Move and other calcaultion are don";
            for (int i = 0; i < k; i++)
            {
                vector<float> res;
                float temp = sumx[i] / countx[i];
                res.push_back(temp);
                temp = sumy[i] / county[i];
                res.push_back(temp);

                newMeanList.push_back(res);
            }
            //cout << "\n sums rae calcaulated";
            bool movement = false;
            //cout << "\n size is " << nodeList.size();
            meanList.clear();
            meanList = newMeanList;
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
                        cur_distance = newDistance;
                        tempAssignment[i] = j;
                    }
                }

                if (currentAssignment[i] != tempAssignment[i])
                {
                    //      cout << "\n yes a movement has happended";
                    movement = true;
                }
            }
            //cout << "\n rounf completef;";
            move1++;
            currentAssignment = tempAssignment;
            //cout << "\n prinitn updated details now:-";
            for (int i = 0; i < nodeList.size(); i++)
            {
                //  cout << " " << currentAssignment[i];
            }

            //cout << "\n assignment done";
            if (movement == false)
            {
                //  cout << "\n making it false";
                move = false;
            }
            //cout << "\n status updated";
            if (move == true)
            {
            } //  cout << "truel";
            else
            {
                //cout << "false";
            }

            //cout << "\n curretn set of iteration completed";
        }

        //return final_routes;
        //  cout << " came out";
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

struct NodeDetails beamSearch(vector<int> route, int beamWidth, CVRPTW tw,
                              double distanceTable[300][300])
{
    int tot = route.size() - 1;
    struct NodeDetails n0, nstar;
    n0.visited.push_back(0);
    for (int i = 1; i < route.size() - 1; i++)
    {
        n0.notVisited.push_back(route[i]);
    }
    n0.dist = 0;
    n0.isComplete = false;
    n0.isFeasible = true;
    n0.begin_time = tw.getNodeList()[0].getNodeBeginTime();
    vector<struct NodeDetails> b, boff, boffvoilated;
    b.push_back(n0);
    int l = 0;
    nstar = n0;
    nstar.dist = FLT_MAX;
    nstar.isComplete = false;
    nstar.isFeasible = true;
    //cout << " parameters set";
    //return nstar;
    while (b.size() != 0)
    {
        // cout << "\ n processing current set of b nodes";
        //brach from each node

        for (auto itr = b.begin(); itr != b.end(); itr++)
        {
            // cout << "\n start new iteration of this";
            struct NodeDetails temp = *itr;
            int last = temp.visited[temp.visited.size() - 1];
            // cout << "\n last node is " << last;
            bool voilated = false;
            ;
            for (auto r = temp.notVisited.begin(); r != temp.notVisited.end(); r++)
            {
                // cout << "\n Processing unvisited node " << *r;
                bool flag = false;

                float cost = distanceTable[last][*r] + temp.dist;
                if (cost <= tw.getNodeList()[*r].getNodeEndTime())
                {

                    if (cost < tw.getNodeList()[*r].getNodeBeginTime())
                        cost = tw.getNodeList()[*r].getNodeBeginTime();
                    flag = true;
                }
                else
                {
                    // if(cost+tw.getNodeList()[*r].getNodeServiceTime()<=
                    //tw.getNodeList()[*r].getNodeEndTime())
                    //{
                    //flag=true;
                    // }
                    //else
                    //{

                    // cout << "\n not possible to add";
                    // cout << " \nlast is " << last;
                    //cout << "\n cost is " << cost;
                    //cout << "\n open is " << tw.getNodeList()[*r].getNodeBeginTime();
                    voilated = true;
                    //}
                }
                if (flag == true)
                {
                    if (temp.isFeasible == true)
                    {
                        // cout << "\n yes can be added";
                        std::vector<int>::iterator it;
                        struct NodeDetails child;
                        child.isComplete = false;
                        child.isFeasible = true;
                        child.visited = temp.visited;
                        child.visited.push_back(*r);
                        vector<int> not_vis(temp.notVisited.begin(), temp.notVisited.end());
                        it = std::find(not_vis.begin(), not_vis.end(), *r);
                        not_vis.erase(it);
                        child.notVisited = not_vis;
                        child.begin_time = tw.getNodeList()[*r].getNodeBeginTime();
                        child.dist = temp.dist + distanceTable[last][*r] + tw.getNodeList()[*r].getNodeServiceTime();
                        if (child.notVisited.empty())
                        {
                           // cout << "\n but all are visited in proper";

                            child.isComplete = true;
                            child.visited.push_back(0);
                            child.dist += distanceTable[*r][0];
                            if (nstar.dist == FLT_MAX ||
                                nstar.isFeasible == false || child.dist < nstar.dist)
                                nstar = child;
                        }
                        else
                        {
                            // cout << "\n prepared new child ";
                         //   printNodeDetails(child);
                            boff.push_back(child);
                        }
                    }
                    else
                    {

                        // cout << "\n yes can be added as infeasible";
                        std::vector<int>::iterator it;
                        struct NodeDetails child = temp;
                        child.visited.push_back(*r);
                        vector<int> not_vis(temp.notVisited.begin(), temp.notVisited.end());
                        it = std::find(not_vis.begin(), not_vis.end(), *r);
                        not_vis.erase(it);
                        child.notVisited = not_vis;
                        child.begin_time = tw.getNodeList()[*r].getNodeBeginTime();
                        child.dist = temp.dist + distanceTable[last][*r] + tw.getNodeList()[*r].getNodeServiceTime();
                        if (child.notVisited.empty())
                        {
                            // cout << "\n but all are visited in voilates";

                            child.isComplete = true;
                            child.visited.push_back(0);
                            child.dist += distanceTable[*r][0];
                            if (nstar.dist == FLT_MAX || (nstar.isFeasible == false && child.dist < nstar.dist))
                            {
                                nstar = child;
                                // cout << " \n got a solution";
                            }
                        }
                        else
                        {
                            // cout << "\n prepared new child voilated";
                        //    printNodeDetails(child);
                            boffvoilated.push_back(child);
                        }
                    }
                }
                else
                {
                    struct NodeDetails child = temp;
                    vector<int> not_vis(temp.notVisited.begin(), temp.notVisited.end());
                    auto it = std::find(not_vis.begin(), not_vis.end(), *r);
                    not_vis.erase(it);
                    child.notVisited = not_vis;
                    child.voilated.push_back(*r);
                    child.isFeasible = false;

                    if (child.notVisited.empty())
                    {
                        // cout << "\n but all are visited in voilates";

                        child.isComplete = true;
                        child.visited.push_back(0);
                        child.dist += distanceTable[*r][0];
                        if (nstar.dist == FLT_MAX || (nstar.isFeasible == false && child.dist < nstar.dist))
                            nstar = child;
                    }
                    else
                    {
                        // cout << "\n prepared new child voilated";
                      //  printNodeDetails(child);
                        boffvoilated.push_back(child);
                    }
                }
            }
            // cout << "\n completed for iterations";
        }
        // cout << "\n all nodes processed";

        vector<struct NodeDetails> temp_B(boff.begin(), boff.end());
        sort(temp_B.begin(), temp_B.end(), sortBeamNodes);
        // cout << "\n sorting done";
        // cout << " size of b off is " << temp_B.size();
        b.clear();
        int k = (beamWidth < temp_B.size()) ? beamWidth : temp_B.size();
        // cout << "********";
        // cout << " \n rpitn sort order";
        int count = 1;
        for (auto itr = temp_B.begin(); itr != temp_B.end(); itr++)
        {
            // cout << endl;
            // cout << " ";
           // printNodeDetails(*itr);
            // cout << " \n count " << count++;
        }
        // cout << "\n**** beam wodt is " << beamWidth;
        // cout << "\n*** tem is " << temp_B.size();
        // cout << "\n min(k) is " << k;
        // cout << "\n now it will run for " << k;
        int current_count = 0;
        int index = 0;

        while (current_count <= beamWidth && temp_B.empty() == false)
        {
    //        cout << " now running for loop";
            bool flag = false;
            struct NodeDetails a = temp_B[index];
            // cout << " \n Processing node ";
          //  printNodeDetails(a);
             for (int i = 0; i < a.notVisited.size(); i++)
            {

                float begin_time = tw.getNodeList()[a.notVisited[i]].getNodeBeginTime();
                float end_time = tw.getNodeList()[a.notVisited[i]].getNodeEndTime();
                float service_time = tw.getNodeList()[a.notVisited[i]].getNodeServiceTime();
                float current_cost = 0;
                if (a.dist > end_time)
                {
      //              cout << " cannot process " << a.notVisited[i] << " for this node";
                    a.isFeasible = false;
             //       int drop = a.notVisited[i];
               //     auto it = std::find(a.notVisited.begin(), a.notVisited.end(), drop);
                 //   a.notVisited.erase(it);
                   // a.voilated.push_back(drop);
        //            cout << "\n ushng to off";
                //    printNodeDetails(a);
                    boffvoilated.push_back(a);
                    flag = true;
                    break;
                }
            }
            if (!flag)
            {
                b.push_back(temp_B[index]);
                current_count++;
            }
            index++;
            if (index == temp_B.size())
                break;
        }

        if (current_count < beamWidth)
        {
          //  cout << "\n some room so there for other stuff";
            int i = 0;
            sort(boffvoilated.begin(), boffvoilated.end(), sortBeamNodes);

            int count = 1;
            //cout << "\n printing infeasible solution details";
            for (auto itr = boffvoilated.begin(); itr != boffvoilated.end(); itr++)
            {
              //  cout << endl;
                //cout << " ";
              //  printNodeDetails(*itr);
                //cout << " \n count " << count++;
            }
            // cout << " \nsorted other stuff";
            // cout << "\n size of boff is " << boffvoilated.size();
            // cout << "\n current count is " << current_count;

            while (current_count < beamWidth && boffvoilated.size() != i)
            {
                // cout << " \n curr count in loop" << current_count;
                // cout << " \n curr iin loop" << i;

                b.push_back(boffvoilated[i]);
            //    printNodeDetails(boffvoilated[i]);
                i++;
                // cout << "\n npw pushing";
                current_count++;
            }
        }
        // cout << " new set prepared with size" << b.size();
        boff.clear();
        boffvoilated.clear();
        temp_B.clear();
        // cout << "\n new data prepared";
        //  return nstar;
    }

    return nstar;
}

vector<int> two_opt(vector<int> route, double distanceTable[300][300], CVRPTW tw)
{
    bool improvement = true;
    vector<int> bestRoute = route;
    //cout<<"\n inpute route isn ";
    //printRoute(route);
    while (improvement == true)
    {
        //cout<<"\n ne round started";
        improvement = false;
        for (int i = 1; i < bestRoute.size() - 2; i++)
            for (int j = 1; j < bestRoute.size() - 2; j++)
                if (j != i - 1 && j != i + 1 && i != j)
                {
                    //cout<<"\n CUrrent route is ";
                    //              printRoute(bestRoute);
                    int a = bestRoute[i];
                    int b = bestRoute[j];
                    int c = bestRoute[i + 1];
                    int d = bestRoute[j + 1];
                    //cout<<" \n data access";
                    if ((distanceTable[a][c] + distanceTable[b][d]) >
                        (distanceTable[a][b] + distanceTable[c][d]))
                    {
                        //                      cout<<"\n yes try to update imp";
                        //                    cout<<endl;
                        //                  cout<<a<<" "<<c<<"+"<<" "<<b<<" "<<d;
                        //                cout<<a<<" "<<b<<"+"<<" "<<c<<" "<<d;
                        //              cout<<endl;
                        vector<int> temp_route;

                        if (i < j)
                        {

                            //            cout<<"\n currnet i"<<i<<" j "<<j;
                            //   vector<int> temp_route;
                            for (int k = 0; k <= i; k++)
                            {
                                temp_route.push_back(bestRoute[k]);
                            }
                            for (int k = j; k >= i + 1; k--)
                            {
                                temp_route.push_back(bestRoute[k]);
                            }
                            for (int k = j + 1; k < bestRoute.size(); k++)
                            {
                                temp_route.push_back(bestRoute[k]);
                            }
                        }
                        else
                        {
                            //          cout<<"\n yes here";
                            //            cout<<"*********constructi from***";
                            //              printRoute(bestRoute);
                            //            cout<<"\n currnet i"<<i<<" j "<<j;
                            for (int k = 0; k <= j; k++)
                            {
                                temp_route.push_back(bestRoute[k]);
                            }
                            for (int k = i; k >= j + 1; k--)
                            {
                                temp_route.push_back(bestRoute[k]);
                            }
                            for (int k = i + 1; k < bestRoute.size(); k++)
                            {
                                temp_route.push_back(bestRoute[k]);
                            }
                        }

                        int s = temp_route.size();
                        float cur_time = distanceTable[0][temp_route[1]];
                        bool satisfies = true;
                        for (int i = 1; i < temp_route.size() - 1; i++)
                        {
                            CVRPTWNode node = tw.getNodeList()[temp_route[i]];
                            if (cur_time > node.getNodeEndTime())
                            {
                                satisfies = false;
                                break;
                            }
                            else
                            {
                                cur_time += node.getNodeServiceTime();
                                cur_time += distanceTable[temp_route[i]][temp_route[i + 1]];
                            }
                        }
                        //    cout<<"**** here temp route is ***";
                        //  printRoute(temp_route);
                        if (satisfies)
                        {
                            improvement = true;
                            //    cout<<"\n **********************************yes found improvement";
                            //  cout<<"\n Old tour";
                            //printRoute(bestRoute);
                            bestRoute = temp_route;
                            //                  cout<<"\n new tour";
                            //printRoute(bestRoute);
                        }
                        else
                        {
                            //cout<<"\n no imp";
                        }
                    }
                    else
                    {
                        //cout<<"\n nothing so gar";
                    }
                }
        //cout<<" **** Round is done ****";
    }
    //cout<<"\n let us exit now";
    return bestRoute;
}
