// MICAH HAAS
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


		crn = -1;
		capacity = -1;
		roomPriority = -1;
		timePriority = -1;

	}


	void setTitle( string cT );

	void setCrn( int courseReferenceNum );

	void setSection( string cS );


	void setCapacity( int cap );

	void setRoomPriority( int rP );

	void setTimePriority( int tP );


	
	string getTitle( );

	int getCrn( );

	string getSection( );


	int getCapacity( );

	int getRoomPriority( );

	int setTimePriority( );

	int findRoom( )
	{
		//*RoomPtr;
	}

	friend void fileReadIn( Course classArray[ ] );

	friend ostream &operator<< ( ostream &stream, Course print )
	{
		stream << "CRN is: " << print.crn << endl;
		stream << "Title is: " << print.title << endl;
		stream << "Section Number is: " << print.section << endl;
		stream << "Room Number is: " << print.roomNum << endl;
		stream << "Teacher is: " << print.teacherFN << " " << print.teacherLN << endl;
		stream << "Capacity is: " << print.capacity << endl;
		stream << print.classTime << endl;

		return stream;
	}

};

void fileReadIn( Course classArray[ ] )
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

	while ( !infile.eof( ) )			// For getting the lines from the file.
	{
		getline( infile, line, '\n' );

		//cout << line << endl << endl; // For testing purposes.

		// CRN
		x = line.find( ',' );
		if ( x < 0 )
		{
			continue;
		}
		word = line.substr( 0, x );
		classArray[row].crn = atoi( word.c_str( ) );
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

		// CLASS TITLE
		x = line.find( ',' );
		word = line.substr( 0, x );
		classArray[row].title = word;
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
	}
}

void print( Course arr[ ] )
{
	for ( int i = 0; i < COURSE_ARR_MAX; i++ )
	{
		cout << arr[i] << endl;
	}
}

int main( )
{

	Course classArray[707];


	fileReadIn( classArray );

	print( classArray );

	cout << "**************DONE**************" << endl;

	cout << classArray[0] << endl << endl;

	cout << classArray[706] << endl;

	system( "pause" );
	return 0;
}


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
