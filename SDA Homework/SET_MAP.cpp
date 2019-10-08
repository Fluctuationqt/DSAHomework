/* 
	HOW TO USE STL HASHING, UNORDERED/ORDERED SET/MAP
	
	below are 4 classes with definitions used to explain hashing
	and 2 methods for a complex example of a map of a custom 
	object and set of a custom object.
*/

#include "stdafx.h"
#include <iostream>
#include <string>

#include <unordered_set>
#include <unordered_map>
#include <set>
#include <map>

using namespace std;

// FOR 6.
// Define a custom key object.
// 1. hasher template must be redefined in STD for use in ordered/unordered set/map (SHOWN BELOW)
// 2. operator== must be redefined for use in unordered_set, unordered_map.
//    it compares for collisions after getting an index with hashing function.
// 3. operator< is not defined here, but must be defined for use in ORDERED set/map
//    it compares objects to sort them. (Definition for it exists in class Human BELOW)
struct Key
{
	std::string first;
	std::string second;
	int         third;
	
	Key(string first, string second, int third) {
		this->first = first;
		this->second = second;
		this->third = third;
	}

	// *required for unordered_set/unordered_map
	bool operator==(const Key &other) const
	{
		return (first == other.first
			&& second == other.second
			&& third == other.third);
	}
};

// FOR 6.
// Redefine a template for a custom hash<Key> object.
// 1. operator() must be redefined to accept object and return hash
namespace std
{
	template <>
	struct hash<Key>
	{
		size_t operator()(const Key& k) const
		{
			// Compute individual hash values for first, second and third
			size_t res = 17;
			res = res * 31 + hash<string>()(k.first);
			res = res * 31 + hash<string>()(k.second);
			res = res * 31 + hash<int>()(k.third);
			return res;
		}
	};
}

// FOR 3., 6., 7., 8.
// CUSTOM CLASS HUMAN THAT IS USABLE IN UNORDERED/ORDERED SET/MAP
struct Human
{
	string name;
	int age;

	Human(string Name, int Age) {
		name = Name;
		age = Age;
	}

	void print() const {
		cout << name << ", " << age << endl;
	}

	// *required for unordered/ordered set/map
	bool operator==(const Human &other) const
	{
		return (name == other.name && age == other.age);
	}

	// *required for ordered set/map
	bool operator<(const Human &other) const
	{
		if (age == other.age) {
			// if equal age sort by name
			return name < other.name;
		}
		else {
			// if age is different sort by age
			return (age < other.age);
		}
	}
};

// FOR 7. and 8.
// CUSTOM HASHER FOR CLASS HUMAN
// *required for unordered/ordered set/map
namespace std
{
	template <>
	struct hash<Human>
	{
		size_t operator()(const Human& human) const
		{
			// Compute individual hash values for first, second and third
			size_t res = 17;
			res = res * 31 + hash<string>()(human.name);
			res = res * 31 + hash<int>()(human.age);
			return res;
		}
	};
}

// FOR 8.
// method accepts a person and his friend and a collection of persons and their friends.
// returns true if 'person' has friend 'fr'
bool hasFriend(const Human& person, const Human& fr, map<Human, set<Human>> &human_friends) {
	auto found = human_friends.find(person);
	if (found != human_friends.end()) {
		set<Human> friends = (*found).second;
		for (auto& curFr : friends) {
			if (curFr == fr)
				return true;
		}
	}
	else {
		string errMsg = "Person not found in the collection.";
		throw std::invalid_argument(errMsg);
	}

	return false;
}

// FOR 8.
// prints friendship type of h1 and h2 that are in the collection
void areFriends(const Human& h1, const Human& h2, map<Human, set<Human>>& human_friends)
{
	bool h1_to_h2 = hasFriend(h1, h2, human_friends);
	bool h2_to_h1 = hasFriend(h2, h1, human_friends);
	
	if (h1_to_h2 && h2_to_h1) {
		cout << h1.name <<" and "<< h2.name << " are both friends" << endl;
	}
	else if (h1_to_h2 && !h2_to_h1) {
		cout << h1.name << " is a friend of " << h2.name << endl;
	}
	else if (h2_to_h1 && !h1_to_h2) {
		cout << h2.name << " is a friend of " << h1.name << endl;
	}
	else {
		cout << h1.name << " and " << h2.name << " are not friends" << endl;
	}
}

/* Some useful examples */
int main()
{

/* 1. SIMPLE INTEGER UNORDERED_SET
	unordered_set<int> s;
	
	// insert
	for (int i = 0; i < 10; i++) {
		int t;
		cin >> t;
		s.insert(t);
	}

	// print
	for (auto& i : s) {
		cout << i << ", ";
	}
	cout << endl;

	// find and print rest to end example
	auto found = s.find(3);
	if (found != s.end()) {
		cout << "found 3, rest are: ";
		for (auto it = ++found; it != s.end(); it++)
			cout << *it << ", ";
		cout << endl;
	}
*/
	


/* 2. UNORDERED_MAP OF SIMPLE KEY, SIMPLE VALUE EXAMPLE
	//            key,  value
	unordered_map<string, int> name_age;
	
	// insertion methods
	pair<string, int> niki("niki", 14);
	name_age.insert(niki);
	name_age.insert(make_pair<string, int>("vladi", 14));
	name_age.insert({ "pesho", 12 });
	name_age.insert({ {"niki", 13},{"pesho", 12},{"gogo", 3} });
	name_age["gosho"] = 13;

	// niki, 14
	// vladi, 14
	// pesho, 12
	// niki, 13 (does not insert)
	// pesho, 12 (does not insert)
	// gogo, 3
	// gosho, 13
	
	// modify niki to 3
	name_age["niki"] = 3;

	// print all
	for (auto& person : name_age) {
		cout << person.first << "," << person.second << endl;
	}
*/



/* 3. UNORDERED_MAP OF SIMPLE KEY COMPLEX VALUE EXAMPLE
	unordered_map < string, list<Human> > name_friends;

	// insert name and lists of Human friends
	name_friends.insert({ "vladi", list<Human>() });

	list<Human> ivoFriends;
	ivoFriends.push_back(Human(40, "Emo"));
	ivoFriends.push_back(Human(30, "kremi"));
	ivoFriends.push_back(Human(75, "geri"));
	name_friends.insert({ "ivo", ivoFriends });

	list<Human> kremiFriends;
	kremiFriends.push_back(Human(22, "ivo"));
	kremiFriends.push_back(Human(30, "kremi"));
	kremiFriends.push_back(Human(75, "geri"));
	name_friends.insert({ "kremi", kremiFriends });

	// print person's name and his friends
	for (auto& p : name_friends) {
		string currentName = p.first;
		list<Human> friends = p.second;

		cout << currentName << "'s friends are: " << endl;

		for (auto& fr : friends) {
			cout << fr.name << ", " << fr.age << endl;
		}
		cout << endl;
	}
*/
	


/* 4. MAP OF SIMPLE STRING KEY AND SIMPLE STRING VALUE
	map<string, string> product_id;
	product_id.insert({ "Banana", "hadhwew31" });
	product_id.insert({ "Tomato", "hassdwe1" });
	product_id.insert({ "Banana", "s" }); // did not
	product_id.insert({ "Orange", "a" });
	product_id.insert({ "Monkey", "q2" });
	product_id.insert({ "Banana", "a" }); // did not
	product_id.insert({ "Tomato", "hassdwe1" }); // did not
	product_id.insert({ "Tomato", "hassdwe1" }); // did not
	// They are without duplicates and sorted by key in alphabetical order

	// print
	for (auto& column : product_id) {
		string key = column.first;
		string value = column.second;
		cout << key << "'s id is: " << value << endl;
	}
	cout << endl;

	// modifying
	cout << "setting 'Banana' value to 'a'" << endl;
	product_id["Banana"] = "a";

	// print
	for (auto& column : product_id) {
		string key = column.first;
		string value = column.second;
		cout << key << "'s id is: " << value << endl;
	}
	cout << endl;

	// searching by key (1) - with .find() - faster
	cout << "searching by key 'Banana'" << endl;
	auto found = product_id.find("Banana");
	if (found != product_id.end()) {
		cout << (*found).second << endl;
	}
	cout << endl;

	// searching by key (2) - slower
	cout << "searching by key 'Banana'" << endl;
	for (auto& column : product_id) {
		string key = column.first;
		string value = column.second;
		if (key == "Banana")
			cout << value << endl;
	}
	cout << endl;

	// searching by value - only way
	cout << "searching by value 'a'" << endl;
	for (auto& column : product_id) {
		string key = column.first;
		string value = column.second;
		if (value == "a")
			cout << key << endl;
	}
*/



/* 5. MAP OF SIMPLE DOUBLE KEY, SIMPLE STRING VALUE
	map<double, string> price_product;
	price_product.insert({ 13.50, "Banana" });
	price_product.insert({ 21.13, "Dick" });
	price_product.insert({ 21.13, "Dickov" });
	price_product.insert({ 21.14, "Dick" });
	price_product.insert({ 0.30, "Treva" });
	price_product.insert({ 1, "Rob" });

	// print
	for (auto& column : price_product) {
		double key = column.first;
		string value = column.second;
		cout << key << ", "<< value << endl;
	}
*/
	

		
/*  6.  HOW STL HASHING WORKS
	 
	std::hash<string> h = std::hash<string>();
	cout << "hash of kremi is:"<< h("kremi") << endl;
	cout << "hash of kremi is:" << h("kremi") << endl;
	cout << "hash of ivo is:" << h("ivo") << endl;

	hash<Key> keyhash = hash<Key>();
	Key ivan("Ivan", "Mihailov", 22);
	cout << "hash of key ivan is: " << keyhash(ivan) <<endl;
	cout << "hash of key ivan is: " << keyhash(ivan) << endl;

	cout << "The hash of Human kremi is:" << hash<Human>()(Human("Kremi", 22)) << endl << endl;
*/



/*  7. HOW TO CREATE A CUSTOM HASH FOR AN OBJECT AND MAKE A SET OF OBJECT

	unordered_set<Human> humans;
	humans.insert(Human("Kremi", 22));
	humans.insert(Human("Niki", 12));
	humans.insert(Human("Emo", 40));
	humans.insert(Human("Niki", 24));
	for (auto& human : humans) {
		human.print();
	}
	cout << endl;

	set<Human> humans2;
	humans2.insert(Human("Kremi", 22));
	humans2.insert(Human("Niki", 12));
	humans2.insert(Human("Emo", 40));
	humans2.insert(Human("Niki", 24));
	for (auto& human : humans2) {
		human.print();
	}

*/



/*  8. CREATE MAP OF [CUSTOM OBJECT] AND [SET OF CUSTOM OBJECTS]

	Human ivan("Ivan", 22);
	Human vladi("Vladi", 22);
	Human kremi("Kremi", 20);
	Human niki("Niki", 10);
	Human nati("Natali", 23);
	
	set<Human> ivanFriends;
	set<Human> vladiFriends;
	set<Human> kremiFriends;
	set<Human> nikiFriends;
	set<Human> natiFriends;
	
	ivanFriends.insert(vladi);
	vladiFriends.insert(ivan);
	vladiFriends.insert(kremi);
	kremiFriends.insert(vladi);
	natiFriends.insert(ivan);
	kremiFriends.insert(nati);
	
	map<Human, set<Human>> human_friends;
	human_friends.insert({ ivan, ivanFriends });
	human_friends.insert({ vladi, vladiFriends });
	human_friends.insert({ kremi, kremiFriends });
	human_friends.insert({ niki, nikiFriends });
	human_friends.insert({ nati, natiFriends });
	
	// print
	for (auto& p : human_friends) {
		Human currentPerson = p.first;
		set<Human> currentPersonFriends = p.second;
		currentPerson.print();
		for (auto& fr : currentPersonFriends) {
			cout << " +";
			fr.print();
		}
		cout << endl;
	}
	
	// print all relations
	areFriends(ivan, nati, human_friends);
	areFriends(kremi, vladi, human_friends);
	areFriends(niki, nati, human_friends);
	for (auto& p1 : human_friends) {
		for (auto& p2 : human_friends) {
			if (!(p1 == p2))
				areFriends(p1.first, p2.first, human_friends);
		}
	}
*/



    return 0;
}