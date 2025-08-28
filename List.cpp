#include <iostream>
#include <string>
#include "List.h"
#include "Item.h"
#include "Customer.h"

using namespace std;

// Constructor and Destructor for class node
template <class T>
node<T>::node<T>() { this->next = NULL; }

template <class T>
node<T>::~node<T>() { this->next = NULL; }

node<ShopItem*>::~node<ShopItem*>() {
	delete this->object;
	this->next = NULL;
}

node<Customer*>::~node<Customer*>() {
	delete this->object;
	this->next = NULL;
}

// Getters and Setters for class node
template <class T>
T node<T>::get_object() {
	return this->object;
}

template <class T>
void node<T>::set_object(const T& obj) {
	this->object = obj;
}

template <class T>
node<T>* node<T>::get_next() {
	return this->next;
}

template <class T>
void node<T>::set_next(node<T>* node) {
	this->next = node;
}

// Constructor and Destructor for class List
template <class T>
List<T>::List() {
	head = NULL;
	size = 0;
}

template <class T>
List<T>::~List() {
	auto current = head;
	node<T>* tempNode;

	while (current != NULL) {
		tempNode = current;
		current = current->get_next();
		delete tempNode;
	}
}

// Getters and Setters for class List
template <class T>
void List<T>::set_head(node<T>* _head) { this->head = _head; }

template <class T>
node<T>* List<T>::get_head() { return this->head; }

template <class T>
int List<T>::get_size() { return this->size; }

// List Functions
template <class T>
void List<T>::add(const T& obj) {
	// Add node at the beginning so it will be faster
	node<T>* n = new node<T>();

	n->set_object(obj); // Assign node to contain obj
	n->set_next(this->get_head()); // Set the next node pointer to be the current head
	this->set_head(n); // Set the current head pointer to the newly created node n
	this->size++; // Increment list size
}

template <class T>
void List<T>::remove(const T& obj) {
	// Function to remove the first ocurrence node with object to be deleted
	node<T>* deleted = NULL; // node to be deleted
	node<T>* prev = head; // previous node before current node
	auto current = head; // current node for looping

	// Check whether the current node stores the object to be deleted
	while (current != NULL && current->get_object() != obj) {
		prev = current;
		current = current->get_next();
	}

	// If the node stores the object to be deleted is not found
	if (current == NULL) {
		cout << "Data is not in the list.\n";
		delete deleted;
	}
	// Else if the node stores the object to be deleted is found
	else {
		deleted = current; // Set the node to be deleted as deleted
		current = current->get_next(); // Link the previous node with the node after the deleted node
		prev->set_next(current);

		// If deleted node is head, move head to the next node
		if (deleted == head) {
			head = head->get_next();
			prev = NULL;
		}

		delete deleted; // Delete the node with object to be deleted
	}

	this->size--; // Decrement list size
}

// Functions to output content of lists
template <class T>
void List<T>::print_list() {
	auto current = head;

	while (current != NULL) {
		cout << current->get_object() << endl;
		current = current->get_next();
	}
}

void List<ShopItem*>::print_list() {
	auto current = head;

	while (current != NULL) {
		cout << current->get_object()->toString() << " - (Current stock: " << to_string(current->get_object()->get_stock()) << ")\n";
		current = current->get_next();
	}
}

void List<Customer*>::print_list() {
	auto current = head;

	while (current != NULL) {
		cout << current->get_object()->toString() << endl;
		current = current->get_next();
	}
}

template <class T>
void List<T>::print_list(ostream& stream) {
	auto current = head;

	while (current != NULL) {
		stream << current->get_object() << endl;
		current = current->get_next();
	}
}

void List<ShopItem*>::print_list(ostream& stream) {
	auto current = head;

	while (current != NULL) {
		stream << current->get_object()->toString() << endl;
		current = current->get_next();
	}
}

void List<Customer*>::print_list(ostream& stream) {
	auto current = head;

	while (current != NULL) {
		stream << current->get_object()->toString() << endl;
		current = current->get_next();
	}
}

// Create definition for List<ShopItem*> and List<Customer*> for use in main function
template class List<ShopItem*>;
template class List<Customer*>;