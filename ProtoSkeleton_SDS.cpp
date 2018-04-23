#include <iostream>
#include <fstream>
#include <string>
#include "SkelCommon.h"
#include "SkelRoom.h"
#include "SkelCourse.h"
#include "SkelSchedule.h"

using namespace std;

const short int ROOMCOL = 17;
const short int SECTIONCOL = 14;
const short int NUMCLASSES = 707;
const short int NUMROOMS = 100;
const string ROOMFILE = "Ad_Astra_LC_Room_Description_List.csv";
const string COURSEFILE = "MASTER_NEW.csv";

	//Sets position array to 1337, will not be used in final code
void fillDefaultPosition( int positions[ ], int psize );

	//Opens rooms file, parses information, passes room objects string array
void fillRoom( Room Rooms[ ], int size );

	//Opens course file, parses and passes to course, checks for similar common info, fills common link in courses
void fillSectionCommon( Course Sections[ ], int ssize, Common Commons[ ], int csize, int position[ ], int psize );

	//NOT IN USE, checks for overlapping room/course, passes to schedule
void fillSchedule( Room Rooms[ ], int rsize, Course Sections[ ], int ssize, Schedule &schedule );

int main( )
{
	Room Rooms[NUMROOMS];
	int rsize = NUMROOMS;
	Common Commons[200];
	int csize = 200;
	Course Sections[NUMCLASSES];
	int ssize = NUMCLASSES;

	Schedule schedule;

	int position[10000];
	int psize = 10000;

	fillDefaultPosition( position, psize );
	fillRoom( Rooms, rsize );
	fillSectionCommon( Sections, ssize, Commons, csize, position, psize );

	//fillSchedule( Rooms, rsize, Sections, ssize, schedule );
	schedule.fill( Rooms, rsize, Sections, ssize, position, psize );

	ofstream fout;
	fout.open( "Schedule.csv" );
	fout << schedule;
	fout.close( );

	system( "pause" );
	return 0;
}

void fillDefaultPosition( int positions[ ], int psize )
{
	for ( int i = 0; i < psize; i++ )
	{
		positions[i] = 1337;
	}
}

void fillRoom( Room Rooms[ ], int size )
{
	ifstream fin;
	fin.open( ROOMFILE );

	string raw, cooked[ROOMCOL];
	int i = 0;
	int col = 0;
	while ( !fin.fail( ) && i < size )
	{
		getline( fin, raw );
		col = 0;
		for ( int j = 0; j < ROOMCOL; j++ )
		{
			cooked[j] = "";
		}

		for ( unsigned int j = 0; j < raw.size( ) && col<ROOMCOL; j++ )
		{
			if ( raw[j] == ',' )
			{
				//cout << cooked[col] << endl;
				col++;
			}
			else
			{
				cooked[col] += raw[j];
			}
		}
		Rooms[i].fill( cooked );
		i++;
	}
	fin.close( );
}

void fillSectionCommon( Course Sections[ ], int ssize, Common Commons[ ], int csize, int position[ ], int psize )
{
	ifstream fin;
	fin.open( COURSEFILE );

	string raw, cooked[SECTIONCOL];
	int i = 0;
	int col = 0;
	int com = 0;

	while ( !fin.fail( ) && i < ssize )
	{
		getline( fin, raw );
		col = 0;
		for ( int j = 0; j < SECTIONCOL; j++ )
		{
			cooked[j] = "";
		}

		for ( int j = 0; j < raw.size( ) && col < SECTIONCOL; j++ )
		{
			if ( raw[j] == ',' )
			{
				//cout << cooked[col] << " ";
				col++;
			}

			else
			{
				cooked[col] += raw[j];
			}
		}
		//cout << endl;

		Sections[i].fill( cooked );
		int index = (Sections[i].getCRN( ) - 60000);
		if ( index >= 0 && index < psize )	//Prevents stepping off array
		{
			if ( position[index] != 1337 )	//Links same CRN's
			{
				Sections[position[index]].setLink( &Sections[i], i );
			}
			else
			{
				position[index] = i;
			}
		}
		else
		{
			cout << "Invalid CRN index for Course " << i << endl;
		}

		while ( com < csize )		//Assigns and fills common objects
		{
			if ( !Commons[com].isFull( ) )
			{
				Commons[com].fill( cooked );
				cout << cooked[TITLE] << endl;
				Sections[i].setCommon( &Commons[com] );
				break;
			}
			else if ( Commons[com].isSame( cooked ) )
			{
				cout << cooked[COURSE] << endl;
				Sections[i].setCommon( &Commons[com] );
				break;
			}
			else
			{
				com++;
			}
		}
		i++;
	}
	fin.close( );
}

void fillSchedule( Room Rooms[ ], int rsize, Course Sections[ ], int ssize, Schedule &schedule )
{
	string sroom, room;
	for ( int i = 0; i < rsize; i++ )
	{
		for ( int index = 0; index < ssize; index++ )
		{
			sroom = Sections[index].getRoom( );
			room = Rooms[i].getRoom( );
			if ( sroom == room )
			{
				cout << "Adding room" << endl;
				schedule.add( Rooms[i], Sections[index] );
			}
		}
	}
}
