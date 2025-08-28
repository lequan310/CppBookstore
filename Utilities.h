#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "Item.h"
#include "Customer.h"
#include "List.h"

using namespace std;

// https://www.geeksforgeeks.org/merge-sort-for-linked-list/
void SplitList(node<ShopItem*>* source, node<ShopItem*>** left, node<ShopItem*>** right);
node<Item>* Merge(node<ShopItem*>* left, node<ShopItem*>* right, bool choice, int ascending);
void MergeSort(node<ShopItem*>** headRef, bool choice, int ascending);
void SplitList(node<Customer*>* source, node<Customer*>** left, node<Customer*>** right);
node<Customer>* Merge(node<Customer*>* left, node<Customer*>* right, bool choice, int ascending);
void MergeSort(node<Customer>** headRef, bool choice, int ascending);

void SortByID(List<ShopItem*>** itemList, int ascending);
void SortByID(List<Customer*>** customerList, int ascending);
void SortByName(List<ShopItem*>** itemList, int ascending);
void SortByName(List<Customer*>** customerList, int ascending);

bool check_int(const string& s);
bool check_double(const string& s);
int count_char(const string& s, char c);

// https://www.techiedelight.com/trim-string-cpp-remove-leading-trailing-spaces/
string ltrim(const string& s);
string rtrim(const string& s);
string trim(const string& s);
string split_string(string* s, char c);
string lower_case(const string& s);

bool GetYesNo();