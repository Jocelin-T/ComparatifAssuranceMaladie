#include "Algorithm.hpp"
#include "Config.hpp"
#include "HealthInsurance.hpp"

#include <iostream>

// Potential annual fee = 2300 CHF
// without bonus, only 

namespace logic {
	class HealthInsurance;
}

namespace algo {

	void runAlgorithm(const AlgorithmParameters& params) {
		
#if DEBUG
		for (uint16_t i{ 0 }; i < ALGO_MAX_ENTRIES; i++) {

			if (insurances_ids_matching[i] == 0) {
				continue;
			}

			std::cout << i << " - ID: " << insurances_ids_matching[i] 
				<< " Data: " << bonuses_matching[i] 
				<< " Deductible: " << deductibles_matching[i]
				<< '\n';
		}
#endif // DEBUG

		if (params.user_choosed_max_fee > 0) {

			for (uint16_t i{ 0 }; i < global::NBR_DEDUCTIBLES_PER_INSURANCE; i++) {

				float fee{ params.user_choosed_max_fee };

				fee - global::DEDUCTIBLES_POSSIBLE[i];

				if (fee <= 0) {
					break;
				}

				fee - 700.0f;

				if (fee <= 0) {
					break;
				}


			}
		}

		calculateAllCosts();
	}


	AlgorithmParameters& setAlgorithmParameters(const float user_max_fee, const uint16_t user_region, const uint16_t user_age, const bool user_accident) {
		
		AlgorithmParameters params;

		params.user_choosed_max_fee = user_max_fee;
		params.user_choosed_region = user_region;
		params.user_choosed_age = user_age;
		params.user_choosed_accident = user_accident;

		return params;
	}


	uint16_t calculateAllCosts(const uint16_t insurance_index, const AlgorithmParameters& params, const uint16_t fee) {



		return 0;
	}

	void algorithmTest(void) {

	}

} // namespace algo
