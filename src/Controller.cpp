#include "Controller.hpp"
#include "Config.hpp"
#include "Globals.hpp"
#include "HealthInsurance.hpp"
#include "Deductible.hpp"
#include "DbConnection.hpp"
#include "FileManagement.hpp"
#include "UserInteraction.hpp"
#include "Algorithm.hpp"

#include <iostream>

namespace ctrl {

    // namespace used
    using db::TableDeductible;
    using db::InsuranceIDAndDeductible;
    using ext::CsvRead;
    using ext::CsvWrite;
    using logic::Deductible;


    void runApplication(int argc, char* argv[]) {

        using namespace user;
        using namespace algo;

        bool app_runing{ true };
        uint16_t user_choice{ 0 };
        SqlConnection connect;

        while (app_runing) {

#if DEBUG

#else
            system("cls");
#endif // DEBUG

            switch (user_choice) {

            case 0: // Choice of the user
                user_choice = listUserChoices(choices_main_menu);

                break;

            case 1: // Algorithm
                //user_choice = listUserChoices(choices_algorithm);
                user_choice = 1;

                if (user_choice == 1) {
                    AlgorithmParameters params = setAlgorithmParameters(
                        askUserMaximumFee(),
                        askUserRegion(connect.findAllDifferentRegions()),
                        askUserAge(connect.findLowestAge()),
                        askUserAccident());

                    populateArraysOfAlgorithm(params, connect, insurances_ids_matching, bonuses_matching, deductibles_matching);

                    runAlgorithm(params);
                }

                if (user_choice == 2) {
                    algorithmTest();
                }

                user_choice = 0;
                break;

            case 2: // Display the current DB
                displayDatabase();

                user_choice = 0;
                break;

            case 3:  // Create a new DB an insert a CSV
                createNewDatabase();
                createHealthInsurancesFromCSV(global::path, argc, argv);

                user_choice = 0;
                break;

            case 4:// TODO: make a function

                std::cout << connect.findLowestAge() << '\n';

                user_choice = 0;
                break;

            case 5: // Stop app

                app_runing = false;
                break;

            default:
                std::cout << "Error in Selection of the User\n";
                user_choice = 0;
                break;
            }
        }
    }


    void createNewDatabase(void) {
        SqlConnection connect;
        connect.dropAllTables();
        connect.createAllTables();
        connect.displayAllTableData();
    }


    void displayDatabase(void) {
        SqlConnection connect;
        connect.displayAllTableData();
    }


    // Parse a CSV file, parse this file, insert it to the database
    void createHealthInsurancesFromCSV(const std::string& file_path, int argc, char* argv[]) {
        
        CsvRead raw_file;
        CsvWrite parsed_file;
        std::vector<HealthInsurance> list_insurances;

#if DEBUG
        //parsed_file.showParsing(raw_file.csvReader(file_path, argc, argv));
#endif // DEBUG

        createNewHealthInsurance(raw_file.csvReader(file_path, argc, argv), list_insurances);


        // Insert health insurance, bonus, age and deductible data in database
        SqlConnection connect;
        for (const HealthInsurance& insurance : list_insurances) {
            insertDeductibleInDatabase(connect, insurance,
                saveHealthInsuranceInDatabase(connect, insurance),
                saveBonusInDatabase(connect, insurance),
                saveAgeInDatabase(connect, insurance)
            );
        }
    }


    uint16_t saveHealthInsuranceInDatabase(SqlConnection& connection, const HealthInsurance& insurance) {

		uint16_t insurance_id = connection.findInsuranceIDByName(insurance.getInsuranceName());

        if (insurance_id > 0) {
            std::cout << "Insurance " << insurance.getInsuranceName() << " found at ID: " << insurance_id << '\n';
        }
        else {
            connection.saveInTableInsurances(insurance.getInsuranceName());
            insurance_id = connection.findInsuranceIDByName(insurance.getInsuranceName());
        }    

        return insurance_id;
    }


    uint16_t saveBonusInDatabase(SqlConnection& connection, const HealthInsurance& insurance) {

        uint16_t bonus_id{ 0 };

		for (const Deductible& deductible : insurance.m_deductibles) {

            bonus_id = connection.findBonusIDByName(deductible.getDeductibleBonusName());

            if (bonus_id > 0) {
                std::cout << "Bonus " << deductible.getDeductibleBonusName() << " found at ID: " << bonus_id << '\n';
            }
            else {
                connection.saveInTableBonuses(deductible.getDeductibleBonusName());
                bonus_id = connection.findBonusIDByName(deductible.getDeductibleBonusName());
            }
        }

		return bonus_id;
    }

    
    uint16_t saveAgeInDatabase(SqlConnection& connection, const HealthInsurance& insurance) {

        uint16_t age_category_id{ 0 };

        for (const Deductible& deductible : insurance.m_deductibles) {

            std::string age_category_name{ deductible.getDeductibleAgeCategory() };
            age_category_id = connection.findAgeIDByName(age_category_name);

            if (age_category_id > 0) {
                std::cout << "Age category " << age_category_name << " found at ID: " << age_category_id << '\n';
            }
            else {
                uint16_t start{ 999 };
                uint16_t end{ 999 };

                std::cout << "When is starting the age category " << age_category_name << " : ";
				std::cin >> start;

                std::cout << "When is ending the age category " << age_category_name << " : ";
                std::cin >> end;
                std::cout << '\n';

                connection.saveInTableAge(age_category_name, start, end);
                age_category_id = connection.findAgeIDByName(age_category_name);
            }
        }
		return age_category_id;
    }


    void insertDeductibleInDatabase(
        SqlConnection& connection,
        const HealthInsurance& insurance,
        const uint16_t fk_insurance,
        const uint16_t fk_bonus,
        const uint16_t fk_age
    ) {

        TableDeductible deductible_to_insert;

        deductible_to_insert.m_fk_insurance = fk_insurance;
        deductible_to_insert.m_fk_bonus = fk_bonus;
        deductible_to_insert.m_fk_age = fk_age;

        for (const Deductible& deductible : insurance.m_deductibles) {

#if DEBUG
            deductible.displayDeductible();
#endif // DEBUG

            deductible_to_insert.m_accidents_risk = deductible.getDeductibleAccidentRisk();
            deductible_to_insert.m_model_name = deductible.getDeductibleModelName();
            deductible_to_insert.m_region = deductible.getDeductibleRegion();
            deductible_to_insert.m_deductible_1 = deductible.getDeductibleValue(0);
            deductible_to_insert.m_deductible_2 = deductible.getDeductibleValue(1);
            deductible_to_insert.m_deductible_3 = deductible.getDeductibleValue(2);
            deductible_to_insert.m_deductible_4 = deductible.getDeductibleValue(3);
            deductible_to_insert.m_deductible_5 = deductible.getDeductibleValue(4);
            deductible_to_insert.m_deductible_6 = deductible.getDeductibleValue(5);

            connection.saveInTableDeductibles(deductible_to_insert);
        }
    }


    // TODO: NEED to be rework for clarity
    void createNewHealthInsurance(const std::vector<CsvLine>& lines, std::vector<HealthInsurance>& list_insurances) {

        uint16_t deductible_region{ 0 };
        std::string deductible_bonus_name{ "n/a" };
        std::string deductible_age_category{ "n/a" };
        std::string insurance_year{ "n/a" };
        std::string insurance_state{ "n/a" };

        uint16_t ignored_phases{ 1 };

        for (CsvLine line : lines) {

            // Ignore the footer and reset for the header incoming
            if (line.getString(0).length() > 25 && line.getString(8).length() < 16 ) {

                ignored_phases = 1;
                continue;
            }


            switch (ignored_phases) {
                
            case 1: // Ignore the first line of the Header
                ignored_phases++;
                continue;

            case 2: // Set the Bonus Name to insert later in Deductibles
                    
                for (uint16_t column{ 0 }; column < global::NBR_COLUMN_IN_CSV_FILE; column++) {

                    if (line.getString(column) != "") {
                        deductible_bonus_name = line.getString(column);
#if DEBUG
                        std::cout << "Bonus Name: " << deductible_bonus_name << '\n';
#endif // DEBUG
                        break;
                    }
                    std::cout << "Bonus Name NOT FOUND \n";
                }

                ignored_phases++;
                continue;

            case 3: // Set the Year and State to insert later in the Insurance

                insurance_year = line.getString(6);
                insurance_state = line.getString(7);

                ignored_phases++;
                continue;

            case 4: // Set the Age Category to insert later in the Deductibles

                deductible_age_category = line.getString(6);

                ignored_phases++;
                continue;

            case 5: // Set the Region to insert later in Deductibles

                // Take the last char of the column, then substract a char '0' who give the real number(1) in uint16_t
                deductible_region = (uint16_t)(line.getString(6)[line.getString(6).size() - 1] - '0');
#if DEBUG
                std::cout << "last Char in region found: " << (uint16_t)(line.getString(6)[line.getString(6).size() - 1] - '0') << '\n';
                std::cout << "Region: " << deductible_region << '\n';
#endif // DEBUG

                ignored_phases++;
                continue;
                    
            case 6: // Skip the header

                break;
            }
            
            // Insurance creation 
            HealthInsurance insurance;
            Deductible deductible_with_accidents;
            Deductible deductible_without_accidents;

            insurance.setInsuranceYear(insurance_year);
            insurance.setInsuranceState(insurance_state);
                
            uint16_t column{ 0 };

            // Insert in deductible (0/300 to 600/2500) WITH accidents risk
            deductible_with_accidents.setDeductibleAccidentRisk(true);
            deductible_with_accidents.setDeductibleRegion(deductible_region);
            deductible_with_accidents.setDeductibleBonusName(deductible_bonus_name);
            deductible_with_accidents.setDeductibleAgeCategory(deductible_age_category);

            while (column < 6) {
                deductible_with_accidents.setDeductibleValues(column, line.getDouble(column));
                column++;
            }


            // Insert the Insurance Name and the Deductible Bonus Name
            if (line.getString(column)[0] == '"') {

                std::cout << "Start with: \"\n";

                insurance.setInsuranceName(line.getString(column).erase(0, 1));
                column++;

                deductible_with_accidents.setDeductibleModelName(line.getString(column).erase(line.getString(column).size() - 1));
                deductible_without_accidents.setDeductibleModelName(line.getString(column).erase(line.getString(column).size() - 1));
            }

            // Insert in insurance (name)
            else {
                insurance.setInsuranceName(line.getString(column));
            }
                column++;
            

            // Insert in deductible (0/300 to 600/2500) WITHOUT accidents risk
            deductible_without_accidents.setDeductibleAccidentRisk(false);
            deductible_without_accidents.setDeductibleRegion(deductible_region);
            deductible_without_accidents.setDeductibleBonusName(deductible_bonus_name);
            deductible_without_accidents.setDeductibleAgeCategory(deductible_age_category);

            while (column < 13) {
                deductible_without_accidents.setDeductibleValues(column - 7, line.getDouble(column));
                column++;
            }

            insurance.addDeductibleToInsurance(deductible_with_accidents);
            insurance.addDeductibleToInsurance(deductible_without_accidents);

            list_insurances.push_back(insurance);
        }
    }


    void populateArraysOfAlgorithm(const AlgorithmParameters& params, SqlConnection& connection, uint16_t* array_insurances_id, float* array_bonuses, uint16_t* array_deductibles) {
        
        uint16_t deductible_level{ 5 }; 
        std::vector<InsuranceIDAndDeductible> data_from_db;

        // TODO: useless maybe, else change deductible_level to 0
        //if (params.user_choosed_max_fee > 0) {
        //    for (uint16_t i{ 1 }; i < global::NBR_DEDUCTIBLES_PER_INSURANCE; i++) {

        //        if (params.user_choosed_max_fee > global::DEDUCTIBLES_POSSIBLE[i]) {
        //            deductible_level++;
        //        }
        //    }
        //}
        
        data_from_db = connection.findAllCorrespondingDeductibles(
            deductible_level,
            params.user_choosed_age,
            params.user_choosed_region,
            params.user_choosed_accident
        );

        data_from_db.shrink_to_fit();
        for (uint16_t i{ 0 }; i < data_from_db.size(); i++) {

#if DEBUG
            std::cout << "Loop " << i 
                << " - ID: " << data_from_db[i].m_id 
                << " Data: " << data_from_db[i].m_bonus 
                << " Deductible: " << global::DEDUCTIBLES_POSSIBLE[data_from_db[i].m_deductible]
                << '\n';
#endif // DEBUG

            array_insurances_id[i] = data_from_db[i].m_id;
            array_bonuses[i] = data_from_db[i].m_bonus;
            array_deductibles[i] = global::DEDUCTIBLES_POSSIBLE[data_from_db[i].m_deductible];
        }
    }




} // namespace ctrl
