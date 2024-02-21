#ifndef DEF_HEADER_PLAYER
#define DEF_HEADER_PLAYER

#include <stdio.h>
#include <stdbool.h> 
#include "card.h"


typedef struct player player;
struct player{
    char name[20];
    int score;
    int nbCards;
    struct card *cards;
    bool isAI;
};

int choose_nb_players();
void choose_players_name(player *players, int nb_players);
void init_players(player *players, int nb_players);
void distribute_cards(player *players, card *deck, int nb_players);
void display_cards(player *players, int nb_players);
void display_deck(card *deck, int deck_size);
void play_ai_turn(player *players, card *deck, int *nb_cards_drawn, card *top_card);

#endif
