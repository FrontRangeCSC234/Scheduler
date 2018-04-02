/* Name: Sara Williams and Alex Gibson
*  Project: Reading In CRNs and Finding Range of Unused CRNS
*  Date: 3/30/2018
*  Description: Reads in a .csv file, and find the unused CRNs within the range of
*  CRNs provided in the file. Prints out list of unused CRNs.
*/


//OMG EDIT LOL
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
	bool crnArray[6000];	//array of booleans - if true, then CRN is used

	//initialize all values to false
	for ( int i = 0; i < 6000; i++ )
	{
		crnArray[i] = false;
	}

	ifstream infile("classCRN.txt");		//opens the file
	string cell;						//The string to hold each "cell" with data
	if (infile.is_open())
	{
		getline( infile, cell, '\n' );	//ignore first line (header)
		int i = 0;
		while ( !infile.fail( ))	//while file is still open
		{
			int CRN;
			infile >> CRN;		//grabs CRN
			CRN = CRN - 60000;
			if ( CRN > 0 )
			{
				cout << "CRN is: " << CRN << endl;
				crnArray[CRN] = true;
			}

			getline( infile, cell, '\n' );

		}

		//Prints unused CRNs
		for ( int i = 0; i < 6000; i++ )
		{
			if ( crnArray[i] == false )
			{
				cout << "Index: " << i << " [" << i+60000 << "]" << endl;
			}
		}

		infile.close();
	}
	else
	{
		cout << "File is not open" << '\n';
	}

	cout << endl;
	system("pause");
	return 0;

}