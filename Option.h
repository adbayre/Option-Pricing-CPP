#pragma once
#include <stdexcept>

class Option {
private:
	double _expiry;

public:
	Option(double expiry) {
		if (expiry < 0)
		{
			throw std::invalid_argument("Expiry cannot be negative");
		}
		_expiry = expiry;
	}

	double getExpiry()const {
		return _expiry;
	}

	virtual double payoff(double underlyingPrice) const = 0;

	virtual ~Option() = default;
};