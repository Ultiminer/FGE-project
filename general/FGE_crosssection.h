#ifndef FGE_CROSSSECTION_H_
#define FGE_CROSSSECTION_H_
#include <functional>
#include "FGE_quadrature.h"

namespace FGE{

template<size_t targetNum, size_t reactionNum, size_t beamNum>
constexpr float TotalCrosssection(float beamArea)noexcept
{
    constexpr float conversion{reactionNum/(beamNum*targetNum)};
    return conversion*beamArea;
}
template<size_t targetNum, size_t reactionNum>
constexpr float TotalCrosssection(float beamFlux)noexcept
{
    return reactionNum/(beamFlux*targetNum);
}
template<size_t targetNum>
constexpr float DifferentialCrosssection(float beamFlux, const std::function<float(float)>& reactionOfAngle, float ANGLE)noexcept
{
    return FGE::finiteDiffA<100>(reactionOfAngle, ANGLE)/(beamFlux*targetNum);
}
template<size_t targetNum,  size_t beamNum>
constexpr float DifferentialCrosssection(float beamArea, const std::function<float(float)>& reactionOfAngle, float ANGLE)noexcept
{
    constexpr float conversion{beamArea/(beamNum*targetNum)};
    return FGE::finiteDiffA<100>(reactionOfAngle, ANGLE)*conversion;
}
template<size_t targetNum>
constexpr float Luminosity(float beamFlux)
{
    return beamFlux*targetNum;
}
template<size_t targetNum, size_t beamNum>
constexpr float Luminosity(float beamArea)
{
    return beamNum*targetNum/beamArea;
}
template<size_t beamNum>
constexpr float BeamFlux(float beamArea)
{
    return beamNum/beamArea; 
}





}
#endif