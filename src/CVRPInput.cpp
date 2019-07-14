/*************************************
Filename :- CVRPInput.cpp
Author :- Bateesh Dhingra
Date :- 13th Jul 2019
Description :- implemtation of CVRPInput class functions
***********************************/
#include "CVRPInput.h"


CVRPInput::CVRPInput(vector < vector < int >> data) {

  dimension = data[0][0];
  capacity = data[0][1];
  demandList = data[dimension + 1];
  depotCord = data[dimension + 2];

  auto p1 = data.begin() + 1;
  auto p2 = data.end() - 2;

  customerCordinates = vector < vector < int >> (p1, p2);

}

int CVRPInput::getDimension() {
  return dimension;
}
int CVRPInput::getCapacity() {
  return capacity;
}
vector < int > CVRPInput::getDepotCord() {
  return depotCord;
}

vector < vector < int >> CVRPInput::getCustomerCordinates() {
  return customerCordinates;
}

vector < int > CVRPInput::getDemandList() {
  return demandList;
}
