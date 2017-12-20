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
list<list<pair<double, int>>> test01 ( );
list<pair<double, int>> test02 ( );

//****************************************************************************80

list<list<pair<double, int>>> Compute ()

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
  timestamp ( );
  cout << "\n";
  cout << "POISSON_SIMULATION_TEST\n";
  cout << "  C++ version.\n";
  cout << "  Test the POISSON_SIMULATION library.\n";

  list<list<pair<double, int>>> all;

  list<list<pair<double, int>>> temp = test01 ( );
  for (auto it = temp.begin(); it != temp.end(); ++it) {
    all.push_back(*it);
  }
  all.push_back(test02());

//
//  Terminate.
//
  cout << "\n";
  cout << "POISSON_SIMULATION_TEST\n";
  cout << "  Normal end of execution.\n";
  cout << "\n";
  timestamp ( );

  return all;
}
//****************************************************************************80

list<list<pair<double, int>>> test01 ( )

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
  double lambda;
  int seed;
  double *t;
  double *w;
  double w_ave;
  double *w_bin;
  double w_max;
  double w_min;
  list<list<pair<double, int>>> temp;

  cout << "\n";
  cout << "TEST01:\n";
  cout << "  POISSON_FIXED_EVENTS simulates a Poisson process\n";
  cout << "  until a given number of events have occurred.\n";
  cout << "\n";
  cout << "  Simulate a Poisson process, for which, on average,\n";
  cout << "  LAMBDA events occur per unit time.\n";
  cout << "  Run until you have observed EVENT_NUM events.\n";
 
  lambda = 0.5;
  seed = 123456789;

  cout << "\n";
  cout << "  LAMBDA = " << lambda << "\n";
  cout << "  EVENT_NUM = " << event_num << "\n";

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

  list<pair<double, int>> poissonTimelineData;

  for ( i = 0; i <= event_num; i++ )
  {
    poissonTimelineData.push_back(make_pair(t[i], i));
  }
  temp.push_back(poissonTimelineData);

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
  list<pair<double, int>> poissonTimesData;

  for ( i = 0; i < bin_num; i++ )
  {
    poissonTimesData.push_back(make_pair(w_bin[i], f_bin[i]));
  }
  temp.push_back(poissonTimesData);

  delete [] f_bin;
  delete [] t;
  delete [] w;
  delete [] w_bin;

  return temp;
}
//****************************************************************************80

list<pair<double, int>> test02 ( )

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
  double lambda;
  int *n;
  double *n_bin;
  double n_max;
  double n_mean;
  double n_min;
  double n_var;
  int seed;
  double t;
  int test;
  int test_num = 20000;

  lambda = 0.5;
  t = 1000.0;
  seed = 123456789;

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
  list<pair<double, int>> poissonEventsData;

  for ( i = 0; i < bin_num; i++ )
  {
    poissonEventsData.push_back(make_pair(n_bin[i], f_bin[i]));
  }

  delete [] f_bin;
  delete [] n;
  delete [] n_bin;

  return poissonEventsData;
}