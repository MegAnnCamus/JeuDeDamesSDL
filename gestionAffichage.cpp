#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include"gestionAffichage.h"
#include"classeSaisieTexte.h"

extern blackTile caseNoir;
extern whiteTile caseBlanc;
extern whiteTile caseHighlight;
extern whitePawn pionBlanc;
extern blackPawn pionNoir;
extern plateau plateauDeJeu;
extern int nbClic;
extern joueur joueur1,joueur2;

void gestionEvenements(SDL_Surface *ecran)
{
    int continuer = 1;
    SDL_Event event;

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_MOUSEBUTTONDOWN:
                nbClic = nbClic % 2;
                int* coordonnees = clicPlateau(event);
                //fprintf(stdout,"Coordonnees sur la grille = (%d,%d)\n",coordonnees[0],coordonnees[1]);
                highlightPionClic(coordonnees);
                nbClic++;
                affichePlateauSDL(ecran);
                break;
        }
        //affichePlateauSDL(ecran);
        SDL_Flip(ecran);
    }
}

void affichePlateauSDL(SDL_Surface* ecran){

    ecran = SDL_SetVideoMode(TAILLE_ECRAN_X, TAILLE_ECRAN_Y, 32, SDL_HWSURFACE);
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 243, 235, 215));
	caseNoir.surface = SDL_LoadBMP("./img/cases/caseNoir.bmp");
	caseHighlight.surface = SDL_LoadBMP("./img/cases/caseHighlight.bmp");

	afficheRightPanel(ecran,plateauDeJeu.j1,plateauDeJeu.j2,plateauDeJeu.tour);
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

					if(plateauDeJeu.cases[i].pion.isHighlighted == FALSE){ // Si le pion n'est pas s�lectionn�
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

					if(plateauDeJeu.cases[i].pion.isHighlighted == FALSE){ //Si la dame n'est pas s�lectionn�e
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

					if(plateauDeJeu.cases[i].pion.isHighlighted == FALSE){
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
    /* Mise � jour de l'�cran et de tout ce qu'il contient. */
    SDL_Flip(ecran);
    gestionEvenements(ecran);

    SDL_Quit();
}

void afficheRightPanel(SDL_Surface* ecran, joueur j1, joueur j2, joueur tour){

    TTF_Font *fontBig;
	TTF_Init();
	fontBig = TTF_OpenFont("./highland-gothic/HighlandGothicFLF.ttf",30);

    TTF_Font *fontSmall;
	TTF_Init();
	fontSmall = TTF_OpenFont("./highland-gothic/HighlandGothicFLF.ttf",20);

    const char* labels[NB_ITEMS_PANNEAU] = {"Au tour de : ","Joueur 1 : ", "Joueur 2 : "};
    SDL_Surface* items[NB_ITEMS_PANNEAU];

    SDL_Color color[2] = {{31, 47, 55},{146, 170, 212}};
    items[0] = TTF_RenderText_Solid(fontBig,labels[0],color[0]);
	items[1] = TTF_RenderText_Solid(fontBig,labels[1],color[0]);
	items[2] = TTF_RenderText_Solid(fontBig,labels[2],color[0]);

	const char* sublabels[NB_ITEMS_PANNEAU] = {"Nom : ","Couleur : ", "Nb pions restants : "};
	SDL_Surface* subitems[NB_ITEMS_PANNEAU];

    subitems[0] = TTF_RenderText_Solid(fontSmall,sublabels[0],color[0]);
	subitems[1] = TTF_RenderText_Solid(fontSmall,sublabels[1],color[0]);
	subitems[2] = TTF_RenderText_Solid(fontSmall,sublabels[2],color[0]);

	SDL_Rect positionsItems[NB_ITEMS_PANNEAU];
	//positions gros titres
	positionsItems[0].x = POS_TXT_PANNEAU;
	positionsItems[0].y = POS_TITRE_PANNEAU;
	positionsItems[1].x = POS_TXT_PANNEAU;
	positionsItems[1].y = POS_TITRE_PANNEAU + 100;
    positionsItems[2].x = POS_TXT_PANNEAU;
	positionsItems[2].y = positionsItems[1].y + TAILLE_INFOS_JOUEUR;

	SDL_Surface* couleurEnCours;
	SDL_Rect positionCouleurEnCours;
	if(tour.couleur==BLANC)
        couleurEnCours = SDL_LoadBMP("./img/pions/pionBlanc.bmp");
    else
        couleurEnCours = SDL_LoadBMP("./img/pions/pionNoir.bmp");

    SDL_SetColorKey(couleurEnCours, SDL_SRCCOLORKEY, SDL_MapRGB(couleurEnCours->format, 255, 255, 255));
    positionCouleurEnCours.x = POS_TXT_PANNEAU + 200;
    positionCouleurEnCours.y = POS_TITRE_PANNEAU - 5;
    SDL_BlitSurface(couleurEnCours,NULL,ecran,&positionCouleurEnCours);

    for(int i = 0; i < NB_ITEMS_PANNEAU; i ++) {
			SDL_BlitSurface(items[i],NULL,ecran,&positionsItems[i]);
			if(i==1){
                SDL_Rect positionsSubItems[NB_ITEMS_PANNEAU];
                //positions cat�gories infos joueurs
                positionsSubItems[0].x = POS_TXT_PANNEAU;
                positionsSubItems[0].y = positionsItems[1].y + TAILLE_INFOS_JOUEUR/4;
                positionsSubItems[1].x = POS_TXT_PANNEAU;
                positionsSubItems[1].y = positionsSubItems[0].y + TAILLE_INFOS_JOUEUR/4;
                positionsSubItems[2].x = POS_TXT_PANNEAU;
                positionsSubItems[2].y = positionsSubItems[1].y + TAILLE_INFOS_JOUEUR/4;

                //recup infos sur le joueur 1
                SDL_Surface* infos[NB_ITEMS_PANNEAU];
                infos[0] = TTF_RenderText_Solid(fontSmall,j1.nom,color[0]);
                if(j1.couleur==BLANC)
                    infos[1] = SDL_LoadBMP("./img/icons/iconBlanc.bmp");
                else
                    infos[1] = SDL_LoadBMP("./img/icons/iconNoir.bmp");

                SDL_SetColorKey(infos[1], SDL_SRCCOLORKEY, SDL_MapRGB(infos[1]->format, 255, 255, 255));
                //TODO : ajouter nb pions et l'afficher
                infos[2] = TTF_RenderText_Solid(fontSmall,"20",color[0]);

                SDL_Rect positionsInfos[NB_ITEMS_PANNEAU];
                positionsInfos[0].x = POS_TXT_PANNEAU + 70;
                positionsInfos[0].y = positionsSubItems[0].y;
                positionsInfos[1].x = POS_TXT_PANNEAU + 100;
                positionsInfos[1].y = positionsSubItems[1].y - 10;
                positionsInfos[2].x = POS_TXT_PANNEAU + 210;
                positionsInfos[2].y = positionsSubItems[2].y;

                for(int j = 0; j < NB_ITEMS_PANNEAU; j ++) {
                    SDL_BlitSurface(subitems[j],NULL,ecran,&positionsSubItems[j]);
                    SDL_BlitSurface(infos[j],NULL,ecran,&positionsInfos[j]);

                }
            }
            if(i==2){
                SDL_Rect positionsSubItems[NB_ITEMS_PANNEAU];
                positionsSubItems[0].x = POS_TXT_PANNEAU;
                positionsSubItems[0].y = positionsItems[2].y + TAILLE_INFOS_JOUEUR/4;
                positionsSubItems[1].x = POS_TXT_PANNEAU;
                positionsSubItems[1].y = positionsSubItems[0].y + TAILLE_INFOS_JOUEUR/4;
                positionsSubItems[2].x = POS_TXT_PANNEAU;
                positionsSubItems[2].y = positionsSubItems[1].y + TAILLE_INFOS_JOUEUR/4;

                //recup infos sur le joueur 1
                SDL_Surface* infos[NB_ITEMS_PANNEAU];
                infos[0] = TTF_RenderText_Solid(fontSmall,j2.nom,color[0]);
                if(j2.couleur==BLANC)
                    infos[1] = SDL_LoadBMP("./img/icons/iconBlanc.bmp");
                else
                    infos[1] = SDL_LoadBMP("./img/icons/iconNoir.bmp");

                SDL_SetColorKey(infos[1], SDL_SRCCOLORKEY, SDL_MapRGB(infos[1]->format, 255, 255, 255));
                //TODO : ajouter nb pions et l'afficher
                infos[2] = TTF_RenderText_Solid(fontSmall,"20",color[0]);

                SDL_Rect positionsInfos[NB_ITEMS_PANNEAU];
                positionsInfos[0].x = POS_TXT_PANNEAU + 70;
                positionsInfos[0].y = positionsSubItems[0].y;
                positionsInfos[1].x = POS_TXT_PANNEAU + 100;
                positionsInfos[1].y = positionsSubItems[1].y - 10;
                positionsInfos[2].x = POS_TXT_PANNEAU + 210;
                positionsInfos[2].y = positionsSubItems[2].y;

                for(int j = 0; j < NB_ITEMS_PANNEAU; j ++) {
                    SDL_BlitSurface(subitems[j],NULL,ecran,&positionsSubItems[j]);
                    SDL_BlitSurface(infos[j],NULL,ecran,&positionsInfos[j]);

                }
            }
    }
}


int constructMenu(SDL_Surface* ecran, TTF_Font* font)
{
	int x, y;
    SDL_Surface  *imageDeFond = NULL;

	const char* labels[NB_ITEMS_MENU] = {"Jouer","Quitter"};
	SDL_Surface* menus[NB_ITEMS_MENU];
	int selected[NB_ITEMS_MENU] = {FALSE,FALSE};

	SDL_Color color[2] = {{31, 47, 55},{146, 170, 212}};

    ecran = SDL_SetVideoMode(TAILLE_ECRAN_Y, TAILLE_ECRAN_Y, 32, SDL_HWSURFACE);
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
                                saisieNom(ecran, FALSE, &joueur1);
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
	ecran = SDL_SetVideoMode(TAILLE_ECRAN_Y,TAILLE_ECRAN_Y,32,SDL_SWSURFACE);
	SDL_WM_SetCaption("Jeu de dames", NULL);

	TTF_Font *font;
	TTF_Init();
	font = TTF_OpenFont("./highland-gothic/HighlandGothicFLF.ttf",30);

	int result;
	result = constructMenu(ecran, font);
}

void saisieNom(SDL_Surface *ecran, int gameStart, joueur *player){

    ecran = SDL_SetVideoMode(TAILLE_ECRAN_X/2, TAILLE_ECRAN_Y/2, 32, SDL_HWSURFACE);
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 243, 235, 215));
    SDL_Color color[2] = {{31, 47, 55},{146, 170, 212}};

    TTF_Font *fontBig;
	TTF_Init();
	fontBig = TTF_OpenFont("./highland-gothic/HighlandGothicFLF.ttf",30);
	SDL_Surface* titre;

	if(gameStart == FALSE)
        titre = TTF_RenderText_Solid(fontBig,"Saisir le nom du joueur 1 : ",color[0]);
    else
        titre = TTF_RenderText_Solid(fontBig,"Saisir le nom du joueur 2 : ",color[0]);

    SDL_Rect positionTitre;
	positionTitre.x = 20;
	positionTitre.y = 20;

	SDL_BlitSurface(titre,NULL,ecran,&positionTitre);

    int nomSaisi = FALSE;
    int quitter = FALSE;
    StringInput nomJoueur;
    SDL_Event event;
    while(quitter == FALSE){
         while( SDL_PollEvent( &event ) ){
            if( nomSaisi == FALSE){
                nomJoueur.handleInput(event);

                if( ( event.type == SDL_KEYDOWN ) && ( event.key.keysym.sym == SDLK_RETURN ) )
                {
                    nomSaisi = TRUE;
                    player->nom = strdup(nomJoueur.str.c_str());

                    if(gameStart == TRUE){
                        plateauDeJeu = initPlateau(joueur1,joueur2);
                        affichePlateauSDL(ecran);
                    }
                    else{
                        saisieNom(ecran,TRUE,&joueur2);
                    }
                }
            }
            if( event.type == SDL_QUIT )
            {
                quitter = TRUE;
            }
        }
        nomJoueur.showCentered(ecran);
        SDL_Flip(ecran);
    }

    SDL_FreeSurface( titre );
    TTF_CloseFont( fontBig );
    TTF_Quit();
    SDL_Quit();

}


int* clicPlateau(SDL_Event evenement){
	int* tableau = (int*)malloc(2*sizeof(int));
	int xSouris,ySouris;
	SDL_Rect positionSouris;

	positionSouris.x = evenement.button.x;
	positionSouris.y = evenement.button.y;
	xSouris = positionSouris.x / TAILLE_CASE + 1;
	ySouris = positionSouris.y / TAILLE_CASE + 1;

	tableau[0] = xSouris;
	tableau[1] = ySouris;
	return tableau;
}

casePlateau highlightPionClic(int *tab){
	casePlateau c;
	c = getCasePlateau(tab[0], tab[1], plateauDeJeu);
	//On d�selectionne tous les pions
	for(int i=1;i<=50;i++){
        if(i!=c.notation)
            plateauDeJeu.cases[i].pion.isHighlighted = FALSE;
    }
    //Si c'est bien le joueur en cours
	if(c.pion.couleur == plateauDeJeu.tour.couleur){
        if(plateauDeJeu.cases[c.notation].pion.isHighlighted == TRUE)
            plateauDeJeu.cases[c.notation].pion.isHighlighted = FALSE;
        else
            plateauDeJeu.cases[c.notation].pion.isHighlighted = TRUE;
	}
	return c;
}



