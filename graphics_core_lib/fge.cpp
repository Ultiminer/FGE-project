#include "fge.h"


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

constexpr void __FGE_PRIMITIVE_SetAttributes(int dimensions,int index,int stride  )noexcept
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

inline int __FGE_PRIM_RENDER_UNIFORM_LOCATION(const char* uniform)noexcept
{
    return glGetUniformLocation(__fge_primitive_renderer.shaderProgram,uniform);
} 


inline void FGE_FILL_SHAPE(float* data, size_t Size,GLenum usage)noexcept 
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
inline void FGE_DRAW_SHAPE(float* data, size_t Size,GLenum usage)noexcept 
{
    glBindVertexArray(__fge_primitive_renderer.vertexArray);
    glBindBuffer(GL_ARRAY_BUFFER,__fge_primitive_renderer.vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER,sizeof(float)*2*Size,data,usage);
    
    __FGE_PRIMITIVE_SetAttributes(2);
    glBindVertexArray(__fge_primitive_renderer.vertexArray);
    glUseProgram(__fge_primitive_renderer.shaderProgram);
    glDrawArrays(GL_LINE_STRIP,0,Size);
}
inline void __FGE_PRIM_RENDER_FILL_TRIANGLE(float* data, size_t Size,GLenum usage)noexcept 
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
namespace FGE
{



inline Window::Window(const char* title, int width, int height, Uint32 flags)
{
SDL_Init(SDL_INIT_VIDEO);
SDL_GL_LoadLibrary(NULL);
SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,SDL_GL_CONTEXT_PROFILE_CORE);
SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

sdlWindow=SDL_CreateWindow(title,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, width,height,flags|SDL_WINDOW_OPENGL );
sdlEvent= new SDL_Event();
wWidth=width; wHeight=height;

ctx=SDL_GL_CreateContext(sdlWindow);
gladLoadGLLoader(SDL_GL_GetProcAddress);
SDL_GL_SetSwapInterval(0);
glClearColor(1,0.46,0.8,1);



}
inline Window::Window()
{
SDL_Init(SDL_INIT_VIDEO);
SDL_GL_LoadLibrary(NULL);
SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,SDL_GL_CONTEXT_PROFILE_CORE);
SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

sdlWindow=SDL_CreateWindow(__FGE_WINDOWSIZE_TITLE,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, __FGE_WINDOWSIZE_WIDTH,__FGE_WINDOWSIZE_HEIGHT, SDL_WINDOW_SHOWN|SDL_WINDOW_OPENGL);
sdlEvent= new SDL_Event();
wWidth=__FGE_WINDOWSIZE_WIDTH; wHeight=__FGE_WINDOWSIZE_HEIGHT;

ctx=SDL_GL_CreateContext(sdlWindow);
gladLoadGLLoader(SDL_GL_GetProcAddress);
SDL_GL_SetSwapInterval(0);
glClearColor(1,0.46,0.8,1);


}
inline Window::~Window()
{
    SDL_FreeSurface(iconSurface);
    delete iconSurface;
    SDL_Quit();
    SDL_DestroyWindow(sdlWindow);
    delete sdlEvent;
}
inline Window& Window::SetViewport(float x, float y, float w, float h)
{
glViewport(x,y,w,h);
return *this; 
}
inline Window& Window::PollEvents()
{
    SDL_PollEvent(sdlEvent);
    if(sdlEvent->type==SDL_KEYDOWN&&sdlEvent->key.keysym.sym==SDLK_LSHIFT)UpKey=true;
    if(sdlEvent->type==SDL_KEYUP&&sdlEvent->key.keysym.sym==SDLK_LSHIFT)UpKey=false;

    return *this;
}
constexpr bool Window::GetUpKey()const
{
    return UpKey;
}
inline Window& Window::SetTitle(const char* title)
{
    SDL_SetWindowTitle(sdlWindow, title);
    return *this;
}
inline bool Window::IsRunning()
{
    deltaTime=FGE_CurrentMilliseconds()-currTime;

    #ifndef FGE_NO_VSYNC
    while(1000/(1+deltaTime)>__FGE_FPS_CAP)deltaTime=FGE_CurrentMilliseconds()-currTime;
    #endif

    currTime=FGE_CurrentMilliseconds();

    return sdlEvent->type!=SDL_QUIT;
}
inline size_t Window::GetDeltaTime()const noexcept
{
    return deltaTime; 
}
inline size_t Window::GetFPS()const noexcept
{
    return 1000/(1+deltaTime); 
}
inline bool Window::KeyDown(long long int key)
{
    if(sdlEvent->type!=SDL_KEYDOWN)return false;
    return sdlEvent->key.keysym.sym==key;
}
inline bool Window::KeyUp(long long int key)
{
    if(sdlEvent->type!=SDL_KEYUP)return false;
    return sdlEvent->key.keysym.sym==key;
}
inline int Window::GetWidth()
{
    return wWidth; 
}
inline int Window::GetHeight()
{
    return wHeight; 
}
inline Window& Window::QueryMousePos(FGE_Point& p)
{  
    SDL_GetMouseState(&p.x,&p.y);
    p.x-=wWidth/2;
    p.y=wHeight/2-p.y;
    return* this;   
}
inline Window& Window::SetWidth(int width)
{
    SDL_SetWindowSize(sdlWindow,width,wHeight);
    wWidth=width;
    return *this;
}
inline Window& Window::SetHeight(int height)
{
    SDL_SetWindowSize(sdlWindow,wWidth,height);
    wHeight=height;

    return *this;
}
inline Window& Window::SetSize(int width, int height)
{
    SDL_SetWindowSize(sdlWindow,width,height);
    wWidth=width; wHeight=height; 
    return *this;
}
inline Window& Window::Hint(const char* name, const char* value)
{
    SDL_SetHint(name,value);
    return *this;
}
inline Window& Window::OnTop()
{
    SDL_SetWindowAlwaysOnTop(sdlWindow,(SDL_bool)true);
    return *this;
}
inline Window& Window::NotOnTop()
{
    SDL_SetWindowAlwaysOnTop(sdlWindow,(SDL_bool)false);
    return *this;
}
inline Window& Window::Bordered()
{
    SDL_SetWindowBordered(sdlWindow,(SDL_bool)true);
    return *this;
}
inline Window& Window::UnBordered()
{
    SDL_SetWindowBordered(sdlWindow,(SDL_bool)false);
    return *this;
}
inline Window& Window::SetBrightness(float brightness)
{
    SDL_SetWindowBrightness(sdlWindow, brightness);
    return *this;
}
inline Window& Window::SetDisplayMode(const SDL_DisplayMode& mode)
{
    SDL_SetWindowDisplayMode(sdlWindow,&mode);
    return *this;
}
inline Window& Window::Fullscreen()
{
    SDL_SetWindowFullscreen(sdlWindow,SDL_WINDOW_FULLSCREEN_DESKTOP);
    SDL_GetWindowSize(sdlWindow,&wWidth,&wHeight);

    return *this;
}
inline Window& Window::GrabInput()
{
    SDL_SetWindowGrab(sdlWindow,(SDL_bool)true);
    return *this;
}
inline Window& Window::UnGrabInput()
{
    SDL_SetWindowGrab(sdlWindow,(SDL_bool)false);
    return *this;
}
inline Window& Window::SetIcon(const char* path)
{
    iconSurface=SDL_LoadBMP(path);
    SDL_SetWindowIcon(sdlWindow,iconSurface);
    return *this;
}
inline Window& Window::GrabMouse()
{
    SDL_SetWindowMouseGrab(sdlWindow,(SDL_bool)true);
    return *this;
}
inline Window& Window::UnGrabMouse()
{
    SDL_SetWindowMouseGrab(sdlWindow,(SDL_bool)false);
    return *this;
}
inline Window& Window::SetOpacity(float opacity)
{
    SDL_SetWindowOpacity(sdlWindow,opacity);
    return *this;
}
inline Window& Window::SetResizable(bool resizable)
{
    SDL_SetWindowResizable(sdlWindow, (SDL_bool)resizable);
    return *this;
}
inline Window& Window::Swap()
{
    SDL_GL_SwapWindow(sdlWindow);
    return *this;
}
inline bool Window::LeftClick()
{
return (sdlEvent->type==SDL_MOUSEBUTTONDOWN&&sdlEvent->button.button==SDL_BUTTON_LEFT);
}








}

namespace QM{
    
inline constexpr float EULER_NUM{2.7182818284590452};
inline constexpr float LOG_2_EULER_NUM{1.44269504088896340735};
inline constexpr unsigned int EXP_FLOAT_MASK{0x7f800000};
inline constexpr unsigned int EV_EXPT_EXP_FLOAT_MASK{0x807FFFFF};
inline constexpr float ONE_OVER_LN_2{1.4426950408}; 
inline constexpr float LN_2{0.6931471805599453};
inline constexpr float HALF_LN_2_SQUARED{0.240226506959100};
inline constexpr float POW_TWO_A_1{0.043321698784996581};
inline constexpr float POW_TWO_A_2{9.3838479280898715755293462173177e-4};
inline constexpr float HALF_ROOT_TWO{0.70710678118654};
inline constexpr float QUARTER_PI{0.78539816339744830961566};
inline constexpr size_t PRIMITIVE_FACTORIALS[]={1,1,2,6,24,120,720,5760,51840,518400};
inline constexpr float ONE_OVER_SQRT_2PI{0.398942280401f};

#define GetFloat_Data_Exponent(f) ((*((unsigned int*)&(f)) & EXP_FLOAT_MASK)>>23)
#define AddFloatExponent(f,y) ((((GetFloat_Data_Exponent((f))+(y))<<23)+GetFloat_Data_Mantissa(f)))

//TAKES AS INPUT AN EPSILON BETWEEN -1 and 1 and guesses the corresponding output
constexpr float QUICK_2_TO_EPSILON(float epsilon)
{
  float guess=1+epsilon*(POW_TWO_A_1+POW_TWO_A_2*epsilon); 
  guess*=guess;
  guess*=guess;
  guess*=guess;
  guess*=guess;

  return guess;
}

#define GetFloat_Data_Mantissa(f)((*((unsigned int*)&(f)) & 0x007fffff))
#define GetFloatExponent(f) (((*((unsigned int*)&(f)) & 0x7f800000)>>23)-127)


constexpr float square(float x)
{
    return x*x; 
}
constexpr float sqrt(float x)
{
    //Square root Fixpoint iterations
    #define SQRT_FIX_ITER(guess, eps)(0.5f*((eps)/(guess)+(guess)))
    #define SQRT_2_ITER(guess,eps)(SQRT_FIX_ITER((SQRT_FIX_ITER((SQRT_FIX_ITER((guess),(eps))),(eps))),(eps)))

    constexpr float SQRT_2{1.41421356237};
    constexpr float ONE_OVER_ROOT_TWO{0.707106781186547524};

    //Exponent of float number
    const int e = GetFloatExponent(x);
    
    //Getting float mantissa multiplier
    const unsigned int epsilon=GetFloat_Data_Mantissa(x)+(1<<23)*127; 
    //Half Exponent
    const unsigned int exp_half=(1<<23)*(127+e/2);
   
    if(e%2==0)return (*(float*)&exp_half)*SQRT_2_ITER(0.5f*(1+SQRT_2),*(float*)&epsilon);

    return (*(float*)&exp_half)*((e>=0)?(SQRT_2):(ONE_OVER_ROOT_TWO))*SQRT_2_ITER(0.5f*(1+SQRT_2),*(float*)&epsilon);
}
constexpr float log2(float x)
{
    //Exponent of float number
    const int e = GetFloatExponent(x);
    const unsigned int m_i=GetFloat_Data_Mantissa(x)+(1<<23)*127; 
    const float m=*(float*)&m_i;
    float guess=m-0.97;
    //First Newton iteration
    guess+=ONE_OVER_LN_2*(m*QUICK_2_TO_EPSILON(-guess)-1); 
    //Second Newton iteration
    guess+=ONE_OVER_LN_2*(m*QUICK_2_TO_EPSILON(-guess)-1); 
    //Third Newton iteration
    guess+=ONE_OVER_LN_2*(m*QUICK_2_TO_EPSILON(-guess)-1); 

    return e+guess;
}
constexpr float floor(float x)
{
    if(x>=0)return (int)x; 
    return (int)x-1; 
}
constexpr float pow2(float y)
{
    const unsigned int exp_2=(1<<23)*(127+QM::floor(y));
    return (*(float*)&exp_2)*QUICK_2_TO_EPSILON(y-QM::floor(y)); 
}
constexpr float pow(float x, float y)
{
    return QM::pow2(y*QM::log2(x));
}
constexpr float mod(float x, float m)
{
    if(x<0)return -mod(-x,m);
    return (x-m<0)?x:mod(x-m,m);
}
constexpr float QUICK_SIN_FIRST_QUARTER(float x)
{   
   if(x<0.947)return x-(x*x*x)/6;
   return 1-0.5f*(x-QUARTER_PI*2)*(x-QUARTER_PI*2); 
}
constexpr float sin(float x)
{
    x=mod(x,QUARTER_PI*8);
    if(x<0)x+=QUARTER_PI*8; 
    if(x<=QUARTER_PI*2)
    return QUICK_SIN_FIRST_QUARTER(x);
    if(x<=QUARTER_PI*4)
    return QUICK_SIN_FIRST_QUARTER(4*QUARTER_PI-x);
    if(x<=QUARTER_PI*6)
    return -QUICK_SIN_FIRST_QUARTER(x-QUARTER_PI*4);
    if(x<=QUARTER_PI*8)
    return -QUICK_SIN_FIRST_QUARTER(8*QUARTER_PI-x);

    return 1; 
}
constexpr float cos(float x)
{
    return QM::sin(x+QUARTER_PI*2);
}
constexpr float tan(float x)
{
    return QM::sin(x)/QM::sin(x+QUARTER_PI*2); 
}
constexpr float abs(float x)
{
    if(x>0)return x;
    return -x;
}
constexpr float factorial(size_t n)
{
    if(n<=10)return PRIMITIVE_FACTORIALS[n]; 
    //Stirlings approximation 
    return 2.506628274631000*QM::sqrt(n)*QM::pow(0.36787944117144*n,n);
}
constexpr float binomial_coeff(size_t n, size_t k)
{
 return QM::factorial(n)/(QM::factorial(k)*QM::factorial(n-k));
}
constexpr float ln(float x)
{
    return QM::log2(x)/LOG_2_EULER_NUM; 
}
constexpr float exp(float x)
{
    return QM::pow2(x*LOG_2_EULER_NUM); 
}
constexpr float dist(float x)
{
    return abs(x);
}
constexpr float dist(float x, float y)
{
    return abs(x-y);
}
constexpr float sinh(float x)
{
    return 0.5f*(QM::exp(x)-QM::exp(-x));
}
constexpr float cosh(float x)
{
    return 0.5f*(QM::exp(x)+QM::exp(-x));
}
constexpr float tanh(float x)
{
    const float exp_2_x_{QM::exp(x+x)};
    return 0.5f*((exp_2_x_+1)/(exp_2_x_-1));
}
constexpr float coth(float x)
{
    const float exp_2_x_{QM::exp(x+x)};
    return 0.5f*((exp_2_x_-1)/(exp_2_x_+1));
}
constexpr float atan(float x)
{
    if(x>1)return x/(1+0.28*x*x);
    if(x<-1)return QUARTER_PI*2-x/(x*x+0.28);

    return -QUARTER_PI*2-x/(x*x+0.28);
}
constexpr float asin(float x)
{
    return atan(x/(QM::sqrt(1-x*x))); 
}
constexpr float acos(float x)
{
    return QUARTER_PI*2-atan(x/(QM::sqrt(1-x*x))); 
}
constexpr float max(float x, float y)
{
    if(x>y)return x;
    return y; 
}
constexpr float min(float x, float y)
{
    if(x<y)return x;
    return y; 
}
constexpr size_t max(size_t x, size_t y)
{
    if(x>y)return x;
    return y; 
}
constexpr size_t min(size_t x, size_t y)
{
    if(x<y)return x;
    return y; 
}
constexpr size_t gcd(const size_t m, const size_t n)
{     
    size_t reduction=1; 
    while(true)
    {
        if(m%2+n%2==0)reduction*=2;
        else if(m%3+n%3==0)reduction*=3; 
        else break; 
    }
    const size_t Kmin=QM::min(m,n)/reduction;
    for(size_t g=Kmin; g>1; --g)
    {
        if(m%g+n%g==0)return g*reduction;
    }

    return 1*reduction; 
}
/*Gives the angle of a rise over run situation*/
constexpr float arg(float y, float x)
{
    if(x>0)return QM::atan(y/x);
    if(x<0)
    {
        if(y<0)return atan(y/x)-QUARTER_PI*4;
        return atan(y/x)+QUARTER_PI*4; 
    }
    if(y>0)
    return QUARTER_PI*2;

    return -QUARTER_PI*2;
}
#define SignBit(x) (((*(unsigned int*)&(x)))>>31)

constexpr int sign(float x)
{
    return 1-2*SignBit(x); 
}
constexpr int sign(int x)
{
    return 1-2*SignBit(x); 
}
constexpr int heaviside(float x)
{
    return SignBit(x); 
}
constexpr int step(float x)
{
    return SignBit(x); 
}
constexpr float cron_delta(float x)
{
    if(x==0)return ((float)(1e+300*1e+300));
    return  0;
}
constexpr float normal_distribution(float x, const float mean, const float std_dev)
{
    return ONE_OVER_SQRT_2PI*(1/std_dev)*QM::exp(-0.5f*square((x-mean)/std_dev));
}
constexpr float gaussian(float x)
{
    return ONE_OVER_SQRT_2PI*QM::exp(-0.5f*x*x);
}
constexpr float gd(float x)
{
    return 2*QM::atan(QM::tanh(0.5f*x));
}
constexpr float sinc(float x)
{
    if(x==0)return 1;
    return QM::sin(x)/x; 
}
constexpr float length(float x, float y)
{
    return QM::sqrt(x*x+y*y);
}
constexpr float length(float x, float y, float z)
{
    return QM::sqrt(x*x+y*y+z*z);
}

/*Triangle math*/
constexpr float triangle_height_on_a(float a, float b, float c)
{
    return 0.5f*(1/a)*QM::sqrt((a+b+c)*(a+b-c)*(a-b+c)*(-a+b+c));
}
constexpr float triangle_area(float a, float b, float c)
{
    return 0.5f*a*QM::triangle_height_on_a(a,b,c);
}
}

constexpr FGE_Color operator|(const FGE_Color& a, const FGE_Color& b)
{
	const int R=(a.r+b.r);
	const int G=(a.g+b.g);
	const int B=(a.b+b.b);
	return {(Uint8)(R>>1),(Uint8)(G>>1),(Uint8)(B>>1),255}; 
}
/*Computes the complementary color*/
constexpr FGE_Color operator~(const FGE_Color& a)
{
	const int R=(255-a.r);
	const int G=(255-a.g);
	const int B=(255-a.b);
	return {(Uint8)R,(Uint8)G,(Uint8)B,255}; 
}
namespace FGE{

	template<size_t S>
	constexpr std::array<FGE_Color, S> ColorInterpolationSet(const FGE_Color& a, const FGE_Color& b)
	{
		std::array<FGE_Color, S>retVal; 
		const FGE_Color diff{a.r-b.r, a.g-b.g,a.b-b.b, a.a-b.a};
		constexpr size_t SM{S-1};
		for(size_t i=0; i<S;++i)
		{
		const float t{(i/SM)};
		retVal.at(i)={a.r+diff.r*t,a.g+diff.g*t,a.b+diff.b*t,a.a+diff.a*t}; 
		}
		return retVal;
	}
	/*moves each RGB value closer to zero by a percentage of its distance, alpha MUST BE between zero and one*/
	constexpr FGE_Color darken(const FGE_Color& a, float alpha)
	{
	const float complAlpha{1-alpha};
	return {(Uint8)(a.r*complAlpha),(Uint8)(a.g*complAlpha),(Uint8)(a.b*complAlpha),a.a};
	}
	/*moves each RGB value closer to 255 by a percentage of its distance, alpha MUST BE between zero and one*/
	constexpr FGE_Color lighten(const FGE_Color& a, float alpha)
	{
	const float rDist{255.f-a.r};
	const float gDist{255.f-a.g};
	const float bDist{255.f-a.b};

	return {(Uint8)(a.r+rDist*alpha),(Uint8)(a.g+gDist*alpha),(Uint8)(a.b+bDist*alpha),a.a};
	}


	/*BASIC COLOR CODES: https://www.rapidtables.com/web/color/RGB_Color.html, last visited: 13.10.2023*/
}
inline size_t FGE_CurrentMilliseconds()noexcept{
return std::chrono::duration_cast< std::chrono::milliseconds >(
    std::chrono::system_clock::now().time_since_epoch()
).count();
}


FGE_Texture::FGE_Texture(){}
FGE_Texture::FGE_Texture(const char* path)
{

glGenTextures(1, &id);
glBindTexture(GL_TEXTURE_2D, id);
// set the texture wrapping/filtering options (on the currently bound texture object)
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

stbi_set_flip_vertically_on_load(true);  
unsigned char *data= stbi_load(path, &width, &height, &channelNum, 0);
if (!data) FGE_EXIT("Image path was nonexistent-> exit!");


const GLint format= (channelNum==4)?GL_RGBA:GL_RGB;
glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
glGenerateMipmap(GL_TEXTURE_2D);
stbi_image_free(data);

}
inline void FGE_Texture::bind()
{
glActiveTexture(GL_TEXTURE0);
glBindTexture(GL_TEXTURE_2D,id);
}
FGE_Texture::~FGE_Texture()
{
    glDeleteTextures(1,&id);    
}


constexpr std::array<float,16> __MakeImageVerticies(const FGE_FRect& rect,float widthPercentage,float heightPercentage, float xOffset,float yOffset)
{
    return {rect.x,rect.y+rect.h,xOffset,yOffset+heightPercentage,rect.x+rect.w,rect.y+rect.h,xOffset+widthPercentage,yOffset+heightPercentage,rect.x+rect.w,rect.y,xOffset+widthPercentage,yOffset,rect.x,rect.y,xOffset,yOffset};
}

inline void FGE_DrawImage(const FGE_FRect& rect, FGE_Texture& texture,float widthPercentage,float heightPercentage, float xOffset,float yOffset)
{

    __fge_primitive_uniform_sys.seti("ourTexture",0).seti("drawImage",1);
    const size_t indicesSize{6};
    const auto verticies=__MakeImageVerticies(rect,widthPercentage,heightPercentage,xOffset,yOffset);

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
inline void FGE_DrawImage(float x, float y, float w , float h, FGE_Texture& texture,float widthPercentage,float heightPercentage, float xOffset,float yOffset)
{
const FGE_FRect dummy{x,y,w,h};
FGE_DrawImage(dummy,texture,widthPercentage,heightPercentage,xOffset,yOffset);
};


inline FGE::Window FGE_General_Init()noexcept
{
    FGE::Window wind=FGE::Window();
     //Initializing FGE functionality
    FGE_INIT_RENDER_DEFAULT();
    FGE_RENDER_SMOOTH();
    FGE_SetClearColor(FGE::lightpink|FGE::black);
    FGE_UseAbsoluteCoords(wind.GetWidth(),wind.GetHeight());


    return wind;
}
