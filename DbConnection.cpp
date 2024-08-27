#include "DbConnection.hpp"

namespace db {

    // Connection
    const std::string DB_SERVER = "tcp://127.0.0.1:3306";
    const std::string DB_USERNAME = "root";
    const std::string DB_PASSWORD = "";
    const std::string DATABASE_NAME = "health_insurance";

    // Tables name
    const std::string TABLE_INVENTORY{ "inventory" };


    // Constructor
    SqlConnection::SqlConnection()
    :  m_p_driver(nullptr)
    {
        ConnectToSqlDB();
    }


    // Connection to SQL Database
    void SqlConnection::ConnectToSqlDB() {
        try {
            m_p_driver = get_driver_instance();
            m_p_connection = std::unique_ptr<sql::Connection>(
                m_p_driver->connect(DB_SERVER, DB_USERNAME, DB_PASSWORD)
            );
        }
        catch (const sql::SQLException& e) {
            std::cerr << "Could not connect to server. Error message: " << e.what()
                << "\nSQLState: " << e.getSQLState()
                << "\nError Code: " << e.getErrorCode() << "\n";
            return;
        }

        m_p_connection->setSchema(DATABASE_NAME);
    }


    // Check if the connection with the DB is open
    bool SqlConnection::IsConnectionOpen() const {
        if (!m_p_connection) {
            std::cerr << "Connection not established!\n";
            return false;
        }
        return true;
    }


    // Create Tables
    void SqlConnection::CreateTables() const {

        if (!IsConnectionOpen()) {
            return;
        }

        std::unique_ptr<sql::Statement> p_statement(m_p_connection->createStatement());

        p_statement->execute(
            "DROP TABLE IF EXISTS " + TABLE_INVENTORY
        );
        std::cout << "Finished dropping table (if existed)\n";

        p_statement->execute(
            "CREATE TABLE " + TABLE_INVENTORY + " ("
            "id INT PRIMARY KEY AUTO_INCREMENT, "
            "name VARCHAR(50), "
            "quantity INTEGER); "
        );
        std::cout << "Finished creating table\n";
    }


    // Insert Data
    void SqlConnection::InsertData() {

        if (!IsConnectionOpen()) {
            return;
        }

        std::unique_ptr<sql::PreparedStatement> p_prep_statement(
            m_p_connection->prepareStatement(
                "INSERT INTO " + TABLE_INVENTORY + 
                "(name, quantity) "
                "VALUES(?, ?) ")
        );

        p_prep_statement->setString(1, "banana");
        p_prep_statement->setInt(2, 150);
        p_prep_statement->execute();
        std::cout << "One row inserted.\n";

        p_prep_statement->setString(1, "orange");
        p_prep_statement->setInt(2, 154);
        p_prep_statement->execute();
        std::cout << "One row inserted.\n";

        p_prep_statement->setString(1, "apple");
        p_prep_statement->setInt(2, 100);
        p_prep_statement->execute();
        std::cout << "One row inserted.\n";
    }


    // Read all Data from a table
    void SqlConnection::ReadAllData(const std::string& table_name) const {

        if (!IsConnectionOpen()) {
            return;
        }

        std::unique_ptr<sql::Statement> p_statement(m_p_connection->createStatement());
        std::unique_ptr<sql::ResultSet> p_result_set(p_statement->executeQuery("SELECT * FROM " + table_name + ";"));
        
        // Get the number of columns with metadata (can't be unique_ptr because "getMetaData()" is a protected method)
        sql::ResultSetMetaData* p_result_set_meta = p_result_set->getMetaData();
        unsigned short int nbr_columns = p_result_set_meta->getColumnCount();

        // Loop true the column and their names
        std::cout << "Data in table " << table_name << ":\n";
        for (int i = 1; i <= nbr_columns; i++) {
            std::cout << std::setw(20) << std::left << p_result_set_meta->getColumnName(i);
        }
        std::cout << "\n---------------------------------------------------\n";

        // Loop true the rows and display the data
        while (p_result_set->next()) {
            for (int i = 1; i <= nbr_columns; i++) {
                std::cout << std::setw(20) << std::left << p_result_set->getString(i);
            }
            std::cout << "\n";
        }
    }


    // Update Data
    void SqlConnection::UpdateData() {

        if (!IsConnectionOpen()) {
            return;
        }

        std::unique_ptr<sql::PreparedStatement> p_prep_statement(
            m_p_connection->prepareStatement(
                "UPDATE " + TABLE_INVENTORY + 
                " SET quantity = ? WHERE name = ?")
        );

        p_prep_statement->setInt(1, 200);
        p_prep_statement->setString(2, "banana");
        p_prep_statement->execute();
        std::cout << "Row updated\n";
    }


    // Delete Data
    void SqlConnection::DeleteData() {

        if (!IsConnectionOpen()) {
            return;
        }

        std::unique_ptr<sql::PreparedStatement> p_prep_statement(
            m_p_connection->prepareStatement(
                "DELETE FROM " + TABLE_INVENTORY + 
                " WHERE name = ?")
        );

        p_prep_statement->setString(1, "orange");
        p_prep_statement->execute();
        std::cout << "Row deleted\n";
    }
} // namespace db