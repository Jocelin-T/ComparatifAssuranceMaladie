#include "Algorithm.hpp"
#include <iostream>

// Potential annual fee = 2300 CHF
// without bonus, only 

namespace algo {

	void runAlgorithm(const AlgorithmParameters& params) {
		
		for (uint16_t i{ 0 }; i < ALGO_MAX_ENTRIES; i++) {

			std::cout << i << " ID: " << insurances_id[i] << " data: " << bonuses[i] << '\n';
		}
	}


	AlgorithmParameters& setAlgorithmParameters(const float user_max_fee, const uint16_t user_region, const uint16_t user_age, const bool user_accident) {
		
		AlgorithmParameters params;

		params.user_choosed_maximum_fee = user_max_fee;
		params.user_choosed_region = user_region;
		params.user_choosed_age = user_age;
		params.user_choosed_accident = user_accident;

		return params;
	}


	void algorithmTest(void) {

	}

} // namespace algo
