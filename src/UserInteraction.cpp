#include "UserInteraction.hpp"

#include <iostream>

namespace user {

	// TODO: Display Database
	// TODO: Add CSV to Database
	// TODO: DEBUG mode on/off
	// TODO: 

	void listUserChoices(const std::string* array_of_choices, uint16_t size) {

		std::cout << "In List User Choices\n"; // DEBUG

		for (uint16_t i{ 0 }; i < size; ++i) {
			std::cout << i + 1 << " - " << array_of_choices[i] << '\n';
		}
	}

	std::string choices_main_menu[]{
		"Display Database",
		"Add CSV to Database",
		"Change DEBUG mode"
	};

} // namespace user
