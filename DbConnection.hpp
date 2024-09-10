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


namespace db {

	struct TblDeductible {
		int m_id{ 0 };
		int m_fk_insurance{ 0 };
		int m_fk_bonus{ 0 };
		int m_fk_age{ 0 };
		std::string m_bonus_name{ "n/a" };
		std::string m_model_name{ "n/a" }; // can be empty
		float m_deductible_1{ 0.0f };
		float m_deductible_2{ 0.0f };
		float m_deductible_3{ 0.0f };
		float m_deductible_4{ 0.0f };
		float m_deductible_5{ 0.0f };
		float m_deductible_6{ 0.0f };
		unsigned short int m_age{ 0 };
		unsigned short int m_region{ 0 };
		bool m_accidents_risk{ false };
	};
	
	class SqlConnection{
	
	public:
		SqlConnection();

		void dropAllTables();
		void createAllTables();

		void saveInTableInsurance(const std::string& ins_name);
		void saveInTableBonus(const std::string& bonus_name);
		void saveInTableDeductible(const TblDeductible& tbl);

		// To check if entry is aleready in DB
		int getInsuranceId(/*TODO*/);
		int getBonusId(/*TODO*/);
		int getAgeId(/*TODO*/);


		void displayAllTableData();
		void displayAllData(const std::string& table_name);

		// Not used for now
		void updateData();
		void deleteData();

	private:
		void connectToSqlDatabase();
		bool isConnectionOpen() const;

		sql::Driver* m_p_driver; // raw ptr returned by the C++ Connector lib
		std::unique_ptr<sql::Connection> m_p_connection;
	};
} // namespace db