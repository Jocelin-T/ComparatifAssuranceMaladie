/*****************************************************************//**
 * @file   Controller.hpp
 * @brief  Manage the data to pass between the SQL and the logic
 *
 * @author ThJo
 * @date   10 September 2024
 *********************************************************************/
#pragma once
#include <fstream>
#include <string>
#include <sstream>
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
	using logic::HealthInsurance;
	using db::SqlConnection;
	using ext::CsvLine;

	/**
	 * Drop all Tables and create new Tables
	 */
	void createNewDatabase(void);

	/**
	 * Display all Tables
	 */
	void displayDatabase(void);


	void createHealthInsurancesFromCSV(const std::string& file_path, int argc, char* argv[]);

	uint16_t saveHealthInsuranceInDatabase(SqlConnection& connection, const HealthInsurance& insurance);

	uint16_t saveBonusInDatabase(SqlConnection& connection, const HealthInsurance& insurance);

	uint16_t saveAgeInDatabase(SqlConnection& connection, const HealthInsurance& insurance);

	void saveDeductibleInDatabase(
		SqlConnection& connection,
		const HealthInsurance& insurance,
		const uint16_t fk_insurance,
		const uint16_t fk_bonus, 
		const uint16_t fk_age
	);
	
	/**
	* @brief :
	*
	* @param lines (std::vector<CsvLine>)  => vector holding lines
	*/
	void createNewHealthInsurance(const std::vector<CsvLine>& lines, std::vector<HealthInsurance>& list_insurances);

} // namespace ctrl
