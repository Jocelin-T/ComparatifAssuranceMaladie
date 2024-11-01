#include "UserInteraction.hpp"

namespace user {

	uint16_t getUserChoice(uint16_t N) {

		std::string input{ "" };
		uint16_t user_choice{ 0 };

		std::cin >> input;

		if (!glb::isStringNumeric(input)) {
			system("cls");
			std::cout << "Your entry isn't numeric\n\n";
			return 0;
		}

		user_choice = std::stoi(input);

		if (user_choice > N) {
			system("cls");
			std::cout << "Option choosed doesn't exist\n\n";
			return 0;
		}

		return user_choice;
	}

	float askUserMaximumFee(const float min_bonus) {
		
		std::string input{ "" };
		float user_max_fee{ 0 };

		while (user_max_fee <= 0) {

			std::cout << "Enter the maximum fee you want to pay per year: (min: " << min_bonus * 12 << ")\n";
			std::cin >> input;


			if (!glb::isStringNumeric(input)) {
				system("cls");
				std::cout << "Your entry isn't numeric\n\n";
				continue;
			}

			user_max_fee = std::stof(input);

			if (user_max_fee < min_bonus * 12) {
				system("cls");
				std::cout << "Your entry is too low (min: " << min_bonus * 12 << ")\n\n";
				user_max_fee = 0;
			}
		}

		return user_max_fee;
	}

	uint16_t askUserRegion(void) {
		return 0;
	}

	uint16_t askUserAge(void) {
		return 0;
	}

} // namespace user
