/*****************************************************************//**
 * @file   Controller.hpp
 * @brief  Manage the data to pass between the SQL and the logic
 *
 * @author ThJo
 * @date   10 September 2024
 *********************************************************************/
#pragma once
#include <string>
#include <vector>

#include "Typedef.hpp"

// Forward declaration
namespace logic {
	class HealthInsurance;
}

namespace db {
	class SqlConnection;
}

namespace ext {
	class CsvLine;
}

namespace ctrl {

	// Used namespace
	using logic::HealthInsurance;
	using db::SqlConnection;
	using ext::CsvLine;

	/**
	* @brief Creates a new database by dropping all existing tables and creating new ones.
	*
	* This function initializes the database structure by removing any existing tables
	* and creating new tables with the required schema for the health insurance system.
	*
	* @param (void)
	*
	* @return (void)
	*/
	void createNewDatabase(void);


	/**
	* @brief Displays the contents of all tables in the database.
	*
	* This function retrieves and displays the data from all tables in the database,
	* providing a comprehensive view of the stored health insurance information.
	*
	* @param (void)
	*
	* @return (void)
	*/
	void displayDatabase(void);


	/**
	* @brief Creates health insurance records from a CSV file.
	*
	* This function reads data from a CSV file, processes each line,
	* and creates health insurance records. It handles file reading,
	* data parsing, and populates the database with the extracted information.
	*
	* @param file_path (const std::string&)	=> The path to the CSV file containing health insurance data.
	* @param argc (int)						=> The number of command-line arguments.
	* @param argv (char* [])				=> An array of command-line argument strings.
	*
	* @return (void)
	*/
	void createHealthInsurancesFromCSV(const std::string& file_path, int argc, char* argv[]);


	/**
	* @brief Saves a health insurance record in the database.
	*
	* This function inserts a health insurance record into the database.
	* It ensures that all necessary fields are correctly populated and
	* handles any database constraints or requirements.
	*
	* @param connection (SqlConnection&)		=> The database connection object.
	* @param insurance (const HealthInsurance&)	=> The health insurance object to be saved.
	*
	* @return (uint16_t)						=> The ID of the newly inserted health insurance record.
	*/
	uint16_t saveHealthInsuranceInDatabase(SqlConnection& connection, const HealthInsurance& insurance);


	/**
	* @brief Saves the bonus data related to health insurance in the database.
	*
	* This function iterates through the deductibles of a given health insurance,
	* checks if the bonus name already exists in the database, and if not,
	* inserts the bonus data into the 'bonuses' table.
	*
	* @param connection (SqlConnection&)		=> The database connection object.
	* @param insurance (const HealthInsurance&) => The health insurance object containing the deductibles.
	*
	* @return (uint16_t)						=> The ID of the last inserted bonus in the 'bonuses' table.
	*												If a bonus with the same name already exists, 
	*												the function returns the ID of the existing bonus.
	*/
	uint16_t saveBonusInDatabase(SqlConnection& connection, const HealthInsurance& insurance);


	/**
	* @brief Saves the age categories of the health insurance plans in the database.
	*
	* This function checks if the age category already exists in the database.
	* If it exists, it retrieves the ID of the existing age category.
	* If it does not exist, it inserts the age category into the database and retrieves the new ID.
	*
	* @param connection (SqlConnection&)		=> The database connection object.
	* @param insurance (const HealthInsurance&) => The health insurance object containing the deductibles.
	*
	* @return (uint16_t)						=> The ID of the age category in the database.
	*/
	uint16_t saveAgeInDatabase(SqlConnection& connection, const HealthInsurance& insurance);


	/**
	* @brief Inserts a deductible record into the database.
	*
	* This function inserts a deductible record into the database.
	* It ensures that all necessary fields are correctly populated and
	* handles any database constraints or requirements.
	*
	* @param connection (SqlConnection&)		=> The database connection object.
	* @param insurance (const HealthInsurance&) => The health insurance object containing the deductibles.
	* @param fk_insurance (uint16_t)			=> The foreign key referencing the health insurance record.
	* @param fk_bonus (uint16_t)				=> The foreign key referencing the bonus record.
	* @param fk_age (uint16_t)					=> The foreign key referencing the age category record.
	*
	* @return (void)
	*/
	void insertDeductibleInDatabase(
		SqlConnection& connection,
		const HealthInsurance& insurance,
		const uint16_t fk_insurance,
		const uint16_t fk_bonus,
		const uint16_t fk_age
	);
	

	/**
	* @brief Creates new health insurance records from CSV data.
	*
	* This function processes CSV lines to create health insurance records.
	* It parses each line, extracts relevant data, and populates a list of
	* HealthInsurance objects. The function ensures that all necessary fields
	* are correctly populated and handles any data inconsistencies.
	*
	* @param lines (std::vector<CsvLine>&)						=> Vector holding CSV lines to be processed.
	* @param list_insurances (std::vector<HealthInsurance>&)	=> Vector to store the created health insurance objects.
	*
	* @return (void)
	*/
	void createNewHealthInsurance(const std::vector<CsvLine>& lines, std::vector<HealthInsurance>& list_insurances);

} // namespace ctrl
