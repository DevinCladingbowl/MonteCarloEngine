#pragma once
#include <vector>
#include <random>
#include <cmath>
#include <concepts>
#include <utility>

// MODEL CONCEPTS - Each model that uses the MCEngine must implement the below
template <class Model>
concept HasEvolve = requires(Model model, std::pair<double, double> currState, double dt, double spotInnov, double volInnov) {
	{ model.Evolve(currState, dt, spotInnov, volInnov) } -> std::convertible_to<std::pair<double, double>>;
};

template <class Model>
concept HasIsStochastic = requires(Model model) {
	{ model.IsStochasticVol() } -> std::convertible_to<bool>;
};

// COMBINED MODEL CONCEPTS
template <typename T>
concept ValidModel = HasEvolve<T> && HasIsStochastic<T>;

// PAYOFF CONCEPTS - Each Payoff that uses the MCEngine must implement the below
template <class Payoff>
concept HasGetPayoff = requires(Payoff payoff, double spot) {
	{ payoff.GetPayoff(spot) } -> std::convertible_to<double>;
};

template <class Payoff>
concept HasGetMaturity = requires(Payoff payoff) {
	{ payoff.GetMaturity() } -> std::convertible_to<int>;
};

// COMBINED PAYOFF CONCEPTS
template <class Payoff>
concept ValidPayoff = HasGetPayoff<Payoff> && HasGetMaturity<Payoff>;

template <ValidModel Model, ValidPayoff Payoff>
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
#include "MCEngine.cpp"