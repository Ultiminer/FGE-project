#include "FGE_renderer.h"

namespace FGE{

Renderer& Renderer::AddShapeSupport(const char* name, bool indexed)
{
vertexBuffer.add(name);
vertexArray.add(name);
if(indexed)elementBuffer.add(name);
return *this;
}
template <size_t S>
Renderer& Renderer::AddShapeSupport(const std::array<const char*,S>& shape_name, bool indexed)
{
   vertexBuffer.add<S>(shape_name);
   vertexArray.add<S>(shape_name);
   if(indexed)elementBuffer.add<S>(shape_name);
   return *this;
}


Renderer::Renderer():defaultVertex("../shader/default_vertex.glsl"), defaultFragment("../shader/default_fragment.glsl")
{
    SetBgColor({255,0,255,255});
    program.attach(defaultVertex.id).attach(defaultFragment.id).link().use();
    AddShapeSupport<2>({"line","triangle"}).AddShapeSupport<4>({"rect","circle","ellipse","shape"},true);
    SetDrawAttributes();
    uniformSystem=program.id; 
    uniformSystem.add("myColor").add("myBlend").add("myShift").add("myMultiply");

    uniformSystem.setf("myMultiply",1.f,1.f).seti("myColor", 255,255,255,255).setf("myShift",0,0);

}
Renderer& Renderer::DrawLine(float x1, float y1, float x2,float y2)
{
    vertexArray.bind("line");
    vertexBuffer.bind("line").copyData<4>({x1,y1,x2,y2},GL_DYNAMIC_DRAW);
    
    SetDrawAttributes(2);
    program.use().draw(GL_LINES,2);
    return *this; 
}
Renderer& Renderer::DrawTriangle(const FGE_FPoint& a, const FGE_FPoint& b, const FGE_FPoint& c)
{
    vertexArray.bind("triangle");
    vertexBuffer.bind("triangle").copyData<6>({a.x,a.y,b.x,b.y,c.x,c.y},GL_DYNAMIC_DRAW);
    
    SetDrawAttributes(2);
    program.use().draw(GL_TRIANGLES,3);
    return *this; 
}

Renderer& Renderer::DrawThickLine(float x1, float y1, float x2,float y2, float thickness)
{
    const std::array<FGE_FPoint,4>vertices=MapLineToRect({x1,y1,x2,y2},thickness);
    vertexArray.bind("rect");
    vertexBuffer.bind("rect").copyData((float*)(vertices.data()),GL_DYNAMIC_DRAW,8);
    elementBuffer.bind("rect").copyData<6>({0,1,2,2,3,1},GL_DYNAMIC_DRAW);
    SetDrawAttributes(2);
    elementBuffer.bind("rect");
    program.use().drawIndices(GL_TRIANGLES,6);


    return *this; 
}
Renderer& Renderer::FillCircle(const FGE_Circle& circle, size_t precision)
{
    const std::vector<FGE_FPoint> vertices= MapOutCircle(circle,precision); 
    _primitive__Fill((float*)vertices.data(),vertices.size(),"circle");
    return *this; 
}
Renderer& Renderer::FillEllipse(const FGE_Ellipse& ellipse, size_t precision)
{
    const std::vector<FGE_FPoint> vertices= MapOutEllipse(ellipse,precision); 
    _primitive__Fill((float*)vertices.data(),vertices.size(),"ellipse");
    return *this; 
}
Renderer& Renderer::SetColor(const FGE_Color& color)
{
    uniformSystem.seti("myColor",color.r,color.g,color.b,color.a);
    return *this;   
}

Renderer& Renderer::TransformWorld(float shiftX,float shiftY, float multiplyX, float multiplyY)
{
    uniformSystem.setf("myShift",shiftX,shiftY);
    uniformSystem.setf("myMultiply",multiplyX,multiplyY);
    return *this;
}
Renderer& Renderer::FillShape(const std::vector<FGE_FPoint>& vertices)
{
    _primitive__Fill((float*)vertices.data(),vertices.size(),"shape");
    return *this; 
}
Renderer& Renderer::DrawShape(const std::vector<FGE_FPoint>& Vertices )
{
    std::vector<FGE_FPoint>vertices=Vertices;
    vertices.push_back(vertices.front());
    _primitive__Draw((float*)vertices.data(),vertices.size(),"shape");
    return *this; 
}
Renderer& Renderer::DrawEllipse(const FGE_Ellipse& ellipse, size_t precision)
{
    std::vector<FGE_FPoint> vertices= MapOutEllipse(ellipse,precision); 
    vertices.push_back(vertices.front());
    _primitive__Draw((float*)vertices.data(),vertices.size(),"ellipse");
    return *this;
}
Renderer& Renderer::DrawRect(const FGE_FRect& rect)
{
    std::vector<FGE_FPoint> vertices= MapOutRect(rect); 
    vertices.push_back(vertices.front());
    _primitive__Draw((float*)vertices.data(),vertices.size(),"rect");
    return *this;
}
Renderer& Renderer::FillRect(const FGE_FRect& rect)
{
    std::vector<FGE_FPoint> vertices= MapOutRect(rect); 
    _primitive__Fill((float*)vertices.data(),vertices.size(),"rect");
    return *this;
}
Renderer& Renderer::DrawCircle(const FGE_Circle& circle, size_t precision)
{
    std::vector<FGE_FPoint> vertices= MapOutCircle(circle,precision); 
    vertices.push_back(vertices.front());
    _primitive__Draw((float*)vertices.data(),vertices.size(),"circle");
    return *this;
}
Renderer& Renderer::DrawGraph(const std::function<float(float)>& graph,float start, float end, float epsilon, float thick)
{
    // Alphablending an
    std::vector<FGE_FPoint> vertices= MapOutGraph(graph,start,end,thick,epsilon);
    
    const std::vector<unsigned int> indices= CreateGraphIndexArray(vertices.size()); 
    const std::vector<unsigned int> outlineIndices= CreateGraphOutlineIndexArray(vertices.size()); 
    vertexArray.bind("shape");
    vertexBuffer.bind("shape").copyData(vertices.data(),GL_STATIC_DRAW,vertices.size()*2);
    elementBuffer.bind("shape").copyData(indices.data(),GL_STATIC_DRAW,indices.size());
    SetDrawAttributes(2);
    program.use().drawIndices(GL_TRIANGLES,indices.size());

    elementBuffer.bind("shape").copyData(outlineIndices.data(),GL_STATIC_DRAW,outlineIndices.size());
    SetDrawAttributes(2);
    program.use().drawIndices(GL_LINE_STRIP,outlineIndices.size());

    return *this; 
}
Renderer& Renderer::DrawGraph(const std::function<float(float)>& graph,float start, float end, float epsilon)
{
    std::vector<FGE_FPoint> vertices= MapOutGraph(graph,start,end,epsilon); 
    _primitive__Draw((float*)vertices.data(),vertices.size(),"shape");
    return *this;
}



}