#include "GBM.h"
#include <cmath>
std::pair<double, double> GBM::Evolve(std::pair<double, double> currState, double dt, double spotInnov, double volInnov)
{
	double newSpot = currState.first * std::exp((r_ - 0.5 * vol_ * vol_) * dt + vol_ * spotInnov * std::sqrt(dt));
	return { newSpot, vol_ };
}