out vec4 FragColor;
uniform vec4 myColor; 
uniform bool drawImage; 

in vec2 TexCoord;

uniform sampler2D ourTexture;

const float conv=0.0039215686274509803921568627451;



void main()
{
if(drawImage){FragColor= texture(ourTexture,TexCoord); return;}
FragColor = vec4(myColor.x*conv,myColor.y*conv,myColor.z*conv,myColor.w*conv);
}
