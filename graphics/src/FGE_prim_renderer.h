#ifndef FGE_PRIM_RENDERER_H_
#define FGE_PRIM_RENDERER_H_
#include "glad.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <unordered_map>
#include "FGE_sdl_types.h"
#include "FGE_prim_geometry.h"


#define PRIM_DEBUG 
#ifdef PRIM_DEBUG
#define PRIM_DEBUG_PRINT(x) std::cout<<x<<std::endl;
#else 
#define PRIM_DEBUG_PRINT(x)
#endif



#define __FGE_EXPAND_COLOR_STRUCT(__COLOR_STRUCT__)(float)__COLOR_STRUCT__.r,(float)__COLOR_STRUCT__.g,(float)__COLOR_STRUCT__.b,(float)__COLOR_STRUCT__.a
#define FGE_START_RENDER() glClear(GL_COLOR_BUFFER_BIT)

#ifndef FGE_CUSTOM_ENTRY_POINT
#define FGE_Main WinMain
#endif

inline struct __FGE_PRIMITIVE_RENDERER{unsigned int vertexBuffer; unsigned int vertexArray; unsigned int elementBuffer;
 unsigned int shaderProgram;}
__fge_primitive_renderer;
inline class __FGE_PRIMITIVE_GlUniformSystem
{
private:
std::unordered_map<const char*, int> uniformMap;
public:
inline __FGE_PRIMITIVE_GlUniformSystem() {};
inline __FGE_PRIMITIVE_GlUniformSystem& add(const char* uniform)
{
    int location=glGetUniformLocation(__fge_primitive_renderer.shaderProgram,uniform);
    uniformMap.insert({uniform,location});
    return *this;
}
inline __FGE_PRIMITIVE_GlUniformSystem& setf(const char* uniform,float val)
{
    glUniform1f(uniformMap.at(uniform),val);
    return *this;
}
inline __FGE_PRIMITIVE_GlUniformSystem& setf(const char* uniform,float val1, float val2)
{
    glUniform2f(uniformMap.at(uniform),val1,val2);
    return *this;
}
inline __FGE_PRIMITIVE_GlUniformSystem& setf(const char* uniform,float val1, float val2, float val3)
{
    glUniform3f(uniformMap.at(uniform),val1,val2,val3);
    return *this;
}
inline __FGE_PRIMITIVE_GlUniformSystem& setf(const char* uniform,float val1, float val2, float val3, float val4)
{
    glUniform4f(uniformMap.at(uniform),val1,val2,val3, val4);
    return *this;
}
inline __FGE_PRIMITIVE_GlUniformSystem& seti(const char* uniform,int val1)
{
    glUniform1i(uniformMap.at(uniform),val1);
    return *this;
}
inline __FGE_PRIMITIVE_GlUniformSystem& seti(const char* uniform,int val1, int val2)
{
    glUniform2i(uniformMap.at(uniform),val1,val2);
    return *this;
}
inline __FGE_PRIMITIVE_GlUniformSystem& seti(const char* uniform,int val1, int val2, int val3)
{
    glUniform3i(uniformMap.at(uniform),val1,val2,val3);
    return *this;
}
inline __FGE_PRIMITIVE_GlUniformSystem& seti(const char* uniform,int val1, int val2, int val3, int val4)
{
    glUniform4i(uniformMap.at(uniform),val1,val2,val3, val4);
    return *this;
}


} __fge_primitive_uniform_sys;




constexpr std::string_view ShaderVersion{"#version 330 core\n"};

inline std::vector<unsigned int> __FGE_PRIMITIVE_INDICES(size_t S)noexcept
{  
    std::vector<unsigned int> retVal;
    retVal.reserve(3*(S-1));

    for(size_t i=1; i<S-1; ++i){retVal.push_back(0);retVal.push_back(i);retVal.push_back(i+1); }
    return retVal;
}

inline std::string __FGE_PRIMITIVE_GetShaderSrc(const char* src)noexcept
{
    std::ifstream file(src,std::ios::binary);
    std::string shaderSource;
    shaderSource+=ShaderVersion;
    {
    std::string line="";
    while(std::getline(file,line))shaderSource+=line+"\n";
    shaderSource+="\0";
    }

    return shaderSource;
}

constexpr void __FGE_PRIMITIVE_SetAttributes(int dimensions=2,int index= 0,int stride=0  )noexcept
{
if(!stride)stride=dimensions; 

glVertexAttribPointer(index, dimensions, GL_FLOAT, GL_FALSE, stride * sizeof(float),
(void*)0);
glEnableVertexAttribArray(0);
}

inline void __FGE_PRIM_RENDER_INIT(const char* vertexSrc, const char* fragmentSrc, const std::vector<const char*>& uniformArgs )noexcept
{
    glGenBuffers(1,&__fge_primitive_renderer.vertexBuffer);
    glGenBuffers(1,&__fge_primitive_renderer.elementBuffer);
    glGenVertexArrays(1,&__fge_primitive_renderer.vertexArray);

    unsigned int vertexId=glCreateShader(GL_VERTEX_SHADER);
    std::string retVal=__FGE_PRIMITIVE_GetShaderSrc(vertexSrc);
    const char* Ssource=retVal.c_str();
    glShaderSource(vertexId, 1, &Ssource, NULL);
    glCompileShader(vertexId);

    #ifdef PRIM_DEBUG
    int success;
    char infoLog[512];
    glGetShaderiv(vertexId, GL_COMPILE_STATUS, &success);
    if(!success)
    {
    glGetShaderInfoLog(vertexId, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" <<
    infoLog << std::endl;
    }
    #endif

    unsigned int fragmentId=glCreateShader(GL_FRAGMENT_SHADER);
    retVal=__FGE_PRIMITIVE_GetShaderSrc(fragmentSrc);
    Ssource=retVal.c_str();
    glShaderSource(fragmentId, 1, &Ssource, NULL);
    glCompileShader(fragmentId);

    #ifdef PRIM_DEBUG
    
    glGetShaderiv(fragmentId, GL_COMPILE_STATUS, &success);
    if(!success)
    {
    glGetShaderInfoLog(fragmentId, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" <<
    infoLog << std::endl;
    }
    #endif

    __fge_primitive_renderer.shaderProgram=glCreateProgram();
    glAttachShader(__fge_primitive_renderer.shaderProgram,vertexId);
    glAttachShader(__fge_primitive_renderer.shaderProgram,fragmentId);
    glLinkProgram(__fge_primitive_renderer.shaderProgram);
    
    glDeleteShader(vertexId); glDeleteShader(fragmentId);

    #ifdef PRIM_DEBUG
  
    glGetProgramiv(__fge_primitive_renderer.shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
    glGetProgramInfoLog(__fge_primitive_renderer.shaderProgram, 512, NULL, infoLog);
    std::cout << "ERROR::PROGRAM::COMPILATION_FAILED\n" <<
    infoLog << std::endl;
    }
    #endif

    glUseProgram(__fge_primitive_renderer.shaderProgram);

    for(auto& el: uniformArgs)__fge_primitive_uniform_sys.add(el);
}
inline void __FGE_PRIM_RENDER_DELETE()noexcept
{
    glDeleteProgram(__fge_primitive_renderer.shaderProgram);
    glDeleteBuffers(1,&__fge_primitive_renderer.vertexBuffer);
    glDeleteBuffers(1,&__fge_primitive_renderer.elementBuffer);
    glDeleteVertexArrays(1,&__fge_primitive_renderer.vertexArray);
}
#define FGE_PRIM_RENDER_DELETE() __FGE_PRIM_RENDER_DELETE()
inline int __FGE_PRIM_RENDER_UNIFORM_LOCATION(const char* uniform)noexcept
{
    return glGetUniformLocation(__fge_primitive_renderer.shaderProgram,uniform);
} 


inline void __FGE_PRIM_RENDER_FILL_SHAPE(float* data, size_t Size,GLenum usage=GL_DYNAMIC_DRAW)noexcept 
{
    const size_t indicesSize{3*(Size-1)};

    glBindVertexArray(__fge_primitive_renderer.vertexArray);
    glBindBuffer(GL_ARRAY_BUFFER,__fge_primitive_renderer.vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER,sizeof(float)*2*Size,data,usage);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,__fge_primitive_renderer.elementBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(unsigned int)*indicesSize,__FGE_PRIMITIVE_PRELOAD_INDICES,usage);
    
    __FGE_PRIMITIVE_SetAttributes(2);

    glUseProgram(__fge_primitive_renderer.shaderProgram);
    glDrawElements(GL_TRIANGLES,indicesSize,GL_UNSIGNED_INT,0);
}
inline void __FGE_PRIM_RENDER_DRAW_SHAPE(float* data, size_t Size,GLenum usage=GL_DYNAMIC_DRAW)noexcept 
{
    glBindVertexArray(__fge_primitive_renderer.vertexArray);
    glBindBuffer(GL_ARRAY_BUFFER,__fge_primitive_renderer.vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER,sizeof(float)*2*Size,data,usage);
    
    __FGE_PRIMITIVE_SetAttributes(2);
    glBindVertexArray(__fge_primitive_renderer.vertexArray);
    glUseProgram(__fge_primitive_renderer.shaderProgram);
    glDrawArrays(GL_LINE_STRIP,0,Size);
}
inline void __FGE_PRIM_RENDER_FILL_TRIANGLE(float* data, size_t Size,GLenum usage=GL_DYNAMIC_DRAW)noexcept 
{
    glBindVertexArray(__fge_primitive_renderer.vertexArray);
    glBindBuffer(GL_ARRAY_BUFFER,__fge_primitive_renderer.vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER,sizeof(float)*2*Size,data,usage);
    
    __FGE_PRIMITIVE_SetAttributes(2);
    glBindVertexArray(__fge_primitive_renderer.vertexArray);
    glUseProgram(__fge_primitive_renderer.shaderProgram);
    glDrawArrays(GL_TRIANGLES,0,Size);
}
inline void __FGE_PRIM_RENDER_FILL_SIMPLE_ARROW(GLenum usage=GL_DYNAMIC_DRAW)noexcept 
{
  

    glBindVertexArray(__fge_primitive_renderer.vertexArray);
    glBindBuffer(GL_ARRAY_BUFFER,__fge_primitive_renderer.vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER,sizeof(float)*14,(float*)__FGE_PRIMITIVE_PRELOAD_SIMPLE_ARROW_VERTICES,usage);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,__fge_primitive_renderer.elementBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(unsigned int)*9,(unsigned int*)__FGE_PRIMITIVE_PRELOAD_SIMPLE_ARROW_INDICES,usage);
    
    __FGE_PRIMITIVE_SetAttributes(2);

    glUseProgram(__fge_primitive_renderer.shaderProgram);
    glDrawElements(GL_TRIANGLES,9,GL_UNSIGNED_INT,0);
}

inline void __FGE_PRIM_RENDER_DRAW_SIMPLE_ARROW(GLenum usage=GL_DYNAMIC_DRAW)noexcept 
{
    glBindVertexArray(__fge_primitive_renderer.vertexArray);
    glBindBuffer(GL_ARRAY_BUFFER,__fge_primitive_renderer.vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER,sizeof(float)*16,__FGE_PRIMITIVE_PRELOAD_SIMPLE_ARROW_VERTICES,usage);
    
    __FGE_PRIMITIVE_SetAttributes(2);
    glBindVertexArray(__fge_primitive_renderer.vertexArray);
    glUseProgram(__fge_primitive_renderer.shaderProgram);
    glDrawArrays(GL_LINE_STRIP,0,8);
}

/*FIX DRAW CODE, DEPRECATED*/
inline void __FGE_PRIM_RENDER_FILL_FANCY_ARROW(GLenum usage=GL_DYNAMIC_DRAW)noexcept 
{
  

    glBindVertexArray(__fge_primitive_renderer.vertexArray);
    glBindBuffer(GL_ARRAY_BUFFER,__fge_primitive_renderer.vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER,sizeof(float)*16,(float*)__FGE_PRIMITIVE_PRELOAD_FANCY_ARROW_VERTICES,usage);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,__fge_primitive_renderer.elementBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(unsigned int)*12,(unsigned int*)__FGE_PRIMITIVE_PRELOAD_FANCY_ARROW_INDICES,usage);
    
    __FGE_PRIMITIVE_SetAttributes(2);

    glUseProgram(__fge_primitive_renderer.shaderProgram);
    glDrawElements(GL_TRIANGLES,12,GL_UNSIGNED_INT,0);
}
/*FIX DRAW CODE, DEPRECATED*/
inline void __FGE_PRIM_RENDER_DRAW_FANCY_ARROW(GLenum usage=GL_DYNAMIC_DRAW)noexcept 
{
    glBindVertexArray(__fge_primitive_renderer.vertexArray);
    glBindBuffer(GL_ARRAY_BUFFER,__fge_primitive_renderer.vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER,sizeof(float)*16,__FGE_PRIMITIVE_PRELOAD_FANCY_ARROW_VERTICES,usage);
    
    __FGE_PRIMITIVE_SetAttributes(2);
    glBindVertexArray(__fge_primitive_renderer.vertexArray);
    glUseProgram(__fge_primitive_renderer.shaderProgram);
    glDrawArrays(GL_LINE_STRIP,0,8);
}


inline void FGE_RENDER_SMOOTH()
{
    glEnable( GL_LINE_SMOOTH );
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}


inline void FGE_INIT_RENDER_DEFAULT()
{
    __FGE_PRIM_RENDER_INIT("../shader/default_vertex.glsl","../shader/default_fragment.glsl",{"myColor","myAngle","myShape","myCamera","windSize","coordMode","drawImage"});
    __fge_primitive_uniform_sys.setf("myColor",0,0,0,0).setf("myAngle",0).setf("myShape",0,0,1,1).setf("myCamera",0,0)
    .setf("windSize",800,600).seti("coordMode",0).seti("drawImage",false);
}

inline void FGE_UseRelativeCoords()noexcept
{
   __fge_primitive_uniform_sys.seti("coordMode",0);
}
inline void FGE_UseAbsoluteCoords(float winWidth, float winHeight)noexcept
{
   __fge_primitive_uniform_sys.seti("coordMode",1).setf("windSize",winWidth,winHeight);
}
inline void FGE_SetColor(const FGE_Color& col)noexcept
{
 __fge_primitive_uniform_sys.setf("myColor",__FGE_EXPAND_COLOR_STRUCT(col));
}
inline void FGE_SetClearColor(const FGE_Color& col)noexcept
{
    glClearColor(col.r/255.0f,col.g/255.0f,col.b/255.0f,col.a/255.0f);
}
inline void FGE_SetCamera(const FGE_FPoint& p)noexcept
{
 __fge_primitive_uniform_sys.setf("myCamera",p.x,p.y);
}
inline void FGE_WorldShift(float x, float y, float w, float h)noexcept
{
__fge_primitive_uniform_sys.setf("myShape",x,y,w,h);
}
inline void FGE_WorldRotate(float angle)noexcept
{
__fge_primitive_uniform_sys.setf("myAngle",angle);
}


#endif