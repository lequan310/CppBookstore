#include <iostream>

using namespace std;
// Display main option
void PrintMenu() {
    cout << "---------------------------------------------------------\n";
    cout << "Welcome to Genie's video store\n";
    cout << "Enter an option below.\n";
    cout << "1. Add a new item, update or delete an existing item\n";
    cout << "2. Add new customer or update an existing customer\n";
    cout << "3. Promote an existing customer\n";
    cout << "4. Rent or return an item\n";
    cout << "5. Display all items\n";
    cout << "6. Display out-of-stock items\n";
    cout << "7. Display all customers\n";
    cout << "8. Display group of customers\n";
    cout << "9. Search items or customers\n";
    cout << "10. Save or load file\n";
    cout << "Type Exit to exit the program.\n";
}

// Sub-menu 1 (Add, update or delete item)
void OptionMenu1() {
    cout << "---------------------------------------------------------\n";
    cout << "1. Add a new item\n";
    cout << "2. Update an existing item\n";
    cout << "3. Delete an existing item\n";
    cout << "0. Back\n";
}

// Sub-menu 2 (Add or update customer)
void OptionMenu2() {
    cout << "---------------------------------------------------------\n";
    cout << "1. Add a new customer\n";
    cout << "2. Update an existing customer\n";
    cout << "0. Back\n";
}

// Sub-menu 3 (Promote customer with ID or name)
void OptionMenu3() {
    cout << "---------------------------------------------------------\n";
    cout << "1. Promote customer with ID\n";
    cout << "2. Promote customer with name\n";
    cout << "0. Back\n";
}

//Sub-menu 4 (Rent or return an item)
void OptionMenu4() {
    cout << "1. Rent an item\n";
    cout << "2. Return an item\n";
    cout << "0. Back\n";
}

// Sub-menu 5 (Display all item sotred with ID or title in ascending or descending order)
void OptionMenu5() {
    cout << "---------------------------------------------------------\n";
    cout << "1. Display all item sorted by ID (Ascending)\n";
    cout << "2. Display all item sorted by ID (Descending)\n";
    cout << "3. Display all item sorted by title (Ascending)\n";
    cout << "4. Display all item sorted by title (Descending)\n";
    cout << "0. Back\n";
}

// Sub-menu for finding item with ID or title
void FindItemOutput() {
    cout << "1. Find item with ID\n";
    cout << "2. Find item with title\n";
    cout << "0. Back\n";
}

// Sub-menu for finding customer by ID or name
void FindCustomerOutput() {
    cout << "1. Find customer with ID\n";
    cout << "2. Find customer with name\n";
    cout << "0. Back\n";
}

// Sub-menu 7 (Display customer sotred by ID or name in ascending or descending order)
void OptionMenu7() {
    cout << "---------------------------------------------------------\n";
    cout << "1. Display all customer sorted by ID (Ascending)\n";
    cout << "2. Display all customer sorted by ID (Descending)\n";
    cout << "3. Display all customer sorted by name (Ascending)\n";
    cout << "4. Display all customer sorted by name (Descending)\n";
    cout << "0. Back\n";
}

// Sub-menu 8 (Display guest, regular or VIP customer)
void OptionMenu8() {
    cout << "---------------------------------------------------------\n";
    cout << "1. Display all Guest customer\n";
    cout << "2. Display all Regular customer\n";
    cout << "3. Display all VIP customer\n";
    cout << "0. Back\n";
}

// Sub-menu 9 (Searching for item or customer by  ID or name)
void OptionMenu9() {
    cout << "---------------------------------------------------------\n";
    cout << "1. Search for an item by ID\n";
    cout << "2. Search for an item by name\n";
    cout << "3. Search for a customer by ID\n";
    cout << "4. Search for a customer by name\n";
    cout << "0. Back\n";
}

// Sub-menu 10 (Save or load file)
void OptionMenu10() {
    cout << "---------------------------------------------------------\n";
    cout << "1. Save file\n";
    cout << "2. Load file\n";
    cout << "0. Back\n";
}