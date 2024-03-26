#ifndef FGE_ICON_H_
#define FGE_ICON_H_

#include "FGE_shape.h"
#include <vector>
#include "FGE_file_parsing.h"
namespace FGE{

struct Icon
{
    FGE::SRect iconFrame{0,0,100,100};
    std::vector<FGE::SCircle>scircle;
    std::vector<FGE::SRect>srect;
    std::vector<FGE::SEllipse>sellipse;
    std::vector<FGE::SPlus>splus;
    std::vector<FGE::SRoundedRect>splus;
    std::vector<FGE::SSquircle>splus;

    constexpr float ElementaryPosTransform(const char* p)
    {
        if(strcmp(p,"left")==0)return iconFrame.xm-iconFrame.w2;
        if(strcmp(p,"right")==0)return iconFrame.xm+iconFrame.w2;
        if(strcmp(p,"top")==0)return iconFrame.ym+iconFrame.h2;
        if(strcmp(p,"bottom")==0)return iconFrame.ym-iconFrame.h2;
        if(strcmp(p,"centerX")==0)return iconFrame.xm;
        if(strcmp(p,"centerY")==0)return iconFrame.ym;
        if(contains(p,'%'))return atof_ignore(p)*0.02*iconFrame.w2; 

        return atof_ignore(p);
    }
    inline float PosTransform(std::string p)
    {
        const SeperatorList l=SeperateString(p,{'+'});
        float sum=0;
        for(auto& el:l)sum+=ElementaryPosTransform(el.c_str());

        return sum; 
    }
    //ToDO: Create File Parser
    inline void LoadIconData(const char* path)
    {
        
    }

};



}

#endif