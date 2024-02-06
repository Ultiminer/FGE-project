#ifndef FGE_INTRINSICS_H_
#define FGE_INTRINSICS_H_
#include<array>
#include<emmintrin.h> 

#define __FGE_M128 *(__m128*)
//This header allows users easy access to the SSE2 instruction set

/*Adds the components of the two arrays into a new array*/
template<size_t S>
constexpr std::array<float, S> FGE_CompAdd(const std::array<float, S>& a, const std::array<float, S>& b)noexcept
{
   std::array<float,S>retVal; 
    constexpr size_t numChunks{4};
    constexpr size_t numVectorizable{S/numChunks};
    
    for(size_t i=0;i<numVectorizable;++i){
    const size_t currMem{i*numChunks};
    _mm_storeu_ps(retVal.data()+currMem,_mm_add_ps(__FGE_M128(a.data()+currMem),__FGE_M128(b.data()+currMem)));
    }
    for(size_t i=numVectorizable; i<a.size();++i)retVal.at(i)=a.at(i)+b.at(i);
    return retVal; 
}

template<size_t S>
constexpr std::array<float, S> FGE_CompSub(const std::array<float, S>& a, const std::array<float, S>& b)noexcept
{
   std::array<float,S>retVal; 
    constexpr size_t numChunks{4};
    constexpr size_t numVectorizable{S/numChunks};

    for(size_t i=0;i<numVectorizable;++i)
    _mm_storeu_ps(retVal.data()+i*numChunks,_mm_sub_ps(__FGE_M128(a.data()+i*numChunks),__FGE_M128(b.data()+i*numChunks)));
    
    for(size_t i=numVectorizable; i<a.size();++i)retVal.at(i)=a.at(i)-b.at(i);
    return retVal; 
}
/*Multiplys the components of the two arrays into a new array*/
template<size_t S>
constexpr std::array<float, S> FGE_CompMultiply(const std::array<float, S>& a, const std::array<float, S>& b)noexcept
{
    std::array<float,S>retVal; 
    constexpr size_t numChunks{4};
    constexpr size_t numVectorizable{S/numChunks};
    
    for(size_t i=0;i<numVectorizable;++i){
    const size_t currMem{i*numChunks};
    _mm_storeu_ps(retVal.data()+currMem,_mm_mul_ps(__FGE_M128(a.data()+currMem),__FGE_M128(b.data()+currMem)));
    }
    for(size_t i=numVectorizable; i<a.size();++i)retVal.at(i)=a.at(i)*b.at(i);
    return retVal; 
}

/*Sums up all the elements in a vector, is up to 3 times faster then using a normal for loop*/
template<size_t S>
constexpr float FGE_VecSum(const std::array<float, S>& V)noexcept
{
    float retVal=0; 
    constexpr size_t pSize=static_cast<int>(S/16)*16; 

    for(size_t i=pSize;i<S;++i)retVal+=V.at(i); 
    if(pSize==0)return retVal; 
 
    float a[4]={0,0,0,0};
    __m128 A=_mm_loadu_ps(a);
    
    for(size_t i=0;i<pSize; i+=16)
    A=_mm_add_ps(_mm_add_ps(_mm_add_ps(_mm_add_ps(A,__FGE_M128(V.data()+i)),__FGE_M128(V.data()+i+4)),__FGE_M128(V.data()+i+8)),__FGE_M128(V.data()+i+12)); 
    
    
    _mm_storeu_ps(a,A);

    return retVal+a[0]+a[1]+a[2]+a[3]; 
}

template<size_t S>
constexpr float FGE_DotProd(const std::array<float, S>& a, const std::array<float, S>& b)noexcept
{
    return FGE_VecSum(FGE_CompMultiply(a,b)); 
}
template<size_t S>
constexpr float FGE_Average(const std::array<float, S>& quantity, const std::array<float, S>& mass)noexcept
{
    return FGE_VecSum(FGE_CompMultiply(quantity*mass))/FGE_VecSum(mass); 
}







#endif
