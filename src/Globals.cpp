#include "Globals.hpp"
#include <cctype>


namespace global::function {

	bool isStringNumeric(const std::string& str) {

        bool is_negative{ false };
        bool is_float{ false };

        for (uint16_t i{ 0 }; i < str.length(); i++) {

            if (!std::isdigit(str[i])) {

                if (str[i] == '.' && i != 0 && !is_float) {
                    is_float = true;
                    continue;
                }

                if (str[0] == '-' && !is_negative) {
                    is_negative = true;
                    continue;
                }
                return false;
            }
        }
        return true;
	}

} // namespace global::function

