/*

USClockPrototypes.h
Header file for functions used in the U.S. Clock program.
Written by Isiah Torres

*/
//================================================================================================
// Include guard for USClockPrototypes.h
#ifndef USCLOCKPROTOTYPES_H
#define USCLOCKPROTOTYPES_H

//================================================================================================
#include <string> // to include string arguments
#include "Time.h" // so a Time object can be recognized
#include "TimeZones.h" // so TimeZone objects can be recognized. 
using namespace std;

//================================================================================================

// displayTime() will take a constant string, a constant time object, and a shared pointer.
void displayTime(const string& message, const Time& time, shared_ptr<TimeZone>& zone);

// takes two int types to find the difference in value.
int timeDifference(int from, int to);

// takes an unsigned int and a int to perform calculations for the time objects.
unsigned int convertTime(unsigned int hours, int difference);

// allows user to set time using Time object's method's. Pass by reference to ensure changes.
void askTime(Time&);

// ask user if they would like to run the program again. 
void askRepeat(char&);

#endif // end of include guard for USClockPrototypes.h
