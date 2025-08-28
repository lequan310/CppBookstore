#include <iostream>
#include <string>
#include <vector>
#include "Customer.h"
#include "Item.h"
#include "List.h"
#include "Utilities.h"

using namespace std;

// Constructors for Customers (Guest, Regular, VIP)
Customer::Customer() {
	this->nBorrow = 0;
	this->nReturn = 0;
}

Customer::Customer(string _id, string _name, string _address, string _phone, int _borrow, int _return) {
	this->id = _id;
	this->name = _name;
	this->address = _address;
	this->phone = _phone;
	this->nBorrow = _borrow;
	this->nReturn = _return;
}

Customer::~Customer() {
	list.clear();
}

Guest::Guest() : Customer() {
	this->set_limit(GUEST_MAX);
}

// Convert from customer to Guest (used in promotion)
Guest::Guest(Customer& o) {
	this->id = o.get_id();
	this->name = o.get_name();
	this->address = o.get_address();
	this->phone = o.get_phone();
	this->list = o.get_list();
	this->limit = GUEST_MAX;
	this->nBorrow = o.get_borrow();
	this->nReturn = o.get_return();
}

Guest::Guest(string _id, string _name, string _address, string _phone, int _borrow)
	: Customer(_id, _name, _address, _phone, _borrow) {
	this->set_limit(GUEST_MAX);
}

Regular::Regular() : Customer() {}

// Convert from customer to Regular (used in promotion)
Regular::Regular(Customer& o) {
	this->id = o.get_id();
	this->name = o.get_name();
	this->address = o.get_address();
	this->phone = o.get_phone();
	this->list = o.get_list();
	this->nBorrow = o.get_borrow();
	this->nReturn = 0;
}

Regular::Regular(string _id, string _name, string _address, string _phone, int _borrow)
	: Customer(_id, _name, _address, _phone, _borrow) {}

Vip::Vip() : Customer() { this->reward = 0; }

// Convert from customer to VIP (used in promotion)
Vip::Vip(Customer& o) {
	this->id = o.get_id();
	this->name = o.get_name();
	this->address = o.get_address();
	this->phone = o.get_phone();
	this->list = o.get_list();
	this->nBorrow = o.get_borrow();
	this->nReturn = 0;
}

Vip::Vip(string _id, string _name, string _address, string _phone, int _borrow)
	: Customer(_id, _name, _address, _phone, _borrow) {
	this->reward = 0;
}

// Customer Getters
string Customer::get_id() { return this->id; }
string Customer::get_name() { return this->name; }
string Customer::get_address() { return this->address; }
string Customer::get_phone() { return this->phone; }
int Guest::get_limit() { return this->limit; }
vector<Item> Customer::get_list() { return this->list; }
int Customer::get_borrow() { return this->nBorrow; }
int Customer::get_return() { return this->nReturn; }
int Vip::get_reward() { return this->reward; }

// Customer Setters
void Customer::set_id(string _id) { this->id = _id; }
void Customer::set_name(string _name) { this->name = _name; }
void Customer::set_address(string _address) { this->address = _address; }
void Customer::set_phone(string _phone) { this->phone = _phone; }
void Guest::set_limit(int _limit) { this->limit = _limit; }
void Customer::set_list(vector<Item> _list) {
	this->list = _list;
}
void Customer::set_borrow(int _borrow) { this->nBorrow = _borrow; }
void Customer::set_return(int _return) { this->nReturn = _return; }
void Vip::set_reward(int _reward) { this->reward = _reward; }

// Output the items currently borrowed by the customer into the ostream
void Customer::output_list(ostream& stream) {
	for (Item i : this->list) {
		stream << i << endl;
	}
}

// Add item to customer borrow list
void Customer::add_to_list(const Item& _item) {
	list.push_back(_item);
}

// Remove item from customer borrow list
void Customer::remove_from_list(const Item& _item) {
	for (int i = 0; i < list.size(); i++) {
		// Find the first occurence of item in the borrow list to remove
		if (list[i] == _item) {
			list.erase(list.begin() + i);
			break;
		}
	}
}

// Borrow function without interaction used when loading files
bool Customer::borrow(List<ShopItem*>** _list, const string& id) {
	// Check if item with ID exists in the shop item list
	node<ShopItem*>* itemNode = find_with_id(_list, id);

	// If item exists in shop item list
	if (itemNode != NULL) {
		ShopItem* temp = itemNode->get_object();

		// If the item is available
		if (temp->get_available()) {
			// Check if customer has this item in the customer list already.
			for (Item i : this->list) {
				if (i.get_id().compare(temp->get_id()) == 0) {
					cout << "Customer already rented item with ID " << i.get_id() << " before. ";
					return false;
				}
			}

			this->add_to_list(*temp);
			temp->borrowed(); // Decrease stock
			nBorrow++; // Increase number of borrowed items for that customer
			if (temp->get_stock() <= 0) temp->set_available(false); // Set item available status to false if stock is 0.

			return true;
		}
		// If item is out of stock
		else {
			cout << "Item " << id << " is out of stock. ";
			return false;
		}
	}
	// If item doesn't exist in shop item list
	else {
		cout << "Shop does not have item with ID " << id << ". ";
		return false;
	}
}

// Overriden borrow function for guest without interaction used when loading files
bool Guest::borrow(List<ShopItem*>** _list, const string& id) {
	// If number of borrowed items for that Guest is 2 or more
	if (nBorrow >= limit) {
		cout << "Guest account can only rent maximum 2 video items at a time. ";
		return false;
	}

	// Check if item with ID exists in the shop item list
	node<ShopItem*>* itemNode = find_with_id(_list, id);

	// If item exists in shop item list
	if (itemNode != NULL) {
		ShopItem* temp = itemNode->get_object();

		// If the item is available
		if (temp->get_available()) {
			// If item loan type is 2-day
			if (temp->get_loan() == TWODAY) {
				cout << "Guest account " << this->id << " can't rent 2-day video items. ";
				return false;
			}

			// Check if customer has this item in the customer list already.
			for (Item i : this->list) {
				if (i.get_id().compare(temp->get_id()) == 0) {
					cout << "Customer already rented item with ID " << i.get_id() << " before. ";
					return false;
				}
			}

			this->add_to_list(*temp);
			temp->borrowed();
			nBorrow++;
			if (temp->get_stock() <= 0) temp->set_available(false);

			return true;
		}
		// If item is out of stock
		else {
			cout << "Item " << id << " is out of stock. ";
			return false;
		}
	}
	// If item doesn't exist in shop item list
	else {
		cout << "Shop does not have item with ID " << id << ". ";
		return false;
	}
}

// Base borrow function with interaction used in shop menu
bool Customer::borrow_item(List<ShopItem*>** _list, const string& _id) {
	// Check if item with ID exists in the shop item list
	node<ShopItem*>* itemNode = find_with_id(_list, _id);

	// If item exists in shop item list
	if (itemNode != NULL) {
		ShopItem* temp = itemNode->get_object();

		// If the item is available
		if (temp->get_available()) {
			// Check if customer has this item in the customer list already.
			for (Item i : this->list) {
				if (i.get_id().compare(temp->get_id()) == 0) {
					cout << "Customer is currently renting item with ID " << i.get_id() << " already.\n";
					return false;
				}
			}

			// User interaction to choose either to rent the item or not
			cout << "Do you want to rent this item for $" << temp->get_fee() << endl;
			if (!GetYesNo()) {
				return false;
			}

			this->add_to_list(*temp);
			temp->borrowed();
			nBorrow++;
			if (temp->get_stock() <= 0) temp->set_available(false);

			cout << this->get_id() << ", " << this->get_name() << " rented [" << (Item)*temp << "] successfully\n";
			return true;
		}
		// If item is out of stock
		else {
			cout << "Item " << _id << " is out of stock.\n";
			return false;
		}
	}
	// If item doesn't exist in shop item list
	else {
		cout << "Shop does not have item with ID " << id << endl;
		return false;
	}
}

// Overriden borrow function for Guest with interaction used in shop menu
bool Guest::borrow_item(List<ShopItem*>** _list, const string& _id) {
	// If number of borrowed items for that Guest is 2 or more
	if (nBorrow >= limit) {
		cout << "Guest account can only rent maximum 2 video items at a time.\n";
		return false;
	}

	// Check if item with ID exists in the shop item list
	node<ShopItem*>* itemNode = find_with_id(_list, _id);

	// If item exists in shop item list
	if (itemNode != NULL) {
		ShopItem* temp = itemNode->get_object();

		// If item loan type is 2-day
		if (temp->get_loan() == TWODAY) {
			cout << "Guest account " << this->id << " can't rent 2-day video items.\n";
			return false;
		}

		// If the item is available
		if (temp->get_available()) {
			// Check if customer has this item in the customer list already.
			for (Item i : this->list) {
				if (i.get_id().compare(temp->get_id()) == 0) {
					cout << "Customer is currently renting item with ID " << i.get_id() << " already.\n";
					return false;
				}
			}

			// User interaction to choose either to rent the item or not
			cout << "Do you want to rent this item for $" << temp->get_fee() << endl;
			if (!GetYesNo()) {
				return false;
			}

			this->add_to_list(*temp);
			temp->borrowed();
			nBorrow++;
			if (temp->get_stock() <= 0) temp->set_available(false);

			cout << this->get_id() << ", " << this->get_name() << " rented [" << (Item)*temp << "] successfully\n";
			return true;
		}
		// If the item is out of stock
		else {
			cout << "Item " << _id << " is out of stock.\n";
			return false;
		}
	}
	// If item doesn't exist in shop item list
	else {
		cout << "Shop does not have item with ID " << id << endl;
		return false;
	}
}

// Overriden borrow function for VIP with interaction used in shop menu
bool Vip::borrow_item(List<ShopItem*>** _list, const string& _id) {
	// Check if item with ID exists in the shop item list
	node<ShopItem*>* itemNode = find_with_id(_list, _id);

	// If item exists in shop item list
	if (itemNode != NULL) {
		ShopItem* temp = itemNode->get_object();

		// If the item is available
		if (temp->get_available()) {
			// Check if customer has this item in the customer list already.
			for (Item i : this->list) {
				if (i.get_id().compare(temp->get_id()) == 0) {
					cout << "Customer is currently renting item with ID " << i.get_id() << " already.\n";
					return false;
				}
			}

			// If VIP has 100 or more reward points
			if (this->reward >= 100) {
				// Ask the user whether they want to use reward points to rent for free
				cout << "Do you want to rent this item for free with 100 reward points?\n";

				// If user agree subtract reward points by 100
				if (GetYesNo()) {
					this->reward -= FREE_RENT;
				}
				// If they don't agree ask whether they want to rent the item for the default fee
				else {
					cout << "Do you want to rent this item for $" << temp->get_fee() << endl;
					if (!GetYesNo()) {
						return false;
					}
				}
			}
			else {
				cout << "Do you want to rent this item for $" << temp->get_fee() << endl;
				if (!GetYesNo()) {
					return false;
				}
			}

			this->add_to_list(*temp);
			temp->borrowed();
			nBorrow++;
			if (temp->get_stock() <= 0) temp->set_available(false);
			this->reward += 10;

			cout << this->get_id() << ", " << this->get_name() << " rented [" << (Item)*temp << "] successfully. Receive 10 reward points.\n";
			return true;
		}
		// If item is out of stock
		else {
			cout << "Item " << _id << " is out of stock.\n";
			return false;
		}
	}
	// If item doesn't exist in shop item list
	else {
		cout << "Shop does not have item with ID " << id << endl;
		return false;
	}
}

// Base return function with interaction used in shop menu
bool Customer::return_item(List<ShopItem*>** _list, const string& _id) {
	bool have = false;

	// Check if customer has the item in the borrow list
	for (Item i : this->list) {
		if (i.get_id().compare(_id) == 0) {
			have = true;
			break;
		}
	}

	// If customer doesn't have the item in the list return false
	if (!have) {
		cout << "Customer does not have this item in the rent list.\n";
		return false;
	}

	// If customer has the item in the borrow list, find the shop item node
	node<ShopItem*>* itemNode = find_with_id(_list, _id);

	if (itemNode != NULL) {
		ShopItem* temp = itemNode->get_object();

		// Remove item from borrow list, increase stock and set availability to true
		this->remove_from_list(*temp);
		temp->returned();
		temp->set_available(true);
		// Decrease the number of items borrowed and increase the number of items returned
		nBorrow--;
		nReturn++;

		cout << this->get_id() << ", " << this->get_name() << " returned [" << (Item)*temp << "] successfully\n";
		return true;
	}
	else {
		cout << "Shop does not have this item.\n";
		return false;
	}
}

// Converting all customers attributes into string
string Customer::toString() {
	string s = "";
	s.append(this->id + ",");
	s.append(this->name + ",");
	s.append(this->address + ",");
	s.append(this->phone + ",");
	s.append(to_string(this->nBorrow));

	return s;
}

// Converting Guest attributes into string
string Guest::toString() {
	string s = "";
	s.append(this->id + ",");
	s.append(this->name + ",");
	s.append(this->address + ",");
	s.append(this->phone + ",");
	s.append(to_string(this->nBorrow) + ",");
	s.append("Guest");

	return s;
}

// Converting Regular attributes into string
string Regular::toString() {
	string s = "";
	s.append(this->id + ",");
	s.append(this->name + ",");
	s.append(this->address + ",");
	s.append(this->phone + ",");
	s.append(to_string(this->nBorrow) + ",");
	s.append("Regular");

	return s;
}

// Converting VIP attributes into string
string Vip::toString() {
	string s = "";
	s.append(this->id + ",");
	s.append(this->name + ",");
	s.append(this->address + ",");
	s.append(this->phone + ",");
	s.append(to_string(this->nBorrow) + ",");
	s.append("VIP");

	return s;
}

// Converting between enum Level and string
string level2str(Level level) {
	if (level == GUEST) return "Guest";
	else if (level == REGULAR) return "Regular";
	else if (level == VIP) return "VIP";
	else return "";
}

// Check customer level for promotion
bool str2level(const string& s, Level* level) {
	if (s.compare("guest") == 0) {
		*level = GUEST;
		return true;
	}
	else if (s.compare("regular") == 0) {
		*level = REGULAR;
		return true;
	}
	else if (s.compare("vip") == 0) {
		*level = VIP;
		return true;
	}
	else {
		return false;
	}
}

// Find item or customer node using ID
node<ShopItem*>* find_with_id(List<ShopItem*>** list, const string& _id) {
	node<ShopItem*>* curr = (*list)->get_head();

	while (curr != NULL && curr->get_object()->get_id().compare(_id) != 0) {
		curr = curr->get_next();
	}

	return curr;
}

node<Customer*>* find_with_id(List<Customer*>** list, const string& _id) {
	node<Customer*>* curr = (*list)->get_head();

	while (curr != NULL && curr->get_object()->get_id().compare(_id) != 0) {
		curr = curr->get_next();
	}

	return curr;
}

// Call find_with_id and provide output for menu when using search function
bool search_with_id(List<ShopItem*>** list, const string& _id) {
	node<ShopItem*>* found = find_with_id(list, _id);

	// If item with ID exists in the shop item list
	if (found != NULL) {
		cout << "Found [" << found->get_object()->toString() << "] - (Current stock: " << to_string(found->get_object()->get_stock()) << ")\n";
		return true;
	}
	// If item with ID doesn't exists in the shop item list
	else {
		cout << "Cant find item with id: " << _id << endl;
		return false;
	}
}

bool search_with_id(List<Customer*>** list, const string& _id) {
	node<Customer*>* found = find_with_id(list, _id);

	// If customer with ID exists in the customer list
	if (found != NULL) {
		cout << "Found [" << found->get_object()->toString() << "]. Owned items:\n";
		found->get_object()->output_list(cout);
		return true;
	}
	// If customer with ID doesn't exist in the customer list
	else {
		cout << "Cant find customer with id: " << _id << endl;
		return false;
	}
}

// Find a list of item or customer using name
vector<ShopItem*> find_with_name(List<ShopItem*>** list, const string& _name) {
	vector<ShopItem*> sameName;
	node<ShopItem*>* curr = (*list)->get_head();

	// Loop through the shop item list and add the shop items with the name being searched into a list
	while (curr != NULL) {
		if (curr->get_object()->get_title().compare(_name) == 0) {
			sameName.push_back(curr->get_object());
		}
		curr = curr->get_next();
	}

	// Return the list of shop items with the searched name
	return sameName;
}

vector<Customer*> find_with_name(List<Customer*>** list, const string& _name) {
	vector<Customer*> sameName;
	node<Customer*>* curr = (*list)->get_head();

	// Loop through the customer list and add the customer with the name being searched into a list
	while (curr != NULL) {
		if (curr->get_object()->get_name().compare(_name) == 0) {
			sameName.push_back(curr->get_object());
		}
		curr = curr->get_next();
	}

	// Return the list of customers with the searched name
	return sameName;
}