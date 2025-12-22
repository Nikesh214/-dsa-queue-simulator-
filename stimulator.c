#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define RECT_WIDTH 100
#define RECT_HEIGHT 80
#define SPEED 5

int main(int argc, char* argv[]) {
    (void)argc;
    (void)argv;

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Event event;
    bool running = true;

    /* Rectangle position */
    int rectX = 350;
    int rectY = 260;

    /* Initialize SDL2 */
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        return 1;
    }

    /* Create window */
    window = SDL_CreateWindow(
        "SDL2 Simulator - Arrow keys to move, ESC to Quit",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN
    );

    if (!window) {
        SDL_Log("Window creation failed: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    /* Create renderer */
    renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if (!renderer) {
        SDL_Log("Renderer creation failed: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    /* Main loop */
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                running = false;

            /* Keyboard input */
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        running = false;
                        break;
                    case SDLK_LEFT:
                        rectX -= SPEED;
                        if (rectX < 0) rectX = 0;
                        break;
                    case SDLK_RIGHT:
                        rectX += SPEED;
                        if (rectX + RECT_WIDTH > WINDOW_WIDTH) rectX = WINDOW_WIDTH - RECT_WIDTH;
                        break;
                    case SDLK_UP:
                        rectY -= SPEED;
                        if (rectY < 0) rectY = 0;
                        break;
                    case SDLK_DOWN:
                        rectY += SPEED;
                        if (rectY + RECT_HEIGHT > WINDOW_HEIGHT) rectY = WINDOW_HEIGHT - RECT_HEIGHT;
                        break;
                }
            }
        }

        /* Clear background */
        SDL_SetRenderDrawColor(renderer, 230, 230, 230, 255);
        SDL_RenderClear(renderer);

        /* Draw rectangle */
        SDL_Rect box = {rectX, rectY, RECT_WIDTH, RECT_HEIGHT};
        SDL_SetRenderDrawColor(renderer, 0, 120, 255, 255);
        SDL_RenderFillRect(renderer, &box);

        SDL_RenderPresent(renderer);
        SDL_Delay(16); /* ~60 FPS */
    }

    /* Cleanup */
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
