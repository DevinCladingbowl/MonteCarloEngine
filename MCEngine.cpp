#pragma once
#include "MCEngine.h"
#include <utility>
#include <numeric>
#include <omp.h>
template <ValidModel Model, ValidPayoff Payoff>
MCEngine<Model, Payoff>::MCEngine(Model& model, Payoff& payoff, int numPaths)
	: model_(model), payoff_(payoff), numPaths_(numPaths), rng_(std::random_device{}()), dist_(0, 1)
{
	numTimes_ = payoff.GetMaturity() + 1;
}

template <ValidModel Model, ValidPayoff Payoff>
double MCEngine<Model, Payoff>::Price()
{
    GenerateInnovations();
    
    std::vector<std::vector<double>> paths(numPaths_, std::vector<double>(numTimes_));
    std::vector<double> payoffs(numPaths_);

    // If set up for paralleliation ensure all vectors are assigned memory first, and watch for thread unsafe behaviour.
    //#pragma omp parallel for
    for (int path = 0; path < numPaths_; ++path) {
        std::pair<double, double> currentState = {100,0.3};
        double prevTime = 0;

        for (int time = 0; time < numTimes_; ++time) {
            double spotInnov = innovations_[path][time];
            double volInnov = volInnovations_[path][time];
            double dt = (time - prevTime) / 365;

            currentState = model_.Evolve(currentState, dt, spotInnov, volInnov);
            if (false)
            {
                paths[path][time] = currentState.first;
            }
            
            //std::cout << currentPrice << '\n';
            if (time == payoff_.GetMaturity())
            {
                payoffs.push_back(payoff_.GetPayoff(currentState.first));
            }

            prevTime = time;
        }
    }

    double avgPayoff = std::accumulate(payoffs.begin(), payoffs.end(), 0.0) / numPaths_;

	return avgPayoff;
}

template <ValidModel Model, ValidPayoff Payoff>
void MCEngine<Model, Payoff>::GenerateInnovations()
{
    // Pre-generate all innovations upfront
    innovations_.assign(numPaths_, std::vector<double>(numTimes_));
    volInnovations_.assign(numPaths_, std::vector<double>(numTimes_));

    // Generate asset innovations
    for (auto& path : innovations_)
    {
        std::generate(path.begin(), path.end(), [this]() { return dist_(rng_); });
    }

    if (!model_.IsStochasticVol())
    {
        // If volatility is deterministic, just use the same vector
        volInnovations_ = innovations_;
    }
    else
    {
        // Generate separate volatility innovations for stochastic models (E.g heston)
        for (auto& path : volInnovations_)
        {
            std::generate(path.begin(), path.end(), [this]() { return dist_(rng_); });
        }
    }
}
