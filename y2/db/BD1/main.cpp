#include "hospital.h"
#include <iostream>
#include <fstream>
#include <vector>

vector<Hospital> Hospitals;
vector<Doctor> Doctors;
vector<pair<int, int>> Indices;
const string path = "D:\\c\\kubick\\labs\\BD1\\",
hospitalHead = "HospitalID  HospitalName  Index\n",
doctorHead = "DoctorID  DoctorName  HospitalID  Index\n",
indexHead = "ArrayPosition  NextIndex\n",
space = "     ";
int maxHospital = 0;
int maxDoctor = 0;

void ReadMaster()
{
	fstream fi(path + "S.fl", ios::in | ios::binary);

	if (!fi)
	{
		cout << "Can't open " + path + "S.fl\n";
		return;
	}

	fi.seekg(0, ios::end);
	int l = fi.tellg() / sizeof(Hospital);
	Hospitals.resize(l);
	fi.seekp(0, ios::beg);
	

	for (int i = 0; i < l; ++i)
	{
		fi.read((char*)&Hospitals[i], sizeof(Hospital));

		if (Hospitals[i].HospitalID >= maxHospital)
			maxHospital = Hospitals[i].HospitalID + 1;
	}

	if (!fi.good())
	{
		cout << "Error occurred at reading time!" << errno << endl;
		return;
	}

	fi.close();
}

void ReadSlave()
{
	fstream fi(path + "SP.fl", ios::in | ios::binary);

	if (!fi)
	{
		cout << "Can't open " + path + "SP.fl\n";
		return;
	}

	fi.seekg(0, ios::end);
	int l = fi.tellg() / sizeof(Doctor);
	Doctors.resize(l);
	fi.seekp(0, ios::beg);

	for (int i = 0; i < l; ++i)
	{
		fi.read((char*)&Doctors[i], sizeof(Doctor));

		if (Doctors[i].DoctorID >= maxDoctor)
			maxDoctor = Doctors[i].DoctorID + 1;
	}

	if (!fi.good())
	{
		cout << "Error occurred at reading time!\n";
		return;
	}

	fi.close();
}

void ReadIndex()
{
	fstream fi(path + "S.ind", ios::in | ios::binary);

	if (!fi)
	{
		cout << "Can't open " + path + "S.ind\n";
		return;
	}

	fi.seekg(0, ios::end);
	int l = fi.tellg() / sizeof(pair<int, int>);
	Indices.resize(l);
	fi.seekp(0, ios::beg);

	for (int i = 0; i < l; ++i)
		fi.read((char*)&Indices[i], sizeof(pair<int, int>));

	if (!fi.good())
	{
		cout << "Error occurred at reading time!\n";
		return;
	}

	fi.close();
}

void ReadFiles()
{
	ReadMaster();
	ReadSlave();
	ReadIndex();
}

void WriteMaster()
{
	fstream fo(path + "S.fl", ios::out | ios::binary);
	
	if (!fo)
	{
		cout << "Can't open " + path + "S.fl\n";
		return;
	}

	for (Hospital& i : Hospitals)
		fo.write((char*) &i, sizeof(Hospital));

	fo.close();

	if (!fo.good())
	{
		cout << "Error occurred at writing time!\n";
		return;
	}
}

void WriteSlave()
{
	fstream fo(path + "SP.fl", ios::out | ios::binary);

	if (!fo)
	{
		cout << "Can't open " + path + "SP.fl\n";
		return;
	}

	for (Doctor& i : Doctors)
		fo.write((char*)&i, sizeof(Doctor));

	fo.close();

	if (!fo.good())
	{
		cout << "Error occurred at writing time!\n";
		return;
	}
}

void WriteIndex()
{
	fstream fo(path + "S.ind", ios::out | ios::binary);

	if (!fo)
	{
		cout << "Can't open " + path + "S.ind\n";
		return;
	}

	for (pair<int, int>& i : Indices)
		fo.write((char*)&i, sizeof(pair<int, int>));

	fo.close();

	if (!fo.good())
	{
		cout << "Error occurred at writing time!\n";
		return;
	}
}

void WriteFiles()
{
	WriteMaster();
	WriteSlave();
	WriteIndex();
}

int findHospital(int x)
{
	for (int i = 0; i < Hospitals.size(); ++i)
		if (Hospitals[i].HospitalID == x)
			return i;

	return -1;
}

int findDoctor(int x)
{
	for (int i = 0; i < Doctors.size(); ++i)
		if (Doctors[i].DoctorID == x)
			return i;

	return -1;
}

int findFreeHospital()
{
	for (int i = 0; i < Hospitals.size(); ++i)
		if (Hospitals[i].Index < 0)
			return i;

	Hospital h;
	Hospitals.push_back(h);
	return Hospitals.size() - 1;
}

int findFreeDoctor()
{
	for (int i = 0; i < Doctors.size(); ++i)
		if (Doctors[i].Index < 0)
			return i;

	Doctor d;
	Doctors.push_back(d);
	return Doctors.size() - 1;
}

int findFreeIndex()
{
	for (int i = 0; i < Indices.size(); ++i)
		if (Indices[i].first < 0)
			return i;

	Indices.push_back(pair<int, int>(-1, -1));
	return Indices.size() - 1;
}

void CreateMaster(string x)
{
	int hospitalIndex = findFreeIndex();
	int hospitalPos = findFreeHospital();
	Indices[hospitalIndex].first = hospitalPos;
	Indices[hospitalIndex].second = -1;
	strcpy_s(Hospitals[hospitalPos].HospitalName, x.c_str());
	Hospitals[hospitalPos].Index = hospitalIndex;
	Hospitals[hospitalPos].HospitalID = maxHospital++;
}

void CreateSlave(string x, int y)
{
	int hospitalPos = findHospital(y);

	if (hospitalPos != -1)
	{
		int doctorIndex = findFreeIndex();
		int doctorPos = findFreeDoctor();
		int hospitalIndex = Hospitals[hospitalPos].Index;
		Indices[doctorIndex].first = doctorPos;
		Indices[doctorIndex].second = Indices[hospitalIndex].second;
		Indices[hospitalIndex].second = doctorIndex;
		Doctors[doctorPos].DoctorID = maxDoctor++;
		strcpy_s(Doctors[doctorPos].DoctorName, x.c_str());
		Doctors[doctorPos].HospitalID = y;
		Doctors[doctorPos].Index = doctorIndex;
	}
}

void DeleteMaster(int x)
{
	int hospitalPos = findHospital(x);

	if (hospitalPos == -1)
		return;

	int hospitalIndex = Hospitals[hospitalPos].Index;

	Hospitals[hospitalPos].Index = -1;
	Indices[hospitalIndex].first = -1;

	int doctorIndex = Indices[hospitalIndex].second;

	while (doctorIndex != -1)
	{
		int doctorPos = Indices[doctorIndex].first;
		Indices[doctorIndex].first = -1;
		Doctors[doctorPos].Index = -1;
		doctorIndex = Indices[doctorIndex].second;
	}
}

void DeleteSlave(int x)
{
	int doctorPos = findDoctor(x);

	if (doctorPos == -1)
		return;

	int doctorIndex = Doctors[doctorPos].Index;
	int hospitalPos = findHospital(Doctors[doctorPos].HospitalID);
	int hospitalIndex = Hospitals[hospitalPos].Index;
	
	if (Indices[hospitalIndex].second == doctorIndex)
	{
		Indices[hospitalIndex].second = Indices[doctorIndex].second;
		Indices[doctorIndex].first = -1;
	}
	else
	{
		int doctorIndex1 = Indices[hospitalIndex].second;
		int doctorPos1 = Indices[doctorIndex1].first;
		Indices[hospitalIndex].second = Indices[doctorIndex1].second;
		Doctors[doctorPos1].Index = doctorIndex;
		Indices[doctorIndex].first = doctorPos1;
	}

	Doctors[doctorPos].Index = -1;
}

string Print(Hospital x)
{
	return to_string(x.HospitalID) + space + x.HospitalName + space + to_string(x.Index) + '\n';
}

string Print(Doctor x)
{
	return to_string(x.DoctorID) + space + x.DoctorName + space + to_string(x.HospitalID) + space + to_string(x.Index) + '\n';
}

int main()
{
	ReadFiles();
	ifstream in;
	in.open(path + "input.txt");
	/*CreateMaster("FirstHospital");
	CreateMaster("SecondHospital");
	CreateSlave("DoctorFirst", 1);
	CreateMaster("ThirdHospital");
	CreateSlave("DoctorSecond", 1);
	CreateSlave("DoctorThird", 2);*/

	while (true)
	{
		string command, Data;
		in >> command;
		cout << "----------------------------------------------------------" << endl << command << endl;
		int HospitalID, DoctorID, DoctorPos, HospitalPos, DoctorIndex;

		if (command == "stop")
		{
			break;
		}
		else if (command == "get-s")
		{
			in >> DoctorID;
			DoctorPos = findDoctor(DoctorID);

			if (DoctorPos < 0)
				cout << "Wrong ID\n";
			else
			{
				Doctor d = Doctors[DoctorPos];

				cout << doctorHead;
				cout << Print(d);
			}
		}
		else if (command == "get-m")
		{
			in >> HospitalID;
			HospitalPos = findHospital(HospitalID);

			if (HospitalPos < 0)
				cout << "Wrong ID\n";
			else
			{
				Hospital h = Hospitals[findHospital(HospitalID)];

				cout << hospitalHead;
				cout << Print(h);
				cout << doctorHead;
				DoctorIndex = Indices[h.Index].second;

				while (DoctorIndex >= 0)
				{
					cout << Print(Doctors[Indices[DoctorIndex].first]);
					DoctorIndex = Indices[DoctorIndex].second;
				}
			}
		}
		else if (command == "del-s")
		{
			in >> DoctorID;
			DeleteSlave(DoctorID);
		}
		else if (command == "del-m")
		{
			in >> HospitalID;
			DeleteMaster(HospitalID);
		}
		else if (command == "update-s")
		{
			in >> DoctorID >> Data;
			DoctorPos = findDoctor(DoctorID);

			if (DoctorPos < 0)
				cout << "Wrong ID\n";
			else
				strcpy_s(Doctors[DoctorPos].DoctorName, Data.c_str());
		}
		else if (command == "update-m")
		{
			in >> HospitalID >> Data;
			HospitalPos = findHospital(HospitalID);

			if (HospitalPos < 0)
				cout << "Wrong ID\n";
			else
				strcpy_s(Hospitals[HospitalPos].HospitalName, Data.c_str());
		}
		else if (command == "insert-s")
		{
			in >> Data >> HospitalID;

			if (findHospital(HospitalID) < 0)
				cout << "Wrong ID\n";
			else
				CreateSlave(Data, HospitalID);
		}
		else if (command == "insert-m")
		{
			in >> Data;

			CreateMaster(Data);
		}
		else if (command == "calc-s")
		{
			int globalCount = 0;

			for (int i = 0; i < Hospitals.size(); ++i)
			{
				if (Hospitals[i].Index >= 0)
				{
					cout << "Hospital ID: " << Hospitals[i].HospitalID;

					DoctorIndex = Indices[Hospitals[i].Index].second;
					int count = 0;

					while (DoctorIndex >= 0)
					{
						DoctorIndex = Indices[DoctorIndex].second;
						++count;
					}

					globalCount += count;
					cout << " " << count << " slave entries\n";
				}
			}

			cout << globalCount << " active slave entries total\n";
		}
		else if (command == "calc-m")
		{
			int count = 0;

			for (int i = 0; i < Hospitals.size(); ++i)
				if (Hospitals[i].Index >= 0)
					++count;

			cout << count << " active master entries total\n";
		}
		else if (command == "ut-s")
		{
			WriteFiles();
			cout << doctorHead;

			for (Doctor d : Doctors)
			{
				cout << d.DoctorID << ' ' << d.DoctorName << ' ' << d.HospitalID << ' ' << d.Index << endl;
			}
		}
		else if (command == "ut-m")
		{
			WriteFiles();
			cout << hospitalHead;

			for (Hospital h : Hospitals)
			{
				cout << h.HospitalID << ' ' << h.HospitalName << ' ' << h.Index << endl;
			}
		}
	}

	in.close();
	WriteFiles();
}