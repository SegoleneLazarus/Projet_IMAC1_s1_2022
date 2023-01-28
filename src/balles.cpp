#include "balles.h"
#include "murs.h"
#include <iostream>
#include <string>


const int nbMur = 5;

struct Mur{
    int x1;
    int y1;
    int x2;
    int y2;
};

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
    Ellipse* next = nullptr;
};

// structure liste chainée
struct LinkedList {
  Ellipse* head = nullptr;
};

std::string checkCommandLineArgs(int argc, char** argv){
    if(argc > 2){ // s'il y a plus d'un argument
        std::string argcolor = argv[2];
        if(argcolor == "green"){
            mainColor = "G";
        }
        else if(argcolor == "red"){
            mainColor = "R";
        }
        else if(argcolor == "blue"){
            mainColor = "B";
        }
    } else {
        mainColor = "random";
    }
    return mainColor ;
}




void drawEllipses(LinkedList liste, SDL_Renderer* renderer){
    Ellipse* current = liste.head;
    while(current!=nullptr){ //on parcoure la liste chaînée
        filledEllipseRGBA(renderer, current->coordX, current->coordY,current->rayon, current->rayon, current->compoRouge,current->compoVert, current->compoBleu, 255);
        current=current->next;
    }
}

void initialiseEllipse(Ellipse* ellipse, Sint16 x, Sint16 y, Sint16 dx, Sint16 dy, Sint16 radius, Uint8 r, Uint8 g, Uint8 b){
    ellipse->coordX = x;
    ellipse->coordY = y;
    ellipse->vitX = dx;
    ellipse->vitY = dy;
    ellipse->rayon = radius;
    ellipse->compoRouge = r;
    ellipse->compoVert = g;
    ellipse->compoBleu = b;
    // ellipse->next=nullptr;
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

void updateEllipses(LinkedList list, Mur* tabMur, SDL_Renderer* renderer){
    Ellipse *current = list.head;
    while (current != nullptr) { //on parcoure la liste chaînée
        updateEllipse(tabMur, current);
        current=current->next;
    }
}


void generateEllipseColor(std::string mainColor){
    int Rouge, Vert, Bleu;
    if (mainColor == "random"){
        Rouge = rand()%128+128;
        Vert =  rand()%128+128;
        Bleu = rand()%128+128;
        printf("random");
        // return Rouge, Vert, Bleu;
    } else if (mainColor == "R"){
        Rouge = 255;
        Vert = rand()%70;
        Bleu = rand()%70;
    } else if (mainColor == "G"){
        Rouge = rand()%70;
        Vert = 255;
        Bleu = rand()%70;
    }  else if (mainColor == "B"){
        Rouge = rand()%100+1;
        Vert = rand()%100+1;
        Bleu = 255;
    }
    // return 0;
}


void ajoutEllipse(LinkedList *liste, int x, int y, std::string mainColor) {
    int Rouge, Vert, Bleu;

    Ellipse *ellip = new Ellipse;
    ellip->coordX = x;
    ellip->coordY = y;
    ellip->vitX = pow((-1),(rand()%2))*(rand()%5+5); //permet d'avoir une vitesse positive ou négative
    ellip->vitY = pow((-1),(rand()%2))*(rand()%5+5); //permet d'avoir une vitesse positive ou négative
    ellip->rayon = 25;

    // generateEllipseColor(mainColor);
    // ellip->compoRouge = Rouge;
    // ellip->compoVert = Vert;
    // ellip->compoBleu = Bleu;

    if (mainColor == "random"){
        ellip->compoRouge = rand()%128+128;
        ellip->compoVert = rand()%128+128;
        ellip->compoBleu = rand()%128+128;
    } else if (mainColor == "R"){
        ellip->compoRouge = rand()%85 + 170;
        ellip->compoVert = rand()%128;
        ellip->compoBleu = rand()%128;
    } else if (mainColor == "G"){
        ellip->compoRouge = rand()%128;
        ellip->compoVert = rand()%85 + 170;
        ellip->compoBleu = rand()%128;

    } else if (mainColor == "B"){
        ellip->compoRouge = rand()%128;
        ellip->compoVert = rand()%128;
        ellip->compoBleu = rand()%85 + 170;
    }

    ellip->next = liste->head; //le pointeur vers l'ellipse suivante devient le pointeur vers la tete de la liste
    liste->head = ellip; // notre ellipse est placée à la tete de la liste
    //printf("une ellipse est créée");
}

bool mouseCoordIsInsideEllipse(Ellipse *ellipse, int mouseX, int mouseY){
    // int mouseX, mouseY;
    // SDL_GetMouseState(&mouseX,&mouseY);
    int dx = ellipse->coordX - mouseX;
    int dy = ellipse->coordY - mouseY;
    return dx * dx + dy * dy <= ellipse->rayon * ellipse->rayon;
    //formule : (x - center_x)^2 / a^2 + (y - center_y)^2 / b^2 <= 1 (où a est le rayon horizontal et b est le rayon vertical de l'ellipse)
    //Dans cette fonction, on calcule la distance entre le point cliqué (x, y) et le centre de l'ellipse (ellipse->coordX, ellipse->coordY) en utilisant la formule dx = ellipse->coordX - x, dy = ellipse->coordY - y.
    //Ensuite, on calcule dx * dx + dy * dy et on le compare avec le rayon de l'ellipse au carré (ellipse->rayon * ellipse->rayon). Si cette valeur est inférieure ou égale, cela signifie que le point cliqué est à l'intérieur de l'ellipse, donc la fonction renvoie vrai. Sinon, elle renvoie faux.
}

bool supprEllipse(LinkedList* list, int mouseX, int mouseY){
    Ellipse* current = list->head; //on se place au début de la liste
    Ellipse* previous = nullptr;
    while(current!=nullptr){

        if(mouseCoordIsInsideEllipse(current, mouseX, mouseY)){
            printf("c'est réel");
            if(previous==nullptr){
                // cas du premier élément de la liste (ou current == list->head)
                list->head=current->next;
                delete current;
                // on replace le pointeur courant sur la nouvelle tête de liste
                current = list->head;
            } else {
                previous->next=current->next;
                delete current;
                // on replace le pointeur courant sur le nouveau noeud suivant
                current = previous->next;
            }
            return true;
        } else {
            // on passe au noeud suivant
            previous = current;
            current = current->next;
        }
    }
    return false;
}

void ajoutEllipseXY(LinkedList *liste, int mouseX, int mouseY) {
    Ellipse *current = liste->head;
    while(current!=nullptr){
        if (mouseCoordIsInsideEllipse(current, mouseX, mouseY)){ // si l'utilisateur clique sur une balle
            //return;
            break;
        }
        current = current->next;
    }
    printf("balle ratée");
    ajoutEllipse(liste, mouseX, mouseY, mainColor); // on créée une nouvelle ellipse aux coordonnées du clic
}

int setNumberOfEllipse(int argc, char **argv) {
    int numberOfEllipses;
    int firstArg;

    if(argc == 1){
        numberOfEllipses = 5; // par défaut, le nombre d'Ellipses sera égal à 5
    }
    else if(argc > 1){ // s'il y a un argument ou plus
        numberOfEllipses=atoi(argv[1]); // atoi permet de passer la chaine de carac en entier
    }
    return numberOfEllipses;
}

bool handleEvent(LinkedList **ellipses)
{
    /* Remplissez cette fonction pour gérer les inputs utilisateurs */
    SDL_Event e; 
    while (SDL_PollEvent(&e)){ 
        
        if (e.type == SDL_QUIT) 
            return false; 

        else if(e.type == SDL_MOUSEBUTTONDOWN){
            int mouseX, mouseY;

            SDL_GetMouseState(&mouseX,&mouseY);
            bool ballclicked = false ; //on créée un variable booleen false pour l'instant
            ballclicked = supprEllipse(*ellipses, mouseX, mouseY); // la variable prend la valeur true sur une ellipse est touchée, et reste false sinon
            if(ballclicked == false){//si la variable est false, on ajoute une ellipse
                ajoutEllipseXY(*ellipses, mouseX, mouseY);
            }
        }
    }

    return true;
}

