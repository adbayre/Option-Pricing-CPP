#pragma once
#include "Option.h"

class EuropeanVanillaOption : public Option {
private:
	double _strike;

public:
	enum class OptionType { Call, Put };
	EuropeanVanillaOption(double expiry, double strike) : Option(expiry) {
		if (expiry < 0) {
			throw std::invalid_argument("Expiry cannot be negative");
		}
		_strike = strike;
	}

	double getStrike()const
	{
		return _strike;
	}
	virtual OptionType getOptionType() const = 0; 
	virtual ~EuropeanVanillaOption() = default;
};