#ifndef FGE_IMAGE_H_
#define FGE_IMAGE_H_


#include <iostream>
#include "FGE_shape.h"
#include <unordered_map>
#include <vector>
#include "FGE_bmp.h"

/* 
----------------------IMAGE LIBRARY THAT SUPPORTS BMP FILES---------------------
---------------------------------TODO------------------------------------------
(1) PROVIDE A DEFINITION FOR THE LOAD_BMP FUNCTION
(2) MAKE IMAGE CREATION WORK WITH THE CURRENT SHADERS
*/




inline void FGE_TextureInit()
{
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

struct FGE_Texture
{
    unsigned int id;  
    FGE::BMP_DESCRIPTOR descriptor;
    FGE_Texture(const char* imgPath)
    {
    descriptor= FGE::LoadBitmap(imgPath); 
      glGenTextures( 1,&id); 
      glActiveTexture(GL_TEXTURE0);
      glBindTexture(GL_TEXTURE_2D, id); 

      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      

      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, descriptor.width, descriptor.height, 0,GL_RGB, GL_BYTE, (char*)descriptor.data.data());
      glGenerateMipmap(GL_TEXTURE_2D);
    }
    ~FGE_Texture()
    {
        glDeleteTextures(1,&id);
        descriptor.data.erase(descriptor.data.begin(),descriptor.data.end());
    }
};

inline void FGE_DrawTexture(const FGE_Texture& texture, const FGE::SRect& rect)
{
    __fge_primitive_uniform_sys.setf("colorEdge", rect.xm,rect.ym);
    __fge_primitive_uniform_sys.seti("drawImage", 1);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture.id);
    rect.Draw();
    __fge_primitive_uniform_sys.seti("drawImage", 0);
}

#endif