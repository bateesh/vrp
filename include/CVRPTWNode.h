#include <bits/stdc++.h> 
using namespace std; 
class CVRPTWNode 
{ 
    private:
    int id;
    float x_cordinate;
    float y_cordinate;
    float service_time;
    int demand;
    float begin_time;
    float end_time;

    public:
    CVRPTWNode(int identifier,float x,float y,float s,int d,float b,float e);
    int getNodeId();
    float getNodeXCordinate();
    float getNodeYCordinate();
    float getNodeServiceTime();
    int getNodeDemand();
    float getNodeBeginTime();
    float getNodeEndTime();
    void printCVRPNode();
}; 