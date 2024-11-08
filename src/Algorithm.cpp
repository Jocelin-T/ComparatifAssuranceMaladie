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

			std::cout 
				<< i 
				<< " - ID: " << insurances_ids_matching[i] 
				<< " Data: " << contributions_matching[i] 
				<< " Deductible: " << deductibles_matching[i]
				<< '\n';
		}
#endif // DEBUG

		// Calculate the best insurance if the value given by the user is over the lowest deductible
		if (params.user_choosed_max_fee > global::DEDUCTIBLES_POSSIBLE[0]) {

			for (uint16_t i{ 0 }; i < global::NBR_DEDUCTIBLES_PER_INSURANCE; i++) {

				float fee{ params.user_choosed_max_fee };
				std::cout << "User max fee: " << fee << '\n';

				fee -= global::DEDUCTIBLES_POSSIBLE[i];
				std::cout << "Max fee -deductible: " << fee << '\n';

				if (fee <= 0) {
					std::cout << "Break at: " << fee << " Deductible: " << global::DEDUCTIBLES_POSSIBLE[i] << '\n';
					break;
				}

				fee -= global::MAX_SHARE;
				std::cout << "Max fee -deductible & -max share: " << fee << '\n';

				if (fee <= 0 || i == global::NBR_DEDUCTIBLES_PER_INSURANCE - 1) {
					std::cout << "Break at: " << fee << " Deductible: " << global::DEDUCTIBLES_POSSIBLE[i] << '\n';
					break;
				}


			}
		}
		else {
			// TODO: Get the lowest value Data(insurance_id, monthly_contribution, deductible) for the higher deductible
			std::cout << "Lowest than the min deductible\n";
		}


		// TODO: Value to update
		calculateAllCosts(0, params, 700);
	}


	AlgorithmParameters& setAlgorithmParameters(
		const float user_max_fee,
		const uint16_t user_region,
		const uint16_t user_age,
		const bool user_accident) {
		
		AlgorithmParameters params;

		params.user_choosed_max_fee = user_max_fee;
		params.user_choosed_region = user_region;
		params.user_choosed_age = user_age;
		params.user_choosed_accident = user_accident;

		return params;
	}


	uint16_t calculateAllCosts(const uint16_t matching_index, const AlgorithmParameters& params, const float fee) {

		uint16_t deductible{ deductibles_matching[matching_index] };
		float monthly_contribution{ contributions_matching[matching_index] };


		return monthly_contribution * 12;
	}


	void algorithmTest(void) {

	}

} // namespace algo
