#include "Controller.hpp"


namespace ctrl {

    void createNewDatabase() {
        SqlConnection con;
        con.dropAllTables();
        con.createAllTables();
        con.displayAllTableData();
    }


    void displayDatabase() {
        SqlConnection con;
        con.displayAllTableData();
    }


    void saveHealthInsurance(const HealthInsurance& insurance) {
        SqlConnection con;
        con.saveInTableInsurance(insurance.getInsuranceName());
        //con.saveInTableBonus(insurance./*TODO: getBonusName*/);
    }

} // namespace ctrl
