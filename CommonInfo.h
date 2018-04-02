//Sam Scheuerman, Kyle Dickens, Josh Penrod
//Room Scheduling Reading & Parsing Pt1
//Due: 3/30/18
//The portion of code for reading in all pertinent elements about a course from a file and storing them in appropriate, memory efficient, objects.

#pragma once
#include <string>
#include <iostream>
using namespace std;

//CommonInfo: Contains all members that could be shared between courses as well as appropriate methods for filling and testing.
class CommonInfo
{
private:
	string prefix;// 3 character course prefix: CSC, CNG, MAT, etc...
	int CRS;// CRS Course Number: 101, 119, 234, etc...
	string title;// Course's full title
	int credits;// How many credits the Course is worth
	int capacity;// How many people can be taught in one Class
	CommonInfo * next;// link for next element in linked list

public:
	//Getters
	string getPrefix( )
	{
		return prefix;
	}
	int getCRS( )
	{
		return CRS;
	}
	string getTitle( )
	{
		return title;
	}
	int getCredits( )
	{
		return credits;
	}
	int getCapacity( )
	{
		return capacity;
	}
	CommonInfo *getNext( )
	{
		return next;
	}
	//Setters
	void setPrefix(string prefixSetter )
	{
		prefix = prefixSetter;
	}
	void setCRS(int CRSSetter )
	{
		CRS = CRSSetter;
	}
	void setTitle(string titleSetter )
	{
		title = titleSetter;
	}
	void setCredits(int creditsSetter )
	{
		credits = creditsSetter;
	}
	void setCapacity(int capacitySetter )
	{
		capacity = capacitySetter;
	}
	void setNext( CommonInfo *next )
	{
		this->next = next;
	}
	
	//Default Constructor
	CommonInfo( )
	{
		CRS = 0;
		prefix = "";
		title = "";
		next = nullptr;
	}
	//Overloaded Constructor
	CommonInfo(  string prefix, int CRS, string title, int credits, int capacity )
	{
		this->CRS = CRS;
		this->prefix = prefix;
		this->title = title;
		this->credits = credits;
		this->capacity = capacity;
		next = nullptr;
	}
	
	void setAll( string prefix, int CRS, string title, int credits, int capacity );// changes all current object values to passed in ones

	bool isSame( string prefix, int CRS, string title, int credits, int capacity );// checks if CommonInfo matches

	friend ostream &operator<<( ostream &stream, CommonInfo *toOutput );//Overloaded output operator for testing
};


