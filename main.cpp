#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
#include <fstream>

using namespace std;

bool checkNum(string text) {
    for (int i = 0; i < text.length(); i++) {
        if (isdigit(text[i]) == false) {
            return false;
        }
    }

    return true;
}

bool toConfirm(string question) {
    string choice;

    while (true) {
        cout << question << " (Y/N): ";
        getline(cin, choice);

        if (choice == "Y" || choice == "y") {
            return true;
        } else if (choice == "N" || choice == "n") {
            return false;
        } else {
            cout << "ERROR: INVALID OPTION\n";
        }
    }
}

void printLine(string reference) {
    for (int i = 0; i < reference.length(); i++) {
        cout << "--";
    }

    cout << endl;
}

void clearScreen() {
    system("cls");
}

void displayTasks(string task, string description, string category, int importance) {
    cout << "[]\t|" << task << "\t\t\t|" << description << "\t\t\t|" << category << endl;
}

void storage(string task, string category, string description, int level, bool status, int action) {
    static map<string, bool> unimportant;
    static map<string, bool> important;
    static map<string, bool> rush;
    static vector<string> allTasks;
    static vector<string> cat;
    static vector<string> desc;
    string tableHeaders = "STATUS\t|\t\tTASK\t\t|\t\t\tDESCRIPTION\t\t\t|\tCATEGORY\n";
    string wait;

    switch (action) { // ACTIONS: 1 FOR CREATE | 2 FOR REMOVE | 3 FOR UPDATE | 4 FOR DISPLAY
        case 1: // Adds the received values to storage
            if (level == 1) {
                unimportant.insert({task, status});
            } else if (level == 2) {
                important.insert({task, status});
            } else if (level == 3) {
                rush.insert({task, status});
            } else {
                cout << "ERROR: INVALID LEVEL OF IMPORTANCE\n";
            }

            allTasks.push_back(task);
            cat.push_back(category);
            desc.push_back(description);
            break;

        case 4: 
            clearScreen();
            cout << "==========YOUR TO-DO LIST==========\n";
            cout << tableHeaders;
            printLine(tableHeaders);
            cout << "\t\t\t\t\tRUSH\n";
            printLine(tableHeaders);

            for (auto R_Task : rush) {
                for (int i = 0; i < allTasks.size(); i++) {
                    if (allTasks[i] == R_Task.first) {
                        displayTasks(allTasks[i], desc[i], cat[i], 3); // 3 corresponds to "Rush"
                    }
                }
            }

            cout << endl;
            printLine(tableHeaders);
            cout << "\t\t\t\t     IMPORTANT\n";
            printLine(tableHeaders);

            for (auto I_Task : important) {
                for (int i = 0; i < allTasks.size(); i++) {
                    if (allTasks[i] == I_Task.first) {
                        displayTasks(allTasks[i], desc[i], cat[i], 2); // 2 corresponds to "Important"
                    }
                }
            }

            cout << endl;
            printLine(tableHeaders);
            cout << "\t\t\t\t   DAILT ROUTINE\n";
            printLine(tableHeaders);

            for (auto U_Task : unimportant) {
                for (int i = 0; i < allTasks.size(); i++) {
                    if (allTasks[i] == U_Task.first) {
                        displayTasks(allTasks[i], desc[i], cat[i], 1); // 1 corresponds to "Unimportant"
                    }
                }
            }
            printLine(tableHeaders);
            cout << "Press any key to continue: ";
            getline(cin, wait);

            break;

        default:
            cout << "ERROR: INVALID ACTION\n";
    }
}

void createTask() {
    string task, desc, category, importance, choice;
    bool correctInput;

    while (true) {
        do {
            correctInput = false;

            // This part will ask the user for details of the task
            cout << "Enter task: ";
            getline(cin, task);

            cout << "Add Description of the task: ";
            getline(cin, desc);

            cout << "Enter the category (Study/Work/...): ";
            getline(cin, category);
            do {
                cout<<"\nLEVEL OF IMPORTANCE\n1 - Unimportant/Daily Routine\n2 - Important\n3 - Rush\n\n";
                cout<<"Enter Level of Importance (1/2/3): ";
                getline(cin, importance);

                if (checkNum(importance)) { // This will ensure that the input is correct
                    if (stoi(importance) >= 1 && stoi(importance) <= 3) {
                        correctInput = true;
                    }
                }
            } while (!correctInput); // checks if the input is a digit. The '!' is there to flip the value of the correctInput

            clearScreen(); // This block of code displays the input values to confirm if it's correct
            cout << "TASK: " << task << endl;
            cout << "DESCRIPTION: " << desc << endl;
            cout << "LEVEL OF IMPORTANCE: " << importance << endl;

        } while (!toConfirm("Are the information above correct?"));

        // Sending the value to the storage
        storage(task, category, desc, stoi(importance), false, 1);

        if (!toConfirm("\nDo you want to add more task?")) {
            break;
        }

        clearScreen();
    }
}

void saveFile() {

}

int main() {
    string choice;
    bool running = true;

    // MAIN MENU
    while (running) {
        do {
            clearScreen();
            cout << "GROUP 5 - TO-DO LIST APP\n====================\n"; // The title of the program
            cout << "\nMAIN MENU\n1.) Create Task\n2.) Remove Task\n3.) Update Task\n4.) Display Task\n5.) Exit\n\n"; // Options

            cout << "Select from the menu (1/2/3/4/5): ";
            getline(cin, choice);
        } while (!checkNum(choice));

        switch (stoi(choice)) {
            case 1: // Creation of Task
                createTask();

                break;
            case 2: // Removal of Task

                break;
            case 3: // Update of status

                break;
            case 4: // Display all of the task
                storage("", "", "", 0, false, 4);

                break;
            case 5:
                running = false;

                break;
            default:
                cout << "ERROR: INVALID OPTION\n";
        }
    }

    return EXIT_SUCCESS;
}
