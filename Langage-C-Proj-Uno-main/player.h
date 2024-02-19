#ifndef DEF_HEADER_PLAYER
#define DEF_HEADER_PLAYER

#include <stdio.h>

typedef struct player player;
struct player{
    char name[20];
    int score;
    int nbCards;
    struct card *cards;
};
int choose_nb_players();
void choose_players_name(player *players, int nb_players);
void init_players(player *players, int nb_players);
void distribute_cards(player *players, card *deck, int nb_players);
void display_cards(player *players, int nb_players);
void display_deck(card *deck, int deck_size) ;
card draw_card(card *deck, int *nb_cards_drawn);



#endif 
