#include "Globals.hpp"
#include <cctype>

namespace global {

	bool isStringNumeric(const std::string& str) {

        bool is_negative{ false };

        for (uint16_t i{ 0 }; i < str.length(); i++) {
            if (!std::isdigit(str[i]) && str[i] != '.') { // Allow digits and a decimal point

                if (str[0] == '-' && !is_negative) {
                    is_negative = true;
                    continue;
                }
                return false;
            }
        }
        return true;
	}
}
