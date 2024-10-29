#pragma once

#include <string>
#include <iostream>


#include "Typedef.hpp"
#include "Globals.hpp"
#include "Config.hpp"

namespace user {

	uint16_t getUserChoice(uint16_t N);


	// Template need to be in the header
	template <uint16_t N> // N => size of the array passed 
	uint16_t listUserChoices(const std::string(&array_of_choices)[N]) {

		std::cout << "Choose an option:\n";

		for (uint16_t i = 0; i < N; ++i) {
			std::cout << i + 1 << " - " << array_of_choices[i] << '\n';
		}

		return getUserChoice(N);
	}

	// Arrays need to be in the header because of the Template
	inline std::string choices_main_menu[]{
		"Enter data for Algorithm",
		"Display Database",
		"Create Database and insert CSV to Database",
		"Change DEBUG mode",
		"Stop program"
	};

	inline std::string choices_algorithm[]{
		"",
		""
	};

}; // namespace user

