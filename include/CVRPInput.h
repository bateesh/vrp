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
  int dimension;
  int capacity;
  vector < int > depotCord;
  vector < vector < int >> customerCordinates;
  vector < int > demandList;
  public:
    //constructor
    CVRPInput(vector < vector < int >> data);

  //get the dimension
  int getDimension();

  //get the capacity
  int getCapacity();

  //get the central depot cordinates
  vector < int > getDepotCord();

  //get the customer cordinates
  vector < vector < int >> getCustomerCordinates();

  //get customer demand list
  vector < int > getDemandList();

};
#endif