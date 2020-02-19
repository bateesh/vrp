#include <bits/stdc++.h>
using namespace std;
class TSPSolver
{
    vector<vector<double>> nodes;
    vector<double> depot;
    double distanceTableTSP[300][300];
    map<pair<double,double>,int> locationToIndexMap;
    
public:
    TSPSolver(vector<vector<double>> nodes,vector<double> depot);
    vector<vector<double>> solveTSP();
    double getDistance(int x,int y);
};