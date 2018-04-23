#pragma once
#include <string>

/***********************************
Documentation:

Necessary Variables:
-Any commonly overlapping data
-Full indicator (unless a method solves this process a different way)
Necessary methods:
-Check a string array of data against stored members, return bool
-Fill all data members with string array
-Check if the object has been filled, return bool
************************************/

using namespace std;

const enum COURSEPOSITION { CRN, PREFIX, COURSE, SECTION, TITLE, CREDITS, DAYS, STARTTIME, ENDTIME, PREFROOM, CAP, SDATE, EDATE, TEACHER };

class Common
{
private:
	string title;
	string prefix;
	int course;
	bool full;
public:
	Common( )
	{
		title = "";
		prefix = "";
		course = 0;
		full = false;
	}

		//Fills all variables from input string array
	void fill( string input[ ] )
	{
		title = input[TITLE];
		prefix = input[PREFIX];
		course = atoi( input[COURSE].c_str( ) );
		full = true;
	}

		//Compares object to string array of data, returns true of identical
	bool isSame( string compare[ ] )
	{
		bool toReturn = false;
		int compcourse = atoi( compare[COURSE].c_str( ) );
		if ( title == compare[TITLE] && prefix == compare[PREFIX] && course == compcourse )
		{
			toReturn = true;
		}
		return toReturn;
	}

		//Checks if Common is full, should be replaced w/ check if title is empty
	bool isFull( )
	{
		return full;
	}
};