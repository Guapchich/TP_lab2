#include "container.h"
#include "student.h"
#include "check.h"
#include "sentense_filter.h"

void display_menu() {
    cout << "\n===== Group Management Menu =====" << endl;
    cout << "1. Add a group" << endl;
    cout << "2. Remove a group" << endl;
    cout << "3. Edit group data" << endl;
    cout << "4. Display all groups" << endl;
    cout << "0. Exit" << endl;
    cout << "Enter your choice: ";
}

int students_program() {
    Container container; 
    int choice;

    while (true) {
        display_menu();
        choice = check_input();

        switch (choice) {
            case 1: {
                int group_number, subject_count;
                cout << "Enter group number: ";
                group_number = check_input();
                cout << "Enter the number of subjects: ";
                subject_count = check_input();

                string* subjects = new string[subject_count];
                cout << "Enter subject names:" << endl;
                for (int i = 0; i < subject_count; ++i) {
                    cin >> subjects[i];
                }
                cout << "Enter the index to add:\n";
                int index = check_input();

                Group* new_group = new Group(0.0, subjects, group_number, subject_count, 0);
                container.add_group(new_group, index - 1);
                cout << "Group added successfully." << endl;

                break;
            }
            case 2: {
                cout << "Enter the index of the group to remove: ";
                int index = check_input();
                try {
                    container.delete_group(index - 1);
                    cout << "Group removed successfully." << endl;
                } catch (const out_of_range& e) {
                    cerr << e.what() << endl;
                }
                break;
            }
            case 3: {
                cout << "Enter the index of the group to edit: ";
                int index = check_input();
                try {
                    container.edit_group(index - 1);
                } catch (const out_of_range& e) {
                    cerr << e.what() << endl;
                }
                break;
            }
            case 4: {
                container.display_groups();
                break;
            }
            case 0: {
                cout << "Exiting the program." << endl;
                return 0;
            }
            default:
                cout << "Invalid choice! Try again." << endl;
                break;
        }
    }
}
int words_program() {
    try {
        int choice;
        cout << "Select a source (1 - text string, 2 - file): ";
        if (!(cin >> choice)) {
            throw invalid_argument("Error: Invalid input for source selection.");
        }

        if (choice == 1) {
            cin.ignore();
            char text[8192];
            cout << "Enter the text: ";
            cin.getline(text, sizeof(text));

            if (cin.fail()) {
                throw overflow_error("Error: Exceeded maximum text length.");
            }

            SentenceFilter filter(text, true);
            filter.result();
        } else if (choice == 2) {
            char filename[256];
            cout << "Enter the file name: ";
            cin >> filename;
            ifstream file(filename);
            if (!file) {
                throw runtime_error("Error: File not found or cannot be opened.");
            }
            file.close();
            SentenceFilter filter(filename);
            filter.result();
        } else {
            throw out_of_range("Error: Selected source does not exist.");
        }
    }
    catch (const invalid_argument& e) {
        cerr << e.what() << endl;
        return 1;
    }
    catch (const overflow_error& e) {
        cerr << e.what() << endl;
        return 2;
    }
    catch (const runtime_error& e) {
        cerr << e.what() << endl;
        return 3;
    }
    catch (const out_of_range& e) {
        cerr << e.what() << endl;
        return 4;
    }
    catch (...) {
        cerr << "An unknown error occurred." << endl;
        return -1;
    }
    return 0;
}

int main() {
    int choice;
    while (true) {
        cout << "Select task type:" << endl;
        cout << "1 - Standard streams" << endl;
        cout << "2 - File and text streams" << endl;
        cout << "3 - Exit" << endl;
        choice = check_input();

        switch (choice) {
            case 1:
                students_program();
                break;
            case 2:
                words_program();
                break;
            case 3:
                cout << "Exiting." << endl;
                return 0;
            default:
                cout << "Invalid choice! Try again." << endl;
                break;
        }
    }
}
