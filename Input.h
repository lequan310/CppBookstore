#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "Item.h"
#include "List.h"
#include "Customer.h"

#define CUSTOMER_COMMA 5

using namespace std;

int get_option();
int get_option(const string& s);

ShopItem* GetShopItem(List<ShopItem*>** itemList);
Customer* GetCustomer(List<Customer*>** customerList);
ShopItem* ChooseShopItem(const string& name, List<ShopItem*>** itemList);
Customer* ChooseCustomer(const string& name, List<Customer*>** customerList);

// Load file into shop item list
bool LoadFile(List<ShopItem*>** itemList, const string& fileName);

// Load file into customer list
bool LoadFile(List<ShopItem*>** itemList, List<Customer*>** customerList, const string& fileName);

// Save from list into file
bool SaveFile(List<ShopItem*>** itemList, List<Customer*>** customerList, const string& itemFile, const string& customerFile);