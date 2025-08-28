#include <iostream>
#include <string>
#include <fstream>
#include "Input.h"
#include "Item.h"
#include "Customer.h"
#include "List.h"
#include "Utilities.h"
#include "Validation.h"

using namespace std;

// Function to get user's option input 
int get_option() {
    string input;

    cout << "Enter option: ";
    getline(cin, input);

    // Validate user's input
    if (check_int(input)) {
        try {
            return stoi(input);
        }
        catch (exception) {
            return -1;
        }
    }

    return -1;
}

// Function to get user's option input for exit/back
int get_option(const string& s) {
    string input;

    cout << "Enter option: ";
    getline(cin, input);
    input = lower_case(input);

    // Validate user's input
    if (input.compare(s) == 0) return 0;

    if (check_int(input)) {
        try {
            if (stoi(input) == 0) return -1;

            return stoi(input);
        }
        catch (exception) {
            return -1;
        }
    }

    return -1;
}

// Function to ask user for item details  
ShopItem* GetShopItem(List<ShopItem*>** itemList) {
    string id = "", title = "", type = "", loan = "", stock = "", fee = "", genre = "";
    Type _type;
    Loan _loan;
    Genre _genre = NONE;

    // Ask for user's input then validate those inputs
    while (!CheckNewItemID(id, itemList)) {
        cout << "Enter item ID (Format: I000-0000): ";
        getline(cin, id);
        id = trim(id);
    }

    while (!ValidateString(title)) {
        cout << "Enter item title: ";
        getline(cin, title);
        title = trim(title);
    }

    while (!str2type(type, &_type)) {
        cout << "Enter item rental type (DVD, Record, Game): ";
        getline(cin, type);
        type = lower_case(trim(type));
    }

    while (!str2loan(loan, &_loan)) {
        cout << "Enter item loan type (2-day OR 1-week): ";
        getline(cin, loan);
        loan = lower_case(trim(loan));
    }

    while (!check_int(trim(stock))) {
        cout << "Enter item number of copies held in stock: ";
        getline(cin, stock);
    }

    while (!check_double(trim(fee))) {
        cout << "Enter item rental fee: ";
        getline(cin, fee);
    }

    if (_type != GAME) {
        while (!str2genre(genre, &_genre)) {
            cout << "Enter item genre (Action, Horror, Drama, Comedy): ";
            getline(cin, genre);
            genre = lower_case(trim(genre));
        }
    }

    // Identify the type of item
    if (_type == GAME) {
        Game* temp = new Game(id, title, _loan, stoi(stock), stod(fee));
        return temp;
    }
    else if (_type == RECORD) {
        Record* temp = new Record(id, title, _loan, stoi(stock), stod(fee), _genre);
        return temp;
    }
    else if (_type == DVDDISK) {
        DVD* temp = new DVD(id, title, _loan, stoi(stock), stod(fee), _genre);
        return temp;
    }
    else return NULL;
}

// Function to ask user for customer's detail
Customer* GetCustomer(List<Customer*>** customerList) {
    string id = "", name = "", address = "", phone = "", level = "";
    Level _level = GUEST;

    // Ask for user's input then validate those inputs
    while (!CheckNewCustomerID(id, customerList)) {
        cout << "Enter customer ID (Format: C000): ";
        getline(cin, id);
        id = trim(id);
    }

    while (!ValidateString(name)) {
        cout << "Enter customer name: ";
        getline(cin, name);
        name = trim(name);
    }

    while (!ValidateString(address)) {
        cout << "Enter customer address: ";
        getline(cin, address);
        address = trim(address);
    }

    while (!ValidatePhone(phone)) {
        cout << "Enter customer phone number: ";
        getline(cin, phone);
        phone = trim(phone);
    }

    while (!str2level(level, &_level)) {
        cout << "Enter customer level (Guest, Regular, VIP): ";
        getline(cin, level);
        level = lower_case(trim(level));
    }

    // Identify the type of customers
    if (_level == GUEST) {
        Guest* guest = new Guest(id, name, address, phone);
        return guest;
    }
    else if (_level == REGULAR) {
        Regular* regular = new Regular(id, name, address, phone);
        return regular;
    }
    else if (_level == VIP) {
        Vip* vip = new Vip(id, name, address, phone);
        return vip;
    }
    else return NULL;
}

// Function to search for item by name to update
ShopItem* ChooseShopItem(const string& name, List<ShopItem*>** itemList) {
    if (name.compare("") == 0) return NULL;

    vector<ShopItem*> found = find_with_name(itemList, name);

    // There is no item with the listed name
    if (found.size() == 0) {
        cout << "There is no item with the name " << name << " in the shop item list.\n";
        return NULL;
    }
    // There is one item with the listed name
    else if (found.size() == 1) {
        return found[0];
    }
    // More than one item with same name
    else {
        int choice = 0;

        cout << "Found:\n";
        for (int i = 0; i < found.size(); i++) {
            cout << i + 1 << ". " << found[i]->toString() << endl;
        }

        cout << "Enter item order number above. ";
        choice = get_option();

        if (choice >= 1 && choice <= found.size()) {
            return found[choice - 1];
        }
        else {
            cout << "Invalid choice.\n";
            return NULL;
        }
    }
}

// Function to search for customer by name
Customer* ChooseCustomer(const string& name, List<Customer*>** customerList) {
    if (name.compare("") == 0) return NULL;

    vector<Customer*> found = find_with_name(customerList, name);

    // No customer with same name
    if (found.size() == 0) {
        cout << "There is no customer with name " << name << " in the customer list.\n";
        return NULL;
    }
    // One customer with same name
    else if (found.size() == 1) {
        return found[0];
    }
    // More than one customer with same name
    else {
        int choice = 0;

        cout << "Found:\n";
        for (int i = 0; i < found.size(); i++) {
            cout << i + 1 << ". " << found[i]->toString() << endl;
        }

        cout << "Enter customer order number above. ";
        choice = get_option();

        if (choice >= 1 && choice <= found.size()) {
            return found[choice - 1];
        }
        else {
            cout << "Invalid choice.\n";
            return NULL;
        }
    }
}

// Function to validate and load item file data
bool LoadFile(List<ShopItem*>** itemList, const string& fileName) {
    int line = 0;

    fstream file;
    file.open(fileName, ios::in);

    // Return notification if unable to open the file
    if (!file.is_open()) {
        cout << "Fail to open item file.\n";
        return false;
    }

    string original = "";

    // Check if data line is valid
    // Ignore a line if it is invalid
    while (getline(file, original)) {
        line++;

        if (!StringToItemList(&original, itemList)) {
            cout << "(Ignore line " << to_string(line) << ", " << fileName << ")\n";;
        }
    }

    // Close the file and issue a notification if successfully loaded
    file.close();
    cout << "Loaded item file to shop item list successfully.\n\n";
    return true;
}

// Function to validate and load customer file data
bool LoadFile(List<ShopItem*>** itemList, List<Customer*>** customerList, const string& fileName) {
    int line = 0;

    fstream file;
    file.open(fileName, ios::in);

    // Issue notification if unable to open the file
    if (!file.is_open()) {
        cout << "Fail to open customer file.\n";
        return false;
    }

    string original;
    bool started = false;
    int tempCount = 0, borrow = 0;
    Customer* customer = NULL;

    while (getline(file, original)) {
        line++;
        original = trim(original);

        // 5 comma means customer line
        // Cross-check if a customer is missing an item
        if (count_char(original, ',') == CUSTOMER_COMMA) {
            if (tempCount < borrow && started == true) {
                cout << "Customer " << customer->get_id() << " is missing " << to_string(borrow - tempCount) << " items. ";
                cout << "Program will change the number of borrowed items for customer " << customer->get_id() << " to " << to_string(tempCount) << " items.\n";
                customer->set_borrow(tempCount);
            }
            else if (tempCount > borrow && started == true) {
                cout << "Customer " << customer->get_id() << " borrowed more than " << to_string(borrow) << " items. ";
                cout << "Program will change the number of borrowed items for customer " << customer->get_id() << " to " << to_string(tempCount) << " items.\n";
                customer->set_borrow(tempCount);
            }

            if (StringToCustomer(&customer, &original, customerList, &borrow)) {
                started = true;
                tempCount = 0;
            }
            else {
                cout << "(Ignore line " << to_string(line) << ", " << fileName << ")\n";
                started = false;
                tempCount = 0;
                borrow = 0;
            }
        }
        // No comma means item line
        // Check if data line is valid
        // Ignore a line if it is invalid
        else if (count_char(original, ',') == 0) {
            if (!CheckExistedItemID(original, itemList)) {
                cout << "(Ignore line " << to_string(line) << ", " << fileName << ")\n";;
                continue;
            }

            if (!started) {
                cout << "Can't detect customers before. (Ignore line " << to_string(line) << ", " << fileName << ")\n";;
                continue;
            }

            if (customer->borrow(itemList, original)) {
                tempCount++;
            }
            else {
                cout << "(Ignore line " << to_string(line) << ", " << fileName << ")\n";;
            }
        }
        else {
            cout << "Line error: [" << original << "]. (Ignore line " << to_string(line) << ", " << fileName << ")\n";;
        }
    }

    // Inform user of reduced items borrowed when they are missing 
    if (tempCount < borrow && started == true) {
        cout << "Customer " << customer->get_id() << " is missing " << to_string(borrow - tempCount) << " items. ";
        cout << "Program will change the number of borrowed items for customer " << customer->get_id() << " to " << to_string(tempCount) << " items.\n";
        customer->set_borrow(tempCount);
    }
    else if (tempCount > borrow && started == true) {
        cout << "Customer " << customer->get_id() << " borrowed more than " << to_string(borrow) << " items. ";
        cout << "Program will change the number of borrowed items for customer " << customer->get_id() << " to " << to_string(tempCount) << " items.\n";
        customer->set_borrow(tempCount);
    }

    // Close the file and issue a notification if file loaded successfully
    file.close();
    cout << "Loaded customer file to customer list successfully.\n";
    return true;
}

// Function to save customer and item data into a file
bool SaveFile(List<ShopItem*>** itemList, List<Customer*>** customerList, const string& itemFile, const string& customerFile) {
    SortByID(itemList, 1);
    SortByID(customerList, 1);

    //Save items to a file and issue a notification when done
    fstream fout;
    fout.open(itemFile, ios::out);
    (*itemList)->print_list(fout);
    fout.close();
    cout << "Save shop item list to " << itemFile << " successfully.\n";

    //Save customers to a file and issue a notification when done
    fout.open(customerFile, ios::out);

    node<Customer*>* customerNode = (*customerList)->get_head();

    while (customerNode != NULL) {
        Customer* customer = customerNode->get_object();
        fout << customer->toString() << endl;

        for (Item item : customer->get_list()) {
            fout << item.get_id() << endl;
        }

        customerNode = customerNode->get_next();
    }

    fout.close();
    cout << "Save customer list to " << customerFile << " successfully.\n";

    return true;
}