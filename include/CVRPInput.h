/*************************************
Filename :- CVRPInput.h
Author :- Bateesh Dhingra
Date :- 13th Jul 2019
Description :- Declaration of CVRPInput class.It represents the input to CVRP instance
***********************************/

#ifndef _CVRPInput_H_
#define _CVRPInput_H_
#include <bits/stdc++.h>

using namespace std;

class CVRPInput {
  double dimension;
  double capacity;
  int vehicles;
  vector<double> vechilesCapacity;
  vector < double > depotCord;
  vector < vector < double >> customerCordinates;
  vector < vector < double >> allCordinates;
  vector < double > demandList;
  vector<double> vehicleID;
  vector<double> shipmentID;
  map<vector<double>, int> cordinateToCutomerMapping; 
  map<int, vector<double>> customerToCordinateMapping; 
  void populatemap  (vector<vector<double>> data); 

  public:
    //constructor

  CVRPInput(vector < vector < double >> data);

  //get the dimension
  double getDimension();

  double getVehicles();

  vector < double >  getVechilesCapacity();

  //get the capacity
  double getCapacity();

  //get the central depot cordinates
  vector < double > getDepotCord();

  //get the customer cordinates
  vector < vector < double >> getCustomerCordinates();
  vector < vector < double >> getAllCordinates();

  //get customer demand list
  vector < double > getDemandList();

  vector<vector<double>> convertRouteToCordinateList(vector<int> route);

  vector<int> convertCordinateListToRoute(vector<vector<double>> customerCordinates);
  vector<double> getVechicleID();
  vector<double> getShipmentID();

};
#endif
