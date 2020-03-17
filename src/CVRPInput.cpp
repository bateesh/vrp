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
  vehicles=data[0][2];
  vechilesCapacity.clear();
  vehicleID.clear();
  shipmentID.clear();
  int j=0;
  for(int i=0;i<vehicles;i++)
  {
    cout<<"\n n ow vapacity pushimjg "<<data[0][3+i+j]<<" "<<data[0][4+i+j];
    
  vechilesCapacity.push_back(data[0][4+i+j]);
  vehicleID.push_back(data[0][3+i+j]);
  j++;
      cout<<"\n current size is "<<vechilesCapacity.size();

  }

  cout<<"\n see here";
int i=0;
  for (auto itr = getVechilesCapacity().begin(); itr != getVechilesCapacity().end(); itr++)
	{
		double data = *itr;
		cout<<"\n datais  : "<<data;
    cout<<" \n is cap : "<<vechilesCapacity[i];
    cout<<" \n is cap : "<<vehicleID[i++];
		//cout << " " << data;
		cout<<endl;
	}

  demandList = data[dimension + 1];
  shipmentID= data[dimension + 2];

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

vector <double>  CVRPInput::getVechilesCapacity()
{
return vechilesCapacity;
}

double   CVRPInput:: getVehicles()
{
  return vehicles;
}

vector<double>  CVRPInput::getVechicleID()
{
  return vehicleID;
}
  vector<double> CVRPInput::getShipmentID()
  {
    return shipmentID;
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
