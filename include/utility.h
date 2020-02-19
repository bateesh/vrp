/*************************************
Filename :- utility.h
Author :- Bateesh Dhingra
Date :- 11th Jul 2019
Description :- utility functions declaration e.g file read etc.
***********************************/
#ifndef _UTILITY_H_
#define _UTILITY_H_

#include <bits/stdc++.h>
#include <curl/curl.h>
#include <jsoncpp/json/json.h>

#include "CVRPTW.h"
using namespace std;

// extract the first number in a string
int extract_int(const string & );

// extract all numbers in a string
vector < int > extract_ints(const string & );


// extract the first float number in a string
float extract_float(const string & );

// extract all floats in a string
vector < float > extract_floats(const string & );

// read CVRP data file and parse to a vector
vector < vector < double > > readFile(const char * );

// read CVRP data file and parse to a vector of double
vector < vector < double > > readFile_double(const char * );
//read a file and return CVRPTW instace
CVRPTW readFileWithTimeWindows(const char * path);

//getDistanceTable to preprocess all distance between any two customers

void getDistanceTable(vector < vector < double > > d,double distanceTable[300][300]);

void getLiveDistanceTable(vector < vector < double > > d,double distanceTable[300][300]);
void getLiveDistanceTableTSP(vector < vector < double > > d,
double distanceTable[300][300]);
//getDistance between two points (px,py) and (dx,dy)
double getDistance(int px, int py, int dx, int dy);
void getDistanceTableTW(CVRPTW cvrptw,double distanceTable[300][300]) ;

double getLiveDistance(double px, double py, double dx, double dy);
double getLiveDistance(vector<double> px,vector<double> dx);

double getDistanceByCustomerNumber(int c1,int c2);

double getRouteCapacity(vector < double> demand,vector<int> route);
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
