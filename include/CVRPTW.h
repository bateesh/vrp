#include <bits/stdc++.h>
#include "CVRPTWNode.h"

using namespace std; 
class CVRPTW
{ 
    private:
    int maxNumberOfVehicles;
    int numberOfNodes;
    int maximumCapacity;
    vector<CVRPTWNode> nodeList;
    
    public:
    CVRPTW(int v,int c,int m,vector<CVRPTWNode> list);
    int getMaxNumberOfVehicles();
    int getNumberOfNodes();
    int getmaximumCapacity();
    vector<CVRPTWNode> getNodeList();
    void printCVRPInstance();

}; 