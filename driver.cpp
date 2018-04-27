//Question, what does parse15 mean?
//

#include <iostream>
#include <string>
#include <fstream>
#include <ostream>
#include "Room.h"
using namespace std;

int main()
{
	int row=0;
	int num;
	int wordLength;
	string word;
	string line;
	string crs;
	string prefix;
	string roomNumber;
	string nameArray[RMMAX];
	ifstream inFile;
	ofstream fout;
	Room roomList[RMMAX];

	
	fillRoomArray(roomList, nameArray);
	

	inFile.open("MASTER.csv");
	fout.open("MASTER_MKII.txt");
	getline(inFile, line, '\n');
	while (!inFile.eof())			// For getting the lines from the file.
	{

		wordLength = line.find(',');
		if (wordLength <= 0)
		{
			continue;
		}

		// CRN
		word = line.substr(0, wordLength);
		fout << word << ", ";
		line = line.substr(wordLength + 1, line.length());

		// Prefix
		wordLength = line.find(',');
		prefix = line.substr(0, wordLength);
		fout << prefix << ", ";
		line = line.substr(wordLength + 1, line.length());

		// CRS
		wordLength = line.find(',');
		crs = line.substr(0, wordLength);
		fout << crs << ", ";
		line = line.substr(wordLength + 1, line.length());

		// SECTION NUMBER
		wordLength = line.find(',');
		word = line.substr(0, wordLength);
		fout << word << ", ";
		line = line.substr(wordLength + 1, line.length());

		// course name
		wordLength = line.find(',');
		word = line.substr(0, wordLength);
		fout << word << ", ";
		line = line.substr(wordLength + 1, line.length());

		// credits
		wordLength = line.find(',');
		word = line.substr(0, wordLength);
		fout << word << ", ";
		line = line.substr(wordLength + 1, line.length());

		// DAYS OF WEEK
		wordLength = line.find(',');
		word = line.substr(0, wordLength);
		fout << word << ", ";
		line = line.substr(wordLength + 1, line.length());

		// START TIME
		wordLength = line.find(',');
		word = line.substr(0, wordLength);
		fout << word << ", ";
		line = line.substr(wordLength + 1, line.length());

		// END TIME
		wordLength = line.find(',');
		word = line.substr(0, wordLength);
		fout << word << ", ";
		line = line.substr(wordLength + 1, line.length());

		// ROOM NUMBER
		wordLength = line.find(',');
		roomNumber = line.substr(0, wordLength);
		changeToLowerCase(roomNumber);
		fout << roomNumber << ", ";
		line = line.substr(wordLength + 1, line.length());

		// CAPACITY
		wordLength = line.find(',');
		word = line.substr(0, wordLength);
		fout << word << ", ";
		line = line.substr(wordLength + 1, line.length());

		// START DATE
		wordLength = line.find(',');
		word = line.substr(0, wordLength);
		fout << word << ", ";
		line = line.substr(wordLength + 1, line.length());

		// END DATE
		wordLength = line.find(',');
		word = line.substr(0, wordLength);
		fout << word << ", ";
		line = line.substr(wordLength + 1, line.length());

		// TEACHER LAST NAME
		wordLength = line.find(',');
		word = line.substr(0, wordLength);
		fout << word << ", ";
		line = line.substr(wordLength + 1, line.length());

		// TEACHER FIRST NAME  last item in the master file.
		fout << line << ", ";
		num = 0;
		while (!(roomList[num].getRoomName() == roomNumber && num < RAROW))  //find the room  could be changed to a binary search if array is in order
		{
			num++;
		}
		if (num < RMMAX)   //room was found
		{
			for (int index = 0; index < AMAX; index++)
			{
				if (roomList[num].getbRoomFeatures()[index])  //boolean array
				{
					fout << ROOMITEM[index] << ", ";
					fout << roomList[num].getqRoomFeatures()[index] << ", ";
				}
			}
		}
		else
		{
			fout << "error room wasn't found major problem";
			system("pause");

		}
		row++;
		fout << endl;
		getline(inFile, line, '\n');
	}
	fout.close();
	inFile.close();
	system("pause");
}