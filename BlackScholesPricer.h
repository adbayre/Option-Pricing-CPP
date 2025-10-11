#pragma once
#include "EuropeanVanillaOption.h"
#include <cmath>

class BlackScholesPricer {
private:
	EuropeanVanillaOption* _option;
	double _assetPrice;
	double _interestRate;
	double _volatility;

public:
	BlackScholesPricer(EuropeanVanillaOption* option, double assetPrice, double interestRate, double volatility) :_option(option), _assetPrice(assetPrice), _interestRate(interestRate), _volatility(volatility) {}

	double operator()()const;
	double delta() const;
};