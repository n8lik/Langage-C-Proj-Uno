#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
    // Initialisation de SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
        return 1;
    }

    // Initialisation de TTF
    if (TTF_Init() != 0)
    {
        fprintf(stderr, "Unable to initialize SDL_ttf: %s\n", TTF_GetError());
        SDL_Quit();
        return 1;
    }

    // Création de la fenêtre
    SDL_Surface *screen = SDL_SetVideoMode(1280, 720, 32, SDL_SWSURFACE);
    if (screen == NULL)
    {
        fprintf(stderr, "Unable to set video mode: %s\n", SDL_GetError());
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    // Chargement de l'image de fond
    SDL_Surface *backgroundImage = IMG_Load("assets/background.jpg");
    if (!backgroundImage)
    {
        fprintf(stderr, "Unable to load background image: %s\n", IMG_GetError());
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    // Affichage de l'image de fond
    SDL_BlitSurface(backgroundImage, NULL, screen, NULL);

    // Chargement de la police
    TTF_Font *font = TTF_OpenFont("assets/PressStart2P-Regular.ttf", 40);
    if (!font)
    {
        fprintf(stderr, "Unable to load font: %s\n", TTF_GetError());
        SDL_FreeSurface(backgroundImage);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    // Couleur du texte
    SDL_Color textColor = {255, 255, 255};

    // Création du texte SOLO
    SDL_Surface *textSurfacesolo = TTF_RenderText_Solid(font, "SOLO", textColor);
    if (!textSurfacesolo)
    {
        fprintf(stderr, "Unable to render text: %s\n", TTF_GetError());
        TTF_CloseFont(font);
        SDL_FreeSurface(backgroundImage);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }
    int x_position = 1110; // par exemple, 100 pixels depuis la gauche de l'écran
    int y_position = 183;  // par exemple, 100 pixels depuis le haut de l'écran
    // Position du texte sur l'écran
    SDL_Rect textPositionsolo = {x_position, y_position, 0, 0};
    SDL_BlitSurface(textSurfacesolo, NULL, screen, &textPositionsolo);

    // Création du texte MULTI
    SDL_Surface *textSurfacemulti = TTF_RenderText_Solid(font, "MULTI", textColor);
    if (!textSurfacemulti)
    {
        fprintf(stderr, "Unable to render text: %s\n", TTF_GetError());
        TTF_CloseFont(font);
        SDL_FreeSurface(backgroundImage);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }
    int x_position2 = 1070; // par exemple, 100 pixels depuis la gauche de l'écran
    int y_position2 = 323;  // par exemple, 100 pixels depuis le haut de l'écran
    // Position du texte sur l'écran
    SDL_Rect textPositionmulti = {x_position2, y_position2, 0, 0};
    SDL_BlitSurface(textSurfacemulti, NULL, screen, &textPositionmulti);

    // création du texte ANARCHIE
    SDL_Surface *textSurfaceanarchie = TTF_RenderText_Solid(font, "ANARCHIE", textColor);
    if (!textSurfaceanarchie)
    {
        fprintf(stderr, "Unable to render text: %s\n", TTF_GetError());
        TTF_CloseFont(font);
        SDL_FreeSurface(backgroundImage);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }
    int x_position3 = 950; // par exemple, 100 pixels depuis la gauche de l'écran
    int y_position3 = 463;  // par exemple, 100 pixels depuis le haut de l'écran
    // Position du texte sur l'écran
    SDL_Rect textPositionanarchie = {x_position3, y_position3, 0, 0};
    SDL_BlitSurface(textSurfaceanarchie, NULL, screen, &textPositionanarchie);
    
    // Création du texte QUITTER en haut a droite

    SDL_Surface *textSurfacequitter = TTF_RenderText_Solid(font, "QUITTER", textColor);
    if (!textSurfacequitter)
    {
        fprintf(stderr, "Unable to render text: %s\n", TTF_GetError());
        TTF_CloseFont(font);
        SDL_FreeSurface(backgroundImage);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }
    int x_position4 = 20; // par exemple, 100 pixels depuis la gauche de l'écran
    int y_position4 = 10;  // par exemple, 100 pixels depuis le haut de l'écran
    // Position du texte sur l'écran
    SDL_Rect textPositionquitter = {x_position4, y_position4, 0, 0};
    SDL_BlitSurface(textSurfacequitter, NULL, screen, &textPositionquitter);

// IMAGE des paramètres en bas à droite
    SDL_Surface *parametre = IMG_Load("assets/parametre.jpg");
    if (!parametre)
    {
        fprintf(stderr, "Unable to load image: %s\n", IMG_GetError());
        TTF_CloseFont(font);
        SDL_FreeSurface(backgroundImage);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }
    int x_position5 = 1200; // par exemple, 100 pixels depuis la gauche de l'écran
    int y_position5 = 650;  // par exemple, 100 pixels depuis le haut de l'écran
    // Position du texte sur l'écran
    SDL_Rect parametrepos = {x_position5, y_position5, 0, 0};
    SDL_BlitSurface(parametre, NULL, screen, &parametrepos);

    //shop au milieu à gauche  
    SDL_Surface *shop = IMG_Load("assets/shop.jpg");
    if (!shop)
    {
        fprintf(stderr, "Unable to load image: %s\n", IMG_GetError());
        TTF_CloseFont(font);
        SDL_FreeSurface(backgroundImage);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }
    int x_position6 = 20; // par exemple, 100 pixels depuis la gauche de l'écran
    int y_position6 = 200;  // par exemple, 100 pixels depuis le haut de l'écran
    // Position du texte sur l'écran
    SDL_Rect shoppos = {x_position6, y_position6, 0, 0};
    SDL_BlitSurface(shop, NULL, screen, &shoppos);


    // Actualisation de l'écran
    SDL_Flip(screen);

    // Boucle principale
    bool running = true;
    SDL_Event event;
    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                running = false;
                break;
                // Ajouter ici la gestion des interactions avec les boutons
            }
        }
    }

    // Nettoyage
    SDL_FreeSurface(textSurfacesolo);
    SDL_FreeSurface(textSurfacemulti);
    SDL_FreeSurface(textSurfaceanarchie);
    SDL_FreeSurface(textSurfacequitter);
    SDL_FreeSurface(shop);
    SDL_FreeSurface(parametre);
    TTF_CloseFont(font);
    SDL_FreeSurface(backgroundImage);
    TTF_Quit();
    SDL_Quit();
    return 0;
}
