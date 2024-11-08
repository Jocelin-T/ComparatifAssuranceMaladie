/*****************************************************************//**
 * @file   Algorithm.hpp
 * @brief  
 * 
 * @author ThJo
 * @date   11 September 2024
 *********************************************************************/
#pragma once

#include "Typedef.hpp"

namespace algo {
	// TODO: Use Data Oriented Design (DOD), will be better for the Algorithm

	struct AlgorithmParameters {
		float user_choosed_max_fee{ 0.0f };
		uint16_t user_choosed_region{ 999 };
		uint16_t user_choosed_age{ 999 };
		bool user_choosed_accident{ false };
	};

	inline const uint16_t ALGO_MAX_ENTRIES{ 120 };
	inline uint16_t insurances_ids_matching[ALGO_MAX_ENTRIES];
	inline float contributions_matching[ALGO_MAX_ENTRIES];
	inline uint16_t deductibles_matching[ALGO_MAX_ENTRIES];

	void runAlgorithm(const AlgorithmParameters& params); // TODO: Return the ID of the best insurance

	AlgorithmParameters& setAlgorithmParameters(
		const float user_max_fee,
		const uint16_t user_region,
		const uint16_t user_age,
		const bool user_accident
	);

	void findBestInsurance();


	uint16_t calculateAllCosts(
		const uint16_t matching_index,
		const AlgorithmParameters& params,
		const float fee
	);

	// Debug function
	void algorithmTest(void);

} // namespace algo

