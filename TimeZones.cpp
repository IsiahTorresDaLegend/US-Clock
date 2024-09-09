/*

TimeZones.cpp
member-function definitions for TimeZones class
Written by Isiah Torres

*/
//================================================================================================
#include <string>
#include <iostream>
#include "TimeZones.h" // class TimeZones definitions
using namespace std;

//================================================================================================

// Constructors
TimeZone::TimeZone() {}; // default constructor. Used to initialize members based on user's choice
TimeZone::TimeZone(string n, int t) : // custom constructor, short hand syntax to initialize.
	fullName(n), timeChange(t) {}

TimeZone::~TimeZone() // create a destructor for TimeZone objects
{
	// lets user know when a TimeZone has been destroyed.
	// 'this' refers to the current object that is calling the destructor.
	// 'this' is a pointer to the current object.
	cout << "\n" << this->getFullName() << " has been destroyed.";
}
// set and get methods

void TimeZone::setFullName(string n) { fullName = n; } // set fullName.
string TimeZone::getFullName() const { return fullName; } // get fullName.

void TimeZone::setTimeChange(unsigned int t) { timeChange = t; } // set timeChange.
int TimeZone::getTimeChange() const { return timeChange; } // get timeChange.