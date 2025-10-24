#pragma once
#include <random>

class MT {
private:
	static std::mt19937 _generator;
	MT() = default;

public:
	static double rand_unif()
	{
		std::uniform_real_distribution<double> dist(0.0, 1.0);
		return dist(_generator);
	}

	static double rand_norm()
	{
		std::normal_distribution<double> dist(0.0, 1.0);
		return dist(_generator);
	}
};