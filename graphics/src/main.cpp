#include <iostream>
#include "math.h"
#include "FGE_setup.h"
#include "FGE_image.h"
#include "FGE_font.h"
//This library can be super extended with any kind of SDL, SDL2, or OpenGL functionality 
int FGE_Main()
{
    BUILD_ALL_TARGETS;
    //Creating the window context
    FGE::Window wind= FGE_General_Init();
    
    FGE::SRect rect={0,0,100,100};
    FGE_Texture text="test.png";
    FGE::SRect cool{100,100,40,40};
    FGE::Label label=FGE::Label({0,0,400,50},"Hi Mum, ",FGE::LabelStd);
    FGE_Loop_Start(wind);
    cool.Draw(FGE::blue).UpdateShape();
    FGE_DrawImage(rect,text);
    rect.Rotate(0.01).UpdateShape();
    label.Draw();
    FGE_Loop_End(wind);

    FGE_Return();
}