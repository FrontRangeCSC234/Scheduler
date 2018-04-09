#include <iostream>
#include <string>

using namespace std;

const string MONTHS[12] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };

void turnToNumber( string input, int &day, int &month, int &year );

int main( )
{
	string date = "24-May-19";
	cout << date << endl;
	int day, month, year;
	turnToNumber( date, day, month, year );
	cout << "Day: " << day << " Month: " << month << " Year: " << year << endl;

	system( "pause" );
	return 0;
}

void turnToNumber( string input, int &day, int &month, int &year )
{
	//This is where we need to parse the date string into usable numbers
	string nums = "";
	string chars = "";
	string days = "";
	string years = "";

	for ( int i = 0; i < input.size( ); i++ )
	{
		if ( isdigit( input[i] ) )
		{
			nums += input[i];
		}
		else if ( isalpha( input[i] ) )
		{
			chars += input[i];
		}
		else
		{
			continue;
		}

	}

	for ( int index = 0; index < 12; index++ )
	{
		if ( chars == MONTHS[index] )
		{
			month = index + 1;
		}
	}

	if ( nums.size( ) == 3 )
	{
		days += nums[0];
		for ( int e = 1; e < nums.size( ); e++ )
		{
			years += nums[e];
		}
	}
	else
	{
		int c = 0;
		while ( c < 2 )
		{
			days += nums[c];
			c++;
		}
		for ( int d = c; d < nums.size( ); d++ )
		{
			years += nums[d];
		}
	}

	day = atoi( days.c_str( ) );
	year = atoi( years.c_str( ) );

	//This was here to test, leaving it in in case I need it later
	/*cout << day << endl << year << endl;
	cout << endl << endl << "Final form." << endl;
	cout << "Day " << day << endl;
	cout << "Month " << month << endl;
	cout << "Year " << year << endl << endl;*/
}