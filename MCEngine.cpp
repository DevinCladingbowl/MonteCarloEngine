#pragma once
#include "MCEngine.h"
#include <utility>
#include <numeric>

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

    for (int path = 0; path < numPaths_; ++path) {
        double currentPrice = 100;
        double prevTime = 0;

        for (int time = 0; time < numTimes_; ++time) {
            double innov = innovations_[path][time];
            double dt = (time - prevTime) / 365;

            currentPrice = model_.Evolve(currentPrice, dt, innov);
            if (true)
            {
                paths[path][time] = currentPrice;
            }
            
            //std::cout << currentPrice << '\n';
            if (time == payoff_.GetMaturity())
            {
                payoffs.push_back(payoff_.GetPayoff(currentPrice));
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
    innovations_.resize(numPaths_);
    for (int i = 0; i < numPaths_; ++i)
    {
        innovations_[i].resize(numTimes_);

        for (int t = 0; t < numTimes_; ++t) 
        {
            innovations_[i][t] = dist_(rng_);
        }
    }

    if (model_.IsStochasticVol()) //Does not account for correlation.
    {
        volInnovations_.resize(numPaths_);
        for (int i = 0; i < numPaths_; ++i)
        {
            volInnovations_[i].resize(numTimes_);

            for (int t = 0; t < numTimes_; ++t)
            {
                volInnovations_[i][t] = dist_(rng_);
            }
        }
    }
}
