#include "UserInteraction.hpp"

namespace user {

	uint16_t getUserChoice(uint16_t array_size) {

		std::string input{ "" };
		uint16_t user_choice{ 0 };

		std::cin >> input;

		if (!global::function::isStringNumeric(input)) {
			system("cls");
			std::cout << "Your entry isn't numeric\n\n";
			return 0;
		}

		user_choice = std::stoi(input);

		if (user_choice > array_size) {
			system("cls");
			std::cout << "Option choosed doesn't exist\n\n";
			return 0;
		}

		return user_choice;
	}


	float askUserMaximumFee(void) {

		system("cls");
		std::string input{ "" };
		float user_max_fee{ -99 };

		while (user_max_fee < 0) {

			std::cout << "Enter the maximum fee (without bonus) you think you gonna pay this year: ";
			std::cin >> input;

			if (!global::function::isStringNumeric(input)) {
				system("cls");
				std::cout << "Your entry isn't numeric\n\n";
				continue;
			}

			user_max_fee = std::stof(input);

			if (user_max_fee < 0) {
				system("cls");
				std::cout << "Your entry too low\n\n";
				continue;
			}
		}

		return user_max_fee;
	}


	uint16_t askUserRegion(const std::vector<uint16_t>& array_regions) {

		system("cls");
		std::string input{ "" };
		int16_t user_region{ -99 };

		while (user_region <= 0) {

			std::cout << "Choose one of the region available:\n";
			for (const uint16_t region : array_regions) {
				std::cout << " - " << region << '\n';
			}
			std::cin >> input;

			if (!global::function::isStringNumeric(input)) {
				system("cls");
				std::cout << "Your entry isn't numeric\n\n";
				continue;
			}

			user_region = std::stof(input);

			for (const uint16_t region : array_regions) {

				// Entry exist
				if (user_region == region) {
					return user_region;
				}
			}

			system("cls");
			std::cout << "Your entry isn't available \n\n";
			user_region = -99;
		}
	}


	uint16_t askUserAge(const uint16_t min_age) {

		system("cls");
		std::string input{ "" };
		int16_t user_age{ -99 };

		while (user_age < min_age) {

			std::cout << "Enter your age (min: " << min_age << "): ";
			std::cin >> input;

			if (!global::function::isStringNumeric(input)) {
				system("cls");
				std::cout << "Your entry isn't numeric\n\n";
				continue;
			}

			user_age = std::stof(input);

			if (user_age < min_age) {
				system("cls");
				std::cout << "Your entry is under the minimal age possible\n\n";
				user_age = -99;
				continue;
			}

			return user_age;
		}
	}


	bool askUserAccident(void) {

		system("cls");
		std::string input{ "" };
		bool user_accident{ false };

		while (true) {

			std::cout << "Do you want with the accident insurance (Y/N): ";
			std::cin >> input;

			if (input == "n"
				|| input == "N") {

				return false;
			}

			if (input == "y"
				|| input == "Y") {

				return true;
			}

			std::cout << "Your entry isn't Y or N\n\n";
		}
	}

} // namespace user
