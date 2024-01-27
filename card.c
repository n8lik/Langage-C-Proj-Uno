#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "card.h"

const char *get_card_name(int value)
{
    switch (value)
    {
    case 0 ... 9:
        static char number[2];
        sprintf(number, "%d", value);
        return number;
    case 10:
        return "+2";
    case 11:
        return "sens";
    case 12:
        return "pass";
    case 13:
        return "joker";
    case 14:
        return "+4";
    default:
        return "";
    }
}

const char *get_color_name(Color c)
{
    switch (c)
    {
    case RED:
        return "Rouge";
    case BLUE:
        return "Bleu";
    case GREEN:
        return "Vert";
    case YELLOW:
        return "Jaune";
    case BLACK:
        return "Noir";
    default:
        return "Inconnu";
    }
}

const char *get_type_name(Type t)
{
    switch (t)
    {
    case 0:
        return "Normal";
    case 1:
        return "deux";
    case 2:
        return "sens";
    case 3:
        return "pass";
    case 4:
        return "joker";
    case 5:
        return "quatre";
    default:
        return "Inconnu";
    }
}

card *create_deck()
{
    card *deck = malloc(108 * sizeof(card));
    int index = 0;

    // Ajouter des cartes normales
    for (Color c = YELLOW; c <= GREEN; c++)
    {
        for (int i = 0; i < 10; i++)
        {
            int count = (i == 0) ? 1 : 2; // Un seul 0, deux pour les autres
            for (int j = 0; j < count; j++)
            {
                deck[index].value = i;
                deck[index].color = c;
                deck[index].type = NORMAL;
                index++;
            }
        }
    }

    // Ajouter des cartes spéciales pour chaque couleur sauf noire
    for (Color c = YELLOW; c <= GREEN; c++)
    {
        for (int i = 10; i <= 12; i++)
        { // +2, sens, passe ton tour
            for (int j = 0; j < 2; j++)
            { // 2 de chaque
                deck[index].value = i;
                deck[index].color = c;
                deck[index].type = i - 9;
                index++;
            }
        }
    }

    // Ajouter des jokers et +4, uniquement noirs
    for (int i = 13; i <= 14; i++)
    { // joker et +4
        for (int j = 0; j < 4; j++)
        { // 4 de chaque
            deck[index].value = i;
            deck[index].color = BLACK;
            deck[index].type = i - 9;
            index++;
        }
    }

    return deck;
}

void shuffle_deck(card *deck, int deck_size)
{
    srand(time(NULL)); // Initialisation du générateur de nombres aléatoires

    for (int i = deck_size - 1; i > 0; i--)
    {
        int j = rand() % (i + 1); // Sélectionner un index aléatoire

        // Échanger deck[i] et deck[j]
        card temp = deck[i];
        deck[i] = deck[j];
        deck[j] = temp;
    }
        printf("Deck mélangé.\n");

}