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

	TO FIX:
		-
*/

// To generate code with Tabnine:

// Can you write the comment for this function in the same style (the data type, the sign => who are aligned in the same column) as below:
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


namespace glb{
	inline std::string path{ "C:\\Users\\ThJo\\source\\repos\\ComparatifAssuranceMaladie\\x64\\Release\\2024_Test.csv" }; // CSV without children, cause there is 2 more columns
	//inline std::string path{ "C:\\Users\\ThJo\\source\\repos\\ComparatifAssuranceMaladie\\x64\\Release\\2024_Canton.VD.csv" };

	inline const uint16_t NBR_VALUES_PER_DEDUCTIBLE{ 6 };
	inline const uint16_t NBR_COLUMN_IN_CSV_FILE{ 13 };

	inline const uint16_t DEDUCTIBLES_POSSIBLE[]{ 300,500,1000,1500,2000,2500 };



	// @brief Checks if a string represents a valid numeric value.
	//
	// This function examines the input string to determine if it represents
	// a valid numeric value. It allows for integers, decimal numbers, and
	// negative numbers. The function considers the following as valid:
	// - Digits (0-9)
	// - A single decimal point (.)
	// - A single negative sign (-) at the beginning
	//
	// @param str (const std::string&) => The string to be checked for numeric content.
	//
	// @return (bool)                  => true if the string represents a valid numeric value,
	//                                    false otherwise.
	//
	bool isStringNumeric(const std::string& string);

} // namespace glb


