#pragma once
// MICAH HAAS
// Edits and additions by Kyle Dickens, 4/27/18 12:46 AM
#include <iostream>
#include <string>
#include <fstream>
#include "Time.h"

using namespace std;
const int COURSE_ARR_MAX = 707;

class Course
{
private:
	string title;
	string roomNum;
	string teacherFN;
	string teacherLN;
	string section;

	int crn;
	int capacity;
	int roomPriority;
	int timePriority;

	Time classTime;

	Course* linked;

	//Room *RoomPtr;

	//TimeInfo *ptrTime;

	//CommonInfo *ptrInfo;
	//
public:

	Course( )
	{
		title = "null";
		roomNum = "null";
		teacherFN = "null";
		teacherLN = "null";
		section = "null";

		linked = nullptr;


		crn = -1;
		capacity = -1;
		roomPriority = -1;
		timePriority = -1;

	}

	//Kyle Dickens, added for Sam S.
	//Checks for a time conflict between the two courses. Will also check linked courses if need be.
	//Edit: most of it commented out cause Sam S. is positive it will break his stuff, and I haven't had a chance to look at the interactions.
	bool conflictCheck(Course toCompare)
	{
		//if (linked == nullptr && toCompare.linked == nullptr)
		//{
			return classTime.checkForConflict(toCompare.classTime);
		//}
		//else
		//{
		//	bool check = false;
		//	if (linked != nullptr)
		//	{
		//		if (classTime.checkForConflict(toCompare.classTime) || linked->classTime.checkForConflict(toCompare.classTime))
		//		{
		//			check = true;
		//		}
		//		if (toCompare.linked != nullptr)
		//		{
		//			if (classTime.checkForConflict(toCompare.linked->classTime) || linked->classTime.checkForConflict(toCompare.linked->classTime))
		//			{
		//				check = true;
		//			}
		//		}
		//	}
		//	return check;
		//}
	}


	void setTitle( string cT );

	void setCrn( int courseReferenceNum );

	void setSection( string cS );

	//Kyle Dickens, getters and Setters for RoomNum, TeacherLN, and Teacher FN
	void setRoomNum(string rmNm)
	{
		roomNum = rmNm;
	}
	string getRoomNum()
	{
		return roomNum;
	}
	void setTeacherLN(string word)
	{
		teacherLN = word;
	}
	string getTeacherLN()
	{
		return teacherLN;
	}
	void setTeacherFN(string word)
	{
		teacherFN = word;
	}
	string getTeacherFN()
	{
		return teacherFN;
	}


	void setCapacity( int cap );

	void setRoomPriority( int rP );

	void setTimePriority( int tP );

	//Kyle Dickens, getters and setters for *classTime, and *linked
	Time* getClassTimePtr()
	{
		return &classTime;
	}
	void setClassTimePtr(Time ptr)
	{
		classTime = ptr;
	}
	Course* getLinked()
	{
		return linked;
	}
	void setLinked(Course* ptr)
	{
		linked = ptr;
	}

	
	string getTitle( );

	int getCrn( );

	string getSection( );


	int getCapacity( );

	int getRoomPriority( );

	int setTimePriority( );


	friend void courseFileReadIn( Course classArray[ ] );

	friend ostream &operator<< ( ostream &stream, Course print )
	{
		stream << "CRN is: " << print.crn << endl;
		stream << "Section Number is: " << print.section << endl;
		stream << "Room Number is: " << print.roomNum << endl;
		stream << "Teacher is: " << print.teacherFN << " " << print.teacherLN << endl;
		stream << "Capacity is: " << print.capacity << endl;
		stream << print.classTime << endl;

		return stream;
	}

};


/*
Kyle Dickens
Makes an array of pointers. Then makes course objects, and puts the pointer in the spot corrosponding to the course's CRN.
BOTH MUST BE DELETED AFTERWARDS!!
I modified a copy paste of courseFileReadIn by Micah Haas and much of the logic is his. Recognition where it's due.
*/
Course** coursePointerFill()
{
	Course** cArray = new Course*[10000];
	for ( int i = 0; i < 10000; i++ )
	{
		cArray[i] = nullptr;
	}

	ifstream infile;
	infile.open("MASTER.csv");
	string line;
	getline(infile, line, '\n');
	while (!infile.eof())
	{
		Course* current = new Course();
		int x;
		int row = 0;

		string word;
		string startTime;
		string endTime;
		string startDate;
		string endDate;
		string dayOfWeek;

		// CRN
		x = line.find(',');
		if (x <= 0)
		{
			continue;
		}
		word = line.substr(0, x);
		row = atoi(word.c_str());
		current->setCrn(row);
		if (cArray[(row - 60000)] == nullptr)
		{
			cArray[(row - 60000)] = current;
		}
		else
		{
			cArray[(row - 60000)]->setLinked(current);
			current->setLinked(cArray[(row - 60000)]);
		}
		
		line = line.substr(x + 1, line.length());

		// SKIP
		x = line.find(',');
		line = line.substr(x + 1, line.length());

		// SKIP
		x = line.find(',');
		line = line.substr(x + 1, line.length());

		// SECTION NUMBER
		x = line.find(',');
		word = line.substr(0, x);
		current->setSection(word);
		line = line.substr(x + 1, line.length());

		// SKIP
		x = line.find(',');
		line = line.substr(x + 1, line.length());

		// SKIP
		x = line.find(',');
		line = line.substr(x + 1, line.length());

		// DAYS OF WEEK
		x = line.find(',');
		word = line.substr(0, x);
		dayOfWeek = word;
		line = line.substr(x + 1, line.length());

		// START TIME
		x = line.find(',');
		word = line.substr(0, x);
		startTime = word;
		line = line.substr(x + 1, line.length());

		// END TIME
		x = line.find(',');
		word = line.substr(0, x);
		endTime = word;
		line = line.substr(x + 1, line.length());

		// ROOM NUMBER
		x = line.find(',');
		word = line.substr(0, x);
		current->setRoomNum(word);
		line = line.substr(x + 1, line.length());

		// CAPACITY
		x = line.find(',');
		word = line.substr(0, x);
		current->setCapacity(atoi(word.c_str()));
		line = line.substr(x + 1, line.length());

		// START DATE
		x = line.find(',');
		word = line.substr(0, x);
		startDate = word;
		line = line.substr(x + 1, line.length());

		// END DATE
		x = line.find(',');
		word = line.substr(0, x);
		endDate = word;
		line = line.substr(x + 1, line.length());

		// TEACHER LAST NAME
		x = line.find(',');
		word = line.substr(0, x);
		current->setTeacherLN(word);
		line = line.substr(x + 1, line.length());

		// TEACHER FIRST NAME
		x = line.find(',');
		word = line.substr(0, x);
		current->setTeacherFN(word);

		Time* classTime = current->getClassTimePtr();
		classTime->setAll(dayOfWeek, startTime, endTime, startDate, endDate);

		getline(infile, line, '\n');
	}

	return cArray;
}

/*
Kyle Dickens
Deletes the pointer array passed into after deleting all of the pointers inside of it, assuming the pointers are not nullptr;
*/
void deletePointerArray(Course* cArray[])
{
	for (int i = 0; i < 10000; i++)
	{
		if (cArray[i] != nullptr)
		{
			delete cArray[i];
		}
	}
	delete cArray;
}

void courseFileReadIn( Course classArray[ ] )
{
	int x;
	int row = 0;

	ifstream infile;

	string line;
	string word;
	string startTime;
	string endTime;
	string startDate;
	string endDate;
	string dayOfWeek;


	infile.open( "MASTER.csv" );
	getline( infile, line, '\n' );
	while ( !infile.eof( ) )			// For getting the lines from the file.
	{

		//cout << line << endl << endl; // For testing purposes.

		// CRN
		x = line.find( ',' );
		if ( x <= 0 )
		{
			continue;
		}
		word = line.substr( 0, x );
		classArray[row].crn = atoi(word.c_str());
		line = line.substr( x + 1, line.length( ) );

		// SKIP
		x = line.find( ',' );
		line = line.substr( x + 1, line.length( ) );

		// SKIP
		x = line.find( ',' );
		line = line.substr( x + 1, line.length( ) );

		// SECTION NUMBER
		x = line.find( ',' );
		word = line.substr( 0, x );
		classArray[row].section = word;
		line = line.substr( x + 1, line.length( ) );

		// SKIP
		x = line.find( ',' );
		line = line.substr( x + 1, line.length( ) );

		// SKIP
		x = line.find( ',' );
		line = line.substr( x + 1, line.length( ) );

		// DAYS OF WEEK
		x = line.find( ',' );
		word = line.substr( 0, x );
		dayOfWeek = word;
		line = line.substr( x + 1, line.length( ) );

		// START TIME
		x = line.find( ',' );
		word = line.substr( 0, x );
		startTime = word;
		line = line.substr( x + 1, line.length( ) );

		// END TIME
		x = line.find( ',' );
		word = line.substr( 0, x );
		endTime = word;
		line = line.substr( x + 1, line.length( ) );

		// ROOM NUMBER
		x = line.find( ',' );
		word = line.substr( 0, x );
		classArray[row].roomNum = word;
		line = line.substr( x + 1, line.length( ) );

		// CAPACITY
		x = line.find( ',' );
		word = line.substr( 0, x );
		classArray[row].capacity = atoi( word.c_str( ) );
		line = line.substr( x + 1, line.length( ) );

		// START DATE
		x = line.find( ',' );
		word = line.substr( 0, x );
		startDate = word;
		line = line.substr( x + 1, line.length( ) );

		// END DATE
		x = line.find( ',' );
		word = line.substr( 0, x );
		endDate = word;
		line = line.substr( x + 1, line.length( ) );

		// TEACHER LAST NAME
		x = line.find( ',' );
		word = line.substr( 0, x );
		classArray[row].teacherLN = word;
		line = line.substr( x + 1, line.length( ) );

		// TEACHER FIRST NAME
		classArray[row].teacherFN = line;

		classArray[row].classTime.setAll( dayOfWeek, startTime, endTime, startDate, endDate );

		row++;
		getline( infile, line, '\n' );
	}
}

int parseInt(string word)
{
	int total = 0;
	for ( int i = 0; i < word.length( ); i++ )
	{
		total += word[i];
	}
	return total;
}

void print( Course arr[ ] )
{
	for ( int i = 0; i < COURSE_ARR_MAX; i++ )
	{
		cout << "Line: " << i << endl;
		cout << arr[i] << endl;
	}
}

//int main( )
//{
//
//	Course classArray[750];
//
//
//	fileReadIn( classArray );
//
//	print( classArray );
//
//	cout << "**************DONE**************" << endl;
//
//	cout << classArray[0] << endl << endl;
//
//	cout << classArray[706] << endl;
//
//	system( "pause" );
//	return 0;
//}


void Course::setTitle( string cT )
{
	title = cT;
}
void Course::setCrn( int courseReferenceNum )
{
	crn = courseReferenceNum;
}
void Course::setSection( string cS )
{
	section = cS;
}
void Course::setCapacity( int cap )
{
	capacity = cap;
}
void Course::setRoomPriority( int rP )
{
	roomPriority = rP;
}
void Course::setTimePriority( int tP )
{
	timePriority = tP;
}



string Course::getTitle( )
{
	return title;
}
int Course::getCrn( )
{
	return crn;
}
string Course::getSection( )
{
	return section;
}
int Course::getCapacity( )
{
	return capacity;
}
int Course::getRoomPriority( )
{
	return roomPriority;
}
int Course::setTimePriority( )
{
	return timePriority;
}
