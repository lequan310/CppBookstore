#pragma once
#include <iostream>
#include <string>
#include "Item.h"
#include "List.h"
#include <vector>

#define GUEST_MAX 2
#define FREE_RENT 100

using namespace std;

// Used in promotion to identify the current level of customer
enum Level { GUEST, REGULAR, VIP, CUSTOMER };

// Class declaration
class Customer {
protected:
	string id;
	string name;
	string address;
	string phone;
	vector<Item> list;

	int nBorrow;
	int nReturn;
public:
	Customer();
	Customer(string _id, string _name, string _address, string _phone, int _borrow = 0, int _return = 0);
	~Customer();

	// Getters
	void set_id(string _id);
	void set_name(string _name);
	void set_address(string _address);
	void set_phone(string _phone);
	void set_list(vector<Item> _list);
	void set_borrow(int _borrow);
	void set_return(int _return);

	// Setters
	string get_id();
	string get_name();
	string get_address();
	string get_phone();
	vector<Item> get_list();
	int get_borrow();
	int get_return();
	virtual Level get_level() { return CUSTOMER; }

	void output_list(ostream& stream);
	void add_to_list(const Item& _item);
	void remove_from_list(const Item& _item);
	virtual bool borrow(List<ShopItem*>** _list, const string& id);
	virtual bool borrow_item(List<ShopItem*>** _list, const string& _id);
	virtual bool return_item(List<ShopItem*>** _list, const string& _id);

	virtual string toString();
};

// Guest, Regular, VIP inherits from Customer
class Guest : public Customer {
private:
	int limit;
public:
	Guest();
	Guest(Customer& o);
	Guest(string _id, string _name, string _address, string _phone, int borrow = 0);

	void set_limit(int _limit);
	int get_limit();
	virtual Level get_level() { return GUEST; }

	virtual bool borrow(List<ShopItem*>** _list, const string& _id);
	virtual bool borrow_item(List<ShopItem*>** _list, const string& _id);

	virtual string toString();
};

class Regular : public Customer {
public:
	Regular();
	Regular(Customer& o);
	Regular(string _id, string _name, string _address, string _phone, int borrow = 0);

	virtual Level get_level() { return REGULAR; }

	virtual string toString();
};

class Vip : public Customer {
private:
	int reward;
public:
	Vip();
	Vip(Customer& o);
	Vip(string _id, string _name, string _address, string _phone, int borrow = 0);

	int get_reward();
	void set_reward(int _reward);
	virtual Level get_level() { return VIP; }

	virtual bool borrow_item(List<ShopItem*>** _list, const string& _id);

	virtual string toString();
};

// Function declaration for converting between level and string
string level2str(Level level);
bool str2level(const string& s, Level* level);

// Function declaration for searching functions
node<ShopItem*>* find_with_id(List<ShopItem*>** list, const string& _id);
node<Customer*>* find_with_id(List<Customer*>** list, const string& _id);
bool search_with_id(List<ShopItem*>** list, const string& _id);
bool search_with_id(List<Customer*>** list, const string& _id);
vector<ShopItem*> find_with_name(List<ShopItem*>** list, const string& _name);
vector<Customer*> find_with_name(List<Customer*>** list, const string& _name);