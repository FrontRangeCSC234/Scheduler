#include "Common.h"
#include "All_Included_Files.h"

using namespace std; 
//default constructor
Common::Common ( )
{
	prefix = "none";
	crs = -1;
	title = "none";
	credits = -1;
}

Common:: Common ( string prefix, int crs, string title, int credits )
{
	prefix = prefix;
	crs = crs;
	title = title;
	credits = credits;
}


static void initializeCommonArray( Common array[750] )
{
	for ( int i = 0; i <750; i++ )
	{
		array[i].prefix = "none";
		array[i].crs = -1;
		array[i].title = "none";
		array[i].credits = -1;
	}
}


static void fillCommon( Common array[750] )
{
	ifstream fin;
	fin.open( "MasterFile.csv" );

	bool sameTitle = true;    //helps to keep track of duplicates
	bool sameCrs = false;     //helps to keep track of duplciates
	string data;              //the data read in as a string
	int crs = 0;              //the course number
	int credits;              //number of credits
	int  count = 1;           //which column
	string prefix;            //prefix of the class
	int rowCount = 0;        //keeps track for to put into the array
	string title;            //name of the class

	int numData;




	while ( getline( fin, data, ',' ) )
	{
		if ( data[0] == '1' || data[0] == '2' ||
			data[0] == '3' || data[0] == '4' || data[0] == '5' || data[0] == '9' )
		{
			numData = stoi( data );     //parses info into an int if necessary
			if ( numData == crs )
			{
				sameCrs = true;
			}
		}

		else if ( data == title )
		{
			sameTitle = true;
		}

		else
		{
			sameTitle = false;
			sameCrs = false;
		}

		if ( count == 2 )
		{
			prefix = data;

		}

		else if ( count == 3 && sameCrs != true )
		{

			crs = numData;

		}
		else  if ( count == 5 && sameTitle != true )
		{

			title = data;
		}
		else if ( count == 6 && sameTitle != true && numData < 6 )
		{

			credits = numData;

			array[rowCount].prefix = prefix;
			array[rowCount].crs = crs;
			array[rowCount].title = title;
			array[rowCount].credits = credits;

			rowCount++;

		}


		if ( count == 14 )
		{

			count = 1;

		}

		else
		{
			count++;
		}



	}
	//Prints for debugging purposes
	/*

	for ( int i = 0; i < 750; i++ )
	{
	cout << array[i].title << endl;
	}*/

	fin.close( );
}




//Getters and Setters
Common:: string getPrefix( )
{
	return prefix;
}

Common:: int getCrs( )
{
	return crs;
}

Common:: string getTitle( )
{
	return title;
}

Common:: int getCredits( )
{
	return credits;
}

Common:: void setPrefix( string setPrefix )
{
	prefix = setPrefix;
}

Common:: void setCrs( int setCrs )
{
	crs = setCrs;
}

Common:: void setTitle( string setTitle )
{
	title = setTitle;
}

Common:: void setCredits( int setCredits )
{
	credits = setCredits;
}