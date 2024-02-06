#ifndef FGE_POLYNOMIAL_H_
#define FGE_POLYNOMIAL_H_

#include "FGE_intrinsics.h"

namespace FGE{



template<size_t N>
constexpr std::array<float,N+1> PowerTower(float x)
{
    std::array<float,N+1>retVal{x};
    for(size_t i=1; i<N+1; ++i)retVal.at(i)=retVal.at(i-1)*x;
    
    return retVal; 
}

template<size_t N>
struct polynomial
{
    std::array<float,N+1> coefficients;
    std::array<float,N+1>powerTower{0};
    constexpr float evaluate(float x)const
    {
        if(powerTower.front()!=x)powerTower=PowerTower(x);
        return FGE_DotProd(coefficients,powerTower);
    }
    constexpr float at(size_t i)const
    {
        return coefficients.at(i); 
    }
    inline float& at(size_t i)
    {
        return coefficients.at(i); 
    }
    constexpr size_t size()const
    {
        return N+1;
    }
    constexpr size_t degree()const
    {
        return N;
    }
    constexpr float evaluateSlope(float x)const
    {
        if(powerTower.front()!=x)powerTower=PowerTower(x);
        return FGE_DotProd(coefficients,powerTower);
    }
};
template<size_t N>
constexpr polynomial<N> create_polynomial(const std::array<float,N+1>& coefficients)noexcept
{
    polynomial<N> dummyVar; 
    dummyVar.coefficients=coefficients;
    return dummyVar; 
}
template<size_t N>
constexpr polynomial<N> operator+(const polynomial<N>& a,const polynomial<N>& b)
{
    return create_polynomial(FGE_CompAdd(a.coefficients,b.coefficients)); 
}
template<size_t N>
constexpr polynomial<N> operator-(const polynomial<N>& a,const polynomial<N>& b)
{
    return create_polynomial(FGE_CompSub(a.coefficients,b.coefficients)); 
}
template<size_t N>
constexpr polynomial<N> operator*(const polynomial<N>& a,float x)
{
    polynomial<N> retVal; 
   for(size_t i=0; i<N+1; ++i)retVal.coefficients.at(i)=a.coefficients.at(i)*x; 
   return retVal; 
}
template<size_t N>
constexpr polynomial<N> operator*(float x,const polynomial<N>& a)
{
    polynomial<N> retVal; 
   for(size_t i=0; i<N+1; ++i)retVal.coefficients.at(i)=a.coefficients.at(i)*x; 
   return retVal; 
}
template<size_t N>
constexpr polynomial<N> operator/(const polynomial<N>& a,float x)
{
    polynomial<N> retVal; 
   for(size_t i=0; i<N+1; ++i)retVal.coefficients.at(i)=a.coefficients.at(i)/x; 
   return retVal; 
}
template<size_t N>
constexpr polynomial<N> operator*(const polynomial<N>& a,const polynomial<N>& b)
{
    polynomial<N> retVal; 
   for(size_t i=0; i<N+1; ++i)for(size_t j=0; j<=i; ++j)retVal.coefficients.at(i)=a.coefficients.at(j)*b.coefficients.at(i-j);
   return retVal; 
}



};



#endif