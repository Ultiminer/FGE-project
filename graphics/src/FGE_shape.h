#ifndef FGE_SHAPE_H_
#define FGE_SHAPE_H_
#include "FGE_prim_renderer.h"
#include "math.h"
#include <array>
#include <string>
#include "GCEM/gcem.hpp"



/*Interface for the drawing operation and geometric manipulation of basic shapes*/
/*
-----------TODO----------------
>Transform the vertices every time position or object size changes, so there is no need for extensive uniform overloading 
>Add more shapes + Possibility to draw thick circle arcs and thick shape borders
>Mimic every css functionality
*/


namespace FGE{

constexpr float SHAPE_SMOOTHSTEP(float x)
{
    if(x>0.8)return 1; 
    if(x<-0.8)return -1; 
    return tanh(x);
}


/*REMARK: Maybe vectorize in the future*/
/*Vertices should only be transformed when parameters change, so there is performance gained by doing static transformations outside of the shader*/
template <size_t S>
constexpr std::array<float,S> TransformVertices(const float* const vertices, float xShift, float yShift=0, float widthMultiplier=1, float heightMultiplier=1, float rotateAngle=0)noexcept
{
    //Error ! Can not be 2d vectorized - contradicts underlying assumption
    if(S%2!=0)exit(-1);
    std::array<float,S> retValue; 

    if(rotateAngle==0)
    {
    for(size_t i=0; i<S;i+=2){
    retValue.at(i)=vertices[i]*widthMultiplier+xShift;
    retValue.at(i+1)=vertices[i+1]*heightMultiplier+yShift;
    }
    return retValue; 
    }

    //IMPLEMENT ANGLE VERSION HERE
    const float cosVal=gcem::cos(rotateAngle);
    const float sinVal=gcem::sin(rotateAngle);
    for(size_t i=0; i<S;i+=2)
    {
        const float nX=vertices[i]*widthMultiplier*cosVal+vertices[i+1]*heightMultiplier*sinVal;
        const float nY=-vertices[i]*widthMultiplier*sinVal+vertices[i+1]*heightMultiplier*cosVal;
        retValue.at(i)=nX+xShift;
        retValue.at(i+1)=nY+yShift; 
    }

    return retValue; 
} 

class SCircle
{
public: 
float x; float y; float r; std::array<float,1026>vertices; 
inline void UpdateShape()noexcept
{
vertices=TransformVertices<1026>(__FGE_PRIMITIVE_PRELOAD_CIRCLE_DATA,x,y,r,r);
}

SCircle(float X, float Y, float R):x(X),y(Y),r(R){
UpdateShape();

}
inline SCircle& Draw()noexcept
{
    __FGE_PRIM_RENDER_FILL_SHAPE((float*)vertices.data(),513);
    return *this;
}
inline SCircle& DrawBorder()noexcept
{
    __FGE_PRIM_RENDER_DRAW_SHAPE((float*)vertices.data(),513);
    return *this;
}
inline SCircle& DrawBorder(const FGE_Color& color)noexcept
{
    FGE_SetColor(color);
    return  DrawBorder();
}
inline SCircle& Draw(const FGE_Color& color)noexcept
{
    FGE_SetColor(color);
    return Draw();
}
inline SCircle& SetX(float X)noexcept{x=X;return *this;}
inline SCircle& SetY(float Y)noexcept{y=Y;return *this;}
inline SCircle& SetR(float R)noexcept{r=R;return *this;}
inline SCircle& ShiftX(float dx)noexcept{x+=dx;return *this;}
inline SCircle& ShiftY(float dy)noexcept{y+=dy;return *this;}
inline SCircle& LERP(const FGE_FPoint& p, float lerpRate=0.01){x+=lerpRate*(p.x-x);y+=lerpRate*(p.y-y);return *this;}
inline SCircle& SMOOTHSTEP(const FGE_FPoint& p, float stepRate=0.04){x+=SHAPE_SMOOTHSTEP(stepRate*gcem::tanh(p.x-x))*(p.x-x);y+=SHAPE_SMOOTHSTEP(stepRate*gcem::tanh(p.y-y))*(p.y-y);return *this;}

inline float GetX()const noexcept{return x;}
inline float GetY()const noexcept{return y;}
inline float GetR()const noexcept{return r;}

};
class SEllipse
{
public:
float x; float y; float a; float b; float angle; std::array<float, 1026>vertices; 

inline void UpdateShape()noexcept
{
    vertices= TransformVertices<1026>(__FGE_PRIMITIVE_PRELOAD_CIRCLE_DATA, x,y,a,b,angle);
}
public:

SEllipse(float X, float Y, float A, float B,float ANGLE=0):x(X),y(Y),a(A),b(B),angle(ANGLE){
    UpdateShape();
}
inline SEllipse& Draw()noexcept
{
    __FGE_PRIM_RENDER_FILL_SHAPE((float*)vertices.data(),513);
    return *this;
}
inline SEllipse& Draw(const FGE_Color& color)noexcept
{
    FGE_SetColor(color);
    return Draw();
}
inline SEllipse& DrawBorder()noexcept
{
    __FGE_PRIM_RENDER_DRAW_SHAPE((float*)vertices.data(),513);
    return *this;
}
inline SEllipse& DrawBorder(const FGE_Color& color)noexcept
{
    FGE_SetColor(color); 
    return DrawBorder();
}
inline SEllipse& SetX(float X)noexcept{x=X; return *this;}
inline SEllipse& SetY(float Y)noexcept{y=Y; return *this;}
inline SEllipse& SetA(float A)noexcept{a=A; return *this;}
inline SEllipse& SetB(float B)noexcept{b=B; return *this;}
inline SEllipse& SetAngle(float ANGLE)noexcept{angle=ANGLE; return *this;}
inline SEllipse& ShiftX(float dx)noexcept{x+=dx;return *this;}
inline SEllipse& ShiftY(float dy)noexcept{y+=dy;return *this;}
inline SEllipse& Rotate(float dTheta)noexcept{angle+=dTheta;return *this;}
inline SEllipse& LERP(const FGE_FPoint& p, float lerpRate=0.01){x+=lerpRate*(p.x-x);y+=lerpRate*(p.y-y);return *this;}
inline SEllipse& SMOOTHSTEP(const FGE_FPoint& p, float stepRate=0.04){x+=SHAPE_SMOOTHSTEP(stepRate*gcem::tanh(p.x-x))*(p.x-x);y+=SHAPE_SMOOTHSTEP(stepRate*gcem::tanh(p.y-y))*(p.y-y);return *this;}


inline float GetX()const noexcept{return x;}
inline float GetY()const noexcept{return y;}
inline float GetA()const noexcept{return a;}
inline float GetB()const noexcept{return b;}
inline float GetAngle()const noexcept{return angle;}

};
class SRect
{
public: 
float xm; float ym; float w2; float h2;float angle;  std::array<float, 10>vertices;

inline SRect UpdateShape()noexcept
{
vertices=TransformVertices<10>(__FGE_PRIMITIVE_PRELOAD_SQUARE_DATA,xm,ym,w2,h2,angle);
return *this;
}

SRect(float X_M, float Y_M, float W_HALF, float H_HALF, float ANGLE=0):xm(X_M),ym(Y_M),w2(W_HALF),h2(H_HALF),angle(ANGLE){
UpdateShape();
}
inline SRect& Draw()noexcept
{
    __FGE_PRIM_RENDER_FILL_SHAPE((float*)vertices.data(),5);
    return *this;
}
inline SRect& SetRect(const FGE_FRect& RECT)
{
xm=RECT.x;
ym=RECT.y;
w2=RECT.w;
h2=RECT.h;
return *this;
}
inline SRect& Draw(const FGE_Color& color)noexcept
{
    FGE_SetColor(color);
    return Draw();
}
inline SRect& DrawBorder()noexcept
{
    __FGE_PRIM_RENDER_DRAW_SHAPE((float*)vertices.data(),5);
    return *this;
}
inline SRect& DrawBorder(const FGE_Color& color)noexcept
{
    FGE_SetColor(color);
    return DrawBorder();
}
inline SRect& SetXM(float XM)noexcept{xm=XM; return*this;}
inline SRect& SetYM(float YM)noexcept{ym=YM; return*this;}
inline SRect& SetW2(float W2)noexcept{w2=W2; return*this;}
inline SRect& SetH2(float H2)noexcept{h2=H2; return*this;}
inline SRect& SetAngle(float ANGLE)noexcept{angle=ANGLE; return*this;}
inline FGE_FRect& GetRect()noexcept
{
    return (FGE_FRect&)*this;
}
inline SRect& ShiftX(float dx)noexcept{xm+=dx;return *this;}
inline SRect& ShiftY(float dy)noexcept{ym+=dy;return *this;}
inline SRect& Rotate(float dTheta)noexcept{angle+=dTheta;return *this;}
inline SRect& LERP(const FGE_FPoint& p, float lerpRate=0.01){xm+=lerpRate*(p.x-xm);ym+=lerpRate*(p.y-ym);return *this;}
inline SRect& SMOOTHSTEP(const FGE_FPoint& p, float stepRate=0.04){xm+=SHAPE_SMOOTHSTEP(stepRate*gcem::tanh(p.x-xm))*(p.x-xm);ym+=SHAPE_SMOOTHSTEP(stepRate*gcem::tanh(p.y-ym))*(p.y-ym);return *this;}

inline float GetXM()const noexcept{return xm;}
inline float GetYM()const noexcept{return ym;}
inline float GetW2()const noexcept{return w2;}
inline float GetH2()const noexcept{return h2;}
inline float GetAngle()const noexcept{return angle;}
};
class SSquircle
{
public: 
float x; float y; float a; float b; float angle; std::array<float,1026>vertices; 

inline void UpdateShape()noexcept
{
    vertices= TransformVertices<1026>(__FGE_PRIMITIVE_PRELOAD_SQUIRCLE_DATA, x,y,a,b,angle);
}

SSquircle(float X, float Y, float A, float B,float ANGLE=0):x(X),y(Y),a(A),b(B),angle{ANGLE}{
    UpdateShape();
}
inline SSquircle& Draw()noexcept
{
    __FGE_PRIM_RENDER_FILL_SHAPE((float*)vertices.data(),513);
    return *this;
}
inline SSquircle& Draw(const FGE_Color& color)noexcept
{
    FGE_SetColor(color);
    return Draw();
}
inline SSquircle& DrawBorder()noexcept
{
    __FGE_PRIM_RENDER_DRAW_SHAPE((float*)vertices.data(),513);
    return *this;
}
inline SSquircle& DrawBorder(const FGE_Color& color)noexcept
{
    FGE_SetColor(color);
    return DrawBorder();
}
inline SSquircle& SetX(float X)noexcept{x=X;return *this;}
inline SSquircle& SetY(float Y)noexcept{y=Y;return *this;}
inline SSquircle& SetA(float A)noexcept{a=A;return *this;}
inline SSquircle& SetB(float B)noexcept{b=B;return *this;}
inline SSquircle& SetAngle(float ANGLE)noexcept{angle=ANGLE;return *this;}
inline SSquircle& ShiftX(float dx)noexcept{x+=dx;return *this;}
inline SSquircle& ShiftY(float dy)noexcept{y+=dy;return *this;}
inline SSquircle& Rotate(float dTheta)noexcept{angle+=dTheta;return *this;}
inline SSquircle& LERP(const FGE_FPoint& p, float lerpRate=0.01){x+=lerpRate*(p.x-x);y+=lerpRate*(p.y-y);return *this;}
inline SSquircle& SMOOTHSTEP(const FGE_FPoint& p, float stepRate=0.04){x+=SHAPE_SMOOTHSTEP(stepRate*gcem::tanh(p.x-x))*(p.x-x);y+=SHAPE_SMOOTHSTEP(stepRate*gcem::tanh(p.y-y))*(p.y-y);return *this;}

inline float GetX()const noexcept{return x;}
inline float GetY()const noexcept{return y;}
inline float GetA()const noexcept{return a;}
inline float GetB()const noexcept{return b;}
inline float GetAngle()const noexcept{return angle;}

};
class STriangle
{
public: 
FGE_FPoint a,b,c;
STriangle(const FGE_FPoint& A, const FGE_FPoint& B, const FGE_FPoint& C ):a(A),b(B),c(C){}
inline std::array<float,6> GetVertices()const noexcept
{
    return {a.x,a.y,b.x,b.y,c.x,c.y};
}

inline STriangle& Draw()noexcept
{
    __FGE_PRIM_RENDER_FILL_TRIANGLE((float*)this,3);
    return *this;
}
inline STriangle& DrawBorder()noexcept
{
    __FGE_PRIM_RENDER_DRAW_SHAPE((float*)this,3);
    return *this;
}
inline STriangle& DrawBorder(const FGE_Color& color)noexcept
{
    FGE_SetColor(color);
    return  DrawBorder();
}
inline STriangle& Draw(const FGE_Color& color)noexcept
{
    FGE_SetColor(color);
    return Draw();
}
inline STriangle& SetA(const FGE_FPoint& A)noexcept{a=A;return *this;}
inline STriangle& SetB(const FGE_FPoint& B)noexcept{b=B;return *this;}
inline STriangle& SetC(const FGE_FPoint& C)noexcept{c=C;return *this;}

inline FGE_FPoint GetA()const noexcept{return a;}
inline FGE_FPoint GetB()const noexcept{return b;}
inline FGE_FPoint GetC()const noexcept{return c;}
};






}


#endif