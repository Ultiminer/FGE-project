#ifndef FGE_ARRAY_H_
#define FGE_ARRAY_H_
#include "ostream"

namespace FGE{

template<size_t S>
struct array{
float data[S];

inline void fill(float num) noexcept {for(size_t i=0; i<S;++i)data[i]=num;}
inline void swap(size_t id1, size_t id2)noexcept{data[id1]+=data[id2]; data[id2]=data[id1]-data[id2];data[id1]-=data[id2];}
constexpr bool is_empty()const noexcept {return !S;}
constexpr size_t length()const noexcept {return S;}
constexpr size_t size()const noexcept {return S;}
constexpr float at(size_t i)const noexcept {return data[i%S];}
inline float& at(size_t i) noexcept {return data[i%S];}
constexpr float max()const noexcept {float currMax=0;for(size_t i=0; i<S;++i)currMax=(data[i]>currMax)?data[i]:currMax; return currMax;}
constexpr float min()const noexcept {if(S==0)return 0;float currMin=data[0];for(size_t i=0; i<S;++i)currMin=(data[i]<currMin)?data[i]:currMin; return currMin;}
constexpr float front(size_t i)const noexcept {return data[0];}
inline float& front(size_t i) noexcept {return data[0];}
constexpr float back(size_t i)const noexcept {return at(S-1);}
inline float& back(size_t i) noexcept {return at(S-1);}
constexpr float mid(size_t i)const noexcept {return at((S-1)*0.5f);}
inline float& mid(size_t i) noexcept {return at((S-1)*0.5f);}
constexpr float quarter(size_t i)const noexcept {return at((S-1)*0.25f);}
inline float& quarter(size_t i) noexcept {return at((S-1)/4);}
constexpr float three_quarter(size_t i)const noexcept {return at((S-1)*0.25f);}
inline float& three_quarter(size_t i) noexcept {return at((S-1)*0.75f);}
constexpr float sum()const noexcept{float result=0; for(size_t i=0;i<S;++i)result+=data[i]; return result;}
constexpr float avg()const noexcept{return sum()/S; }
constexpr float variance()const noexcept{const float AVG{sum()/S}; float result=0; for(size_t i=0; i<S;++i)result+=(data[i]-AVG)*(data[i]-AVG); return result;};
inline float& operator[](size_t i)noexcept
{
    return data[i];
}
constexpr float operator[](size_t i)const noexcept
{
    return data[i];
}
inline void flip()noexcept
{
    for(size_t i=0; i<S/2;++i)swap(i,S-i-1);
}


};


template<size_t S>
constexpr array<S> operator+(const array<S>& a,const array<S>&b)
{
    array<S> retVal;
    for(size_t i=0; i<S;++i)retVal[i]=a[i]+b[i];
    return retVal;
}
template<size_t S>
constexpr array<S> operator-(const array<S>& a,const array<S>&b)
{
    array<S> retVal;
    for(size_t i=0; i<S;++i)retVal[i]=a[i]-b[i];
    return retVal;
}
template<size_t S>
constexpr array<S> operator*(const array<S>& a,const array<S>&b)
{
    array<S> retVal;
    for(size_t i=0; i<S;++i)retVal[i]=a[i]*b[i];
    return retVal;
}
template<size_t S>
constexpr array<S> operator/(const array<S>& a,const array<S>&b)
{
    array<S> retVal;
    for(size_t i=0; i<S;++i)retVal[i]=a[i]/b[i];
    return retVal;
}
template<size_t S>
constexpr array<S> operator*(const array<S>& a, float x)
{
    array<S> retVal;
    for(size_t i=0; i<S;++i)retVal[i]=a[i]*x;
    return retVal;
}
template<size_t S>
constexpr array<S> operator*(float x,const array<S>& a)
{
    array<S> retVal;
    for(size_t i=0; i<S;++i)retVal[i]=a[i]*x;
    return retVal;
}
template<size_t S>
constexpr array<S> operator/(const array<S>& a, float x)
{
    array<S> retVal;
    for(size_t i=0; i<S;++i)retVal[i]=a[i]/x;
    return retVal;
}


template<size_t S>
constexpr float dot(const array<S>& a,const array<S>&b)
{
    return (a*b).sum();
}

template<size_t S>
inline std::ostream& operator<<(std::ostream& stream, const FGE::array<S>& a)
{
    stream<<"{";
    for(size_t i=0; i<S-1;++i)stream<<a[i]<<","; 
    if(S!=0)stream<<a[S-1];
    stream<<"}\n";

    return stream; 
}


};



#endif