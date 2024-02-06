#ifndef FGE_QUICK_START_H_
#define FGE_QUICK_START_H_

#define FGE_FAST_VSYNC

#include "src/FGE_color.h"
#include "src/FGE_window.h"
#include "src/FGE_shape.h"


using namespace FGE; 
class FGE_Entry
{
    public:
    FGE::Window window; 
    void Init();
    void Loop();
    void End(); 
};
int FGE_Main()
{    
    //Creating the window context
    FGE_Entry entry; 
    entry.window=FGE::Window(); 
    entry.Init(); 
    
    //Initializing FGE functionality
    FGE_INIT_RENDER_DEFAULT();
    FGE_RENDER_SMOOTH();
     /*Creating BLACKPINK tm xDDD*/
    FGE_SetClearColor(FGE::lightpink|FGE::black);
    FGE_UseAbsoluteCoords(entry.window.GetWidth(),entry.window.GetHeight());

    while(entry.window.IsRunning())
    {
        FGE_START_RENDER();
        entry.Loop();
        entry.window.Swap();
        entry.window.PollEvents();
    }
    entry.End();
    FGE_PRIM_RENDER_DELETE();
    return 0;
}



#endif