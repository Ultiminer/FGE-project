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
    
    FGE::SRect rect={0,0,100,100};
    FGE_Texture text="test.bmp";
    FGE_Loop_Start(wind)
    FGE_DrawImage(rect,text);
    FGE_Loop_End(wind)

    FGE_Return();
}