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
#include "PoissonPointProcess.hpp"

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

    if(nrhs == 1) {
        if (nlhs == 1) {

            int32_t lambda = static_cast<int32_t>(*mxGetPr(prhs[0])); 
            
#ifndef NDEBUG
            cout << "Lambda: " << lambda << endl;
#endif
            //PoissonPointProcess::Compute(lambda);


            // mxArray * value;

            // value = mxCreateDoubleScalar(15);
            // mxSetFieldByNumber(plhs[0], 12, 20, value);

            //plhs[0] = mxCreateDoubleMatrix(10, 20, mxREAL);

            //plhs[0] = Compute(nlhs, plhs, nrhs, prhs);

            list<list<pair<double, int>>> allPoissonDatas = Compute();

            list<pair<double, int>> poissonTimelineData = allPoissonDatas.front();
            allPoissonDatas.pop_front();

            list<pair<double, int>> poissonTimesData = allPoissonDatas.front();
            allPoissonDatas.pop_front();

            list<pair<double, int>> poissonEventsData = allPoissonDatas.front();

            //prepare the output to be returned to matlab prompt
            const char *field_names[] = {"timelineTime", "timelineNumOfEvents", "timesWaitingTime", "timesFrequency", "eventsNumOfEvents", "eventsFrequency"};
            
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

  

//list<pair<double, int>> test02(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])

            //cout << "Exited from function" << endl;


        }
        else {
            mexErrMsgTxt("Expects 1 output arguments");
        }
    }
    else {
        mexErrMsgTxt("Expects 1 input arguments");
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

// //****************************************************************************80

// void Compute(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])

// //****************************************************************************80
// //
// //  Purpose:
// //
// //    MAIN is the main program for POISSON_SIMULATION_PRB.
// //
// //  Discussion:
// //
// //    POISSON_SIMULATION_PRB tests the POISSON_SIMULATION library.
// //
// //  Licensing:
// //
// //    This code is distributed under the GNU LGPL license.
// //
// //  Modified:
// //
// //    27 September 2012
// //
// //  Author:
// //
// //    John Burkardt
// //
// {
//   timestamp ( );
//   cout << "\n";
//   cout << "POISSON_SIMULATION_TEST\n";
//   cout << "  C++ version.\n";
//   cout << "  Test the POISSON_SIMULATION library.\n";

//   test01(nlhs, plhs, nrhs, prhs);
//   test02(nlhs, plhs, nrhs, prhs);
// //
// //  Terminate.
// //
//   cout << "\n";
//   cout << "POISSON_SIMULATION_TEST\n";
//   cout << "  Normal end of execution.\n";
//   cout << "\n";
//   timestamp ( );

//   return;
// }
// //****************************************************************************80

// void test01(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])

// //****************************************************************************80
// //
// //  Purpose:
// //
// //    TEST01 simulates waiting for a given number of events.
// //
// //  Licensing:
// //
// //    This code is distributed under the GNU LGPL license.
// //
// //  Modified:
// //
// //    27 September 2012
// //
// //  Author:
// //
// //    John Burkardt
// //
// {
//   int bin_num = 30;
//   string command_filename;
//   ofstream command;
//   string data_filename;
//   ofstream data;
//   int event_num = 1000;
//   int *f_bin;
//   int i;
//   int j;
//   double lambda;
//   int seed;
//   double *t;
//   double *w;
//   double w_ave;
//   double *w_bin;
//   double w_max;
//   double w_min;
//   double width;

//   cout << "\n";
//   cout << "TEST01:\n";
//   cout << "  POISSON_FIXED_EVENTS simulates a Poisson process\n";
//   cout << "  until a given number of events have occurred.\n";
//   cout << "\n";
//   cout << "  Simulate a Poisson process, for which, on average,\n";
//   cout << "  LAMBDA events occur per unit time.\n";
//   cout << "  Run until you have observed EVENT_NUM events.\n";
 
//   lambda = 0.5;
//   seed = 123456789;

//   cout << "\n";
//   cout << "  LAMBDA = " << lambda << "\n";
//   cout << "  EVENT_NUM = " << event_num << "\n";

//   t = new double[event_num+1];
//   w = new double[event_num+1];
//   poisson_fixed_events ( lambda, event_num, seed, t, w );

//   w_min = r8vec_min ( event_num + 1, w );
//   w_max = r8vec_max ( event_num + 1, w );
//   w_ave = r8vec_mean ( event_num + 1, w );

//   cout << "\n";
//   cout << "  Minimum wait = " << w_min << "\n";
//   cout << "  Average wait = " << w_ave << "\n";
//   cout << "  Maximum wait = " << w_max << "\n";

//   cout << "\n";
//   cout << " Count            Time            Wait\n";
//   cout << "\n";
//   for ( i = 0; i <= 5; i++ )
//   {
//     cout << "  " << i
//          << "  " << t[i]
//          << "  " << w[i] << "\n";
//   }
//   cout << "  ....  ..............  ..............\n";
//   for ( i = event_num - 5; i <= event_num; i++ )
//   {
//     cout << "  " << i
//          << "  " << t[i]
//          << "  " << w[i] << "\n";
//   }
// //
// //  Create the data file.
// //
//   data_filename = "poisson_timeline_data.txt";

//   data.open ( data_filename.c_str ( ) );

//   for ( i = 0; i <= event_num; i++ )
//   {
//     data << "  " << t[i]
//          << "  " << i << "\n";
//   }
//   data.close ( );

//   cout << " \n";
//   cout << "  Data stored in \"" << data_filename << "\".\n";
// //
// //  Create the command file.
// //
//   command_filename = "poisson_timeline_commands.txt";

//   command.open ( command_filename.c_str ( ) );

//   command << "# poisson_timeline_commands.txt\n";
//   command << "#\n";
//   command << "# Usage:\n";
//   command << "#  gnuplot < poisson_timeline_commands.txt\n";
//   command << "#\n";
//   command << "set term png\n";
//   command << "set output 'poisson_timeline.png'\n";
//   command << "set style data lines\n";
//   command << "set xlabel 'Time'\n";
//   command << "set ylabel 'Number of Events'\n";
//   command << "set title 'Observation of Fixed Number of Poisson Events'\n";
//   command << "set grid\n";
//   command << "plot 'poisson_timeline_data.txt' using 1:2 lw 2\n";
//   command << "quit\n";

//   command.close ( );

//   cout << "  Plot commands stored in \"" << command_filename << "\".\n";
// //
// //  Determine bin information.
// //
//   w_min = r8vec_min ( event_num + 1, w );
//   w_max = r8vec_max ( event_num + 1, w );

//   w_bin = r8vec_midspace_new ( bin_num, w_min, w_max );
//   f_bin = new int[bin_num];

//   for ( i = 0; i < bin_num; i++ )
//   {
//     f_bin[i] = 0;
//   }

//   for ( i = 0; i <= event_num; i++ )
//   {
//     j = 1 + ( int ) ( ( double ) ( bin_num ) * ( w[i] - w_min ) / ( w_max - w_min ) );
//     j = i4_min ( j, bin_num );
//     f_bin[j] = f_bin[j] + 1;
//   }
// //
// //  Create the data file.
// //
//   data_filename = "poisson_times_data.txt";

//   data.open ( data_filename.c_str ( ) );

//   for ( i = 0; i < bin_num; i++ )
//   {
//     data << "  " << w_bin[i]
//          << "  " << f_bin[i] << "\n";
//   }
//   data.close ( );

//   cout << " \n";
//   cout << "  Data stored in \"" << data_filename << "\".\n";
// //
// //  Create the command file.
// //
//   command_filename = "poisson_times_commands.txt";

//   command.open ( command_filename.c_str ( ) );

//   command << "# poisson_times_commands.txt\n";
//   command << "#\n";
//   command << "# Usage:\n";
//   command << "#  gnuplot < poisson_times_commands.txt\n";
//   command << "#\n";
//   command << "set term png\n";
//   command << "set output 'poisson_times.png'\n";
//   command << "set xlabel 'Waiting Time'\n";
//   command << "set ylabel 'Frequency'\n";
//   command << "set title 'Waiting Times Observed Over Fixed Time'\n";
//   command << "set grid\n";
//   command << "set style fill solid\n";
//   width = 0.85 * ( w_max - w_min ) / ( double ) ( bin_num );
//   command << "plot 'poisson_times_data.txt' using 1:2:(" << width << ") with boxes\n";
//   command << "quit\n";

//   command.close ( );

//   cout << "  Plot commands stored in \"" << command_filename << "\".\n";

//   delete [] f_bin;
//   delete [] t;
//   delete [] w;
//   delete [] w_bin;

//   return;
// }
// //****************************************************************************80

// list<pair<double, int>> test02(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])

// //****************************************************************************80
// //
// //  Purpose:
// //
// //    TEST02 simulates waiting for a given length of time.
// //
// //  Licensing:
// //
// //    This code is distributed under the GNU LGPL license.
// //
// //  Modified:
// //
// //    27 September 2012
// //
// //  Author:
// //
// //    John Burkardt
// //
// {
//   int bin_num = 30;
//   string command_filename;
//   ofstream command;
//   string data_filename;
//   ofstream data;
//   int *f_bin;
//   int i;
//   double lambda;
//   int *n;
//   double *n_bin;
//   double n_max;
//   double n_mean;
//   double n_min;
//   double n_var;
//   int seed;
//   double t;
//   int test;
//   int test_num = 20000;
//   double w;

//   lambda = 0.5;
//   t = 1000.0;
//   seed = 123456789;

//   cout << "\n";
//   cout << "TEST02:\n";
//   cout << "  POISSON_FIXED_EVENTS simulates a Poisson process\n";
//   cout << "  counting the number of events that occur during\n";
//   cout << "  a given time.\n";
//   cout << "\n";
//   cout << "  Simulate a Poisson process, for which, on average,\n";
//   cout << "  LAMBDA events occur per unit time.\n";
//   cout << "  Run for a total of " << t << " time units.\n";
//   cout << "  LAMBDA = " << lambda << "\n";

//   n = new int[test_num];

//   for ( test = 0; test < test_num; test++ )
//   {
//     n[test] = poisson_fixed_time ( lambda, t, seed );
//   }

//   n_mean = i4vec_mean ( test_num, n );
//   n_var = i4vec_variance ( test_num, n );
//   cout << "\n";
//   cout << "  Mean number of events = " << n_mean << "\n";
//   cout << "  Variance = " << n_var << "\n";
//   cout << "  STD = " << sqrt ( n_var ) << "\n";

//   n_min = ( double ) ( i4vec_min ( test_num, n ) );
//   n_max = ( double ) ( i4vec_max ( test_num, n ) );

//   n_bin = r8vec_midspace_new ( bin_num, n_min, n_max );

//   f_bin = new int[bin_num];
//   for ( i = 0; i < bin_num; i++ )
//   {
//     f_bin[i] = 0;
//   }
//   for ( test = 0; test < test_num; test++ )
//   {
//     i = 1 + ( int ) ( ( double ) ( bin_num * ( n[test] - n_min ) ) 
//       / ( double ) ( n_max - n_min ) );
//     i = i4_min ( i, bin_num );
//     f_bin[i] = f_bin[i] + 1;
//   }
// //
// //  Create the data file.
// //
//   data_filename = "poisson_events_data.txt";

//   data.open ( data_filename.c_str ( ) );
  
//   list<pair<double, int>> poissonEventsData;

//   for ( i = 0; i < bin_num; i++ )
//   {
//     data << "  " << n_bin[i]
//          << "  " << f_bin[i] << "\n";
//     poissonEventsData.push_back(make_pair(n_bin[i], f_bin[i]));
//   }

//   data.close ( );

//   cout << " \n";
//   cout << "  Data stored in \"" << data_filename << "\".\n";
// //
// //  Create the command file.
// //
//   command_filename = "poisson_events_commands.txt";

//   command.open ( command_filename.c_str ( ) );

//   command << "# poisson_events_commands.txt\n";
//   command << "#\n";
//   command << "# Usage:\n";
//   command << "#  gnuplot < poisson_events_commands.txt\n";
//   command << "#\n";
//   command << "set term png\n";
//   command << "set output 'poisson_events.png'\n";
//   command << "set xlabel 'Number of Events'\n";
//   command << "set ylabel 'Frequency'\n";
//   command << "set title 'Number of Poisson Events Over Fixed Time'\n";
//   command << "set grid\n";
//   command << "set style fill solid\n";
//   w = 0.85 * ( n_max - n_min ) / ( double ) ( bin_num );
//   command << "plot 'poisson_events_data.txt' using 1:2:(" << w << ") with boxes\n";
//   command << "quit\n";

//   command.close ( );

//   cout << "  Plot commands stored in \"" << command_filename << "\".\n";

//   delete [] f_bin;
//   delete [] n;
//   delete [] n_bin;

//   return poissonEventsData;
// }