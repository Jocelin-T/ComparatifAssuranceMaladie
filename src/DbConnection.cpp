#include "DbConnection.hpp"
#include "Typedef.hpp"
#include "Config.hpp"


namespace db {

    // Connection to Database
    const std::string m_DATABASE_SERVER = "tcp://127.0.0.1:3306";
    const std::string m_DATABASE_USERNAME = "root";
    const std::string m_DATABASE_PASSWORD = "";
    const std::string m_DATABASE_NAME = "health_insurance";

    // Tables
    const std::string m_TABLE_INSURANCES{ "INSURANCES" };
    const std::string m_INS_ID{ "ins_id" };
    const std::string m_INS_NAME{ "ins_name" };

    const std::string m_TABLE_BONUSES{ "BONUSES" };
    const std::string m_BON_ID{ "bon_id" };
    const std::string m_BON_NAME{ "bon_name" };

    const std::string m_TABLE_AGES{ "AGES" };
	const std::string m_AGE_ID{ "age_id" };
	const std::string m_AGE_NAME{ "age_name" };
	const std::string m_AGE_MIN{ "age_min" };
	const std::string m_AGE_MAX{ "age_max" };

    const std::string m_TABLE_DEDUCTIBLES{ "DEDUCTIBLES" };
	const std::string m_DED_ID{ "ded_id" };
	const std::string m_DED_NAME{ "ded_name" };
    const std::string m_DED_DEDUCTIBLE_1{ "ded_deductible_0" };
	const std::string m_DED_DEDUCTIBLE_2{ "ded_deductible_1" };
	const std::string m_DED_DEDUCTIBLE_3{ "ded_deductible_2" };
	const std::string m_DED_DEDUCTIBLE_4{ "ded_deductible_3" };
	const std::string m_DED_DEDUCTIBLE_5{ "ded_deductible_4" };
	const std::string m_DED_DEDUCTIBLE_6{ "ded_deductible_5" };
    const std::string m_DED_REGION{ "ded_region" };
    const std::string m_DED_ACCIDENT{ "ded_accident" };
    const std::string m_DED_FK_INSURANCE{ "fk_insurance" };
    const std::string m_DED_FK_BONUS{ "fk_bonus" };
    const std::string m_DED_FK_AGE{ "fk_age" };



    // Add Tables references here!
    std::vector<const std::string*> m_list_tables_names{
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
            for (const std::string* table_name : m_list_tables_names) {
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
                    + m_INS_ID + " INT PRIMARY KEY AUTO_INCREMENT, "
                    + m_INS_NAME + " VARCHAR(50) NOT NULL "
                ");"
            );

            // Table Bonuses (primes)
            p_statement->execute(
                "CREATE TABLE " + m_TABLE_BONUSES + " ("
                    + m_BON_ID + " INT PRIMARY KEY AUTO_INCREMENT, "
                    + m_BON_NAME + " VARCHAR(50) NOT NULL "
                ");"
            );

            // Table Ages
            p_statement->execute(
                "CREATE TABLE " + m_TABLE_AGES + " ("
                    + m_AGE_ID + " INT PRIMARY KEY AUTO_INCREMENT, "
                    + m_AGE_NAME + " VARCHAR(50) NOT NULL, "
                    + m_AGE_MIN + " INT NOT NULL, "
                    + m_AGE_MAX + " INT NOT NULL "
                ");"
            );

            // Table Deducitbles (franchises)
            p_statement->execute(
                "CREATE TABLE " + m_TABLE_DEDUCTIBLES + " ("
                    + m_DED_ID + " INT PRIMARY KEY AUTO_INCREMENT, "
                    + m_DED_NAME + " VARCHAR(50) NULL, "
                    + m_DED_DEDUCTIBLE_1 + " DECIMAL(6,2) NOT NULL, "
                    + m_DED_DEDUCTIBLE_2 + " DECIMAL(6,2) NOT NULL, "
                    + m_DED_DEDUCTIBLE_3 + " DECIMAL(6,2) NOT NULL, "
                    + m_DED_DEDUCTIBLE_4 + " DECIMAL(6,2) NOT NULL, "
                    + m_DED_DEDUCTIBLE_5 + " DECIMAL(6,2) NOT NULL, "
                    + m_DED_DEDUCTIBLE_6 + " DECIMAL(6,2) NOT NULL, "
                    + m_DED_REGION + " INT NOT NULL, "
                    + m_DED_ACCIDENT + " BOOL NOT NULL, "
                    + m_DED_FK_INSURANCE + " INT NOT NULL, "
                    + m_DED_FK_BONUS + " INT NOT NULL, "
                    + m_DED_FK_AGE + " INT NOT NULL, "
                    "FOREIGN KEY (" + m_DED_FK_INSURANCE + ") REFERENCES " + m_TABLE_INSURANCES + " (" + m_INS_ID + "), "
                    "FOREIGN KEY (" + m_DED_FK_BONUS + ") REFERENCES " + m_TABLE_BONUSES + " (" + m_BON_ID + "), "
                "FOREIGN KEY (" + m_DED_FK_AGE + ") REFERENCES " + m_TABLE_AGES + " (" + m_AGE_ID + ")"
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
                    "(" + m_INS_NAME + ") "
                    "VALUES(?) "
                )
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
                    "(" + m_BON_NAME + ") "
                    "VALUES(?) "
                )
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


    void SqlConnection::saveInTableAge(const std::string& age_category_name, const uint16_t start_age, const uint16_t end_age) {

        if (!isConnectionOpen()) {
            return;
        }

        try {
            std::unique_ptr<sql::PreparedStatement> p_prep_statement(
                m_p_connection->prepareStatement(
                    "INSERT INTO " + m_TABLE_AGES +
                    "("
                    + m_AGE_NAME + ", "
                    + m_AGE_MIN + ", "
                    + m_AGE_MAX +
                    ") "

                    "VALUES(?,?,?) ")
            );

            p_prep_statement->setString(1, age_category_name);
            p_prep_statement->setInt(2, start_age);
            p_prep_statement->setInt(3, end_age);

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
    void SqlConnection::saveInTableDeductibles(const TableDeductible& deductible) {

        if (!isConnectionOpen()) {
            return;
        }

        try {
            std::unique_ptr<sql::PreparedStatement> p_prep_statement(
                m_p_connection->prepareStatement(
                    "INSERT INTO " + m_TABLE_DEDUCTIBLES +
                    "("
                    + m_DED_NAME + ", "
                    + m_DED_DEDUCTIBLE_1 + ", "
                    + m_DED_DEDUCTIBLE_2 + ", "
                    + m_DED_DEDUCTIBLE_3 + ", "
                    + m_DED_DEDUCTIBLE_4 + ", "
                    + m_DED_DEDUCTIBLE_5 + ", "
                    + m_DED_DEDUCTIBLE_6 + ", "
                    + m_DED_REGION + ", "
                    + m_DED_ACCIDENT + ", "
                    + m_DED_FK_INSURANCE + ", " 
                    + m_DED_FK_BONUS + ", "
                    + m_DED_FK_AGE +
                    ") "

                    "VALUES(?,?,?,?,?,?,?,?,?,?,?,?) ")
            );

            p_prep_statement->setString(1, deductible.m_model_name);
            p_prep_statement->setDouble(2, deductible.m_deductible_1);
            p_prep_statement->setDouble(3, deductible.m_deductible_2);
            p_prep_statement->setDouble(4, deductible.m_deductible_3);
            p_prep_statement->setDouble(5, deductible.m_deductible_4);
            p_prep_statement->setDouble(6, deductible.m_deductible_5);
            p_prep_statement->setDouble(7, deductible.m_deductible_6);
            p_prep_statement->setInt(8, deductible.m_region);
            p_prep_statement->setBoolean(9, deductible.m_accidents_risk);
            p_prep_statement->setInt(10, deductible.m_fk_insurance);
            p_prep_statement->setInt(11, deductible.m_fk_bonus);
            p_prep_statement->setInt(12, deductible.m_fk_age);

            p_prep_statement->execute();
        }
        catch (sql::SQLException& e) {
            std::cerr << "SQL Error: " << e.what() << std::endl;
        }
        catch (std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }


    uint16_t SqlConnection::findLowestBonus(void) const {

        if (!isConnectionOpen()) {
            return 0;
        }

        try {
            std::unique_ptr<sql::PreparedStatement> p_prep_statement(
                m_p_connection->prepareStatement(
                    "SELECT MIN(" + m_DED_DEDUCTIBLE_6 + ")"
                    " FROM " + m_TABLE_DEDUCTIBLES +
                    " WHERE " + m_DED_DEDUCTIBLE_6 + " > 0;"
                )
            );

            std::unique_ptr<sql::ResultSet> result(p_prep_statement->executeQuery());

            if (result->next()) {
                return result->getDouble("MIN(" + m_DED_DEDUCTIBLE_6 + ")");
            }
        }
        catch (sql::SQLException& e) {
            std::cerr << "SQL Error: " << e.what() << std::endl;
        }
        catch (std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    // Return an array(pointer) with all differents regions found in the DB
    std::vector<uint16_t> SqlConnection::findAllDifferentRegions(void) const {

        std::vector<uint16_t> regions;

        if (!isConnectionOpen()) {
            return regions;
        }

        try {
            std::unique_ptr<sql::PreparedStatement> p_prep_statement(
                m_p_connection->prepareStatement(
                    "SELECT DISTINCT " + m_DED_REGION +
                    " FROM " + m_TABLE_DEDUCTIBLES +
                    " ;"
                )
            );

            std::unique_ptr<sql::ResultSet> result(p_prep_statement->executeQuery());

            while (true) {
                if (result->next()) {
					regions.push_back(result->getInt(m_DED_REGION));
                }
                else {
                    return regions;
                }
            }
        }
        catch (sql::SQLException& e) {
            std::cerr << "SQL Error: " << e.what() << std::endl;
        }
        catch (std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }


    uint16_t SqlConnection::findLowestAge(void) const {

        if (!isConnectionOpen()) {
            return 0;
        }

        try {
            std::unique_ptr<sql::PreparedStatement> p_prep_statement(
                m_p_connection->prepareStatement(
                    "SELECT MIN(" + m_AGE_MIN + ")"
                    " FROM " + m_TABLE_AGES +
                    " ;"
                )
            );

            std::unique_ptr<sql::ResultSet> result(p_prep_statement->executeQuery());

            while (true) {
                if (result->next()) {
					return result->getInt("MIN(" + m_AGE_MIN + ")");
                }
            }
        }
        catch (sql::SQLException& e) {
            std::cerr << "SQL Error: " << e.what() << std::endl;
        }
        catch (std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }


    std::vector<InsuranceIDAndDeductible> SqlConnection::findAllCorrespondingDeductibles(const uint16_t deductible_level, const uint16_t age, const uint16_t region, const bool accident) {

        std::vector<InsuranceIDAndDeductible> data_to_send;

        if (!isConnectionOpen()) {
            return data_to_send;
        }

		std::string query{ "" };

        switch (deductible_level) {
        case 1:
            data_to_send.reserve(40);
            query =
                "(SELECT " + m_DED_ID + " AS id, " + m_DED_DEDUCTIBLE_1 + " AS value, '" + m_DED_DEDUCTIBLE_1 + "' AS column_name FROM " + m_TABLE_DEDUCTIBLES +
                " WHERE " + m_DED_DEDUCTIBLE_1 + " > 0 ORDER BY " + m_DED_DEDUCTIBLE_1 + " ASC LIMIT 20) "
                "UNION ALL"
                "(SELECT " + m_DED_ID + " AS id, " + m_DED_DEDUCTIBLE_2 + " AS value, '" + m_DED_DEDUCTIBLE_2 + "' AS column_name FROM " + m_TABLE_DEDUCTIBLES +
                " WHERE " + m_DED_DEDUCTIBLE_2 + " > 0 ORDER BY " + m_DED_DEDUCTIBLE_2 + " ASC LIMIT 20); ";
            break;

        case 2:
            data_to_send.reserve(60);
            query =
                "(SELECT " + m_DED_ID + " AS id, " + m_DED_DEDUCTIBLE_1 + " AS value, '" + m_DED_DEDUCTIBLE_1 + "' AS column_name FROM " + m_TABLE_DEDUCTIBLES +
                " WHERE " + m_DED_DEDUCTIBLE_1 + " > 0 ORDER BY " + m_DED_DEDUCTIBLE_1 + " ASC LIMIT 20) "
                "UNION ALL"
                "(SELECT " + m_DED_ID + " AS id, " + m_DED_DEDUCTIBLE_2 + " AS value, '" + m_DED_DEDUCTIBLE_2 + "' AS column_name FROM " + m_TABLE_DEDUCTIBLES +
                " WHERE " + m_DED_DEDUCTIBLE_2 + " > 0 ORDER BY " + m_DED_DEDUCTIBLE_2 + " ASC LIMIT 20) "
                "UNION ALL"
                "(SELECT " + m_DED_ID + " AS id, " + m_DED_DEDUCTIBLE_3 + " AS value, '" + m_DED_DEDUCTIBLE_3 + "' AS column_name FROM " + m_TABLE_DEDUCTIBLES +
                " WHERE " + m_DED_DEDUCTIBLE_3 + " > 0 ORDER BY " + m_DED_DEDUCTIBLE_3 + " ASC LIMIT 20); ";
            break;

        case 3:
            data_to_send.reserve(80);
            query =
                "(SELECT " + m_DED_ID + " AS id, " + m_DED_DEDUCTIBLE_1 + " AS value, '" + m_DED_DEDUCTIBLE_1 + "' AS column_name FROM " + m_TABLE_DEDUCTIBLES +
                " WHERE " + m_DED_DEDUCTIBLE_1 + " > 0 ORDER BY " + m_DED_DEDUCTIBLE_1 + " ASC LIMIT 20) "
                "UNION ALL"
                "(SELECT " + m_DED_ID + " AS id, " + m_DED_DEDUCTIBLE_2 + " AS value, '" + m_DED_DEDUCTIBLE_2 + "' AS column_name FROM " + m_TABLE_DEDUCTIBLES +
                " WHERE " + m_DED_DEDUCTIBLE_2 + " > 0 ORDER BY " + m_DED_DEDUCTIBLE_2 + " ASC LIMIT 20) "
                "UNION ALL"
                "(SELECT " + m_DED_ID + " AS id, " + m_DED_DEDUCTIBLE_3 + " AS value, '" + m_DED_DEDUCTIBLE_3 + "' AS column_name FROM " + m_TABLE_DEDUCTIBLES +
                " WHERE " + m_DED_DEDUCTIBLE_3 + " > 0 ORDER BY " + m_DED_DEDUCTIBLE_3 + " ASC LIMIT 20) "
                "UNION ALL"
                "(SELECT " + m_DED_ID + " AS id, " + m_DED_DEDUCTIBLE_4 + " AS value, '" + m_DED_DEDUCTIBLE_4 + "' AS column_name FROM " + m_TABLE_DEDUCTIBLES +
                " WHERE " + m_DED_DEDUCTIBLE_4 + " > 0 ORDER BY " + m_DED_DEDUCTIBLE_4 + " ASC LIMIT 20); ";
            break;

        case 4:
            data_to_send.reserve(100);
            query =
                "(SELECT " + m_DED_ID + " AS id, " + m_DED_DEDUCTIBLE_1 + " AS value, '" + m_DED_DEDUCTIBLE_1 + "' AS column_name FROM " + m_TABLE_DEDUCTIBLES +
                " WHERE " + m_DED_DEDUCTIBLE_1 + " > 0 ORDER BY " + m_DED_DEDUCTIBLE_1 + " ASC LIMIT 20) "
                "UNION ALL"
                "(SELECT " + m_DED_ID + " AS id, " + m_DED_DEDUCTIBLE_2 + " AS value, '" + m_DED_DEDUCTIBLE_2 + "' AS column_name FROM " + m_TABLE_DEDUCTIBLES +
                " WHERE " + m_DED_DEDUCTIBLE_2 + " > 0 ORDER BY " + m_DED_DEDUCTIBLE_2 + " ASC LIMIT 20) "
                "UNION ALL"
                "(SELECT " + m_DED_ID + " AS id, " + m_DED_DEDUCTIBLE_3 + " AS value, '" + m_DED_DEDUCTIBLE_3 + "' AS column_name FROM " + m_TABLE_DEDUCTIBLES +
                " WHERE " + m_DED_DEDUCTIBLE_3 + " > 0 ORDER BY " + m_DED_DEDUCTIBLE_3 + " ASC LIMIT 20) "
                "UNION ALL"
                "(SELECT " + m_DED_ID + " AS id, " + m_DED_DEDUCTIBLE_4 + " AS value, '" + m_DED_DEDUCTIBLE_4 + "' AS column_name FROM " + m_TABLE_DEDUCTIBLES +
                " WHERE " + m_DED_DEDUCTIBLE_4 + " > 0 ORDER BY " + m_DED_DEDUCTIBLE_4 + " ASC LIMIT 20) "
                "UNION ALL"
                "(SELECT " + m_DED_ID + " AS id, " + m_DED_DEDUCTIBLE_5 + " AS value, '" + m_DED_DEDUCTIBLE_5 + "' AS column_name FROM " + m_TABLE_DEDUCTIBLES +
                " WHERE " + m_DED_DEDUCTIBLE_5 + " > 0 ORDER BY " + m_DED_DEDUCTIBLE_5 + " ASC LIMIT 20); ";
            break;

        case 5:
            data_to_send.reserve(120);
            query =
                "(SELECT " + m_DED_ID + " AS id, " + m_DED_DEDUCTIBLE_1 + " AS value, '" + m_DED_DEDUCTIBLE_1 + "' AS column_name FROM " + m_TABLE_DEDUCTIBLES +
                " WHERE " + m_DED_DEDUCTIBLE_1 + " > 0 ORDER BY " + m_DED_DEDUCTIBLE_1 + " ASC LIMIT 20) "
                "UNION ALL"
                "(SELECT " + m_DED_ID + " AS id, " + m_DED_DEDUCTIBLE_2 + " AS value, '" + m_DED_DEDUCTIBLE_2 + "' AS column_name FROM " + m_TABLE_DEDUCTIBLES +
                " WHERE " + m_DED_DEDUCTIBLE_2 + " > 0 ORDER BY " + m_DED_DEDUCTIBLE_2 + " ASC LIMIT 20) "
                "UNION ALL"
                "(SELECT " + m_DED_ID + " AS id, " + m_DED_DEDUCTIBLE_3 + " AS value, '" + m_DED_DEDUCTIBLE_3 + "' AS column_name FROM " + m_TABLE_DEDUCTIBLES +
                " WHERE " + m_DED_DEDUCTIBLE_3 + " > 0 ORDER BY " + m_DED_DEDUCTIBLE_3 + " ASC LIMIT 20) "
                "UNION ALL"
                "(SELECT " + m_DED_ID + " AS id, " + m_DED_DEDUCTIBLE_4 + " AS value, '" + m_DED_DEDUCTIBLE_4 + "' AS column_name FROM " + m_TABLE_DEDUCTIBLES +
                " WHERE " + m_DED_DEDUCTIBLE_4 + " > 0 ORDER BY " + m_DED_DEDUCTIBLE_4 + " ASC LIMIT 20) "
                "UNION ALL"
                "(SELECT " + m_DED_ID + " AS id, " + m_DED_DEDUCTIBLE_5 + " AS value, '" + m_DED_DEDUCTIBLE_5 + "' AS column_name FROM " + m_TABLE_DEDUCTIBLES +
                " WHERE " + m_DED_DEDUCTIBLE_5 + " > 0 ORDER BY " + m_DED_DEDUCTIBLE_5 + " ASC LIMIT 20) "
                "UNION ALL"
                "(SELECT " + m_DED_ID + " AS id, " + m_DED_DEDUCTIBLE_6 + " AS value, '" + m_DED_DEDUCTIBLE_6 + "' AS column_name FROM " + m_TABLE_DEDUCTIBLES +
                " WHERE " + m_DED_DEDUCTIBLE_6 + " > 0 ORDER BY " + m_DED_DEDUCTIBLE_6 + " ASC LIMIT 20); ";
            break;

        default:
            data_to_send.reserve(20);
            query =
                "(SELECT " + m_DED_ID + " AS id, " + m_DED_DEDUCTIBLE_1 + " AS value, '" + m_DED_DEDUCTIBLE_1 + "' AS column_name FROM " + m_TABLE_DEDUCTIBLES +
                " WHERE " + m_DED_DEDUCTIBLE_1 + " > 0 ORDER BY " + m_DED_DEDUCTIBLE_1 + " ASC LIMIT 20); ";
            break;
        }

        try {
            std::unique_ptr<sql::PreparedStatement> p_prep_statement(
                m_p_connection->prepareStatement(query)
            );

            std::unique_ptr<sql::ResultSet> result(p_prep_statement->executeQuery());


            while (result->next()) {
                
                InsuranceIDAndDeductible data;

                data.m_id = result->getInt("id");
                data.m_bonus = result->getDouble("value");

                std::string column_name = result->getString("column_name");
                data.m_deductible = column_name.back() - '0'; // Return the last char of the column name has a digit

#if DEBUG
                std::cout << "ID: " << data.m_id << " Column: " << column_name << ", Value: " << data.m_bonus << '\n';
#endif // DEBUG

                data_to_send.push_back(data);
            }

            return data_to_send;

        }
        catch (sql::SQLException& e) {
            std::cerr << "SQL Error: " << e.what() << std::endl;
        }
        catch (std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }


    // Return the insurance ID with the insurance name passed has parameter, or 0 if not found
    uint16_t SqlConnection::findInsuranceIDByName(const std::string& insurance_name) const {

        return findIDInTableByName(m_TABLE_INSURANCES, insurance_name, m_INS_NAME, m_INS_ID);
    }


    // Return the bonus ID with the bonus name passed has parameter, or 0 if not found
    uint16_t SqlConnection::findBonusIDByName(const std::string& bonus_name) const {

        return findIDInTableByName(m_TABLE_BONUSES, bonus_name, m_BON_NAME, m_BON_ID);
    }


    // Return the age ID with the age name passed has parameter, or 0 if not found
    uint16_t SqlConnection::findAgeIDByName(const std::string& age_name) const {

        return findIDInTableByName(m_TABLE_AGES, age_name, m_AGE_NAME, m_AGE_ID);
    }


    // Read all Data from all Tables
    void SqlConnection::displayAllTableData(void) {

        for (const std::string* table_name : m_list_tables_names) {
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
            std::cout << "\nData in table " << table_name << ":\n";
            for (uint16_t i{ 1 }; i <= nbr_columns; i++) {
                std::cout << std::setw(12) << std::left << p_result_set_meta->getColumnName(i) << '|';
            }
            std::cout << "\n---------------------------------------------------\n";

            // Loop true the rows and display the data
            while (p_result_set->next()) {
                for (uint16_t i{ 1 }; i <= nbr_columns; i++) {
                    std::cout << std::setw(12) << std::left << p_result_set->getString(i) << '|';
                }
                std::cout << '\n';
            }
            std::cout << "\n===================================================\n";

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


	// Return the Name inside a Table with the ID passed in parameter
    std::string SqlConnection::findNameInTableByID(const std::string& table_name, const uint16_t find_id, const std::string& column_name, const std::string& column_id) const {

        if (!isConnectionOpen()) {
            return "";
        }

        try {
            std::unique_ptr<sql::PreparedStatement> p_prep_statement(
                m_p_connection->prepareStatement(
					"SELECT " + column_name + " AS name"
                    " FROM " + table_name +
                    " WHERE " + column_id + " = ? ;"
                )
            );

            p_prep_statement->setInt(1, find_id);
            std::unique_ptr<sql::ResultSet> result(p_prep_statement->executeQuery());

            if (result->next()) {
                return result->getString("name");
            }
            else {
                return "";
            }
        }
        catch (sql::SQLException& e) {
            std::cerr << "SQL Error: " << e.what() << std::endl;
        }
        catch (std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }


    // Return an ID by searching the name inside the Table passed in parameters
    uint16_t SqlConnection::findIDInTableByName(const std::string& table_name, const std::string& find_name, const std::string& column_name, const std::string& column_id) const {

        if (!isConnectionOpen()) {
            return 0;
        }

        try {
            std::unique_ptr<sql::PreparedStatement> p_prep_statement(
                m_p_connection->prepareStatement(
                    "SELECT " + column_id + " AS id"
                    " FROM " + table_name +
                    " WHERE " + column_name + " = ? ;"
                )
            );

            p_prep_statement->setString(1, find_name);
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