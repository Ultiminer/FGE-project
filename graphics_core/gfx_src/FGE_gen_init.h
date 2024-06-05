#ifndef FGE_GEN_INIT_H_
#define FGE_GEN_INIT_H_
#include "FGE_image.h"
#include "FGE_prim_renderer.h"
#include "FGE_window.h"
#include "FGE_color.h"


inline FGE::Window FGE_General_Init()noexcept
{
    FGE::Window wind=FGE::Window();
     //Initializing FGE functionality
    FGE_INIT_RENDER_DEFAULT();
    FGE_RENDER_SMOOTH();
    FGE_SetClearColor(FGE::lightpink|FGE::black);
    FGE_UseAbsoluteCoords(wind.GetWidth(),wind.GetHeight());


    return wind;
}





#endif