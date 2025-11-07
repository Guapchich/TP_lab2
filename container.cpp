#include "container.h"

Container::Container() : head(nullptr), tail(nullptr), count(0) {cout << "The constructor without parameters for the Container class is called\n";}

Container::Container(Node* h, Node* t, const int c) : head(h), tail(t), count(c) {
    cout << "The constructor with parameters for the Container class is called\n";
}

Container::Container(const Container& other) : head(other.head), tail(other.tail), count(other.count) {
    cout << "The copy constructor for the Container class is called\n";
}

Container::~Container() {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp->data;
        delete temp;
    }
    tail = nullptr;
    count = 0;
    cout << "The destructor for the Container class is called" << endl;
}


Node* Container::get_head() {
    return this->head;
}

Node* Container::get_tail() {
    return this->tail;
}

void Container::add_group(Group* St, int index) {
    if (index < 0 || index > count) {
        throw out_of_range("Index out of range");
    }
    
    Node* node_to_add = new Node;
    node_to_add->data = St;
    node_to_add->next = nullptr;

    if (index == 0) {
        node_to_add->next = head;
        head = node_to_add;
        if (count == 0) {
            tail = node_to_add;
        }
    } else {
        Node* prev = head;
        for (int i = 0; i < index - 1; ++i) {
            prev = prev->next;
        }
        node_to_add->next = prev->next;
        prev->next = node_to_add;
        
        if (node_to_add->next == nullptr) {
            tail = node_to_add;
        }
    }
    
    ++count;
}

Container& Container::delete_group(int index) {
    if (index < 0 || index >= count) {
        throw out_of_range("Index out of range");
    }

    Node* temp = head;

    if (index == 0) {
        head = head->next;
        delete temp->data;
        delete temp;
        if (head == nullptr) {
            tail = nullptr;
        }
    } else {
        Node* prev = nullptr;
        for (int i = 0; i < index; ++i) {
            prev = temp;
            temp = temp->next;
        }
        prev->next = temp->next;
        if (temp == tail) {
            tail = prev;
        }
        delete temp->data;
        delete temp;
    }

    --count;
    return *this;
}

void Container::display_groups() {
    Node* temp = head;
    if (count == 0) {
        cout << "No data" << endl;
        return;
    }

    int index = 1;
    while (temp != nullptr) {
        cout << index << " - group:\n";
        temp->data->display_group();
        temp = temp->next;
        index++;
    }
}


void Container::sort_groups_by_number() {
    if (count < 2) return;

    for (Node* i = head; i != nullptr; i = i->next) {
        for (Node* j = i->next; j != nullptr; j = j->next) {
            if (i->data->get_number() > j->data->get_number()) { 
                Group* temp = i->data;
                i->data = j->data;
                j->data = temp;
            }
        }
    }
}

void Container::search_groups_with_average_marks_more_than_4() {
    Node* temp = head;
    bool found = false;

    while (temp != nullptr) {
        if (temp->data->get_aver_mark() > 4.0) {
            cout << "Group with group number " << temp->data->get_number() 
                 << " has an average mark more than 4: " 
                 << temp->data->get_aver_mark() << endl;
            found = true;
        }
        temp = temp->next;
    }

    if (!found) {
        cout << "No groups with average marks more than 4 were found." << endl;
    }
}


Container& Container::edit_group(int index) {
    if (index < 0 || index >= count) {
        throw out_of_range("Index out of range");
    }
    Node* temp = head;
    for (int i = 0; i < index; ++i) {
        temp = temp->next;
    }
    while (true) {
        cout << "\n===== Student Management Menu =====" << endl;
        cout << "1. Add a student" << endl;
        cout << "2. Remove a student" << endl;
        cout << "3. Edit student data" << endl;
        cout << "4. Display data group" << endl;
        cout << "5. Edit subjects" << endl;
        cout << "6. Edit number" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        int choice = check_input();

        switch (choice) {
            case 1: {
                string name;
                int number, size;
                cout << "Enter student's name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter the number of marks: ";
                size = check_input();

                float* marks = new float[size];

                cout << "Enter marks: ";
                for (int i = 0; i < size; i++) {
                    cin >> marks[i];
                }

                cout << "Enter the student's index to add: ";
                int student_index = check_input();

                Student* new_student = new Student(name, marks, size);
                temp->data->add_student(new_student, student_index - 1);
                cout << "Student added." << endl;
                break;
            }
            case 2: {
                int student_index;
                cout << "Enter the index of the student to remove: ";
                student_index = check_input();
                try {
                    temp->data->delete_student(student_index - 1);
                    cout << "Student removed." << endl;
                } catch (const out_of_range& e) {
                    cout << e.what() << endl;
                }
                break;
            }
            case 3: {
                int student_index;
                cout << "Enter the index of the student to edit: ";
                student_index = check_input();
                try {
                    temp->data->edit_student(student_index - 1);
                    cout << "Student data updated." << endl;
                } catch (const out_of_range& e) {
                    cout << e.what() << endl;
                }
                break;
            }
            case 4: {
                temp->data->display_group();
                break;
            }
            case 5: {
                cout << "Enter the number of subjects: ";
                int subject_count = check_input();

                string* subjects = new string[subject_count];
                cout << "Enter subject names:" << endl;
                for (int i = 0; i < subject_count; ++i) {
                    cin >> subjects[i];
                }
                temp->data->set_subjects(subjects, subject_count);
                break;
            }
            case 6: {
                cout << "Enter the new number of the group: ";
                int num = check_input();
                temp->data->set_number(num);
                break;
            }
            case 0: {
                cout << "Exiting the menu." << endl;
                return *this;
            }
            default: {
                cout << "Invalid choice! Try again." << endl;
                break;
            }
        }
    }
}


Group& Container::operator[](int index) {
    if (index < 0 || index >= count) {
        throw out_of_range("Index out of range");
    }

    Node* temp = head;
    for (int i = 0; i < index; ++i) {
        temp = temp->next;
    }

    return *temp->data;
}

