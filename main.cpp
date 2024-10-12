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
        cout << "---";
    }

    cout << endl;
}

void printTab(string text) {
    int numberOfChar = text.length();
    int tabNeeded = numberOfChar / 4;
    string tab;

    if (tabNeeded <= 2) {
        tab = "\t\t\t\t";
    } else if (tabNeeded <= 3) {
        tab = "\t\t\t";
    } else if (tabNeeded <= 5) {
        tab = "\t\t";
    } else {
        tab = "\t";
    }
    
    cout << tab;
}

void clearScreen() {
    system("cls");
}

void displayTasks(bool check, string task, string description, string category, int importance) {
    if (check) {
        cout << "[/]\t|" << task;
    } else {
        cout << "[ ]\t|" << task;
    }
    printTab(task);
    cout << "|" << description;
    printTab(description);
    cout << "|" << category << endl;
}

void storage(string filename, string task, string category, string description, int level, bool status, int action) {
    static map<string, bool> unimportant;
    static map<string, bool> important;
    static map<string, bool> rush;
    static vector<string> allTasks;
    static vector<string> cat;
    static vector<string> desc;
    int targetIndex;
    string tableHeaders = "STATUS\t|\t\tTASK\t\t|\t\tDESCRIPTION\t\t|\tCATEGORY\n";
    string wait, remove, update;

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

        case 2:
            do {
                clearScreen();
                cout << "REMOVE TASK\n";
                for (int i = 0; i < allTasks.size(); i++) {
                    cout << (i + 1) << ".) " << allTasks[i] << endl;
                }

                cout << "\nSelect the number of the task you want to remove ('0' to EXIT): ";
                getline(cin, remove);

                if (remove == "0") {
                    break;
                }
            } while (checkNum(remove) == false);

            if (remove == "0") {
                break;
            } else {
                targetIndex = stoi(remove) - 1;
                task = allTasks[targetIndex];

                // REMOVES ALL OF THE RELATED COMPONENTS
                allTasks.erase(allTasks.begin() + targetIndex);
                cat.erase(cat.begin() + targetIndex);
                desc.erase(cat.begin() + targetIndex);
                unimportant.erase(task);
                important.erase(task);
                rush.erase(task);

            }

            break;
        case 3:
            do {
                clearScreen();
                cout << "UPDATE TASK\n";
                for (int i = 0; i < allTasks.size(); i++) {
                    cout << (i + 1) << ".) " << allTasks[i] << endl;
                }

                cout << "\nSelect the number of the task you want to update ('0' to EXIT): ";
                getline(cin, update);

                if (update == "0") {
                    break;
                }
            } while (checkNum(update) == false);

            if (update == "0") {
                break;
            } else {
                targetIndex = stoi(update) - 1;
                task = allTasks[targetIndex];

                if (rush.find(task) != rush.end()) {
                    rush[task] = !rush[task];
                } else if (important.find(task) != important.end()) {
                    important[task] = !important[task];
                } else if (unimportant.find(task) != unimportant.end()) {
                    unimportant[task] = !unimportant[task];
                }          
            }

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
                        displayTasks(R_Task.second, allTasks[i], desc[i], cat[i], 3); // 3 corresponds to "Rush"
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
                        displayTasks(I_Task.second, allTasks[i], desc[i], cat[i], 2); // 2 corresponds to "Important"
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
                        displayTasks(U_Task.second, allTasks[i], desc[i], cat[i], 1); // 1 corresponds to "Unimportant"
                    }
                }
            }
            printLine(tableHeaders);
            cout << "Press any key to continue: ";
            getline(cin, wait);

            break;
        case 5:
            if (true) { 
                ofstream user(filename);

                user << "RUSH" << endl;
                for (auto R_Task : rush) {
                    for (int i = 0; i < allTasks.size(); i++) {
                        if (allTasks[i] == R_Task.first) {
                            user << R_Task.second << "`" << allTasks[i] << "`" << desc[i] << "`" << cat[i] << endl;
                        }
                    }
                }

                user << "IMPORTANT" << endl;
                for (auto I_Task : important) {
                    for (int i = 0; i < allTasks.size(); i++) {
                        if (allTasks[i] == I_Task.first) {
                            user << I_Task.second << "`" << allTasks[i] << "`" << desc[i] << "`" << cat[i] << endl;
                        }
                    }
                }

                user << "DAILY ROUTINE" << endl;
                for (auto U_Task : unimportant) {
                    for (int i = 0; i < allTasks.size(); i++) {
                        if (allTasks[i] == U_Task.first) {
                            user << U_Task.second << "`" << allTasks[i] << "`" << desc[i] << "`" << cat[i] << endl;
                        }
                    }
                }
            }

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

            clearScreen();
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
        storage("", task, category, desc, stoi(importance), false, 1);

        if (!toConfirm("\nDo you want to add more task?")) {
            break;
        }

        clearScreen();
    }
}

void readLine(string line, int level) {
    string task = "";
    string description = "";
    string category = "";
    int backtick = 0;
    bool checklist;

    if (line[0] == '0') {
        checklist = false;
    } else {
        checklist = true;
    }

    for (int j = 2; j < line.length(); j++) { // If it has confirmed, then it will take each letter of the line
        switch (backtick) { // The backtick is used to seperate each component in the file
            case 0: // This is the task line in the file
                if (line[j] != '`') {
                    task += line[j];
                } else {
                    backtick++;
                }

                break;
            case 1: // The backtick will serve as a seperator
                if (line[j] != '`') {
                    description += line[j];
                } else {
                    backtick++;
                }

                break;
            case 2:
                if (line[j] != '`') {
                    category += line[j];
                } else {
                    backtick = 0;
                }

                break;
            default:
                cout << "ERROR: There was an error with the file!\n";
        }
    }
    
    // Adds the line
    storage("", task, category, description, level, checklist, 1);
}

void readFile(string filename) {
    string line;

    ifstream user(filename);

    if (!user.is_open()) { // Checks if the file can be opened
        cout << "ERROR: UNABLE TO OPEN FILE!";
    } else {
        for (int i = 0; i < 3; i++) { // This loop is used to iterate over the 3 main parts; RUSH, IMPORTANT, DAILY ROUTINE
            getline(user, line);
            if (line == "RUSH") { // This is for all the RUSH Tasks
                while (getline(user, line)) {
                    if (line[0] == '0' || line[0] == '1') { // It will make sure if it starts with 0 or 1 because that is the symbol for the checklist
                        readLine(line, 3);
                    } else {
                        break;
                    }
                }
            }
            if (line == "IMPORTANT") { // This is for all the IMPORTANT Tasks
                while (getline(user, line)) {
                    if (line[0] == '0' || line[0] == '1') { // It will make sure if it starts with 0 or 1 because that is the symbol for the checklist
                        readLine(line, 2);
                    } else {
                        break;
                    }
                }
            }
            if (line == "DAILY ROUTINE") {
                while (getline(user, line)) { // This is for all the DAILY ROUTINE Tasks
                    if (line[0] == '0' || line[0] == '1') { // It will make sure if it starts with 0 or 1 because that is the symbol for the checklist
                        readLine(line, 1);
                    } else {
                        break;
                    }
                }
            }
        }
    }
}

string logIn() {
    string username, filename;

    while (true) {
        clearScreen();
        cout << "GROUP 5 - TO-DO LIST APP\n====================\n";
        cout << "Enter your username: ";
        getline(cin, username);

        filename = username + ".chk"; // the username is also the filename.

        ifstream user(filename); // takes the user name and adds the .chk file to look for the save file
        if (user.is_open()) {
            readFile(filename);

            user.close();

            break;
        } else {
            ofstream user(username + ".chk");

            break;
        }
    }

    return username;
}

int main() {
    string choice, username;
    bool running = true;

    // LOG IN
    username = logIn();

    // MAIN MENU
    while (running) {
        do {
            clearScreen();
            cout << "NOTE: PLEASE MAKE SURE TO EXIT THE PROGRAM THROUGH THE MENU, THE PROGRAM MAY NOT SAVE YOUR PROGRESS IF FAILED TO DO SO\n";
            cout << "\nGROUP 5 - TO-DO LIST APP\n====================\n"; // The title of the program
            cout << "\nWelcome, " << username << endl <<endl;
            cout << "\nMAIN MENU\n1.) Create Task\n2.) Remove Task\n3.) Update Task\n4.) Display Task\n5.) Exit\n\n"; // Options

            cout << "Select from the menu (1/2/3/4/5): ";
            getline(cin, choice);
        } while (!checkNum(choice));

        switch (stoi(choice)) {
            case 1: // Creation of Task
                createTask();

                break;
            case 2: // Removal of Task
                storage("", "", "", "", 0, false, 2);

                break;
            case 3: // Update of status
                storage("", "", "", "", 0, false, 3);

                break;
            case 4: // Display all of the task
                storage("", "", "", "", 0, false, 4);

                break;
            case 5:
                storage(username + ".chk", "", "", "", 0, false, 5);

                running = false;

                break;
            default:
                cout << "ERROR: INVALID OPTION\n";
        }
    }

    return EXIT_SUCCESS;
}
