#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Course
{
private:
	string title;
	string dayOfWeek;
	string roomNum;
	string teacher;

	int crn;
	int section;
	int capacity;
	int roomPriority;
	int timePriority;
	int startTime;
	int endTime;
	int startDate;
	int endDate;

	//Room *RoomPtr;

	//TimeInfo *ptrTime;

	//CommonInfo *ptrInfo;
	//
public:

	Course( )
	{
		title = "null";

		crn = -1;
		section = -1;
		capacity = -1;
		roomPriority = -1;
		timePriority = -1;
	}


	void setTitle( string cT );

	void setCrn( int courseReferenceNum );

	void setSection( int cS );


	void setCapacity( int cap );

	void setRoomPriority( int rP );

	void setTimePriority( int tP );


	
	string getTitle( );

	int getCrn( );

	int getSection( );


	int getCapacity( );

	int getRoomPriority( );

	int setTimePriority( );

	int findRoom( )
	{
		//*RoomPtr;
	}

	void fileReadIn( )
	{
		ifstream infile;
		string line;
		string word;
		int x;
		int row = 0;
		int column = 0;

		infile.open( "MasterFile.csv" );

		//while ( !infile.eof( ) )			// The first loop for getting the rows from the file.
		//{
			getline( infile, line, '\n' );

			//		cout << line << endl << endl; // For testing purposes.

			for ( int i = 0; i < 15; i++ )	// The second loop for parcing through to the correct data.
			{
				x = line.find( ',' );
				if ( x != string::npos )
				{
					word = line.substr( 0, x );
					if ( i == 0 )
					{
						column = 0;
						cout << word << endl;
						crn = stringToInt( word );
					}

					else if ( i == 3 )
					{
						column = 2;
						cout << word << endl;
						section = stringToInt( word );
					}
					else if ( i == 4 )
					{
						column = 3;
						cout << word << endl;
						title = word;
					}
					else if ( i == 6 )
					{
						column = 4;
						cout << word << endl;
						dayOfWeek = stringToInt( word );
					}
					else if ( i == 7 )
					{
						column = 1;
						cout << word << endl;
						startTime = stringToInt( word );
					}
					else if ( i == 8 )
					{
						column = 1;
						cout << word << endl;
						endTime = stringToInt( word );
					}
					else if ( i == 9 )
					{
						column = 1;
						cout << word << endl;
						roomNum = word;
					}
					else if ( i == 10 )
					{
						column = 1;
						cout << word << endl;
						startDate = stringToInt( word );
					}
					else if ( i == 11 )
					{
						column = 1;
						cout << word << endl;
						teacher = word;
					}

					//wordArray[row][column] = word;
					//					cout << word << endl;					// For testing purposes.
					//					cout << line.length( ) << endl << endl
					line = line.substr( x + 1, line.length( ) );
				}
			}
			cout << "New line. " << endl << endl;

			row++;
		//}
	}
};

int main( )
{
	Course course1;

	cout << course1.getTitle( ) << endl;

	course1.setTitle( "hi" );

	cout << course1.getTitle( ) << endl << endl;

	course1.fileReadIn();

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
void Course::setSection( int cS )
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
int Course::getSection( )
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
