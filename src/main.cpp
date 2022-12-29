#include "application_ui.h"
#include "SDL2_gfxPrimitives.h"
#include <iostream>
using namespace std;

// j'ai tout mis dans le main pour l'instant

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

// initialisation de Ellipse 
void initialiseEllispe(Ellipse* ellipse, Sint16 x, Sint16 y, Sint16 dx, Sint16 dy, Sint16 radius, Uint8 r, Uint8 g, Uint8 b){
    ellipse->coordX = x;
    ellipse->coordY = y;
    ellipse->vitX = dx;
    ellipse->vitY = dy;
    ellipse->rayon = radius;
    ellipse->compoRouge = r;
    ellipse->compoVert = g;
    ellipse->compoBleu = b;
}

// PERMET DE METTRE A JOUR LA VITESSE DE LA BOULE QUAND ELLE TAPE UN MUR
void updateEllipse(Ellipse* ellipse) {
    ellipse->coordX = ellipse->coordX + ellipse->vitX;
    ellipse->coordY = ellipse->coordY + ellipse->vitY;

    if(ellipse->coordX <= ellipse->rayon || ellipse->coordX >= SCREEN_WIDTH-ellipse->rayon){
        ellipse->vitX = - ellipse->vitX;
    }

    if(ellipse->coordY <= ellipse->rayon || ellipse->coordY >= SCREEN_HEIGHT-ellipse->rayon){
        ellipse->vitY = - ellipse->vitY;
    }
}


// structure de la chaine d'ellipse (A CHANGER POUR LES LISTES CHAINES)
struct ChaineEllipse{
    Ellipse *ellipse;
    ChaineEllipse* suivant; // pointeur vers la prochaine boule qui sera créée
};
// initialisation de ChaineEllipse
void initialiseChaineEllipse(ChaineEllipse* chaine, Ellipse *ellipse, ChaineEllipse* suivant){
    chaine->ellipse = ellipse;
    chaine->suivant = suivant;
}

// structure du Mur
struct Mur{
    int coordX1;
    int coordY1;
    int coordX2;
    int coordY2;
};



// on a mis ChaineEllipse en paramètres car on va en avoir besoin dans le main
void draw(SDL_Renderer* renderer,Ellipse* boule)
{
    /* Remplissez cette fonction pour faire l'affichage du jeu */

    int a = 255;

	filledEllipseRGBA(renderer,boule->coordX,boule->coordY,boule->rayon,boule->rayon,boule->compoRouge,boule->compoVert,boule->compoBleu,a);
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


    // tout ce dont on a besoin pour faire une boule
    // PERMET DE CREER UNE BOULE

    Uint8 r,g,b;
    Sint16 x,y,dx,dy,radius;
    Ellipse boule; 
    Ellipse boule2; 

	x = rand()%SCREEN_WIDTH;
	y = rand()%SCREEN_HEIGHT;
    dx = pow((-1),(rand()%2))*(rand()%5+5); //permet d'avoir une vitesse positive ou négative
    dy = pow((-1),(rand()%2))*(rand()%5+5); //permet d'avoir une vitesse positive ou négative
	radius = 15;
	r = rand()%128+128;
	g = rand()%128+128;
	b = rand()%128+128;

    initialiseEllispe(&boule,x,y,dx,dy,radius,r,g,b);

    // BOULE 2 DE TEST

    x = rand()%SCREEN_WIDTH;
	y = rand()%SCREEN_HEIGHT;
    dx = pow((-1),(rand()%2))*(rand()%5+5); //permet d'avoir une vitesse positive ou négative
    dy = pow((-1),(rand()%2))*(rand()%5+5); //permet d'avoir une vitesse positive ou négative
	radius = 15;
	r = rand()%128+128;
	g = rand()%128+128;
	b = rand()%128+128;

    initialiseEllispe(&boule2,x,y,dx,dy,radius,r,g,b);

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
        
        // DESSIN DE LA BOULE
        draw(renderer, &boule);

        // mettre à jour boule ET SA VITESSE QD ELLE COGNE UN MUR
        updateEllipse(&boule);

        // DESSIN BOULE2
        draw(renderer, &boule2);

        // mettre à jour boule2
        updateEllipse(&boule2);

        // VALIDATION FRAME
        SDL_RenderPresent(renderer);

        // PAUSE en ms
        SDL_Delay(1000/30); 
    }

    //Free resources and close SDL
    close(gWindow, renderer);

    return 0;
}