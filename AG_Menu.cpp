#include <iostream>
#include <string>

using namespace std;

// Calls the code to read in the CSVs and create a master file
void createMasterFile()
{
	cout << "Not yet implemented" << endl;
}

// Find CRNs in the range that are not used.
void findUnusedCRNs()
{
	cout << "Not yet implemented" << endl;
}

// Search for a course by CRN to find out everything that needs to be known about it
void searchForCourse()
{
	cout << "Not yet implemented" << endl;
}

// Search for a room to find out everything that needs to be known about it
void searchForRoom()
{
	cout << "Not yet implemented" << endl;
}

// Find all rooms with open timeslots
void findAvailableRooms()
{
	cout << "Not yet implemented" << endl;
}

// Add a course to the schedule
void addCourse()
{
	cout << "Not yet implemented" << endl;
}

int main()
{
	// used to track which operation from the menu to run
	int userChoice;

	cout << "What would you like to do?" << endl;
	cout << "(1) Create a master file." << endl;
	cout << "(2) Find unused CRNs." << endl;
	cout << "(3) Search for a course." << endl;
	cout << "(4) Search for a room." << endl;
	cout << "(5) Find available rooms." << endl;
	cout << "(6) Add a course." << endl;
	cin >> userChoice;

	// Each case is one of the choices that will correspond to a method call
	// This also makes it easy to add more if needed
	switch (userChoice)
	{
	case 1: 
		cout << "case 1" << endl;
		createMasterFile();
		break;
	case 2: 
		cout << "case 2" << endl;
		findUnusedCRNs();
		break;
	case 3:
		cout << "case 3" << endl;
		searchForCourse();
		break;
	case 4: 
		cout << "case 4" << endl;
		searchForRoom();
		break;
	case 5:
		cout << "case 5" << endl;
		findAvailableRooms();
		break;
	case 6:
		cout << "case 6" << endl;
		addCourse();
		break;
	default:
		cout << "Invalid choice" << endl;
		break;
	}

	system("PAUSE");
	return 0;
}

