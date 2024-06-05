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
#include "FGE_debug.h"




constexpr unsigned int __FGE_PRIMITIVE_PRELOAD_INDICES[]=
{0,1,2,0,2,3,0,3,4,0,4,5,0,5,6,0,6,7,0,7,8,0,8,9,0,9,10,0,10,11,0,11,12,0,12,13,0,13,14,0,14,15,0,15,16,0,16,17,0,17,18,0,18,19,0,19,20,0,20,21,0,21,22,0,22,23,0,23,24,0,24,25,0,25,26,0,26,27,0,27,28,0,28,29,0,29,30,0,30,31,0,31,32,0,32,33,0,33,34,0,34,35,0,35,36,0,36,37,0,37,38,0,38,39,0,39,40,0,40,41,0,41,42,0,42,43,0,43,44,0,44,45,0,45,46,0,46,47,0,47,48,0,48,49,0,49,50,0,50,51,0,51,52,0,52,53,0,53,54,0,54,55,0,55,56,0,56,57,0,57,58,0,58,59,0,59,60,0,60,61,0,61,62,0,62,63,0,63,64,0,64,65,0,65,66,0,66,67,0,67,68,0,68,69,0,69,70,0,70,71,0,71,72,0,72,73,0,73,74,0,74,75,0,75,76,0,76,77,0,77,78,0,78,79,0,79,80,0,80,81,0,81,82,0,82,83,0,83,84,0,84,85,0,85,86,0,86,87,0,87,88,0,88,89,0,89,90,0,90,91,0,91,92,0,92,93,0,93,94,0,94,95,0,95,96,0,96,97,0,97,98,0,98,99,0,99,100,0,100,101,0,101,102,0,102,103,0,103,104,0,104,105,0,105,106,0,106,107,0,107,108,0,108,109,0,109,110,0,110,111,0,111,112,0,112,113,0,113,114,0,114,115,0,115,116,0,116,117,0,117,118,0,118,119,0,119,120,0,120,121,0,121,122,0,122,123,0,123,124,0,124,125,0,125,126,0,126,127,0,127,128,0,128,129,0,129,130,0,130,131,0,131,132,0,132,133,0,133,134,0,134,135,0,135,136,0,136,137,0,137,138,0,138,139,0,139,140,0,140,141,0,141,142,0,142,143,0,143,144,0,144,145,0,145,146,0,146,147,0,147,148,0,148,149,0,149,150,0,150,151,0,151,152,0,152,153,0,153,154,0,154,155,0,155,156,0,156,157,0,157,158,0,158,159,0,159,160,0,160,161,0,161,162,0,162,163,0,163,164,0,164,165,0,165,166,0,166,167,0,167,168,0,168,169,0,169,170,0,170,171,0,171,172,0,172,173,0,173,174,0,174,175,0,175,176,0,176,177,0,177,178,0,178,179,0,179,180,0,180,181,0,181,182,0,182,183,0,183,184,0,184,185,0,185,186,0,186,187,0,187,188,0,188,189,0,189,190,0,190,191,0,191,192,0,192,193,0,193,194,0,194,195,0,195,196,0,196,197,0,197,198,0,198,199,0,199,200,0,200,201,0,201,202,0,202,203,0,203,204,0,204,205,0,205,206,0,206,207,0,207,208,0,208,209,0,209,210,0,210,211,0,211,212,0,212,213,0,213,214,0,214,215,0,215,216,0,216,217,0,217,218,0,218,219,0,219,220,0,220,221,0,221,222,0,222,223,0,223,224,0,224,225,0,225,226,0,226,227,0,227,228,0,228,229,0,229,230,0,230,231,0,231,232,0,232,233,0,233,234,0,234,235,0,235,236,0,236,237,0,237,238,0,238,239,0,239,240,0,240,241,0,241,242,0,242,243,0,243,244,0,244,245,0,245,246,0,246,247,0,247,248,0,248,249,0,249,250,0,250,251,0,251,252,0,252,253,0,253,254,0,254,255,0,255,256,0,256,257,0,257,258,0,258,259,0,259,260,0,260,261,0,261,262,0,262,263,0,263,264,0,264,265,0,265,266,0,266,267,0,267,268,0,268,269,0,269,270,0,270,271,0,271,272,0,272,273,0,273,274,0,274,275,0,275,276,0,276,277,0,277,278,0,278,279,0,279,280,0,280,281,0,281,282,0,282,283,0,283,284,0,284,285,0,285,286,0,286,287,0,287,288,0,288,289,0,289,290,0,290,291,0,291,292,0,292,293,0,293,294,0,294,295,0,295,296,0,296,297,0,297,298,0,298,299,0,299,300,0,300,301,0,301,302,0,302,303,0,303,304,0,304,305,0,305,306,0,306,307,0,307,308,0,308,309,0,309,310,0,310,311,0,311,312,0,312,313,0,313,314,0,314,315,0,315,316,0,316,317,0,317,318,0,318,319,0,319,320,0,320,321,0,321,322,0,322,323,0,323,324,0,324,325,0,325,326,0,326,327,0,327,328,0,328,329,0,329,330,0,330,331,0,331,332,0,332,333,0,333,334,0,334,335,0,335,336,0,336,337,0,337,338,0,338,339,0,339,340,0,340,341,0,341,342,0,342,343,0,343,344,0,344,345,0,345,346,0,346,347,0,347,348,0,348,349,0,349,350,0,350,351,0,351,352,0,352,353,0,353,354,0,354,355,0,355,356,0,356,357,0,357,358,0,358,359,0,359,360,0,360,361,0,361,362,0,362,363,0,363,364,0,364,365,0,365,366,0,366,367,0,367,368,0,368,369,0,369,370,0,370,371,0,371,372,0,372,373,0,373,374,0,374,375,0,375,376,0,376,377,0,377,378,0,378,379,0,379,380,0,380,381,0,381,382,0,382,383,0,383,384,0,384,385,0,385,386,0,386,387,0,387,388,0,388,389,0,389,390,0,390,391,0,391,392,0,392,393,0,393,394,0,394,395,0,395,396,0,396,397,0,397,398,0,398,399,0,399,400,0,400,401,0,401,402,0,402,403,0,403,404,0,404,405,0,405,406,0,406,407,0,407,408,0,408,409,0,409,410,0,410,411,0,411,412,0,412,413,0,413,414,0,414,415,0,415,416,0,416,417,0,417,418,0,418,419,0,419,420,0,420,421,0,421,422,0,422,423,0,423,424,0,424,425,0,425,426,0,426,427,0,427,428,0,428,429,0,429,430,0,430,431,0,431,432,0,432,433,0,433,434,0,434,435,0,435,436,0,436,437,0,437,438,0,438,439,0,439,440,0,440,441,0,441,442,0,442,443,0,443,444,0,444,445,0,445,446,0,446,447,0,447,448,0,448,449,0,449,450,0,450,451,0,451,452,0,452,453,0,453,454,0,454,455,0,455,456,0,456,457,0,457,458,0,458,459,0,459,460,0,460,461,0,461,462,0,462,463,0,463,464,0,464,465,0,465,466,0,466,467,0,467,468,0,468,469,0,469,470,0,470,471,0,471,472,0,472,473,0,473,474,0,474,475,0,475,476,0,476,477,0,477,478,0,478,479,0,479,480,0,480,481,0,481,482,0,482,483,0,483,484,0,484,485,0,485,486,0,486,487,0,487,488,0,488,489,0,489,490,0,490,491,0,491,492,0,492,493,0,493,494,0,494,495,0,495,496,0,496,497,0,497,498,0,498,499,0,499,500,0,500,501,0,501,502,0,502,503,0,503,504,0,504,505,0,505,506,0,506,507,0,507,508,0,508,509,0,509,510,0,510,511};


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
(void*)(index*dimensions*sizeof(float)));
glEnableVertexAttribArray(index);
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

    #ifndef FGE_Active
    int success;
    char infoLog[512];
    glGetShaderiv(vertexId, GL_COMPILE_STATUS, &success);
    if(!success)
    {
    glGetShaderInfoLog(vertexId, 512, NULL, infoLog);
    FGE_EXIT("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" <<infoLog);
    
    }
    #endif

    unsigned int fragmentId=glCreateShader(GL_FRAGMENT_SHADER);
    retVal=__FGE_PRIMITIVE_GetShaderSrc(fragmentSrc);
    Ssource=retVal.c_str();
    glShaderSource(fragmentId, 1, &Ssource, NULL);
    glCompileShader(fragmentId);

    #ifndef FGE_Active
    
    if(!success)
    {    
    glGetShaderiv(fragmentId, GL_COMPILE_STATUS, &success);
    glGetShaderInfoLog(fragmentId, 512, NULL, infoLog);
    FGE_EXIT("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" <<infoLog ) ;
    }
    #endif

    __fge_primitive_renderer.shaderProgram=glCreateProgram();
    glAttachShader(__fge_primitive_renderer.shaderProgram,vertexId);
    glAttachShader(__fge_primitive_renderer.shaderProgram,fragmentId);
    glLinkProgram(__fge_primitive_renderer.shaderProgram);
    
    glDeleteShader(vertexId); glDeleteShader(fragmentId);

    #ifndef FGE_Active
  
    glGetProgramiv(__fge_primitive_renderer.shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
    glGetProgramInfoLog(__fge_primitive_renderer.shaderProgram, 512, NULL, infoLog);
    FGE_EXIT("ERROR::PROGRAM::COMPILATION_FAILED\n" <<infoLog );
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
#define FGE_DELETE_RENDER() __FGE_PRIM_RENDER_DELETE()
inline int __FGE_PRIM_RENDER_UNIFORM_LOCATION(const char* uniform)noexcept
{
    return glGetUniformLocation(__fge_primitive_renderer.shaderProgram,uniform);
} 


inline void FGE_FILL_SHAPE(float* data, size_t Size,GLenum usage=GL_DYNAMIC_DRAW)noexcept 
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
inline void FGE_DRAW_SHAPE(float* data, size_t Size,GLenum usage=GL_DYNAMIC_DRAW)noexcept 
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



inline void FGE_RENDER_SMOOTH()
{
    glEnable( GL_LINE_SMOOTH );
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}


inline void FGE_INIT_RENDER_DEFAULT()
{
    __FGE_PRIM_RENDER_INIT("../gfx_src/default_vertex.glsl","../gfx_src/default_fragment.glsl",{"myColor","windSize","coordMode","drawImage","ourTexture"});
    __fge_primitive_uniform_sys.setf("myColor",0,0,0,0)
    .setf("windSize",800,600).seti("coordMode",0).seti("drawImage",0).seti("ourTexture",0);

    FGE_RENDER_SMOOTH();
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

#endif