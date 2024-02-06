#include <iostream>
#include "math.h"
#include "FGE_setup.h"

//This library can be super extended with any kind of SDL, SDL2, or OpenGL functionality 
int FGE_Main()
{
    BUILD_ALL_TARGETS;
    //Creating the window context
    FGE::Window wind= FGE_General_Init();
    
    FGE::SSquircle rect={0,0,100,100};
    FGE_Loop_Start(wind)
        rect.Draw({yellow|brown}).DrawBorder();
    FGE_Loop_End(wind)
    

    FGE_Return();
}