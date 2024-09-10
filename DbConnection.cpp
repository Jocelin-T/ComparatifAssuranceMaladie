#include "DbConnection.hpp"
#include "Config.hpp"


namespace db {

    // Connection
    const std::string DB_SERVER = "tcp://127.0.0.1:3306";
    const std::string DB_USERNAME = "root";
    const std::string DB_PASSWORD = "";
    const std::string DATABASE_NAME = "health_insurance";

    // Tables name
    const std::string TABLE_INSURANCE{ "insurance" }; // hold insurances name
    const std::string TABLE_BONUS{ "bonus" };
    const std::string TABLE_AGE{ "age" };
    const std::string TABLE_DEDUCTIBLE{ "deductible" };
   
    // Add Tables references here!
    std::vector<const std::string*> list_tables_name{
        &TABLE_INSURANCE,
        &TABLE_BONUS,
        &TABLE_AGE,
        &TABLE_DEDUCTIBLE
    };


    // Constructor
    SqlConnection::SqlConnection()
    :  m_p_driver(nullptr)
    {
        connectToSqlDatabase();
    }


    // Connection to SQL Database
    void SqlConnection::connectToSqlDatabase() {
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
    bool SqlConnection::isConnectionOpen() const {
        if (!m_p_connection) {
            std::cerr << "Connection not established!\n";
            return false;
        }
        return true;
    }


    // Drop all Tables if they exist
    void SqlConnection::dropAllTables() {

        if (!isConnectionOpen()) {
            return;
        }

        try {
            std::unique_ptr<sql::Statement> p_statement(m_p_connection->createStatement());

            // Disable foreign key checks
            p_statement->execute("SET FOREIGN_KEY_CHECKS = 0;");

            // Drop tables if they exist
            for (const std::string* table_name : list_tables_name) {
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
    void SqlConnection::createAllTables() {

        if (!isConnectionOpen()) {
            return;
        }

        try {
            std::unique_ptr<sql::Statement> p_statement(m_p_connection->createStatement());

            // Table Insurance (assurances)
            p_statement->execute(
                "CREATE TABLE " + TABLE_INSURANCE + " ("
                    "id INT PRIMARY KEY AUTO_INCREMENT, "
                    "name VARCHAR(50) NOT NULL "
                ");"
            );

            // Table Bonus (primes)
            p_statement->execute(
                "CREATE TABLE " + TABLE_BONUS + " ("
                    "id INT PRIMARY KEY AUTO_INCREMENT, "
                    "name VARCHAR(50) NOT NULL "
                ");"
            );

            // Table Age
            p_statement->execute(
                "CREATE TABLE " + TABLE_AGE + " ("
                    "id INT PRIMARY KEY AUTO_INCREMENT, "
                    "name VARCHAR(50) NOT NULL, "
                    "start SMALLINT NOT NULL, "
                    "end SMALLINT NOT NULL "
                ");"
            );

            // Table Deducitble (franchises)
            p_statement->execute(
                "CREATE TABLE " + TABLE_DEDUCTIBLE + " ("
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
                    "region BIT NOT NULL, "
                    "accident BOOL NOT NULL, "
                    "FOREIGN KEY (fk_insurance) REFERENCES " + TABLE_INSURANCE + "(id), "
                    "FOREIGN KEY (fk_bonus) REFERENCES " + TABLE_BONUS + "(id), "
                    "FOREIGN KEY (fk_age) REFERENCES " + TABLE_AGE + "(id)"
                ");"
            );
            std::cout << "Finished creating table\n";

        }
        catch (sql::SQLException& e) {
            std::cerr << "SQL Error: " << e.what() << std::endl;
        }
        catch (std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }


    // Insert/Update in Table Insurance
    void SqlConnection::saveInTableInsurance(const std::string& ins_name) {

        if (!isConnectionOpen()) {
            return;
        }

        try {
            std::unique_ptr<sql::PreparedStatement> p_prep_statement(
                m_p_connection->prepareStatement(
                    "INSERT INTO " + TABLE_INSURANCE +
                    "(name) "
                    "VALUES(?) ")
            );

            p_prep_statement->setString(1, ins_name);
            p_prep_statement->execute();
        }
        catch (sql::SQLException& e) {
            std::cerr << "SQL Error: " << e.what() << std::endl;
        }
        catch (std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }


    // Insert/Update in Table Bonus
    void SqlConnection::saveInTableBonus(const std::string& bonus_name) {
        if (!isConnectionOpen()) {
            return;
        }

        try {
            std::unique_ptr<sql::PreparedStatement> p_prep_statement(
                m_p_connection->prepareStatement(
                    "INSERT INTO " + TABLE_BONUS +
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


    // Insert/Update in Table Deductible
    void SqlConnection::saveInTableDeductible(const TblDeductible& tbl) {
        if (!isConnectionOpen()) {
            return;
        }

        try {
            std::unique_ptr<sql::PreparedStatement> p_prep_statement(
                m_p_connection->prepareStatement(
                    "INSERT INTO " + TABLE_DEDUCTIBLE +
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

            p_prep_statement->setInt(1, tbl.m_fk_insurance);
            p_prep_statement->setInt(2, tbl.m_fk_bonus);
            p_prep_statement->setInt(3, tbl.m_fk_age);
            p_prep_statement->setString(4, tbl.m_model_name);
            p_prep_statement->setDouble(5, tbl.m_deductible_1);
            p_prep_statement->setDouble(6, tbl.m_deductible_2);
            p_prep_statement->setDouble(7, tbl.m_deductible_3);
            p_prep_statement->setDouble(8, tbl.m_deductible_4);
            p_prep_statement->setDouble(9, tbl.m_deductible_5);
            p_prep_statement->setDouble(10, tbl.m_deductible_6);
            p_prep_statement->setInt(11, tbl.m_region);
            p_prep_statement->setBoolean(12, tbl.m_accidents_risk);

            p_prep_statement->execute();
        }
        catch (sql::SQLException& e) {
            std::cerr << "SQL Error: " << e.what() << std::endl;
        }
        catch (std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    // Read all Data from all Tables
    void SqlConnection::displayAllTableData() {

        for (const std::string* table_name : list_tables_name) {
            displayAllData(*table_name);
        }
    }


    // Read all Data from a Table
    void SqlConnection::displayAllData(const std::string& table_name) {

        if (!isConnectionOpen()) {
            return;
        }

        try{
            std::unique_ptr<sql::Statement> p_statement(m_p_connection->createStatement());
            std::unique_ptr<sql::ResultSet> p_result_set(p_statement->executeQuery("SELECT * FROM " + table_name + ";"));
        
            // Get the number of columns with metadata (can't be unique_ptr because "getMetaData()" is a protected method)
            sql::ResultSetMetaData* p_result_set_meta = p_result_set->getMetaData();
            unsigned short int nbr_columns = p_result_set_meta->getColumnCount();

            // Loop true the column and their names
            std::cout << "Data in table " << table_name << ":\n";
            for (int i = 1; i <= nbr_columns; i++) {
                std::cout << std::setw(15) << std::left << p_result_set_meta->getColumnName(i);
            }
            std::cout << "\n---------------------------------------------------\n";

            // Loop true the rows and display the data
            while (p_result_set->next()) {
                for (int i = 1; i <= nbr_columns; i++) {
                    std::cout << std::setw(25) << std::left << p_result_set->getString(i);
                }
                std::cout << "\n";
            }
        }
        catch (sql::SQLException& e) {
            std::cerr << "SQL Error: " << e.what() << std::endl;
        }
        catch (std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }


    // Update Data
    void SqlConnection::updateData() {

        if (!isConnectionOpen()) {
            return;
        }

        try{
            std::unique_ptr<sql::PreparedStatement> p_prep_statement(
                m_p_connection->prepareStatement(
                    "UPDATE " + TABLE_INSURANCE + 
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


    // Delete Data
    void SqlConnection::deleteData() {

        if (!isConnectionOpen()) {
            return;
        }

        try{
            std::unique_ptr<sql::PreparedStatement> p_prep_statement(
                m_p_connection->prepareStatement(
                    "DELETE FROM " + TABLE_INSURANCE + 
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
} // namespace db