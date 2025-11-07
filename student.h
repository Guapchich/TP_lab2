#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include "check.h"

using namespace std;

class Student {
    private:
        string name;
        float* marks;
        int size;
    public:
        Student();
        Student(const string& n, const float* m, const int& siz);
        Student(const Student& other);
        ~Student();

        string get_name() const;
        void set_name(const string& n);

        const float* get_marks() const;
        void set_marks(const float* m, int siz);

        int get_size() const;
        void set_size(const int& size);

        void display_student();
        void edit_student();
};