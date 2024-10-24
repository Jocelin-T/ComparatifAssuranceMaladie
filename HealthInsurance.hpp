/*****************************************************************//**
 * @file   HealthInsurance.h
 * @brief  Base Class for any health insurance.
 *
 * @author ThJo
 * @date   14 August 2024
 *********************************************************************/
#pragma once
#include <string>
#include <vector>

#include "Typedef.hpp"
#include "Globals.hpp"


namespace logic {

	// Deductible => Franchise
	// Bonus => Primes

	class Deductible {
	public:

		void displayDeductible(void) const;

		// Setter
		void setDeductibleBonusName(const std::string& bonus_name);
		void setDeductibleModelName(const std::string& model_name);
		void setDeductibleAgeCategory(const std::string& age_category);
		void setDeductibleValues(const uint16_t index, const float value);
		void setDeductibleRegion(const uint16_t region);
		void setDeductibleAccidentRisk(const bool accidents_risk);

		// Getter
		std::string getDeductibleBonusName(void) const;
		std::string getDeductibleModelName(void) const;
		std::string getDeductibleAgeCategory(void) const;
		float getDeductibleValue(const uint16_t index) const;
		uint16_t getDeductibleRegion(void) const;
		bool getDeductibleAccidentRisk(void) const;

	private:
		std::string m_bonus_name{ "n/a" };
		std::string m_model_name{ "n/a" }; // can be empty
		std::string m_age_category{ "n/a" };
		float m_deductible_values[glb::NBR_VALUES_PER_DEDUCTIBLE]{ 0.0f };
		uint16_t m_region{ 0 };
		bool m_accidents_risk{ false };
	};



	class HealthInsurance {
	public:

		HealthInsurance(void);

		std::vector<Deductible> m_deductibles;

		// Push one deductible to the std::vector
		void addDeductibleToInsurance(Deductible& deductible);

		// Setter
		void setInsuranceName(const std::string& insurance_name);
		void setInsuranceState(const std::string& state_name);
		void setInsuranceYear(const std::string& year_in_str);

		// Getter
		std::string getInsuranceName(void) const;
		std::string getInsuranceState(void) const;
		std::string getInsuranceYear(void) const;
		float getInsuranceMinShare(void) const;
		float getInsuranceMaxShare(void) const;
		float getInsuranceMaxShareKid(void) const;
		float getInsuranceQuota(void) const;

	private:

		std::string m_insurance_name{ "n/a" };
		std::string m_state{ "n/a" };
		std::string m_year{ "2024" };
		const float m_MIN_SHARE{ 0.0f };
		const float m_MAX_SHARE{ 700.0f };
		const float m_MAX_SHARE_KID{ 350.0f };
		const float m_QUOTA{ 0.1f }; // quote-part 10%
	};
} // namespace logic

