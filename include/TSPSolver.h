#include <bits/stdc++.h>
using namespace std;
class TSPSolver
{
    vector<vector<int>> nodes;
    vector<int> depot;
    
public:
    TSPSolver(vector<vector<int>> nodes,vector<int> depot);

    vector<vector<int>> solveTSP();
};