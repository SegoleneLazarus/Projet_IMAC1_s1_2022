#include "application_ui.h"
#include "SDL2_gfxPrimitives.h"
#include "balles.h"
#include "murs.h"
#include <iostream>
#include <string>

using namespace std;

// const int nbBoule = 10;

const int nbMur = 5;

// const char *image_path = "among-us.bmp";
// int compoRouge, compoVert, compoBleu;

// Ellipse *createEllipseElement(Ellipse *ellip){
//     Ellipse *newElement;
//     newElement = new Ellipse;
//     newElement->next= nullptr;
//     newElement=ellip;
//     //return newElement;
// }



// void displaytest(LinkedList liste){
//     Ellipse *cellstock = liste.head;
//     while (cellstock!=nullptr ){
//         printf("le test marche");
//         cellstock=cellstock->next;
//     }
// }

int main(int argc, char** argv) {
    SDL_Window* gWindow;
    SDL_Renderer* renderer;
    bool is_running = true; 
    SDL_bool quit = SDL_FALSE;

    // Creation de la fenetre
    gWindow = init("Clic to win !");


    if (!gWindow)
    {
        SDL_Log("Failed to initialize!\n");
        exit(1);
    }

    renderer = SDL_CreateRenderer(gWindow, -1, 0); // SDL_RENDERER_PRESENTVSYNC
    SDL_Surface* image = SDL_LoadBMP(image_path);

    if (!image) {// si l'image ne marche pas
        printf("Failed to load image at %s: %s\n", image_path, SDL_GetError());
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    
    

    checkCommandLineArgs(argc, argv);

    //mur
    Mur tabMur[nbMur];

    LinkedList ellipses;
    LinkedList *pt_liste = &ellipses;
    // pt_liste=NULL;
    SDL_Rect test = {320, 240, 100, 50};
    SDL_RenderCopy(renderer, texture, NULL, &test);
    SDL_RenderPresent(renderer);


    for (int j=0 ; j< setNumberOfEllipse(argc, argv) ; j++){
        ajoutEllipse(&ellipses, rand()%SCREEN_WIDTH, rand()%SCREEN_HEIGHT, mainColor);
    }

    // contour
    initialiseMur(&tabMur[0],0,SCREEN_WIDTH,0,0); 
    initialiseMur(&tabMur[1],SCREEN_WIDTH-1,SCREEN_WIDTH-1,0,SCREEN_HEIGHT); 
    initialiseMur(&tabMur[2],SCREEN_WIDTH,0,SCREEN_HEIGHT-1,SCREEN_HEIGHT-1); 
    initialiseMur(&tabMur[3],0,0,SCREEN_HEIGHT,0);

    // mur au pif à l'intérieur
    initialiseMur(&tabMur[4],0,SCREEN_WIDTH/2,SCREEN_HEIGHT/2,SCREEN_HEIGHT/2);

    Uint8 r,g,b;
    Sint16 x,y,dx,dy,radius;
    

    /*  GAME LOOP  */
    while(true)
    {
        // INPUTS
        is_running = handleEvent(&pt_liste);
        if (!is_running)
            break;

        // GESTION ACTEURS

        // ...
        
        // EFFACAGE FRAME
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // afficher mur 
        for(int i=0;i<nbMur;i++){
            drawMur(renderer,&tabMur[i]);
        }

        // supprEllipse(&boule);
        // supprEllipse(&boule2);

        drawEllipses(ellipses, renderer);
        //displaytest(ellipses);
        //on dessine la liste d'ellipses
        updateEllipses(ellipses, tabMur, renderer);
        //on fait bouger les ellipses

        // VALIDATION FRAME
        SDL_RenderPresent(renderer);

        // PAUSE en ms
        SDL_Delay(1000/30); 

        SDL_DestroyTexture(texture);
        // SDL_DestroyRenderer(renderer);
        // SDL_DestroyWindow(window);
        // SDL_Quit();

    }

    //Free resources and close SDL
    
    close(gWindow, renderer);
    return 0;
}