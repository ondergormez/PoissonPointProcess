#include "prng_uniform.hpp"

using namespace std;

namespace os_prng_tests
{
    namespace in_progress
    {
        //unsigned PRNG_Uniform::seed = chrono::high_resolution_clock::now().time_since_epoch().count();
        //default_random_engine PRNG_Uniform::generator(seed);
        
        unsigned PRNG_Uniform::seed = chrono::high_resolution_clock::now().time_since_epoch().count();;
        default_random_engine PRNG_Uniform::generator(seed);

#ifdef USE_SHARED_PTR_FOR_DISTRIBUTION
        shared_ptr<uniform_real_distribution<double>>  PRNG_Uniform::distribution
            = make_shared<uniform_real_distribution<double>>(0.0, 1.0);
#else
        uniform_real_distribution<double> PRNG_Uniform::distribution(0.0, 1.0);
#endif
            void PRNG_Uniform::ChangeSeed(default_random_engine &generator)
            {
                seed = chrono::high_resolution_clock::now().time_since_epoch().count();
                generator.seed(seed);
            }

            std::vector<double> * PRNG_Uniform::getNumbers(unsigned int howMany)
            {
                ChangeSeed(generator);
                using namespace std;

                vector<double> *current = new vector<double> ();
                current->clear();
                
                for (unsigned int ii = 0; ii < howMany; ++ii)
                {
#ifdef USE_SHARED_PTR_FOR_DISTRIBUTION
                    (*current).push_back((*distribution)(generator));
#else
                    (*current).push_back(distribution(generator));
#endif
                }

                return current;
            }

            void PRNG_Uniform::getNumbers(std::vector<double> & current, unsigned int howMany)
            {
                ChangeSeed(generator);
                using namespace std;

                current.clear();

                for (unsigned int ii = 0; ii < howMany; ++ii) {
#ifdef USE_SHARED_PTR_FOR_DISTRIBUTION
                    current.push_back((*distribution)(generator));
#else
                    current.push_back(distribution(generator));
#endif
                }
            }

            int32_t PRNG_Uniform::PoissonRandom(double number)
            {
                std::default_random_engine generator;
                ChangeSeed(generator);
                std::poisson_distribution<int> distribution(number);

                return distribution(generator);
            }
    }
}