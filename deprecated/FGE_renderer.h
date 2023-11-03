#ifndef FGE_RENDERER_H_
#define FGE_RENDERER_H_
#include "glad.h"
#include "FGE_sdl_types.h"
#include "FGE_gl_wrapper.h"
#include "FGE_shape_map.h"
namespace FGE{



class Renderer
{

public:
Renderer();

Renderer& DrawLine(float x1, float y1, float x2,float y2);
Renderer& DrawTriangle(const FGE_FPoint& a, const FGE_FPoint& b, const FGE_FPoint& c);
Renderer& DrawThickLine(float x1, float y1, float x2,float y2, float thickness);
Renderer& FillCircle(const FGE_Circle& circle, size_t precision=100);
Renderer& FillEllipse(const FGE_Ellipse& ellipse, size_t precision=100);
Renderer& FillShape(const std::vector<FGE_FPoint>& vertices);
Renderer& DrawShape(const std::vector<FGE_FPoint>& vertices);
Renderer& DrawEllipse(const FGE_Ellipse& ellipse, size_t precision=100);
Renderer& DrawRect(const FGE_FRect& rect);
Renderer& FillRect(const FGE_FRect& rect);
Renderer& DrawCircle(const FGE_Circle& circle, size_t precision=100);
Renderer& DrawGraph(const std::function<float(float)>& graph,float start, float end, float epsilon, float thick);
Renderer& DrawGraph(const std::function<float(float)>& graph,float start, float end, float epsilon);

Renderer& SetColor(const FGE_Color& color);
Renderer& TransformWorld(float shiftX,float shiftY, float multiplyX, float multiplyY);


private:
Renderer& AddShapeSupport(const char* shape_name, bool indexed=false);
template <size_t S>
Renderer& AddShapeSupport(const std::array<const char*,S>& shape_name, bool indexed=false);

private:
//Buffers
GlVertexBufferSystem vertexBuffer;GlElementBufferSystem elementBuffer; GlVertexArraySystem vertexArray; 
//Shaders
VertexShader defaultVertex; FragmentShader defaultFragment; ShaderProgram program;
//Uniforms
GlUniformSystem uniformSystem; 
private:
inline void _primitive__Draw(float* data, size_t Size, const char* shapeName)noexcept
{
    vertexArray.bind(shapeName);
    vertexBuffer.bind(shapeName).copyData(data,GL_DYNAMIC_DRAW,Size*2);
    SetDrawAttributes(2);
    elementBuffer.bind(shapeName);
    program.use().draw(GL_LINE_STRIP,Size);
}
inline void _primitive__Fill(float* data, size_t Size, const char* shapeName)noexcept
{
    const std::vector<unsigned int> indices= CreateCircleIndexArray(Size); 
    vertexArray.bind(shapeName);
    vertexBuffer.bind(shapeName).copyData(data,GL_DYNAMIC_DRAW,Size*2);
    elementBuffer.bind(shapeName).copyData(indices.data(),GL_DYNAMIC_DRAW,indices.size());
    SetDrawAttributes(2);
    elementBuffer.bind(shapeName);
    program.use().drawIndices(GL_TRIANGLES,indices.size());
}
    
};


}


#endif