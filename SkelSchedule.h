#pragma once
#include "SkelCourse.h"
#include "SkelRoom.h"

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

class Schedule
{
private:
	string rooms[127];
	int schedule[91][127];
public:
	Schedule( )
	{
		for ( int i = 0; i < 127; i++ )
		{
			rooms[i] = "NULL";
		}
		for ( int i = 0; i < 91; i++ )
		{
			for ( int j = 0; j < 127; j++ )
			{
				schedule[i][j] = 0;
			}
		}
	}

		//Adds a single course to the schedule, cannot check for conflicts
	void add( Room &room, Course &Course )
	{
		cout << "In add" << endl;
		int index = 0;
		string roomnum = room.getRoom( );
		while ( index < 127 )
		{
			if ( rooms[index] == "NULL" )
			{
				cout << "Adding room" << endl;
				rooms[index] = roomnum;
				room.setIndex( index );
				Course.setIndex( index );
				cout << rooms[index] << endl;
				break;
			}
			else if ( rooms[index] == roomnum )
			{
				cout << "Found room" << endl;
				Course.setIndex( index );
				cout << rooms[index] << endl;
				break;
			}
			else
			{
				index++;
			}
		}
		bool full = true;
		int crn = Course.getCRN( );
		for ( int row = 0; row < 91; row++ )
		{
			if ( schedule[row][index] == 0 )
			{
				cout << "Setting CRN" << endl;
				schedule[row][index] = crn;
				full = false;
				cout << schedule[row][index] << endl;
				break;
			}
		}
		if ( full )
		{
			cout << roomnum[index] << " was full" << endl;
		}
	}

		//Returns the index of a room in the rooms array
	int findRoom( string room )
	{
		int index = 0;
		while ( index < 127 )
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
		cout << "Error when trying to find room" << endl;
		return 0;
	}

		//Schedules all rooms at once, methods are outdated
	void fill( Room Rooms[ ], int rsize, Course Sections[ ], int ssize, int positions[ ], int psize )
	{
		string sroom, room;
		for ( int i = 0; i < rsize; i++ )
		{
			room = Rooms[i].getRoom( );
			for ( int index = 0; index < ssize; index++ )
			{
				cout << "Checking for room " << room << endl;
				sroom = Sections[index].getRoom( );
				if ( sroom == room )
				{
					int loc = findRoom( room );
					Rooms[i].setIndex( loc );
					bool full = true;
					int row = 0;
					while ( row < 91 )
					{
						if ( schedule[row][loc] == 0 )
						{
							schedule[row][loc] = Sections[index].getCRN( );
							Sections[index].setIndex( loc );
							full = false;
							break;
						}
						else
						{
							int ref = (schedule[row][loc] - 60000);
							if ( ref >= 0 && ref < psize )
							{
								bool conflict = Sections[index].conflictCheck( Sections[positions[ref]] );
								if ( Sections[index].hasLink( ) )
								{
									Course* link = Sections[index].getLink( );
									if ( link->getRoom( ) == room )
									{
										conflict += link->conflictCheck( Sections[positions[ref]] );
									}
								}
								if ( conflict )
								{
									cout << Sections[index].getCRN( ) << " conflicts with " << schedule[row][loc] << endl;
									full = false;
									break;
								}
							}
							else
							{
								cout << "Reference error. CRN was out of scope" << endl;
							}
							row++;
						}
					}
					if ( full )
					{
						cout << rooms[loc] << " was full" << endl;
					}
				}
			}
		}
	}

		//Finds an existing index or assigns one to a room, returns the index
	int findRoomIndex( Room *Room )
	{
		int index = 0;
		string roomnum = Room->getRoom( );
		while ( index < 127 )
		{
			if ( rooms[index] == "NULL" )
			{
				cout << "Adding room" << endl;
				rooms[index] = roomnum;
				Room->setIndex( index );
				cout << rooms[index] << endl;
				break;
			}
			else if ( rooms[index] == roomnum )
			{
				cout << "Found room" << endl;
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

		//NOT FINISHED
	void addSection( Course *course, Course sections[ ], int index, int pos[ ], int psize )
	{
		int i = 0;
		while ( i < 91 )
		{
			int position = schedule[i][index];
			if ( schedule[i][index] == 0 )
			{
				schedule[i][index] = course->getCRN( );
				break;
			}
			else if ( course->conflictCheck( sections[pos[position]] ) )
			{
				cout << "conflict reached" << endl;
				break;
			}
			else
			{
				i++;
			}
		}
	}

		//Outputs entire schedule array in CSV friendly format
	friend ostream &operator<< ( ostream &stream, Schedule toOutput )
	{
		for ( int i = 0; i < 127; i++ )
		{
			stream << toOutput.rooms[i] << ',';
		}
		stream << endl;
		for ( int i = 0; i < 91; i++ )
		{
			for ( int index = 0; index < 127; index++ )
			{
				stream << toOutput.schedule[i][index] << ',';
			}
			stream << endl;
		}
		return stream;
	}
};