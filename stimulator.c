#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define RECT_WIDTH 100
#define RECT_HEIGHT 80
#define SPEED 300.0f   /* pixels per second */

int main(int argc, char* argv[]) {
    (void)argc;
    (void)argv;

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Event event;
    bool running = true;

    int winWidth = WINDOW_WIDTH;
    int winHeight = WINDOW_HEIGHT;

    /* Rectangle position */
    float rectX = 350.0f;
    float rectY = 260.0f;

    Uint32 lastTick = 0;

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
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
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

    lastTick = SDL_GetTicks();

    /* Main loop */
    while (running) {
        Uint32 currentTick = SDL_GetTicks();
        float deltaTime = (currentTick - lastTick) / 1000.0f;
        lastTick = currentTick;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                running = false;

            if (event.type == SDL_WINDOWEVENT &&
                event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                winWidth = event.window.data1;
                winHeight = event.window.data2;
            }

            if (event.type == SDL_KEYDOWN &&
                event.key.keysym.sym == SDLK_ESCAPE) {
                running = false;
            }
        }

        /* Keyboard state for smooth movement */
        const Uint8* state = SDL_GetKeyboardState(NULL);

        if (state[SDL_SCANCODE_LEFT])
            rectX -= SPEED * deltaTime;
        if (state[SDL_SCANCODE_RIGHT])
            rectX += SPEED * deltaTime;
        if (state[SDL_SCANCODE_UP])
            rectY -= SPEED * deltaTime;
        if (state[SDL_SCANCODE_DOWN])
            rectY += SPEED * deltaTime;

        /* Clamp to window */
        if (rectX < 0) rectX = 0;
        if (rectY < 0) rectY = 0;
        if (rectX + RECT_WIDTH > winWidth)
            rectX = winWidth - RECT_WIDTH;
        if (rectY + RECT_HEIGHT > winHeight)
            rectY = winHeight - RECT_HEIGHT;

        /* Clear background */
        SDL_SetRenderDrawColor(renderer, 230, 230, 230, 255);
        SDL_RenderClear(renderer);

        /* Draw rectangle */
        SDL_Rect box = {
            (int)rectX,
            (int)rectY,
            RECT_WIDTH,
            RECT_HEIGHT
        };

        SDL_SetRenderDrawColor(renderer, 0, 120, 255, 255);
        SDL_RenderFillRect(renderer, &box);

        SDL_RenderPresent(renderer);
    }

    /* Cleanup */
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
