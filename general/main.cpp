#include <iostream>
#include "FGE_bmp.h"

#define Print(x) std::cout<< x <<std::endl;


int main()
{
   auto file=FGE::LoadBitmap("black_square.bmp");
    std::cout<<"width: "<<file.width<<" height: "<<file.height<<" channelNum: "<<file.channelNum<<std::endl;
    return 0;
}