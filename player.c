#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <time.h>
#include "card.h"
#include "player.h"

// Pour afficher les messages
void display_message(SDL_Surface *screen, TTF_Font *font, const char *message, SDL_Color color, int x, int y)
{
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, message, color);
    SDL_Rect textLocation = {x, y, 0, 0};
    SDL_BlitSurface(textSurface, NULL, screen, &textLocation);
    SDL_Flip(screen);
    SDL_FreeSurface(textSurface);
}

// choix du nombre de joueurs (2 a 4 )
int choose_nb_players()
{

    // Ouvrir une fenêtre pour choisir le nombre de joueurs
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Surface *ecran = SDL_SetVideoMode(400, 200, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Choix du nombre de joueurs", NULL);
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
    SDL_Flip(ecran);
    SDL_Event event;

    // Initialisation de TTF
    int nb_players = 0;
    int continuer = 1;
    TTF_Init();
    TTF_Font *police = NULL;
    police = TTF_OpenFont("assets/DUSTERY.ttf", 20);
    // Si la police n'est pas chargée correctement on quitte la partie
    if (police == NULL)
    {
        printf("Erreur de chargement de la police : %s\n", TTF_GetError());
        return 1;
    }

    // Affichage du texte
    SDL_Color couleurNoire = {0, 0, 0, 0};
    SDL_Rect position;
    position.x = 0;
    position.y = 0;
    SDL_Surface *texte = NULL;
    texte = TTF_RenderText_Blended(police, "Choisissez le nombre de joueurs", couleurNoire);
    SDL_BlitSurface(texte, NULL, ecran, &position);
    SDL_Flip(ecran);
    SDL_FreeSurface(texte);

    // Affichage des boutons cotes a cotes, avec juste des ecritures 2 3 4
    SDL_Rect position2;
    position2.x = 100;
    position2.y = 100;
    SDL_Surface *texte2 = NULL;
    texte2 = TTF_RenderText_Blended(police, "2", couleurNoire);
    SDL_BlitSurface(texte2, NULL, ecran, &position2);
    SDL_Flip(ecran);
    SDL_FreeSurface(texte2);

    SDL_Rect position3;
    position3.x = 200;
    position3.y = 100;
    SDL_Surface *texte3 = NULL;
    texte3 = TTF_RenderText_Blended(police, "3", couleurNoire);
    SDL_BlitSurface(texte3, NULL, ecran, &position3);
    SDL_Flip(ecran);
    SDL_FreeSurface(texte3);

    SDL_Rect position4;
    position4.x = 300;
    position4.y = 100;
    SDL_Surface *texte4 = NULL;
    texte4 = TTF_RenderText_Blended(police, "4", couleurNoire);
    SDL_BlitSurface(texte4, NULL, ecran, &position4);
    SDL_Flip(ecran);
    SDL_FreeSurface(texte4);

    // Boucle infinie
    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
            continuer = 0;
            break;
        case SDL_MOUSEBUTTONUP:
            if (event.button.x > 100 && event.button.x < 150 && event.button.y > 100 && event.button.y < 150)
            {
                nb_players = 2;
                continuer = 0;
            }
            if (event.button.x > 200 && event.button.x < 250 && event.button.y > 100 && event.button.y < 150)
            {
                nb_players = 3;
                continuer = 0;
            }
            if (event.button.x > 300 && event.button.x < 350 && event.button.y > 100 && event.button.y < 150)
            {
                nb_players = 4;
                continuer = 0;
            }
            break;
        }
    }
    // Fermeture de TTF
    TTF_Quit();
    SDL_Quit();
    return nb_players;
}

void choose_players_name(player *players, int nb_players)
{
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    SDL_Surface *screen = SDL_SetVideoMode(550, 100, 32, SDL_SWSURFACE);
    TTF_Font *font = TTF_OpenFont("assets/DUSTERY.ttf", 20);
    SDL_Color color = {0, 0, 0, 0};
    // Efface l'écran
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));

    // Ecrire dans la fenêtre "Entrez les noms des joueurs dans le terminal"
    display_message(screen, font, "Entrez les noms des joueurs dans le terminal", color, 50, 50);

    // Saisie des noms dans le terminal
    for (int i = 0; i < nb_players; i++)
    {
        printf("Entrez le nom du joueur %d: ", i + 1);
        scanf("%19s", players[i].name);
    }

    // On ferme cet ecran et on ouvre un autre pour afficher les noms des joueurs
    SDL_FreeSurface(screen);
    screen = SDL_SetVideoMode(400, 300, 32, SDL_SWSURFACE);
    SDL_WM_SetCaption("Validation des noms des joueurs", NULL);
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));

    // Affiche les noms des joueurs dans la fenêtre SDL
    for (int i = 0; i < nb_players; i++)
    {
        char displayText[30];
        snprintf(displayText, 30, "Joueur %d: %s", i + 1, players[i].name);
        display_message(screen, font, displayText, color, 50, 100 + i * 30);
    }

    // Affiche un bouton "Valider"
    display_message(screen, font, "Valider", color, 50, 200);
    // Affiche un bouton "Recommencer"
    display_message(screen, font, "Recommencer", color, 150, 200);

    SDL_Rect validerButton = {50, 200, 100, 30};      // Zone pour le bouton Valider
    SDL_Rect recommencerButton = {150, 200, 100, 30}; // Zone pour le bouton Recommencer

    SDL_Event event;
    int loop = 1;
    while (loop)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                loop = 0;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT &&
                    event.button.x >= validerButton.x && event.button.x <= (validerButton.x + validerButton.w) &&
                    event.button.y >= validerButton.y && event.button.y <= (validerButton.y + validerButton.h))
                {
                    // Le bouton Valider a été cliqué
                    loop = 0; // Sortie de la boucle
                }
                if (event.button.button == SDL_BUTTON_LEFT &&
                    event.button.x >= recommencerButton.x && event.button.x <= (recommencerButton.x + recommencerButton.w) &&
                    event.button.y >= recommencerButton.y && event.button.y <= (recommencerButton.y + recommencerButton.h))
                {
                    // Le bouton Recommencer a été cliqué
                    loop = 0;                                 // Sortie de la boucle
                    choose_players_name(players, nb_players); // Recommencer la saisie des noms
                }
                break;
            }
        }
    }

    TTF_CloseFont(font);
    SDL_FreeSurface(screen);
    TTF_Quit();
    SDL_Quit();
    return;
}

// initialisation des joueurs
void init_players(player *players, int nb_players)
{
    for (int i = 0; i < nb_players; i++)
    {
        players[i].nbCards = 0;
        players[i].cards = malloc(MAX_CARDS_PER_PLAYER * sizeof(card));
    }
}
// ceci est un test
//  distribution des cartes
void distribute_cards(player *players, card *deck, int nb_players)
{
    for (int i = 0; i < nb_players; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            int deck_index = i * 7 + j; // This should not exceed deck_size - 1
            players[i].cards[j] = deck[deck_index];
            players[i].nbCards++;
            players[i].nb_cards_to_draw = 0; // Initialisation à 0 pour chaque joueur
        }
    }
}

// affichage des cartes
void display_cards(player *players, int nb_players)
{
    for (int i = 0; i < nb_players; i++)
    {
        printf("Joueur %d : %s\n", i + 1, players[i].name);
        for (int j = 0; j < players[i].nbCards; j++)
        {
            printf("Carte %d : Valeur=%s, Couleur=%s, Type=%s\n", j + 1, get_card_name(players[i].cards[j].value), get_color_name(players[i].cards[j].color), get_type_name(players[i].cards[j].type));
        }

        printf("Joueur %d a %d cartes après distribution.\n", i + 1, players[i].nbCards);
    }
}

void display_deck(card *deck, int deck_size)
{
    // Afficher le deck avec toutes ces caraaactéristiques, couleur, type, valeur, image
    for (int i = 0; i < deck_size; i++)
    {
        printf("Carte %d : Valeur=%s, Couleur=%s, Type=%s, Image=%s\n", i + 1, get_card_name(deck[i].value), get_color_name(deck[i].color), get_type_name(deck[i].type), deck[i].img);
    }
}

// piocher une carte non déjà distribuée en rajoutant celle qu'on vient de piocher dans les déjà distribuées
card draw_card(card *deck, int *nb_cards, player *p)
{
    if (*nb_cards <= 0)
    {
        printf("Il n'y a plus de cartes à piocher!\n");
        return (card){0}; // Retourne une carte vide si le deck est vide
    }

    // Piocher la dernière carte du deck
    card drawn_card = deck[*nb_cards - 1];

    // Ajouter la carte piochée à la main du joueur
    p->cards[p->nbCards] = drawn_card;
    p->nbCards++;

    // Retirer la carte piochée du deck
    (*nb_cards)--;

    // Retourner la carte piochée
    return drawn_card;
}
