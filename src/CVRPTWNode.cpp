#include "CVRPTWNode.h"

CVRPTWNode::CVRPTWNode(int identifier, float x, float y, float s, int d, float b, float e)
{
    id = identifier;
    x_cordinate = x;
    y_cordinate = y;
    service_time = s;
    demand = d;
    begin_time = b;
    end_time = e;
}
void CVRPTWNode::printCVRPNode()
{
    cout<<"\n"<<id<<" "<<x_cordinate<<" "<<y_cordinate<<" "<<service_time<<" "<<demand<<" "<<begin_time<<" "<<end_time<<" ";
}


int CVRPTWNode::getNodeId()
{
    return id;
}

float CVRPTWNode::getNodeXCordinate()
{
    return x_cordinate;
}
float CVRPTWNode::getNodeYCordinate()
{
    return y_cordinate;
}
float CVRPTWNode::getNodeServiceTime()
{
    return service_time;
}
int CVRPTWNode::getNodeDemand()
{
    return demand;
}

float CVRPTWNode::getNodeBeginTime()
{
    return begin_time;
}

float CVRPTWNode::getNodeEndTime()
{
    return end_time;
}
