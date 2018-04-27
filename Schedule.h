#pragma once
//#include "SkelCourse.h"
//#include "Room.h"
#include "All_Included_Files.h"

/*****************************
Documentation:

Necessary variables:
-Way to organize rooms (currently string array of room numbers)
-2D array of CRN's (each column is a room)
-Possibly index array where CRN-60000 stores the objects location in the Course array
(This is currently in main, but it used both places. As a class, should decide where
is the best place for it to go)
Necessary methods:
-Way to add sections and rooms to relevant arrays (either as a single operation, or
for the entire file; both are presented here, with the entire file method
currently in use)
-Method for checking a room number against the current array
-Method to tell if a space is empty (currently, array is initialized to all 0's then
checks for 0's when scheduling)
-Method for outputing schedule, currently outputs arrays using overloaded <<
*******************************/

const int COURSEMAX = 10000;

class Schedule
{
private:
	string rooms[RMMAX];
	Course * schedule[91][RMMAX];

	Course **focus;
public:
	Schedule( )
	{
		for ( int i = 0; i < RMMAX; i++ )
		{
			rooms[i] = "NULL";
		}
		for ( int i = 0; i < 91; i++ )
		{
			for ( int j = 0; j < RMMAX; j++ )
			{
				schedule[i][j] = nullptr;
			}
		}

		focus = nullptr;
	}

	Schedule( string rmArray[RMMAX] )
	{
		for ( int i = 0; i < RMMAX; i++ )
		{
			cout << rmArray[i];
			rooms[i] = rmArray[i];
			cout << "Room added: " << rooms[i];
		}

		for ( int i = 0; i < 91; i++ )
		{
			for ( int j = 0; j < RMMAX; j++ )
			{
				schedule[i][j] = nullptr;
			}
		}

		focus = nullptr;
	}

	~Schedule( )
	{
		delete focus;
	}

	////////////////////SETTERS/////////////////////

	void setRoomArray( string rmArray[RMMAX] )
	{
		for ( int i = 0; i < RMMAX; i++ )
		{
			rooms[i] = rmArray[i];
		}
	}

	void setSchedule( Room rms[ ], Course crs[ ] )
	{
		fill( rms, crs );
	}

	void setSingleRoom( string rm, int index )
	{
		rooms[index] = rm;
	}

	void setSingleCourse( Course *crs, int row, int col )
	{
		schedule[row][col] = crs;
	}

	/////////////////////GETTERS///////////////////////////

	string getSingleRoom( int index )
	{
		return rooms[index];
	}

	Course * getCourse( int row, int col )
	{
		return schedule[row][col];
	}

	string * getRooms( )
	{
		return rooms;
	}

	void getSchedule( Course * toReturn[91][RMMAX] )
	{
		for ( int i = 0; i < 91; i++ )
		{
			for ( int j = 0; j < RMMAX; j++ )
			{
				toReturn[i][j] = schedule[i][j];
			}
		}
	}

	void getColumn( Course * toReturn[91], int index )
	{
		for ( int i = 0; i < 91; i++ )
		{
			toReturn[i] = schedule[i][index];
		}
	}

	Course * getFocusedColumn( int index )
	{
		delete focus;
		focus = new Course*[91];
		for ( int i = 0; i < 91; i++ )
		{
			focus[i] = schedule[i][index];
		}
		return *focus;
	}

	////////////////////METHODS////////////////////////////

		//Returns the index of a room in the rooms array
	int findRoom( string room )
	{
		int index = 0;						//Position in rooms string array
		while ( index < RMMAX )
		{
			if ( rooms[index] == "NULL" )
			{
				rooms[index] = room;
				return index;
			}
			else if ( rooms[index] == room )
			{
				return index;
			}
			else
			{
				index++;
			}
		}
		cout << "Error when trying to find room " << room << endl;
		return -1;
	}

		//Schedules all rooms at once, methods are outdated
	void fill( Room Rooms[ ], Course Sections[ ])
	{
		ofstream fout;
		fout.open( "ScheduleConflicts.txt" );
		string sroom, room;
		for ( int i = 0; i < RMMAX; i++ )
		{
			room = Rooms[i].getRoomName( );
			//cout << "Checking for room " << room << endl;
			for ( int index = 0; index < COURSEMAX; index++ )
			{
				sroom = Sections[index].getRoomNum( );
				//cout << "sroom is " << sroom << endl;
				if ( sroom == room )
				{
					int loc = findRoom( room );
					//Rooms[i].setIndex( loc );
					bool full = true;
					int row = 0;
					while ( row < 91 )
					{
						//cout << "In while loop" << endl;
						//cout << "row is " << row << endl;
						if ( schedule[row][loc] == nullptr )
						{
							//cout << "Scheduling " << Sections[index].getCRN( ) << endl;
							schedule[row][loc] = &Sections[index];
							//Sections[index].setIndex( loc );
							full = false;
							break;
						}
						else
						{
							bool conflict = Sections[index].conflictCheck( *schedule[row][loc] );
							if ( conflict )
							{
								cout << Sections[index].getCrn( ) << " conflicts with " << schedule[row][loc]->getCrn( ) << endl;
								fout << Sections[index].getCrn( ) << endl;
								full = false;
								break;
							}
							row++;
						}
						//cout << "End found" << endl;
					}
					//cout << "Made it to the end" << endl;
					if ( full )
					{
						cout << rooms[loc] << " was full" << endl;
					}
				}
			}
		}
		fout.close( );
	}

		//Fills schedule array using course ptr array, assumes rooms has been set
	void fillQuicklyPTRArray( Course *courses[ ] )
	{
		int i = 0;							//While loop control
		int col = 0;						//Active columns

		ofstream fout;						//Error output
		fout.open( "problems.txt" );
		while ( i < COURSEMAX )
		{
			//cout << i << endl;
			if ( i == 907 )
			{
				cout << "Something" << endl;
			}
			if ( courses[i] != nullptr )
			{
				
				col = findRoom( courses[i]->getRoomNum( ) );	//Finds column for desired room
				if ( col >= 0 && col < RMMAX )
				{
					for ( int row = 0; row < 91; row++ )
					{
						if ( schedule[row][col] == nullptr )
						{
							schedule[row][col] = courses[i];
							break;
						}
						else if ( schedule[row][col]->conflictCheck( *courses[i] ) )
						{
							//cout << "Conflict found" << endl;			//For testing

							fout << schedule[row][col]->getCrn() << " : " << courses[i]->getCrn( ) << endl;		//Error output
							break;
						}
						else
						{
							//cout << "Checking next row" << endl;	//For testing
						}
					}
				}
				else
				{
					//cout << "Room not found" << endl;		//For testing

					fout << courses[i]->getCrn( ) << endl;		//Error output
				}

					//Below checks for and schedules a course linked to courses[i]
				if ( courses[i]->getLinked( ) != nullptr )
				{
					Course *link = courses[i]->getLinked( );
					col = findRoom( link->getRoomNum( ) );
					for ( int row = 0; row < 91; row++ )
					{
						if ( schedule[row][col] == nullptr )
						{
							//cout << "Scheduling linked course" << link->getCrn( ) << endl;	//For testing
							
							schedule[row][col] = link;
							break;
						}
						else if ( schedule[row][col]->conflictCheck( *link ) )
						{
							//cout << "conflict found with linked course" << endl;	//For testing
							
								//Outputs main and linked CRN's to show that a linked course had an error
							fout << schedule[row][col]->getCrn() << " : " << courses[i]->getCrn( ) << ',' << link->getCrn( ) << endl;
							break;
						}
						else
						{
							//cout << "Link checking next row" << endl;		//For testing
						}
					}
				}

				i++;
			}
			else
			{
				i++;
			}
		}
		fout.close( );
	}

		//Fills schedule array usinge course obj array, assumes rooms has been set
	void fillQuicklyOBJArray( Course courses[ ] )
	{
		int i = 0;							//While loop control
		int col = 0;						//Active column

		ofstream fout;						//For error output
		fout.open( "problems.txt" );

		while ( i < COURSEMAX )
		{
			if ( courses[i].getCrn( ) != -1 )		//Makes sure course is filled
			{
				col = findRoom( courses[i].getRoomNum( ) );		//Finds index of desired room
				if ( col >= 0 && col < RMMAX )
				{
					for ( int row = 0; row < 91; row++ )		//Checks entire column
					{
						if ( schedule[row][col] == nullptr )
						{
							schedule[row][col] = &courses[i];
							break;
						}
						else if ( schedule[row][col]->conflictCheck( courses[i] ) )
						{
							//cout << "Conflict found" << endl;			//For testing

							fout <<schedule[row][col]->getCrn() << " : " << courses[i].getCrn( ) << endl;		//Error output
							break;
						}				
						else								//For testing if loop is working			
						{
							//cout << "Checking next row" << endl;		//For testing
						}
					}
				}
				else								//Room didn't exist
				{
					//cout << "Room not found" << endl;				//For testing

					fout << courses[i].getCrn( ) << endl;
				}

					//Below checks for and schedules a course linked to courses[i]
				Course*link = courses[i].getLinked( );
				if ( link != nullptr )
				{
					col = findRoom( link->getRoomNum( ) );
					for ( int row = 0; row < 91; row++ )
					{
						if ( schedule[row][col] == nullptr )
						{
							schedule[row][col] = link;
							break;
						}
						else if ( schedule[row][col]->conflictCheck( *link ) )
						{
							//cout << "conflict found with linked course" << endl;		//For testing
							
							fout <<schedule[row][col]->getCrn() << " : " << courses[i].getCrn( ) << ',' << link->getCrn( ) << endl;
							break;
						}
						else
						{
							//cout << "Link checking next row" << endl;		//For testing
						}
					}
				}
				else
				{
					//cout << "Link was nullptr" << endl;		//For testing
				}
				i++;
			}
			else
			{
				i++;
			}
		}
		fout.close( );
	}

	//Finds an existing index or assigns one to a room, returns the index
	int findRoomIndex( Room *Room )
	{
		int index = 0;
		string roomnum = Room->getRoomName( );
		while ( index < RMMAX )
		{
			if ( rooms[index] == "NULL" )
			{
				//cout << "Adding room" << endl;
				rooms[index] = roomnum;
				//Room->setIndex( index );
				cout << rooms[index] << endl;
				break;
			}
			else if ( rooms[index] == roomnum )
			{
				//cout << "Found room" << endl;
				cout << rooms[index] << endl;
				break;
			}
			else
			{
				index++;
			}
		}
		return index;
	}

	/*void outputRoomSchedule( Room toFind )
	{
	ofstream fout;
	string desiredRoom = toFind.getRoom( );
	string filename = desiredRoom + ".csv";
	int loc = findRoomIndex( &toFind );
	fout.open( filename );
	for ( int i = 0; i < 91; i++ )
	{
	for ( int j = 0; j < 7; j++ )
	{
	if ( schedule[i][loc]->checkDays( j ) )
	{
	fout << schedule[i][loc]->getCRN( ) << ',';
	}
	else
	{
	fout << ',';
	}
	}
	fout << endl;
	}
	fout.close( );
	}*/

	//Outputs entire schedule array in CSV friendly format
	friend ostream &operator<< ( ostream &stream, Schedule toOutput )
	{
		for ( int i = 0; i < RMMAX; i++ )
		{
			stream << toOutput.rooms[i] << ',';
		}
		stream << endl;
		for ( int i = 0; i < 91; i++ )
		{
			for ( int index = 0; index < RMMAX; index++ )
			{
				if ( toOutput.schedule[i][index] != nullptr )
				{
					stream << toOutput.schedule[i][index]->getCrn( ) << ',';
				}
				else
				{
					stream << 0 << ',';
				}
			}
			stream << endl;
		}
		return stream;
	}
};