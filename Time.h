//Josh Penrod
//Room Scheduling Time Info Pt1
//Due: 4/16/18
//The portion of code for storing all of the relevant time information for a course.
#pragma once	
#include <iostream>
using namespace std;
class Time
{
private:
	int courseWeek[2][7];// Array of start times and end times for one week, if class doesn't meet the day's times are set to -1  
	int startY;// The Year the class starts
	int startM;// The Month the class starts
	int startD;// The Day the class starts
	int endY;// The Year the class ends
	int endM;// The Month the class ends
	int endD;// The Day the class ends
public:
	//Setters
	void setStartY( int startYSetter )
	{
		startY = startYSetter;
	}
	void setStartM( int startMSetter )
	{
		startM = startMSetter;
	}
	void setStartD( int startDSetter )  
	{
		startD = startDSetter;
	}
	void setEndY( int endYSetter )
	{
		endY = endYSetter;
	}
	void setEndM( int endMSetter )
	{
		endM = endMSetter;
	}
	void setEndD( int endDSetter )
	{
		endD = endDSetter;
	}
	//Getters
	int getStartY( )
	{
		return startY;
	}
	int getStartM( )
	{
		return startM;
	}
	int getStartD( )
	{
		return startD;
	}
	int getEndY( )
	{
		return endY;
	}
	int getEndM( )
	{
		return endM;
	}	  
	int getEndD( )
	{
		return endD;
	}

	//Default Constructor
	Time( )
	{
		for ( int i = 0; i < 2; i++ )
		{
			for ( int j = 0; j < 7; j++ )
			{
				courseWeek[i][j] = -1;
			}
		}
		startY = -1;
		startM = -1;
		startD = -1;
		endY = -1;
		endM = -1;
		endD = -1;
	}

	//Tyler's Time conflict methods
	bool checkForConflict(Time toCheck)
	{
		bool toReturn = false;
		if (checkTimeOverlap(this->startY, toCheck.startY, this->endY, toCheck.endY ) )// Do they happen in the same year(s)
		{
			if ( checkTimeOverlap( this->startM, toCheck.startM, this->endM, toCheck.endM ) )// Do they happen in the same month(s)
			{
				if (checkDayOverlap(this->courseWeek, toCheck.courseWeek))// Do they ever meet on the same day in the week
				{
					if (checkDayOfMonthOverlap( toCheck))
					{
						for (int i = 0; i < 7; i++)// Do they try to meet at the same time
						{
							if (this->courseWeek[0][i] != -1)
							{
								if (checkTimeOverlap(this->courseWeek[0][i], toCheck.courseWeek[0][i], this->courseWeek[1][i], toCheck.courseWeek[1][i]))
								{
									toReturn = true;
								}
							}
						}
					}
				}
			}
		}
		return toReturn;
	}
	bool checkTimeOverlap (int time1Start, int time2Start, int time1End, int time2End )
	{
		bool toReturn = false;
		if (time1Start >= time2Start && time1Start <= time2End || time1End >= time2Start && time1End <= time2End )
		{
			toReturn = true;
		}
		return toReturn;
	}
	bool checkDayOverlap( int class1Week[2][7], int class2Week[2][7] )
	{
		bool toReturn = false;
		for (int i = 0; i < 7; i++  )
		{
			if (class1Week[0][i] > -1 && class2Week[0][i] > -1 )
			{
				toReturn = true;
			}
		}
		return toReturn;
	}
	bool checkDayOfMonthOverlap( Time toCheck)
	{
		bool toReturn = true;
		if (this->startM == toCheck.endM|| this->endM == toCheck.startM)
		{
			if (!checkTimeOverlap(this->startD, toCheck.startD, this->endD, toCheck.endD))// Do they happen in the same days(s) within the month
			{
				toReturn = false;
			}
		}
		return toReturn;
	}

	//setAll: takes in the 5 strings from the file and calls the appropriate methods/sets the values directly
	void setAll ( string week, string startTime, string endTime, string startDate, string endDate )
	{
		fillDays( week, atoi( startTime.c_str( ) ), atoi( endTime.c_str( ) ) );
		startY = parseYear( startDate );
		startM = parseMonth( startDate );
		startD = parseDay( startDate );
		endY = parseYear( endDate );
		endM = parseMonth( endDate );
		endD = parseDay( endDate );
	}

	//fillDays: called in setAll, fills the courseWeekArray with the start times and end times.
	//week: the days the class meets
	//startT: the time of day class starts
	//endT: the time of day class ends
	void fillDays( string week, int startT, int endT )
	{
		for ( int k = 0; k < week.length( ); k++ )
		{
			courseWeek[0][findDayLoc( week[k] )] = startT;
			courseWeek[1][findDayLoc( week[k] )] = endT;
		}
	}

	//findDayLoc: called in fillDays, returns the correct location in the courseWeek array based off the char passed in
	int findDayLoc( char toFind )
	{
		toFind = tolower( toFind );
		int toReturn = -1;
		switch ( toFind )
		{
		case 'm': toReturn = 0;
			break;
		case 't': toReturn = 1;
			break;
		case 'w': toReturn = 2;
			break;
		case 'r': toReturn = 3;
			break;
		case 'f': toReturn = 4;
			break;
		case 's': toReturn = 5;
			break;
		case 'u': toReturn = 6;
		}
		return toReturn;
	}

	//parseDay: for the sake of storing start and end dates as split apart ints it takes in the date and returns the day as an int
	//date: the full date in day-month(spelled out)-year(last 2 digits)
	int parseDay( string date )
	{
		int toReturn;
		date = date.substr( 0, date.find( '-' ) );
		toReturn = stoi( date );
		return toReturn;
	}

	//parseDay: for the sake of storing start and end dates as split apart ints it takes in the date and returns the month as an int
	//date: the full date in day-month(spelled out)-year(last 2 digits)
	int parseMonth( string date )
	{
		int toReturn = 0;
		date = date.substr( date.find( '-' ) + 1, 3 );
		for ( int i = 0; i < date.length( ); i++ )
		{
			date[i] = tolower( date[i] );
		}
		if ( date == "jan" )
		{
			toReturn = 1;
		}
		else if ( date == "feb" )
		{
			toReturn = 2;
		}
		else if ( date == "mar" )
		{
			toReturn = 3;
		}
		else if ( date == "apr" )
		{
			toReturn = 4;
		}
		else if ( date == "may" )
		{
			toReturn = 5;
		}
		else if ( date == "jun" )
		{
			toReturn = 6;
		}
		else if ( date == "jul" )
		{
			toReturn = 7;
		}
		else if ( date == "aug" )
		{
			toReturn = 8;
		}
		else if ( date == "sep" )
		{
			toReturn = 9;
		}
		else if ( date == "oct" )
		{
			toReturn = 10;
		}
		else if ( date == "nov" )
		{
			toReturn = 11;
		}
		else if ( date == "dec" )
		{
			toReturn = 12;
		}
		return toReturn;
	}

	//parseDay: for the sake of storing start and end dates as split apart ints it takes in the date and returns the year as an int
	//date: the full date in day-month(spelled out)-year(last 2 digits)
	int parseYear( string date )
	{
		int toReturn;
		date = date.substr( date.rfind( '-' ) + 1, 2 );
		toReturn = stoi( date );
		return toReturn;
	}

	//overloaded output operator for testing
	friend ostream &operator<< ( ostream &stream, Time toPrint )
	{
		stream << "Start Time: ";
		for ( int j = 0; j < 7; j++ )
		{
			stream << toPrint.courseWeek[0][j] << " , ";
		}
		stream << endl;
		stream << "End Time: ";
		for ( int j = 0; j < 7; j++ )
		{
			stream << toPrint.courseWeek[1][j] << " , ";
		}
		stream << endl;
		stream << "Start Date: " << toPrint.startM << "/" << toPrint.startD << "/" << toPrint.startY << endl;
		stream << "End Date: " << toPrint.endM << "/" << toPrint.endD << "/" << toPrint.endY << endl;
		return stream;
	}
};