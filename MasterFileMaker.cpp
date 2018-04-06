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
const int SECTION = 3;
const int TITLE = 4;   //Added section because it was missing LG
const int CR = 5;
const int DAYS = 6;
const int STARTTIME = 7;
const int ENDTIME = 8;
const int ROOM = 9;
const int CAP = 10;
const int STARTDATE = 11;
const int ENDDATE = 12;
const int LASTNAME = 13;
const int FIRSTNAME = 14;

const int MAX = 10000;
const int COLS = 15;

string master[COLS][MAX];
const string ORDER[COLS] = {"CRN", "PREF","CRS", "SECT",  "TITLE", "CR", "DAYS", "ST TM", "END TM", "ROOM", "CAP", "ST DT", "END DT", "LST NM", "FST NM"};
int indexes[COLS]; // This would be the index of each "important" column in the file being read in

int getHeader(int index);
const int SIZE = 11;

bool containsNewLine(string s);
void printMaster();
string toMilitary(string time);
void writeToMaster();
void fillArray (string files[] );
void initalizeMasterArray ();
int determineIndexes(string file);
void findBlanks();


void outputErrors (string file);
int main()
{

    string files[SIZE] =  {"/home/lili/CLionProjects/untitled1/alliedHealth.csv", "/home/lili/CLionProjects/untitled1/com.csv", "/home/lili/CLionProjects/untitled1/science.csv" , "/home/lili/CLionProjects/untitled1/eco.csv" , "/home/lili/CLionProjects/untitled1/eng.csv", "/home/lili/CLionProjects/untitled1/geo.csv", "/home/lili/CLionProjects/untitled1/hva.csv", "/home/lili/CLionProjects/untitled1/languages.csv", "/home/lili/CLionProjects/untitled1/nursing.csv", "/home/lili/CLionProjects/untitled1/phi.csv", "/home/lili/CLionProjects/untitled1/science.csv"  };
    initalizeMasterArray();
    fillArray(files);
    findBlanks();
    printMaster();




    writeToMaster();












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

            cout<<"\nin the file: " << file << "\nHeader " << ORDER[i] << "' is missing. Make sure to rename it to the correct header name" << endl;
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
//Modified by Lili Gurski
void fillArray(string files[SIZE])
{
    ifstream fin2;
    string cell;
    int goodRow; //number for the function determineIndexes LG
    int row = 0, col = 0;

    for (int i = 0; i < SIZE; i++)
    {
        goodRow = determineIndexes(files[i]);
        if (goodRow != 1)
        {
            fin2.open(files[i]);
            getline(fin2, cell); // get the headers over with BC

            while (getline(fin2, cell, ','))
            {
                if (containsNewLine(cell))
                {
                    row++;
                    col = 0;
                    cell.erase(0, 1); // delete the first character (in this case \n) BC
                }

                //deal with cell here BC
                if (getHeader(col) != -1)
                {
                    master[getHeader(col)][row] = cell;

                }


                //cout << "Row: " << row << " Col: " << col << " Header: " << getHeader(indexes[col]) << " | " << cell << endl;

                col++;

            }
            fin2.close();

            findBlanks();
            outputErrors(files[i]);
        }



    }

}




void outputErrors (string file)
{
    ofstream fout2;     //second outfile that keeps track of errors
    fout2.open("error.csv");
    fout2<<"In the file: "<<file << "Please fix the following errors: "<<endl;


    for (int row = 0; row <MAX; row++)
    {

        for (int col = 0; col < COLS; col++)
        {
            if(master[col][row] == "Row has Error")
            {

            }
                fout2<< "at row " <<row << " column " <<col << " there is missing data "<<endl;   //outputs that
            }
        }

    fout2.close();
}


// Lili Gurski
//Parameters: the file name as a string
//Description: goes through 2D array and then either outputs an error  or a perfect row
void writeToMaster()
{
    ofstream fout;      //first outfile that will be the "master file"

    fout.open("master.csv");

    for (int row = 0; row < MAX; row++)
    {

        for (int col = 0; col < COLS; col++)
        {
            if (master[col][row] != "NONE")   //if the entire row or column has any data LG
            {


                if (master[col][row] != "Row has Error")   //if the row has data that is invalid LG
                {


                    fout << master[col][row] << ",";

                    //for formatting purposes LG
                    if (col == 14)
                    {
                        fout << endl;
                    }

                } else
                {

                }
            }

        }

    }
    fout.close();
}

//Lili Gurski
//Description: if the word in the cell is empty, it makes the entire row invalid so it will skip over it when writing it to outfile

void findBlanks()
{
    for (int col = 0; col < COLS; col++)
    {
        for (int row = 0; row < MAX; row++)
        {
            if (master[col][row].length() == 0 || master[col][row] == "ONLINE")
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
                    master[14][row] = "Row has Error";
                }

            }
        }
    }


//Overall changes I made (LG): made different functions and made prototypes for them, fixed the function writeToMaster, and made new function called findBlanks