#include "GBM.h"
#include <cmath>
double GBM::Evolve(double currPrice, double dt, double innov)
{
	return currPrice * std::exp((r_ - 0.5 * vol_ * vol_) * dt + vol_ * innov * std::sqrt(dt));
}