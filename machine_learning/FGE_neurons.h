#ifndef FGE_NEURONS_H_
#define FGE_NEURONS_H_
#include "FGE_analysis.h"
#include "FGE_linear_algebra.h"
#include "FGE_random.h"
#include <array>

namespace FGE{


template<size_t S>
struct Layer
{
std::array<std::array<float,S>,S>weights;
std::array<float,S>b; 
std::function<float(float)>fun;
Layer(const std::function<float(float)>& activation , float value_range=1)
{
for(size_t i=0; i<S*S; ++i)weights.at(i/S).at(i%S)=value_range*random(-1,1);
for(size_t i=0; i<S;++i)b.at(i)=value_range*random(-1,1);
fun=activation;
}

constexpr std::array<float,S> operator()(const std::array<float,S>& a_prev)
{
    
    std::array<float,S> retVal; 
    const std::array<float,S> result=Add(b,Multiply(weights,a_prev));
    for(size_t i=0; i<S;++i)retVal.at(i)=fun(result.at(i));

    return retVal;
}


};



}
#endif