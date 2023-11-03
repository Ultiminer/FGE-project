#ifndef FGE_EFFICIENT_TYPES_H_
#define FGE_EFFICIENT_TYPES_H_
#include<iostream>
#include <cstdint>
#include <stdio.h>
#include <string>
#include <functional>




#define FGE_IGNORE(x)



namespace FGE{
/*CONST POINTER TO CONST */
using i32ptr =const int32_t* const;
using u32ptr =const uint32_t* const;
using i64ptr =const int64_t* const;
using u64ptr =const uint64_t* const;
using i16ptr =const int16_t* const;
using u16ptr =const uint32_t* const;
using i8ptr =const int8_t* const;
using u8ptr =const uint8_t* const;
using f32ptr =const float* const;
using f64ptr =const double* const;
using strptr= const std::string* const;
/*NORMAL POINTER*/
using i32mptr = int32_t*;
using u32mptr = uint32_t*;
using i64mptr = int64_t*;
using u64mptr = uint64_t*;
using i16mptr = int16_t*;
using u16mptr = uint32_t*;
using i8mptr = int8_t*;
using u8mptr = uint8_t*;
using f32mptr = float*;
using f64mptr = double*;
using strmptr= std::string*;
/*IMMUTABLE TYPES*/
using i32 =const int32_t;
using u32 =const uint32_t;
using i64 =const int64_t;
using u64 =const uint64_t;
using i16 =const int16_t;
using u16 =const uint32_t;
using i8 =const int8_t;
using u8 =const uint8_t;
using f32 =const float;
using f64 =const double;
using str=const std::string;
/*IMMUTABLE EXPRESSIONS (TRUE CONSTANTS)*/
#define i32c constexpr int32_t
#define u32c constexpr uint32_t
#define i64c constexpr int64_t
#define u64c constexpr uint64_t
#define i16c constexpr int16_t
#define u16c constexpr uint32_t
#define i8c constexpr int8_t
#define u8c constexpr uint8_t
#define f32c constexpr float
#define f64c constexpr double
#define strc constexpr std::string
/*MUTABLE TYPES*/
using i32m = int32_t;
using u32m = uint32_t;
using i64m = int64_t;
using u64m = uint64_t;
using i16m = int16_t;
using u16m = uint32_t;
using i8m = int8_t;
using u8m = uint8_t;
using f32m = float;
using f64m = double;
using strm=std::string;
/*REFERENCE TYPES*/
using i32r = int32_t&;
using u32r = uint32_t&;
using i64r = int64_t&;
using u64r = uint64_t&;
using i16r = int16_t&;
using u16r = uint32_t&;
using i8r = int8_t&;
using u8r = uint8_t&;
using f32r = float&;
using f64r = double&;
using strr= std::string&;


template<class A, class B>
constexpr A& mem_cast(B& obj)noexcept{return *(A*)(&obj);}

template<typename T>
struct mem_ptr
{
T*const adr;
constexpr T&& val()noexcept
{
    return *adr; 
}
constexpr T& ref()noexcept
{
    return *adr; 
}

~mem_ptr()noexcept
{
    delete adr; 
}

};
template<typename T>
struct secure_ptr
{
const T*const adr;
constexpr T&& val()noexcept
{
    return *adr; 
}

~secure_ptr()noexcept
{
    delete adr; 
}

};
template<typename T>
struct unsafe_ptr
{
T* adr;
constexpr T&& val()noexcept
{
    return *adr; 
}
constexpr T& ref()noexcept
{
    return *adr; 
}
};




}

#endif