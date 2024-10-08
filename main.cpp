#include <iostream>
#include <cstdlib>
#include <cctype>
#include <vector>
#include <map>

using namespace std;

bool isDigit(string text) {
    char character;
    bool found = false;

    for (int i = 0; i < text.length(); i++) {
        character = text[i];

        if (character >= '0' && character <= '9') {
            continue;
        } else {
            found = true;

            break;
        }
    }

    if (found) {
        return found;
    } else {
        return found;
    }
}

bool toConfirm(string question) {
    string choice;

    while (true) {
        cout << question << " (Y/N): ";
        cin.ignore();
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

void clearScreen() {
    system("cls");
}

void storage(string task, string category, string description, int level, bool status, int action) {
    map<string, bool> unimportant = {};
    map<string, bool> important = {};
    map<string, bool> rush = {};
    vector<string> tasks = {};
    vector<string> cat = {};
    vector<string> desc = {};

    switch (action) { // ACTIONS: 1 FOR CREATE | 2 FOR REMOVE | 3 FOR UPDATE | 4 FOR DISPLAY
        case 1: // Adds the receive value to the storages
            if (level == 1) {
                unimportant.insert({task, status});
            } else if (level == 2) {
                important.insert({task, status});
            } else if (level == 3) {
                rush.insert({task, status});
            } else {
                cout << "ERROR: INVALID LEVEL OF IMPORTANCE\n";
            }

            tasks.push_back(task);
            cat.push_back(category);
            desc.push_back(description);

            break;
        case 2: // Deletion of tasks and its components

            break;
        case 3: // Updates the status of the task
            break;
        case 4: // Displays the tasks in an organized way
    }
}

void createTask() {
    string task, desc, category, importance, choice;

    while (true) {
        do {
            cout << "Enter task: ";
            cin.ignore();
            getline(cin, task);

            cout << "Add Description of the Task: ";
            cin.ignore();
            getline(cin, desc);

            cout << "Enter the category (Study/Work/...): ";
            cin.ignore();
            getline(cin, category);
            do {
                cout<<"\nLEVEL OF IMPORTANCE\n1 - Unimportant/Daily Routine\n2 - Important\n3- Rush\n\n";
                cout<<"Enter Level of Importance (1/2/3): ";
                cin.ignore();
                getline(cin, importance);
            } while (isDigit(importance) && stoi(importance) >= 1 && stoi(importance) <= 3); // checks if the input is a digit

            clearScreen(); // This block of code displays the input values to confirm if it's correct
            cout << "TASK: " << task << endl;
            cout << "DESCRIPTION: " << desc << endl;
            cout << "LEVEL OF IMPORTANCE: " << importance << endl;

        } while (!toConfirm("Are the information above correct?"));

        // Sending the value to the storage
        storage(task, category, desc, stoi(importance), false, 1);

        if (!toConfirm("Do you want to add more task?")) {
            break;
        }
    }
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
            cin.ignore();
            getline(cin, choice);
        } while (isDigit(choice));

        switch (stoi(choice)) {
            case 1:
                createTask();

                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                running = false;

                break;
            default:
                cout << "ERROR: INVALID OPTION!\n";
        }
    }

    return EXIT_SUCCESS;
}