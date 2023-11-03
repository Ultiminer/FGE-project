#ifndef FGE_QUADRATURE_H_
#define FGE_QUADRATURE_H_
#include <functional>

namespace FGE{
constexpr float GAUSS_FIVE_OVER_NINE{0.55555555556f};
constexpr float GAUSS_W1{0.774596669241f};


constexpr float forwardDiff(const std::function<float(float)>& f, const float x)
{
    return f(x+1)-f(x);
}
template<size_t precision>
constexpr float finiteDiffP(const std::function<float(float)>& f, const float x)noexcept
{
    return precision*(f(x+1/precision)-f(x));
}
template<size_t precision>
constexpr float finiteDiffN(const std::function<float(float)>& f, const float x)noexcept
{
    return precision*(f(x+1/precision)-f(x));
}
template<size_t precision>
constexpr float finiteDiffA(const std::function<float(float)>& f, const float x)noexcept
{
    constexpr float delta{1/(2*precision)};
    return precision*(f(x+delta)-f(x-delta));
}

template<size_t precision>
constexpr float finiteMult(const std::function<float(float)>& f, const float x)noexcept
{
    const float t{1+1/precision};
    return precision*(f(tx)-f(x))/x;
}

constexpr float FastQuadrature(const std::function<float(float)>& f, const float a, const float b)
{
    const float diff{b-a};
    return diff*f(a+diff*0.5f); 
}
constexpr float GaußQuadrature3(const std::function<float(float)>& f, const float a, const float b)
{
    const float nF{(b-a)*0.5f};const float pF{(b+a)*0.5f};
    const float nFw1{nF*GAUSS_W1};

    return nF*(f(pF-nFw1)*GAUSS_FIVE_OVER_NINE+f(pF)*0.8888888888889f+f(pF+nFw1)*GAUSS_FIVE_OVER_NINE);
}
template<size_t precision>
constexpr float RectangleQuadrature(const std::function<float(float)>& f, const float a, const float b)
{
    float Res=0; 
    const float forwardDiff{(b-a)/precision};
    for(size_t i=0; i<precision; ++i)Res+=f(a+forwardDiff*i)*forwardDiff;

    return Res;      
}
template<size_t precision>
constexpr float TriangularQuadrature(const std::function<float(float)>& f, const float a, const float b)
{
    float Res=0; 
    const float forwardDiff{(b-a)/precision};
    const float forwardDiffD2{forwardDiff*0.5f};
    float first=f(a); 
    for(size_t i=1; i<precision+1; ++i)
    {
        const float next{f(a+forwardDiff*i)};
        Res+=(first+next)*forwardDiffD2;
        first=std::move(next); 
    }
    return Res;      
}








};
 


#endif