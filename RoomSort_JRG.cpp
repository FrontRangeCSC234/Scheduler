//James Gillman
//Room Number Sort
//4/14/18
//Sorts roomnumbers using LSD Radix Sort

#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

void radixSort(string testArray[], int dataSize); //Does a Radix sort on the array of data
void lsdSort(string testArray[], int size, int digitLocation); // sorts the array using a copy array and a bucket to keep track of sizes.
int getMax(string testArray[], int n); //Gets the highest amount of letters that are in the a string

int main()
{
    string testArray[] = {
            "BP113",
            "LBP332",
            "CP992",
            "AP123",
            "AB134",
            "A1"
    }; //TEST DATA.

    int dataSize = (int)(sizeof(testArray) / sizeof(testArray[0])); //How many strings are in the array?

    cout << ("BEFORE SORTING:") << endl;
    for (size_t i = 0; i < dataSize; i++)
    {
        cout << testArray[i] << endl;
    }
    radixSort(testArray, dataSize);
   cout << ("AFTER SORTING") << endl;
    for (size_t i = 0;i < dataSize; i++)
    {
       cout << testArray[i] << endl;
    }
    system("pause");
    return 0;

}

/*************************************************************************************************************
 * methodName: getMax
 * Author: James (Ron) Gillman [SafetyPanda]
 * Parameters: testArray: Array of words (will be changed to actual data), dataSize: amount of words in the array
 * Description: Gets the max data for the radix sort. Shouldn't need this but for testing purposes is nice.
 * Return: int
 ************************************************************************************************************/
int getMax(string testArray[], int dataSize)
{
    int max = testArray[0].size(); //Largest string size in the array
    for (int i = 1; i < dataSize; i++)
    {
        if (testArray[i].size()>max)
            max = testArray[i].size();
    }
    return max;
}

/*************************************************************************************************************
 * methodName: lsdSort
 * Author: James (Ron) Gillman [SafetyPanda]
 * Parameters: testArray: Array of test words, size: how mig is the array, digitLocation: Which character are we at?
 * Description: sorts the array using a lsd Radix sort, by converting to an integer and sorting it that way.
 * Return: void
 *************************************************************************************************************/
void lsdSort(string testArray[], int size, int digitLocation)
{
    string *copyArray = NULL; //Holds sorted words.
    int *lengthBucket = NULL; //Holds length of words.
    copyArray = new string[size];
    lengthBucket = new int[1000];



    for (int i = 0; i <1000; i++)
    {
        lengthBucket[i] = 0;
    }

    for (int j = 0; j <size; j++)
    {
        lengthBucket[digitLocation < testArray[j].size() ? (int) testArray[j][digitLocation] + 1 : 0]++;
    }

    for (int f = 0; f <1000; f++)
    {
        lengthBucket[f] += lengthBucket[f - 1];
    }

    for (int r = size - 1; r >= 0; r--)
    {
        copyArray[lengthBucket[(digitLocation < testArray[r].size() ? (int) testArray[r][digitLocation] + 1 : 0)] - 1] = testArray[r];
        lengthBucket[digitLocation < testArray[r].size() ? (int) testArray[r][digitLocation] + 1 : 0]--;
    }

    for (int l = 0; l < size; l++)
    {
        testArray[l] = copyArray[l];
    }

    ////////////////////////////////
    // NO MEMORY LEAKS HERE MATEY //
    ////////////////////////////////

    delete[] copyArray;
    delete[] lengthBucket;
}

/*********************************************************************************************************************
 * methodName: radixSort
 * Author: James (Ron) Gillman [SafetyPanda]
 * Paramters: testArray: Array of test strings. dataSize: amount of words in the array
 * Description: Sorts the array by going through the characters of a string one by one
 * Return: void
 *********************************************************************************************************************/

void radixSort(string testArray[], int dataSize)
{
    int max = getMax(testArray, dataSize); //Biggest data Size.
    for (int digit = max; digit > 0; digit--)
    {
        lsdSort(testArray, dataSize, digit - 1);
    }

}