/*****************************************************************//**
 * @file   Algorithm.hpp
 * @brief  
 * 
 * @author ThJo
 * @date   11 September 2024
 *********************************************************************/
#pragma once

#include "Typedef.hpp"

#include <string>


namespace algo {

	// TODO: Use Data Oriented Design (DOD), will be better for the Algorithm

	void runAlgorithm(const float user_fee, const uint16_t user_region, const uint16_t user_age);

	void setAlgorithmParameters(const float user_fee, const uint16_t user_region, const uint16_t user_age);

	// Debug function
	void algorithmTest(void);

} // namespace algo

