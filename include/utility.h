/*************************************
Filename :- utility.h
Author :- Bateesh Dhingra
Date :- 11th Jul 2019
Description :- utility functions declaration e.g file read etc.
***********************************/
#ifndef _UTILITY_H_
#define _UTILITY_H_
#include <bits/stdc++.h>

using namespace std;

// extract the first number in a string
int extract_int(const string & );

// extract all numbers in a string
vector < int > extract_ints(const string & );

// read CVRP data file and parse to a vector
vector < vector < int > > readFile(const char * );

//getDistanceTable to preprocess all distance between any two customers

void getDistanceTable(vector < vector < int > > d,double distanceTable[300][300]);
//getDistance between two points (px,py) and (dx,dy)
double getDistance(int px, int py, int dx, int dy);

double getDistanceByCustomerNumber(int c1,int c2);

int getRouteCapacity(vector < int> demand,vector<int> route);
double getRouteCost(vector<int> route);

void printRoute(vector<int> cr);

double calculateRouteCost(vector<int> route, double distance[300][300]);

// generic functions
template < typename T >
  bool contain(const vector < T > & vec,
    const T & elem) {
    if (find(vec.begin(), vec.end(), elem) == vec.end()) return false;
    else return true;
  }
 #endif
