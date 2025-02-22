#pragma once
#include <utility>

//Heston - Models underlying asset according to
/*
    dS_t = rS_tdt + sqrt(\nu_t) S_t dW_t
    d\nu_t = 
*/
// For constant r and \sigma (risk free rate and volatility).
class HestonModel
{
public:
    HestonModel(double rate, double kappa, double theta, double sigma, double rho, double initialVol) :
        r_(rate), kappa_(kappa), theta_(theta), sigma_(sigma), rho_(rho), v0_(initialVol) 
    {
        ;
    }

    std::pair<double, double> Evolve(std::pair<double, double> currState, double dt, double spotInnov, double volInnov);

    bool IsStochasticVol() { return true; }

private:
    double r_;       // Risk-free rate
    double kappa_;   // Mean-reversion speed
    double theta_;   // Long-run variance
    double sigma_;   // Volatility of volatility
    double rho_;     // Correlation between asset and volatility
    double v0_;      // Initial volatility
};