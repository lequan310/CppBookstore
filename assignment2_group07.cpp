#include <iostream>
#include "Item.h"
#include "Customer.h"
#include "List.h"
#include "Utilities.h"
#include "Input.h"
#include "Validation.h"
#include "Menu.h"

using namespace std;

// Sub-menu 1 (Add, update or delete item)
void SubMenu1(List<ShopItem*>** itemList, List<Customer*>** customerList) {
    // Output the options to the screen
    OptionMenu1();

    int option;

    // Loop the sub-menu until 0 (back) is entered
    while ((option = get_option()) != 0) {

        // Add a new item to item list
        if (option == 1) {
            ShopItem* addedItem;

            if ((addedItem = GetShopItem(itemList)) != NULL) {
                (*itemList)->add(addedItem);
                cout << "Add [" << addedItem->toString() << "] to shop item list successfully.\n";
            }

            break;
        }

        // Update an existing item
        else if (option == 2) {
            string itemID = "";
            int option2;

            // Output search options to the screen
            FindItemOutput();

            // Loop until received 0 (back) from user
            while ((option2 = get_option()) != 0) {

                // Search for the item via ID 
                if (option2 == 1) {

                    // Enter and check if the ID is valid
                    while (!CheckExistedItemID(itemID, itemList)) {
                        cout << "Enter item ID: ";
                        getline(cin, itemID);
                        itemID = trim(itemID);
                    }
                    break;
                }

                // Search for the item via name
                else if (option2 == 2) {
                    ShopItem* temp;
                    string itemTitle = "";

                    // Enter and validate the name
                    cout << "Enter item title: ";
                    getline(cin, itemTitle);
                    itemTitle = trim(itemTitle);

                    // Loop until found the item with matching name
                    while ((temp = ChooseShopItem(itemTitle, itemList)) == NULL) {
                        cout << "Enter item title: ";
                        getline(cin, itemTitle);
                        itemTitle = trim(itemTitle);
                    }

                    itemID = temp->get_id();
                    break;
                }

                // If anything other than the listed options were entered
                else {
                    cout << "Invalid option.\n";
                }
            }

            node<ShopItem*>* itemNode;
            if ((itemNode = find_with_id(itemList, itemID)) != NULL) {
                ShopItem* item = itemNode->get_object();

                string id = "", title = "", type = "", loan = "", stock = "", fee = "", genre = "";
                Loan _loan;
                Genre _genre = NONE;

                // Display possible options for updating items
                cout << "Old item: [" << item->toString() << "]. (Current stock: " << to_string(item->get_stock()) << ")\n\n";
                cout << "1. Update item ID\n"; // Can't update if borrowed
                cout << "2. Update item title\n"; // Can't update if borrowed
                cout << "3. Update item genre\n"; // Can't update if borrowed
                cout << "4. Update item stock\n"; // Can update if borrowed
                cout << "5. Update item loan type\n"; // Can't update if borrowed
                cout << "6. Update item fee\n"; // Can update if borrowed
                cout << "0. Back\n";

                // Loop until received 0 (back) from user
                while ((option2 = get_option()) != 0)
                {
                    // Update item ID
                    if (option2 == 1) {
                        if (NotRented(itemID, customerList)) {
                            cout << "Enter item new ID: ";
                            getline(cin, id);

                            while (!CheckNewItemID(id, itemList)) {
                                cout << "Enter item new ID: ";
                                getline(cin, id);
                                id = trim(id);
                            }

                            item->set_id(id);
                            id = "";
                        }
                    }
                    // Update item title
                    else if (option2 == 2) {
                        if (NotRented(itemID, customerList)) {
                            while (!ValidateString(title)) {
                                cout << "Enter item new title: ";
                                getline(cin, title);
                                title = trim(title);
                            }

                            item->set_title(title);
                            title = "";
                        }
                    }

                    // Update item genre
                    else if (option2 == 3) {
                        if (NotRented(itemID, customerList)) {
                            if (item->isDVD() || item->isRecord()) {
                                while (!str2genre(lower_case(trim(genre)), &_genre)) {
                                    cout << "Enter item new genre (Action, Horror, Drama, Comedy): ";
                                    getline(cin, genre);
                                }

                                item->set_genre(_genre);
                                genre = "";
                            }
                            else {
                                cout << "Item with rental type Game does not have a genre variable.\n";
                            }
                        }
                    }

                    // Update amount of stock
                    else if (option2 == 4) {
                        cout << "Enter item number of copies held in stock: ";
                        getline(cin, stock);

                        while (!check_int(trim(stock))) {
                            cout << "Wrong input format. Re-enter item number of copies held in stock: ";
                            getline(cin, stock);
                        }

                        try {
                            int newStock = stoi(stock);
                            int newCopies = item->get_copies() + (newStock - item->get_stock());

                            item->set_copies(newCopies);
                            item->set_stock(newStock);
                            stock = "";
                        }
                        catch (exception) {
                            cout << "Can't convert " << stock << " into integer.\n";
                            stock = "";
                        }
                    }

                    // Update loan type
                    else if (option2 == 5) {
                        if (NotRented(itemID, customerList)) {
                            while (!str2loan(lower_case(trim(loan)), &_loan)) {
                                cout << "Enter item loan type (2-day OR 1-week): ";
                                getline(cin, loan);
                            }

                            item->set_loan(_loan);
                            loan = "";
                        }
                    }

                    // Update rental fee
                    else if (option2 == 6) {
                        while (!check_double(trim(fee))) {
                            cout << "Enter item rental fee: ";
                            getline(cin, fee);
                        }

                        try {
                            item->set_fee(stod(fee));
                            fee = "";
                        }
                        catch (exception) {
                            cout << "Can't convert to double.\n";
                        }
                    }
                    else {
                        cout << "Invalid option.\n";
                    }
                }

                cout << "Updated item: [" << item->toString() << "]. (Current stock: " << to_string(item->get_stock()) << ")\n";
            }

            // Return notification if no item with listed ID is found
            else {
                cout << "There is no item with ID " << itemID << " in the shop item list.\n";
            }

            break;
        }

        // Delete an existing item
        else if (option == 3) {
            string itemID = "";
            int option2;
            ShopItem* temp;

            // Output search option to the screen
            FindItemOutput();

            // Search for item via ID
            while ((option2 = get_option()) != 0) {
                if (option2 == 1) {
                    while (!CheckExistedItemID(itemID, itemList)) {
                        cout << "Enter item ID: ";
                        getline(cin, itemID);
                        itemID = trim(itemID);
                    }

                    break;
                }

                // Search for item via title
                else if (option2 == 2) {
                    string itemTitle = "";
                    cout << "Enter item title: ";
                    getline(cin, itemTitle);
                    itemTitle = trim(itemTitle);

                    // Iterate item user input until a matching title is found in the list 
                    while ((temp = ChooseShopItem(itemTitle, itemList)) == NULL) {
                        cout << "Enter item title: ";
                        getline(cin, itemTitle);
                        itemTitle = trim(itemTitle);
                    }

                    itemID = temp->get_id();
                    break;
                }
                else {
                    cout << "Invalid option.\n";
                }
            }

            node<ShopItem*>* itemNode = find_with_id(itemList, itemID);

            // Delete an existing item from the shop item list
            if (itemNode != NULL) {
                if (NotRented(itemID, customerList)) {
                    ShopItem* item = itemNode->get_object();
                    string removed = item->toString();

                    (*itemList)->remove(itemNode->get_object());
                    cout << "Remove [" << removed << "] from shop item list successfully.\n";
                }
            }

            // Issue a notification if no item with the provided ID is found
            else {
                cout << "There is no item with ID " << itemID << " in the shop item list.\n";
            }

            break;
        }
        else {
            cout << "Invalid option\n";
        }
    }
}

// Sub-menu 2 (Add or update customer)
void SubMenu2(List<Customer*>** customerList) {
    OptionMenu2();

    int option;

    while ((option = get_option()) != 0) {

        // Add a new customer
        if (option == 1) {
            cout << "Note: Add customer and then go to borrow section to add books to rent list.\n";

            Customer* customer;
            if ((customer = GetCustomer(customerList)) != NULL) {
                (*customerList)->add(customer);
                cout << "Add [" << customer->toString() << "] to customer list successfully.\n";
            }

            break;
        }

        // Update an existing customer
        else if (option == 2) {
            string customerID = "";
            int option2;

            // Ouput search options to the screen
            FindCustomerOutput();

            while ((option2 = get_option()) != 0) {

                // Search and validate for customer by ID
                if (option2 == 1) {
                    while (!CheckExistedCustomerID(customerID, customerList)) {
                        cout << "Enter customer ID: ";
                        getline(cin, customerID);
                        customerID = trim(customerID);
                    }

                    break;
                }


                // Search and validate for customer by name
                else if (option2 == 2) {
                    Customer* temp;
                    string customerName;

                    while ((temp = ChooseCustomer(customerName, customerList)) == NULL) {
                        cout << "Enter customer name: ";
                        getline(cin, customerName);
                        customerName = trim(customerName);
                    }

                    customerID = temp->get_id();
                    break;
                }
                else {
                    cout << "Invalid option.\n";
                }
            }

            node<Customer*>* customerNode;
            if ((customerNode = find_with_id(customerList, customerID)) != NULL) {
                Customer* customer = customerNode->get_object();

                string id = "", name = "", address = "", phone = "";

                // Output customer update options
                cout << "Customer before update: " << customer->toString() << endl;
                cout << "1. Update customer ID\n";
                cout << "2. Update customer name\n";
                cout << "3. Update customer address\n";
                cout << "4. Update customer phone number\n";
                cout << "0. Back\n";

                while ((option2 = get_option()) != 0) {

                    // Update customer ID
                    if (option2 == 1) {
                        cout << "Enter customer ID: ";
                        getline(cin, id);

                        // Ask and validate for the new customer ID
                        while (!CheckNewCustomerID(id, customerList)) {
                            cout << "Enter new customer ID: ";
                            getline(cin, id);
                            id = trim(id);
                        }

                        customer->set_id(id);
                        id = "";
                    }

                    // Update customer name
                    else if (option2 == 2) {

                        // Ask and validate for the new customer name
                        while (!ValidateString(name)) {
                            cout << "Enter customer name: ";
                            getline(cin, name);
                            name = trim(name);
                        }

                        customer->set_name(name);
                        name = "";
                    }

                    // Update and validate customer address
                    else if (option2 == 3) {
                        while (!ValidateString(address)) {
                            cout << "Enter customer address: ";
                            getline(cin, address);
                            address = trim(address);
                        }

                        customer->set_address(address);
                        address = "";
                    }

                    // Update and validate customer phone number
                    else if (option2 == 4) {
                        while (!ValidatePhone(phone)) {
                            cout << "Enter customer phone number: ";
                            getline(cin, phone);
                            phone = trim(phone);
                        }

                        customer->set_phone(phone);
                        phone = "";
                    }
                    else {
                        cout << "Invalid option.\n";
                    }
                }

                // Display all details about customer after update
                cout << "Customer after update: " << customer->toString() << endl;
            }

            // Issue a notification if given ID match no customer in the list
            else {
                cout << "There is no customer with ID " << customerID << " in the customer list.\n";
            }

            break;
        }
        else {
            cout << "Invalid option\n";
        }
    }
}

// Sub-menu 3 (Promote customer with ID or name)
void SubMenu3(List<Customer*>** customerList) {
    int option;
    string id, name;
    node<Customer*>* tempNode;

    // Output all promote options, either by ID or name
    OptionMenu3();

    while ((option = get_option()) != 0) {

        // Promote customer by ID
        if (option == 1) {

            // Ask user for the ID
            cout << "Enter customer ID: ";
            getline(cin, id);

            // Find the customer with given ID
            if ((tempNode = find_with_id(customerList, id)) != NULL) {
                Customer* customer = tempNode->get_object();

                // Check if the guest customer has met the requirement for promotion
                if (customer->get_level() == GUEST) {
                    if (customer->get_return() <= 3) {

                        // Display the requirement for promotion if condition not met
                        cout << customer->get_id() << " needs to return more than 3 items successfully to be promoted. ";
                        cout << "Currently returned " << customer->get_borrow() << " items.\n";
                        return;
                    }

                    Regular* regular = new Regular(*customer);

                    // Promote guest customers to regular customers
                    (*customerList)->remove(customer);
                    (*customerList)->add(regular);
                    cout << "Customer " << id << ", " << regular->get_name() << " has been promoted to Regular.\n";
                }

                // Check if the regular customer has met the requirement for promotion
                else if (customer->get_level() == REGULAR) {
                    if (customer->get_return() <= 3) {

                        // Display the requirement for promotion if condition not met
                        cout << customer->get_id() << " needs to return more than 3 items successfully to be promoted. ";
                        cout << "Currently returned " << customer->get_borrow() << " items.\n";
                        return;
                    }

                    Vip* vip = new Vip(*customer);

                    // Promote regular customers to vip customers
                    (*customerList)->remove(customer);
                    (*customerList)->add(vip);
                    cout << "Customer " << id << ", " << vip->get_name() << " has been promoted to VIP.\n";
                }

                // VIP customers can not be promoted further
                else if (customer->get_level() == VIP) {
                    cout << "Customer is at highest level (VIP).\n";
                }
            }

            // Issue a notification if no customer with provided ID is found
            else {
                cout << "There is no customer with ID " << id << " in the customer list.\n";
            }

            break;
        }

        // Promote customer by name
        else if (option == 2) {
            Customer* customer;

            // Ask user for the name
            cout << "Enter customer name: ";
            getline(cin, name);
            name = trim(name);

            // Find the customer with given name
            if ((customer = ChooseCustomer(name, customerList)) != NULL) {

                // Check if the guest customer has met the requirement for promotion
                if (customer->get_level() == GUEST) {
                    if (customer->get_return() <= 3) {

                        // Display the requirement for promotion if condition not met
                        cout << customer->get_id() << " needs to return more than 3 items successfully to be promoted. ";
                        cout << "Currently borrow " << customer->get_borrow() << " items.\n";
                        return;
                    }

                    Regular* regular = new Regular(*customer);

                    // Promote guest customers to regular customers
                    (*customerList)->remove(customer);
                    (*customerList)->add(regular);
                    cout << "Customer " << id << ", " << regular->get_name() << " has been promoted to Regular.\n";
                }

                // Check if the regular customer has met the requirement for promotion
                else if (customer->get_level() == REGULAR) {
                    if (customer->get_return() <= 3) {

                        // Check if the regular customer has met the requirement for promotion
                        cout << customer->get_id() << " needs to return more than 3 items successfully to be promoted. ";
                        cout << "Currently borrow " << customer->get_borrow() << " items.\n";
                        return;
                    }

                    Vip* vip = new Vip(*customer);

                    // Promote regular customers to VIP customers
                    (*customerList)->remove(customer);
                    (*customerList)->add(vip);
                    cout << "Customer " << id << ", " << vip->get_name() << " has been promoted to VIP.\n";
                }

                // VIP customers can not be promoted further
                else if (customer->get_level() == VIP) {
                    cout << "Customer is at highest level (VIP).\n";
                }
            }
            else {
                cout << "Invalid choice.\n";
                return;
            }
        }
        else {
            cout << "Invalid option. Please re-enter your option.\n";
        }
    }
}

//Sub-menu 4 (Rent or return an item)
void SubMenu4(List<ShopItem*>** itemList, List<Customer*>** customerList) {
    string customerID, customerName, itemID;
    int option, option2;
    node<Customer*>* customerNode;
    Customer* customer = NULL;

    // Get customer information
    cout << "---------------------------------------------------------\n";
    FindCustomerOutput();

    while ((option2 = get_option()) != 0) {
        if (option2 == 1) {

            // Ask for customer ID
            cout << "Enter customer ID: ";
            getline(cin, customerID);

            // Iterate through customer list to find matching ID
            if ((customerNode = find_with_id(customerList, customerID)) != NULL) {
                customer = customerNode->get_object();
            }

            // Return a notification if no customer with given ID is found
            else {
                cout << "Can't find customer with ID " << customerID << " in the customer list.\n";
                return;
            }

            break;
        }
        else if (option2 == 2) {

            // Ask for customer name
            cout << "Enter customer name: ";
            getline(cin, customerName);

            // Iterate through customer list to find matching name 
            if ((customer = ChooseCustomer(customerName, customerList)) == NULL) {
                return;
            }

            break;
        }
        else {
            cout << "Invalid option.\n";
        }
    }

    if (option2 == 0) return;

    // Get item information
    cout << "---------------------------------------------------------\n";
    cout << "Current customer: [" << customer->get_id() << " " << customer->get_name() << "]\n";

    // Display action list
    OptionMenu4();

    while ((option = get_option()) != 0) {
        itemID = "";

        // Rent an item
        if (option == 1) {
            
            // Ask and validate item ID
            while (!CheckExistedItemID(itemID, itemList)) {
                cout << "Enter item ID: ";
                getline(cin, itemID);
                itemID = trim(itemID);
            }

            // Give the identified ID to found customer
            customer->borrow_item(itemList, itemID);

            OptionMenu4();
            continue;
        }

        // Return an item
        else if (option == 2) {

            // Ask and validate item ID
            while (!CheckExistedItemID(itemID, itemList)) {
                cout << "Enter item ID: ";
                getline(cin, itemID);
                itemID = trim(itemID);
            }

            // Receive the item from found customer
            customer->return_item(itemList, itemID);

            OptionMenu4();
            continue;
        }
        else {
            cout << "Invalid option\n";
        }
    }
}

// Sub-menu 5 (Display all item sotred with ID or title in ascending or descending order)
void SubMenu5(List<ShopItem*>** itemList) {

    // Output to the screen the sort options
    OptionMenu5();

    int option;

    while ((option = get_option()) != 0) {

        // Display all item sorted by ID (Ascending)
        if (option == 1) {

            // Sort the item list by ID ascending
            SortByID(itemList, 1);

            // Print out the sorted list
            if ((*itemList)->get_size() != 0) {
                (*itemList)->print_list();
            }

            // Issue a notification if there are no items in the list
            else {
                cout << "There are no items in the shop item list.\n";
            }

            break;
        }

        // Display all item sorted by ID (Descending)
        else if (option == 2) {

            // Sort the item list by ID descending
            SortByID(itemList, -1);

            // Print out the sorted list
            if ((*itemList)->get_size() != 0) {
                (*itemList)->print_list();
            }

            // Issue a notification if there are no items in the list
            else {
                cout << "There are no items in the shop item list.\n";
            }

            break;
        }

        // Display all item sorted by title (Ascending)
        else if (option == 3) {

            // Sort the item list by title ascending
            SortByName(itemList, 1);

            // Print out the sorted list
            if ((*itemList)->get_size() != 0) {
                (*itemList)->print_list();
            }

            // Issue a notification if there are no items in the list
            else {
                cout << "There are no items in the shop item list.\n";
            }

            break;
        }

        // Display all item sorted by title (Descending)
        else if (option == 4) {

            // Sort the item list by title descending
            SortByName(itemList, -1);

            // Print out the sorted list
            if ((*itemList)->get_size() != 0) {
                (*itemList)->print_list();
            }

            // Issue a notification if there are no items in the list
            else {
                cout << "There are no items in the shop item list.\n";
            }

            break;
        }
        else {
            cout << "Invalid option\n";
        }
    }
}

// Display out-of-stock items
void SubMenu6(List<ShopItem*>** itemList) {
    int count = 0;
    node<ShopItem*>* curr = (*itemList)->get_head();

    // Iterate through item list to find out-of-stock items
    while (curr != NULL) {
        if (curr->get_object()->get_stock() == 0) {
            cout << curr->get_object() ->toString() << endl;
            count++;
        }

        curr = curr->get_next();
    }

    // Return notification if no out-of-stock items are found
    if (count == 0) {
        cout << "There are no out-of-stock items in the shop item list.\n";
    }
}

// Sub-menu 7 (Display customer sotred by ID or name in ascending or descending order)
void SubMenu7(List<Customer*>** customerList) {

    // Output to the screen sorting options
    OptionMenu7();

    int option;

    while ((option = get_option()) != 0) {

        // Display all customer sorted by ID (Ascending)
        if (option == 1) {
            // Sort customer list ascending by ID
            SortByID(customerList, 1);

            // Print out the sorted list
            if ((*customerList)->get_size() != 0) {
                (*customerList)->print_list();
            }

            // Issue a notification if there are no customers in the list
            else {
                cout << "There are no customers in the customer list.\n";
            }

            break;
        }

        // Display all customer sorted by ID (Descending)
        else if (option == 2) {

            // Sort customer list descending by ID
            SortByID(customerList, -1);

            // Print out the sorted list
            if ((*customerList)->get_size() != 0) {
                (*customerList)->print_list();
            }

            // Issue a notification if there are no customers in the list
            else {
                cout << "There are no customers in the customer list.\n";
            }

            break;
        }

        // Display all customer sorted by name (Ascending)
        else if (option == 3) {

            // Sort customer list ascending by name
            SortByName(customerList, 1);

            // Print out the sorted list
            if ((*customerList)->get_size() != 0) {
                (*customerList)->print_list();
            }

            // Issue a notification if there are no customers in the list
            else {
                cout << "There are no customers in the customer list.\n";
            }

            break;
        }

        // Display all customer sorted by name (Ascending)
        else if (option == 4) {

            // Sort customer list descending by name
            SortByName(customerList, -1);

            // Print out the sorted list
            if ((*customerList)->get_size() != 0) {
                (*customerList)->print_list();
            }

            // Issue a notification if there are no customers in the list
            else {
                cout << "There are no customers in the customer list.\n";
            }

            break;
        }
        else {
            cout << "Invalid option\n";
        }
    }
}

// Sub-menu 8 (Display guest, regular or VIP customer)
void SubMenu8(List<Customer*>** customerList) {

    // Output to the screen the list of display options
    OptionMenu8();

    int option, count = 0;
    node<Customer*>* current;

    // Sort the customer list by ID
    SortByID(customerList, 1);
    current = (*customerList)->get_head();

    while ((option = get_option()) != 0) {

        // Display all guest customers
        if (option == 1) {

            // Iterate through customer list to output customers with the type GUEST
            while (current != NULL) {
                if (current->get_object()->get_level() == GUEST) {
                    cout << current->get_object()->toString() << endl;
                    count++;
                }

                current = current->get_next();
            }

            // Return a notification if no customer iwht type GUEST is found
            if (count == 0) {
                cout << "There are no Guest in the customer list.\n";
            }

            break;
        }

        // Display all regular customers
        else if (option == 2) {

            // Iterate through customer list to output customers with the type REGULAR
            while (current != NULL) {
                if (current->get_object()->get_level() == REGULAR) {
                    cout << current->get_object()->toString() << endl;
                    count++;
                }

                current = current->get_next();
            }

            // Return a notification if no customer iwht type REGULAR is found
            if (count == 0) {
                cout << "There are no Regular in the customer list.\n";
            }

            break;
        }

        // Display all VIP customers
        else if (option == 3) {

            // Iterate through customer list to output customers with the type VIP
            while (current != NULL) {
                if (current->get_object()->get_level() == VIP) {
                    cout << current->get_object()->toString() << endl;
                    count++;
                }

                current = current->get_next();
            }

            // Return a notification if no customer iwht type VIP is found
            if (count == 0) {
                cout << "There are no VIP in the customer list.\n";
            }

            break;
        }
        else {
            cout << "Invalid option\n";
        }
    }
}

// Sub-menu 9 (Searching for item or customer by ID or name)
void SubMenu9(List<ShopItem*>** itemList, List<Customer*>** customerList) {
    OptionMenu9();

    int option;
    string id, name;

    while ((option = get_option()) != 0) {
        id = "", name = "";

        if (option == 1) {

            // Ask for user's input item ID, validate, and search for it
            while (!CheckExistedItemID(id, itemList)) {
                cout << "Enter item ID: ";
                getline(cin, id);
                id = trim(id);
            }

            // Find item associated with the given item ID
            search_with_id(itemList, id);
            break;
        }
        else if (option == 2) {

            // Ask for user's input title, validate, and search for it
            cout << "Enter item title: ";
            getline(cin, name);

            vector<ShopItem*> found = find_with_name(itemList, name);

            // Issue a notification if item not found
            if (found.size() == 0) {
                cout << "Shop doesn't have any item with name: " << name << endl;
                return;
            }

            // Issue item's information if it is found in the list
            for (ShopItem* item : found) {
                cout << "Found [" << item->toString() << "] - (Current stock: " << to_string(item->get_stock()) << ")\n";
            }

            break;
        }

        // Search for customer via ID
        else if (option == 3) {
            while (!CheckExistedCustomerID(id, customerList)) {
                cout << "Enter customer ID: ";
                getline(cin, id);
                id = trim(id);
            }

            search_with_id(customerList, id);
            break;
        }

        // Search for customer via name
        else if (option == 4) {
            cout << "Enter customer name: ";
            getline(cin, name);

            vector<Customer*> found = find_with_name(customerList, name);

            // Issue a notification if no user with specified name is in the list
            if (found.size() == 0) {
                cout << "Shop doesn't have any customer with name: " << name << endl;
                return;
            }

            // Issue the customer name with their owned items if their name is found in the list
            for (Customer* customer : found) {
                cout << "Found [" << customer->toString() << "]. Owned items:\n";
                customer->output_list(cout);
            }

            break;
        }
        else {
            cout << "Invalid option. Please re-enter your option.\n";
        }
    }
}

// Sub-menu 10 (Save or load file)
void SubMenu10(List<ShopItem*>** itemList, List<Customer*>** customerList) {
    OptionMenu10();

    int option;
    string itemFile, customerFile;

    while ((option = get_option()) != 0) {
        // First option is for saving
        if (option == 1) {

            cout << "Enter name of item file to save: ";
            getline(cin, itemFile);
            cout << "Enter name of customer file to save: ";
            getline(cin, customerFile);

            if (!SaveFile(itemList, customerList, itemFile, customerFile)) {
                cout << "Fail to save file.\n";
            }

            break;
        }

        // Second option is for loading
        else if (option == 2) {
            cout << "Load file will override all shop items and customers data from the program. Do you want to continue?\n";
            if (GetYesNo()) {
                cout << "Enter name of item file to load: ";
                getline(cin, itemFile);
                cout << "Enter name of customer file to load: ";
                getline(cin, customerFile);

                delete (*itemList);
                delete (*customerList);

                (*itemList) = new List<ShopItem*>();
                (*customerList) = new List<Customer*>();

                // Validate and load file data
                LoadFile(itemList, itemFile);
                LoadFile(itemList, customerList, customerFile);
            }

            break;
        }

        // Return a message if user enter a non-listed option
        else {
            cout << "Invalid option\n";
        }
    }
}

int main(int argc, char* argv[])
{
    int option;
    List<ShopItem*>* itemList = new List<ShopItem*>();
    List<Customer*>* customerList = new List<Customer*>();

    // Check if the arguments have approriate format
    if (argc != 3) {
        cout << "Program requires 2 arguments/files to run. Please input item file and customer file in order.\n";
        return -1;
    }

    // Functions to load input files from the arguments
    LoadFile(&itemList, argv[1]);
    LoadFile(&itemList, &customerList, argv[2]);

    // Function to print out the main menu
    PrintMenu();

    // Loop the main menu until 'exit' is entered
    while ((option = get_option("exit")) != 0) {
        cout << endl;

        // Sub-menu 1 (Add, update or delete item)
        if (option == 1) {
            SubMenu1(&itemList, &customerList);
        }

        // Sub-menu 2 (Add or update customer)
        else if (option == 2) {
            SubMenu2(&customerList);
        }

        // Sub-menu 3 (Promote customer with ID or name)
        else if (option == 3) {
            SubMenu3(&customerList);
        }

        //Sub-menu 4 (Rent or return an item)
        else if (option == 4) {
            SubMenu4(&itemList, &customerList);
        }

        // Sub-menu 5 (Display all item sotred with ID or title in ascending or descending order)
        else if (option == 5) {
            SubMenu5(&itemList);
        }

        // Display out-of-stock items
        else if (option == 6) {
            SubMenu6(&itemList);
        }

        // Display all customers
        else if (option == 7) {
            SubMenu7(&customerList);
        }

        // Display group of customers
        else if (option == 8) {
            SubMenu8(&customerList);
        }

        // Search items or customers
        else if (option == 9) {
            SubMenu9(&itemList, &customerList);
        }

        // Save and load data files
        else if (option == 10) {
            SubMenu10(&itemList, &customerList);
        }
        else {
            cout << "Invalid option. Please re-enter your option.\n";
            continue;
        }

        cout << endl;
        PrintMenu();
    }

    // Automatically save data after exiting the program
    SaveFile(&itemList, &customerList, argv[1], argv[2]);

    delete customerList;
    delete itemList;

    // Output team information
    cout << "Program exits.\n";
    cout << "\nASSIGNMENT 2 GROUP 7\n";
    cout << "s3877969, s3877969@rmit.edu.vn, Quan, Le Minh\n";
    cout << "s3878413, s3878413@rmit.edu.vn, Nam, Pham Thanh\n";
    cout << "s3865443, s3865443@rmit.edu.vn, Duong, Nguyen Vu Thuy\n";
    cout << "s3878070, s3878070@rmit.edu.vn, Phi, Thai Manh\n";

    return 0;
}