#pragma once

#include <string>
#include <iostream>
#include <vector>

#include "Typedef.hpp"
#include "Globals.hpp"
#include "Config.hpp"

namespace user {

	float askUserMaximumFee(void);

	uint16_t askUserRegion(const std::vector<uint16_t>& array_regions);

	uint16_t askUserAge(const uint16_t min_age);

	bool askUserAccident(void);


	uint16_t getUserChoice(uint16_t array_size);

	// Template need to be in the header and order matter
	template <uint16_t N> // N => size of the array passed 
	uint16_t listUserChoices(const std::string(&array_of_choices)[N]) {

		std::cout << "Choose an option:\n";

		for (uint16_t i = 0; i < N; ++i) {
			std::cout << i + 1 << " - " << array_of_choices[i] << '\n';
		}
		std::cout << "0 - Return\n";

		return getUserChoice(N);
	}

	// Arrays need to be in the header because of the Template
	inline std::string choices_main_menu[]{
		"Enter data for Algorithm",
		"Display Database",
		"Create Database and insert CSV to Database",
		"DEBUG",
		"Stop program"
	};

	inline std::string choices_algorithm[]{
		"Start Algorithm",
		"DEBUG Algorithm"
	};

}; // namespace user

