//Author: Lili Gurski
#pragma once
#include "All_Included_Files.h"
using namespace std;
class Common
{
private:
	string prefix;    //the prefix
	int crs;          //the course number
	string title;     //name of the class
	int credits;      //number of credits

public:

	//default constructor
	Common( )
	{
		prefix = "none";
		crs = -1;
		title = "none";
		credits = -1;
	}


	Common( string prefix, int crs, string title, int credits )
	{
		prefix = prefix;
		crs = crs;
		title = title;
		credits = credits;
	}



	static void initializeCommonArray( Common array[750] )
	{
		{
			for ( int i = 0; i < 750; i++ )
			{
				array[i].prefix = "none";
				array[i].crs = -1;
				array[i].title = "none";
				array[i].credits = -1;
			}
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


	string getPrefix( )
	{
		return prefix;
	}

	int getCrs( )
	{
		return crs;
	}

	string getTitle( )
	{
		return title;
	}

	int getCredits( )
	{
		return credits;
	}

	void setPrefix( string setPrefix )
	{
		prefix = setPrefix;
	}

	void setCrs( int setCrs )
	{
		crs = setCrs;
	}

	void setTitle( string setTitle )
	{
		title = setTitle;
	}

	void setCredits( int setCredits )
	{
		credits = setCredits;
	}



};




