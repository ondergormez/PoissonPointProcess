//# include <cstdlib>
# include <iostream>
# include <fstream>
# include <iomanip>
# include <cmath>
# include <ctime>
# include <cstring>

using namespace std;

# include "poisson_simulation.hpp"
#include "poisson_simulation_prb.hpp"

//https://people.sc.fsu.edu/~jburkardt/cpp_src/poisson_simulation/poisson_simulation_prb.cpp
void test01(double lambda, int seed,
  vector<pair<double, int>> &poissonTimelineData,
  vector<pair<double, int>> &poissonTimesData);

void test02 (double lambda, int seed,
  vector<pair<double, int>> &poissonEventsData);

//****************************************************************************80

void Compute(double lambda,int seed,
  vector<pair<double, int>> &poissonTimelineData,
  vector<pair<double, int>> &poissonTimesData,
  vector<pair<double, int>> &poissonEventsData)

//****************************************************************************80
//
//  Purpose:
//
//    MAIN is the main program for POISSON_SIMULATION_PRB.
//
//  Discussion:
//
//    POISSON_SIMULATION_PRB tests the POISSON_SIMULATION library.
//
//  Licensing:
//
//    This code is distributed under the GNU LGPL license.
//
//  Modified:
//
//    27 September 2012
//
//  Author:
//
//    John Burkardt
//
{
  //timestamp ( );
  cout << "\n";
  cout << "POISSON_SIMULATION_TEST\n";
  cout << "  C++ version.\n";
  cout << "  Test the POISSON_SIMULATION library.\n";

  test01 (lambda, seed, poissonTimelineData, poissonTimesData);
  test02(lambda, seed, poissonEventsData);

  //
  //  Terminate.
  //
  cout << "\n";
  cout << "POISSON_SIMULATION_TEST\n";
  cout << "  Normal end of execution.\n";
  cout << "\n";
  //timestamp ( );
}
//****************************************************************************80

void test01(double lambda, int seed,
  vector<pair<double, int>>&poissonTimelineData,
  vector<pair<double, int>>&poissonTimesData)

//****************************************************************************80
//
//  Purpose:
//
//    TEST01 simulates waiting for a given number of events.
//
//  Licensing:
//
//    This code is distributed under the GNU LGPL license.
//
//  Modified:
//
//    27 September 2012
//
//  Author:
//
//    John Burkardt
//
{
  int bin_num = 30;
  int event_num = 1000;
  int *f_bin;
  int i;
  int j;
  double *t;
  double *w;
  double w_ave;
  double *w_bin;
  double w_max;
  double w_min;

  cout << "\n";
  cout << "TEST01:\n";
  cout << "  POISSON_FIXED_EVENTS simulates a Poisson process\n";
  cout << "  until a given number of events have occurred.\n";
  cout << "\n";
  cout << "  Simulate a Poisson process, for which, on average,\n";
  cout << "  LAMBDA events occur per unit time.\n";
  cout << "  Run until you have observed EVENT_NUM events.\n";

  cout << "\n";
  cout << "  LAMBDA = " << lambda << "\n";
  cout << "  EVENT_NUM = " << event_num << "\n";
  cout << "  SEED = " << seed << "\n";

  t = new double[event_num+1];
  w = new double[event_num+1];
  poisson_fixed_events ( lambda, event_num, seed, t, w );

  w_min = r8vec_min ( event_num + 1, w );
  w_max = r8vec_max ( event_num + 1, w );
  w_ave = r8vec_mean ( event_num + 1, w );

  cout << "\n";
  cout << "  Minimum wait = " << w_min << "\n";
  cout << "  Average wait = " << w_ave << "\n";
  cout << "  Maximum wait = " << w_max << "\n";

  cout << "\n";
  cout << " Count            Time            Wait\n";
  cout << "\n";
  for ( i = 0; i <= 5; i++ )
  {
    cout << "  " << i
         << "  " << t[i]
         << "  " << w[i] << "\n";
  }
  cout << "  ....  ..............  ..............\n";
  for ( i = event_num - 5; i <= event_num; i++ )
  {
    cout << "  " << i
         << "  " << t[i]
         << "  " << w[i] << "\n";
  }

  for ( i = 0; i <= event_num; i++ )
  {
    poissonTimelineData.push_back(make_pair(t[i], i));
  }

  //
  //  Determine bin information.
  //
  w_min = r8vec_min ( event_num + 1, w );
  w_max = r8vec_max ( event_num + 1, w );

  w_bin = r8vec_midspace_new ( bin_num, w_min, w_max );
  f_bin = new int[bin_num];

  for ( i = 0; i < bin_num; i++ )
  {
    f_bin[i] = 0;
  }

  for ( i = 0; i <= event_num; i++ )
  {
    j = 1 + ( int ) ( ( double ) ( bin_num ) * ( w[i] - w_min ) / ( w_max - w_min ) );
    j = i4_min ( j, bin_num );
    f_bin[j] = f_bin[j] + 1;
  }

  for ( i = 0; i < bin_num; i++ )
  {
    poissonTimesData.push_back(make_pair(w_bin[i], f_bin[i]));
  }

  delete [] f_bin;
  delete [] t;
  delete [] w;
  delete [] w_bin;
}
//****************************************************************************80

void test02(double lambda, int seed, vector<pair<double, int>> &poissonEventsData)

//****************************************************************************80
//
//  Purpose:
//
//    TEST02 simulates waiting for a given length of time.
//
//  Licensing:
//
//    This code is distributed under the GNU LGPL license.
//
//  Modified:
//
//    27 September 2012
//
//  Author:
//
//    John Burkardt
//
{
  int bin_num = 30;
  int *f_bin;
  int i;
  int *n;
  double *n_bin;
  double n_max;
  double n_mean;
  double n_min;
  double n_var;
  double t;
  int test;
  int test_num = 20000;
  t = 1000.0;

  cout << "\n";
  cout << "TEST02:\n";
  cout << "  POISSON_FIXED_EVENTS simulates a Poisson process\n";
  cout << "  counting the number of events that occur during\n";
  cout << "  a given time.\n";
  cout << "\n";
  cout << "  Simulate a Poisson process, for which, on average,\n";
  cout << "  LAMBDA events occur per unit time.\n";
  cout << "  Run for a total of " << t << " time units.\n";
  cout << "  LAMBDA = " << lambda << "\n";
  cout << "  SEED = " << seed << "\n";

  n = new int[test_num];

  for ( test = 0; test < test_num; test++ )
  {
    n[test] = poisson_fixed_time ( lambda, t, seed );
  }

  n_mean = i4vec_mean ( test_num, n );
  n_var = i4vec_variance ( test_num, n );
  cout << "\n";
  cout << "  Mean number of events = " << n_mean << "\n";
  cout << "  Variance = " << n_var << "\n";
  cout << "  STD = " << sqrt ( n_var ) << "\n";

  n_min = ( double ) ( i4vec_min ( test_num, n ) );
  n_max = ( double ) ( i4vec_max ( test_num, n ) );

  n_bin = r8vec_midspace_new ( bin_num, n_min, n_max );

  f_bin = new int[bin_num];
  for ( i = 0; i < bin_num; i++ )
  {
    f_bin[i] = 0;
  }
  for ( test = 0; test < test_num; test++ )
  {
    i = 1 + ( int ) ( ( double ) ( bin_num * ( n[test] - n_min ) ) 
      / ( double ) ( n_max - n_min ) );
    i = i4_min ( i, bin_num );
    f_bin[i] = f_bin[i] + 1;
  }

  //
  //  Fill pair list with results.
  //
  for ( i = 0; i < bin_num; i++ )
  {
    poissonEventsData.push_back(make_pair(n_bin[i], f_bin[i]));
  }

  delete [] f_bin;
  delete [] n;
  delete [] n_bin;
}