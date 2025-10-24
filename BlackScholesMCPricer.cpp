#include "BlackScholesMCPricer.h"
#include "MT.h"

BlackScholesMCPricer::BlackScholesMCPricer(Option* option, double initial_price, double interest_rate, double volatility): _option(option),_initial_price(initial_price), _interest_rate(interest_rate), _volatility(volatility){}

void generate(int nb_paths) 
{

}
