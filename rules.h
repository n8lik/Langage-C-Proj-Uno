#ifndef DEF_HEADER_RULES
#define DEF_HEADER_RULES

#include "card.h"
#include "player.h"



void apply_special_card_effect(struct card card, struct player *players, int nb_players, int *current_player, int *direction, int *nb_cards_to_draw, struct card *top_card, struct card *deck, int deck_size);
int can_be_played(struct card card, struct card top_card);
int has_won(player player);

void play_turn(player *players, int nb_players, card *deck, int deck_size, int *nb_cards_drawn, int *current_player, int *direction, int *nb_cards_to_draw, card *top_card);

void calculate_scores(player *players, int nb_players);

card draw_card(card *deck, int *nb_cards_drawn);


#endif