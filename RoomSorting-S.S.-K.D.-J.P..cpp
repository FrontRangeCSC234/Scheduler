//Sam Scheuerman, Kyle Dickens, Josh Penrod
//Room Scheduling Reading & Parsing Pt1
//Due: 3/30/18
//The portion of code for reading in all pertinent elements about a course from a file and storing them in appropriate, memory efficient, objects.

#include "AllData.h"
using namespace std;

int main( )
{
	AllData myData;
	myData.fill( );
	myData.linkCheck( );
	myData.printContents( );
	cout << "Everything output above comes from the objects that data has been read into, and not just output from the file." << endl;	
	cout << "Number of CourseInfo Objects (Unique): " << myData.getCourseInfoSize( )-1 << endl;
	cout << "Number of CommonInfo Objects (General): " << myData.getMyCommons( )->getNumNodes( ) << endl;

	cout << endl;
	system( "pause" );
	return 0;
}

//fill: reads, parses, and passes correct data onto CommonInfo & CourseInfo
void AllData:: fill( )
{
	string rawCourseData[MAX];// whole file in one array
	string myArray[16];// one line of file split into 16 element array
	ParseInfo parser;// object of ParseInfo class for splitting apart file and converting from string to int
	CommonInfo *link;// pointer for passing link from 
	int CRS, CRN, section, credits, startT, endT, capacity;// All elements that will need to be converted from string to int to be stored

	ifstream getcourseinfo;
	getcourseinfo.open( "201930 Natural Science First Draft.csv" );
	getline( getcourseinfo, rawCourseData[courseInfoSize] );
	while ( !getcourseinfo.fail( ) && courseInfoSize < MAX )
	{
		courseInfoSize++;
		getline( getcourseinfo, rawCourseData[courseInfoSize] );
	}
	//Reading in and storing 1st element
	myCourses = new CourseInfo[courseInfoSize];
	parser.parseAll( myArray, rawCourseData[1] );
	CRS = parser.stringToNumber( myArray[2] );
	CRN = parser.stringToNumber( myArray[0] );
	section = parser.stringToNumber( myArray[3] );
	credits = parser.stringToNumber( myArray[5] );
	startT = parser.stringToNumber( myArray[7] );
	endT = parser.stringToNumber( myArray[8] );
	capacity = parser.stringToNumber( myArray[11] );
	myCommons.setHead( myArray[1], CRS, myArray[4], credits, capacity );
	link = myCommons.setCommon( myArray[1], CRS, myArray[4], credits, capacity );
	myCourses[0].setAllValues( myArray, parser, link );
	//Reading in and storing rest of file
	for ( int i = 1; i < courseInfoSize - 1; i++ )
	{
		parser.parseAll( myArray, rawCourseData[i + 1] );
		CRS = parser.stringToNumber( myArray[2] );
		CRN = parser.stringToNumber( myArray[0] );
		section = parser.stringToNumber( myArray[3] );
		credits = parser.stringToNumber( myArray[5] );
		startT = parser.stringToNumber( myArray[7] );
		endT = parser.stringToNumber( myArray[8] );
		capacity = parser.stringToNumber( myArray[11] );
		link = myCommons.setCommon( myArray[1], CRS, myArray[4], credits, capacity );
		myCourses[i].setAllValues( myArray, parser, link );
	}

}

//linkCheck: calls function to check if CRN is the same
void AllData:: linkCheck( )
{
	for ( int i = 0; i < courseInfoSize - 2; i++ )
	{
		myCourses[i].checkForLink( myCourses[i + 1] );
	}
}

//printContents: uses overloaded operators in CommonInfo & CourseInfo to output contents of objects
void AllData::printContents( )
{
	for ( int i = 0; i < courseInfoSize - 1; i++ )
	{
		cout << myCourses[i];
	}
}

//setAllValues: sets all values in an object of CourseInfo to a real value read in from the file
//rawInput[]: a single line read in from the file
//parser: object of ParseInfo used for it's stringToNumber method
//link: address established in AllData that links to the appropriate member of CommonInfo
void CourseInfo::setAllValues( string rawInput[16], ParseInfo &parser, CommonInfo *link )
{
	CRN = parser.stringToNumber( rawInput[0] );
	section = parser.stringToNumber( rawInput[3] );
	days = rawInput[6];
	startT = parser.stringToNumber( rawInput[7] );
	endT = parser.stringToNumber( rawInput[8] );
	prefRoom = rawInput[10];
	startD = rawInput[12];
	endD = rawInput[13];
	myCommons = link;
}

//checkForLink: checks if two objects have the same CRN, useful for connecting a lecture/lab class
//toCompare: the other object of CourseInfo besides the one that checkForLink is called from
void CourseInfo::checkForLink( CourseInfo toCompare )
{
	if ( CRN == toCompare.CRN )
	{
		link = &toCompare;
	}
}

//Overloaded CourseInfo output operator for testing
ostream &operator<<( ostream &stream, CourseInfo toOutput )
{
	stream << "CRN: " << toOutput.CRN << endl;
	stream << "Section: " << toOutput.section << endl;
	stream << "Days: " << toOutput.days << endl;
	stream << "Start Time: " << toOutput.startT << endl;
	stream << "End Time: " << toOutput.endT << endl;
	stream << "Preferred Room: " << toOutput.prefRoom << endl;
	stream << "Start Date: " << toOutput.startD << endl;
	stream << "End Date: " << toOutput.endD << endl;
	stream << toOutput.myCommons << endl;
	return stream;
}

//setAll: takes in all values in the common info class except for next and changes the ones in the current object to the passed in values
//prefix: 3 character course prefix: CSC, CNG, MAT, etc..
//CRS: Course Number: 101, 119, 234, etc...
//Title: Course's full title
//credits: How many credits the Course is worth
//capacity: How many people can be taught in one Class
void CommonInfo::setAll( string prefix, int CRS, string title, int credits, int capacity )
{
	this->CRS = CRS;
	this->prefix = prefix;
	this->title = title;
	this->credits = credits;
	this->capacity = capacity;

}

//isSame: takes in all members of CommonInfo and checks if they are identical. Returns true if they are the same, otherwise false.
//prefix: 3 character course prefix: CSC, CNG, MAT, etc..
//CRS: Course Number: 101, 119, 234, etc...
//Title: Course's full title
//credits: How many credits the Course is worth
//capacity: How many people can be taught in one Class
bool CommonInfo::isSame( string prefix, int CRS, string title, int credits, int capacity )
{
	bool toReturn;// return value
	if ( this->CRS == CRS && this->prefix == prefix && this->title == title && this->credits == credits && this->capacity == capacity )
	{
		toReturn = true;
	}
	else
	{
		toReturn = false;
	}
	return toReturn;
}

//Overloaded CommonInfo output operator for testing
ostream &operator<<( ostream &stream, CommonInfo *toOutput )
{
	stream << "Prefix: " << toOutput->prefix << endl;
	stream << "CRS: " << toOutput->CRS << endl;
	stream << "Title: " << toOutput->title << endl;
	stream << "Credits: " << toOutput->credits << endl;
	stream << "Capacity: " << toOutput->capacity << endl;
	return stream;
}

//parseAll: takes in a raw string and parses it into a 16 position array based off of a comma delimeter
//target[]: array for holding all elements of a line seperately
//rawInput: the complete string before being pulled apart
void ParseInfo::parseAll( string target[16], string rawInput )
{
	if ( rawInput[0] == ',' )
	{
		return;
	}
	for ( int i = 0; i < 16; i++ )
	{
		target[i] = "";
	}
	int position = 0;
	for ( int i = 0; i < rawInput.size( ) && position<16; i++ )
	{
		if ( rawInput[i] == ',' )
		{
			position++;
		}
		else
		{
			target[position] += rawInput[i];
		}
	}
}

//stringToNumber: an alpha to numeric conversion utilized for all elements read in that need to be stored as ints
//rawInput: string to be converted to int
int ParseInfo::stringToNumber( string rawInput )
{
	return atoi( rawInput.c_str( ) );
}

//setCommon: checks if a new node of the Common Info linked list is needed or if a correct element already exists. Returns link to new or existing node
//prefix: 3 character course prefix: CSC, CNG, MAT, etc..
//CRS: Course Number: 101, 119, 234, etc...
//Title: Course's full title
//credits: How many credits the Course is worth
//capacity: How many people can be taught in one Class
CommonInfo * CommonCapsule::setCommon( string prefix, int CRS, string title, int credits, int capacity )
{

	CommonInfo *cur = head;
	CommonInfo *toReturn = nullptr;
	CommonInfo *next = nullptr;
	while ( cur )
	{
		next = cur->getNext( );
		if ( cur->isSame( prefix, CRS, title, credits, capacity ) )
		{
			toReturn = cur;
			break;
		}
		else if ( next == nullptr )
		{
			next = new CommonInfo( prefix, CRS, title, credits, capacity );
			cur->setNext( next );
			toReturn = next;
			numNodes++;
			break;
		}
		else
		{
			cur = next;
		}
	}
	return toReturn;
}

//deleteAll: deletes all elements of the CommonInfo linked list
void CommonCapsule::deleteAll( )
{
	CommonInfo *cur = head;
	while ( cur )
	{
		head = head->getNext( );
		delete cur;
		cur = head;
	}
}