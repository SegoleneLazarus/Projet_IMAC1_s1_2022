#include "application_ui.h"
#include "SDL2_gfxPrimitives.h"
#include <iostream>
#include <string>

struct Mur;

void initialiseMur(Mur* mur, int x1,int x2,int y1,int y2);

void drawMur(SDL_Renderer* renderer, Mur* mur);