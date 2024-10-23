#include <iostream>

#include "Controller.hpp"
#include "Config.hpp"
#include "HealthInsurance.hpp"
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


        SqlConnection connect;

        for (const HealthInsurance& insurance : list_insurances) {

            saveHealthInsuranceInDatabase(connect, insurance);
            saveBonusInDatabase(connect, insurance);
            saveAgeInDatabase(connect, insurance);
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


    // BUG does not work
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

        uint16_t age_category_id = connection.findInsuranceIDByName(insurance.getInsuranceName());

		return age_category_id;
    }


    // TODO: Use a parsed CSV file to create a HealthInsurance Object.
    void createNewHealthInsurance(const std::vector<CsvLine>& lines, std::vector<HealthInsurance>& list_insurances) {

        for (CsvLine line : lines) {
            uint16_t column{ 0 };

            HealthInsurance insurance;
			
            // Insert in deductible (0/300 to 600/2500) WITH accident risk
            Deductible deductible_with_accidents;
            deductible_with_accidents.setDeductibleAccidentRisk(true);

            while (column < 6) {
                deductible_with_accidents.setDeductibleValues(column, line.getDouble(column));
                column++;
            }

            // Insert in insurance (name)
            insurance.setInsuranceName(line.getString(column));
            column++;

            // Insert in deductible (0/300 to 600/2500) WITHOUT accident risk
            Deductible deductible_without_accidents;
            deductible_without_accidents.setDeductibleAccidentRisk(false);

            while (column < 13) {
                deductible_without_accidents.setDeductibleValues(column - 7, line.getDouble(column));
                column++;
            }

            insurance.addDeductibleToInsurance(deductible_with_accidents);
            insurance.addDeductibleToInsurance(deductible_without_accidents);

            list_insurances.push_back(insurance);
        }
    }

} // namespace ctrl
