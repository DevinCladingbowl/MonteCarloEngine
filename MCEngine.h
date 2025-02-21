#pragma once
#include <vector>
template <class Model, class Payoff>
class MCEngine
{
public:
	MCEngine(Model model, Payoff payoff, int numPaths);

	double Price();

protected:
	void GenerateInnovations(); //Generating the innovations (random variables) used in MC simulation.

private:
	Model& model_;
	Payoff& payoff_;
	int numPaths_;
	std::vector<std::vector<double>> innovations_; 
};
