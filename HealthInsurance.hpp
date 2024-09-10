/*****************************************************************//**
 * @file   HealthInsurance.h
 * @brief  Base Class for any health insurance.
 * 
 * @author ThJo
 * @date   14 August 2024
 *********************************************************************/
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <memory>


namespace logic {

	// Deductible => Franchise
	// Bonus => Primes

	struct Deductible {
		std::string m_bonus_name{ "n/a" };
		std::string m_model_name{ "n/a" }; // can be empty
		float m_deductible_1{ 0.0f };
		float m_deductible_2{ 0.0f };
		float m_deductible_3{ 0.0f };
		float m_deductible_4{ 0.0f };
		float m_deductible_5{ 0.0f };
		float m_deductible_6{ 0.0f };
		unsigned short int m_age{ 0 };
		unsigned short int m_region{ 0 };
		bool m_accidents_risk{ false };
	};



	class HealthInsurance{
	public:
		// --- option vector ptr --- 
		std::unique_ptr<std::vector<Deductible>> m_p_deductibles = 
			std::make_unique<std::vector<Deductible>>();

		std::string getInsuranceName() const {
			return m_insurance_name;
		}


	private:

		std::string m_insurance_name{ "n/a" };
		std::string m_state{ "n/a" };
		std::string m_year{ "2024" };
		const float m_MAX_SHARE{ 700.0f };
		const float m_MAX_SHARE_KID{ 350.0f };
		const float m_QUOTA{ 0.1f }; // quote-part 10%
	};
} // namespace logic

