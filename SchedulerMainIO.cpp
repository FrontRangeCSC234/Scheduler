//Ian Oliver - Heuristic and Main fill for 4/16/2018

#include <iostream>
#include "RoomList.h"
#include "CourseInfo.h"
#include "Schedule.h"
#include "Time.h"

int const ROOMS = 98;
int const COURSES = 1000;

using namespace std;




void menu();	//assumed there was menu
Schedule askComp(CourseInfo cinfo[], RoomList room[]);

int main()
{
	CourseInfo cinfo[COURSES];
	RoomList room[ROOMS];
	Schedule schedule;	//default schedule made by the information 
	Schedule compRec;	//schedule made by the heuristic

	menu();


	//ThisIsABlossom2011TimesTheSizeOfOtherThings

	cout << endl;
	system("pause");
	return 0;
}

void menu()
{
	//put code inside of me
}

/********************************************************************************
 *askComp - takes the information and computer makes a schedule
 *	takes in CourseInfo cinfo[] and RoomList room[]
 *	returns the schedule object
 ********************************************************************************/
Schedule askComp(CourseInfo cinfo[], RoomList room[])
{
	int courseCount = 0;
	int proir = 0;
	string priority[COURSES];
	string priorityA[COURSES];	
	string priorityB[COURSES];	
	string priorityC[COURSES];
	string line;
	Schedule compIdea;
	string requestedTime = "none";
	//morning 0600 - 1200
	//afternoon 1200 - 1700
	//evening 1700 - 2200

	//makes a string formated like [DEPARTMENT_COURSENUM-SECTION@REQUESTEDTIME>REQUESTEDROOM] ex. [MAT_121-601@MORNING>CP120] from data structures
	for (int i = 0; i < COURSES; i++)
	{
		line = "[";
		line = line + cinfo[i].getMyCommons()->getPrefix() + '_' + std::to_string(cinfo[i].getMyCommons()->getCRS()) + '@' +
			requestedTime + '>' + cinfo[i].getPrefRoom() + ']';

		priority[i] = line;
	}
	for (int i = 0; i < COURSES; i++)	//sorts into priority ques
	{
		proir = 0;
		if (room pref is in same dept as class name )
		{
			proir++;
		}
		if (requestedTime != "none")
		{
			proir++;
		}
		if (proir < 2)
		{
			priorityA[i] = priority[courseCount];
		}
		else
		{
			priorityB[i] = priority[courseCount];
		}
		courseCount++;
	}


	//make a priority que based off of heiristic
	//check if course requested to be in a room of the matching department, if true priority++
	//check if course requested to be at a specific time of day, if true priority++
	//check if course requested room is open for use at specified time, if true priority++
	//fill schedule data based on priority que

	return compIdea;
}