#pragma once
class Schedule
{
private:
	Course* schedule[98][100];
	Room* rooms;
public:
	Schedule();
	Schedule(Room rms[]);
	~Schedule();
	void placeCourse(int index, CourseInfo* newCourse);
};

