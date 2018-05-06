#pragma once
#include "All_Included_Files.h"

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

		//Prompts user to enter a room number and checks that room is valid, returns room
	string displayMenu( )
	{
		int indexCheck = -1;
		string toReturn;

		while ( indexCheck == -1 )
		{
			cout << "Please enter a room number" << endl;
			cin >> toReturn;

			for ( int i = 0; i < toReturn.size( ); i++ )
			{
				toReturn[i] = toupper( toReturn[i] );		//Prevents capitalization error
			}

			indexCheck = findRoom( toReturn );				//Checks that room exists
		}
		return toReturn;
	}

		//Outputs the schedule of a single room in the schedule array
	void outputRoom( )
	{
		string rm = displayMenu( );
		int col = findRoom( rm );
		string output = rm + ".csv";			//File is named after room
		ofstream fout;

		int full[7] = { 0 };					//Tracks number of pointers in columns of toOutput
		Course * toOutput[13][7];				//Stores output courses in correct format

		for ( int i = 0; i < 13; i++ )
		{
			for ( int j = 0; j < 7; j++ )
			{
				toOutput[i][j] = nullptr;
			}
		}

		fout.open( output );
		fout << ",,," << rm << endl;				//Name at top of schedule
		fout << "MONDAY,TUESDAY,WEDNESDAY,THURSDAY,FRIDAY,SATURDAY,SUNDAY" << endl;
		for ( int i = 0; i < 91 && schedule[i][col] != nullptr; i++ )
		{
			fillOutputRoomArray( toOutput, schedule[i][col], full );
			//Old, working code
			/*fout << schedule[i][col]->getCrn( ) << ',' << schedule[i][col]->getTeacherFN( ) << ',' << schedule[i][col]->getTeacherLN( );
			fout << endl;*/
		}
		for ( int i = 0; i < 13; i++ )
		{
			for ( int j = 0; j < 7; j++ )
			{
				if ( toOutput[i][j] != nullptr )
				{
					fout << toOutput[i][j]->getCrn( ) << ',';
				}
				else
				{
					fout << "0,";
				}
			}
			fout << endl;
		}
		fout.close( );
	}

		//Uses courseWeek array to place courses in columns corresponding to days of the week
	void fillOutputRoomArray( Course * toOutput[13][7], Course * raw, int fullArray[7] )
	{
		/************************************************************
		Get's a pointer to the time object's courseWeek array.

		NOTE: courseWeek is a 2D array: courseWeek[2][7]. The
		returned pointer treats it as a 1D array with 14 members.
		The first row [0][0-6] is accessed using indeces 0-6
		while the second row [1][0-6] is accessed using indeces
		7-13.
		**********************************************************/
		int *time = raw->getClassTimePtr( )->getCourseWeek( );
		for ( int i = 0; i < 7; i++ )
		{
			if ( time[(i)] != -1 )
			{
				toOutput[fullArray[i]][i] = raw;
				fullArray[i]++;
			}
		}
	}

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