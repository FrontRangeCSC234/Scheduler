//Author: Lili Gurski
//Fills an array of common info that course can reference

#include <iostream>
#include <fstream>
#include <string>;
#include "Common.h"

using namespace std;
int main()
{

    Common array [200];

    ifstream fin;
    fin.open("noOnline.csv");

    bool sameTitle = true;    //helps to keep track of duplicates
    bool sameCrs = false;     //helps to keep track of duplciates
    string data;              //the data read in as a string
    int crs = 0;              //the course number
    int credits;              //number of credits
    int  count = 1;           //which column
    string prefix;            //prefix of the class
    int rowCount = 0;        //keeps track for to put into the array
    string title;            //name of the class

    int numData;

    while (getline(fin, data, ','))
    {
            if (data[0] == '1'  || data[0] == '2'||
                data[0] == '3' || data[0] == '4'  || data[0] == '5' || data[0] == '9')
            {
                numData = stoi(data);     //parses info into an int if necessary
                if (numData == crs)
                {
                    sameCrs = true;
                }
            }

            else if (data == title)
            {
                sameTitle = true;
            }

            else
            {
                sameTitle = false;
                sameCrs = false;
            }

            if (count == 2 )
            {
                prefix = data;

            }

            else if (count == 3 && sameCrs != true)
            {

                crs =numData;

            }
            else  if (count == 5 && sameTitle != true)
            {

                title = data;
            }
            else if (count == 6 && sameTitle != true && numData < 6)
            {

                credits = numData;

                array[rowCount].setPrefix(prefix);
                array[rowCount].setCrs(crs);
                array[rowCount].setTitle(title);
                array[rowCount].setCredits(credits);

                rowCount++;

            }


            if (count == 14)
            {

                count = 1;

            }

            else
            {
               count++;
            }

    }


    //prints array mainly for debugging purposes
    for(int i = 0; i < 200; i++)
    {
        cout<<array[i].getPrefix()<<" "<<array[i].getCrs()<<" " <<array[i].getTitle()<<" "<<array[i].getCredits()<<endl;
    }
    fin.close();


    cout<<endl;
    system("pause");
    return 0;
}