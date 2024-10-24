/*****************************************************************//**
 * @file   Globals.hpp
 * @brief  All Globals variables are defined in this file
 * 
 * @author ThJo
 * @date   24 October 2024
 *********************************************************************/
#pragma once
#include "Typedef.hpp"

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
// @param my_string (std::string&)			=> The database connection object. (default = "example")
// @param insurance (const HealthInsurance&)	=> The health insurance object to be saved.
//
// @return (uint16_t)						=> The ID of the newly inserted health insurance record.
//uint16_t saveHealthInsuranceInDatabase(std::string& my_string = "example", const HealthInsurance& insurance);

namespace glb{

	inline const uint16_t NBR_VALUES_PER_DEDUCTIBLE{ 6 };

} // namespace glb


