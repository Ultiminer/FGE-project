#ifndef FGE_FRAC_H_
#define FGE_FRAC_H_
#include <cstdint>
#include <array>
#include <iostream>
namespace FGE{

#define __FGE_CFRACTION_TOP(x) (const int32_t)(((const int32_t*)(&(x)))[0])
#define __FGE_CFRACTION_BOTTOM(x) (const int32_t)(((const int32_t*)(&(x)))[0])
#define __FGE_FRACTION_TOP(x) ((( int32_t*)(&(x))))[0]
#define __FGE_FRACTION_BOTTOM(x) ((( int32_t*)(&(x))))[1]
#define __FGE_FRACTION(x) *((const frac*)(&(x)))

struct frac
{
private:
uint64_t data;
};

constexpr frac create_frac(int32_t top, int32_t bottom)noexcept
{
const union{struct{int32_t a; int32_t b;}; uint64_t data;}mapMeOutNOW{top,bottom};

return __FGE_FRACTION(mapMeOutNOW.data); 
}

constexpr frac operator+(const frac& a, const frac& b)noexcept
{
    return create_frac(__FGE_CFRACTION_TOP(a)*__FGE_CFRACTION_BOTTOM(b)+__FGE_CFRACTION_TOP(b)*__FGE_CFRACTION_BOTTOM(a),
    __FGE_CFRACTION_BOTTOM(a)*__FGE_CFRACTION_BOTTOM(b));
}
constexpr frac operator-(const frac& a, const frac& b)noexcept
{
    
    return create_frac(__FGE_CFRACTION_TOP(a)*__FGE_CFRACTION_BOTTOM(b)-__FGE_CFRACTION_TOP(b)*__FGE_CFRACTION_BOTTOM(a),
    __FGE_CFRACTION_BOTTOM(a)*__FGE_CFRACTION_BOTTOM(b));
}
constexpr frac operator*(const frac& a, const frac& b)noexcept
{
    return create_frac(__FGE_CFRACTION_TOP(a)*__FGE_CFRACTION_TOP(b),
    __FGE_CFRACTION_BOTTOM(a)*__FGE_CFRACTION_BOTTOM(b));
}
constexpr frac operator/(const frac& a, const frac& b)noexcept
{
    return create_frac(__FGE_CFRACTION_TOP(a)*__FGE_CFRACTION_BOTTOM(b),
    __FGE_CFRACTION_BOTTOM(a)*__FGE_CFRACTION_TOP(b));
}

inline std::ostream& operator<<(std::ostream& stream, const frac& f)noexcept
{
    stream<<"{"<<__FGE_FRACTION_TOP(f)<<"/"<<__FGE_FRACTION_BOTTOM(f)<<"}";
    return stream; 
}


}

#endif