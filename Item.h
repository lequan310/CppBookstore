#pragma once
#include <iostream>
#include <string>

using namespace std;

enum Type { RECORD, DVDDISK, GAME };
enum Loan { TWODAY, ONEWEEK };
enum Genre { ACTION, HORROR, DRAMA, COMEDY, NONE };

// Class declaration
class Item {
protected:
	string id;
	string title;
public:
	// Constructor and Destructor
	Item();
	Item(string _id, string _title);
	~Item();

	// Getters
	string get_id();
	string get_title();

	// Setters
	void set_id(string _id);
	void set_title(string _title);

	bool operator==(const Item& item);
	bool operator!=(const Item& item);
	friend ostream& operator<<(ostream& stream, const Item& item);
};

// ShopItem inherits from Item
class ShopItem : public Item {
protected:
	int copies; // Number of copies
	int stock; // Number of copies available for borrow
	Loan loan;
	double fee;
	bool available;
public:
	ShopItem();
	ShopItem(string _id, string _title, Loan _loan, int _copies, double _fee);

	// Getters
	Loan get_loan();
	int get_copies();
	int get_stock();
	double get_fee();
	bool get_available();
	virtual Genre get_genre() { return NONE; }

	// Setters
	void set_loan(Loan _loan);
	void set_copies(int _copies);
	void set_stock(int _stock);
	void set_fee(double _fee);
	void set_available(bool _available);
	virtual void set_genre(Genre _genre) {}

	virtual bool isRecord() { return false; }
	virtual bool isDVD() { return false; }

	void borrowed();
	void returned();

	virtual string toString();
};

// Record, DVD, Game inherits from ShopItem
class Record : public ShopItem {
private:
	Genre genre;
public:
	Record();
	Record(ShopItem* item);
	Record(string _id, string _title, Loan _loan, int _copies, double _fee, Genre _genre);

	virtual Genre get_genre();
	virtual void set_genre(Genre _genre);

	virtual bool isRecord();
	virtual bool isDVD();

	virtual string toString();
};

class DVD : public ShopItem {
private:
	Genre genre;
public:
	DVD();
	DVD(ShopItem* item);
	DVD(string _id, string _title, Loan _loan, int _copies, double _fee, Genre _genre);

	virtual Genre get_genre();
	virtual void set_genre(Genre _genre);

	virtual bool isRecord();
	virtual bool isDVD();

	virtual string toString();
};

class Game : public ShopItem {
public:
	Game();
	Game(ShopItem* item);
	Game(string _id, string _title, Loan _loan, int _copies, double _fee);

	virtual bool isRecord();
	virtual bool isDVD();
	virtual Genre get_genre() { return NONE; }
};

// Declaration for conversion functions between string and object
bool str2type(const string& s, Type* type);
bool str2loan(const string& s, Loan* loan);
bool str2genre(const string& s, Genre* genre);
string type2str(Type type);
string loan2str(Loan loan);
string genre2str(Genre genre);