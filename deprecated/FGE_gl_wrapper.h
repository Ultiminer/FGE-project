#ifndef FGE_GL_WRAPPER_H_
#define FGE_GL_WRAPPER_H_
#include "glad.h"
#include <array>
#include <fstream>
#include <string>
#include <iostream>
#include <unordered_map>
#include "FGE_sdl_types.h"

namespace FGE{


constexpr void SetBgColor(const FGE_Color& color)
{
    glClearColor(color.r,color.g,color.b,color.a);
}    
constexpr std::string_view ShaderVersion{"#version 330 core\n"};

constexpr void SetDrawAttributes(int dimensions=2,int index= 0,int stride=0  )
{
if(!stride)stride=dimensions; 

glVertexAttribPointer(index, dimensions, GL_FLOAT, GL_FALSE, stride * sizeof(float),
(void*)0);
glEnableVertexAttribArray(0);
}

using DrawMode= size_t;


inline std::string GetShaderSrc(const char* src)
{
    std::ifstream file(src,std::ios::binary);
    std::string shaderSource;
    shaderSource+=ShaderVersion;
    {
    std::string line="";
    while(std::getline(file,line))
    {
        shaderSource+=line+"\n";
    }
    shaderSource+="\0";
    }

    return shaderSource;
}


struct VertexShader{
unsigned int id;
inline VertexShader(const char* src)
{
    id=glCreateShader(GL_VERTEX_SHADER);
    std::string retVal=GetShaderSrc(src);
    const char* Ssource=retVal.c_str();
    glShaderSource(id, 1, &Ssource, NULL);
    glCompileShader(id);

    int success;
    char infoLog[512];
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if(!success)
    {
    glGetShaderInfoLog(id, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" <<
    infoLog << std::endl;
    }

    
}
inline ~VertexShader()
{
    glDeleteShader(id);
}
};

struct FragmentShader{
unsigned int id;
inline FragmentShader(const char* src)
    {
    id=glCreateShader(GL_FRAGMENT_SHADER);
    std::string retVal=GetShaderSrc(src);
    const char* Ssource=retVal.c_str();
    glShaderSource(id, 1, &Ssource, NULL);
    glCompileShader(id);

    int success;
    char infoLog[512];
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if(!success)
    {
    glGetShaderInfoLog(id, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" <<
    infoLog << std::endl;
    }

    
    }
inline ~FragmentShader()
{
    glDeleteShader(id);
}

};


struct ShaderProgram{
unsigned int id; 
inline ShaderProgram()
{
    id=glCreateProgram();
}
inline ShaderProgram& attach(unsigned int shader)
{
glAttachShader(id,shader);
return *this;
}
inline ShaderProgram& detach(unsigned int shader)
{
glDetachShader(id,shader);
return *this;
}
inline ShaderProgram& link()
{
glLinkProgram(id);
char infoLog[512];
int success;
glGetProgramiv(id, GL_LINK_STATUS, &success);
if(!success) {
glGetProgramInfoLog(id, 512, NULL, infoLog);
 std::cout << "ERROR::PROGRAM::COMPILATION_FAILED\n" <<
    infoLog << std::endl;
}
return *this;
}
inline ShaderProgram& use()
{
glUseProgram(id);
return *this;
}
inline ShaderProgram& draw(FGEenum mode, size_t first, size_t count)
{
    glDrawArrays(mode,first,count);
    return *this;
}
inline ShaderProgram& draw(FGEenum mode, size_t size)
{
    glDrawArrays(mode,0,size);
    return *this;
}
inline ShaderProgram& drawIndices(FGEenum mode,size_t indicesSize)
{
    glDrawElements(mode,indicesSize,GL_UNSIGNED_INT,0);
    return *this;
}


inline ~ShaderProgram()
{
    glDeleteProgram(id);
}
};

class GlVertexBufferSystem{
private:
std::unordered_map<const char*, unsigned int>vertexMap;
public:
GlVertexBufferSystem(){}
template <size_t S>
inline GlVertexBufferSystem(const std::array<const char*,S>& names){std::array<unsigned int,S> ids; glGenBuffers(ids.size(),ids.data());for(int i=0; i<names.size();++i)vertexMap.insert({names.at(i),ids.at(i)});}
template <size_t S>
inline GlVertexBufferSystem& add(const std::array<const char*,S>& names)
{
std::array<unsigned int,S> ids;
glGenBuffers(ids.size(),ids.data());
for(size_t i=0; i<names.size();++i)
vertexMap.insert({names.at(i),ids.at(i)});

return *this;
}

inline GlVertexBufferSystem& add(const char* name)
{
unsigned int id; 
glGenBuffers(1,&id);

vertexMap.insert({name,id});

return *this;
}
inline GlVertexBufferSystem& remove(const char* name)
{
glDeleteBuffers(1,&vertexMap.at(name));
vertexMap.erase(name);

return *this;
}
inline unsigned int getId(const char* name)const
{
    return vertexMap.at(name);
}
inline GlVertexBufferSystem& bind(const char* name)
{
    glBindBuffer(GL_ARRAY_BUFFER, vertexMap.at(name));
    return *this;
}
inline GlVertexBufferSystem& unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    return *this;
}
inline ~GlVertexBufferSystem()
{
    for(auto& el: vertexMap)remove(el.first);
}
template <size_t S>
inline GlVertexBufferSystem& copyData(const std::array<float,S>& vertices, const DrawMode& mode)
{
    glBufferData(GL_ARRAY_BUFFER, S*sizeof(float), vertices.data(), mode);

    return *this;
}
inline GlVertexBufferSystem& copyData(const void* vertices, const DrawMode& mode, size_t size)
{
    glBufferData(GL_ARRAY_BUFFER, size*sizeof(float), vertices, mode);

    return *this;
}
};
class GlVertexArraySystem{
private:
std::unordered_map<const char*, unsigned int>vertexMap;
public:
GlVertexArraySystem(){}
template <size_t S>
inline GlVertexArraySystem(const std::array<const char*,S>& names){std::array<unsigned int,S> ids; glGenVertexArrays(ids.size(),ids.data());for(int i=0; i<names.size();++i)vertexMap.insert({names.at(i),ids.at(i)});}
template <size_t S>
inline GlVertexArraySystem& add(const std::array<const char*,S>& names)
{
std::array<unsigned int,S> ids;
glGenVertexArrays(ids.size(),ids.data());
for(size_t i=0; i<names.size();++i)
vertexMap.insert({names.at(i),ids.at(i)});

return *this;
}

inline GlVertexArraySystem& add(const char* name)
{
unsigned int id; 
glGenVertexArrays(1,&id);

vertexMap.insert({name,id});

return *this;
}
inline GlVertexArraySystem& remove(const char* name)
{
glDeleteVertexArrays(1,&vertexMap.at(name));
vertexMap.erase(name);

return *this;
}
inline unsigned int getId(const char* name)const
{
    return vertexMap.at(name);
}
inline GlVertexArraySystem& bind(const char* name)
{
    const unsigned int id=std::move(vertexMap.at(name));
    glBindVertexArray(id);
    return *this;
}
inline GlVertexArraySystem& unbind()
{
    glBindVertexArray(0);
    return *this;
}
inline ~GlVertexArraySystem()
{
    for(auto& el: vertexMap)remove(el.first);
}

};
class GlElementBufferSystem{
private:
std::unordered_map<const char*, unsigned int>vertexMap;
public:
GlElementBufferSystem(){}
template <size_t S>
inline GlElementBufferSystem(const std::array<const char*,S>& names){std::array<unsigned int,S> ids; glGenBuffers(ids.size(),ids.data());for(int i=0; i<names.size();++i)vertexMap.insert({names.at(i),ids.at(i)});}
template <size_t S>
inline GlElementBufferSystem& add(const std::array<const char*,S>& names)
{
std::array<unsigned int,S> ids;
glGenBuffers(ids.size(),ids.data());
for(size_t i=0; i<names.size();++i)
vertexMap.insert({names.at(i),ids.at(i)});

return *this;
}

inline GlElementBufferSystem& add(const char* name)
{
unsigned int id; 
glGenBuffers(1,&id);

vertexMap.insert({name,id});

return *this;
}
inline GlElementBufferSystem& remove(const char* name)
{
glDeleteBuffers(1,&vertexMap.at(name));
vertexMap.erase(name);

return *this;
}
inline unsigned int getId(const char* name)const
{
    return vertexMap.at(name);
}
inline GlElementBufferSystem& bind(const char* name)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexMap.at(name));
    return *this;
}
inline GlElementBufferSystem& unbind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    return *this;
}
inline ~GlElementBufferSystem()
{
    for(auto& el: vertexMap)remove(el.first);
}
template <size_t S>
inline GlElementBufferSystem& copyData(const std::array<unsigned int,S>& indices, const DrawMode& mode)
{
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(unsigned int), indices.data(), mode);

    return *this;
}
inline GlElementBufferSystem& copyData(const void* indices, const DrawMode& mode, size_t size)
{
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size*sizeof(unsigned int), indices, mode);

    return *this;
}
};


class GlUniformSystem
{
private:
std::unordered_map<const char*, int> uniformMap;
unsigned int shaderProgram=0;
public:
inline GlUniformSystem() {};
inline GlUniformSystem(unsigned int shaderProgramId):shaderProgram(shaderProgramId) {};
inline GlUniformSystem& add(const char* uniform)
{
    int location=glGetUniformLocation(shaderProgram,uniform);
    uniformMap.insert({uniform,location});
    return *this;
}
inline GlUniformSystem& setf(const char* uniform,float val)
{
    glUniform1f(uniformMap.at(uniform),val);
    return *this;
}
inline GlUniformSystem& setf(const char* uniform,float val1, float val2)
{
    glUniform2f(uniformMap.at(uniform),val1,val2);
    return *this;
}
inline GlUniformSystem& setf(const char* uniform,float val1, float val2, float val3)
{
    glUniform3f(uniformMap.at(uniform),val1,val2,val3);
    return *this;
}
inline GlUniformSystem& setf(const char* uniform,float val1, float val2, float val3, float val4)
{
    glUniform4f(uniformMap.at(uniform),val1,val2,val3, val4);
    return *this;
}
inline GlUniformSystem& seti(const char* uniform,int val1)
{
    glUniform1i(uniformMap.at(uniform),val1);
    return *this;
}
inline GlUniformSystem& seti(const char* uniform,int val1, int val2)
{
    glUniform2i(uniformMap.at(uniform),val1,val2);
    return *this;
}
inline GlUniformSystem& seti(const char* uniform,int val1, int val2, int val3)
{
    glUniform3i(uniformMap.at(uniform),val1,val2,val3);
    return *this;
}
inline GlUniformSystem& seti(const char* uniform,int val1, int val2, int val3, int val4)
{
    glUniform4i(uniformMap.at(uniform),val1,val2,val3, val4);
    return *this;
}


};

namespace FGE{
inline void BlendingMode()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA); 
}

}
}
#endif