//Sam Scheuerman, Kyle Dickens, Josh Penrod
//Room Scheduling Reading & Parsing Pt1
//Due: 3/30/18
//The portion of code for reading in all pertinent elements about a course from a file and storing them in appropriate, memory efficient, objects.

#pragma once
#include <iostream>
#include <string>
#include "CommonInfo.h"
using namespace std;

//CommonCapsule: class for non-recursive search and delete methods for CommonInfo linked list
class CommonCapsule
{
private:
	CommonInfo * head;// first element of the linked list
	int numNodes;// the number of new nodes created
public:
	//Getters
	CommonInfo* getHead( )
	{
		return head;
	}
	int getNumNodes( )
	{
		return numNodes;
	}
	//Setters
	void setHead( string prefix, int CRS, string title, int credits, int capacity )
	{
		head = new CommonInfo( prefix, CRS, title, credits, capacity );
		numNodes = 1;
	}
	void setNumNodes (int numNodesSetter )
	{
		numNodes = numNodesSetter;
	}

	//Default Constructor
	CommonCapsule( )
	{
		head = nullptr;
		numNodes = 0;
	}
	//Overloaded Constructor
	CommonCapsule( string prefix, int CRS, string title, int credits, int capacity )
	{
		head = new CommonInfo( prefix, CRS, title, credits, capacity );
		numNodes = 1;
	}
	//Default Destructor
	~CommonCapsule( )
	{
		deleteAll( );
	}

	CommonInfo *setCommon( string prefix, int CRS, string title, int credits, int capacity );// checks if a new node is needed 
	void deleteAll( );// deletes linked list
};