#pragma once
#include "AsianOption.h"
#include <vector>

class AsianPutOption : public AsianOption {

private:
	double _strike;
public:
	AsianPutOption(double expiry, std::vector<double> timeSteps, double strike):AsianOption(expiry, timeSteps), _strike(strike){}

	double payoff(double underlyingPrice)const override
	{
		return(underlyingPrice < _strike) ? (_strike - underlyingPrice) : 0.0;
	}
};