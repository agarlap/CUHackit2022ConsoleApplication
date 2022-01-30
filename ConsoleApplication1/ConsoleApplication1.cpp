//
//  main.cpp
//  CUhackit_plannter
//
//  Created by Joseph Suter, Rich Bozard,  Aman Garlapati on 1/29/22.
//
//
//  main.cpp
//  CUhackit_plannter
//
//  Created by Joseph  Suter on 1/29/22.
//
#include "Header.h"
using namespace std;

int main() {

    // Sets Users Name
    string userName;
    cout << "Please enter name: ";
    cin >> userName;
    cout << userName << endl;

    //Set Week up
    struct CLOCK wakeup, sleep, activeHours;

    cout << "What time do you start your day (Type the time in 'Hours min seconds am/pm' form): " << endl;
    cin >> wakeup.hours >> wakeup.minutes >> wakeup.seconds >> wakeup.AMPM1;

    cout << "What time do you end your day (Type the time in 'Hours min seconds am/pm' form): " << endl;
    cin >> sleep.hours >> sleep.minutes >> sleep.seconds >> sleep.AMPM2;

    timeDifference(wakeup, sleep, &activeHours);

    //Display activeHours
    cout << "Daily hours " << activeHours.hours << " hours, " << activeHours.minutes << " minutes, " << activeHours.seconds << " seconds" << endl;

    double workSeconds = (activeHours.hours * 3600) + (activeHours.minutes * 60) + (activeHours.seconds);
    double workWeekHours = (workSeconds * 5) / 3600;
    cout << "Weekly Hours " << workWeekHours;
    cout << endl;

    //Task Array
    int currenttasknum = 0;
    struct TASKS TaskArray[25];

    int choice = 0;
    int printingentry = 0;

    string businessdays[5] = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday" };
    int todayindex = 0;
    int duedayindex = 0;
    int businessdayshourlimit[5] = { workWeekHours / 5, workWeekHours / 5, workWeekHours / 5, workWeekHours / 5,  workWeekHours / 5 };

    //our map data structure used to store the tasks in a map using the days of the week as keys
    map<string, vector<struct TASKS>> calendar_schedular_mapping;
    map<string, vector<struct TASKS>>::iterator itr; // some iterator for traversal

    //make empty vectors for each day key
    calendar_schedular_mapping.insert(pair<string, vector<struct TASKS>>(businessdays[0], vector<struct TASKS>()));
    calendar_schedular_mapping.insert(pair<string, vector<struct TASKS>>(businessdays[1], vector<struct TASKS>()));
    calendar_schedular_mapping.insert(pair<string, vector<struct TASKS>>(businessdays[2], vector<struct TASKS>()));
    calendar_schedular_mapping.insert(pair<string, vector<struct TASKS>>(businessdays[3], vector<struct TASKS>()));
    calendar_schedular_mapping.insert(pair<string, vector<struct TASKS>>(businessdays[4], vector<struct TASKS>()));

    while (choice != 10) {
        choice = printMenu(choice);
        if (choice == 1) {

            string taskname;
            double workTime;
            string today;
            string dueday;

            cout << "enter the name of the task:" << endl;
            //cin >> taskname;
            cin.ignore();
            getline(cin, taskname);
            cout << "enter time estimated duration of task: ";
            cin >> workTime;
            cout << "enter the current day: " << endl;
            cin >> today;
            cout << "enter the day task must be done:" << endl;
            cin >> dueday;

            TaskArray[currenttasknum].name = taskname;
            TaskArray[currenttasknum].duration = workTime;
            TaskArray[currenttasknum].currentDay = today;
            TaskArray[currenttasknum].dueDay = dueday;

            // calculating priority
            if (today == "Monday")
            {
                todayindex = 0;
            }
            else if (today == "Tuesday")
            {
                todayindex = 1;
            }
            else if (today == "Wednesday")
            {
                todayindex = 2;
            }
            else if (today == "Thursday")
            {
                todayindex = 3;
            }
            else if (today == "Friday")
            {
                todayindex = 4;
            }
            else
            {

            }

            if (dueday == "Monday")
            {
                duedayindex = 0;
            }
            else if (dueday == "Tuesday")
            {
                duedayindex = 1;
            }
            else if (dueday == "Wednesday")
            {
                duedayindex = 2;
            }
            else if (dueday == "Thursday")
            {
                duedayindex = 3;
            }
            else if (dueday == "Friday")
            {
                duedayindex = 4;
            }
            else
            {

            }

            TaskArray[currenttasknum].priorty = 5 - (duedayindex - todayindex);

            // increment currenttasknum count to prepare for the next task to be created
            currenttasknum = currenttasknum + 1;
        }
        else if (choice == 2) {
            if (currenttasknum != 0)
            {
                cout << "|          TASK          | PRIORITY | TIME (HOURS) | START DAY | DUE DAY |" << endl;
                cout << "-----------------------------------------------------" << endl;
                for (int i = 0; i < currenttasknum; i++) {
                    cout << TaskArray[i].name << " " << TaskArray[i].priorty << " " << TaskArray[i].duration << " " << TaskArray[i].currentDay << " " << TaskArray[i].dueDay << endl;
                }
                cout << "-----------------------------------------------------" << endl;
            }
            else
            {
                cout << "NO TASKS CREATED!" << endl;
            }
        }
        else if (choice == 3) {
            
            // Create and open a text file
            ofstream MyFile("mylistoftasks.txt");

            // adding things into our text file
            if (currenttasknum != 0)
            {
                MyFile << "|          TASK          | PRIORITY | TIME (HOURS) | START DAY | DUE DAY |" << endl;
                MyFile << "-----------------------------------------------------" << endl;
            }

            while (printingentry != currenttasknum)
            {
                // Write to the file
                MyFile << "|" << TaskArray[printingentry].name << " |     " << TaskArray[printingentry].priorty << "     |     " << TaskArray[printingentry].duration << "     | " << TaskArray[printingentry].currentDay << " | " << TaskArray[printingentry].dueDay << " |" << endl;
                printingentry = printingentry + 1;
            }

            if (currenttasknum != 0)
            {
                MyFile << "-----------------------------------------------------" << endl;
            }

            // Close the file
            MyFile.close();

            printingentry = 0;
        }
        else if (choice == 4) {
            if (currenttasknum != 0 && currenttasknum != 1)
            {
                bubblesortprioritize(TaskArray, currenttasknum);
            }
            else
            {
                cout << "CANNOT SORT! MUST HAVE AT LEAST 2 TASKS!";
            }
        }
        else if (choice == 5)
        {
            // store sorted tasks in calendar using the days as keys
            for (int j = 0; j < currenttasknum; j++)
            {
                // store highest priority tasks first and use the current day as the key
                // keep doing this until the day limit of the particular current day is reached
                int tempdayindex = 0;
                if (TaskArray[j].currentDay == "Monday")
                {
                    tempdayindex = 0;
                }
                else if (TaskArray[j].currentDay == "Tuesday")
                {
                    tempdayindex = 1;
                }
                else if (TaskArray[j].currentDay == "Wednesday")
                {
                    tempdayindex = 2;
                }
                else if (TaskArray[j].currentDay == "Thursday")
                {
                    tempdayindex = 3;
                }
                else if (TaskArray[j].currentDay == "Friday")
                {
                    tempdayindex = 4;
                }
                else
                {

                }

                /*
                if (TaskArray[j].duration <= businessdayshourlimit[tempdayindex])
                {
                    calendar_schedular_mapping[TaskArray[j].currentDay].push_back(TaskArray[j]);
                    businessdayshourlimit[tempdayindex] = businessdayshourlimit[tempdayindex] - TaskArray[j].duration;
                }
                else
                {
                    //overflowing case in case a day is full of tasks to where the current task isn't placeable in the current day
                    tempdayindex = tempdayindex + 1;
                    calendar_schedular_mapping[businessdays[tempdayindex]].push_back(TaskArray[j]);
                    businessdayshourlimit[tempdayindex] = businessdayshourlimit[tempdayindex] - TaskArray[j].duration;
                }
                */
                while (TaskArray[j].duration > businessdayshourlimit[tempdayindex])
                {
                    tempdayindex = tempdayindex + 1;
                }

                calendar_schedular_mapping[businessdays[tempdayindex]].push_back(TaskArray[j]);
                businessdayshourlimit[tempdayindex] = businessdayshourlimit[tempdayindex] - TaskArray[j].duration;
            }

            cout << businessdayshourlimit[0] << " " << businessdayshourlimit[1] << " " << businessdayshourlimit[2] << " " << businessdayshourlimit[3] << " " << businessdayshourlimit[4] << endl;
        }
        else if (choice == 6)
        {
            // print calendar of tasks
            for (int k = 0; k < 5; k++)
            {
                cout << businessdays[k] << ":\n";

                for (int l = 0; l < calendar_schedular_mapping[businessdays[k]].size(); l++)
                {
                    cout << "\t";
                    cout << calendar_schedular_mapping[businessdays[k]].at(l).name << ' ';
                    cout << calendar_schedular_mapping[businessdays[k]].at(l).priorty << ' ';
                    cout << calendar_schedular_mapping[businessdays[k]].at(l).duration << ' ';
                    cout << calendar_schedular_mapping[businessdays[k]].at(l).currentDay << ' ';
                    cout << calendar_schedular_mapping[businessdays[k]].at(l).dueDay << endl;
                }
            }
        }
        else if (choice == 7)
        {
            // print calendar contents to a separate text file

            // Create and open a text file
            ofstream MyFile2("mycalendaroftasks.txt");

            // adding things into our text file
            for (int k = 0; k < 5; k++)
            {
                MyFile2 << businessdays[k] << ":\n";

                for (int l = 0; l < calendar_schedular_mapping[businessdays[k]].size(); l++)
                {
                    MyFile2 << "\t";
                    MyFile2 << calendar_schedular_mapping[businessdays[k]].at(l).name << ' ';
                    MyFile2 << calendar_schedular_mapping[businessdays[k]].at(l).priorty << ' ';
                    MyFile2 << calendar_schedular_mapping[businessdays[k]].at(l).duration << ' ';
                    MyFile2 << calendar_schedular_mapping[businessdays[k]].at(l).currentDay << ' ';
                    MyFile2 << calendar_schedular_mapping[businessdays[k]].at(l).dueDay << endl;
                }
            }

            // Close the file
            MyFile2.close();

        }
        else if (choice == 8)
        {
            // clear out tasks
            for (int m = 0; m < currenttasknum; m++)
            {
                TaskArray[m].name = "N/A";
                TaskArray[m].priorty = 0;
                TaskArray[m].duration = 0;
                TaskArray[m].currentDay = "N/A";
                TaskArray[m].dueDay = "N/A";
            }

            currenttasknum = 0;
        }
        else if (choice == 9)
        {
            // clear out calendar
            for (int n = 0; n < 5; n++)
            {
                for (int o = 0; o < calendar_schedular_mapping[businessdays[n]].size(); o++)
                {
                    calendar_schedular_mapping[businessdays[n]].clear();
                }
            }
            // reset time available on calendar
            businessdayshourlimit[0] = workWeekHours / 5;
            businessdayshourlimit[1] = workWeekHours / 5;
            businessdayshourlimit[2] = workWeekHours / 5;
            businessdayshourlimit[3] = workWeekHours / 5;
            businessdayshourlimit[4] = workWeekHours / 5;

        }
    } //Ends while loop

    return 0;
}