//Author: Lili Gurski
#include<iostream>;
#include<string>;
using namespace std;
class Common
{
private:
    string prefix;    //the prefix
    int crs;          //the course number
    string title;     //name of the class
    int credits;      //number of credits

public:

    //default constructor
    Common();

    Common(string prefix, int crs, string title, int credits);


    //GETTERS
    string getPrefix ();
    int getCrs();
    string getTitle ();
    int getCredits ();

    //SETTERS
    void setPrefix (string setPrefix);
    void setCrs (int setCrs);
    void setTitle (string setTitle);
    void setCredits (int setCredits);
};



