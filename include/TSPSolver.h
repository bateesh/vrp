#include <bits/stdc++.h>
using namespace std;
class TSPSolver
{
    vector<vector<double>> nodes;
    vector<double> depot;
    double distanceTableTSP[10][10];
    map<pair<double,double>,int> locationToIndexMap;
    
public:
    TSPSolver(vector<vector<double>> nodes,vector<double> depot);
    vector<vector<double>> solveTSP();
    double getDistance(int x,int y);
};