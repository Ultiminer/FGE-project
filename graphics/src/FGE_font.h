#ifndef FGE_FONT_H_
#define FGE_FONT_H_

#include "FGE_image.h"
#include "FGE_shape.h"
#include "FGE_sdl_types.h"
#include "FGE_styles.h"
#include <string>
#include "FGE_window.h"
#include "quick_math.h"

inline void FGE_DrawFont(const FGE_FRect& rect, char c,bool loadHalf=false)
{
    static FGE_Texture base_font="../ttf/text.png";

    FGE_DrawImage(rect,base_font,1.f/95.f-loadHalf*0.5f/95.f,1,(float)(c-32)/95.f);
}
inline void FGE_DrawFont(const FGE_FRect& rect, std::string text, float l)
{
    const float lpadded=l*0.9f; 
    for(size_t i=0; i<text.size();++i)
    {
        if(rect.w-i*lpadded<l)
        {
        if(rect.w-i*lpadded>=l/2)
        FGE_DrawFont({rect.x+i*lpadded,rect.y,l/2,rect.h},text.at(i),true);
        return;
        }
        FGE_DrawFont({rect.x+i*lpadded,rect.y,l,rect.h},text.at(i));
    }
    
}

namespace FGE{

struct Label
{    
    FGE::SRect labelRect={}; 
    float padding=0; 
    FGE_Color outside={}; 
    FGE_Color inside={}; 
    std::string txt;
    Label(){}
    Label(const FGE_FRect& LabelRect,const std::string &Txt,float Padding=7,FGE_Color Outside=FGE::lightgray,FGE_Color Inside= FGE::darkgray)
    {
        labelRect={LabelRect.x+LabelRect.w/2,LabelRect.y+LabelRect.h/2,LabelRect.w/2,LabelRect.h/2}; 
        padding=Padding;
        outside=Outside;
        inside=Inside;
        txt=Txt;
    }
    Label(const FGE_FRect& LabelRect,const std::string &Txt, const LabelStyle& Style)
    {
        labelRect={LabelRect.x+LabelRect.w/2,LabelRect.y+LabelRect.h/2,LabelRect.w/2,LabelRect.h/2}; 
        padding=Style.padding;
        outside=Style.outside;
        inside=Style.inside;
        txt=Txt;
    }
    inline Label& Draw()
    {
        FGE::SRect innerRect={labelRect.xm,labelRect.ym,labelRect.w2-padding/2,labelRect.h2-padding/2};
        labelRect.Draw(outside).DrawBorder();
        innerRect.Draw(inside);
        FGE_DrawFont({innerRect.xm-innerRect.w2,innerRect.ym-innerRect.h2,innerRect.w2*2,innerRect.h2*2},txt,innerRect.h2);

        return *this;
    }
    inline Label& SetText(const std::string& Txt)
    {
        txt=Txt;
        return *this;
    }
    inline Label& SetStyle(const LabelStyle& Style)
    {
        padding=Style.padding;
        outside=Style.outside;
        inside=Style.inside;
        return *this;
    }
    inline Label& SetRect(const FGE_FRect& LabelRect)
    {
        labelRect={LabelRect.x+LabelRect.w/2,LabelRect.y+LabelRect.h/2,LabelRect.w/2,LabelRect.h/2}; 
        return *this;
    }
    inline Label& SetX(float x)
    {
        labelRect.xm=x+labelRect.w2;
        return *this;
    }
    inline Label& SetY(float y)
    {
        labelRect.ym=y+labelRect.h2;
        return *this;
    }
    inline Label& SetW(float w)
    {
        labelRect.w2=w/2;
        return *this;
    }
    inline Label& SetH(float h)
    {
        labelRect.h2=h/2;
        return *this;
    }
    constexpr float GetX()const
    {
        return labelRect.xm-labelRect.w2;
    }
    constexpr float GetY()const
    {
        return labelRect.ym-labelRect.h2;
    }
    constexpr float GetW()const
    {
        return 2*labelRect.w2;
    }
    constexpr float GetH()const
    {
        return 2*labelRect.h2;
    }
    inline std::string GetText()const
    {
        return txt; 
    }
    /*ASSUMES QWERTZ keyboard lol*/
    inline Label& GetInput(FGE::Window& wind)
    {
        if(wind.KeyDown(SDLK_BACKSPACE)){if(txt.size()>0)txt.erase(txt.begin()+txt.size()-1);return *this;}
        if(wind.GetUpKey())
        {
            if(wind.KeyDown('.')){txt+=":";return *this;}
            if(wind.KeyDown(',')){txt+=";";return *this;}
            if(wind.KeyDown('-')){txt+="_";return *this;}
            if(wind.KeyDown('+')){txt+="*";return *this;}
            if(wind.KeyDown('#')){txt+="'";return *this;}
            if(wind.KeyDown('<')){txt+=">";return *this;}
            if(wind.KeyDown(SDLK_BACKSLASH)){txt+="?";return *this;}


        }
        
        for(size_t i=32; i<32+95;++i)if(wind.KeyDown(i)){txt+=(char)i-(wind.GetUpKey()&&i>='a'&&i<='z')*32-(wind.GetUpKey()&&i>='0'&&i<='9')*16;return *this;}
        return *this;
    }
    constexpr bool OnHover(const FGE_Point& mouse)const
    {
        return (QM::abs(labelRect.xm-mouse.x)<labelRect.w2&&QM::abs(labelRect.ym-mouse.y)<labelRect.h2);
    }
  
    inline Label& GetInputOnHover(FGE::Window& wind)
    {
        SDL_Point pos; 
        wind.QueryMousePos(pos);
        if(!OnHover(pos))return *this;
        GetInput(wind);
        return *this;
    }
    inline Label& Update()
    {
        labelRect.UpdateShape();
        return *this;
    }
};







};

#endif