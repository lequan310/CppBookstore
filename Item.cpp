#include <iostream>
#include <string>
#include <sstream>
#include "Item.h"

using namespace std;

// Constructors for base class Item and ShopItem
Item::Item() {}
Item::Item(string _id, string _title) {
	this->id = _id;
	this->title = _title;
}
Item::~Item() {}

ShopItem::ShopItem() {}
ShopItem::ShopItem(string _id, string _title, Loan _loan, int _copies, double _fee)
	: Item(_id, _title) {
	this->loan = _loan;
	this->copies = _copies;
	this->stock = _copies;
	this->fee = _fee;
	this->available = (stock > 0) ? true : false;
}

// Definition for setters
void Item::set_id(string _id) { this->id = _id; }
void Item::set_title(string _title) { this->title = _title; }
void ShopItem::set_loan(Loan _loan) { this->loan = _loan; }
void ShopItem::set_copies(int _copies) { this->copies = _copies; }
void ShopItem::set_stock(int _stock) { this->stock = _stock; }
void ShopItem::set_fee(double _fee) { this->fee = _fee; }
void ShopItem::set_available(bool _available) { this->available = _available; }
void Record::set_genre(Genre _genre) { this->genre = _genre; }
void DVD::set_genre(Genre _genre) { this->genre = _genre; }

// Definition for getters
string Item::get_id() { return this->id; }
string Item::get_title() { return this->title; }
Loan ShopItem::get_loan() { return this->loan; }
int ShopItem::get_copies() { return this->copies; }
int ShopItem::get_stock() { return this->stock; }
double ShopItem::get_fee() { return this->fee; }
bool ShopItem::get_available() { return this->available; }
Genre Record::get_genre() { return this->genre; }
Genre DVD::get_genre() { return this->genre; }

// Virtual function to identify whether the item is DVD or Record. If neither of them are true then it's Game
bool Record::isDVD() { return false; }
bool Record::isRecord() { return true; }
bool DVD::isDVD() { return true; }
bool DVD::isRecord() { return false; }
bool Game::isDVD() { return false; }
bool Game::isRecord() { return false; }

// Decrease stock when borrowed
void ShopItem::borrowed() {
	this->stock -= 1;
}

// Increase stock when borrowed
void ShopItem::returned() {
	this->stock += 1;
}

// Operator overloading to compare between 2 items
bool Item::operator==(const Item& item) {
	if (this->id.compare(item.id) != 0) return false;
	if (this->title.compare(item.title) != 0) return false;

	return true;
}

bool Item::operator!=(const Item& item) {
	if (this->id.compare(item.id) != 0) return true;
	if (this->title.compare(item.title) != 0) return true;

	return false;
}

// Operator overloading to output item
ostream& operator<<(ostream& stream, const Item& item) {
	stream << item.id << ", ";
	stream << item.title;

	return stream;
}

// Converting item (Record, DVD, and Game) to string
string ShopItem::toString() {
	string s = "", _fee;
	stringstream ss(_fee);

	ss << this->fee;
	ss >> _fee;

	s.append(this->id + ",");
	s.append(this->title + ",");
	s.append("Game,");
	s.append(loan2str(this->loan) + ",");
	s.append(to_string(this->copies) + ",");
	s.append(_fee);

	return s;
}

string Record::toString() {
	string s = "", _fee;
	stringstream ss(_fee);

	ss << this->fee;
	ss >> _fee;

	s.append(this->id + ",");
	s.append(this->title + ",");
	s.append("Record,");
	s.append(loan2str(this->loan) + ",");
	s.append(to_string(this->copies) + ",");
	s.append(_fee + ",");
	s.append(genre2str(this->genre));

	return s;
}

string DVD::toString() {
	string s = "", _fee;
	stringstream ss(_fee);

	ss << this->fee;
	ss >> _fee;

	s.append(this->id + ",");
	s.append(this->title + ",");
	s.append("DVD,");
	s.append(loan2str(this->loan) + ",");
	s.append(to_string(this->copies) + ",");
	s.append(_fee + ",");
	s.append(genre2str(this->genre));

	return s;
}

// Constructor for derived class: Record, DVD and Game
Record::Record() {}

Record::Record(ShopItem* item) {
	this->id = item->get_id();
	this->title = item->get_title();
	this->copies = item->get_copies();
	this->stock = item->get_stock();
	this->loan = item->get_loan();
	this->fee = item->get_fee();
	this->available = item->get_available();
	this->genre = item->get_genre();
}

Record::Record(string _id, string _title, Loan _loan, int _stock, double _fee, Genre _genre)
	: ShopItem(_id, _title, _loan, _stock, _fee) {
	this->genre = _genre;
}

DVD::DVD() {}

DVD::DVD(ShopItem* item) {
	this->id = item->get_id();
	this->title = item->get_title();
	this->copies = item->get_copies();
	this->stock = item->get_stock();
	this->loan = item->get_loan();
	this->fee = item->get_fee();
	this->available = item->get_available();
	this->genre = item->get_genre();
}

DVD::DVD(string _id, string _title, Loan _loan, int _stock, double _fee, Genre _genre)
	: ShopItem(_id, _title, _loan, _stock, _fee) {
	this->genre = _genre;
}

Game::Game() {}

Game::Game(ShopItem* item) {
	this->id = item->get_id();
	this->title = item->get_title();
	this->copies = item->get_copies();
	this->stock = item->get_stock();
	this->loan = item->get_loan();
	this->fee = item->get_fee();
	this->available = item->get_available();
}

Game::Game(string _id, string _title, Loan _loan, int _stock, double _fee)
	: ShopItem(_id, _title, _loan, _stock, _fee) {}

// Converting between (item type and string), (loan type and string), (genre and string)
bool str2type(const string& s, Type* type) {
	if (s.compare("record") == 0) {
		*type = RECORD;
		return true;
	}
	else if (s.compare("dvd") == 0) {
		*type = DVDDISK;
		return true;
	}
	else if (s.compare("game") == 0) {
		*type = GAME;
		return true;
	}
	else {
		return false;
	}
}

bool str2loan(const string& s, Loan* loan) {
	if (s.compare("1-week") == 0) {
		*loan = ONEWEEK;
		return true;
	}
	else if (s.compare("2-day") == 0) {
		*loan = TWODAY;
		return true;
	}
	else {
		return false;
	}
}

bool str2genre(const string& s, Genre* genre) {
	if (s.compare("action") == 0) {
		*genre = ACTION;
		return true;
	}
	else if (s.compare("horror") == 0) {
		*genre = HORROR;
		return true;
	}
	else if (s.compare("drama") == 0) {
		*genre = DRAMA;
		return true;
	}
	else if (s.compare("comedy") == 0) {
		*genre = COMEDY;
		return true;
	}
	else {
		return false;
	}
}

string type2str(Type type) {
	if (type == RECORD) return "Record";
	else if (type == DVDDISK) return "DVD";
	else if (type == GAME) return "Game";
	else return "";
}

string loan2str(Loan loan) {
	if (loan == TWODAY) return "2-day";
	else if (loan == ONEWEEK) return "1-week";
	else return "";
}

string genre2str(Genre genre) {
	if (genre == ACTION) return "Action";
	else if (genre == HORROR) return "Horror";
	else if (genre == DRAMA) return "Drama";
	else if (genre == COMEDY) return "Comedy";
	else return "";
}