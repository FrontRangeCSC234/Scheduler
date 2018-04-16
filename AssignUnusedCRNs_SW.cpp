/* Name: Sara Williams
*  Project: Assign Unused CRNS to courses with blank CRNS
*  Date: 4/16/2018
*  Description: Reads in a .csv file, and find the unused CRNs within the range of
*  CRNs provided in the file. Overwrites the file and plugs in unused CRNs in any
*  courses that do have the CRN location blank.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

//void printAvailableCRNs( vector<int>unusedCRNArray );	//prints the list of available CRNs

int main( )
{
	bool crnArray[6000];	//array of booleans - if true, then CRN is used

	ofstream outFile;
	outFile.open( "MasterFile.txt", ofstream::out | ofstream::app );

	//initialize all values to false
	for ( int i = 0; i < 6000; i++ )
	{
		crnArray[i] = false;
	}

	ifstream infile( "MissingCRNs.csv" );		//opens the file
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

		//printAvailableCRNs( unusedCRNArray );

		ifstream infile( "MissingCRNs.csv" );		//opens the file

		if ( infile.is_open( ) )
		{
			getline( infile, cell, '\n' );	//ignore first line (header)
			int i = 0;
			while ( !infile.fail( ) )	//while file is still open
			{
				if ( cell[0] == ',')
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

		cout << endl;
		system( "pause" );
		return 0;

	}
}//end main

//void printAvailableCRNs(vector<int>unusedCRNArray )
//{
//	for ( int i = 0; i < unusedCRNArray.size( ); i++ )
//	{
//		cout << i << ": " << unusedCRNArray[i] << endl;
//	}
//}