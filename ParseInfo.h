//Sam Scheuerman, Kyle Dickens, Josh Penrod
//Room Scheduling Reading & Parsing Pt1
//Due: 3/30/18
//The portion of code for reading in all pertinent elements about a course from a file and storing them in appropriate, memory efficient, objects.

#pragma once
#include <string>
using namespace std;

//ParseInfo: Class that contains methods for splitting apart data & converting data to correct types
class ParseInfo
{
public:
	void parseAll( string target[16], string rawInput );// splits apart one line with comma delimeters 
	int stringToNumber( string rawInput );// an alpha to numeric conversion 
};