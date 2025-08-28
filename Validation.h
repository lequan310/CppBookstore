#pragma once
#include <iostream>
#include <string>
#include "Item.h"
#include "Customer.h"
#include "Utilities.h"

using namespace std;

bool CheckNewItemID(const string& id, List<ShopItem*>** itemList);
bool CheckExistedItemID(const string& id, List<ShopItem*>** itemList);

bool CheckNewCustomerID(const string& _id, List<Customer*>** customerList);
bool CheckExistedCustomerID(const string& _id, List<Customer*>** customerList);

bool ValidateString(const string& s);

bool ValidatePhone(const string& s);

bool NotRented(const string& id, List<Customer*>** customerList);

bool StringToItemList(string* line, List<ShopItem*>** itemList);

bool StringToCustomer(Customer** customer, string* original, List<Customer*>** customerList, int* borrow);