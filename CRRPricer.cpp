#include "CRRPricer.h"
#include <iostream>
#include <cmath>
#include <numeric>
#include <algorithm>
#include <stdexcept>

void CRRPricer::checkArbitrage()const {
	if(!((_down < _rate)&&(_rate < _up))) throw std::invalid_argument ("Arbitrage détecté; il faut D < R < U");
}

CRRPricer::CRRPricer(EuropeanVanillaOption* option, int depth, double up, double assetPrice, double down, double rate)
	: _option(option), _depth(depth), _up(up), _down(down), _rate(rate), _assetPrice(assetPrice), _computed(false)
{
	if (option->isAsianOption())
	{
		throw std::invalid_argument ("A CRR Cannot be an asian option!");
	}
	checkArbitrage();
	_tree.setDepth(depth);
}

void CRRPricer::compute() const
{
	if (_computed) return;

	double q = (_rate - _down) / (_up - _down);


	//starting value
	for (int i = 0; i <= _depth; i++)
	{
		double S = _assetPrice * std::pow(1 + _up, i) * std::pow(1 + _down, _depth - i);
		_tree.setNode(_depth, i, _option->payoff(S));
	}

	//remopontée de l'arbre
	for (int n = _depth - 1; n >= 0; n--)  // commencer à _depth-1
	{
		for (int i = 0; i <= n; i++)
		{
			double H_next_up = _tree.getNode(n + 1, i + 1);
			double H_next_down = _tree.getNode(n + 1, i);
			double H = ((q * H_next_up) + (1 - q) * H_next_down) / (1 + _rate);

			_tree.setNode(n, i, H);
		}
	}


	_computed = true;
}

double CRRPricer::get(int n, int i)const
{
	return _tree.getNode(n, i);
}

double CRRPricer::operator()(bool closed_form) const
{
	if (closed_form)
	{
		double price = 0.0;
		double q = (_rate - _down) / (_up - _down);

		for (int i = 0; i <= _depth; i++)
		{
			double comb = 1;
			for (int k = 0; k < i; k++)
			{
				comb *= (_depth - k) / double(k + 1);
			}
			double S = _assetPrice * std::pow(1 + _up, i) * std::pow(1 + _down, _depth - i);
			price += comb * std::pow(q, i) * std::pow(1 - q, _depth - i) * _option->payoff(S);
		}
		return price / std::pow(1 + _rate, _depth);
	}
	else {
		compute();
		return _tree.getNode(0, 0);
	}
}
