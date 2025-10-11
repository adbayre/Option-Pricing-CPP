#pragma once
#include "EuropeanVanillaOption.h"

class PutOption : public EuropeanVanillaOption {
public:
	PutOption(double expiry, double strike) :EuropeanVanillaOption(expiry, strike) {}

	double payoff(double underlyingPrice) const override {
		return (getStrike() > underlyingPrice) ? (getStrike() - underlyingPrice) : 0.0;
	}

	OptionType getOptionType()const override {
		return OptionType::Put;
	}
};