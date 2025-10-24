#pragma once
#include <vector>
#include "Option.h"
#include <numeric>

class AsianOption : public Option {
private:
	std::vector<double> _timeSteps;

public:
	AsianOption(double expiry, const std::vector<double>& timeSteps):Option(expiry), _timeSteps(timeSteps){}

	const std::vector<double>& getTimeSteps()const
	{
		return _timeSteps;
	}

	double payoffPath(const std::vector<double>& path)const
	{
		if (path.empty())
		{
			throw std::invalid_argument("The path is empty (impossible!!)");
		}
		else
		{
			double sum = std::accumulate(path.begin(), path.end(), 0.0);
			double mean = sum / path.size();
			return payoff(mean);
		}
	}
	bool isAsianOption() const
	{
		return true;;
	}
};