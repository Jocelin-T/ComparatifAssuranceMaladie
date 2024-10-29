#include "UserInteraction.hpp"

#include <iostream>

namespace user {

	uint16_t getUserChoice(uint16_t N) {

		uint16_t user_choice{ 0 };

		std::cin >> user_choice;
		
		if (std::cin.fail()) {
			system("cls");
			std::cout << "Option choosed isn't numeric\n\n";
			std::cin.clear();
			std::cin.ignore(256, '\n');
			return 0;
		}

		if (user_choice > N) {
			system("cls");
			std::cout << "Option choosed doesn't exist\n\n";
			return 0;
		}

		return user_choice;

	}

} // namespace user
