/*****************************************************************//**
 * @file   Algorithm.hpp
 * @brief  
 * 
 * @author ThJo
 * @date   11 September 2024
 *********************************************************************/
#pragma once

#include "Typedef.hpp"
#include "Globals.hpp"

namespace algo {

	struct AlgorithmParameters {
		float user_choosed_prediction_fee{ 0.0f };
		uint16_t user_choosed_region{ 999 };
		uint16_t user_choosed_age{ 999 };
		bool user_choosed_accident{ false };
	};

	// Use Data Oriented Design (DOD), will be better for the Algorithm
	inline constexpr uint16_t ALGO_MAX_ENTRIES{ global::NBR_DEDUCTIBLES_PER_INSURANCE * global::NBR_RESULT_PER_DEDUCTIBLE };
	inline float contributions_matching[ALGO_MAX_ENTRIES];
	inline uint16_t deductibles_ids_matching[ALGO_MAX_ENTRIES];
	inline uint16_t deductibles_matching[ALGO_MAX_ENTRIES];
	inline uint16_t array_matching_id{ 0 };

	AlgorithmParameters& setAlgorithmParameters(
		const float user_max_fee,
		const uint16_t user_region,
		const uint16_t user_age,
		const bool user_accident
	);

	void clearAlgorithmArrays(void);

	// Return the ID of the best deductible
	uint16_t runAlgorithm(const AlgorithmParameters& params);



} // namespace algo

