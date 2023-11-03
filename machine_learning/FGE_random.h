#ifndef FGE_RANDOM_H_
#define FGE_RANDOM_H_
#include<random>
#include<time.h>
constexpr double FRAND_PREC{static_cast<int>(RAND_MAX)};



namespace FGE
{

    inline double frand(void)noexcept
    {
        return rand()/FRAND_PREC;
    }
    inline struct Random
    {
        Random()noexcept{srand(static_cast<unsigned int>(time(nullptr)));}
        Random(unsigned int seed)noexcept{srand(seed);}
        inline float operator()(float start, float end)noexcept
        {
            return start+ (end-start)*frand();
        }
        inline float operator()()noexcept
        {
            return frand();
        }
        inline float operator()(float length)noexcept
        {
            return length*frand();
        }

        inline int int_rand(int start, int end)noexcept
        {
            return start+rand()%(end-start);
        }
        inline int int_rand(int length)noexcept
        {
            return rand()%(length);
        }
        inline Random& set_seed(unsigned int seed)noexcept
        {
            srand(seed);
            return *this; 
        }
    }random;
}




#endif