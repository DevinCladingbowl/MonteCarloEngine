#pragma once

// Model class - Governs evolution of underyling asset via a stochastic process.
class Model
{
public:
	virtual ~Model() { ; }
	virtual double Evolve(double currPrice,double dt, double innov) = 0;
	virtual bool IsStochasticVol() = 0;
};