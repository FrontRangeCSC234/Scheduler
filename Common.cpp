//Author: Lili Gurski


#include "Common.h"

//default consructor
Common::Common()
{
    prefix = "none";
    crs = -1;
    title = "none";
    credits = -1;
}

Common::Common(string prefix, int crs, string title, int credits)
{
    prefix = prefix;
    crs= crs;
    title = title;
    credits = credits;
}


//Getters and Setters
string Common::getPrefix()
{
    return prefix;
}

int Common::getCrs()
{
    return crs;
}

string Common::getTitle()
{
    return title;
}

int Common::getCredits()
{
    return credits;
}

void Common::setPrefix(string setPrefix)
{
    prefix = setPrefix;
}

void Common::setCrs(int setCrs)
{
    crs = setCrs;
}

void Common::setTitle(string setTitle)
{
    title = setTitle;
}

void Common::setCredits(int setCredits)
{
    credits = setCredits;
}
