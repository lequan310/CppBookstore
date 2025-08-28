#include <iostream>
#include <fstream>
#include <string>
#include "Item.h"
#include "Customer.h"
#include "List.h"

using namespace std;

void SplitList(node<ShopItem*>* source, node<ShopItem*>** left, node<ShopItem*>** right) {
	node<ShopItem*>* slow = source;
	node<ShopItem*>* fast = source->get_next();

	// Advance 'fast' 2 nodes, and advance 'slow' 1 node
	while (fast != NULL) {
		fast = fast->get_next();
		if (fast != NULL) {
			slow = slow->get_next();
			fast = fast->get_next();
		}
	}

	// Left list is from source to slow, Right list is from slow->next to the end (NULL)
	*left = source;
	*right = slow->get_next();
	slow->set_next(NULL);
}

// Merge 2 list together into a sorted list
node<ShopItem*>* Merge(node<ShopItem*>* left, node<ShopItem*>* right, bool choice, int ascending) {
	node<ShopItem*>* result = NULL;

	// Base case
	if (left == NULL) {
		return right;
	}
	else if (right == NULL) {
		return left;
	}

	// Sort by ID if choice == true, else sort by title
	if (choice == true) {
		if ((left->get_object()->get_id().compare(right->get_object()->get_id())) * ascending <= 0) {
			result = left;
			result->set_next(Merge(left->get_next(), right, choice, ascending));
		}
		else {
			result = right;
			result->set_next(Merge(left, right->get_next(), choice, ascending));
		}
	}
	else {
		if ((left->get_object()->get_title().compare(right->get_object()->get_title())) * ascending <= 0) {
			result = left;
			result->set_next(Merge(left->get_next(), right, choice, ascending));
		}
		else {
			result = right;
			result->set_next(Merge(left, right->get_next(), choice, ascending));
		}
	}

	return result;
}

void MergeSort(node<ShopItem*>** headRef, bool choice, int ascending) {
	node<ShopItem*>* head = *headRef;
	node<ShopItem*>* a;
	node<ShopItem*>* b;

	if ((head == NULL) || (head->get_next() == NULL)) return;

	SplitList(head, &a, &b);
	MergeSort(&a, choice, ascending);
	MergeSort(&b, choice, ascending);

	*headRef = Merge(a, b, choice, ascending);
}

void SplitList(node<Customer*>* source, node<Customer*>** left, node<Customer*>** right) {
	node<Customer*>* slow = source;
	node<Customer*>* fast = source->get_next();

	// Advance 'fast' 2 nodes, and advance 'slow' 1 node
	while (fast != NULL) {
		fast = fast->get_next();
		if (fast != NULL) {
			slow = slow->get_next();
			fast = fast->get_next();
		}
	}

	// Left list is from source to slow, Right list is from slow->next to the end (NULL)
	*left = source;
	*right = slow->get_next();
	slow->set_next(NULL);
}

node<Customer*>* Merge(node<Customer*>* left, node<Customer*>* right, bool choice, int ascending) {
	node<Customer*>* result = NULL;

	// Base case
	if (left == NULL) {
		return right;
	}
	else if (right == NULL) {
		return left;
	}

	// Sort by ID if choice == true, else sort by title
	if (choice == true) {
		if ((left->get_object()->get_id().compare(right->get_object()->get_id())) * ascending <= 0) {
			result = left;
			result->set_next(Merge(left->get_next(), right, choice, ascending));
		}
		else {
			result = right;
			result->set_next(Merge(left, right->get_next(), choice, ascending));
		}
	}
	else {
		if ((left->get_object()->get_name().compare(right->get_object()->get_name())) * ascending <= 0) {
			result = left;
			result->set_next(Merge(left->get_next(), right, choice, ascending));
		}
		else {
			result = right;
			result->set_next(Merge(left, right->get_next(), choice, ascending));
		}
	}

	return result;
}

void MergeSort(node<Customer*>** headRef, bool choice, int ascending) {
	node<Customer*>* head = *headRef;
	node<Customer*>* a;
	node<Customer*>* b;

	if ((head == NULL) || (head->get_next() == NULL)) return;

	SplitList(head, &a, &b);
	MergeSort(&a, choice, ascending);
	MergeSort(&b, choice, ascending);

	*headRef = Merge(a, b, choice, ascending);
}

void SortByID(List<ShopItem*>** itemList, int ascending) {
	node<ShopItem*>* head = (*itemList)->get_head();
	MergeSort(&head, true, ascending);
	(*itemList)->set_head(head);
}

void SortByName(List<ShopItem*>** itemList, int ascending) {
	node<ShopItem*>* head = (*itemList)->get_head();
	MergeSort(&head, false, ascending);
	(*itemList)->set_head(head);
}

void SortByID(List<Customer*>** customerList, int ascending) {
	node<Customer*>* head = (*customerList)->get_head();
	MergeSort(&head, true, ascending);
	(*customerList)->set_head(head);
}

void SortByName(List<Customer*>** customerList, int ascending) {
	node<Customer*>* head = (*customerList)->get_head();
	MergeSort(&head, false, ascending);
	(*customerList)->set_head(head);
}

bool check_int(const string& s) {
	if (s.compare("") == 0) return false;
	if (s.size() >= 10) return false;

	for (char c : s) {
		if (!isdigit(c)) return false;
	}

	return true;
}

bool check_double(const string& s) {
	if (s.length() == 0) return false;

	int dp = 0;

	for (int i = 0; i < s.length(); i++) {
		if (!isdigit(s[i])) {
			if (s[i] == '.' && dp == 0) dp++;
			else return false;
		}
	}

	return true;
}

int count_char(const string& s, char c) {
	int count = 0;

	for (char character : s) {
		if (character == c) count++;
	}

	return count;
}

const string WHITESPACE = " \n\r\t\f\v";

string ltrim(const string& s)
{
	// Find all white space character from the left to trim
	size_t start = s.find_first_not_of(WHITESPACE);
	return (start == string::npos) ? "" : s.substr(start);
}

string rtrim(const string& s)
{
	// Find all white space character from the right to trim
	size_t end = s.find_last_not_of(WHITESPACE);
	return (end == string::npos) ? "" : s.substr(0, end + 1);
}

string trim(const string& s) {
	return rtrim(ltrim(s));
}

// split_string works the same way as strtok but the parameter is a string object, while strtok parameter is a c string
string split_string(string* s, char c) {
	size_t found = (*s).find(c);
	string temp;

	// If the comma ',' is found in the string
	if (found != string::npos) {
		temp = (*s).substr(0, found); // Split the first part into temp
		*s = (*s).substr(found + 1, (*s).length()); // Split the second part and replace the original string
		return temp;
	}
	else return "";
}

string lower_case(const string& s) {
	string temp = "";

	for (char c : s) {
		temp += tolower(c);
	}
	
	return temp;
}

bool GetYesNo() {
	string option;
	cout << "Enter Y or N: ";
	getline(cin, option);

	while (1) {
		if (trim(option).compare("Y") == 0) {
			return true;
		}
		else if (trim(option).compare("N") == 0) {
			return false;
		}
		else {
			cout << "Invalid option. Enter Y or N: ";
			getline(cin, option);
		}
	}

}