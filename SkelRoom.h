#pragma once
#include <string>

/*******************************
Documentation:

Necessary Variables:
-Relevant room information from source file
-Index corresponding to set of assigned CRN's in scheduler
Necessary Methods:
-Way of accessing roomnum(getter) and later equipment
-Ability to set index using int
-Method to fill all variables from a string array
****************************/

using namespace std;

	//Name of all headings in source file, to facilitate easier referencing within code
const enum ROOMPOSITION { CAMPUSSISKEY, CAMPUS, BUILDINGSISKEY, BUILDINGNAME, BUILDINGCODE, ROOMSISKEY, ROOMNAME, ROOMNUMBER, ROOMTYPE, CONFIGURATIONSISKEY, CONFIGURATIONNAME, CONFIGURATIONISDEFAULT, FACILITYLAYOUTSISKEY, FACILITYLAYOUTNAME, CAPACITY, FEATUREQUANTITY, REGIONNAME };

class Room
{
private:
	string roomnum;
	int index;
public:
	Room( )
	{
		roomnum = "";
		index = 1337;
	}

	string getRoom( )
	{
		return roomnum;
	}

		//Index is column in schedule where related classes are stored
	void setIndex( int index )
	{
		this->index = index;
	}

		//Fills with string array
	void fill( string input[ ] )
	{
		roomnum = input[ROOMNUMBER];
	}
};