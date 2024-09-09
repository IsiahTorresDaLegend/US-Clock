/*

Time.cpp
Member-function definitions for Time class
Written by Isiah Torres
*/
//================================================================================================
#include <iomanip> // for setw and setfill stream manipulators
#include <stdexcept> // for invalid_argument exception class
#include <sstream> // for ostringstream class
#include <string>
#include "Time.h" // Time class definition

using namespace std;

//================================================================================================

// set new Time value using universal time
void Time::setTime(int h, int m)
{
    // validate hour, minute, and second
    if ((h >= 0 && h < 24) && (m >= 0 && m < 60))
    {
        // if variables are within the proper range, assign the member variables.
        hour = h;
        minute = m;
    }
    else // if variables are out of range...
    {
        // throw an invalid_arguement error. Throw is used with try and catch.
        throw invalid_argument ("hour, minute, and/or second was out of range.");
    }
}

// return time as a string in universal-time format (HH:MM:SS)
string Time::toUniversalString() const 
{
    // setfill specifies the fill character when an integer is output in a field wider than the 
    // number of digits in the value. for instance, if minute == 2, it will be displayed as 02,
    // because the fill character is set to zero. If the number fills the specified field, the 
    // fill character will not be displayed. setfill applies for all subsequent values that are
    // displayed -- it is a sticky setting. Each sticky setting (such as setfill and setprecision)
    // should be restored to its previous setting when its no longer needed. 
    // setw() is used to set the field's width.
    ostringstream output; // create an ostringstream object to use the str() function.
    output << setfill('0') << setw(2) << hour << ":"
    << setw(2) << minute << setw(2);
    return output.str(); // returns the formatted string
}

// return time as string in standard-time format (HH:MM:SS AM or PM)
string Time::toStandardString() const
{
    // ?: is the conditional operator; if the hour is 0 or 12 (am or pm respectively), it appears
    // as 12, otherwise, we use the remainder operator % to have the hour appear as a value from 
    // 1 to 11
    ostringstream output;
    output << ((hour == 0 || hour == 12) ? 12 : hour % 12) << ":"
        << setfill('0') << setw(2) << minute << setw(2)
        << (hour < 12 ? " AM" : " PM"); // if hour is less than 12, display am, otherwise
                                                // display pm.
        return output.str(); // return the formatted string.
}

// set and get methods

// set hour
void Time::setHour(unsigned int h)
{
    if ((h >= 0 && h < 24)) // if h is within the proper range (0-23)...
    {
        hour = h; // then assign h to hour.
    }
    else // otherwise...
    {
        throw invalid_argument("hour was out of range."); // throw an invalid_argument error.
    }
}

// get hour
unsigned int Time::getHour() const
{
    return hour; // return the hour member variable.
}