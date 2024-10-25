#include <iostream>

#include "Controller.hpp"
#include "Config.hpp"
#include "Globals.hpp"
#include "HealthInsurance.hpp"
#include "Deductible.hpp"
#include "DbConnection.hpp"
#include "FileManagement.hpp"

namespace ctrl {

    // namespace used
    using db::TableDeductible;
    using ext::CsvRead;
    using ext::CsvWrite;
    using logic::Deductible;

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
        parsed_file.showParsing(raw_file.csvReader(file_path, argc, argv));
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


    void createNewHealthInsurance(const std::vector<CsvLine>& lines, std::vector<HealthInsurance>& list_insurances) {

        uint16_t region{ 0 };
        std::string bonus_name{ "n/a" };

        for (CsvLine line : lines) {

            uint16_t column{ 0 };
            HealthInsurance insurance;
            Deductible deductible_with_accidents;
            Deductible deductible_without_accidents;

            if (line.getDouble(column) == NULL && line.getInt(column) == NULL && line.getString(column) == "") {
                bonus_name = line.getString(5);
            }
			
            if (line.getDouble(column) == 300 && line.getDouble(column + 1) == 500) {

                // Take the last char of the column, then substract a char '0' who give the real number(1) in uint16_t
                region = (uint16_t)(line.getString(6)[line.getString(6).size() - 2] - '0');
#if DEBUG
                std::cout << "Region: " << region << '\n';
#endif // DEBUG

                continue;
            }



            // Insert in deductible (0/300 to 600/2500) WITH accidents risk
            deductible_with_accidents.setDeductibleAccidentRisk(true);
            deductible_with_accidents.setDeductibleRegion(region);
            deductible_with_accidents.setDeductibleBonusName(bonus_name);
            while (column < 6) {
                deductible_with_accidents.setDeductibleValues(column, line.getDouble(column));
                column++;
            }

            // Insert in insurance (name)
            insurance.setInsuranceName(line.getString(column));
            column++;

            // Insert in deductible (0/300 to 600/2500) WITHOUT accidents risk
            deductible_without_accidents.setDeductibleAccidentRisk(false);
            deductible_without_accidents.setDeductibleRegion(region);
            deductible_without_accidents.setDeductibleBonusName(bonus_name);
            while (column < 13) {
                deductible_without_accidents.setDeductibleValues(column - 7, line.getDouble(column));
                column++;
            }

            insurance.addDeductibleToInsurance(deductible_with_accidents);
            insurance.addDeductibleToInsurance(deductible_without_accidents);

            list_insurances.push_back(insurance);
        }
    }


    void parseHeaderContent(const std::vector<CsvLine>& lines, std::vector<HealthInsurance>& list_insurances) {

        uint16_t column{ 0 };


    }


    void parseMainContent(const std::vector<CsvLine>& lines, std::vector<HealthInsurance>& list_insurances) {

    }


    void parceFooterContent(const std::vector<CsvLine>& lines, std::vector<HealthInsurance>& list_insurances) {

    }

} // namespace ctrl
