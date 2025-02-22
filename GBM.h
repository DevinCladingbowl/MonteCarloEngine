#pragma once
#include <utility>

//Geometric Brownian Motion - Models underlying asset according to
/*
	dS_t = rS_tdt + \sigma S_t dW_t
*/
// For constant r and \sigma (risk free rate and volatility).
class GBM
{
public:
	GBM(double rate, double vol) : r_(rate), vol_(vol) { ; }

	std::pair<double,double> Evolve(std::pair<double, double> currState, double dt, double spotInnov, double volInnov); // Doesn't actually use volInnov.

	bool IsStochasticVol() { return false; }
private:
	double r_;       // Risk-free rate
	double vol_;     // Constant vol

};