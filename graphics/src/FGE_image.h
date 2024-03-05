#ifndef FGE_IMAGE_H_
#define FGE_IMAGE_H_
#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"
#include "glad.h"
#include "FGE_debug.h"
#include <iostream>
#include "FGE_sdl_types.h"
#include "FGE_shape.h"

struct FGE_Texture
{
unsigned int id=0; 
int width=0;
int height=0; 
int channelNum=0; 

FGE_Texture(const char* path)
{

glGenTextures(1, &id);
glBindTexture(GL_TEXTURE_2D, id);
// set the texture wrapping/filtering options (on the currently bound texture object)
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

stbi_set_flip_vertically_on_load(true);  

unsigned char *data = stbi_load(path, &width, &height, &channelNum, 0);
if (!data) FGE_EXIT("Image path was nonexistent-> exit!");


glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
glGenerateMipmap(GL_TEXTURE_2D);


stbi_image_free(data);
}
inline void bind()
{
glActiveTexture(GL_TEXTURE0);
glBindTexture(GL_TEXTURE_2D,id);
}
~FGE_Texture()
{
    glDeleteTextures(1,&id);    
}

};

constexpr std::array<float,16> __MakeImageVerticies(const FGE_FRect& rect)
{
    return {rect.x-rect.w,rect.y+rect.h,0,1,rect.x+rect.w,rect.y+rect.h,1,1,rect.x+rect.w,rect.y-rect.h,1,0,rect.x-rect.w,rect.y-rect.h,0,0};
}
inline void FGE_DrawImage(const FGE_FRect& rect, FGE_Texture& texture)
{

    __fge_primitive_uniform_sys.seti("ourTexture",0).seti("drawImage",1);
    const size_t indicesSize{6};
    const auto verticies=__MakeImageVerticies(rect);

    glBindVertexArray(__fge_primitive_renderer.vertexArray);
    glBindBuffer(GL_ARRAY_BUFFER,__fge_primitive_renderer.vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER,sizeof(float)*4*4,&verticies,GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,__fge_primitive_renderer.elementBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(unsigned int)*indicesSize,__FGE_PRIMITIVE_PRELOAD_INDICES,GL_DYNAMIC_DRAW);
    
    __FGE_PRIMITIVE_SetAttributes(2,1,4);
    __FGE_PRIMITIVE_SetAttributes(2,0,4);

    glBindVertexArray(__fge_primitive_renderer.vertexArray);
    texture.bind();

    glUseProgram(__fge_primitive_renderer.shaderProgram);
    glDrawElements(GL_TRIANGLES,indicesSize,GL_UNSIGNED_INT,0);
    __fge_primitive_uniform_sys.seti("drawImage",0);
    glDisableVertexAttribArray(1);
}

#endif