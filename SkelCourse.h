#pragma once
#include <iostream>
#include <string>
#include "SkelCommon.h"
#include "SkelTime.h"

/*****************************
Documentation:

Necessary variables:
-Relevant unique data from source file
-Pointer to linked Course (or other data member that can show connection)
-Bool showing if a link exists (or other method of addressing this issue)
-Link to common information not unique to Course (pointer or other, as above)
Necessary methods:
-Setters/Getters
-Method to fill all variables from input string array
-Method to check if object has a linked object, return bool
-Method to check for conflict with another object, return bool
**************************************/

using namespace std;

class Course
{
private:
	int crn;
	string prefroom;
	int roomindex;
	Time time;

	Course *link;
	int linkindex;			//Not currently implemented (idea is to schedule both at once)
	Common *common;
	bool haslink;
public:
	Course( )
	{
		crn = 0;
		prefroom = "";
		link = nullptr;
		linkindex = 1337;
		common = nullptr;
		haslink = false;
		roomindex = 1337;
	}

	int getCRN( )
	{
		return crn;
	}

	string getRoom( )
	{
		return prefroom;
	}

	Course* getLink( )
	{
		return link;
	}

	void setLink( Course* link, int index )
	{
		this->link = link;
		linkindex = index;
		haslink = true;
	}

	void setCommon( Common* common )
	{
		this->common = common;
	}

	void setIndex( int index )
	{
		roomindex = index;
	}

		//Fills from string array
	void fill( string input[ ] )
	{
		crn = atoi( input[CRN].c_str( ) );
		prefroom = input[PREFROOM];
		int stime = atoi( input[STARTTIME].c_str( ) );
		int etime = atoi( input[ENDTIME].c_str( ) );
		time.setAll( input[SDATE], input[EDATE], stime, etime, input[DAYS] );
	}

		//Checks if object linked to another object
	bool hasLink( )
	{
		return haslink;
	}

		//Checks for conflict w/ another object
	bool conflictCheck( Course toCompare )
	{
		bool toReturn = time.checkForConflict( toCompare.time );
		return toReturn;
	}
};