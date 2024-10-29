#pragma once

#include <string>
#include <span>

#include "Typedef.hpp"
#include "Globals.hpp"
#include "Config.hpp"

namespace user {

	//void listUserChoices(const std::string* array_of_choices, uint16_t size);

    template <size_t N>
    void listUserChoices(const std::string(&array_of_choices)[N]) {
        std::cout << "In List User Choices\n";
        for (size_t i = 0; i < N; ++i) {
            std::cout << i + 1 << " - " << array_of_choices[i] << '\n';
        }
    }

	uint16_t getUserChoice(); // TODO

	std::string choices_main_menu[];

}; // namespace user

