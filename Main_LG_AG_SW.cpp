#include "All_Included_Files.h"
using namespace std;


//Prototypes 
void displayMenu( );
void createMasterFile( );




int main( )
{
	Course classArray[750];
	courseFileReadIn( classArray );

	string nameArray[RMMAX];
	Room roomList[RMMAX];

	int userChoice = 1;

	Common commonArray[750]; 

	Course** crnSort;
	



	while ( userChoice != 0 )
	{
		displayMenu( );
		cin >> userChoice;
		switch ( userChoice )
		{
		case 1:
			cout << "case 1" << endl;
			createMasterFile( );
			break;
		case 2:
			cout << "case 2" << endl;
			//searchForCourse( );
			break;
		case 3:
			cout << "case 3" << endl;
			//searchForRoom( );
			break;
		case 4:
			cout << "case 4" << endl;
			//findAvailableRooms( );
			break;
		case 5:
			cout << "case 5" << endl;
			//addCourse( );
			break;
		case 6:
			//callCommon()
			fillRoomArray(nameArray,roomList);
			Common::initializeCommonArray( commonArray );
			Common::fillCommon( commonArray );
			courseFileReadIn( classArray );
			crnSort = coursePointerFill();
			break;
		case 0:
			cout << "EXITING PROGRAM!" << endl;
			break;
		default:
			cout << "Invalid choice" << endl;
			break;
		}
	}

	system( "pause" );
	return 0;
}


/****************************************************************************************
* Author: Alex Gibson
* Displays menu
*/
void displayMenu( )
{


	cout << "What would you like to do?" << endl;
	cout << "(0) EXIT PROGRAM" << endl;
	cout << "(1) Create a master file." << endl;
	cout << "(2) Search for a course." << endl;
	cout << "(3) Search for a room." << endl;
	cout << "(4) Find available rooms." << endl;
	cout << "(5) Add a course." << endl;
	cout << "(6) Make Schedule" << endl;
	
}


/****************************************************************************************
* Author: Sara Williams
* reads in master file, and assigns CRNS to any courses without CRNs
*/
void createMasterFile( )
{
	bool crnArray[6000];	//array of booleans - if true, then CRN is used

	ofstream outFile;
	outFile.open( "MasterFile.csv", ofstream::out | ofstream::app );

	//initialize all values to false
	for ( int i = 0; i < 6000; i++ )
	{
		crnArray[i] = false;
	}

	ifstream infile( "MASTER.csv" );		//opens the file
	string cell;						//The string to hold each "cell" with data
	if ( infile.is_open( ) )
	{
		getline( infile, cell, '\n' );	//ignore first line (header)
		int i = 0;
		while ( !infile.fail( ) )	//while file is still open
		{
			int CRN;
			infile >> CRN;		//grabs CRN
			CRN = CRN - 60000;
			if ( CRN > 0 )
			{
				//cout << "CRN is: " << CRN << endl;
				crnArray[CRN] = true;
			}

			getline( infile, cell, '\n' );
		}

		vector <int> unusedCRNArray;


		for ( int i = 0; i < 6000; i++ )
		{
			if ( crnArray[i] == false )
			{
				unusedCRNArray.push_back( i + 60000 );
				//cout << "Index: " << i << " [" << i+60000 << "]" << endl;
			}
		}


		ifstream infile( "MASTER.csv" );		//opens the file

		if ( infile.is_open( ) )
		{
			getline( infile, cell, '\n' );	//ignore first line (header)
			int i = 0;
			while ( !infile.fail( ) )	//while file is still open
			{
				if ( cell[0] == ',' )
				{
					outFile << unusedCRNArray[i] << cell << " \n";
					i++;
				}
				else
				{
					outFile << cell << " \n";
				}
				getline( infile, cell, '\n' );
			}

		}
		else
		{
			cout << "File is not open" << '\n';
		}

		infile.close( );
		outFile.close( );
	}
}



