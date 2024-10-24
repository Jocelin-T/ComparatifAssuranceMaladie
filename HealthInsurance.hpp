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

	class Deductible;

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

