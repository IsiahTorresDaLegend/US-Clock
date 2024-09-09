/*

main.cpp
Revamped to use smart pointers (shared pointer).
U.S. Clock, takes a time and converts it to another time zone in the U.S. and territories
Written by Isiah Torres for course CSC 275

*/
//================================================================================================
#include <iostream>
#include <stdexcept> // invalid_argument exception class
#include "Time.h" // definition of class Time 
#include "TimeZones.h" // definition of class TimeZones
#include "USClockPrototypes.h" // prototypes for additional functions. 
#include <vector> // allows use of vectors (like dynamic arrays) 
using namespace std;

//================================================================================================

int main() 
{
    Time t; // instantiate object t of class Time
    
    // Official U.S. time zones. According to NIST at time.gov.
    // create a shared pointer and instantiate a TimeZone object for each U.S. time zone.

    // Syntax for using smart pointers:
    // smart_pointer_type<data_type>pointer_name(new data_type());
    // Notice we use TimeZone's constructor.
    shared_ptr<TimeZone> PDT(new TimeZone("Pacific Daylight Time", 7)); // each Zone has a full name and a time change
    shared_ptr<TimeZone> MDT(new TimeZone("Mountain Daylight Time", 6)); // first parameter of the constructor sets the
    shared_ptr<TimeZone> CDT(new TimeZone("Central Daylight Time", 5)); // full name (string), and the second parameter
    shared_ptr<TimeZone> EDT(new TimeZone("Eastern Daylight Time", 4)); // sets the time change from UTC. Time change has
    shared_ptr<TimeZone> MST(new TimeZone("Arizona Mountain Standard Time", 7)); // been inverted to do the math easier.

    // for instance PDT is UTC -7, so we set the time change to 7. CHST is UTC +10, so the
    // time change is set to -10.
    // we do the math with the timeDifference() and convertTime().

    // non-contiguous U.S. and territories
    shared_ptr<TimeZone> AKDT(new TimeZone("Alaska Daylight Time", 8));
    shared_ptr<TimeZone> HST(new TimeZone("Hawaii Standard Time", 10));
    shared_ptr<TimeZone> HADT(new TimeZone("Aleutian Daylight Time", 9));
    shared_ptr<TimeZone> SST(new TimeZone("Samoa Standard Time", 11));
    // CHST is UTC +10 so we change the time change to -10 to work with the math.
    shared_ptr<TimeZone> CHST(new TimeZone("Chamorro Standard Time", -10)); 
    shared_ptr<TimeZone> AST(new TimeZone("Puerto Rico Atlantic Standard Time", 4));
    
    char repeat = 'y';
    while (repeat == 'y')
    {
        system("cls"); // sends the "cls" command to Windows consoles to clear the screen.
        
        cout << "\n\n";
        // use a Raw String Literal 'R"()"' to add ascii art from ascii.today.
        cout << R"( ___  ___      ________               ________  ___       ________  ________  ___  __       
|\  \|\  \    |\   ____\             |\   ____\|\  \     |\   __  \|\   ____\|\  \|\  \     
\ \  \\\  \   \ \  \___|_            \ \  \___|\ \  \    \ \  \|\  \ \  \___|\ \  \/  /|_   
 \ \  \\\  \   \ \_____  \            \ \  \    \ \  \    \ \  \\\  \ \  \    \ \   ___  \  
  \ \  \\\  \ __\|____|\  \  ___       \ \  \____\ \  \____\ \  \\\  \ \  \____\ \  \\ \  \ 
   \ \_______\\__\____\_\  \|\__\       \ \_______\ \_______\ \_______\ \_______\ \__\\ \__\
    \|_______\|__|\_________\|__|        \|_______|\|_______|\|_______|\|_______|\|__| \|__|
                 \|_________|)";
        cout << "\n\n";

        // Short description of the program.
        cout << "This is a U.S. Clock. This can be used to see what time it would be in another \n"
            << "time zone within the U.S. and territories. Enter a time in 24 - hour format, \n"
            << "select a time zone to start from, then select the time zone to convert it to.\n";

        askTime(t); // pass Time object by reference to set data member values. 

        // create a vector of shared pointers to TimeZone objects.
        vector<shared_ptr<TimeZone>> timeZones{ PDT, MDT, CDT, EDT, MST, AKDT, HST,
        HADT, SST, CHST, AST };

        cout << "\n\nSelect the current time zone: (enter 1 - 11)\n";
        int i = 0;  // initialize variable to use as a counter in the following loop.
        // This is a range-based for loop. timeZones is the vector it will go through, for each
        // element of this vector, const is included to ensure no changes occur. 
        // auto is a keyword for conveinence that allows the compiler to deduce the data type.
        // allows us to save typing, but the data type would be shared_ptr<TimeZone>& ...
        // which is a reference to a shared pointer to a timezone object.
        for (const auto& timeZonePtr : timeZones)
        {
            i++; // increment the counter
            // display a list of the elements using the counter and the getFullName() method. 
            // using pointer notation ->
            cout << i << ": " << timeZonePtr->getFullName() << "\n";
        }

        // create a new shared pointerobject for the users starting time zone.
        shared_ptr<TimeZone> usersZone; 
        int choice; // create a variable to represent the user's choice
        bool success = false; // use success to determine when loop should finish

        do // do loop to perform actions at least once. 
        {
            cin >> choice;

            // prevent us from being stuck in an error state after invalid input.
            if (cin.fail()) // Check if input operation failed
            {
                cin.clear(); // Clear the error state
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the rest of the buffer
                cin.sync(); // discard the characters in the input buffer.
            }

            switch (choice) // switch statement used to determine how to proceed based on user's choice
            {
            case 1: // if user types one,
                // one shared pointer will point to another, more efficient than copying data.
                usersZone = PDT; 
                success = true; // stop the do loop.
                break;
            case 2:
                usersZone = MDT; // same as above, but respectively for all the other objects.
                success = true;
                break;
            case 3:
                usersZone = CDT;
                success = true;
                break;
            case 4:
                usersZone = EDT;
                success = true;
                break;
            case 5:
                usersZone = MST;
                success = true;
                break;
            case 6:
                usersZone = AKDT;
                success = true;
                break;
            case 7:
                usersZone = HST;
                success = true;
                break;
            case 8:
                usersZone = HADT;
                success = true;
                break;
            case 9:
                usersZone = SST;
                success = true;
                break;
            case 10:
                usersZone = CHST;
                success = true;
                break;
            case 11:
                usersZone = AST;
                success = true;
                break;
            default: // if user selects anything besides 1 - 11, display this error message...
                cout << "\nInvalid option, select a time zone by entering a number 1 - 11.\n";
            }
        } while (success == false); // ... then restart loop until success == true.


        displayTime("Current Time: ", t, usersZone); // show user the time and zone chosen.

        cout << "Select which time zone to convert to: (enter 1 - 11)\n";

        i = 0; // restart counter to use it again in this for loop.
        for (const auto& timeZonePtr : timeZones) // display each element in the vector again
        {
            // user i as the number in the list, and getFullName() to display the options.
            i++;
            cout << i << ": " << timeZonePtr->getFullName() << "\n";
        }

        // this new shared pointer will be the zone to convert the time to.
        shared_ptr<TimeZone> newZone;  
        int choice2; // second choice for second switch statement.
        success = false; // reset success to use again with a new do loop.
        do // do this action at least once.
        {
            cin >> choice2; // take user input for choice2

            if (cin.fail()) // Check if input operation failed
            {
                cin.clear(); // Clear the error state
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the rest of the buffer
                cin.sync(); // discard the characters in the buffer.
            }

            switch (choice2) // use a switch statment to determine which zone to convert object t to. 
            {
            case 1:
                // assign the new shared pointer to one of the other shared pointers.
                newZone = PDT; // same logic as previous switch. User will select a number 1 - 11.
                success = true; // the corresponding object will assign their data member values to
                break; // the new object. success will end the do loop, and break will end the switch.
            case 2:
                newZone = MDT;
                success = true;
                break;
            case 3:
                newZone = CDT;
                success = true;
                break;
            case 4:
                newZone = EDT;
                success = true;
                break;
            case 5:
                newZone = MST;
                success = true;
                break;
            case 6:
                newZone = AKDT;
                success = true;
                break;
            case 7:
                newZone = HST;
                success = true;
                break;
            case 8:
                newZone = HADT;
                success = true;
                break;
            case 9:
                newZone = SST;
                success = true;
                break;
            case 10:
                newZone = CHST;
                success = true;
                break;
            case 11:
                newZone = AST;
                success = true;
                break;
            default:
                cout << "\nInvalid option, select a time zone by entering a number 1 - 11.\n";
            }
        } while (success == false);

        Time newTime; // a new time object is created to represent the converted time. 
        // the difference in hours from the two time zones are calculated first using each zone's 
        // timeChange member.
        // Use pointer notation to have the shared pointers return a data member value. 
        int difference = timeDifference(usersZone->getTimeChange(), newZone->getTimeChange());
        // Once the difference in hours has been found, the newHour is found by using t's hour member
        // and the difference in time zones. newHour will always be an unsigned int as the valid range
        // is from 0 - 23.
        unsigned int newHour = convertTime(t.getHour(), difference);
        newTime = t; // assign t's data member values to newTime's data members.
        try // theoretically, this should always be successful... try to perform these actions...
        {
            newTime.setHour(newHour); // we change only the hour member to the proper hour calculated.
            cout << "\nConversion done!\n"; // inform user of successful operation.
        }
        catch (invalid_argument& e) // if there is an exception thrown, catch it and display it.
        {
            cout << e.what() << "\n"
                << "Unable to convert time accurately.\n\n"; // inform user that time has not converted

        }

        displayTime("INITIAL TIME ", t, usersZone); // display the initial time and time zone
        displayTime("CONVERTED TIME ", newTime, newZone); // display the converted time and time zone

        askRepeat(repeat); // Ask user if they would like to run the program again.
        
    }
}