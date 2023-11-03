#ifndef FGE_IMAGE_H_
#define FGE_IMAGE_H_
#include "glad.h"
#include <unordered_map>
#include "FGE_sdl_types.h"
#include "FGE_prim_renderer.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

inline void FGE_TextureInit()
{
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

struct FGE_Texture
{
    int width, height, channelNum;
    unsigned int id;  
    FGE_Texture(const char* imgPath)
    {
      unsigned char*data= stbi_load(imgPath, &width, &height, &channelNum, 0); 
        if(!data)exit(-1);
      glGenTextures(1, &id); 
      glBindTexture(GL_TEXTURE_2D, id); 
      FGE_TextureInit();
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
      glGenerateMipmap(GL_TEXTURE_2D);
      stbi_image_free(data);
    }
    ~FGE_Texture()
    {
        glDeleteTextures(1,&id);
    }
};


class FGE_TextureMap
{
private:
std::unordered_map<const char*, FGE_Texture>textMap;

public:
FGE_TextureMap(){}
FGE_TextureMap& Add(const char* name, const char* path)
{
    textMap.insert({name,FGE_Texture(path)});
    return *this; 
}
FGE_Texture& Get(const char* name)
{
    return textMap.at(name);
}



};

inline void FGE_DrawTexture(const FGE_Texture& texture,const FGE_FRect& rect, float angle=0)
{
    __fge_primitive_uniform_sys.seti("drawImage", true);
    glBindTexture(GL_TEXTURE_2D, texture.id);
    __fge_primitive_uniform_sys.setf("myShape",rect.x,rect.y,rect.w,rect.h).setf("myAngle",angle);
    __FGE_PRIM_RENDER_FILL_SHAPE((float*)__FGE_PRIMITIVE_PRELOAD_SQUARE_DATA,4);
     __fge_primitive_uniform_sys.seti("drawImage", false);
}

#endif