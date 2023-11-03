layout (location = 0) in vec2 aPos;

uniform bool drawImage; 
uniform float myAngle; 
uniform vec4 myShape;
uniform vec2 myCamera; 
uniform vec2 windSize; 
uniform int coordMode; 
out vec2 TexCoord; 



void main()
{
if(drawImage)TexCoord=ivec2((aPos.x>0), (aPos.y>0));



float cosVal=cos(myAngle);
float sinVal=sin(myAngle);
vec4 myTrafo={cosVal,sinVal,-sinVal,cosVal};
vec2 tPos=vec2(aPos.x*myShape.z+myShape.x,aPos.y*myShape.w+myShape.y);
tPos= vec2(myShape.x+(tPos.x-myShape.x)*myTrafo.x+(tPos.y-myShape.y)*myTrafo.y,myShape.y+(tPos.x-myShape.x)*myTrafo.z+(tPos.y-myShape.y)*myTrafo.w);
/*DEFAULT CASE*/
if(coordMode==0){gl_Position = vec4(tPos.x-myCamera.x,tPos.y-myCamera.y, 1.0, 1.0); return;}
/*ABSOLUTE COORDINATES*/
if(coordMode==1){gl_Position = vec4(2*(tPos.x-myCamera.x)/windSize.x,2*(tPos.y-myCamera.y)/windSize.y, 1.0, 1.0);  return; }

}