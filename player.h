#ifndef DEF_HEADER_HASHMAP
#define DEF_HEADER_HASHMAP

#include <stdio.h>

typedef struct player player;
struct player{
    char name[20];
    int score;
    int nbCards;
    struct card *cards;
};

#endif // DEF_HEADER_HASHMAP
