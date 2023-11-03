#ifndef FGE_TIMER_H_
#define FGE_TIMER_H_
#include "sysinfoapi.h"

namespace FGE
{
    struct Timer
    {
        size_t currTime=0; 
        size_t diffTime=0;
        Timer(){currTime=GetTickCount64();}
        Timer(size_t setTime){currTime=setTime;}
        inline size_t operator()()noexcept
        {
            return diffTime;
        }
        inline Timer& calc_diff()noexcept
        {
            diffTime=GetTickCount64()-currTime;
            return *this;
        }
        inline Timer& reset()noexcept
        {
            currTime=GetTickCount64();
            return *this;
        }
        inline Timer& reset(size_t newTime)noexcept
        {
            currTime=newTime;
            return *this;
        }
        inline size_t GetDiff()noexcept
        {
            return diffTime; 
        }
    };
} // namespace FGE



#endif