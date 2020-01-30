/*************************************
Filename :- CVRPInput.cpp
Author :- Bateesh Dhingra
Date :- 12th Jul 2019
Description :- Solving CVRP in brute force manner.Start from list and keep on assigning to vehicle until capacity constraints are satisfied
***********************************/
#include "utility.h"

#include "CVRPVehicleOutput.h"

#include "CVRPInput.h"

int main(int argc, char * argv[]) {
  vector < vector < int > > data = readFile(argv[1]);
  CVRPInput input = CVRPInput(data);
  vector < CVRPVehicleOutput > output;
  int dimension = input.getDimension();
  int capacity = input.getCapacity();
  vector < int > demand = input.getDemandList();
  vector < vector < int >> customerCordinates = input.getCustomerCordinates();

  int currentCapacity = 0;
  auto start = demand.begin();

  vector < int > depotLocation = input.getDepotCord();
  int p1 = depotLocation[0];
  int p2 = depotLocation[1];
  cout<<" Depot Location is "<<p1<< " "<<p2;
  auto itr = demand.begin()+1;
  int flag = 0;
  while (itr != demand.end()) {
    vector < int > truck;
    truck.push_back(-1);
    double cost = 0;
    int px = p1;
    int py = p2;

    while (currentCapacity <= capacity) {
      if (currentCapacity + ( * itr) <= capacity) {
        currentCapacity = currentCapacity + ( * itr);

        truck.push_back(distance(start, itr));
        vector < int > customerCord = data[distance(start, itr) +1];
        int dx = customerCord[0];
        int dy = customerCord[1];

        double distance = getDistance(px, py, dx, dy);
        px = dx;
        py = dy;
        cost += distance;

        itr++;
        if (itr == demand.end()) {
          flag = 1;
          break;
        }
      } else {
        break;
      }

    }
    cost += getDistance(p1, p2, px, py);
    truck.push_back(-1);

    CVRPVehicleOutput cvrp = CVRPVehicleOutput(truck, currentCapacity, cost);
    output.push_back(cvrp);

    currentCapacity = 0;
    if (flag == 1)
      break;
  }

  CVRPVehicleOutput::printCVRPOutput(output);

}
