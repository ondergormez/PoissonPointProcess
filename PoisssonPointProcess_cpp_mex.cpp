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
#include <chrono>

/*
 * Coder Created Header Files 
 */
#include "PoissonPointProcess.hpp"

/*
 * Third Party Header Files 
 */
#include "mex.h"

/*
 * Using Declerations
 */
using namespace std;

/*
 * Global Defitions
 */

// int main()
// {
//     PoissonPointProcess::Compute();
// }

// mexFunction
void mexFunction
(
        int       nlhs ,
        mxArray * plhs[] ,
        int       nrhs ,
  const mxArray * prhs[]
)
{
#ifndef NDEBUG
    cout << "*******************************************************************************************************" << endl;
    cout << "**************************This is the Poisson Point Process Mex Function call**************************" << endl;
    cout << "*******************************************************************************************************" << endl;
    auto start = chrono::steady_clock::now();
#endif

    PoissonPointProcess::Compute();

#ifndef NDEBUG
    auto end = chrono::steady_clock::now();
    cout << "*******************************************************************************************************" << endl;
    cout << "*************************************Computation Time Informations*************************************" << endl;
    cout << "*******************************************************************************************************" << endl;

    cout << endl << "Elapsed time in nanoseconds : " 
        << chrono::duration_cast<chrono::nanoseconds>(end - start).count()
        << " ns" << endl;

    cout << "Elapsed time in microseconds : " 
        << chrono::duration_cast<chrono::microseconds>(end - start).count()
        << " µs" << endl;

    cout << "Elapsed time in milliseconds : " 
        << chrono::duration_cast<chrono::milliseconds>(end - start).count()
        << " ms" << endl;

    cout << "Elapsed time in seconds : " 
        << chrono::duration_cast<chrono::seconds>(end - start).count()
        << " sec" << endl << endl;
    cout << "*******************************************************************************************************" << endl;
    cout << "********************************Poisson Point Process Mex Function ended*******************************" << endl;
    cout << "*******************************************************************************************************" << endl;
#endif
}