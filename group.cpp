#include "group.h"
#include <iostream>

using namespace std;

Group::Group() : aver_mark(0.0), subjects(nullptr), number(0), count(0), students(nullptr), stud(0) {
    cout << "The constructor without parameters for the Group class is called\n";
}

Group::Group(const float am, const string* s, const int n, const int c, const int st)
    : aver_mark(am), number(n), count(c), stud(st) {  

    if (c > 0 && s != nullptr) {
        this->subjects = new string[c];
        for (int i = 0; i < c; ++i) {
            this->subjects[i] = s[i];
        }
    } else {
        this->subjects = nullptr;
        this->count = 0;
    }
    
    if (st > 0) {
        students = new Student*[st];
        for (int i = 0; i < st; ++i) {
            students[i] = nullptr;  
        }
    } else {
        students = nullptr;
    }
    
    cout << "The constructor with parameters for the Group class is called\n";
}

Group::Group(const Group& other) 
    : aver_mark(other.aver_mark), number(other.number), count(other.count), stud(other.stud) { 
    
    if (other.count > 0 && other.subjects != nullptr) {
        subjects = new string[other.count];
        for (int i = 0; i < other.count; ++i) {
            subjects[i] = other.subjects[i];
        }
    } else {
        subjects = nullptr;
        count = 0;
    }

    if (other.stud > 0 && other.students != nullptr) {
        students = new Student*[other.stud];
        for (int i = 0; i < other.stud; ++i) {
            if (other.students[i] != nullptr) {
                students[i] = new Student(*other.students[i]); 
            } else {
                students[i] = nullptr;
            }
        }
    } else {
        students = nullptr;
        stud = 0;
    }

    cout << "The copy constructor for the Group class is called\n";
}

Group::~Group() {

    delete[] subjects;
    subjects = nullptr;
    

    if (students != nullptr) {
        for (int i = 0; i < stud; ++i) { 
            if (students[i] != nullptr) {
                delete students[i];
                students[i] = nullptr;
            }
        }
        delete[] students;
        students = nullptr;
    }
    
    cout << "The destructor for the Group class is called\n";
}

float Group::get_aver_mark() const {
    return aver_mark;
}

void Group::set_aver_mark(float am) {
    aver_mark = am;
}

string* Group::get_subjects() const {
    return subjects;
}

void Group::set_subjects(string* s, int c) {
    delete[] subjects;
    if (c > 0 && s != nullptr) {
        subjects = new string[c];
        for (int i = 0; i < c; ++i) {
            subjects[i] = s[i];
        }
        count = c;
    } else {
        subjects = nullptr;
        count = 0;
    }
}

int Group::get_number() const {
    return number;
}

void Group::set_number(int n) {
    number = n;
}

void Group::add_student(Student* St, int index) {
    if (St == nullptr) {
        cout << "Cannot add null student!\n";
        return;
    }
    
    if (index < 0 || index > stud) {
        cout << "Invalid index!\n";
        return;
    }
    
    Student** new_students = new Student*[stud + 1];
    
    for (int i = 0; i < index; ++i) {
        new_students[i] = students[i];
    }
    
    new_students[index] = new Student(*St);
    

    for (int i = index; i < stud; ++i) {
        new_students[i + 1] = students[i];
    }
    
    delete[] students;
    students = new_students;
    ++stud;
    
    this->count_aver_mark();
}

Group& Group::delete_student(int index) {
    if (index >= 0 && index < stud && students != nullptr) {
        // Удаляем студента
        if (students[index] != nullptr) {
            delete students[index];
        }
        
        for (int i = index; i < stud - 1; ++i) {
            students[i] = students[i + 1];
        }
        
        students[stud - 1] = nullptr;
        --stud;
    } else {
        cout << "Invalid index!\n";
    }
    this->count_aver_mark();
    return *this;
}

Group& Group::edit_student(int index) {
    if (index >= 0 && index < stud && students != nullptr && students[index] != nullptr) {
        students[index]->edit_student();
    } else {
        cout << "Invalid index or null student!\n";
    }
    this->count_aver_mark();
    return *this;
}

Student& Group::operator[](int index) {
    if (index >= 0 && index < stud && students != nullptr && students[index] != nullptr) {
        return *students[index];
    } else {
        cout << "Invalid index or null student!\n";
        throw out_of_range("Index out of range or null student");
    }
}

void Group::count_aver_mark() {
    if (stud == 0 || students == nullptr) {
        aver_mark = 0.0;
        return;
    }
    
    float total_marks = 0.0;
    int total_students = 0;
    
    for (int i = 0; i < stud; ++i) {
        if (students[i] != nullptr) {
            const float* marks = students[i]->get_marks();
            int size = students[i]->get_size();
            if (marks != nullptr && size > 0) {
                float student_sum = 0.0;
                for (int j = 0; j < size; ++j) {
                    student_sum += marks[j];
                }
                float student_average = student_sum / size;
                total_marks += student_average;
                ++total_students;
            }
        }
    }
    
    if (total_students > 0) {
        aver_mark = total_marks / total_students;
    } else {
        aver_mark = 0.0;
    }
}

int Group::get_count() const {
    return count;
}

void Group::display_group() const {
    cout << "=== GROUP INFO ===" << endl;
    cout << "Group Number: " << number << endl;
    cout << "Average Mark: " << aver_mark << endl;
    
    cout << "Subjects (" << count << "): ";
    if (subjects != nullptr && count > 0) {
        for (int i = 0; i < count; ++i) {
            cout << subjects[i] << " ";
        }
    } else {
        cout << "No subjects";
    }
    cout << endl;
    
    cout << "Students (" << stud << "):" << endl;
    if (students != nullptr && stud > 0) {
        for (int i = 0; i < stud; ++i) {
            cout << "Student " << i + 1 << ":" << endl;
            if (students[i] != nullptr) {
                students[i]->display_student();
            } else {
                cout << "  [NULL STUDENT POINTER]" << endl;
            }
        }
    } else {
        cout << "No students in group" << endl;
    }
    cout << "==================" << endl;
}
