#pragma once
#include "MCEngine.h"
#include <utility>
// Get VS to recognise .tpp files?

template <class Model, class Payoff>
MCEngine<Model, Payoff>::MCEngine(Model& model, Payoff& payoff, int numPaths)
	: model_(std::move(model)), payoff_(std::move(payoff)), numPaths_(numPaths), rng_(std::random_device{}()), dist_(0, 1)
{
	;
}

template <class Model, class Payoff>
double MCEngine<Model, Payoff>::Price()
{
    GenerateInnovations();

	return 1.0;
}

template <class Model, class Payoff>
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

    if (model_.IsStochasticVol())
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
