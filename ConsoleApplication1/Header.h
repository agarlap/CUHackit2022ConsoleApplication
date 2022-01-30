#pragma once

#include <chrono>
#include <thread>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
using namespace std;

//Clock struct
struct CLOCK {
    int hours;
    int minutes;
    int seconds;
    string AMPM1;
    string AMPM2;
};

//Tasks struct
struct TASKS {
    string name;
    int priorty;
    double duration;
    string currentDay;
    string dueDay;
};

void timeDifference(struct CLOCK, struct CLOCK, struct CLOCK*);
void timer(int hours, int min, int sec);
int printMenu(int userPick);
void bubblesortprioritize(struct TASKS TaskArray[], int number);
void switchentries(struct TASKS * xp, struct TASKS * yp);

//switch entries helper method for bubblesortprioritize
void switchentries(struct TASKS * xp, struct TASKS * yp)
{
    struct TASKS temp = *xp;
    *xp = *yp;
    *yp = temp;
}

//Bubble sort function
void bubblesortprioritize(struct TASKS TaskArray[], int number)
{
    int i, j;
    for (i = 0; i < number - 1; i++)
    {
        // Last i elements are already in place 
        for (j = 0; j < number - i - 1; j++)
        {
            if (TaskArray[j].priorty < TaskArray[j + 1].priorty)
            {
                switchentries(&TaskArray[j], &TaskArray[j+1]);
            }
        }
    }
}

//Timer function
void timer(int hours, int min, int sec) {
    for (;;) { //infinite loop
        if (hours == 0 && min == 0 && sec == 0) {
            break;
        }
        if (sec == 0 && min == 0) {
            min = 60;
            hours--;
        }
        if (sec == 0) {
            sec = 60;
            min--;
        }
        this_thread::sleep_for(chrono::milliseconds(1000));
        cout << hours << ":" << min << ":" << sec-- << endl;
    }
}

void timeDifference(struct CLOCK wakeup, struct CLOCK sleep, struct CLOCK* activeHours) {

    if (wakeup.AMPM1 != sleep.AMPM2) {
        sleep.hours += 12;
    }

    if (wakeup.seconds > sleep.seconds) {
        --sleep.minutes;
        sleep.seconds += 60;
    }
    activeHours->seconds = sleep.seconds - wakeup.seconds;
    if (wakeup.minutes > sleep.minutes) {
        --sleep.hours;
        sleep.minutes += 60;
    }
    activeHours->minutes = sleep.minutes - wakeup.minutes;
    activeHours->hours = sleep.hours - wakeup.hours;
}

// menu function to display menu
int printMenu(int userPick) {
    cout << "===================================" << endl;
    cout << "MENU" << endl;
    cout << "1. Create Task" << endl;
    cout << "2. See Tasks" << endl;
    cout << "3. Print Planned Tasks So Far" << endl;
    cout << "4. Sort Tasks Based on Priority" << endl;
    cout << "5. Store Tasks in Calendar" << endl;
    cout << "6. Print Calendar of Tasks" << endl;
    cout << "7. Clear out List of Tasks" << endl;
    cout << "8. Clear out Stored Calendar" << endl;
    cout << "9. Quit" << endl;
    cout << "===================================" << endl;

    cin >> userPick;
    return userPick;
}

