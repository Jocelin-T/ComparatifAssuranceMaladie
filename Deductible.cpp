#include "Deductible.hpp"
#include "Config.hpp"

#include <iostream>

namespace logic {

    void Deductible::displayDeductible(void) const {
        std::cout << "Bonus name: " << m_bonus_name << '\n';
        std::cout << "Model name: " << m_model_name << '\n';
        std::cout << "Age category: " << m_age_category << '\n';
        for (uint16_t i{ 0 }; i < glb::NBR_VALUES_PER_DEDUCTIBLE; i++) {
            std::cout << "Deductibles values: " << m_deductible_values[i] << '\n';
        }
        std::cout << "Region: " << m_region << '\n';
        std::cout << "Accidents risk: " << (m_accidents_risk ? "Yes" : "No") << '\n';
    }


    void Deductible::setDeductibleBonusName(const std::string& bonus_name) {
        m_bonus_name = bonus_name;
    }


    void Deductible::setDeductibleModelName(const std::string& model_name) {
        m_model_name = model_name;
    }


    void Deductible::setDeductibleAgeCategory(const std::string& age_category) {
        m_age_category = age_category;
    }


    void Deductible::setDeductibleValues(const uint16_t index, const float value) {
        m_deductible_values[index] = value;
    }


    void Deductible::setDeductibleRegion(const uint16_t region) {
        m_region = region;
    }


    void Deductible::setDeductibleAccidentRisk(const bool accidents_risk) {
        m_accidents_risk = accidents_risk;
    }

    std::string Deductible::getDeductibleBonusName(void) const {
        return m_bonus_name;
    }

    std::string Deductible::getDeductibleModelName(void) const {
        return m_model_name;
    }

    std::string Deductible::getDeductibleAgeCategory(void) const {
        return m_age_category;
    }

    float Deductible::getDeductibleValue(const uint16_t index) const {
        return m_deductible_values[index];
    }

    uint16_t Deductible::getDeductibleRegion(void) const {
        return m_region;
    }

    bool Deductible::getDeductibleAccidentRisk(void) const {
        return m_accidents_risk;
    }

} // namespace logic 