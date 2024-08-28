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


namespace bll {

	// Deductible => Franchise
	// Bonus => Primes
	struct Deductible;

	struct Deductible {
		std::string m_bonus_name{ "n/a" };
		std::string m_model_name{ "n/a" }; // can be empty
		float m_deductible_0{ 0.0f };
		float m_deductible_100{ 0.0f };
		float m_deductible_200{ 0.0f };
		float m_deductible_300{ 0.0f };
		float m_deductible_400{ 0.0f };
		float m_deductible_500{ 0.0f };
		float m_deductible_600{ 0.0f };
		float m_deductible_1000{ 0.0f };
		float m_deductible_1500{ 0.0f };
		float m_deductible_2000{ 0.0f };
		float m_deductible_2500{ 0.0f };
		unsigned short int m_age{ 0 };
		unsigned short int m_region{ 0 };
		bool m_accidents_risk{ false };
	};

	class HealthInsurance{
	public:
		// --- option vector ptr --- 
		std::unique_ptr<std::vector<Deductible>> p_deductibles = std::make_unique<std::vector<Deductible>>();


	private:
		// --- option region vector ---
		std::vector<Deductible> m_region_1;
		std::vector<Deductible> m_region_2;

		std::string m_insurance_name{ "n/a" };
		std::string m_state{ "n/a" };
		std::string m_year{ "2024" };
		const float m_MAX_SHARE{ 700.0f };
		const float m_MAX_SHARE_KID{ 350.0f };
		const float m_QUOTA{ 0.1f }; // quote-part 10%

		// --- option age ---
		// age >= 25 years 
		Deductible adults_region_1;
		Deductible adults_region_2;	

		// age >= 18 years && < 25 year
		Deductible young_region_1;
		Deductible young_region_2;

		// age < 18 years
		Deductible kids_region_1;
		Deductible kids_region_2;

	};
} // namespace bll

