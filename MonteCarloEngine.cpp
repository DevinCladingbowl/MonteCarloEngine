// MonteCarloEngine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "MCEngine.h"
#include "GBM.h"
#include "EuropeanOptionPayoff.h"
#include <iostream>
#include <cmath>
#include <chrono>
int main()
{
    GBM gbm(0.2, 0.3);
    EuropeanOptionPayoff payoff(105, 365, EuropeanOptionPayoff::CallPut::Call);
    MCEngine<GBM, EuropeanOptionPayoff> mcEngine(gbm, payoff, 100000);

    auto t1 = std::chrono::high_resolution_clock::now();
    double price = mcEngine.Price();
    auto t2 = std::chrono::high_resolution_clock::now();

    auto ms_int = duration_cast<std::chrono::milliseconds>(t2 - t1);

    std::cout << "Time taken " << ms_int << '\n';
       
    std::cout << "Price " << price * std::exp(-0.2);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
