#pragma once
#include <iostream>
#include "Option.h"

class BlackScholesMCPricer {
private:
	Option* _option;
	double _initial_price;
	double _interest_rate;
	double _volatility;
	int _nbPaths;
	bool _computed;

public:
	BlackScholesMCPricer(Option* option, double initial_price, double interest_rate, double volatility){}

	int getNbPaths()const
	{
		return _nbPaths;
	}
	double operator()()const;
	void generate(int nb_paths);

	std::vector<double> confidenceInterval()const;
};