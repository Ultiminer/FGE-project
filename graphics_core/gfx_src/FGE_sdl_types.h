#ifndef FGE_SDL_TYPES_H_
#define FGE_SDL_TYPES_H_
#include <SDL.h>
#include "glad.h"

using FGE_FPoint= SDL_FPoint;
using FGE_Point=SDL_Point;
using FGE_Rect=SDL_Rect;
using FGE_FRect=SDL_FRect;
using FGE_Color= SDL_Color;
using FGEenum= GLenum;
struct FGE_Circle{float x; float y; float r;};
struct FGE_Ellipse{float x; float y; float a; float b;};

struct FGE_Triangle{FGE_FPoint a; FGE_FPoint b; FGE_FPoint c; };
struct FGE_Line{float x1; float y1; float x2; float y2;};
struct FGE_Squircle{float x; float y; float a; float n;};

#endif