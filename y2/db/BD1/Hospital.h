#pragma once
#include <string>
using namespace std;

class Hospital
{
public:
	int HospitalID;
	char HospitalName[50];
	int Index;
};

class Doctor
{
public:
	int DoctorID;
	char DoctorName[50];
	int HospitalID;
	int Index;
};