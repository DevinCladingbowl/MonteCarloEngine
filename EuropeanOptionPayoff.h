#pragma once
#include <algorithm>
class EuropeanOptionPayoff
{
public:

	enum class CallPut {Call, Put};
	EuropeanOptionPayoff(double strike, int maturity, CallPut callPut) : strike_(strike), maturity_(maturity), callPut_(callPut) { ; }

	int GetMaturity() { return maturity_; }

	double GetPayoff(double spot)
	{
		double payoff = callPut_ == CallPut::Call ? std::max(spot - strike_, 0.0) : std::max(strike_ - spot, 0.0);
		return payoff;
	}
		
private:
	double strike_;
	int maturity_;
	CallPut callPut_;
};