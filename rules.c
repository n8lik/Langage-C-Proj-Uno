#include "card.h"
#include "player.h"
#include "rules.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Fontion pour afficher le texte
void renderText(const char *text, int x, int y, SDL_Surface *screen)
{
    TTF_Font *font = TTF_OpenFont("assets/DUSTERY.ttf", 24);
    if (font == NULL)
    {
        fprintf(stderr, "Erreur lors du chargement de la police : %s\n", TTF_GetError());
        return; // Quitte la fonction en cas d'erreur
    }

    // Définit la couleur du texte
    SDL_Color textColor = {255, 255, 255, 0}; // Blanc avec opacité complète

    // Rend le texte dans une surface SDL
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, text, textColor);
    if (textSurface == NULL)
    {
        fprintf(stderr, "Erreur lors du rendu du texte : %s\n", TTF_GetError());
        TTF_CloseFont(font); // Assurez-vous de fermer la police même en cas d'erreur
        return;              // Quitte la fonction en cas d'erreur
    }

    // Prépare le rectangle pour positionner le texte
    SDL_Rect textPos = {x, y, 0, 0};

    // Blit le texte sur la surface de l'écran
    SDL_BlitSurface(textSurface, NULL, screen, &textPos);

    // Libère les ressources
    TTF_CloseFont(font);          // Ferme la police après utilisation
    SDL_FreeSurface(textSurface); // Libère la surface de texte
}

// fonction pour afficher les cartes de l'adversaire
void renderOpponentCards(player *players, int nb_players, int current_player, SDL_Surface *screen)
{
    for (int i = 0; i < nb_players; i++)
    {
        if (i != current_player)
        {
            int cardOffsetX = 275; // Position de départ en x pour le premier adversaire
            int cardOffsetY = 150; // Position de départ en y pour le premier adversaire
            // Afficher le nom de l'adversaire
            renderText(players[i].name, 600, cardOffsetY - 30, screen);
            // Afficher l'arriere de ses cartes
            char imagePath[256];
            sprintf(imagePath, "assets/cards/pioche.png");
            SDL_Surface *cardImage = IMG_Load(imagePath);
            if (!cardImage)
            {
                fprintf(stderr, "Impossible de charger l'image de la carte : %s\n", IMG_GetError());
                // Gérer l'erreur (par exemple, continuer sans crasher)
            }
            else
            {
                // Faire une boucle pour afficher les cartes de l'adversaire
                for (int j = 0; j < players[i].nbCards; j++)
                {
                    SDL_Rect cardPos;
                    cardPos.x = cardOffsetX + j * 20; // Position x où afficher la carte
                    cardPos.y = cardOffsetY;          // Position y où afficher la carte
                    SDL_BlitSurface(cardImage, NULL, screen, &cardPos);
                    SDL_Flip(screen); // Met à jour l'écran avec la nouvelle image affichée
                }
                SDL_FreeSurface(cardImage); // Libère la mémoire de l'image chargée une fois affichée
            }
            cardOffsetX += 200; // Espacement horizontal entre les cartes
        }
    }
}

//fonction pour afficher le nom et le nombre de cartes de l'adversaire
void renderOpponentsCards(player *players, int nb_players, int current_player, SDL_Surface *screen)
{
    //Afficher le nom et le nombre de cartes de l'adversaire les uns en dessous des autres
    for (int i = 0; i < nb_players; i++)
    {
        if (i != current_player)
        {
            char text[50];
            sprintf(text, "%s : %d cartes", players[i].name, players[i].nbCards);
            renderText(text, 600, 150 + i * 50, screen);
        }
    }
}

// fonction pour vérifier si une carte peut être posée
int can_be_played(struct card card, struct card top_card)
{
    if (card.color == BLACK)
    {
        return 1;
    }
    if (top_card.color == BLACK)
    {
        return 1;
    }
    if (card.value == top_card.value || card.color == top_card.color)
    {
        return 1;
    }
    return 0;
}

// fonction pour vérifier si le joueur a gagné
int has_won(player player)
{
    if (player.nbCards == 0)
    {
        return 1;
    }
    return 0;
}

// fonction du choix de la couleur
int choose_color(SDL_Surface *screen)
{
    // Affiche les instructions pour choisir une couleur
    renderText("Choisissez une couleur :", 400, 410, screen);

    // Définit les rectangles pour les boutons de couleur (x, y, largeur, hauteur)
    SDL_Rect yellowButton = {650, 410, 20, 20};
    SDL_Rect redButton = {700, 410, 20, 20};
    SDL_Rect blueButton = {750, 410, 20, 20};
    SDL_Rect greenButton = {800, 410, 20, 20};

    // Définit les couleurs pour les boutons
    Uint32 yellow = SDL_MapRGB(screen->format, 255, 255, 0);
    Uint32 red = SDL_MapRGB(screen->format, 255, 0, 0);
    Uint32 blue = SDL_MapRGB(screen->format, 0, 0, 255);
    Uint32 green = SDL_MapRGB(screen->format, 0, 255, 0);

    // Dessine les boutons sur l'écran
    SDL_FillRect(screen, &yellowButton, yellow);
    SDL_FillRect(screen, &redButton, red);
    SDL_FillRect(screen, &blueButton, blue);
    SDL_FillRect(screen, &greenButton, green);

    SDL_Flip(screen); // Met à jour l'écran

    bool chosen = false;
    int colorChoice = 1; // Valeur par défaut pour Jaune

    while (!chosen)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                exit(0); // Quitte directement, pourrait être géré plus subtilement
            }
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                int x = event.button.x;
                int y = event.button.y;

                // Vérifie si le clic est sur l'un des boutons de couleur
                if (x >= yellowButton.x && x <= yellowButton.x + yellowButton.w &&
                    y >= yellowButton.y && y <= yellowButton.y + yellowButton.h)
                {
                    colorChoice = 1; // Jaune
                    chosen = true;
                }
                else if (x >= redButton.x && x <= redButton.x + redButton.w &&
                         y >= redButton.y && y <= redButton.y + redButton.h)
                {
                    colorChoice = 2; // Rouge
                    chosen = true;
                }
                else if (x >= blueButton.x && x <= blueButton.x + blueButton.w &&
                         y >= blueButton.y && y <= blueButton.y + blueButton.h)
                {
                    colorChoice = 3; // Bleu
                    chosen = true;
                }
                else if (x >= greenButton.x && x <= greenButton.x + greenButton.w &&
                         y >= greenButton.y && y <= greenButton.y + greenButton.h)
                {
                    colorChoice = 4; // Vert
                    chosen = true;
                }
            }
        }
    }
    return colorChoice;
}

// fonction pour appliquer les effets des cartes spéciales
void apply_special_card_effect(struct card card, player *players, int nb_players, int current_player, int *direction, struct card *top_card, SDL_Surface *screen, SDL_Surface *bgImage)
{
    int next_player; // Pour stocker le joueur suivant
    char color[10];  // Pour stocker la couleur choisie
                     // Pour stocker le joueur suivant
    if (*direction == 1)
    { // Sens des aiguilles d'une montre
        next_player = (current_player + 1) % nb_players;
    }
    else
    { // Sens inverse des aiguilles d'une montre
        next_player = (current_player - 1 + nb_players) % nb_players;
    }

    switch (card.type)
    {
    case deux:
        players[next_player].nb_cards_to_draw += 2;
        // Afficher à l'écran "Le joueur suivant a pioché 2 cartes"
        renderText("Le joueur suivant pioche 2 cartes", 500, 410, screen);
        SDL_Flip(screen); // Met à jour l'écran avec le nouveau texte affiché
        // Attendre 1 seconde
        SDL_Delay(500);

        break;
    case sens:
        *direction *= -1;
        // Afficher à l'écran "Le sens du jeu a changé"
        renderText("Le sens du jeu a change", 500, 410, screen);
        SDL_Flip(screen); // Met à jour l'écran avec le nouveau texte affiché
        // Attendre 1 seconde
        SDL_Delay(500);
        break;
    case pass:
        // le joueur suivant ne peut pas jouer
        players[next_player].pass = 1;
        // Afficher à l'écran "Le joueur suivant ne peut pas jouer"
        renderText("Le joueur suivant ne peut pas jouer", 500, 410, screen);
        SDL_Flip(screen); // Met à jour l'écran avec le nouveau texte affiché
        // Attendre 1 seconde
        SDL_Delay(500);
        break;
    case joker:
        top_card->color = choose_color(screen);
        // Afficher la coueleur de la top_card
        // Transforme la couleur en chaine de caractère
        switch (top_card->color)
        {
        case 1:
            strcpy(color, "Jaune");
            break;
        case 2:
            strcpy(color, "Rouge");
            break;
        case 3:
            strcpy(color, "Bleu");
            break;
        case 4:
            strcpy(color, "Vert");
            break;
        default:
            break;
        }
        // Nettoyer l'écran
        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0)); // Choisissez une couleur de fond adéquate
        SDL_BlitSurface(bgImage, NULL, screen, NULL);                    // Redessine l'image de fond
        SDL_Flip(screen);                                                // Applique le nettoyage à l'affichage
        // Afficher la couleur choisie
        renderText("La couleur choisie est", 400, 410, screen);
        renderText(color, 700, 410, screen);
        SDL_Flip(screen); // Met à jour l'écran avec le nouveau texte affiché
        // Attendre 1 seconde
        SDL_Delay(500);

        break;
    case quatre:
        // nb_cards_to_draw += 4; pour le prochain joueur :
        players[next_player].nb_cards_to_draw += 4;

        renderText("Le joueur suivant pioche 4 cartes", 500, 410, screen);
        SDL_Flip(screen); // Met à jour l'écran avec le nouveau texte affiché
        // Attendre 1 seconde
        SDL_Delay(500);
        top_card->color = choose_color(screen);
        // Afficher la coueleur de la top_card
        // Transforme la couleur en chaine de caractère
        switch (top_card->color)
        {
        case 1:
            strcpy(color, "Jaune");
            break;
        case 2:
            strcpy(color, "Rouge");
            break;
        case 3:
            strcpy(color, "Bleu");
            break;
        case 4:
            strcpy(color, "Vert");
            break;
        default:
            break;
        }
        // Nettoyer l'écran
        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0)); // Choisissez une couleur de fond adéquate
        SDL_BlitSurface(bgImage, NULL, screen, NULL);                    // Redessine l'image de fond
        SDL_Flip(screen);                                                // Applique le nettoyage à l'affichage
        // Afficher la couleur choisie
        renderText("La couleur choisie est", 400, 410, screen);
        renderText(color, 700, 410, screen);
        SDL_Flip(screen); // Met à jour l'écran avec le nouveau texte affiché
        // Attendre 1 seconde
        SDL_Delay(500);

        break;
    default:
        break;
    }
}

// fonction pour gérer le tour d'un joueur (piocher (avec la fonction card draw_card(card *deck, int *nb_cards_drawn) du player.c), jouer, appliquer les effets des cartes spéciales)
void play_turn(struct player *players, int nb_players, card *deck, int *deck_size, player *current_player, int *direction, card *top_card, SDL_Surface *screen, SDL_Surface *bgImage)

{
    // Nettoyage de l'écran
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0)); // Choisissez une couleur de fond adéquate
    SDL_BlitSurface(bgImage, NULL, screen, NULL);                    // Redessine l'image de fond
    SDL_Flip(screen);                                                // Applique le nettoyage à l'affichage





    // ####################################Afficher les cartes de l'adversaire ############################################
    int current_player_index = current_player - players; // Calcule l'indice basé sur l'arithmétique des pointeurs
    //Si l n'y a que 2 joueurs
    if (nb_players == 2)
    {
        renderOpponentCards(players, nb_players, current_player_index, screen);
    }
    else
    {
        //Si il y a plus de 2 joueurs
        renderOpponentsCards(players, nb_players, current_player_index, screen);
    }
    SDL_Flip(screen); // Met à jour l'écran avec le nouveau texte affiché

    if (current_player->pass == 1)
    {
        current_player->pass = 0;
        return;
    }
    if (current_player->nb_cards_to_draw > 0)
    {
        for (int i = 0; i < current_player->nb_cards_to_draw; i++)
        {
            // Assurez-vous qu'il y a encore des cartes dans le deck à piocher
            if (*deck_size > 0)
            {
                // Piocher une carte du deck
                draw_card(deck, deck_size, current_player);
                (*deck_size)--;
            }
            else
            {
                // Gérer le cas où le deck est vide
                printf("Le deck est vide, impossible de piocher une carte.\n");
                break; // Sortir de la boucle si le deck est vide
            }
        }
        // Réinitialiser le nombre de cartes à piocher pour le joueur actuel à 0 après la pioche
        current_player->nb_cards_to_draw = 0;
    }

    // ####################################Afficher la carte du dessus de la pile ############################################
    //  Construire le chemin complet vers l'image de la carte
    char imagePath[256];
    sprintf(imagePath, "assets/cards/%s", top_card->img);

    // Charger l'image de la carte du dessus
    SDL_Surface *topCardImage = IMG_Load(imagePath);
    if (!topCardImage)
    {
        fprintf(stderr, "Impossible de charger l'image de la carte : %s\n", IMG_GetError());
    }
    else
    {
        SDL_Rect topCardPos;
        topCardPos.x = 500; // Position x où afficher la carte
        topCardPos.y = 300; // Position y où afficher la carte

        SDL_BlitSurface(topCardImage, NULL, screen, &topCardPos);
        SDL_Flip(screen); // Met à jour l'écran avec la nouvelle image affichée

        SDL_FreeSurface(topCardImage); // Libère la mémoire de l'image chargée une fois affichée
    }

    // ####################################Afficher la pioche juste à côté de la carte du dessus ############################################
    char imagePath2[256];
    sprintf(imagePath2, "assets/cards/pioche.png");

    // Charger l'image de la carte du dessus
    SDL_Surface *deckImage = IMG_Load(imagePath2);
    if (!deckImage)
    {
        fprintf(stderr, "Impossible de charger l'image de la carte : %s\n", IMG_GetError());
        // Gérer l'erreur (par exemple, continuer sans crasher)
    }
    else
    {
        SDL_Rect deckPos;
        deckPos.x = 700; // Position x où afficher la carte
        deckPos.y = 300; // Position y où afficher la carte

        SDL_BlitSurface(deckImage, NULL, screen, &deckPos);
        SDL_Flip(screen); // Met à jour l'écran avec la nouvelle image affichée

        SDL_FreeSurface(deckImage); // Libère la mémoire de l'image chargée une fois affichée
    }

    // ####################################Afficher le nom du joueur actuel ############################################
    renderText("C'est au tour de", 400, 50, screen);
    renderText(current_player->name, 600, 50, screen);
    SDL_Flip(screen); // Met à jour l'écran avec le nouveau texte affiché

    // ####################################Afficher les cartes du joueur actuel ############################################
    int cardOffsetX = 275;  // Position de départ en x
    int cardOffsetY = 450;  // Position de départ en y
    int cardsPerRow = 12;   // Nombre maximal de cartes par ligne
    int cardSpacingX = 60;  // Espacement horizontal entre les cartes
    int cardSpacingY = 100; // Espacement vertical entre les lignes
    // Tableau pour stocker la position des cartes du joueur du tour
    int cardPos[MAX_CARDS_PER_PLAYER][2];

      //Enregistrer la position de la première carte
    cardPos[0][0] = cardOffsetX;
    cardPos[0][1] = cardOffsetY; 
    
    // Construire le chemin complet vers l'image de la carte
    char imagePath3[256];
    sprintf(imagePath, "assets/cards/%s", current_player->cards[0].img);

    // Charger l'image de la carte
    SDL_Surface *cardImage3 = IMG_Load(imagePath3);
    if (!cardImage3) {
        fprintf(stderr, "Impossible de charger l'image de la carte : %s\n", IMG_GetError());
        // Gérer l'erreur (par exemple, continuer sans crasher)
    } else {
        // Afficher la carte à sa position calculée
        SDL_Rect cardPos3;
        cardPos3.x = cardOffsetX;
        cardPos3.y = cardOffsetY;

        SDL_BlitSurface(cardImage3, NULL, screen, &cardPos3);
        SDL_Flip(screen); // Met à jour l'écran avec la nouvelle image affichée

        SDL_FreeSurface(cardImage3); // Libère la mémoire de l'image chargée une fois affichée
    }

    for (int i = 0; i < current_player->nbCards; i++)
    {
        // Calculer la position de la carte en fonction de son index
        int row = i / cardsPerRow;
        int col = i % cardsPerRow;
        int xPos = cardOffsetX + col * cardSpacingX;
        int yPos = cardOffsetY + row * cardSpacingY;

        // Construire le chemin complet vers l'image de la carte
        char imagePath[256];
        sprintf(imagePath, "assets/cards/%s", current_player->cards[i].img);

        // Charger l'image de la carte
        SDL_Surface *cardImage = IMG_Load(imagePath);
        if (!cardImage)
        {
            fprintf(stderr, "Impossible de charger l'image de la carte : %s\n", IMG_GetError());
            // Gérer l'erreur (par exemple, continuer sans crasher)
        }
        else
        {
            // Afficher la carte à sa position calculée
            SDL_Rect cardPos;
            cardPos.x = xPos;
            cardPos.y = yPos;

            SDL_BlitSurface(cardImage, NULL, screen, &cardPos);
            SDL_Flip(screen); // Met à jour l'écran avec la nouvelle image affichée

            SDL_FreeSurface(cardImage); // Libère la mémoire de l'image chargée une fois affichée
        }

        // Stocker la position de la carte pour pouvoir la retrouver plus tard
        cardPos[i][0] = xPos;
        cardPos[i][1] = yPos;
    }

    // Récupérer le choix du joueur actuel pour piocher ou jouer une carte en cliquant sur la carte
    int choice = -1;
    int mouseX, mouseY;
    while (choice == -1)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                exit(0);
                break;
            case SDL_MOUSEBUTTONDOWN:
                // Récupérer les coordonnées de la souris
                SDL_GetMouseState(&mouseX, &mouseY);
                // Vérifier si les coordonnées de la souris correspondent à une carte
                for (int i = 0; i < current_player->nbCards; i++)
                {
                    //Si les coordonnées de la souris correspondent à la première carte, alors le choix est 0
                    if (mouseX >= cardPos[0][0] && mouseX <= cardPos[0][0] + 40 && mouseY >= cardPos[0][1] && mouseY <= cardPos[0][1] + 100)
                    {
                        choice = 0;
                        break;
                    }
                    if (mouseX >= cardPos[i][0] && mouseX <= cardPos[i][0] + 100 && mouseY >= cardPos[i][1] && mouseY <= cardPos[i][1] + 100)
                    {
                        choice = i + 1;
                        break;
                    }

                    // Vérifier si les coordonnées de la souris correspondent à la pioche
                    if (mouseX >= 700 && mouseX <= 700 + 100 && mouseY >= 300 && mouseY <= 300 + 150)
                    {
                        choice = -2;
                        break;
                    }
                }
                break;
            default:
                break;
            }
        }
    }
    if (choice == -2)
    {
        // Piocher une carte
        if (current_player->nbCards < MAX_CARDS_PER_PLAYER)
        {
            // Assurez-vous que le joueur a de la place dans sa main
            if (current_player->nb_cards_to_draw < *deck_size)
            {
                // Assurez-vous qu'il reste des cartes à piocher
                draw_card(deck, deck_size, current_player);
                // Afficher à l'écran "vous avez pioché une carte"
                renderText("Vous avez pioche une carte", 500, 410, screen);
                SDL_Flip(screen); // Met à jour l'écran avec le nouveau texte affiché
                // Attendre 1 seconde
                SDL_Delay(500);
                // Rejouer le tour
                play_turn(players, nb_players, deck, deck_size, current_player, direction, top_card, screen, bgImage);
            }
            else
            {
                // Afficher à l'écran "La piolche est vide"
                renderText("La pioche est vide", 500, 410, screen);
                SDL_Flip(screen); // Met à jour l'écran avec le nouveau texte affiché
            }
        }
        else
        {
            // Afficher à l'écran "Vous avez atteint le nombre maximum de cartes"
            renderText("Vous avez atteint le nombre maximum de cartes", 500, 410, screen);
            SDL_Flip(screen); // Met à jour l'écran avec le nouveau texte affiché
        }
    }

    else if (choice >= 0 && choice <= current_player->nbCards)
    {
        // Jouer une carte
        int card_index = choice;

        if (can_be_played(current_player->cards[card_index], *top_card))
        {
            // Appliquer les effets de la carte
            apply_special_card_effect(current_player->cards[card_index], players, nb_players, current_player_index, direction, top_card, screen, bgImage);
            // Mettre la carte sur le dessus de la pile
            *top_card = current_player->cards[card_index];

            // Retirer la carte de la main du joueur
            for (int i = card_index; i < current_player->nbCards - 1; i++)
            {
                current_player->cards[i] = current_player->cards[i + 1];
            }
            current_player->nbCards--;
        }
        else
        {
            // Afficher à l'écran "Vous ne pouvez pas jouer cette carte"
            renderText("Vous ne pouvez pas jouer cette carte", 500, 410, screen);
            SDL_Flip(screen); // Met à jour l'écran avec le nouveau texte affiché
            // Attendre 1 seconde
            SDL_Delay(500);
            // rejouer le tour
            play_turn(players, nb_players, deck, deck_size, current_player, direction, top_card, screen, bgImage);
        }
    }
    else
    {
        printf("Choix non valide. Veuillez réessayer.\n");
    }
}

// Fonction pour calculer les scores et les garder dans un fichier nommé score.txt
void calculate_scores()
{
    FILE *score_file = fopen("result/score.txt", "w");
    if (score_file == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier score.txt\n");
        exit(1);
    }

    // Récuperer dans le fichier score.txt le numéro derrière lachaine de caractère "point boutique = " 
    // et le stocker dans une variable score
    int score;
    fscanf(score_file, "point boutique = %d", &score);
    // Ajouter 5 au score
    score = score + 5;
    // Ecrire le nouveau score dans le fichier score.txt
    fprintf(score_file, "point boutique = %d", score);


    fclose(score_file);
}