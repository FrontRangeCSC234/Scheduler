//Sam Scheuerman, Kyle Dickens, Josh Penrod
//Room Scheduling Reading & Parsing Pt1
//Due: 3/30/18
//The portion of code for reading in all pertinent elements about a course from a file and storing them in appropriate, memory efficient, objects.

#include <string>
#include <iostream>
#include <fstream>
#include "CourseInfo.h"
#include "CommonInfo.h"
#include "ParseInfo.h"
#include "CommonCapsule.h"
using namespace std;

const int MAX = 2500;// Maximum number of lines that will be read in.

//AllData: Infrastructure for reading in, parsing, and storing data in their relevant classes as well as output and checking for linked classes (Same CRN).
class AllData
{
private:
	int courseInfoSize;// Number of Classes on their own line
	CourseInfo *myCourses;// Dynamic array of Classes
	CommonCapsule myCommons;// Common capsule for the implementation of non-recursive search and delete
public:
	//Getters
	int getCourseInfoSize( )
	{
		return courseInfoSize;
	}
	CourseInfo* getMyCourses( )
	{
		return myCourses;
	}
	CommonCapsule* getMyCommons( )
	{
		return &myCommons;
	}
	//Setters
	void setCourseInfoSize( int courseInfoSizeSetter )
	{
		courseInfoSize = courseInfoSizeSetter;
	}
	void setMyCourses( CourseInfo *myCoursesSetter )
	{
		myCourses = myCoursesSetter;
	}
	void setMyCommons( CommonCapsule myCommonsSetter )
	{
		myCommons = myCommonsSetter;
	}

	//Default Constructor
	AllData( )
	{
		cout << "In default constructor" << endl;
		courseInfoSize = 0;
		myCourses = nullptr;
	}
	//Default Destructor
	~AllData( )
	{
		delete[ ] myCourses;
	}

	void fill( );// fills array of CourseInfo & list of CommonInfo
	void linkCheck( );//checks for same crn
	void printContents( );//outputs contents of CommonInfo & CourseInfo
};