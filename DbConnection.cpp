#include "DbConnection.hpp"
#include "Typedef.hpp"
#include "Config.hpp"


namespace db {

    // Connection to Database
    const std::string m_DATABASE_SERVER = "tcp://127.0.0.1:3306";
    const std::string m_DATABASE_USERNAME = "root";
    const std::string m_DATABASE_PASSWORD = "";
    const std::string m_DATABASE_NAME = "health_insurance";

    // Tables names
    const std::string m_TABLE_INSURANCES{ "INSURANCES" }; // hold insurances name
    const std::string m_TABLE_BONUSES{ "BONUSES" };
    const std::string m_TABLE_AGES{ "AGES" };
    const std::string m_TABLE_DEDUCTIBLES{ "DEDUCTIBLES" };
   
    // Add Tables references here!
    std::vector<const std::string*> m_list_tables_name{
        &m_TABLE_INSURANCES,
        &m_TABLE_BONUSES,
        &m_TABLE_AGES,
        &m_TABLE_DEDUCTIBLES
    };


    // Constructor
    SqlConnection::SqlConnection(void)
        : m_p_driver(nullptr) {

        connectToSqlDatabase();
    }


    // Drop all Tables if they exist
    void SqlConnection::dropAllTables(void) {

        if (!isConnectionOpen()) {
            return;
        }

        try {
            std::unique_ptr<sql::Statement> p_statement(m_p_connection->createStatement());

            // Disable foreign key checks
            p_statement->execute("SET FOREIGN_KEY_CHECKS = 0;");

            // Drop tables if they exist
            for (const std::string* table_name : m_list_tables_name) {
                p_statement->execute("DROP TABLE IF EXISTS " + *table_name);
            }

            p_statement->execute("SET FOREIGN_KEY_CHECKS = 1;");
            std::cout << "Finished dropping all tables (if existed)\n";
        }
        catch (sql::SQLException& e) {
            std::cerr << "SQL Error: " << e.what() << std::endl;
        }
        catch (std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
    

    // Create Tables
    void SqlConnection::createAllTables(void) {

        if (!isConnectionOpen()) {
            return;
        }

        try {
            std::unique_ptr<sql::Statement> p_statement(m_p_connection->createStatement());

            // Table Insurances (assurances)
            p_statement->execute(
                "CREATE TABLE " + m_TABLE_INSURANCES + " ("
                    "id INT PRIMARY KEY AUTO_INCREMENT, "
                    "name VARCHAR(50) NOT NULL "
                ");"
            );

            // Table Bonuses (primes)
            p_statement->execute(
                "CREATE TABLE " + m_TABLE_BONUSES + " ("
                    "id INT PRIMARY KEY AUTO_INCREMENT, "
                    "name VARCHAR(50) NOT NULL "
                ");"
            );

            // Table Ages
            p_statement->execute(
                "CREATE TABLE " + m_TABLE_AGES + " ("
                    "id INT PRIMARY KEY AUTO_INCREMENT, "
                    "name VARCHAR(50) NOT NULL, "
                    "start INT NOT NULL, "
                    "end INT NOT NULL "
                ");"
            );

            // Table Deducitbles (franchises)
            p_statement->execute(
                "CREATE TABLE " + m_TABLE_DEDUCTIBLES + " ("
                    "id INT PRIMARY KEY AUTO_INCREMENT, "
                    "fk_insurance INT NOT NULL, "
                    "fk_bonus INT NOT NULL, "
                    "fk_age INT NOT NULL, "
                    "model_name VARCHAR(50) NULL, "
                    "deduc_1 DECIMAL(4,2) NULL, "
                    "deduc_2 DECIMAL(4,2) NULL, "
                    "deduc_3 DECIMAL(4,2) NULL, "
                    "deduc_4 DECIMAL(4,2) NULL, "
                    "deduc_5 DECIMAL(4,2) NULL, "
                    "deduc_6 DECIMAL(4,2) NULL, "
                    "region INT NOT NULL, "
                    "accident BOOL NOT NULL, "
                    "FOREIGN KEY (fk_insurance) REFERENCES " + m_TABLE_INSURANCES + " (id), "
                    "FOREIGN KEY (fk_bonus) REFERENCES " + m_TABLE_BONUSES + " (id), "
                    "FOREIGN KEY (fk_age) REFERENCES " + m_TABLE_AGES + " (id)"
                ");"
            );

            std::cout << "Finished creating Tables\n";

        }
        catch (sql::SQLException& e) {
            std::cerr << "SQL Error: " << e.what() << std::endl;
        }
        catch (std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }


    // Insert in Table Insurance
    void SqlConnection::saveInTableInsurances(const std::string& insurance_name) {

        if (!isConnectionOpen()) {
            return;
        }

        try {
            std::unique_ptr<sql::PreparedStatement> p_prep_statement(
                m_p_connection->prepareStatement(
                    "INSERT INTO " + m_TABLE_INSURANCES +
                    "(name) "
                    "VALUES(?) ")
            );

            p_prep_statement->setString(1, insurance_name);
            p_prep_statement->execute();
        }
        catch (sql::SQLException& e) {
            std::cerr << "SQL Error: " << e.what() << std::endl;
        }
        catch (std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }


    // Insert in Table Bonus
    void SqlConnection::saveInTableBonuses(const std::string& bonus_name) {
        if (!isConnectionOpen()) {
            return;
        }

        try {
            std::unique_ptr<sql::PreparedStatement> p_prep_statement(
                m_p_connection->prepareStatement(
                    "INSERT INTO " + m_TABLE_BONUSES +
                    "(name) "
                    "VALUES(?) ")
            );

            p_prep_statement->setString(1, bonus_name);
            p_prep_statement->execute();
        }
        catch (sql::SQLException& e) {
            std::cerr << "SQL Error: " << e.what() << std::endl;
        }
        catch (std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }


    // Insert in Table Deductible
    void SqlConnection::saveInTableDeductibles(const TableDeductible& table) {

        if (!isConnectionOpen()) {
            return;
        }

        try {
            std::unique_ptr<sql::PreparedStatement> p_prep_statement(
                m_p_connection->prepareStatement(
                    "INSERT INTO " + m_TABLE_DEDUCTIBLES +
                    "("
                    "fk_insurance, " 
                    "fk_bonus, "
                    "fk_age, "
                    "model_name, "
                    "deduc_1, "
                    "deduc_2, "
                    "deduc_3, "
                    "deduc_4, "
                    "deduc_5, "
                    "deduc_6, "
                    "region, "
                    "accident"
                    ") "

                    "VALUES(?,?,?,?,?,?,?,?,?,?,?,?) ")
            );

            p_prep_statement->setInt(1, table.m_fk_insurance);
            p_prep_statement->setInt(2, table.m_fk_bonus);
            p_prep_statement->setInt(3, table.m_fk_age);
            p_prep_statement->setString(4, table.m_model_name);
            p_prep_statement->setDouble(5, table.m_deductible_1);
            p_prep_statement->setDouble(6, table.m_deductible_2);
            p_prep_statement->setDouble(7, table.m_deductible_3);
            p_prep_statement->setDouble(8, table.m_deductible_4);
            p_prep_statement->setDouble(9, table.m_deductible_5);
            p_prep_statement->setDouble(10, table.m_deductible_6);
            p_prep_statement->setInt(11, table.m_region);
            p_prep_statement->setBoolean(12, table.m_accidents_risk);

            p_prep_statement->execute();
        }
        catch (sql::SQLException& e) {
            std::cerr << "SQL Error: " << e.what() << std::endl;
        }
        catch (std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    // Return the insurance ID with the insurance name passed has parameter, or 0 if not found
    uint16_t SqlConnection::findInsuranceIDByName(const std::string& insurance_name) {

        return findIDInTableByName(m_TABLE_INSURANCES, insurance_name);
    }


    // Return the bonus ID with the bonus name passed has parameter, or 0 if not found
    uint16_t SqlConnection::findBonusIDByName(const std::string& bonus_name) {

        return findIDInTableByName(m_TABLE_AGES, bonus_name);
    }


    // Return the age ID with the age name passed has parameter, or 0 if not found
    uint16_t SqlConnection::findAgeIDByName(const std::string& age_name) {

        return findIDInTableByName(m_TABLE_AGES, age_name);
    }


    // Read all Data from all Tables
    void SqlConnection::displayAllTableData(void) {

        for (const std::string* table_name : m_list_tables_name) {
            displayAllDataFromOneTable(*table_name);
        }
    }


    // Read all Data from one Table inside the terminal
    void SqlConnection::displayAllDataFromOneTable(const std::string& table_name) {

        if (!isConnectionOpen()) {
            return;
        }

        try{
            std::unique_ptr<sql::Statement> p_statement(m_p_connection->createStatement());
            std::unique_ptr<sql::ResultSet> p_result_set(p_statement->executeQuery("SELECT * FROM " + table_name + ";"));
        
            // Get the number of columns with metadata (can't be unique_ptr because "getMetaData()" is a protected method)
            sql::ResultSetMetaData* p_result_set_meta = p_result_set->getMetaData();
            uint16_t nbr_columns = p_result_set_meta->getColumnCount();

            // Loop true the column and their names
            std::cout << "Data in table " << table_name << ":\n";
            for (uint16_t i{ 1 }; i <= nbr_columns; i++) {
                std::cout << std::setw(15) << std::left << p_result_set_meta->getColumnName(i);
            }
            std::cout << "\n---------------------------------------------------\n";

            // Loop true the rows and display the data
            while (p_result_set->next()) {
                for (uint16_t i{ 1 }; i <= nbr_columns; i++) {
                    std::cout << std::setw(25) << std::left << p_result_set->getString(i);
                }
                std::cout << '\n';
            }
        }
        catch (sql::SQLException& e) {
            std::cerr << "SQL Error: " << e.what() << std::endl;
        }
        catch (std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }


    // Update Data TODO
    void SqlConnection::updateData(void) {

        if (!isConnectionOpen()) {
            return;
        }

        try{
            std::unique_ptr<sql::PreparedStatement> p_prep_statement(
                m_p_connection->prepareStatement(
                    "UPDATE " + m_TABLE_INSURANCES + 
                    " SET quantity = ? WHERE name = ?")
            );

            p_prep_statement->setInt(1, 200);
            p_prep_statement->setString(2, "banana");
            p_prep_statement->execute();
            std::cout << "Row updated\n";
        }
        catch (sql::SQLException& e) {
            std::cerr << "SQL Error: " << e.what() << std::endl;
        }
        catch (std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    
    // Delete Data TODO
    void SqlConnection::deleteData(void) {

        if (!isConnectionOpen()) {
            return;
        }

        try{
            std::unique_ptr<sql::PreparedStatement> p_prep_statement(
                m_p_connection->prepareStatement(
                    "DELETE FROM " + m_TABLE_INSURANCES + 
                    " WHERE name = ?")
            );

            p_prep_statement->setString(1, "orange");
            p_prep_statement->execute();
            std::cout << "Row deleted\n";
        }
        catch (sql::SQLException& e) {
            std::cerr << "SQL Error: " << e.what() << std::endl;
        }
        catch (std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }


    // Return an ID by searching the name inside the Table passed in parameters
    uint16_t SqlConnection::findIDInTableByName(const std::string& table_name, const std::string& name) {

        if (!isConnectionOpen()) {
            return 0;
        }

        try {
            std::unique_ptr<sql::PreparedStatement> p_prep_statement(
                m_p_connection->prepareStatement(
                    "SELECT id"
                    " FROM " + table_name +
                    " WHERE name = ? ;"
                )
            );

            p_prep_statement->setString(1, name);
            std::unique_ptr<sql::ResultSet> result(p_prep_statement->executeQuery());

            if (result->next()) {
                return result->getInt("id");
            }
            else {
                return 0;
            }
        }
        catch (sql::SQLException& e) {
            std::cerr << "SQL Error: " << e.what() << std::endl;
        }
        catch (std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    // Connection to SQL Database
    void SqlConnection::connectToSqlDatabase(void) {
        try {
            m_p_driver = get_driver_instance();
            m_p_connection = std::unique_ptr<sql::Connection>(
                m_p_driver->connect(m_DATABASE_SERVER, m_DATABASE_USERNAME, m_DATABASE_PASSWORD)
            );
        }
        catch (const sql::SQLException& e) {
            std::cerr << "Could not connect to server. Error message: " << e.what()
                << "\nSQLState: " << e.getSQLState()
                << "\nError Code: " << e.getErrorCode() << '\n';
            return;
        }

        m_p_connection->setSchema(m_DATABASE_NAME);
    }


    // Check if the connection with the DB is open
    bool SqlConnection::isConnectionOpen(void) const {
        if (!m_p_connection) {
            std::cerr << "Connection not established!\n";
            return false;
        }
        return true;
    }

} // namespace db