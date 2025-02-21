#pragma once
#include <vector>
#include <random>
#include <cmath>
template <class Model, class Payoff>
class MCEngine
{
public:
	MCEngine(Model& model, Payoff& payoff, int numPaths);

	double Price();

protected:
	void GenerateInnovations(); //Generating the innovations (random variables) used in MC simulation.

private:
	Model& model_;
	Payoff& payoff_;
	int numPaths_;
	int numTimes_; // Days for now. TODO Update to use dates.
	std::mt19937 rng_;
	std::normal_distribution<double> dist_;
	std::vector<std::vector<double>> innovations_; 
	std::vector<std::vector<double>> volInnovations_; 
};
