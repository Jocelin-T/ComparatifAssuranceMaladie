/*****************************************************************//**
 * @file   DbConnection.h
 * @brief  Manage a connection with a SQL Database
 * 
 * @author ThJo
 * @date   15 August 2024
 *********************************************************************/
#pragma once
#include <stdlib.h>
#include <iostream>
#include <string>
#include <memory>
#include <iomanip>
#include <vector>

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/metadata.h>
#include <cppconn/resultset_metadata.h>

#include "Typedef.hpp"


namespace db {

	struct TableDeductible {
		//std::string m_bonus_name{ "n/a" };
		std::string m_model_name{ "n/a" }; // can be empty
		float m_deductible_1{ 0.0f };
		float m_deductible_2{ 0.0f };
		float m_deductible_3{ 0.0f };
		float m_deductible_4{ 0.0f };
		float m_deductible_5{ 0.0f };
		float m_deductible_6{ 0.0f };
		uint16_t m_id{ 0 };
		uint16_t m_fk_insurance{ 0 };
		uint16_t m_fk_bonus{ 0 };
		uint16_t m_fk_age{ 0 };
		uint16_t m_region{ 0 };
		bool m_accidents_risk{ false };
	};

	struct InsuranceIDAndDeductible {
		float m_contribution{ 0.0f };
		uint16_t m_id{ 0 };
		uint16_t m_deductible{ 0 };
	};
	
	class SqlConnection{
	public:

		SqlConnection(void);


		// @brief Drops all tables in the connected database.
		//
		// This function attempts to drop all tables listed in m_list_tables_names.
		// It temporarily disables foreign key checks to allow dropping tables
		// with dependencies. After dropping the tables, it re-enables foreign key checks.
		//
		// @param (void)
		//
		// @return (void)
		//
		void dropAllTables(void);


		// @brief Creates all tables in the connected database.
		//
		// This function attempts to create all tables defined for the database.
		// It creates tables for insurances, bonuses, ages, and deductibles,
		// establishing the necessary relationships between them using foreign keys.
		//
		// @param (void)
		//
		// @return (void)
		//
		void createAllTables(void);


		// @brief Saves an insurance record in the "INSURANCES" table.
		//
		// This function inserts an insurance record into the "INSURANCES" table.
		// It ensures that the name field is correctly populated and
		// handles any database constraints or requirements.
		//
		// @param insurance_name (const std::string&)	=> The name of the insurance to be saved.
		//
		// @return (void)
		void saveInTableInsurances(const std::string& insurance_name);


		// @brief Saves a bonus record in the bonuses table.
		//
		// This function inserts a new bonus record into the bonuses table of the database.
		// It ensures that the bonus name is correctly inserted and handles any database
		// constraints or requirements.
		//
		// @param bonus_name (const std::string&)   => The name of the bonus to be saved.
		//
		// @return (void)
		void saveInTableBonuses(const std::string& bonus_name);


		void saveInTableAge(const std::string& age_category_name, const uint16_t start_age, const uint16_t end_age);


		void saveInTableDeductibles(const TableDeductible& deductible);


		// @brief Finds the lowest non-zero deductible amount in the Deductibles table.
		//
		// This function queries the database to find the minimum value of the deduc_6 column
		// in the Deductibles table, excluding zero values. It handles potential database
		// connection issues and SQL exceptions.
		//
		// @return (uint16_t) => The lowest non-zero deductible amount found.
		//                       Returns 0 if no valid deductible is found or if an error occurs.
		uint16_t findLowestBonus(void) const;


		// @brief Retrieves all distinct regions from the deductibles table.
		//
		// This function queries the database to find all unique region values
		// stored in the deductibles table. It represents all the different
		// regions for which insurance data is available.
		//
		// @param  (void)
		//
		// @return (std::vector<uint16_t>)  => A vector containing all distinct region values.
		//                                     Returns an empty vector if no regions are found
		//                                     or if there's an error in the database connection
		//                                     or query execution.
		std::vector<uint16_t> findAllDifferentRegions(void) const;


		uint16_t findLowestAge(void) const;


		std::vector<InsuranceIDAndDeductible> findAllCorrespondingDeductibles(
			const uint16_t deductible_level,
			const uint16_t age,
			const uint16_t region,
			const bool accident
		);


		// To check if entry is aleready in DB
		uint16_t findInsuranceIDByName(const std::string& insurance_name) const;

		uint16_t findBonusIDByName(const std::string& bonus_name) const;

		uint16_t findAgeIDByName(const std::string& age_name) const;

		
		TableDeductible findDeductibleDataWithID(const uint16_t deductible_id) const;

		std::string findInsuranceNameWithID(const uint16_t insurance_id) const;

		std::string findBonusNameWithID(const uint16_t bonus_id) const;

		std::string findAgeCategoryWithID(const uint16_t age_id) const;


		void displayAllTableData(void);
		void displayAllDataFromOneTable(const std::string& table_name);

		void updateData(void); // Not used for now
		void deleteData(void); // Not used for now

	private:

		uint16_t findCorrespondingAgeID(const uint16_t age);

		std::string findNameInTableByID(
			const std::string& table_name,
			const uint16_t find_id,
			const std::string& column_name,
			const std::string& column_id
		) const;

		uint16_t findIDInTableByName(
			const std::string& table_name,
			const std::string& find_name,
			const std::string& column_name,
			const std::string& column_id
		) const;

		void connectToSqlDatabase(void);

		bool isConnectionOpen(void) const;

		sql::Driver* m_p_driver; // raw ptr returned by the C++ Connector lib
		std::unique_ptr<sql::Connection> m_p_connection;
	};
} // namespace db