#ifndef FGE_TEXT_H_
#define FGE_TEXT_H_

#include "FGE_image.h"

inline FGE_Texture __fge_basic_font{"../ttf/text.png"};

inline void FGE_DrawCharacter(const FGE_FRect& rect, char c)
{
    FGE_DrawImage(rect,__fge_basic_font);
}




#endif