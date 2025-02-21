#pragma once
#include "MCEngine.h"
#include <utility>
// Get VS to recognise .tpp files?

template <class Model, class Payoff>
MCEngine<Model, Payoff>::MCEngine(Model model, Payoff payoff, int numPaths)
	: model_(std::move(model)), payoff_(std::move(payoff)), numPaths_(numPaths)
{
	;
}

template <class Model, class Payoff>
double MCEngine<Model, Payoff>::Price()
{
	return 1.0;
}

template <class Model, class Payoff>
void MCEngine<Model, Payoff>::GenerateInnovations()
{
	;
}
