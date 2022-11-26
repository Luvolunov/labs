#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

const int windowWidth = 800;
const int windowHeight = 600;

const int maxSize = 500;
const int minSize = 100;

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr,"Ошибка в SDL_Init: %s\n", SDL_GetError());
        return 1;
    }
    atexit(SDL_Quit);
    SDL_Window *screen;
    screen = SDL_CreateWindow("Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(screen, -1, 0);
    SDL_Surface *imageSurface = IMG_Load("assets/snow.png");
    SDL_Texture *image = SDL_CreateTextureFromSurface(renderer, imageSurface);
    SDL_FreeSurface(imageSurface);
    
    SDL_Event e;
    bool quit = false;
    bool isGrowing = true;
    int width = minSize;
    int height = minSize;
    while(quit == false) {
        while (SDL_PollEvent(&e)) { if((e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) || e.type == SDL_QUIT) quit = true; }
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);
        
        width += isGrowing ? 1 : -1;
        height += isGrowing ? 1 : -1;
        
        if (width > maxSize) {
            isGrowing = false;
        } else if (width < minSize) {
            isGrowing = true;
        }
        
        SDL_Rect box = { (windowWidth - width) / 2, (windowHeight - height) / 2, width, height };
        
        SDL_RenderCopy(renderer, image, NULL, &box);
        
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(screen);
    SDL_Quit();
    IMG_Quit();
    return 0;
}
