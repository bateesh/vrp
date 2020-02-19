/*************************************
Filename :- CVRPInput.cpp
Author :- Bateesh Dhingra
Date :- 13th Jul 2019
Description :- implemtation of CVRPInput class functions
***********************************/
#include "CVRPInput.h"

CVRPInput::CVRPInput(vector<vector<double>> data)
{

  dimension = data[0][0];
  capacity = data[0][1];
  demandList = data[dimension + 1];
  depotCord = data[1];

  auto p1 = data.begin() + 2;
  auto p2 = data.end() - 1;

  customerCordinates = vector<vector<double>>(p1, p2);
  allCordinates = vector<vector<double>>(p1-1, p2);
  cout<<"\n Total customer a are "<<customerCordinates.size();
  cout<<endl;
  populatemap(data);
}
vector < vector < double >>  CVRPInput::getAllCordinates()
{
return allCordinates;
}

void CVRPInput::populatemap(vector<vector<double>> data)
{
  auto p1 = data.begin() + 1;
  auto p2 = data.end() - 1;
  vector < vector < double >> customerCordinates=vector<vector<double>>(p1, p2);
 
  customerCordinates = vector<vector<double>>(p1, p2);
  int count = 0;
  for (auto itr = customerCordinates.begin(); itr != customerCordinates.end(); itr++)
  {
    cordinateToCutomerMapping[*itr] = count;
    customerToCordinateMapping[count]=*itr;
    count++;
  }

}
 vector<vector<double>> CVRPInput::convertRouteToCordinateList(vector<int> route)
 {
 vector<vector<double>> result;
 for(auto itr=route.begin();itr!=route.end();itr++)
 {
   result.push_back(customerToCordinateMapping[*itr]);
 }
 return result;
 }

vector<int> CVRPInput::convertCordinateListToRoute(vector<vector<double>> customerCordinates)
{
   vector<int> result;
 for(auto itr=customerCordinates.begin();itr!=customerCordinates.end();itr++)
 {
   result.push_back(cordinateToCutomerMapping[*itr]);
 }
 return result;

}

double CVRPInput::getDimension()
{
  return dimension;
}
double CVRPInput::getCapacity()
{
  return capacity;
}
vector<double> CVRPInput::getDepotCord()
{
  return depotCord;
}

vector<vector<double>> CVRPInput::getCustomerCordinates()
{
  return customerCordinates;
}

vector<double> CVRPInput::getDemandList()
{
  return demandList;
}
