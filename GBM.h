#pragma once
#include "Model.h"

//Geometric Brownian Motion - Models underlying asset according to
/*
	dS_t = rS_tdt + \sigma S_t dW_t
*/
// For constant r and \sigma (risk free rate and volatility).
class GBM : Model
{
public:
	GBM(double rate, double vol) : r_(rate), vol_(vol) { ; }

	double Evolve(double currPrice, double dt, double innov) override;

	bool IsStochasticVol() override { return false; }
private:
	double r_;
	double vol_;

};