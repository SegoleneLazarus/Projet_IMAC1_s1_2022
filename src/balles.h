#include "application_ui.h"
#include "SDL2_gfxPrimitives.h"
#include <iostream>
#include <string>

std::string mainColor;

struct Ellipse;
struct LinkedList;
struct Mur;


void drawEllipses(LinkedList liste, SDL_Renderer* renderer);

void initialiseEllipse(Ellipse* ellipse, Sint16 x, Sint16 y, Sint16 dx, Sint16 dy, Sint16 radius, Uint8 r, Uint8 g, Uint8 b);

void updateEllipse(Mur* tabMur, Ellipse* ellipse);

void updateEllipses(LinkedList list, Mur* tabMur, SDL_Renderer* renderer);

std::string checkCommandLineArgs(int argc, char** argv);

void generateEllipseColor(std::string mainColor);

void ajoutEllipse(LinkedList *liste, int x, int y, std::string mainColor);

bool mouseCoordIsInsideEllipse(Ellipse *ellipse, int mouseX, int mouseY);

bool supprEllipse(LinkedList* list, int mouseX, int mouseY);

void ajoutEllipseXY(LinkedList *liste, int mouseX, int mouseY);

int setNumberOfEllipse(int argc, char **argv);

bool handleEvent(LinkedList **ellipses);