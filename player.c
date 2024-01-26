#include <stdio.h>
#include <stdlib.h>
#include "card.h"
#include "player.h"

struct player{
    char name[20];
    int score;
    int nbCards;
    struct card *cards;
};