/*

Time.h 
Time class definition
Written by Isiah Torres
*/
//===============================================================================================
// Include Guard
#ifndef TIME_H
#define TIME_H

//===============================================================================================
#include <string>
using namespace std;

//===============================================================================================

// Time Class Definition
class Time 
{
public:
    void setTime(int, int); // set hour, minute, and second
    string toUniversalString() const; // 24-hour time format string
    string toStandardString() const; // 12-hour time format string


    // set get methods
    void setHour(unsigned int); // setHour is used for the time conversion of another time object.
    unsigned int getHour() const; // will also be used for time conversion. 

private:
    unsigned int hour{0}; // 0-23 (24-hour clock format)
    unsigned int minute{0}; // 0-59 
};

#endif // end of include guard for TIME_H