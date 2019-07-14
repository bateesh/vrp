/*************************************
Filename :- CVRPVehicleOutput.cpp
Author :- Bateesh Dhingra
Date :- 13th Jul 2019
Description :- implemtation of CVRPVehicleOutput class functions
***********************************/

#include "CVRPVehicleOutput.h"


CVRPVehicleOutput::CVRPVehicleOutput(vector < int > r, int t, int c) {
  route = r;
  totalDemandServed = t;
  totalRouteCost = c;

}

vector < int > CVRPVehicleOutput::getRoute() {
  return route;
}

int CVRPVehicleOutput::getTotalDemandServed() {
  return totalDemandServed;
}

int CVRPVehicleOutput::getTotalRouteCost() {
  return totalRouteCost;
}

void CVRPVehicleOutput::printCVRPOutput(vector < CVRPVehicleOutput > output) {
  int r = 1;
  double cost = 0;

  for (auto ptr = output.begin(); ptr != output.end(); ptr++) {
    CVRPVehicleOutput vehicle = * ptr;
    cost += vehicle.getTotalRouteCost();
    cout << " Truck " << r << " Details: ";
    cout << "\n Route Cost " << vehicle.getTotalRouteCost();
    cout << "\n Route Capacity Served by truck " << vehicle.getTotalDemandServed();
    cout << "\n Route followed by Truck : ";
    vector < int > currentRoute = vehicle.getRoute();
    auto routeVisited = currentRoute.begin();
    for (; routeVisited != currentRoute.end() - 1; routeVisited++) {
      cout << " " << * routeVisited << "->";

    }
    cout << * routeVisited;
    cout << endl;
    cout << "--------------------------------------------------------------------------------------------------------------------------------------------";
    cout << endl;

    r++;

  }
  cout << " Summary: ";
  cout << "\n Total vechicles " << output.size();
  cout << "\n Total cost " << cost;
}
