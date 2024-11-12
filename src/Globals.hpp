/*****************************************************************//**
 * @file   Globals.hpp
 * @brief  All Globals variables are defined in this file
 * 
 * @author ThJo
 * @date   24 October 2024
 *********************************************************************/
#pragma once
#include "Typedef.hpp"
#include <string>
#include <cctype>

/*
	TODO:
		- 

	FIX:
		-
*/

// To generate code with TabNine:

// Can you write the comment for the function [INSERT_FUNCTION_SIGNATURE] 
//  located at line [INSERT_LINE] in the file [INSERT_FILE] in the same style 
//	(the data type of the parameters and return between (),
//	the sign => who are aligned in the same column) as below:
// 
// @brief Saves a health insurance record in the database.
//
// This function inserts a health insurance record into the database.
// It ensures that all necessary fields are correctly populated and
// handles any database constraints or requirements.
//
// @param my_string (std::string&)				=> The database connection object. (default = "example")
// @param insurance (const HealthInsurance&)	=> The health insurance object to be saved.
//
// @return (uint16_t)							=> The ID of the newly inserted health insurance record.
//uint16_t saveHealthInsuranceInDatabase(std::string& my_string = "example", const HealthInsurance& insurance);


namespace global {

	inline std::string path{ "C:\\Users\\ThJo\\source\\repos\\ComparatifAssuranceMaladie\\ressources\\2024_Test.csv" }; // CSV without children, cause there is 2 more columns
	//inline std::string path{ "C:\\Users\\ThJo\\source\\repos\\ComparatifAssuranceMaladie\\ressources\\2024_Canton.VD.csv" };

	inline constexpr uint16_t NBR_DEDUCTIBLES_PER_INSURANCE{ 6 };
	inline constexpr uint16_t NBR_COLUMN_IN_CSV_FILE{ 13 };

	inline constexpr uint16_t DEDUCTIBLES_POSSIBLE[NBR_DEDUCTIBLES_PER_INSURANCE]{ 300,500,1000,1500,2000,2500 };
	inline constexpr float MIN_SHARE{ 0.0f };
	inline constexpr float MAX_SHARE{ 700.0f };
	inline constexpr float QUOTA{ 0.1f }; // quote-part 10%

	inline constexpr uint16_t NBR_RESULT_PER_DEDUCTIBLE{ 20 };


	namespace function {

		// @brief Checks if a string represents a valid numeric value.
		//
		// This function examines the input string to determine if it represents
		// a valid numeric value. It allows for integers, decimal numbers, and
		// negative numbers. The function considers the following as valid:
		// - Digits (0-9)
		// - A single decimal point (.) not as first character
		// - A single negative sign (-) at the beginning
		//
		// @param str (const std::string&) => The string to be checked for numeric content.
		//
		// @return (bool)                  => true if the string represents a valid numeric value,
		//                                    false otherwise.
		bool isStringNumeric(const std::string& string);

	} // namespace global::function
} // namespace global


