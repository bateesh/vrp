/*************************************
Filename :- CVRPVehicleOutput.h
Author :- Bateesh Dhingra
Date :- 13th Jul 2019
Description :- declaration of CVRPVehicleOutput class.This shows ouput details of one vehicle
***********************************/

#ifndef _CVRPVehicleOutput_H_
#define _CVRPVehicleOutput_H_
#include <bits/stdc++.h>
using namespace std;
class CVRPVehicleOutput
{
private:
    vector<int> route;
    int totalDemandServed;
    int totalRouteCost;
public:
    CVRPVehicleOutput(vector<int> r,int t,int c);//constructor

    vector<int> getRoute();//get route of current vehicle

    int getTotalDemandServed();//get the total demand serverved by the vechicle

    int getTotalRouteCost();//get the total route cost

    static void printCVRPOutput(vector<CVRPVehicleOutput>);// print CVRPOutput

};
#endif
