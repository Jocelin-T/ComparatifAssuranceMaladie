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


		// @brief Sets the deductible value at the specified index for the current deductible object.
		//
		// @param index  (const uint16_t)	=> The index of the deductible value to be set (0-based).
		// @param value  (const float)		=> The new value to be assigned to the specified index.
		//
		// @return (void)					=> This function does not return a value.
		//
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
} // namespace logic

