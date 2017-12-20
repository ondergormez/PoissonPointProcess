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
# include <iostream>
# include <fstream>
# include <iomanip>
# include <cmath>
# include <ctime>
# include <cstring>
#include <chrono>
#include <list>
#include <utility>

/*
 * Coder Created Header Files 
 */

/*
 * Third Party Header Files 
 */
#include "mex.h"
#include "poisson_simulation_prb.hpp"

/*
 * Using Declerations
 */
using namespace std;

/*
 * Global Defitions
 */
//This section was taken to the link below

// int main()
// {
//     PoissonPointProcess::Compute();
// }

/*
 * mexFunction is the user-defined C routine that is called upon invocation
 * of a MEX-function.
 */
void mexFunction(
    int           nlhs,           /* number of expected outputs */
    mxArray       *plhs[],        /* array of pointers to output arguments */
    int           nrhs,           /* number of inputs */
    const mxArray *prhs[]         /* array of pointers to input arguments */
)
{
#ifndef NDEBUG
    cout << "*******************************************************************************************************" << endl;
    cout << "**************************This is the Poisson Point Process Mex Function call**************************" << endl;
    cout << "*******************************************************************************************************" << endl;
    auto start = chrono::steady_clock::now();
#endif

    if(nrhs == 2) {
        if (nlhs == 1) {

            double lambda = *mxGetPr(prhs[0]);
            int seed = static_cast<int>(*mxGetPr(prhs[1]));
            
#ifndef NDEBUG
            cout << "Lambda value from Matlab: " << lambda << endl;
            cout << "Seed value from Matlab: " << seed << endl;
#endif

            list<list<pair<double, int>>> allPoissonDatas = Compute(lambda, seed);

            list<pair<double, int>> poissonTimelineData = allPoissonDatas.front();
            allPoissonDatas.pop_front();

            list<pair<double, int>> poissonTimesData = allPoissonDatas.front();
            allPoissonDatas.pop_front();

            list<pair<double, int>> poissonEventsData = allPoissonDatas.front();

            //prepare the output to be returned to matlab prompt
            const char *field_names[] = {"timelineTime", "timelineNumOfEvents",
            "timesWaitingTime", "timesFrequency",
            "eventsNumOfEvents", "eventsFrequency"};
            
            unsigned int maxSize = 0;
            if(poissonTimelineData.size() > poissonTimesData.size()) {
                maxSize = poissonTimelineData.size();
            }
            else {
                maxSize = poissonTimesData.size();
            }

            if(poissonEventsData.size() > maxSize) {
                maxSize = poissonEventsData.size();
            }

            mwSize dims[2] = {1, static_cast<int>(maxSize)};

            mxArray *value;
            plhs[0] = mxCreateStructArray(2, dims, 6, field_names);
            int field_timelineTime = mxGetFieldNumber(plhs[0], "timelineTime");
            int field_timelineNumOfEvents = mxGetFieldNumber(plhs[0], "timelineNumOfEvents");
            int field_timesWaitingTime = mxGetFieldNumber(plhs[0], "timesWaitingTime");
            int field_timesFrequency = mxGetFieldNumber(plhs[0], "timesFrequency");
            int field_eventsNumOfEvents = mxGetFieldNumber(plhs[0], "eventsNumOfEvents");
            int field_eventsFrequency = mxGetFieldNumber(plhs[0], "eventsFrequency");

            unsigned int cnt = 0;
            for (auto i = poissonTimelineData.begin(); i != poissonTimelineData.end(); ++i) {
                value = mxCreateDoubleScalar((*i).first);
                mxSetFieldByNumber(plhs[0], cnt, field_timelineTime, value);
                value = mxCreateDoubleScalar((*i).second);
                mxSetFieldByNumber(plhs[0], cnt, field_timelineNumOfEvents, value);
                cnt++;
            }
            cnt = 0;
            for (auto i = poissonTimesData.begin(); i != poissonTimesData.end(); ++i) {
                value = mxCreateDoubleScalar((*i).first);
                mxSetFieldByNumber(plhs[0], cnt, field_timesWaitingTime, value);
                value = mxCreateDoubleScalar((*i).second);
                mxSetFieldByNumber(plhs[0], cnt, field_timesFrequency, value);
                cnt++;
            }
            cnt = 0;
            for (auto i = poissonEventsData.begin(); i != poissonEventsData.end(); ++i) {
                value = mxCreateDoubleScalar((*i).first);
                mxSetFieldByNumber(plhs[0], cnt, field_eventsNumOfEvents, value);
                value = mxCreateDoubleScalar((*i).second);
                mxSetFieldByNumber(plhs[0], cnt, field_eventsFrequency, value);
                cnt++;
            }
        }
        else {
            mexErrMsgTxt("Expects 1 output arguments");
        }
    }
    else {
        mexErrMsgTxt("Expects 2 input arguments");
        mexErrMsgTxt("Argument 1 must be lambda value!");
        mexErrMsgTxt("Argument 2 must be seed value!");
    }

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