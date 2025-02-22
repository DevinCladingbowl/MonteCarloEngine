#include "HestonModel.h"
#include <cmath>
std::pair<double, double> HestonModel::Evolve(std::pair<double, double> currState, double dt, double spotInnov, double volInnov)
{	
	double currSpot = currState.first;
	double currVol = currState.second;

	double dW_v = volInnov * std::sqrt(dt);
	double dW_s = rho_ * dW_v + std::sqrt(1 - rho_ * rho_) * spotInnov * std::sqrt(dt);

	double sqrtCurrVol = std::sqrt(std::max(currVol, 0.0001)); // for numerical stability

	double dS = r_ * currSpot * dt + sqrtCurrVol * currSpot * dW_s;
	double dV = kappa_ * (theta_ - currVol) * dt + sigma_ * sqrtCurrVol * dW_v;


	return { currSpot + dS, std::max(currVol + dV, 0.0001) };
}