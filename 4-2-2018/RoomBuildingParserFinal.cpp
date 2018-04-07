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
const string ROOMITEM[AMAX]					//look up array
= { "Computer - Instructor","DVD Player", "LCD Overhead Projector", "Power Point Clicker", "Screen", "Phone - Star",
"Smart Board", "Speakers", "White Board", "Computer(s) - PC", "Computer(s) - Mac", "Hospital Bed(s)", "Virtual Welder",
"Manufacturing Energy Technology Machines", "Welding Shop", "Auto Shop", "Printer", "Machine", "Storage Cupboard(s)", "Podium",
"Document Camera", "Flip Chart", "Changing Room", "Restroom",	"Piano", "3D Printer", "Imaging Lab", "Printmaking",
"Painting and Drawing Lab", "Sink", "Laptop", "Exam Table", "Human Cadavers in Refrigeration Units", "Refrigerator","Microscope", "Map(s)" };


const int RMMAX = 100;
const int RAROW = 99;
const int RACOL = 17;
const int INTERVAL = ((16 * 60) / 5);

/**************************************************************************************************************************************************
*class RoomList
*data members: const string ROOMITEM[], bool bRoomFeatures[], bool times[], int qRoomFeatures[], string roomName, string regionName, int capacity
*Description: class used for storing the information given by the ad astra csv file
**************************************************************************************************************************************************/
class RoomList
{
private:
	
	bool bRoomFeatures[AMAX] = { false };		//parrell array with qRoomFeatures, holds if something is found in the room
	
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
		cout << "roomName: " << this->getroomName();
		cout << ", regionName: " << this->getRegionName();
		cout << ", roomCap: " << this->getCap() << endl;
		for (int i = 0; i < AMAX; i++)
		{
			if (i < 10)
			{
				cout << " ";
			}
			cout << "[" << i << "]: " << bRoomFeatures[i] << ", " << qRoomFeatures[i] << " " << ROOMITEM[i] << endl;
		}
	}
	/////////////////////////////////////
	// GETTERS AND SETTERS BELOW MATEY //
	/////////////////////////////////////
	string getROOMITEMSingle(int row)
	{
		return ROOMITEM[row];
	}

	bool* getbRoomFeatures()
	{
		return this->bRoomFeatures;
	}

	bool getbRoomSingle(int row)
	{
		return bRoomFeatures[row];
	}
	int* getqRoomFeatures()
	{
		return this->qRoomFeatures;
	}
	int getqRoomSingle(int row)
	{
		return qRoomFeatures[row];
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

	void setqRoomSingle(int num, int i)
	{
		this->qRoomFeatures[i] = num;
	}

	void setbRoomFeatures(bool bRoomFeatures[])
	{
		for (int i = 0; i < AMAX; i++)
		{
			this->bRoomFeatures[i] = bRoomFeatures[i];
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
};

//prototypes live here
void changeToLowerCase(string &line);											//takes in a string and returns the string in lower case
string splitLine(string &line, char dlim);										//takes in a string and delimiter then splits the line
void parseFile(string roomArray[RAROW][RACOL], RoomList roomlist[RMMAX]);				//parses the input file and stores it into the arrays
int convertToNumber(string toConvert);											//takes in a string and returns the integer number
void fillDataStructure(string roomArray[RAROW][RACOL], RoomList rooms[RMMAX]);
void parse15(string line, int row, string roomArray[RAROW][RACOL], RoomList room[RMMAX]);
void clone(RoomList croom, RoomList room);
void printRoomList(RoomList room[RMMAX]);



/*******************************************************************************************
*----------------------------------MAIN LIVES HERE!---------------------------------------*
*******************************************************************************************/
int main()
{
	RoomList roomlist[RMMAX];
	string roomArray[RAROW][RACOL];
	cout << "Before parseFile" << endl;
	parseFile(roomArray, roomlist);
	cout << "After parseFile" << endl;
	fillDataStructure(roomArray, roomlist);
	cout << "After fillDataStructure" << endl;



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

	cout << endl;
	system("pause");
	return 0;
}

/******************************************************************
*parseFile - parses the ad astra csv and intjects into room class*
******************************************************************/
void parseFile(string roomArray[RAROW][RACOL], RoomList roomlist[RMMAX])
{
	ifstream fin;															//input stream for file reading
	fin.open("bleh.csv");			//setting the file to open

	RoomList newRoom;														//temp holder for new room information
	string column;															//holds the string info for the comma deliminated parts
	string line;															//holds the full string

	if (fin.is_open())											//checks to see if the file opens
	{
		int row = 0;														//int value for the row or y
		int index = 0;														//int value for the index or x
		int breakLoc = 0;													//int value for the first delimiter location

		while (getline(fin, line, '\n') && (!fin.eof()) && row < RAROW)			//while the file still another line to get
		{
			changeToLowerCase(line);										//conver to lower case for ease of use

			while ((!line.empty()) && (index < RAROW))							//while the there is something in the line and only 17 commas are found
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
				else if ((index == 16) && row != 0)
				{
					column = splitLine(line, ',');
					roomArray[row][index] = column;
					line = "";
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
		
	}
	else
	{
		cout << "Error occured while trying to open file..." << endl;
		system("exit");
	}
	fin.close();
}

/********************************************************************
*parse15 - Takes in string, parses by ; and checks for special cases*
*********************************************************************/
void parse15(string line, int row, string roomArray[RAROW][RACOL], RoomList room[RMMAX])
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

	while (delim != string::npos)													//while there are still ;'s in the string
	{
		delim = line.find(';');																//the location of the ; character in the string
		part = line.substr(0, delim);														//cuts the line in two at the first ; character found first portion returned
		line = line.substr(delim + 1);													//cuts the line in two at the first ; character found second portion returned
		comma = part.find(',');																//finds a comma in the part of the string

		for (int i = 0; i < AMAX; i++)											//looping through the checker array
		{
			temp = checker[i];																//temp value to hold checker string
			changeToLowerCase(temp);														//converts to lower case for ease of use

			if (part == temp)										//if strings are the same
			{
				room[row].setbRoomSingle(true, i);

			}
			else if (part > temp)
			{
				comma = part.find(',');
				if ((comma != string::npos) && (isdigit(part[part.size() - 1])))//checking for a digit in the string at the last location
				{
					if (isdigit(part[part.size() - 2]))										//checking for a double 
					{
						part = part.substr(part.size() - 2);
					}
					else																		//single digit found
					{
						part = part.substr(part.size() - 1);
					}
					room[row].setqRoomSingle(convertToNumber(part), i);				//sets the number found into the parrelel arrays
				}

			}
		}

	}
}

/********************************************************************************
*fillDataStructure - uses the 2d temp array to fill the RoomList data structure
*parameters: string line, string roomArray[100][17], RoomList rooms[98]
*return: void
********************************************************************************/
void fillDataStructure(string roomArray[RAROW][RACOL], RoomList rooms[RMMAX])
{
	RoomList newRoom;
	string line, line2;
	for (int i = 1; i < 99; i++)										//start putting things in the data structure
	{
		line = roomArray[i][15];
		line2 = roomArray[i][16];

		newRoom.setroomName(roomArray[i][5]);
		//cout << newRoom.getroomName() << endl;
		newRoom.setCap(convertToNumber(roomArray[i][14]));
		newRoom.setRegionName(roomArray[i][16]);

		cout << "After parse15[" << i << "]" << endl;
		cout << "newRoom- roomName: " << newRoom.getroomName() << ", cap: " << newRoom.getCap() << ", regionName: " << newRoom.getRegionName() << endl;
		parse15(line, i, roomArray, rooms);
		clone(rooms[i - 1], newRoom);

		cout << "roomName: " << rooms[i - 1].getroomName();
		cout << ", regionName: " << rooms[i - 1].getRegionName();
		cout << ", roomCap: " << rooms[i - 1].getCap() << endl;
		for (int j = 0; j < AMAX; j++)
		{
			if (j < 10)
			{
				cout << " ";
			}
			cout << "[" << j << "]: " << rooms[i - 1].getbRoomSingle(j) << ", " << rooms[i - 1].getqRoomSingle(j) << " " << rooms[i - 1].getROOMITEMSingle(j) << endl;
		}


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


	if (commaLoc != string::npos && (line[0] == dlim && line[1] == dlim && line[2] == dlim))
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
*convertToNumber - takes string and converts it to an int
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

/****************************************************************
*clone - takes info from one RoomList and clones it into another*
*****************************************************************/
void clone(RoomList croom, RoomList room)
{
	croom.setRegionName(room.getRegionName());
	croom.setroomName(room.getroomName());
	croom.setCap(room.getCap());
}

/****************************************************************
*clone - takes info from one RoomList and clones it into another*
*****************************************************************/
void printRoomList(RoomList room[RMMAX])
{
	for (int index = 0; index < RMMAX; index++)
	{
		cout << "roomName: " << room[index].getroomName();
		cout << ", regionName: " << room[index].getRegionName();
		cout << ", roomCap: " << room[index].getCap() << endl;
		for (int i = 0; i < AMAX; i++)
		{
			if (i < 10)
			{
				cout << " ";
			}
			cout << "[" << i << "]: " << room[index].getbRoomSingle(i) << ", " << room[index].getqRoomSingle(i) << " " << room[index].getROOMITEMSingle(i) << endl;
		}
	}
}



/*----------------------------------------------------------------------------------------------*\
|	Problems: dealing with a type mismatch between a const string and string					|
|				 odd memory leaks that have no buisness being in this program at all			|
\*----------------------------------------------------------------------------------------------*/
