#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<string>
#include<SDL/SDL.h>
#include<SDL/SDL_ttf.h>
#include"constantes.h"

//The key press interpreter
class StringInput
{
    public:
    //The storage string
    std::string str;
    //The text surface
    SDL_Surface *text;
    TTF_Font *fontSmall;
    public:
    //Initializes variables
    StringInput();
    //Does clean up
    ~StringInput();
    //Handles input
    void handleInput(SDL_Event event);
    //Shows the message on screen
    void showCentered(SDL_Surface *ecran);
};
void applySurface( int x, int y, SDL_Surface* source, SDL_Surface* destination);
