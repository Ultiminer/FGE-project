out vec4 FragColor;
uniform vec4 myColor; 
uniform int drawImage; 
uniform vec2 colorEdge; 
uniform sampler2D ourTexture;
in vec2 posCoord; 

const float conv=0.0039215686274509803921568627451;



void main()
{
if(drawImage>0){
vec2 TexCoord;
TexCoord.x=(posCoord.x>colorEdge.x)?1:0;
TexCoord.y=(posCoord.y>colorEdge.y)?1:0;

vec4 texColor= texture(ourTexture,TexCoord); 
FragColor= texColor;
return; 
}
FragColor = vec4(myColor.x*conv,myColor.y*conv,myColor.z*conv,myColor.w*conv);
}
