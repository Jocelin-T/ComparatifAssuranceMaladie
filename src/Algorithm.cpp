#include "Algorithm.hpp"
#include "Config.hpp"

#include <iostream>


namespace algo {

	static float calculateAnnualTotalFee(const float user_prediction_fee, const float user_share, const uint16_t matching_id);
	static float calculateShare(const AlgorithmParameters& params);
	static uint16_t findBestDeductibleIDMatchingIndex(const float user_prediction_fee,const float user_share);
	static uint16_t findBestDeductibleMatchingIndex(const float user_prediction_fee, const float user_share); // FIX: Not used


	AlgorithmParameters& setAlgorithmParameters(
		const float user_prediction_fee,
		const uint16_t user_region,
		const uint16_t user_age,
		const bool user_accident) {

		AlgorithmParameters params;

		params.user_choosed_prediction_fee = user_prediction_fee;
		params.user_choosed_region = user_region;
		params.user_choosed_age = user_age;
		params.user_choosed_accident = user_accident;

		return params;
	}


	void clearAlgorithmArrays(void) {
		for (uint16_t i{ 0 }; i < ALGO_MAX_ENTRIES; i++) {
			contributions_matching[i] = 0.0f;
			deductibles_ids_matching[i] = 0;
			deductibles_matching[i] = 0;
		}
	}


	// Return the ID of the best insurance
	uint16_t runAlgorithm(const AlgorithmParameters& params) {

#if DEBUG
		for (uint16_t i{ 0 }; i < ALGO_MAX_ENTRIES; i++) {

			if (deductibles_ids_matching[i] == 0) {
				continue;
			}

			std::cout << i
				<< " - ID: " << deductibles_ids_matching[i]
				<< " Data: " << contributions_matching[i]
				<< " Deductible: " << deductibles_matching[i]
				<< '\n';
		}
#endif // DEBUG

		float user_prediction_fee{ params.user_choosed_prediction_fee };
		float user_share{ calculateShare(params) };

		return deductibles_ids_matching[
			findBestDeductibleIDMatchingIndex(
				user_prediction_fee,
				user_share
			)
		];
	}


	float calculateAnnualTotalFee(const float user_prediction_fee, const float user_share, const uint16_t matching_id) {

		// FIX: ?? Wrong calculation ??
		float annual_fee{
			(user_prediction_fee <= deductibles_matching[matching_id] ? user_prediction_fee : deductibles_matching[matching_id])
			+ user_share + (contributions_matching[matching_id] * 12)
		};

#if DEBUG
		std::cout << matching_id
			<< " Annual fee: " << annual_fee
			<< " (" << (user_prediction_fee < deductibles_matching[matching_id] ? user_prediction_fee : deductibles_matching[matching_id])
			<< " + " << user_share << " + " << (contributions_matching[matching_id] * 12) << ")"
			<< " at index: " << matching_id
			<< '\n';
#endif // DEBUG

		return annual_fee;
	}


	// Return the share if under the max_share
	float calculateShare(const AlgorithmParameters& params) {

		float share{ params.user_choosed_prediction_fee * global::QUOTA };

#if DEBUG
		std::cout << "Share found: " << share << " for: " << params.user_choosed_prediction_fee << '\n';
#endif // DEBUG

		if (share >= global::MAX_SHARE) {
			return global::MAX_SHARE;
		}

		return share;
	}


	uint16_t findBestDeductibleIDMatchingIndex(
		const float user_prediction_fee,
		const float user_share) {

		uint16_t deductible_id_matching_index{ 999 };
		float lowest_fee{ 999'999.99f };

		for (uint16_t i{ 0 }; i < ALGO_MAX_ENTRIES; i++) {

			if (deductibles_ids_matching[i] == 0) {
				continue;
			}

			float calculated_fee{ calculateAnnualTotalFee(user_prediction_fee, user_share, i) };

			if (calculated_fee < lowest_fee) {
				lowest_fee = calculated_fee;
				deductible_id_matching_index = i;
			}

#if DEBUG
			std::cout << i << " Lowest fee: " << lowest_fee << " at index: " << deductible_id_matching_index << '\n';
#endif // DEBUG
		}

		array_matching_id = deductible_id_matching_index; // Global variable
		return deductible_id_matching_index;
	}


	// Calculate the best insurance if the value given by the user is over the lowest deductible
	uint16_t findBestDeductibleMatchingIndex(const float user_prediction_fee, const float user_share) {

		// user_prediction_fee is too low
		if (user_prediction_fee <= global::DEDUCTIBLES_POSSIBLE[0] + user_share) {
#if DEBUG
			std::cout << "Lowest than the min deductible + max share\n";
#endif // DEBUG
			return 0;
		}

		// user_prediction_fee is too high
		if (user_prediction_fee >= global::DEDUCTIBLES_POSSIBLE[global::NBR_DEDUCTIBLES_PER_INSURANCE - 1] + user_share) {

#if DEBUG
			std::cout << "Highest than the max deductible + max share\n";
#endif // DEBUG
			return global::NBR_DEDUCTIBLES_PER_INSURANCE - 1;
		}

		// Find the highest deductible + share possible
		for (uint16_t i{ 0 }; i < global::NBR_DEDUCTIBLES_PER_INSURANCE; i++) {

			float fee{ user_prediction_fee };
#if DEBUG
			std::cout << "-----------------------------------------------\n";
			std::cout << "User max fee: " << fee << '\n';
#endif // DEBUG

			fee -= global::DEDUCTIBLES_POSSIBLE[i];
#if DEBUG
			std::cout << i << " Max fee -deductible(-" << global::DEDUCTIBLES_POSSIBLE[i] << "): " << fee << '\n';
#endif // DEBUG

			if (fee < 0) {
#if DEBUG
				std::cout << i << " >>>> Break at: " << fee << " Deductible: " << global::DEDUCTIBLES_POSSIBLE[i] << '\n';
#endif // DEBUG
				return i == 0 ? 0 : i - 1;
			}

			fee -= user_share;
#if DEBUG
			std::cout << i << " Max fee -deductible(-" << global::DEDUCTIBLES_POSSIBLE[i]
				<< ") & -user_share(-" << user_share << "): "
				<< fee << '\n';
#endif // DEBUG

			if (fee < 0 || i == global::NBR_DEDUCTIBLES_PER_INSURANCE - 1) {
#if DEBUG
				std::cout << i << " >>>> Break at: " << fee << " Deductible: " << global::DEDUCTIBLES_POSSIBLE[i] << '\n';
#endif // DEBUG
				return i == 0 ? 0 : i - 1;
			}
		}

		return global::NBR_DEDUCTIBLES_PER_INSURANCE - 1;
	}

} // namespace algo
