#include "murs.h"

const int nbMur = 5;

// structure du Mur
struct Mur{
    int x1;
    int y1;
    int x2;
    int y2;
};

void initialiseMur(Mur* mur, int x1,int x2,int y1,int y2){
    // se prémunir contre l'utilsateur con
    if (x2 > x1) {
        mur->x1 = x1;
        mur->x2 = x2;
    } else {
        mur->x1 = x2;
        mur->x2 = x1;
    }

    if (y2 > y1) {
        mur->y1 = y1;
        mur->y2 = y2;
    } else {
        mur->y1 = y2;
        mur->y2 = y1;
    }
}

// faire un tableau de MUR et on le parcourt avec la vitesse


void drawMur(SDL_Renderer* renderer, Mur* mur)
{
    int r = rand()%128+128;
    int g = rand()%128+128;
    int b = rand()%128+128;
    int a = 255;
	lineRGBA(renderer,mur->x1,mur->y1,mur->x2,mur->y2,r,g,b,a);
}
