/*

TimeZones.h
Class definition for creating US time zones
Written by Isiah Torres

*/
//================================================================================================
// Include Guard
#ifndef TIMEZONES_H // if TimeZones.h is not already defined...
#define TIMEZONES_H // then define this header file so compiler can include it. 

//================================================================================================
#include <string>
#include <iostream>
using namespace std;

//================================================================================================
class TimeZone
{

// 
public: 
	TimeZone(); // default constructor
	TimeZone(string, int); // custom constructor

	~TimeZone(); // default destructor

	// set and get methods
	void setFullName(string); // set fullName
	string getFullName() const; // get fullName

	void setTimeChange(unsigned int); // set timeChange
	int getTimeChange() const; // get timeChange

private: 
	string fullName; // the full name of the time zone.
	int timeChange; // according to UTC, insert amount the of hours in the time change.
};


#endif // if TIMEZONES_H has already been defined then skip over this header file.
