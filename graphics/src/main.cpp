#include "FGE_window.h"
#include "FGE_shape.h"
#include <iostream>
#include "math.h"
#include "FGE_Color.h"

#define BUILD_ALL_TARGETS remove("../build/main.o");remove("../build/glad.o");

//This library can be super extended with any kind of SDL, SDL2, or OpenGL functionality 

int FGE_Main()
{
    BUILD_ALL_TARGETS;
    
    //Creating the window context
    FGE::Window wind= FGE::Window();
    
    //Initializing FGE functionality
    FGE_INIT_RENDER_DEFAULT();
    FGE_RENDER_SMOOTH();
     /*Creating BLACKPINK tm xDDD*/
    FGE_SetClearColor(FGE::lightpink|FGE::black);
    FGE_UseAbsoluteCoords(wind.GetWidth(),wind.GetHeight());

    //Specifying the necessary shapes
   // FGE::SArrow arrow{0,100,20,50,0};
    FGE::SRect rect={0,0,400,300};
    while(wind.IsRunning())
    {
        FGE_START_RENDER();
        
        rect.Draw(FGE::blue).Rotate(0.01).SetW2(sin(SDL_GetTicks()%1000)*400).UpdateShape();
        wind.Swap();
        wind.PollEvents();
    }

    FGE_PRIM_RENDER_DELETE();
    return 0;
}