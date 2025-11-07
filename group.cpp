#include "group.h"

Group::Group() : aver_mark(0.0), subjects(nullptr), number(0), count(0), students(nullptr), stud(0) {
    cout << "The constructor without parameters for the Group class is called\n";
}

Group::Group(const float am, const string* s, const int n, const int c, const int st)
    : aver_mark(am), number(n), count(c) {
    this->subjects = new string[c];
    for (int i = 0; i < c; ++i) {
        this->subjects[i] = s[i];
    }
    students = new Student*[st]; 
    cout << "The constructor with parameters for the Group class is called\n";
}

Group::Group(const Group& other) : aver_mark(other.aver_mark), number(other.number), count(other.count) {
    subjects = new string[other.count];
    for (int i = 0; i < other.count; ++i) {
        subjects[i] = other.subjects[i];
    }

    students = new Student*[other.stud];
    for (int i = 0; i < other.stud; ++i) {
        students[i] = new Student(*other.students[i]);
    }

    cout << "The copy constructor for the Group class is called\n";
}


Group::~Group() {
    delete[] subjects;
    for (int i = 0; i < count; ++i) {
        delete students[i];
    }
    delete[] students;
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
    subjects = new string[c];
    for (int i = 0; i < c; ++i) {
        subjects[i] = s[i];
    }
    count = c;
}


int Group::get_number() const {
    return number;
}

void Group::set_number(int n) {
    number = n;
}

void Group::add_student(Student* St, int index) {
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
    if (index >= 0 && index < stud) {
        delete students[index];
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
    if (index >= 0 && index < stud) {
        students[index]->edit_student();
    } else {
        cout << "Invalid index!\n";
    }
    this->count_aver_mark();
    return *this;
}

Student& Group::operator[](int index) {
    if (index >= 0 && index < stud) {
        return *students[index];
    } else {
        cout << "Invalid index!\n";
        throw out_of_range("Index out of range");
    }
}


void Group::count_aver_mark() {
    if (stud == 0) {
        aver_mark = 0.0;
        return;
    }
    float total_marks = 0.0;
    int total_students = 0;
    for (int i = 0; i < stud; ++i) {
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
    cout << "Group Number: " << number << endl;
    cout << "Average Mark: " << aver_mark << endl;
    cout << "Subjects: ";
    for (int i = 0; i < count; ++i) {
        cout << subjects[i] << " ";
    }
    cout << endl;
    cout << "Students (" << stud << "):" << endl;
    for (int i = 0; i < stud; ++i) {
        cout << "Student " << i + 1 << ":" << endl;
        students[i]->display_student();
    }
}
