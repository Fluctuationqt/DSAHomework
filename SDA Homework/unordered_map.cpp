#include "stdafx.h"
#include <iostream>
#include <string>
#include <unordered_map>

int main()
{
	// Create an unordered_map of three strings (that map to strings)
	std::unordered_map<std::string, std::string> u = {
		{ "RED","#FF0000" },
		{ "GREEN","#00FF00" },
		{ "BLUE","#0000FF" }
	};

	// Iterate and print keys and values of unordered_map
	for (const auto& n : u) {
		std::cout << "Key:[" << n.first << "] Value:[" << n.second << "]\n";
	}

	// Add two new entries to the unordered_map
	u["BLACK"] = "#000000";
	u["WHITE"] = "#FFFFFF";
	u.insert(std::pair<std::string, std::string>("PURPLE", "#5500FF"));
	u.insert(std::pair<std::string, std::string>("PURPLE", "#550055")); // duplicates are not stored!
	// Output values by key
	std::cout << "The HEX of color RED is:[" << u["RED"] << "]\n";
	std::cout << "The HEX of color BLACK is:[" << u["BLACK"] << "]\n";
	std::cout << "The HEX of color PURPLE is:[" << u["PURPLE"] << "]\n";

	// find by key
	auto found = u.find("PURPLE");
	if (found == u.end()) {
		std::cout << "could not find" << std::endl;
	}
	else {
		std::cout << "found:" << found->first << ", " << found->second << std::endl;
	}

	// print everything
	std::cout << std::endl;
	for (auto& it : u) {
		std::cout << it.first << ", " << it.second << std::endl;
	}
	std::cout << u.size() << std::endl;
	return 0;
}