#include "EuropeanVanillaOption.h"
#include "BlackScholesPricer.h"
#include <cmath>
#include <stdexcept>

static double N(double x) {
	return 0.5 * std::erfc(-x / std::sqrt(2));
}

double BlackScholesPricer::operator()() const
{
	double S = _assetPrice;
	double K = _option->getStrike();
	double r = _interestRate;
	double T = _option->getExpiry();
	double sigma = _volatility;

	if (T <= 0) throw std::invalid_argument("Expiry must be positive");
	if (sigma <= 0) throw std::invalid_argument("Volatilité must be positive");

	double d1 = (std::log(S / K) + T * (r + 0.5 * sigma * sigma)) / (sigma * std::sqrt(T));
	double d2 = d1 - sigma * std::sqrt(T);

	if (_option->getOptionType() == EuropeanVanillaOption::OptionType::Call)
		return S * N(d1) - K * std::exp(-r * T) * N(d2);
	else
		return K * std::exp(-r * T) * N(-d2) - S * N(-d1);
}


double BlackScholesPricer::delta() const
{
	double S = _assetPrice;
	double K = _option->getStrike();
	double r = _interestRate;
	double T = _option->getExpiry();
	double sigma = _volatility;

	double d1 = (std::log(S / K) + T * (r + 0.5 * sigma * sigma)) / (sigma * std::sqrt(T));

	if (_option->getOptionType() == EuropeanVanillaOption::OptionType::Call)
		return N(d1);
	else
		return N(d1) - 1;
}
