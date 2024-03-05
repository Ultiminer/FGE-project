#include <iostream>
#include "math.h"
#include "FGE_setup.h"
#include "FGE_image.h"

//This library can be super extended with any kind of SDL, SDL2, or OpenGL functionality 
int FGE_Main()
{
    BUILD_ALL_TARGETS;
    //Creating the window context
    FGE::Window wind= FGE_General_Init();
    
    FGE_FRect rect={0,0,200,200};
    FGE_Texture text="test.png";
    FGE::SRect cool{100,100,20,20};
    FGE_Loop_Start(wind);
    FGE_DrawImage(rect,text);
    cool.Draw(FGE::blue).UpdateShape();
    FGE_Loop_End(wind);

    FGE_Return();
}