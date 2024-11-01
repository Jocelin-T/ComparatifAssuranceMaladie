#include "Algorithm.hpp"

// Calcul frais annuel potentiel = 5000 CHF
// Min: 5000 / 12 = 416 CHF
//		Check pour les primes en dessous de 416
//		Check quelle est la franchise la plus basse

// Mid:

// Max: (5000 - 700(quote-part) - 300(franchise la plus basse)) / 12
//		Check si c'est possible avec une franchise supérieur

namespace algo {

	float user_choosed_maximum_fee{ 0.0f };
	uint16_t user_choosed_region{ 999 };
	uint16_t user_choosed_age{ 999 };


	void runAlgorithm(const float user_fee, const uint16_t user_region, const uint16_t user_age) {
		setAlgorithmParameters(user_fee, user_region, user_age);
	}


	void setAlgorithmParameters(const float user_fee, const uint16_t user_region, const uint16_t user_age) {
		user_choosed_maximum_fee = user_fee;
		user_choosed_region = user_region;
		user_choosed_age = user_age;
	}


	void algorithmTest(void) {

	}

} // namespace algo
