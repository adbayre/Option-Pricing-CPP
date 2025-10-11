#pragma once
#include "EuropeanVanillaOption.h"

class CallOption : public EuropeanVanillaOption {

public:
	CallOption(double expiry, double strike) :EuropeanVanillaOption(expiry, strike) {}

	double payoff(double underlyingPrice) const override {
		return (underlyingPrice > getStrike()) ? (underlyingPrice - getStrike()) : 0.0;
	}

	OptionType getOptionType() const override {
		return OptionType::Call;
	}
};