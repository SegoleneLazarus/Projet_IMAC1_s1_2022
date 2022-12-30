#include "application_ui.h"
#include "SDL2_gfxPrimitives.h"
#include <iostream>
using namespace std;

// j'ai tout mis dans le main pour l'instant

const int nbBoule = 10;
const int nbMur = 5;

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

// structure du Mur
struct Mur{
    int x1;
    int y1;
    int x2;
    int y2;
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
void updateEllipse(Mur* tabMur, Ellipse* ellipse) {

    for(int i=0;i<nbMur;i++){
        if(tabMur[i].x1 == tabMur[i].x2){ // mur vertical
            // vérification si boule au niveau du mur
            if((ellipse->coordY >= tabMur[i].y1 && ellipse->coordY <= tabMur[i].y2) && (ellipse->coordY+ellipse->vitY >= tabMur[i].y1 && ellipse->coordY + ellipse->vitY <= tabMur[i].y2)){ 
                // vérification si boule traverse mur
                if((ellipse->coordX <= tabMur[i].x1 && ellipse->coordX + ellipse->vitX >= tabMur[i].x1) || (ellipse->coordX >= tabMur[i].x1 && ellipse->coordX + ellipse->vitX <= tabMur[i].x1)) {
                    ellipse->vitX = -ellipse->vitX;
                }
        }
        } else { //mur horizontal
            // vérification si boule au niveau du mur
            if((ellipse->coordX >= tabMur[i].x1 && ellipse->coordX <= tabMur[i].x2) && (ellipse->coordX + ellipse->vitX >= tabMur[i].x1 && ellipse->coordX + ellipse->vitX <= tabMur[i].x2)){ 
                // vérification si boule traverse mur
                if((ellipse->coordY <= tabMur[i].y1 && ellipse->coordY + ellipse->vitY >= tabMur[i].y1) || (ellipse->coordY >= tabMur[i].y1 && ellipse->coordY + ellipse->vitY <= tabMur[i].y1)) {
                    ellipse->vitY = -ellipse->vitY;
                }
            }
        }
    }

    ellipse->coordX = ellipse->coordX + ellipse->vitX;
    ellipse->coordY = ellipse->coordY + ellipse->vitY;
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

// on a mis ChaineEllipse en paramètres car on va en avoir besoin dans le main
void drawEllipse(SDL_Renderer* renderer,Ellipse* boule)
{
    /* Remplissez cette fonction pour faire l'affichage du jeu */

    int a = 255;

	filledEllipseRGBA(renderer,boule->coordX,boule->coordY,boule->rayon,boule->rayon,boule->compoRouge,boule->compoVert,boule->compoBleu,a);
}

void drawMur(SDL_Renderer* renderer,Mur* mur)
{
   
    int r = 255;
    int g = 255;
    int b = 255;
    int a = 255;

	lineRGBA(renderer,mur->x1,mur->y1,mur->x2,mur->y2,r,g,b,a);
}

//voir struct SDL_GetMouseState dans SDL_mouse.h
//on regarde si les x et y de la souris correspondent à une boule
//on veut que la distance entre le souris et le centre de la balle soit inférieure au rayon de la boule
//lors du clic, la boule disparait

void supprEllipse(Ellipse* ellipse){
    int score=0;
    int xMouse, yMouse;
    if(SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(1)){ // lors d'un clic
        // printf("Mouse Button 1(left) is pressed.\n");
        SDL_GetMouseState(&xMouse,&yMouse);
        if ((abs(xMouse-ellipse->coordX)<= ellipse->rayon) && (abs(yMouse-ellipse->coordY)<= ellipse->rayon)){
            ellipse->coordX = 1000;
            ellipse->coordY = 1000;
            //on suppr pas vraiment la boule, on la met juste à un endroit ou elle est pas affichée sur l'écran
            score = score+1;
            // char affichage = 'score : '+ score;
            // SDLTest_DrawString(renderer, 10, 50, &texte);
        }
        else {
            // initialiseEllispe(&boule3,x,y,dx,dy,radius,r,g,b);
            //a rajouter : si l'utilisateur rate, une nouvelle boule se crée
        }
    }
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

    //mur
    Mur tabMur[nbMur];

    // contour
    initialiseMur(&tabMur[0],0,SCREEN_WIDTH,0,0); 
    initialiseMur(&tabMur[1],SCREEN_WIDTH-1,SCREEN_WIDTH-1,0,SCREEN_HEIGHT); 
    initialiseMur(&tabMur[2],SCREEN_WIDTH,0,SCREEN_HEIGHT-1,SCREEN_HEIGHT-1); 
    initialiseMur(&tabMur[3],0,0,SCREEN_HEIGHT,0);

    // mur au pif à l'intérieur
    initialiseMur(&tabMur[4],0,SCREEN_WIDTH/2,SCREEN_HEIGHT/2,SCREEN_HEIGHT/2);

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

        //lineRGBA(renderer,SCREEN_WIDTH/2,0,SCREEN_WIDTH/2,SCREEN_HEIGHT/2,255,255,255,255);
        //lineRGBA(renderer,0,SCREEN_HEIGHT/2,SCREEN_WIDTH/2,SCREEN_HEIGHT/2,255,255,255,255);
        //drawMur(renderer,&tabMur[4]);
        
        // DESSIN DE LA BOULE
        drawEllipse(renderer, &boule);

        // mettre à jour boule ET SA VITESSE QD ELLE COGNE UN MUR
        updateEllipse(tabMur, &boule);

        // DESSIN BOULE2
        drawEllipse(renderer, &boule2);

        // mettre à jour boule2
        updateEllipse(tabMur, &boule2);

        // afficher mur 
        for(int i=0;i<nbMur;i++){
            drawMur(renderer,&tabMur[i]);
        }

        // supprimer les ellipses

        supprEllipse(&boule);
        supprEllipse(&boule2);

        // VALIDATION FRAME
        SDL_RenderPresent(renderer);

        // PAUSE en ms
        SDL_Delay(1000/30); 
    }

    //Free resources and close SDL
    close(gWindow, renderer);

    return 0;
}