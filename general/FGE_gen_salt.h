#ifndef FGE_GEN_SALT_H_
#define FGE_GEN_SALT_H_
#include <array>
#include <string>
#include "FGE_random.h"
/*Weird ways of encoding text, so that hackers get confused :O*/
constexpr size_t FGE_RAND_TEXT_SEQU_MIN =129; 
constexpr size_t FGE_RAND_TEXT_SEQU_MAX =217; 

namespace FGE{
/*Returns a unique text sequence between FGE_RAND_TEXT_SEQU_MIN and FGE_RAND_TEXT_SEQU_MAX*/
inline std::string GenerateSalt()
{
    random.seed_me_pls();
    std::string retVal; 
    const size_t S=random(FGE_RAND_TEXT_SEQU_MIN,FGE_RAND_TEXT_SEQU_MAX);
    for(size_t i=0; i<S;++i)retVal.push_back((char)(33+random(1,5)*random(1,19))); 
    return retVal; 
}








};




#endif