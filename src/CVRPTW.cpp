#include <bits/stdc++.h>
#include "CVRPTW.h"

CVRPTW::CVRPTW(int v, int c, int m, vector<CVRPTWNode> list)
{
    maxNumberOfVehicles = v;
    numberOfNodes = c;
    maximumCapacity = m;
    nodeList = list;
}

CVRPTW::CVRPTW()
{
}

void CVRPTW:: printCVRPInstance()
{
    printf("\n CVRP Instance.........");
    printf("\n Maximum Number of vehicles %d ",maxNumberOfVehicles);
    printf("\n Maximum Number of nodes %d",numberOfNodes);
    printf("\n Maximum Capacity %d",maximumCapacity);
    for(auto itr=nodeList.begin();itr!=nodeList.end();itr++)
    {
        CVRPTWNode node=(*itr);
        node.printCVRPNode();
    }
    
}
int CVRPTW::getMaxNumberOfVehicles()
{
    return maxNumberOfVehicles;
}
int CVRPTW::getNumberOfNodes()
{
    return numberOfNodes;
}
int CVRPTW::getmaximumCapacity()
{
    return maximumCapacity;
}
vector<CVRPTWNode> CVRPTW::getNodeList()
{
    return nodeList;
}
