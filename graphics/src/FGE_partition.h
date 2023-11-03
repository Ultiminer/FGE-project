#ifndef FGE_PARTITION_H_
#define FGE_PARTITION_H_
#include "FGE_sdl_types.h"

struct BoxPartitions{
const FGE_FPoint Center; 
const FGE_FPoint TopLeft; 
const FGE_FPoint BottomLeft; 
const FGE_FPoint TopRight; 
const FGE_FPoint BottomRight; 
const FGE_FRect BoxLeft;
const FGE_FRect BoxRight;
const FGE_FRect BoxHeader;
const FGE_FRect BoxFooter;
const FGE_FRect BoxMiddle;
const FGE_FRect Rect; 
BoxPartitions(const FGE_FRect& rect, float relPartX=0.33, float relPartY=0.33):
Center({rect.x,rect.y}),TopLeft({rect.x-rect.w,rect.y-rect.h}),BottomLeft({rect.x-rect.w,rect.y+rect.h}),TopRight({rect.x+rect.w,rect.y+rect.h}),BottomRight({rect.x+rect.w,rect.y-rect.h})
,BoxLeft({TopLeft.x+rect.w*relPartX,Center.y,rect.w*relPartX,rect.h*(1-2*relPartY)})
,BoxRight({TopRight.x-rect.w*relPartX,Center.y,rect.w*relPartX,rect.h*(1-2*relPartY)})
,BoxHeader({Center.x,BottomLeft.y-rect.h*relPartY,rect.w,rect.h*relPartY})
,BoxFooter({Center.x,TopLeft.y+rect.h*relPartY,rect.w,rect.h*relPartY})
,BoxMiddle({Center.x,Center.y,rect.w*(1-2*relPartX),rect.h*(1-2*relPartY)})
,Rect{rect}
{}

constexpr FGE_FRect operator()()const 
{
return Rect;
}
};


struct BoxSubPartitions{
const FGE_FPoint Center; 
const FGE_FPoint TopLeft; 
const FGE_FPoint BottomLeft; 
const FGE_FPoint TopRight; 
const FGE_FPoint BottomRight; 
const BoxPartitions BoxLeft;
const BoxPartitions BoxRight;
const BoxPartitions BoxHeader;
const BoxPartitions BoxFooter;
const BoxPartitions BoxMiddle;
BoxSubPartitions(const FGE_FRect& rect, float relPartX=0.2, float relPartY=0.14):
Center({rect.x,rect.y}),TopLeft({rect.x-rect.w,rect.y-rect.h}),BottomLeft({rect.x-rect.w,rect.y+rect.h}),TopRight({rect.x+rect.w,rect.y+rect.h}),BottomRight({rect.x+rect.w,rect.y-rect.h})
,BoxLeft({TopLeft.x+rect.w*relPartX,Center.y,rect.w*relPartX,rect.h*(1-2*relPartY)})
,BoxRight({TopRight.x-rect.w*relPartX,Center.y,rect.w*relPartX,rect.h*(1-2*relPartY)})
,BoxHeader({Center.x,BottomLeft.y-rect.h*relPartY,rect.w,rect.h*relPartY})
,BoxFooter({Center.x,TopLeft.y+rect.h*relPartY,rect.w,rect.h*relPartY})
,BoxMiddle({Center.x,Center.y,rect.w*(1-2*relPartX),rect.h*(1-2*relPartY)})
{}

};



#endif