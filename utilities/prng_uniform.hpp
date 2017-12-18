#ifndef __MY_PRNG_UNIFORM_HH_IN_PROGRESS__
#define __MY_PRNG_UNIFORM_HH_IN_PROGRESS__

#include <chrono>
#include <random>
#include <memory>
#include <vector>
#include <iostream>

#define USE_SHARED_PTR_FOR_DISTRIBUTION

/*
* Note:
* In general, avoid putting using directives in header files (*.h)
* because any file that includes that header will bring everything
* in the namespace into scope, which can cause name hiding and name
* collision problems that are very difficult to debug.
*/

namespace os_prng_tests
{
    namespace in_progress
    {

        class PRNG_Uniform
        {

        private:
            static unsigned seed;
            static std::default_random_engine generator;
#ifdef USE_SHARED_PTR_FOR_DISTRIBUTION
            static std::shared_ptr<std::uniform_real_distribution<double>> distribution;
#else
            static std::uniform_real_distribution<double> distribution;
#endif
            static void ChangeSeed(std::default_random_engine &generator);
            PRNG_Uniform() {}
            ~PRNG_Uniform() {}

        public:
            static std::vector<double> * getNumbers(unsigned int howMany);
            static void getNumbers(std::vector<double> & current, unsigned int howMany);
            static int32_t PoissonRandom(double number);
        };
    }
}

#endif /* __MY_PRNG_UNIFORM_HH_IN_PROGRESS__ */