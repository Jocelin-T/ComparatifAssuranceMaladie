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

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/metadata.h>
#include <cppconn/resultset_metadata.h>

namespace db {
	class SqlConnection{
	public:
		SqlConnection();

		void CreateTables() const;
		void InsertData();
		void ReadAllData(const std::string& table_name) const;
		void UpdateData();
		void DeleteData();

	private:
		void ConnectToSqlDB();
		bool IsConnectionOpen() const;

		sql::Driver* m_p_driver; // raw ptr returned by the C++ Connector lib
		std::unique_ptr<sql::Connection> m_p_connection;
	};
} // namespace db