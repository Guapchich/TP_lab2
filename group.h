#pragma once

#include <iostream>
#include <string>
#include "student.h"

using namespace std;

class Group {
private:
    float aver_mark;
    string* subjects;
    int number; 
    int count;   
    Student** students;
    int stud;

public:
    Group();
    Group(const float am, const string* s, const int n, const int c, const int st);
    Group(const Group& other);
    ~Group();

    float get_aver_mark() const;
    void set_aver_mark(float am);

    string* get_subjects() const;
    void set_subjects(string* s, int c);

    int get_number() const;
    void set_number(int n);

    int get_count() const;

    void add_student(Student* St, int index);
    Group& delete_student(int index);
    Group& edit_student(int index);
    void display_group() const;
    void count_aver_mark();

    Student& operator[](int index);
};
