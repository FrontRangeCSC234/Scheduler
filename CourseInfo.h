//Sam Scheuerman, Kyle Dickens, Josh Penrod
//Room Scheduling Reading & Parsing Pt1
//Due: 3/30/18
//The portion of code for reading in all pertinent elements about a course from a file and storing them in appropriate, memory efficient, objects.	

#pragma once
#include <string>
#include <iostream>
#include "ParseInfo.h"
#include "CommonInfo.h"
using namespace std;

//CourseInfo: Contains all members that would be unique to each course as well as appropriate methods for filling and testing.
class CourseInfo
{
private:
	int CRN;// 5 digit course reference number
	int section;// 3 digit section: 601,602, etc...
	string days;// Days of week class meets
	int startT;// Military time class start time
	int endT;// Military time class end time
	string prefRoom;// The preferred room if any room listed on file 
	string startD;// Day of year class starts (int?)
	string endD;// Day of year class ends (int?)
	CommonInfo *myCommons;// link to correct element in linked list of CommonInfo
	CourseInfo *link;// link to element of CourseInfo for CRN comparison
public:
	//Getters
	int getCRN ( )
	{
		return CRN;
	}
	int getSection( )
	{
		return section;
	}
	string getDays( )
	{
		return days;
	}
	int getStartT( )
	{ 
		return startT;
	}
	int getEndT( )
	{
		return endT;
	}
	string getPrefRoom( )
	{
		return prefRoom;
	}
	string getStartD( )
	{
		return startD;
	}
	string getEndD( )
	{
		return endD;
	}
	CommonInfo* getMyCommons( )
	{
		return myCommons;
	}
	CourseInfo* getLink( )
	{
		return link;
	}
	//Setters
	void setCrn(int CRNSetter )
	{
		CRN = CRNSetter;
	}
	void setSection(int sectionSetter )
	{
		section = sectionSetter;
	}
	void setDays( string daysSetter)
	{
		days = daysSetter;
	}
	void setStartT(int startTSetter )
	{
		startT = startTSetter;
	}
	void setEndT(int endTSetter )
	{
		endT = endTSetter;
	}
	void setPrefRoom(string prefRoomSetter )
	{
		prefRoom = prefRoomSetter;
	}
	void setStartD(string startDSetter )
	{
		startD = startDSetter;
	}
	void setEndD(string endDSetter )
	{
		endD = endDSetter;
	}
	void setMyCommons(CommonInfo* myCommonsSetter )
	{
		myCommons = myCommonsSetter;
	}
	void setLink(CourseInfo* linkSetter )
	{
		link = linkSetter;
	}

	//Default Constructor
	CourseInfo( )
	{
		CRN = -1;
		section = -1;
		days = "NULL";
		startT = -1;
		endT = -1;		
		prefRoom = "NULL";
		startD = "NULL";
		endD = "NULL";
	}

	void setAllValues( string rawInput[16], ParseInfo &parser, CommonInfo *link );//sets all members to passed in value
	void checkForLink( CourseInfo toCompare );// checks for same CRN
	friend ostream &operator<<( ostream &stream, CourseInfo toOutput );//Overloaded output operator for testing
};
