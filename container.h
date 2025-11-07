#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include "student.h"
#include "group.h"
#include "check.h"


using namespace std;

struct Node
{
    Node* next;
    Group* data;
};

class Container
{
private:
    Node* head;
    Node* tail;
    int count;

public:
    Container();
    Container(Node* h, Node* t, const int c);
    Container(const Container& other);
    ~Container();

    Node* get_head();
    Node* get_tail();

    void add_group(Group* St, int index);
    Container& delete_group(int index);
    Container& edit_group(int index);
    void display_groups();
    void sort_groups_by_number();
    void search_groups_with_average_marks_more_than_4();

    Group& operator[](int index);
};

