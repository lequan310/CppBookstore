#pragma once
#include <iostream>
#include <string>

using namespace std;

// Declaration of node<T> to store T class as object
template <class T>
class node {
private:
    T object;
    node<T>* next;
public:
    node<T>();
    ~node<T>();

    T get_object();
    void set_object(const T& obj);
    node<T>* get_next();
    void set_next(node<T>* node);
};

// Declaration of class Linked List for storing Item* and Customer*
template <class T>
class List {
private:
    node<T>* head;
    int size;
public:
    List();
    ~List();

    void set_head(node<T>* _head);

    node<T>* get_head();
    int get_size();

    void add(const T& obj);
    void remove(const T& obj);
    void print_list();
    void print_list(ostream& stream);
};