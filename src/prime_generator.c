#include "prime_generator.h"


static bool is_prime(const int x) {
	if (x < 4) { return false; }
	if (x % 2 == 0) { return false; }
	//Modified brute force check for primes; checks if x is divisible by odds
	for (int i = 3; i < floor(sqrt((double)x)); i += 2) {
		if (x % i == 0) {
			return false;
		}
	}

	return true;
}

int next_prime(int x) {

	while (!is_prime(x)) {
		x++;
	}
	return x;
}