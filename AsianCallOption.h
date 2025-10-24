#pragma once
#include <stdexcept>
#include "AsianOption.h"
#include <vector>

class AsianCallOption : public AsianOption {
private:
	double _strike;

public:
	AsianCallOption(double expiry, std::vector<double> timeSteps, double strike): AsianOption(expiry, timeSteps), _strike(strike){}

	double payoff(double underlyingPrice)const override
	{
		return(underlyingPrice > _strike) ? (underlyingPrice - _strike) : 0.0;
	}
};