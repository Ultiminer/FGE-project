#ifndef FGE_SHAPE_MAP_H_
#define FGE_SHAPE_MAP_H_
#include <array>
#include "FGE_sdl_types.h"
#include <vector>
#include "GCEM/gcem.hpp"
#include <functional>
#include <iostream>
namespace FGE{
constexpr float squirqule(float x, float a, size_t n=4)noexcept
{
    if(n%2==0)
    return gcem::pow(a-gcem::pow(x,n),1/n);
    
    return gcem::pow(a-gcem::pow(gcem::abs(x),n),1/n);
}

constexpr float square(float x)noexcept
{
    return x*x;
}

constexpr std::array<FGE_FPoint,4> MapLineToRect(const FGE_Line& line, float shift=1)noexcept
{
    const float multiplier{shift*gcem::inv_sqrt(square(line.x1-line.x2)+square(line.y1-line.y2))};
    const FGE_FPoint normal{(line.x2-line.x1)*multiplier,(line.y1-line.y2)*multiplier};
    return {{{line.x1+normal.x,line.y1+normal.y},{line.x1-normal.x,line.y1-normal.y}
    ,{line.x2+normal.x,line.y2+normal.y},{line.x2-normal.x,line.y2-normal.y}}};
}

//Maps out an Circle arc with N arc points, icnludes the middle point of the circle as first member angles are in radians

inline std::vector<FGE_FPoint> MapOutCircle(const FGE_Circle& circle, size_t N, float endAngle=6.29,float startAngle=0)noexcept
{
    const float angleRange{(endAngle-startAngle)};
    const float pushForward{angleRange/N};
    std::vector<FGE_FPoint> retVal;
    retVal.reserve(N);
    
    for(float i=startAngle; i<endAngle;i+=pushForward)
    {
    retVal.push_back({circle.x+circle.r*gcem::cos(i),circle.y+circle.r*gcem::sin(i)});
    }
    return retVal; 
}
inline std::vector<FGE_FPoint> MapOutRect(const FGE_FRect& rect)noexcept
{
    return {{{rect.x,rect.y},{rect.x+rect.w,rect.y},{rect.x+rect.w,rect.y+rect.h},{rect.x,rect.y+rect.h}}}; 
}

inline std::vector<unsigned int> CreateCircleIndexArray(size_t S)noexcept
{  
    std::vector<unsigned int> retVal;
    retVal.reserve(3*(S-1));
    for(size_t i=1; i<S-1; ++i){retVal.push_back(0);retVal.push_back(i);retVal.push_back(i+1);}
    return retVal;
}

inline std::vector<FGE_FPoint> MapOutEllipse(const FGE_Ellipse& ellipse, size_t N, float endAngle=6.29,float startAngle=0)noexcept
{
    const float angleRange{(endAngle-startAngle)};
    const float pushForward{angleRange/N};
    std::vector<FGE_FPoint> retVal;
    retVal.reserve(N+1);
    retVal.front()={ellipse.x,ellipse.y};
    
    for(float i=startAngle; i<endAngle;i+=pushForward)
    retVal.push_back({ellipse.x+ellipse.a*gcem::cos(i),ellipse.y+ellipse.b*gcem::sin(i)});

    return retVal; 
}
inline std::vector<FGE_FPoint> MapLineToCapsule(const FGE_Line& line, float shift=1)
{
    std::vector<FGE_FPoint> retVal;
    retVal.reserve(104);
    const float multiplier{shift*gcem::inv_sqrt(square(line.x1-line.x2)+square(line.y1-line.y2))};
    const FGE_FPoint normal{(line.x2-line.x1)*multiplier,(line.y1-line.y2)*multiplier};
    retVal= {{{line.x1+normal.x,line.y1+normal.y},{line.x2-normal.x,line.y2-normal.y}
    ,{line.x1-normal.x,line.y1-normal.y},{line.x2+normal.x,line.y2+normal.y}}};
    
    const float sAngle{gcem::atan((line.y2-line.y1)/(line.x2-line.x1))};
    const std::vector<FGE_FPoint> dataP1=MapOutCircle({line.x2,line.y2,shift},50,sAngle+3.141/2,sAngle-3.141/2);
    const std::vector<FGE_FPoint> dataP2=MapOutCircle({line.x1,line.y1,shift},50,sAngle+3.141*1.5,sAngle+3.141/2);

    retVal.insert(retVal.end(),dataP1.begin(),dataP1.end());
    retVal.insert(retVal.end(),dataP2.begin(),dataP2.end());
    return retVal;
}
inline std::vector<unsigned int> CreateGraphIndexArray(size_t S)noexcept
{  
    std::vector<unsigned int> retVal;
    for(unsigned int i=2; i<S-2; ++i){retVal.insert(retVal.end(),{i,i-1,i-2,i-1,i,i+1,i,i+1,i+2});}
    return retVal;
}
inline std::vector<unsigned int> CreateGraphOutlineIndexArray(size_t S)noexcept
{  
    std::vector<unsigned int> evens;
    std::vector<unsigned int> odds;

    for(unsigned int i=0; i<S*0.5f; ++i){evens.push_back(2*i); odds.insert(odds.begin(),2*i+1);}
    evens.insert(evens.end(),odds.begin(),odds.end());
    return evens;
}
constexpr FGE_FPoint MapGraph3P( FGE_FPoint& a, const FGE_FPoint& b, float height)
{
    const FGE_FPoint vec{b.x-a.x,b.y-a.y};
    const float multiplier{gcem::inv_sqrt(square(vec.x)+square(vec.y))*height};
    const FGE_FPoint normal{(a.y-b.y)*multiplier,(b.x-a.x)*multiplier};
    a.x-=normal.x; 
    a.y-=normal.y;
   
    return {a.x+vec.x/2+2*normal.x,a.y+vec.y/2+2*normal.y};
}
inline std::vector<FGE_FPoint> MapOutGraph(const std::function<float(float)>& f, float start, float end, float epsilon)noexcept
{
    std::vector<FGE_FPoint> pts; 
    for(float x=start+epsilon; x<=end; x+=epsilon)pts.push_back({x,f(x)});

    return pts;
}
inline std::vector<FGE_FPoint> MapOutGraph(const std::function<float(float)>& f, float start, float end, float thick, float epsilon)noexcept
{
    std::vector<FGE_FPoint> pts; 
    SDL_FPoint first={start,f(start)};
    for(float x=start+epsilon; x<=end; x+=epsilon)
    {
        const SDL_FPoint next={x,f(x)};
        pts.push_back(MapGraph3P(first,next,thick));pts.push_back(first);
        first=next;
    }


    return pts;
}

}
#endif