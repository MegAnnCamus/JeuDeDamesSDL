#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<SDL/SDL.h>
#include<SDL/SDL_ttf.h>
#include"constantes.h"
#include"structuresLogiques.h"
#include"structuresSDL.h"

extern blackTile caseNoir;
extern whiteTile caseBlanc;
extern whiteTile caseHighlight;
extern whitePawn pionBlanc;
extern blackPawn pionNoir;
extern plateau plateauDeJeu;

void gestionEvenements(SDL_Surface *ecran)
{
    int continuer = 1;
    SDL_Event event;
    casePlateau *caseCliquee;

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                break;
        }

        SDL_Flip(ecran);
    }
}

void affichePlateauSDL(SDL_Surface* ecran){

    ecran = SDL_SetVideoMode(TAILLE_ECRAN, TAILLE_ECRAN, 32, SDL_HWSURFACE);
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 243, 235, 215));
	caseNoir.surface = SDL_LoadBMP("./img/cases/caseNoir.bmp");
	caseHighlight.surface = SDL_LoadBMP("./img/cases/caseHighlight.bmp");

	for(int i=1;i<=50;i++){

        //Affichage des cases du plateau
        if(plateauDeJeu.cases[i].isHighlighted == FALSE){
            caseNoir.position.x = (plateauDeJeu.cases[i].x - 1) * TAILLE_CASE;
            caseNoir.position.y = (plateauDeJeu.cases[i].y - 1) * TAILLE_CASE;
            SDL_BlitSurface(caseNoir.surface, NULL, ecran, &caseNoir.position);
		}
		else {
            caseHighlight.position.x = (plateauDeJeu.cases[i].x - 1) * TAILLE_CASE;
			caseHighlight.position.y = (plateauDeJeu.cases[i].y - 1) * TAILLE_CASE;
			SDL_BlitSurface(caseHighlight.surface, NULL, ecran, &caseHighlight.position);
		}

		pionBlanc.position.x = (plateauDeJeu.cases[i].x - 1) * TAILLE_CASE + 2;
        pionBlanc.position.y = (plateauDeJeu.cases[i].y - 1) * TAILLE_CASE + 2;
        pionNoir.position.x = (plateauDeJeu.cases[i].x - 1) * TAILLE_CASE + 2;
        pionNoir.position.y = (plateauDeJeu.cases[i].y - 1) * TAILLE_CASE + 2;

        //Affichage des pions
        if(plateauDeJeu.cases[i].isLibre == FALSE){ //S'il y a un pion sur la case

			if(plateauDeJeu.cases[i].pion.couleur == BLANC){ // Si le pion est blanc

				if(plateauDeJeu.cases[i].pion.isDame == FALSE){ // Si le pion n'est pas une dame

					if(plateauDeJeu.cases[i].pion.isHighlighted == FALSE){ // Si le pion n'est pas sélectionné
						pionBlanc.surface = SDL_LoadBMP("./img/pions/pionBlanc.bmp");
						SDL_SetColorKey(pionBlanc.surface, SDL_SRCCOLORKEY, SDL_MapRGB(pionBlanc.surface->format, 255, 255, 255));
						SDL_BlitSurface(pionBlanc.surface, NULL, ecran, &pionBlanc.position);
					}
					else{
						pionBlanc.surface = SDL_LoadBMP("./img/pions/pionBlancHighlight.bmp");
						SDL_SetColorKey(pionBlanc.surface, SDL_SRCCOLORKEY, SDL_MapRGB(pionBlanc.surface->format, 255, 255, 255));
						SDL_BlitSurface(pionBlanc.surface, NULL, ecran, &pionBlanc.position);
					}
				}
				else{

					if(plateauDeJeu.cases[i].pion.isHighlighted == FALSE){ //Si la dame n'est pas sélectionnée
						pionBlanc.surface = SDL_LoadBMP("./img/pions/dameBlanc.bmp");
						SDL_SetColorKey(pionBlanc.surface, SDL_SRCCOLORKEY, SDL_MapRGB(pionBlanc.surface->format, 255, 255, 255));
						SDL_BlitSurface(pionBlanc.surface, NULL, ecran, &pionBlanc.position);
					}
					else{
						pionBlanc.surface = SDL_LoadBMP("./img/pions/dameBlancHighlight.bmp");
						SDL_SetColorKey(pionBlanc.surface, SDL_SRCCOLORKEY, SDL_MapRGB(pionBlanc.surface->format, 255, 255, 255));
						SDL_BlitSurface(pionBlanc.surface, NULL, ecran, &pionBlanc.position);
					}
				}
			}


			if(plateauDeJeu.cases[i].pion.couleur == NOIR){

				if(plateauDeJeu.cases[i].pion.isDame == FALSE){

					if(plateauDeJeu.cases[i].pion.isHighlighted == FALSE){
						pionNoir.surface = SDL_LoadBMP("./img/pions/pionNoir.bmp");
						SDL_SetColorKey(pionNoir.surface, SDL_SRCCOLORKEY, SDL_MapRGB(pionNoir.surface->format, 255, 255, 255));
						SDL_BlitSurface(pionNoir.surface, NULL, ecran, &pionNoir.position);
					}
					else{
						pionNoir.surface = SDL_LoadBMP("./img/pions/pionNoirHighlight.bmp");
						SDL_SetColorKey(pionNoir.surface, SDL_SRCCOLORKEY, SDL_MapRGB(pionNoir.surface->format, 255, 255, 255));
						SDL_BlitSurface(pionNoir.surface, NULL, ecran, &pionNoir.position);
					}
				}

				else{

					if(plateauDeJeu.cases[i].pion.isHighlighted == 0){
						pionNoir.surface = SDL_LoadBMP("./img/pions/dameNoir.bmp");
						SDL_SetColorKey(pionNoir.surface, SDL_SRCCOLORKEY, SDL_MapRGB(pionNoir.surface->format, 255, 255, 255));
						SDL_BlitSurface(pionNoir.surface, NULL, ecran, &pionNoir.position);
					}
					else{
						pionNoir.surface = SDL_LoadBMP("./img/pions/dameNoirHighlight.bmp");
						SDL_SetColorKey(pionNoir.surface, SDL_SRCCOLORKEY, SDL_MapRGB(pionNoir.surface->format, 255, 255, 255));
						SDL_BlitSurface(pionNoir.surface, NULL, ecran, &pionNoir.position);
					}
				}
			}

		}

	}

	SDL_WM_SetCaption("Jeu de dames", NULL);
    /* Mise à jour de l'écran et de tout ce qu'il contient. */
    SDL_Flip(ecran);
    gestionEvenements(ecran);

    SDL_Quit();
}

int constructMenu(SDL_Surface* ecran, TTF_Font* font)
{

	int x, y;
    SDL_Surface  *imageDeFond = NULL;

	const char* labels[NB_ITEMS_MENU] = {"Jouer","Quitter"};
	SDL_Surface* menus[NB_ITEMS_MENU];
	int selected[NB_ITEMS_MENU] = {FALSE,FALSE};

	SDL_Color color[2] = {{218, 225, 237},{146, 170, 212}};

    ecran = SDL_SetVideoMode(TAILLE_ECRAN, TAILLE_ECRAN, 32, SDL_HWSURFACE);
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));

	menus[0] = TTF_RenderText_Solid(font,labels[0],color[0]);
	menus[1] = TTF_RenderText_Solid(font,labels[1],color[0]);

	SDL_Rect positionsItems[NB_ITEMS_MENU];
	positionsItems[0].x = ecran->clip_rect.w/2 - menus[0]->clip_rect.w/2;
	positionsItems[0].y = ecran->clip_rect.h/2 - menus[0]->clip_rect.h;
	positionsItems[1].x = ecran->clip_rect.w/2 - menus[1]->clip_rect.w/2;
	positionsItems[1].y = ecran->clip_rect.h/2 + menus[1]->clip_rect.h;

    SDL_Rect positionFond;

    positionFond.x = 0;
    positionFond.y = 0;

    imageDeFond = SDL_LoadBMP("./img/ui/fond.bmp");

    SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
	SDL_Event event;
	int continuer = 1;
	while(continuer)
	{
		SDL_WaitEvent(&event);

			switch(event.type)
			{
				case SDL_QUIT:
					SDL_FreeSurface(menus[0]);
					SDL_FreeSurface(menus[1]);
					continuer = 0;
				case SDL_MOUSEMOTION:
					x = event.motion.x;
					y = event.motion.y;
					for(int i = 0; i < NB_ITEMS_MENU; i++) {
						if(x>=positionsItems[i].x && x<=positionsItems[i].x+positionsItems[i].w && y>=positionsItems[i].y && y<=positionsItems[i].y+positionsItems[i].h)
						{
							if(selected[i]==FALSE)
							{
								selected[i] = TRUE;
								SDL_FreeSurface(menus[i]);
								menus[i] = TTF_RenderText_Solid(font,labels[i],color[1]);
							}
						}
						else
						{
							if(selected[i]==TRUE)
							{
								selected[i] = FALSE;
								SDL_FreeSurface(menus[i]);
								menus[i] = TTF_RenderText_Solid(font,labels[i],color[0]);
							}
						}
					}
					break;
				case SDL_MOUSEBUTTONDOWN:
					x = event.button.x;
					y = event.button.y;
					for(int i = 0; i < NB_ITEMS_MENU; i ++) {
						if(x>=positionsItems[i].x && x<=positionsItems[i].x+positionsItems[i].w && y>=positionsItems[i].y && y<=positionsItems[i].y+positionsItems[i].h)
						{
						    switch(i){

                            case 0 :
                                SDL_FreeSurface(menus[0]);
                                SDL_FreeSurface(menus[1]);
                                affichePlateauSDL(ecran);
                                break;

						    default :
                                SDL_FreeSurface(menus[0]);
                                SDL_FreeSurface(menus[1]);
                                break;
						    }
						}
					}
					break;
			}

		for(int i = 0; i < NB_ITEMS_MENU; i ++) {
			SDL_BlitSurface(menus[i],NULL,ecran,&positionsItems[i]);
		}

		SDL_Flip(ecran);
	}


    SDL_Quit();
}

void afficheMenuJeu(SDL_Surface *ecran)
{
	ecran = SDL_SetVideoMode(TAILLE_ECRAN,TAILLE_ECRAN,32,SDL_SWSURFACE);
	SDL_WM_SetCaption("Jeu de dames", NULL);

	TTF_Font *font;
	TTF_Init();
	font = TTF_OpenFont("./highland-gothic/HighlandGothicFLF.ttf",30);

	int result;
	result = constructMenu(ecran, font);
}


