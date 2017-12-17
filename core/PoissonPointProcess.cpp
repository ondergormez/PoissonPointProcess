/**
 * Copyright (C) 2017 Önder Görmez

 * This program is free software: you can redistribute it and/or modify it under the terms of the GNU General
 * Public License as published by the Free Software Foundation, either version 3 of the License, or (at your 
 * option) any later version. This program is distributed in the hope that it will be useful, but WITHOUT ANY 
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the 
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License along with this program. If not, see 
 * http://www.gnu.org/licenses/.

 * For any questions, please contact me @ ondergormez@gmail.com.
 */

/*
 * Standart Header Files
 */
#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <random>

/*
 * Coder Created Header Files 
 */
#include "PoissonPointProcess.hpp"

/*
 * Using Declerations
 */
using namespace std;

/*
 * Global Defitions
 */

/*
 * Constructor
 */
PoissonPointProcess::PoissonPointProcess()
{

}

/*
 * Destructer
 */
PoissonPointProcess::~PoissonPointProcess()
{

}

/*
 * Compute
 * So the PDF is f(t) = -L*exp(-Lt), and the 
 * CDF is F(t) = Prob(T < t) = 1 - exp(-Lt).
 */
void PoissonPointProcess::Compute(void)
{
	std::random_device rd;
    std::mt19937 gen(rd());
 
    // if an event occurs 4 times a minute on average
    // how often is it that it occurs n times in one minute?
    std::poisson_distribution<> d(4);
    int L = 100;
    double cdf = 1 - exp(-L*4);
        std::cout << "CDF value = " << cdf << '\n';
        
    double pdf = -L * exp(-L*4);
        std::cout << "PDF value = " << pdf << '\n';
     
    std::map<int, int> hist;
    for(int n=0; n<10000; ++n) {
        ++hist[d(gen)];
    }
    for(auto p : hist) {
        std::cout << p.first <<
                ' ' << std::string(p.second/100, '*') << '\n';
    }
}

