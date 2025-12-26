#include <SDL3/SDL.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("SDL Init Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow(
        "DSA Queue Simulator",
        800,
        600,
        0
    );

    if (!window)
    {
        printf("Window Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Event event;
    int running = 1;

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
            {
                running = 0;
            }
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
