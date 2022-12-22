#include "application_ui.h"
#include "SDL2_gfxPrimitives.h"

// j'ai tout mis dans le main pour l'instant parce que quand je mets dans un autre fichier j'ai plein d'erreurs et j'ai la flemme de tout régler mtn mais faudra mettre les struct autre part

salut AD c sego en gros

// structure de l'ellipse 
struct Ellipse{
    int coordX;
    int coordY;
    int vitX;
    int vitY;
    int rayon;
    unsigned int compoRouge;
    unsigned int compoVert;
    unsigned int compoBleu;
};

// structure de la chaine d'ellipse
struct ChaineEllipse{
    Ellipse *ellipse;
    int *nod; // je n'ai pas vu les noeuds donc j'ai aucune idée de comment ils fonctionnent
};

// structure du Mur
struct Mur{
    int coordX1;
    int coordY1;
    int coordX2;
    int coordY2;
};

// pas finie je pense mais au moins y'a la base de la fonction (jsp si elle est utile mais je crois que si)
void initialiseEllispe(Ellipse* ellipse){
    ellipse->coordX = 0;
    ellipse->coordY = 0;
    ellipse->vitX = 0;
    ellipse->vitY = 0;
    ellipse->rayon = 0;
    ellipse->compoRouge = 0;
    ellipse->compoVert = 0;
    ellipse->compoBleu = 0;
}

void draw(SDL_Renderer* renderer)
{
    /* Remplissez cette fonction pour faire l'affichage du jeu */
    
    // int filledEllipseRGBA (SDL_Surface *dst, Sint16 x, Sint16 y, Sint16 rx, Sint16 ry, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    filledEllipseRGBA(
        renderer, ... ?
    ); 
    
   
}

bool handleEvent()
{
    /* Remplissez cette fonction pour gérer les inputs utilisateurs */
    SDL_Event e; 
    while (SDL_PollEvent(&e)){ 
        if (e.type == SDL_QUIT) 
            return false; 
    }
    return true;
}


int main(int argc, char** argv) {
    SDL_Window* gWindow;
    SDL_Renderer* renderer;
    bool is_running = true; 

    // Creation de la fenetre
    gWindow = init("Awesome Game");

    if (!gWindow)
    {
        SDL_Log("Failed to initialize!\n");
        exit(1);
    }

    renderer = SDL_CreateRenderer(gWindow, -1, 0); // SDL_RENDERER_PRESENTVSYNC

    /*  GAME LOOP  */
    while(true)
    {
        // INPUTS
        is_running = handleEvent();
        if (!is_running)
            break;

        // GESTION ACTEURS

        // ...
        
        
        // EFFACAGE FRAME
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        
        // DESSIN
        draw(renderer);

        // VALIDATION FRAME
        SDL_RenderPresent(renderer);

        // PAUSE en ms
        SDL_Delay(1000/30); 
    }

    //Free resources and close SDL
    close(gWindow, renderer);

    return 0;
}
