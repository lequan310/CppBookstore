#include <iostream>
#include <string>
#include "Item.h"
#include "Customer.h"
#include "Utilities.h"
#include "List.h"

using namespace std;

// Function to validate new customer's input ID
bool CheckNewCustomerID(const string& id, List<Customer*>** customerList) {

    // Check if customer's ID fits specified format
    if (id.size() == 0) return false;

    if (id.size() != 4) {
        cout << "Wrong Customer ID Format. ";
        return false;
    }

    if (id[0] != 'C' || !isdigit(id[1]) || !isdigit(id[2]) || !isdigit(id[3])) {
        cout << "Wrong Customer ID Format. ";
        return false;
    }

    // ID should be unique
    // Return a notification if there is already a same ID in list 
    if (find_with_id(customerList, id) != NULL) {
        cout << "Customer ID " << id << " existed in customer list. ";
        return false;
    }

    return true;
}

// Function to validate old customer's input ID when searching for them
bool CheckExistedCustomerID(const string& id, List<Customer*>** customerList) {
    // Check if customer's ID fits specified format
    if (id.size() == 0) return false;

    if (id.size() != 4) {
        cout << "Wrong Customer ID Format. ";
        return false;
    }

    if (id[0] != 'C' || !isdigit(id[1]) || !isdigit(id[2]) || !isdigit(id[3])) {
        cout << "Wrong Customer ID Format. ";
        return false;
    }

    // Return a notification if the input ID does not exist in the list
    if (find_with_id(customerList, id) == NULL) {
        cout << "Customer ID " << id << " does not exist in customer list. ";
        return false;
    }

    return true;
}

// Function to validate new item's input ID to add them
bool CheckNewItemID(const string& id, List<ShopItem*>** itemList) {

    // Check if item's ID fits specified format
    if (id.size() == 0) return false;

    if (id.size() != 9) {
        cout << "Wrong Item ID Format. ";
        return false;
    }

    if (id[0] != 'I' || !isdigit(id[1]) || !isdigit(id[2]) || !isdigit(id[3]) || id[4] != '-'
        || !isdigit(id[5]) || !isdigit(id[6]) || !isdigit(id[7]) || !isdigit(id[8])) {
        cout << "Wrong Item ID Format. ";
        return false;
    }

    // ID should be unique
    // Return a notification if there is already a same ID in list 
    if (find_with_id(itemList, id) != NULL) {
        cout << "Item ID " << id << " existed in shop item list. ";
        return false;
    }

    return true;
}

// Function to validate existing item's input ID when searching for them
bool CheckExistedItemID(const string& id, List<ShopItem*>** itemList) {

    // Check if item's ID fits specified format
    if (id.size() == 0) return false;

    if (id.size() != 9) {
        cout << "Wrong Item ID Format. ";
        return false;
    }

    if (id[0] != 'I' || !isdigit(id[1]) || !isdigit(id[2]) || !isdigit(id[3]) || id[4] != '-'
        || !isdigit(id[5]) || !isdigit(id[6]) || !isdigit(id[7]) || !isdigit(id[8])) {
        cout << "Wrong Item ID Format. ";
        return false;
    }

    // Return a notification if the input ID does not exist in the list
    if (find_with_id(itemList, id) == NULL) {
        cout << "Item ID " << id << " does not exist in shop item list. ";
        return false;
    }

    return true;
}

// Validate item and customer's name
bool ValidateString(const string& s) {
    if (s.compare("") == 0) {
        return false;
    }

    // Return a notification if there is a comma in the name
    for (char c : s) {
        if (c == ',') {
            cout << "String cannot contain comma. ";
            return false;
        }
    }

    return true;
}

// Validate phone number
bool ValidatePhone(const string& s) {

    // Check if the phone number string is empty
    if (s.compare("") == 0) {
        return false;
    }

    for (char c : s) {
        // Check if there is a ',' in the phone number string
        if (c == ',') {
            cout << "String cannot contain comma. ";
            return false;
        }

        // Check if the phone number string contain any characters that are not numbers.
        if (!isdigit(c)) {
            cout << "Phone number can't contain non-numerical characters.\n";
            return false;
        }
    }

    return true;
}

// Function to check if an item is rented
bool NotRented(const string& id, List<Customer*>** customerList) {
    vector<Customer> own;
    node<Customer*>* current = (*customerList)->get_head();

    // Iterate through the borrowed item list to see if the item with id in question has been borrowed
    while (current != NULL) {
        Customer c = *(current->get_object());
        vector<Item> temp = c.get_list();

        for (Item i : temp) {
            if (i.get_id() == id) {
                own.push_back(c);
            }
        }

        current = current->get_next();
    }

    // If an item is rented, it cannot be modified
    if (own.size() > 0) {
        cout << "Can't modify this item variables since it is being borrowed by the following customers:\n";
        for (Customer c : own) {
            cout << c.get_id() << ", " << c.get_name() << endl;
        }

        return false;
    }

    return true;
}

// Convert shop item tokens in a line, seperated by a comma, to item properties
bool StringToItemList(string* original, List<ShopItem*>** itemList) {
    string line = *original, token, id, title;

    // First token is item ID
    token = split_string(&line, ',');
    token = trim(token);

    // Issue a notification if the token is empty
    if (token.compare("") == 0) {
        cout << "Error line: [" << *original << "]. ";
        return false;
    }

    if (!CheckNewItemID(token, itemList)) {
        cout << "Item ID: " << token << " ";
        return false;
    }

    id = token;

    // Second token is item title
    token = split_string(&line, ',');
    token = trim(token);

    // Issue a notification if the token is empty
    if (token.compare("") == 0) {
        cout << "Error line: " << *original << ". ";
        return false;
    }

    title = token;

    // Third token is rental type
    Type type;
    token = split_string(&line, ',');
    token = lower_case(trim(token));

    // Issue a notification if the token is empty
    if (token.compare("") == 0) {
        cout << "Error line: [" << *original << "]. ";
        return false;
    }

    // Issue a notification if the rental type is in the wrong format
    if (!str2type(token, &type)) {
        cout << "Rental type: " << token << " is wrong format. ";
        return false;
    }

    // Fourth token is loan type
    Loan loan;
    token = split_string(&line, ',');
    token = lower_case(trim(token));

    // Issue a notification if the token is empty
    if (token.compare("") == 0) {
        cout << "Error line: [" << *original << "]. ";
        return false;
    }

    // Issue a notification if the loan type is in the wrong format
    if (!str2loan(token, &loan)) {
        cout << "Loan type: " << token << " is wrong format. ";
        return false;
    }

    // Fifth token is number of copies
    int copies;
    token = split_string(&line, ',');
    token = trim(token);

    // Issue a notification if the token is empty
    if (token.compare("") == 0) {
        cout << "Error line: [" << *original << "]. ";
        return false;
    }

    // Check if token is able to convert into number of copies
    if (check_int(token)) {
        try {
            copies = stoi(token);
        }
        catch (exception) {
            cout << "Fail to convert " << token << " into integer. ";
            return false;
        }
    }
    else {
        cout << "Number of copies: " << token << " is wrong format. ";
        return false;
    }

    // Sixth token is item fee
    double fee;
    // If type is Game then sixth token is the last token (no genre)
    if (type == GAME) {
        token = line;
        token = trim(token);
        string temp = split_string(&line, ',');

        // In case string of game item has genre
        if (temp.compare("") != 0) {
            token = temp;
            token = trim(token);
            temp = line;
            cout << "Ignore [" << line << "] part of " << *original << endl;
        }

        // Issue a notification if the token is empty
        if (token.compare("") == 0) {
            cout << "Error line: [" << *original << "]. ";
            return false;
        }
        if (check_double(token)) {
            try {
                fee = stod(token);
            }
            catch (exception) {
                cout << "Can't convert " << token << " into double. ";
                return false;
            }
        }
        // Issue a notification if the item fee is in the wrong format
        else {
            cout << "Item fee: " << token << " is wrong format. ";
            return false;
        }

        Game* item = new Game(id, title, loan, copies, fee);
        (*itemList)->add(item);
        return true;
    }
    else {
        token = split_string(&line, ',');
        token = trim(token);

        // Issue a notification if the token is empty
        if (token.compare("") == 0) {
            cout << "Error line: [" << *original << "]. ";
            return false;
        }
        if (check_double(token)) {
            try {
                fee = stod(token);
            }
            catch (exception) {
                cout << "Fail to convert " << token << " into double. ";
                return false;
            }
        }
        // Issue a notification if item fee is in the wrong format
        else {
            cout << "Item fee: " << token << " is wrong format. ";
            return false;
        }

        // Seventh token is genre
        Genre genre;
        token = line;
        token = lower_case(trim(token));
        string temp = split_string(&line, ',');

        // In case string contains excessive parameters
        if (temp.compare("") != 0) {
            token = temp;
            token = lower_case(trim(token));
            temp = line;
            cout << "Ignore [" << line << "] part of " << *original << endl;
        }

        // Issue a notification if token is empty
        if (token.compare("") == 0) {
            cout << "Error line: [" << *original << "]. ";
            return false;
        }

        // Issue a notification if the genre is in the wrong format
        if (!str2genre(token, &genre)) {
            cout << "Genre: " << token << " is wrong format. ";
            return false;
        }

        // Add genre to applicable item type
        if (type == RECORD) {
            Record* item = new Record(id, title, loan, copies, fee, genre);
            (*itemList)->add(item);
            return true;
        }
        else {
            DVD* item = new DVD(id, title, loan, copies, fee, genre);
            (*itemList)->add(item);
            return true;
        }
    }
}

// Convert customer tokens in a line, seperated by a comma, to customer properties
bool StringToCustomer(Customer** customer, string* original, List<Customer*>** customerList, int* borrow) {
    string line = *original, token, id, name, phone, address;

    // First token is customer ID
    token = split_string(&line, ',');
    token = trim(token);

    // Issue a notification if token is empty
    if (token.compare("") == 0) {
        cout << "Error line: [" << *original << "]. ";
        return false;
    }

    if (!CheckNewCustomerID(token, customerList)) {
        return false;
    }
    id = token;

    // Second token is customer name
    token = split_string(&line, ',');
    token = trim(token);

    // Issue a notification if token is empty
    if (token.compare("") == 0) {
        cout << "Error line: [" << *original << "]. ";
        return false;
    }
    name = token;

    // Third token is customer address
    token = split_string(&line, ',');
    token = trim(token);

    // Issue a notification if token is empty
    if (token.compare("") == 0) {
        cout << "Error line: [" << *original << "]. ";
        return false;
    }
    address = token;

    // Fourth token is phone number
    token = split_string(&line, ',');
    token = trim(token);

    // Issue a notification if token is empty
    if (token.compare("") == 0) {
        cout << "Error line: [" << *original << "]. ";
        return false;
    }

    // Validate customer phone number
    for (char c : token) {
        if (!isdigit(c)) {
            cout << "Phone number: " << token << " has non numerical character. ";
            return false;
        }
    }
    phone = token;

    // Fifth token is number of borrowed items
    token = split_string(&line, ',');
    token = trim(token);

    // Issue a notification if token is empty
    if (token.compare("") == 0) {
        cout << "Error line: [" << *original << "]. ";
        return false;
    }

    // Attempt to convert token into integer
    if (check_int(token)) {
        try {
            *borrow = stoi(token);
        }
        catch (exception) {
            cout << "Can't convert " << token << " into integer. ";
            return false;
        }
    }
    else {
        // Issue a notification if number of borrowed items is in the wrong format
        cout << "Number of borrowed items: " << token << " is wrong format. ";
        return false;
    }

    // Sixth token is customer level
    Level level;
    token = line;
    token = lower_case(trim(token));

    // Issue a notification if token is empty
    if (token.compare("") == 0) {
        cout << "Error line: [" << *original << "]. ";
        return false;
    }

    // Issue a notification if number of borrowed items is in the wrong format
    if (!str2level(token, &level)) {
        cout << "Customer level: " << token << " is in wrong format. ";
        return false;
    }

    Customer* temp = NULL;

    // Cross-check to make sure guest users can only own two items
    if (level == GUEST) {
        if (*borrow > GUEST_MAX) {
            cout << "Guest " << id << " has " << to_string(*borrow) << " in rent list. ";
            cout << "The program will only read the first 2 possible items.\n";
            *borrow = GUEST_MAX;
        }

        temp = new Guest(id, name, address, phone);
    }

    else if (level == REGULAR) {
        temp = new Regular(id, name, address, phone);
    }
    else if (level == VIP) {
        temp = new Vip(id, name, address, phone);
    }

    (*customerList)->add(temp);
    *customer = temp;
    return true;
}