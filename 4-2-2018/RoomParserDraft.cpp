//Ian Oliver, James Gillman, Micah Haas
/*********************************************************************************************************************************************\
|     Authors:	Ian Oliver, James Gillman, Micah Haas
|  Instructor: Victoria Eisele
|      Titile: Roomlist structures
|         Due: 3/30/2018
|   Submitted: 3/31/2018
|DESCRIPTION:
|				Reads in the CSV for the Ad Astra master room list. Parses the informtion and stores whats needed into the 
|				RoomList class as an array
|
\*********************************************************************************************************************************************/

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>

using namespace std;

const int AMAX = 36;
const int RAROW = 99;
const int RACOL = 16;
const int INTERVAL = ((16 * 60) / 5);

/**************************************************************************************************************************************************
 *class RoomList
 *data members: const string ROOMITEM[], bool bRoomFeatures[], bool times[], int qRoomFeatures[], string roomName, string regionName, int capacity 
 *Description: class used for storing the information given by the ad astra csv file
 **************************************************************************************************************************************************/
class RoomList
{
private:
	const string ROOMITEM[AMAX]					//look up array
	= { "Computer - Instructor","DVD Player", "LCD Overhead Projector", "Power Point Clicker", "Screen", "Phone - Star",
	"Smart Board", "Speakers", "White Board", "Computer(s) - PC", "Computer(s) - Mac", "Hospital Bed(s)", "Virtual Welder",
	"Manufacturing Energy Technology Machines", "Welding Shop", "Auto Shop", "Printer", "Machine", "Storage Cupboard(s)", "Podium",
	"Document Camera", "Flip Chart", "Changing Room", "Restroom",	"Piano", "3D Printer", "Imaging Lab", "Printmaking",
	"Painting and Drawing Lab", "Sink", "Laptop", "Exam Table", "Human Cadavers in Refrigeration Units", "Refrigerator","Microscope", "Map(s)" };
	bool bRoomFeatures[AMAX] = { false };		//parrell array with qRoomFeatures, holds if something is found in the room
	bool times[192] = { false };					//array holding the 5 minute intervals of the specific room
	int qRoomFeatures[AMAX] = { 0 };				//parrell array with bRoomFeatures, holds how many of something if found in the room
	string roomName;									//holds the room name and number
	string regionName;								//holds the region stats for priority
	int capacity;										//holds the max number people a room can hold

public:

		//defualt constructor
	RoomList()
	{
		roomName = "EMPTY";
		regionName = "EMPTY";
	}
		//paramtered constructor
	RoomList(int capacity, string roomName, string regionName, bool bRoomFeatures[], int iRoomFeatures[])
	{
		this->roomName = roomName;
		this->regionName = regionName;
		this->capacity = capacity;
		for (int i = 0; i < AMAX; i++)
		{
			this->bRoomFeatures[i] = bRoomFeatures[i];
			this->qRoomFeatures[i] = iRoomFeatures[i];
		}
	}
		//prints the room info for the class
	void printRoomInfo()
	{
		cout << "roomName: " << this->roomName;
		cout << ", regionName: " << this->regionName;
		cout << ", roomCap: " << this->capacity << endl;;
		for (int i = 0; i < AMAX; i++)
		{
			if (i < 10)
			{
				cout << " ";
			}
			cout << "[" << i << "]: " << bRoomFeatures[i] << ", " << qRoomFeatures[i] << " " << this->ROOMITEM[i] << endl;
		}
	}

		//getters and setters for the class
	const string* getROOMITEM()
	{
		return this->ROOMITEM;
	}
	bool* getbRoomFeatures()
	{
		return this->bRoomFeatures;
	}

	bool getbRoomSingle(int row)
	{
		return bRoomFeatures[row];
	}
	bool* getTimes()
	{
		return this->times;
	}
	int* getqRoomFeatures()
	{
		return this->qRoomFeatures;
	}
	int getCap()
	{
		return this->capacity;
	}
	string getroomName()
	{
		return this->roomName;
	}
	string getRegionName()
	{
		return this->regionName;
	}

	void setbRoomSingle(bool b, int i)
	{
		this->bRoomFeatures[i] = b;
	}

	void setqRoomSingle(int index, int num)
	{
		this->qRoomFeatures[index] = num;
	}

	void setbRoomFeatures(bool bRoomFeatures[])
	{
		for (int i = 0; i < AMAX; i++)
		{
			this->bRoomFeatures[i] = bRoomFeatures[i];
		}
	}
	void setTimes(bool times[])
	{
		for (int i = 0; i < AMAX; i++)
		{
			this->times[i] = times[i];
		}
	}
	void setqRoomFeatures()
	{
		for (int i = 0; i < AMAX; i++)
		{
			this->qRoomFeatures[i] = qRoomFeatures[i];
		}
	}
	void setCap(int capacity)
	{
		this->capacity = capacity;
	}
	void setroomName(string roomName)
	{
		this->roomName = roomName;
	}
	void setRegionName(string regionName)
	{
		this->regionName = regionName;
	}

		//clone function for the RoomList class, copies info from right side to left
	void clone(RoomList room)
	{
		this->capacity = room.capacity;
		this->regionName = room.regionName;
		this->roomName = room.roomName;
		for (int i = 0; i < AMAX; i++)
		{
			this->bRoomFeatures[i] = room.bRoomFeatures[i];
			this->qRoomFeatures[i] = room.qRoomFeatures[i];
		}
		for (int j = 0; j < 192; j++)
		{
			this->times[j] = room.times[j];
		}
		
	}
	void cloneNoArray(RoomList room)
	{
		this->capacity = room.capacity;
		this->regionName = room.regionName;
		this->roomName = room.roomName;
	}

};

		//prototypes live here
void changeToLowerCase(string &line);											//takes in a string and returns the string in lower case
string splitLine(string &line, char dlim);										//takes in a string and delimiter then splits the line
void parseFile(string roomArray[RAROW][RACOL], RoomList roomlist[98]);				//parses the input file and stores it into the arrays
int convertToNumber(string toConvert);											//takes in a string and returns the integer number
void fillDataStructure(string roomArray[RAROW][RACOL], RoomList rooms[98]);
void parse15(string line, int row, string roomArray[100][17], RoomList room[98]);



/*******************************************************************************************
 *----------------------------------MAIN LIVES HERE!---------------------------------------*
 *******************************************************************************************/
int main()
{
	RoomList roomlist[98];
	string roomArray[RAROW][RACOL];
	parseFile(roomArray, roomlist);
	fillDataStructure(roomArray,roomlist);
	
	//for (int i = 0; i < 100; i++)
	//{
	//	for (int j = 0; j < 17; j++)
	//	{
	//		cout << roomArray[i][j] << " ";
	//	}
	//	cout << endl;
	//}

	//cout << endl << endl;
	//int row = 98;
	//for (int index = 0; index <= 17; index++)
	//{
	//	cout << "roomArray[" << row << "][" << index << "]: " << roomArray[row][index] << endl;
	//}

	//RoomList room;
	//room.setroomName("This is a room");
	//room.setRegionName("This is a region name");
	//room.setCap(25);
	//roomlist[0].printRoomInfo();
	//roomlist[0].clone(room);
	//roomlist[0].printRoomInfo();




	cout << endl;
	system("pause");
	return 0;
}

/******************************************************************
 *parseFile - parses the ad astra csv and intjects into room class*
 ******************************************************************/
void parseFile(string roomArray[100][16], RoomList roomlist[98])
{
	ifstream fin;															//input stream for file reading
	fin.open("Ad Astra LC Room Description List.csv");			//setting the file to open

	RoomList newRoom;														//temp holder for new room information
	string column;															//holds the string info for the comma deliminated parts
	string line;															//holds the full string

	if (fin.is_open())											//checks to see if the file opens
	{
		int row = 0;														//int value for the row or y
		int index = 0;														//int value for the index or x
		int breakLoc = 0;													//int value for the first delimiter location


		while (getline(fin, line, '\n') && row < 100)			//while the file still another line to get
		{	
			changeToLowerCase(line);										//conver to lower case for ease of use
			while (!line.empty() && index <= 17)							//while the there is something in the line and only 17 commas are found
			{
				if ((index == 15) && row != 0)					//if the 15th location is found and its not in the title row
				{
					breakLoc = 0;											
					while (((line[breakLoc + 1] != 'f') && (line[breakLoc] != ',')) || isdigit(line[breakLoc + 1]))	//looking ,f in the file for stopping point
					{
						breakLoc++;
					}

					column = line.substr(0, breakLoc);
					line = line.substr(breakLoc + 1);
					roomArray[row][index] = column;							//sets information in a 2d array

				}
				else											//not the 15th location continue using the standard delimiter
				{
					column = splitLine(line, ',');
					roomArray[row][index] = column;
				}
				index++;
			}
			row++;
			index = 0;
		}
		fin.close();
	}
	else
	{
		cout << "Error occured while trying to open file..." << endl;
	}
}

/********************************************************************
*parse15 - Takes in string, parses by ; and checks for special cases*
*********************************************************************/
void parse15(string line, int row, string roomArray[RAROW][RACOL], RoomList room[98] )
{
	string part;									//a part of the full string
	string temp;									//temperary holder of the comparison string
	std::size_t delim = line.find(';');				//the location of the ; character in the string line
	std::size_t comma = line.find(',');				//the location of the , character in the string line

	string checker[AMAX]							//temp array for comparison reasons
		= { "Computer - Instructor","DVD Player", "LCD Overhead Projector", "Power Point Clicker", "Screen", "Phone - Star",
		"Smart Board", "Speakers", "White Board", "Computer(s) - PC", "Computer(s) - Mac", "Hospital Bed(s)", "Virtual Welder",
		"Manufacturing Energy Technology Machines", "Welding Shop", "Auto Shop", "Printer", "Machine", "Storage Cupboard(s)", "Podium",
		"Document Camera", "Flip Chart", "Changing Room", "Restroom",	"Piano", "3D Printer", "Imaging Lab", "Printmaking",
		"Painting and Drawing Lab", "Sink", "Laptop", "Exam Table", "Human Cadavers in Refrigeration Units", "Refrigerator","Microscope", "Map(s)" };

	while (delim != string::npos)												//while there are still ;'s in the string
	{
		delim = line.find(';');																//the location of the ; character in the string
		part = line.substr(0, delim);														//cuts the line in two at the first ; character found first portion returned
		line = line.substr(delim + 1);														//cuts the line in two at the first ; character found second portion returned
		comma = part.find(',');																//finds a comma in the part of the string

		for (int i = 0; i < AMAX; i++)											//looping through the checker array
		{
			temp = checker[i];																//temp value to hold checker string
			changeToLowerCase(temp);														//converts to lower case for ease of use

			if (part.compare(temp))															//if strings are the same
			{
				room[row].setbRoomSingle(true, i);
				//cout << "room[" << row << "]: " << room[row].getbRoomSingle(i);
			}
			if ((comma != string::npos) && (isdigit(part[part.size()-1])))		//checking for a digit in the string at the last location
			{
				if (isdigit(part[part.size() - 2]))											//checking for a double 
				{
					part = part.substr(part.size() - 2);
				}
				else															//single digit found
				{
					part = part.substr(part.size() - 1);
				}
				room[row].setqRoomSingle(i, convertToNumber(part));							//sets the number found into the parrelel arrays
			}
		}

	}
}

/********************************************************************************
 *fillDataStructure - uses the 2d temp array to fill the RoomList data structure
 *parameters: string line, string roomArray[100][17], RoomList rooms[98]
 *return: void
 ********************************************************************************/
void fillDataStructure(string roomArray[RAROW][RACOL], RoomList rooms[98])
{
	RoomList newRoom;
	string line;
	for (int i = 0; i < 98; i++)										//start putting things in the data structure
	{
		line = roomArray[i+1][15];
		cout << line << endl;
		newRoom.setroomName(roomArray[i+1][6]);
		newRoom.setCap(convertToNumber(roomArray[i+1][14]));
		newRoom.setRegionName(roomArray[i+1][16]);

		//newRoom.setbRoomFeatures();
		parse15(line, i, roomArray, rooms);
		rooms[i].cloneNoArray(newRoom);
	}
}


/*************************************************************
*changeToLowerCase - Takes in string, converts to lower case*
*************************************************************/
void changeToLowerCase(string &line)
{
	int index = 0;
	while (index < line.size())
	{
		line[index] = tolower(line[index]);
		index++;
	}
}


/*************************************************************
*splits the line into parts from the  - Takes in string, converts to lower case*
*************************************************************/
string splitLine(string &line, char dlim)
{
	string col;
	int commaLoc = line.find(dlim);	//delimiter is a white space


	if (commaLoc != string::npos &&(line[0] == dlim && line[1] == dlim && line[2]==dlim))
	{
		col = "";
		line = line.substr(0, 0);
	}
	else if (commaLoc != string::npos)	// string::npos is what string.find() returns if char not found
	{
		col = line.substr(0, commaLoc);
		line = line.substr(commaLoc + 1);
	}
	else 
	{
		col = line;
		line = line.substr(0, 0);
	}
	return col;
}

/*****************************************************
This is our version. just converts a string to an int.
returns the value of the string
*****************************************************/
int convertToNumber(string toConvert)
{
	int size = toConvert.length();	// the number of characters
	int power = size - 1;				// this is the exponent for the base, which is how we convert
	int constantValue = 0;				// the value of the string to return
	for (int k = 0; k < size; k++)
	{
		constantValue += (toConvert[k] - 48) * pow(10, power);
		power--;
	}
	return constantValue;
}


/*----------------------------------------------------------------------------------------------*\
 |	Problems: dealing with a type mismatch between a const string and string					|
 |				 odd memory leaks that have no buisness being in this program at all			|
\*----------------------------------------------------------------------------------------------*/