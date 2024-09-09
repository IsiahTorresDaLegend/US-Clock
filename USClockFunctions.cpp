/*

USClockFunctions.cpp
Contains function definitions for the U.S. Clock program.
Written by Isiah Torres

*/
//================================================================================================
#include <iostream>
#include <string>
#include <stdexcept>
#include "Time.h"
#include "TimeZones.h"
using namespace std;

//================================================================================================

// displays a Time in 24-hour and 12-hour formats.
// pass arguments by reference to avoid copying. 
// also takes a shared pointer as argument.
void displayTime(const string& message, const Time& time, shared_ptr<TimeZone>& zone)
{
    // calls member functions to display different formats as strings.
    cout << "\n" << message << "\nUniversal time: " << time.toUniversalString()
        << "\nStandard time: " << time.toStandardString()
        << "\nTime Zone: " << zone->getFullName() << "\n\n"; // pointer calls method 
}

// Calculate time zone difference.
int timeDifference(int from, int to)
{
    // initial time zone value - value of the time zone were converting to.
    // we invert the time change to do the math... for instance, PDT is UTC -7, so time change for
    // that object would be set to 7. To find the difference in hours for say EDT (UTC -4), we can
    // do 7 - 4 = 3 hour difference. This also works if the hours were ahead as well... Ex:
    // PDT (UTC -7) and CHST (UTC +10)... would be 7 -(-10) = 17 hour difference in those zones...
    // which is true. 
    int difference = from - to;
    return difference; // return the answer of the above equation. 
}

// change hour based on time zone difference
unsigned int convertTime(unsigned int hours, int difference)
{
    // hour is the initial hour, difference is the hour difference between one zone and another.
    unsigned int newHour;
    if (hours + difference < 0) // if the sum of the initial hour and the difference is < 0...
    {
        // there are times when the sum would be less than zero, but the range to display 
        // hours is from 0-23. (Ex: inital time is 12am PDT [or hour 0] and the difference 
        // in time zones from PDT to AKST is 7 - 8 = -1. The sum of the initial hour and 
        // the difference is  0 + (-1) = -1... which cannot be used to represent a hour. 
        // however... 24 + (-1) + 0 = 23 which would be 11pm ) this can successfully 
        // demonstrate going back one hour from 12am to 11pm.

        newHour = 24 + difference + hours; // ... use this formula.
    }
    else if (hours + difference > 23) // if the sum is > 23 ...
    {
        // same issue as above except the sum would be greater than the max hour (23)
        // Ex: 8pm PDT or 20 is the initial hour and were trying to convert it to CHST...
        // the difference would be 7 - (-10) = 17, and the sum of the initial hour and the 
        // difference would be 20 + 17 = 37 which cannot represent a hour.
        // however... 20 + 17 - 24 = 13 which would be 1pm. This can successfully demonstrate
        // going forward 17 hours from 8pm to 1pm.
        newHour = hours + difference - 24; // ... use this formula.
    }
    else // if the sum is neither < 0 or > 23 then...
    {
        newHour = hours + difference; // ...this formula will work
    }
    return newHour;
}

// take user input and assign Time object data members to input. 
void askTime(Time& t) // takes a Time object and passes by reference. 
{
    bool success = false; // create a variable so loop knows when to finish.
    do // use a do loop to perform these actions at least once. 
    {
        cout << "Enter the hour: (0-23; 0 would be 12am, 23 would be 11pm.)\n";
        unsigned int hour; // hour should be positive, will use to set time of object t.
        cin >> hour; // store user input in hour.

        // prevent us from being stuck in an error state after invalid input.
        // cin.fail() is used to determine if a stream operation failed.
        if (cin.fail()) // if user enter anything thats not a number...
        {
            // input/output operations won't work correctly until error flags have been reset, 
            cin.clear(); // we use cin.clear() to clear the error flags for cin. 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the rest of the buffer
            cin.sync(); // discard all characters in the input buffer.
            cout << "Exception: Input is not a number.\n";
            continue; // restart loop until proper input is collected. 
        }

        cout << "\nEnter the minute: (0-59)\n";
        unsigned int minute; // minute should also be positive.
        cin >> minute; // assign user input to minute.

        // prevent us from being stuck in an error state after invalid input.
        if (cin.fail()) // Check if input operation failed
        {
            cin.clear(); // Clear the error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the rest of the buffer
            cin.sync(); // discard all characters in the input buffer.
            cout << "Exception: Input is not a number.\n"; // inform user of error
            continue; // restart loop until proper input is collected.
        }

        try // try to use hour and minute as arguments for t.setTime()
        {
            t.setTime(hour, minute);
            success = true; // if no exception is thrown, continue the program. 
        }
        catch (invalid_argument& e) // if an exception is thrown, catch it and display it.
        {
            cout << "Exception: " << e.what() << "\n\n"; // e is the reference to the exception
        } // .what() displays the value of the exception. 
    } while (success == false); // loop again if success still == false.
}

// ask user if they would like to run the program again.
void askRepeat(char& answer) // pass a variable by reference.
{
    char choice; // choice3 created to validate restart program option.
    bool  success = false; // reset success to false to use in do loop.
    do // do this action at least once until user selects a proper option.
    {
        try // try the following actions. 
        {

            cout << "Would you like to run again? (enter y or n)\n";
            cin >> choice; // choice3 should be 'y' or 'n'
            if (cin.fail()) // Check if input operation failed
            {
                cin.clear(); // Clear the error state
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the rest of the buffer
                cin.sync(); // discard the characters in the buffer.
            }
            if (choice == 'y' || choice == 'n') // if choice3 == y or n, repeat the program.
            {
                answer = choice; // while loop continues.
                success = true; // do loop ends.
            }
            else // if choice3 does not equal y or n
            {
                // throw this exception. this is a string, but strings are objects, not 
                // data types... 
                throw "Exception: Invalid answer, please enter 'y' for yes or 'n' for no.\n\n";
            }
        }
        // the exception is essentially an array of characters so to refer to it we must use
        // a pointer.
        catch (const char* e)
        {
            cout << e << endl; // display the exception message to user.
        }

    } while (success == false); // continue loop until successful. 
}