#include <iostream>
#include "gfx_src/FGE_gen_init.h"

int FGE_Main() 
{
    remove("../build/main.o");
    //Creating the window context
    FGE::Window wind= FGE_General_Init();
    while(wind.IsRunning()){
        FGE_START_RENDER();
        wind.Swap();
        wind.PollEvents();
    }
    FGE_DELETE_RENDER();

    return 0;
}