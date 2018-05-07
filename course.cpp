// MICAH HAAS
#include <iostream>
#include <string>
#include <fstream>
#include "Time.h"
#include "Common.h"

using namespace std;
const int COURSE_ARR_MAX = 750;

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

	Common* commonPtr;

	Time classTime;

	
public:

	Course( ) // Default constructor.
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

	Common* getPtr( ) { return commonPtr; };

	// Prototypes for the getters and setters.

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

	void setTime( Time set )
	{
		classTime = set;
	}

	Time getTime( )
	{
		return classTime;
	}

	friend Common* searchCommon( Common array[ ], string crs, string prefix );

	friend void fileReadIn( Course classArray[ ], Common commonArray[ ] );

	friend ostream &operator<< ( ostream &stream, Course print )
	{
		stream << "CRN is: " << print.crn << endl;
		stream << "Prefix is: " << print.commonPtr->getPrefix() << endl;
		stream << "CRS is: " << print.commonPtr->getCrs() << endl;
		stream << "Title is: " << print.commonPtr->getTitle() << endl;
		stream << "Number of Credits are: " << print.commonPtr->getCredits() << endl;
		stream << "Section Number is: " << print.section << endl;
		stream << "Room Number is: " << print.roomNum << endl;
		stream << "Teacher is: " << print.teacherFN << " " << print.teacherLN << endl;
		stream << "Capacity is: " << print.capacity << endl;
		stream << print.classTime << endl;

		return stream;
	}

};

string getNextStringVal( string line, int x );

/*
This funtion creates a pointer in each course to the common data for that course.
*/
Common* searchCommon( Common array[ ], string crs, string prefix )
{
	for ( int i = 0; i < 750; i++ )
	{
		string s1 = array[i].getCrs( );
		string s2 = array[i].getPrefix( );
		if ( s2 == "ENG" )
		{
			int j = 1;
		}
		if ( array[i].getCrs( ) == crs && array[i].getPrefix( ) == prefix )
		{
			return &array[i];
		}
	}
	return nullptr;
}


/*
This function reads-in the data from the file and parses the file into the 
proper data members.
*/
void fileReadIn( Course classArrayC[ ], Common commonArray[ ] )
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
	string prefix;
	string crs;


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
		classArrayC[row].crn = atoi( word.c_str( ) );
		line = line.substr( x + 1, line.length( ) );

		// prefix
		x = line.find( ',' );
		prefix = getNextStringVal( line, x );
		line = line.substr( x + 1, line.length( ) );

		// CRS
		x = line.find( ',' );
		crs = getNextStringVal( line, x );
		line = line.substr( x + 1, line.length( ) );


		// SECTION NUMBER
		x = line.find( ',' );
		word = getNextStringVal( line, x );
		classArrayC[row].section = word;
		line = line.substr( x + 1, line.length( ) );

		// SKIP
		x = line.find( ',' );
		line = line.substr( x + 1, line.length( ) );

		// SKIP
		x = line.find( ',' );
		line = line.substr( x + 1, line.length( ) );

		// DAYS OF WEEK
		x = line.find( ',' );
		word = getNextStringVal( line, x );
		dayOfWeek = word;
		line = line.substr( x + 1, line.length( ) );

		// START TIME
		x = line.find( ',' );
		word = getNextStringVal( line, x );
		startTime = word;
		line = line.substr( x + 1, line.length( ) );

		// END TIME
		x = line.find( ',' );
		word = getNextStringVal( line, x );
		endTime = word;
		line = line.substr( x + 1, line.length( ) );

		// ROOM NUMBER
		x = line.find( ',' );
		word = getNextStringVal( line, x );
		classArrayC[row].roomNum = word;
		line = line.substr( x + 1, line.length( ) );

		// CAPACITY
		x = line.find( ',' );
		word = getNextStringVal( line, x );
		classArrayC[row].capacity = atoi( word.c_str( ) );
		line = line.substr( x + 1, line.length( ) );

		// START DATE
		x = line.find( ',' );
		word = getNextStringVal( line, x );
		startDate = word;
		line = line.substr( x + 1, line.length( ) );

		// END DATE
		x = line.find( ',' );
		word = getNextStringVal( line, x );
		endDate = word;
		line = line.substr( x + 1, line.length( ) );

		// TEACHER LAST NAME
		x = line.find( ',' );
		word = getNextStringVal( line, x );
		classArrayC[row].teacherLN = word;
		line = line.substr( x + 1, line.length( ) );

		// TEACHER FIRST NAME
		classArrayC[row].teacherFN = line;

		classArrayC[row].classTime.setAll( dayOfWeek, startTime, endTime, startDate, endDate );


		classArrayC[row].commonPtr = searchCommon( commonArray, crs, prefix );
		
		//printf( "row=%ds ", row );
		//printf( "title=%s ", classArrayC[row].commonPtr->getTitle( ).c_str( ) );

		row++;
		getline( infile, line, '\n' );

	}

}

/*
This function is used as the file is being read-in to find and erase 
white spaces in order for the .compare function to work.
*/
string getNextStringVal( string line, int x )
{
	string s = line.substr( 0, x );
	int l = s.length( );
	char c = s.at( s.length( )-1 );
	while ( s.at( s.length( )-1) == ' ' )
	{
		s = s.substr( 0, s.length( ) - 1 );
	}
	return s;
}

void printCourse( Course arr[ ] )						// Used to print out all of the course info 
{														// for all courses.
	for ( int i = 0; i < 707; i++ )
	{
		//printf( "i=%d ", i);												// For debugging purposes.
		//printf( "title=%s ", arr[i].getPtr()->getTitle( ).c_str( ) );
		cout << "Line: " << i << endl;
		cout << arr[i] << endl;
	}
}

int main( )
{

	Course classArray[750];

	Common commonArray[750];

	Common::fillCommon( commonArray );

	fileReadIn( classArray, commonArray );

	printCourse( classArray );

	cout << "**************DONE**************" << endl;

	cout << classArray[0] << endl << endl;

	cout << classArray[706] << endl;


	system( "pause" );
	return 0;
}

// Getters and setters. 

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
