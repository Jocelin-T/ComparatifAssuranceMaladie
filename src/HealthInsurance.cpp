#include "HealthInsurance.hpp"
#include "Config.hpp"
#include "Deductible.hpp"

#include <iostream>

namespace logic{

    HealthInsurance::HealthInsurance(void) {
        m_deductibles.reserve(2);
    }


    void HealthInsurance::addDeductibleToInsurance(Deductible& deductible) {
        m_deductibles.push_back(std::move(deductible)); // Use std::move to avoid copying
    }


    void HealthInsurance::setInsuranceName(const std::string& insurance_name) {
		m_insurance_name = insurance_name;
    }


    void HealthInsurance::setInsuranceState(const std::string& state_name) {
		m_state = state_name;
    }


    void HealthInsurance::setInsuranceYear(const std::string& year_in_str) {
		m_year = year_in_str;
    }


    std::string HealthInsurance::getInsuranceName(void) const {
        return m_insurance_name;
    }


    std::string HealthInsurance::getInsuranceState(void) const {
        return m_state;
    }


    std::string HealthInsurance::getInsuranceYear(void) const {
        return m_year;
    }


    float HealthInsurance::getInsuranceMinShare(void) const {
        return m_MIN_SHARE;
    }


    float HealthInsurance::getInsuranceMaxShare(void) const {
        return m_MAX_SHARE;
    }


    float HealthInsurance::getInsuranceMaxShareKid(void) const {
        return m_MAX_SHARE_KID;
    }


    float HealthInsurance::getInsuranceQuota(void) const {
        return m_QUOTA;
    }

} // namespace logic 
