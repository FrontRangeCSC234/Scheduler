#include "Schedule.h"



Schedule::Schedule()
{
}

Schedule::Schedule(Room rms[])
{
	rooms = rms;
}


Schedule::~Schedule()
{
}

void Schedule::placeCourse(int index, Course* newCourse)
{
	if (rooms[index].checkRequirements(newCourse))
	{
		int i = 0;
		while (schedule[index][i] != nullptr && i < 100)
		{
			if (newCourse->checkConflict(schedule[index][i]))
			{
				cout << "Conflict" << endl;
				return;
			}
			else
			{
				i++;
			}
		}
		schedule[index][i] = newCourse;
	}
}
