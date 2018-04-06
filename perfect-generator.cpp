// Group 1 - Creating the perfect file
#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
using namespace std;
const int CRN = 0;
const int PREF = 1;
const int CRS = 2;
const int TITLE = 3;
const int CR = 4;
const int DAYS = 5;
const int STARTTIME = 6;
const int ENDTIME = 7;
const int ROOM = 8;
const int CAP = 9;
const int STARTDATE = 10;
const int ENDDATE = 11;
const int LASTNAME = 12;
const int FIRSTNAME = 13;

const int MAX = 200;
const int COLS = 14;

string master[COLS][MAX];

const string ORDER[COLS] = {"CRN", "PREF","CRS", "TITLE", "CR", "DAYS", "ST TM", "END TM", "ROOM", "CAP", "ST DT", "END DT", "LST NM", "FST NM"};
int indexes[COLS]; // This would be the index of each "important" column in the file being read in

int getHeader(int index);


bool containsNewLine(string s);
void printMaster();
string toMilitary(string time);
void writeToMaster(string file);
void fillArray (string file );
void initalizeMasterArray ();
int determineIndexes(string file);
void findBlanks();


int main()
{

    string file = "imperfect/com.csv";
    initalizeMasterArray();
    //printMaster(); // This should be empty
    int goodHeaders = determineIndexes(file);
    if (goodHeaders != 1)              //if the determineIndexes returned a zero it won't output to the files LG
    {
        fillArray(file);
        findBlanks();
        printMaster(); // This should be empty

        //------------------------------------Almost Done! change times to military time-----------------------
        for (int i = 0; i < MAX; i++) {
            master[STARTTIME][i] = toMilitary(master[STARTTIME][i]);
            master[ENDTIME][i] = toMilitary(master[ENDTIME][i]);
        }
        writeToMaster(file);

    }










    //---------------------------------Last Step(?) - write to master file------------------------

    return 0;
}

//Branson Camp
//Modifications: moved into it's own separate method LG
void initalizeMasterArray ()
{
    // initialize array elements
    for (int i = 0; i < COLS; i++) {
        for (int j = 0; j < MAX; j++) {
            master[i][j] = "NONE"; // Initialize with NONE so we will know if something is wrong
        }
    }
}

//Branson Camp
//Made into it's own function and made it return a int LG
int determineIndexes(string file )   //passed in file as parameter LG
{


    //---------------------------------READ RAW DATA FROM FILE-----------------------------------
    ifstream fin;
    fin.open(file);   //it is currently working with nursing, can't seem to get it to work i
    //---------------------------------DETERMINE INDEXES----------------------------
    // Indexes are determined to make sure every file is not missing any rows, and every column
    // 		is in the right order

    string headers[100];
    string cell;
    int i = 0;
    int goodHeaders = 0;  //if it has good headers it returns 0 otherwise it returns 1 LG

    // gets headers
    while (!containsNewLine(cell)) {
        //cout << "b" << endl;
        getline(fin, cell, ',');
        headers[i] = cell;
        i++;
    }
    fin.close();


    // initialize index
    for (int i = 0; i < COLS; i++) {
        indexes[i] = 99; // 99 = error
    }
    // gets indexes
    for (int i = 0; i < 100; i++) {
        string header = headers[i];

        // compare to ORDER
        for (int j = 0; j < COLS; j++) {
            if (header == ORDER[j]) {
                indexes[j] = i; // sorry if this is confusing
            }
        }
    }

    // diagnostics - alert user if headers are missing
    for (int i = 0; i < COLS; i++) {
        int index = indexes[i];
        //cout << index << endl;
        if (index == 99) {
            cout << "Header '" << ORDER[i] << "' is missing. Make sure to rename it to the correct header name" << endl;
            goodHeaders = 1;
        }
    }

    return goodHeaders;
}

//Branson Camp
int getHeader(int index)
{
    for (int i = 0; i < COLS; i++) {
        if (indexes[i] == index) {
            return i;
        }
    }
    return -1; // oops something went wrong
}


//Branson Camp
bool containsNewLine(string s)
{
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '\n') {
            return true;
        }
    }
    return false;
}

//Branson Camp
//Modifications Lili Gurski
void printMaster()
{
    for (int col = 0; col < COLS; col++) {
        cout << "=====" << ORDER[col] << "=====" << endl;
        for (int row = 0; row < MAX; row++) {
            if (master[col][row] != "NONE") {

                cout << master[col][row] << endl;
            }
        }
        //cout << endl << endl; // for formatting
    }
}

//Branson Camp
string toMilitary(string time)
{
    // -------------Checks--------------

    // Check if TBA
    if (time == "TBA") {
        return "None";
    }

    // Check if length is correct
    if (time.length() != 6) {
        //cout << "Time format is incorrect: " << time << endl;
        return "NONE";
    }

    //-------------Conversion-------------
    string numberstr = time.substr(0, 4); // example 0150
    string suffix = time.substr(4, 2);  // example PM

    int numbers = stoi(numberstr);

    if (suffix == "am" || suffix == "AM") {
        if (numbers >= 1200) {
            return to_string(numbers-1200);
        } else {
            return to_string(numbers);
        }
    } else if (suffix == "pm" || suffix == "PM") {
        if (numbers >= 1200) {
            return to_string(numbers);
        } else {
            return to_string(numbers+1200);
        }
        return to_string(numbers);
    }
    cout << suffix << endl;
    return "ERROR";
}

//Branson Camp
void fillArray(string file)
{
    ifstream fin2;
    string cell;
    fin2.open(file);
    getline(fin2, cell); // get the headers over with BC
    int row = 0, col = 0;
    int stop;
    while (col < 50)
    {
        getline(fin2, cell, ',');
        if (containsNewLine(cell))
        {
            row++;
            col = 0;
            cell.erase(0, 1); // delete the first character (in this case \n) BC
        }


        //deal with cell here Branson Camp
        if (getHeader(col) != -1)
        {
            master[getHeader(col)][row] = cell;
        }
        cout << "Row: " << row << " Col: " << col << " Header: " << getHeader(indexes[col]) << " | " << cell << endl;

        col++;

    }

    fin2.close();
}

// Lili Gurski
//Parameters: the file name as a string
//Description: goes through 2D array and then either outputs an error  or a perfect row
void writeToMaster(string file)
{
    ofstream fout;      //first outfile that will be the "master file"
    ofstream fout2;     //second outfile that keeps track of errors
    fout.open ("master-test.csv");
    fout2.open("error.csv");
    fout2<<"Please fix the following errors: "<<endl;
    fout2<<"In the file: " << file <<endl;
    for (int row = 0; row < MAX; row++)
    {
        for (int col = 0; col < COLS; col++)
        {
            if (master[col][row] != "NONE")   //if the entire row or column has any data LG
            {


                if (master[col][row]!= "Row has Error")   //if the row has data that is invalid LG
                {


                    fout<<master[col][row]<<",";

                    //for formatting purposes LG
                    if (col == 13)
                    {
                        fout<<endl;
                    }

                }
                else
                {
                    fout2<< "on row " <<row << " there is missing data "<<endl;   //outputs that there was an error in the row in the second file LG
                }
            }
        }

    }

    fout2.close();
}

//Lili Gurski
//Description: if the word in the cell is empty, it makes the entire row invalid so it will skip over it when writing it to outfile

void findBlanks()
{
    for (int col = 0; col < COLS; col++)
    {
        for (int row = 0; row < MAX; row++)
        {
            if (master[col][row].length() == 0 )
            {
                master[0][row] = "Row has Error";
                master[1][row] = "Row has Error";
                master[2][row] = "Row has Error";
                master[3][row] = "Row has Error";
                master[4][row] = "Row has Error";
                master[5][row] = "Row has Error";
                master[6][row] = "Row has Error";
                master[7][row] = "Row has Error";
                master[8][row] = "Row has Error";
                master[9][row] = "Row has Error";
                master[10][row] = "Row has Error";
                master[11][row] = "Row has Error";
                master[12][row] = "Row has Error";
                master[13][row] = "Row has Error";


            }

        }
    }

}

//Overall changes I made (LG): made different functions and made prototypes for them, fixed the function writeToMaster, and made new function called findBlanks
