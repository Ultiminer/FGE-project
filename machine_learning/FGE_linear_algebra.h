#ifndef FGE_LINEAR_ALGEBRA_H_
#define FGE_LINEAR_ALGEBRA_H_
#include "GCEM/gcem.hpp"
#include <immintrin.h>
#include <array>

#define FGE_Vec(S) std::array<float,(S)>
namespace FGE{

template<size_t S>
constexpr std::array<float, S> Add(const std::array<float,S>& a, const std::array<float,S>& b)
{
    std::array<float,S>retVal; 
    constexpr size_t numChunks{16};
    constexpr size_t numVectorizable{S/numChunks};

    for(size_t i=0;i<numVectorizable;++i){
    const size_t memoryId{i*numChunks};
    auto registerA= _mm512_loadu_ps(a.data()+memoryId);
    auto registerB= _mm512_loadu_ps(b.data()+memoryId);
    auto sum=_mm512_add_ps(registerA,registerB);

    _mm512_storeu_ps(retVal.data()+memoryId,sum);
    }
    for(size_t i=numVectorizable; i<a.size();++i)retVal.at(i)=a.at(i)+b.at(i);
    return retVal; 
}
template<size_t S>
constexpr std::array<float, S> Sub(const std::array<float,S>& a, const std::array<float,S>& b)
{
    std::array<float,S>retVal; 
    constexpr size_t numChunks{16};
    constexpr size_t numVectorizable{S/numChunks};

    for(size_t i=0;i<numVectorizable;++i){
    const size_t memoryId{i*numChunks};
    auto registerA= _mm512_loadu_ps(a.data()+memoryId);
    auto registerB= _mm512_loadu_ps(b.data()+memoryId);
    auto sum=_mm512_sub_ps(registerA,registerB);
    __mm512_storeu_ps(retVal.data()+memoryId,sum);
    }
    for(size_t i=numVectorizable; i<a.size();++i)retVal.at(i)=a.at(i)-b.at(i);
    return retVal; 
}
template<size_t S>
constexpr std::array<float, S> Multiply(const std::array<float,S>& a, const std::array<float,S>& b)
{
    std::array<float,S>retVal; 
    constexpr size_t numChunks{16};
    constexpr size_t numVectorizable{S/numChunks};

    for(size_t i=0;i<numVectorizable;++i){
    const size_t memoryId{i*numChunks};
    auto registerA= _mm512_loadu_ps(a.data()+memoryId);
    auto registerB= _mm512_loadu_ps(b.data()+memoryId);
    auto sum=_mm512_mul_ps(registerA,registerB);
     _mm512_storeu_ps(retVal.data()+memoryId,sum);
    }
    for(size_t i=numVectorizable; i<a.size();++i)retVal.at(i)=a.at(i)*b.at(i);
    return retVal;  
}
template<size_t S>
constexpr float AddThrough(const std::array<float,S>& a)
{
    float retVal=0; 
    for(size_t i=0; i<a.size();++i)retVal+=a.at(i);
    return retVal; 
}

template<size_t S>
constexpr float Dot(const std::array<float,S>& a, const std::array<float,S>& b)
{
   return AddThrough(Multiply(a,b));
}
template<size_t S>
constexpr std::array<float,S> PowerTower(float x)
{   
    if(S<3)
    {if(S==0)return {};if(S==1)return {1};if(S==2)return {1,x};}
    
    std::array<float, S>retVal;
    retVal.front()=1;
    retVal.at(1)=x; 
    for(size_t i=2; i<S; ++i)retVal.at(i)=retVal.at(i-1)*x; 

    return retVal;
}

template<size_t S>
constexpr float Squaredist(const std::array<float,S>& a)
{
return Dot(a,a);
}
template<size_t S>
constexpr float Squaredist(const std::array<float,S>& a,const std::array<float,S>& b)
{
return Squaredist(Sub(a,b));
}

constexpr float Squaredist(float x){return x*x;}
constexpr float Squaredist(float a, float b){const float d{a-b}; return d*d; }
template<size_t S, size_t L>
constexpr std::array<std::array<float,L>,S> ChangeVecMapping(const std::array<std::array<float,S>,L>& multVecs)
{
std::array<std::array<float,L>,S> retVal; 
for(size_t i=0; i<S;++i)for(size_t j=0; j<L;++j)retVal.at(i)[j]=multVecs.at(j)[i]; 
return retVal; 
}

template<size_t S, size_t L>
constexpr std::array<float,S> AddMultiple(const std::array<std::array<float,S>,L>& multVecs)
{
    std::array<float,S>retVal; 
    for(size_t i=0; i<L; ++i)Add(retVal,multVecs.at(i));
    return retVal; 
}

template<size_t S>
constexpr std::array<float, S> Multiply(const std::array<float, S>& v, float x)
{
    std::array<float, S>retVal=std::move(v); 
    for(size_t i=0; i<S;++i)retVal.at(i)*=x;
    return retVal; 
}
template<size_t S>
constexpr std::array<float, S> Multiply(const std::array<std::array<float,S>,S>& matrix,const std::array<float,S>& v)
{
    std::array<float, S>retVal; 
    for(size_t i=0; i<S;++i)retVal.at(i)=Dot(v,matrix.at(i));
    return retVal; 
}

template<size_t S>
constexpr float MeanSquaredError(const std::array<float, S>& a, const std::array<float, S>& b)
{
    return Squaredist(a,b)/S;
}

}

#endif