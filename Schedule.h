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

const int NUMROOMZ = 100;

class Schedule
{
private:
	string rooms[NUMROOMZ];
	Course * schedule[91][NUMROOMZ];
public:
	Schedule( )
	{
		for ( int i = 0; i < NUMROOMZ; i++ )
		{
			rooms[i] = "NULL";
		}
		for ( int i = 0; i < 91; i++ )
		{
			for ( int j = 0; j < NUMROOMZ; j++ )
			{
				schedule[i][j] = nullptr;
			}
		}
	}

		//Adds a single course to the schedule, cannot check for conflicts
	void add( Room &room, Course &Course )
	{
		cout << "In add" << endl;
		int index = 0;
		string roomnum = room.getRoom( );
		while ( index < NUMROOMZ )
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
		//int crn = Course.getCRN( );
		for ( int row = 0; row < 91; row++ )
		{
			if ( schedule[row][index] == nullptr )
			{
				cout << "Setting CRN" << endl;
				schedule[row][index] = &Course;
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
		while ( index < NUMROOMZ )
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
		ofstream fout;
		fout.open( "ScheduleConflicts.txt" );
		string sroom, room;
		for ( int i = 0; i < rsize; i++ )
		{
			room = Rooms[i].getRoom( );
			cout << "Checking for room " << room << endl;
			for ( int index = 0; index < ssize; index++ )
			{
				sroom = Sections[index].getRoom( );
				//cout << "sroom is " << sroom << endl;
				if ( sroom == room )
				{
					int loc = findRoom( room );
					Rooms[i].setIndex( loc );
					bool full = true;
					int row = 0;
					while ( row < 91 )
					{
						cout << "In while loop" << endl;
						cout << "row is " << row << endl;
						if ( schedule[row][loc] == nullptr )
						{
							cout << "Scheduling " << Sections[index].getCRN( ) << endl;
							schedule[row][loc] = &Sections[index];
							Sections[index].setIndex( loc );
							full = false;
							break;
						}
						else
						{
							cout << "Row " << row << " was full" << endl;
							int ref = (schedule[row][loc]->getCRN( ) - 60000);
							if ( ref >= 0 && ref < psize )
							{
								//cout << "Checking for conflict" << endl;
								//cout << Sections[index].getCRN( ) << " " << Sections[positions[ref]].getCRN( ) << endl;
								bool conflict = Sections[index].conflictCheck( Sections[positions[ref]] );
								//cout << "Conflict was " << conflict << endl;
								/*if ( Sections[index].hasLink( ) )
								{
									Course* link = Sections[index].getLink( );
									if ( link->getRoom( ) == room )
									{
										conflict += link->conflictCheck( Sections[positions[ref]] );
									}
								}*/
								if ( conflict )
								{
									cout << Sections[index].getCRN( ) << " conflicts with " << schedule[row][loc]->getCRN( ) << endl;
									fout << Sections[index].getCRN( ) << endl;
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
						cout << "End found" << endl;
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

		//Finds an existing index or assigns one to a room, returns the index
	int findRoomIndex( Room *Room )
	{
		int index = 0;
		string roomnum = Room->getRoom( );
		while ( index < NUMROOMZ )
		{
			if ( rooms[index] == "NULL" )
			{
				//cout << "Adding room" << endl;
				rooms[index] = roomnum;
				Room->setIndex( index );
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

		//NOT FINISHED
	void addSection( Course *course, Course sections[ ], int index, int pos[ ], int psize )
	{
		int i = 0;
		while ( i < 91 )
		{
			int position = (schedule[i][index]->getCRN( ) - 60000);
			if ( schedule[i][index] == 0 )
			{
				schedule[i][index] = course;
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
		for ( int i = 0; i < NUMROOMZ; i++ )
		{
			stream << toOutput.rooms[i] << ',';
		}
		stream << endl;
		for ( int i = 0; i < 91; i++ )
		{
			for ( int index = 0; index < NUMROOMZ; index++ )
			{
				if ( toOutput.schedule[i][index] != nullptr )
				{
					stream << toOutput.schedule[i][index]->getCRN( ) << ',';
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