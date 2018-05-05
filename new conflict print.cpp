//This will only work once we have Common and Course linked.

void printSectionCourseCommonInfo(ostream &outFile, Course classSection)
{
	Common cInfo = classSection.link;  //once the course and common are linked
	outFile << classSection.getCrn() << " " << cInfo.getPrefix() << cInfo.getCrs() << classSection.getSection() << " "
		<< classSection.getTitle() << " " << endl;
	outFile << "     "<< classSection.getClassTimePtr() << "  " << classSection.getRoomNum() << endl;
}


/*There would be a change where the output for the confict is callled.

in schedule
in the method fill 
directly after the call to conflictCheck

here is the new code*/
bool conflict = Sections[index].conflictCheck(*schedule[row][loc]);
if (conflict)
{
	      //print to the screen
	printSectionCourseCommonInfo(cout, Sections[index]);
	cout << "      conflicts with \n";
	printSectionCourseCommonInfo(cout, schedule[row][loc]);
	cout << endl;

		  //print to the file
	printSectionCourseCommonInfo(fout, Sections[index]);
	cout << "      conflicts with \n";
	printSectionCourseCommonInfo(fout, schedule[row][loc]);
	fout << endl;

	full = false;
	break;
}