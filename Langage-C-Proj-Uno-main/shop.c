#include "shop.h"
#include <SDL/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL/SDL_image.h>

typedef struct {
    SDL_Rect position;
    SDL_Surface* imageNormal;
    SDL_Surface* imageHover;
    bool isHovered;
} Button;

static SDL_Surface* backgroundSurface = NULL;
static Button buttons[4];

SDL_Surface* loadAndResizeImage(const char* path, int width, int height) {
    SDL_Surface* loadedSurface = IMG_Load(path);
    if (!loadedSurface) {
        printf("Unable to load image %s! SDL Error: %s\n", path, SDL_GetError());
        return NULL;
    }

    SDL_Surface* optimizedSurface = SDL_DisplayFormatAlpha(loadedSurface);
    SDL_FreeSurface(loadedSurface);
    
    SDL_Surface* resizedSurface = SDL_CreateRGBSurface(SDL_SWSURFACE, width, height, optimizedSurface->format->BitsPerPixel,
                                                       optimizedSurface->format->Rmask, optimizedSurface->format->Gmask,
                                                       optimizedSurface->format->Bmask, optimizedSurface->format->Amask);
    
    if (resizedSurface) {
        SDL_SoftStretch(optimizedSurface, NULL, resizedSurface, NULL); 
    }
    
    SDL_FreeSurface(optimizedSurface);
    
    return resizedSurface; // Retourne la nouvelle surface redimensionnée
}


static void initButtons(SDL_Surface* screen) {
    int buttonWidth = 200;
    int buttonHeight = 100;
    int buttonSpacing = 85;
    int totalButtonsWidth = (buttonWidth * 4) + (buttonSpacing * 3);
    int startX = (screen->w - totalButtonsWidth) / 2;
    int startY = (screen->h - buttonHeight) / 2;

    for (int i = 0; i < 4; ++i) {
        buttons[i].position.x = startX + i * (buttonWidth + buttonSpacing);
        buttons[i].position.y = startY;
        buttons[i].position.w = buttonWidth;
        buttons[i].position.h = buttonHeight;
        
        char imagePathNormal[255];
        char imagePathHover[255];
        sprintf(imagePathNormal, "assets/button%d.PNG", i + 1);
        sprintf(imagePathHover, "assets/button%d_hover.png", i + 1);

        buttons[i].imageNormal = loadAndResizeImage(imagePathNormal, buttonWidth, buttonHeight);
        buttons[i].imageHover = loadAndResizeImage(imagePathHover, buttonWidth, buttonHeight);
        buttons[i].isHovered = false;
    }
}

static void renderButtons(SDL_Surface* screen) {
    for (int i = 0; i < 4; ++i) {
        SDL_BlitSurface(buttons[i].isHovered ? buttons[i].imageHover : buttons[i].imageNormal,
                        NULL, screen, &buttons[i].position);
    }
}

static void handleButtonEvents(SDL_Event* event) {
    int mouseX, mouseY;
    switch (event->type) {
        case SDL_MOUSEMOTION:
            mouseX = event->motion.x;
            mouseY = event->motion.y;
            for (int i = 0; i < 4; ++i) {
                buttons[i].isHovered = (mouseX >= buttons[i].position.x &&
                                        mouseX < buttons[i].position.x + buttons[i].position.w &&
                                        mouseY >= buttons[i].position.y &&
                                        mouseY < buttons[i].position.y + buttons[i].position.h);
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (event->button.button == SDL_BUTTON_LEFT) {
                mouseX = event->button.x;
                mouseY = event->button.y;
                for (int i = 0; i < 4; ++i) {
                    if (mouseX >= buttons[i].position.x &&
                        mouseX < buttons[i].position.x + buttons[i].position.w &&
                        mouseY >= buttons[i].position.y &&
                        mouseY < buttons[i].position.y + buttons[i].position.h) {
                        printf("Button %d clicked\n", i + 1);
                    }
                }
            }
            break;
    }
}

void closeShop() {
    if (backgroundSurface != NULL) {
        SDL_FreeSurface(backgroundSurface);
        backgroundSurface = NULL;
    }
    for (int i = 0; i < 4; ++i) {
        SDL_FreeSurface(buttons[i].imageNormal);
        SDL_FreeSurface(buttons[i].imageHover);
    }
}

void shop(SDL_Surface* screen) {
    backgroundSurface = loadAndResizeImage("assets/shopback.jpg", screen->w, screen->h);
    if (backgroundSurface == NULL) {
        fprintf(stderr, "Failed to load and resize shop background image!\n");
        return;
    }

    initButtons(screen);

    bool shopRunning = true;
    SDL_Event event;
    while (shopRunning) {
    while (SDL_PollEvent(&event) != 0) {
        handleButtonEvents(&event); // Ici, on ne passe plus 'screen' comme argument
        if (event.type == SDL_QUIT) {
            shopRunning = false;
        }
    }

        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
        SDL_BlitSurface(backgroundSurface, NULL, screen, NULL);
        renderButtons(screen);
        SDL_Flip(screen);
    }

    closeShop();
}
