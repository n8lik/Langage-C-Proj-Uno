#include "card.h"
#include "player.h"
#include "rules.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


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
Color choose_color()
{
    int color;
    printf("Choisissez une couleur :\n");
    printf("1. Jaune\n");
    printf("2. Rouge\n");
    printf("3. Bleu\n");
    printf("4. Vert\n");
    scanf("%d", &color);
    while (color < 1 || color > 4)
    {
        printf("Erreur, veuillez choisir une couleur entre 1 et 4 : ");
        scanf("%d", &color);
    }
    return color;
}
// fonction pour appliquer les effets des cartes spéciales
void apply_special_card_effect(struct card card, struct player *players, int nb_players, int *current_player, int *direction, int *nb_cards_to_draw, struct card *top_card, struct card *deck, int deck_size)
{
    struct player previous_player; // Pour stocker le joueur précédent
    int next_player = (*current_player + *direction + nb_players) % nb_players;

    switch (card.type)
    {
    case deux:
        *nb_cards_to_draw += 2;
        if (players[next_player].nbCards < MAX_CARDS_PER_PLAYER && deck_size > 0)
        {
            players[next_player].cards[players[next_player].nbCards] = draw_card(deck, &deck_size); // Si deck_size est un int et vous changez la signature de draw_card
            players[next_player].nbCards++;
        }
        else
        {
            printf("Le joueur %s a atteint le nombre maximum de cartes ou le deck est vide.\n", players[next_player].name);
        }

        *current_player = next_player;
        *nb_cards_to_draw = 0;

        break;
    case sens:
        *direction *= -1;
        break;
    case pass:
        // Stocker le joueur précédent
        previous_player = players[*current_player];

        // Changer de joueur
        *current_player = (*current_player + *direction + nb_players) % nb_players;

        // Réaffecter les cartes du joueur précédent au joueur actuel
        players[*current_player].cards = previous_player.cards;
        players[*current_player].nbCards = previous_player.nbCards;
        break;
    case joker:
        top_card->color = choose_color();
        break;
    case quatre:
        *nb_cards_to_draw += 4;
        if (players[next_player].nbCards < MAX_CARDS_PER_PLAYER && deck_size > 0)
        {
            players[next_player].cards[players[next_player].nbCards] = draw_card(deck, &deck_size); // Si deck_size est un int et vous changez la signature de draw_card
            players[next_player].nbCards++;
        }
        else
        {
            printf("Le joueur %s a atteint le nombre maximum de cartes ou le deck est vide.\n", players[next_player].name);
        }

        *current_player = next_player;
        *nb_cards_to_draw = 0;

        break;
    default:
        break;
    }
}

// fonction pour gérer le tour d'un joueur (piocher (avec la fonction card draw_card(card *deck, int *nb_cards_drawn) du player.c), jouer, appliquer les effets des cartes spéciales)
void play_turn(player *players, int nb_players, card *deck, int deck_size, int *nb_cards_drawn, int *current_player, int *direction, int *nb_cards_to_draw, card *top_card, SDL_Surface *screen,SDL_Surface *bgImage)
{
      // Nettoyage de l'écran
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0)); // Choisissez une couleur de fond adéquate
    SDL_BlitSurface(bgImage, NULL, screen, NULL); // Redessine l'image de fond
    SDL_Flip(screen); // Applique le nettoyage à l'affichage


    //Afficher la carte du dessus
    printf("\n\nCarte du dessus : Valeur=%s, Couleur=%s, Type=%s\n", get_card_name(top_card->value), get_color_name(top_card->color), get_type_name(top_card->type));


    // Construire le chemin complet vers l'image de la carte
    char imagePath[256]; // Assurez-vous que ce tableau est assez grand
    sprintf(imagePath, "assets/cards/%s", top_card->img);

    // Charger l'image de la carte du dessus
    SDL_Surface *topCardImage = IMG_Load(imagePath);
    if (!topCardImage) {
        fprintf(stderr, "Impossible de charger l'image de la carte : %s\n", IMG_GetError());
        // Gérer l'erreur (par exemple, continuer sans crasher)
    } else {
        SDL_Rect topCardPos;
        topCardPos.x = 500; // Position x où afficher la carte
        topCardPos.y = 300; // Position y où afficher la carte

        SDL_BlitSurface(topCardImage, NULL, screen, &topCardPos);
        SDL_Flip(screen); // Met à jour l'écran avec la nouvelle image affichée

        SDL_FreeSurface(topCardImage); // Libère la mémoire de l'image chargée une fois affichée
    }
    //Afficher la pioche juste à côté de la carte du dessus
    char imagePath2[256]; // Assurez-vous que ce tableau est assez grand
    sprintf(imagePath2, "assets/cards/pioche.png");

    // Charger l'image de la carte du dessus
    SDL_Surface *deckImage = IMG_Load(imagePath2);
    if (!deckImage) {
        fprintf(stderr, "Impossible de charger l'image de la carte : %s\n", IMG_GetError());
        // Gérer l'erreur (par exemple, continuer sans crasher)
    } else {
        SDL_Rect deckPos;
        deckPos.x = 700; // Position x où afficher la carte
        deckPos.y = 300; // Position y où afficher la carte

        SDL_BlitSurface(deckImage, NULL, screen, &deckPos);
        SDL_Flip(screen); // Met à jour l'écran avec la nouvelle image affichée

        SDL_FreeSurface(deckImage); // Libère la mémoire de l'image chargée une fois affichée
    }

    //Afficher le nom du joueur actuel en SDL
    TTF_Font *font = TTF_OpenFont("assets/DUSTERY.ttf", 24);
    if (font == NULL)
    {
        fprintf(stderr, "Erreur lors du chargement de la police : %s\n", TTF_GetError());
        // Gérer l'erreur (par exemple, continuer sans crasher)
    }
    SDL_Color textColor = {255, 255, 255,0};
    SDL_Surface *text = TTF_RenderText_Solid(font, players[*current_player].name, textColor);
    if (text == NULL)
    {
        fprintf(stderr, "Erreur lors du rendu du texte : %s\n", TTF_GetError());
        // Gérer l'erreur (par exemple, continuer sans crasher)
    }
    SDL_Rect textPos;
    textPos.x = 500; // Position x où afficher le texte
    textPos.y = 50; // Position y où afficher le texte
    SDL_BlitSurface(text, NULL, screen, &textPos);
    SDL_Flip(screen); // Met à jour l'écran avec le nouveau texte affiché
    TTF_CloseFont(font); // Libère la mémoire de la police une fois utilisée
    SDL_FreeSurface(text); // Libère la mémoire du texte une fois affiché


    // Afficher les cartes du joueur
    printf("%s Vos cartes :\n", players[*current_player].name);
    for (int i = 0; i < players[*current_player].nbCards; i++)
    {
        printf("Carte %d : Valeur=%s, Couleur=%s, Type=%s\n", i + 1, get_card_name(players[*current_player].cards[i].value), get_color_name(players[*current_player].cards[i].color), get_type_name(players[*current_player].cards[i].type));
    }

    // Afficher les cartes du joueur avec des images
    for (int i = 0; i < players[*current_player].nbCards; i++)
    {
        // Construire le chemin complet vers l'image de la carte
        char imagePath[256]; // Assurez-vous que ce tableau est assez grand
        sprintf(imagePath, "assets/cards/%s", players[*current_player].cards[i].img);

        // Charger l'image de la carte
        SDL_Surface *cardImage = IMG_Load(imagePath);
        if (!cardImage) {
            fprintf(stderr, "Impossible de charger l'image de la carte : %s\n", IMG_GetError());
            // Gérer l'erreur (par exemple, continuer sans crasher)
        } else {
            SDL_Rect cardPos;
            cardPos.x = 350 + i * 100; // Position x où afficher la carte
            cardPos.y = 500; // Position y où afficher la carte

            SDL_BlitSurface(cardImage, NULL, screen, &cardPos);
            SDL_Flip(screen); // Met à jour l'écran avec la nouvelle image affichée

            SDL_FreeSurface(cardImage); // Libère la mémoire de l'image chargée une fois affichée
        }
    }

    // Demander au joueur de choisir une carte ou de piocher
    printf("Veuillez choisir une carte à jouer (1-%d) ou piocher (0) : ", players[*current_player].nbCards);
    int choice;
    scanf("%d", &choice);
    


    if (choice == 0)
    {
        // Piocher une carte
        if (players[*current_player].nbCards < MAX_CARDS_PER_PLAYER)
        {
            // Assurez-vous que le joueur a de la place dans sa main
            if (*nb_cards_drawn < deck_size)
            {
                players[*current_player].cards[players[*current_player].nbCards] = draw_card(deck, nb_cards_drawn);
                players[*current_player].nbCards++;
                printf("Vous avez pioché une carte.\n");
                play_turn(players, nb_players, deck, deck_size, nb_cards_drawn, current_player, direction, nb_cards_to_draw, top_card,screen, bgImage);
            }
            else
            {
                printf("Il n'y a plus de cartes à piocher.\n");
            }
        }
        else
        {
            printf("Vous avez atteint le nombre maximum de cartes.\n");
        }
    }

    else if (choice > 0 && choice <= players[*current_player].nbCards)
    {
        // Jouer une carte
        int card_index = choice - 1;

        if (can_be_played(players[*current_player].cards[card_index], *top_card))
        {
            // Appliquer les effets de la carte
            apply_special_card_effect(players[*current_player].cards[card_index], players, nb_players, current_player, direction, nb_cards_to_draw, top_card, deck, deck_size);

            // Mettre la carte sur le dessus de la pile
            *top_card = players[*current_player].cards[card_index];

            // Retirer la carte de la main du joueur
            for (int i = card_index; i < players[*current_player].nbCards - 1; i++)
            {
                players[*current_player].cards[i] = players[*current_player].cards[i + 1];
            }
            players[*current_player].nbCards--;
        }
        else
        {
            printf("Vous ne pouvez pas jouer cette carte.\n");
            // rejouer le tour
            play_turn(players, nb_players, deck, deck_size, nb_cards_drawn, current_player, direction, nb_cards_to_draw, top_card,screen, bgImage);
        }
    }
    else
    {
        printf("Choix non valide. Veuillez réessayer.\n");
    }

}

// Fonction pour calculer les scores et les garder dans un fichier nommé score.txt
void calculate_scores(player *players, int nb_players)
{
    FILE *score_file = fopen("result/score.txt", "w");
    if (score_file == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier score.txt\n");
        exit(1);
    }

    for (int i = 0; i < nb_players; i++)
    {
        int score = 0;
        for (int j = 0; j < players[i].nbCards; j++)
        {
            score += players[i].cards[j].value;
        }
        players[i].score += score;
        fprintf(score_file, "%s : %d\n", players[i].name, players[i].score);
    }

    fclose(score_file);
}