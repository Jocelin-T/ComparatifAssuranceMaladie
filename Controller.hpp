/*****************************************************************//**
 * @file   Controller.hpp
 * @brief  Manage the data to pass between the SQL and the logic
 *
 * @author ThJo
 * @date   10 September 2024
 *********************************************************************/
#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <memory>

#include "Config.hpp"
#include "HealthInsurance.hpp"
#include "DbConnection.hpp"

 // namespace used
using logic::HealthInsurance;
using logic::Deductible;
using db::SqlConnection;
using db::TblDeductible;

namespace ctrl {


	/**
	 * Drop all Tables and create new Tables
	 */
	void createNewDatabase();

	/**
	 * Display all Tables
	 */
	void displayDatabase();


	void saveHealthInsurance(const HealthInsurance& insurance);
	


} // namespace ctrl
