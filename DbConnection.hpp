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
		uint16_t m_id{ 0 };
		uint16_t m_fk_insurance{ 0 };
		uint16_t m_fk_bonus{ 0 };
		uint16_t m_fk_age{ 0 };
		std::string m_bonus_name{ "n/a" };
		std::string m_model_name{ "n/a" }; // can be empty
		float m_deductible_1{ 0.0f };
		float m_deductible_2{ 0.0f };
		float m_deductible_3{ 0.0f };
		float m_deductible_4{ 0.0f };
		float m_deductible_5{ 0.0f };
		float m_deductible_6{ 0.0f };
		uint16_t m_region{ 0 };
		bool m_accidents_risk{ false };
	};
	
	class SqlConnection{
	
	public:
		SqlConnection(void);

		void dropAllTables(void);
		void createAllTables(void);

		void saveInTableInsurances(const std::string& insurance_name);
		void saveInTableBonuses(const std::string& bonus_name);
		void saveInTableDeductibles(const TableDeductible& table);

		// To check if entry is aleready in DB
		uint16_t findInsuranceIDByName(const std::string& insurance_name);
		uint16_t findBonusIDByName(const std::string& bonus_name);
		uint16_t findAgeIDByName(const std::string& age_name);


		void displayAllTableData(void);
		void displayAllDataFromOneTable(const std::string& table_name);

		void updateData(void); // Not used for now
		void deleteData(void); // Not used for now

	private:
		uint16_t findIDInTableByName(const std::string& table_name, const std::string& name);
		void connectToSqlDatabase(void);
		bool isConnectionOpen(void) const;

		sql::Driver* m_p_driver; // raw ptr returned by the C++ Connector lib
		std::unique_ptr<sql::Connection> m_p_connection;
	};
} // namespace db