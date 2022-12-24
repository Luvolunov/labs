// Variant 3
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

// Константы с размерами окна
const int windowWidth = 800;
const int windowHeight = 600;

// Константы с максимальным и минимальным размером снежинки
const int maxSize = 500;
const int minSize = 100;

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr,"Ошибка в SDL_Init: %s\n", SDL_GetError());
        return 1;
    }
    atexit(IMG_Quit);
    atexit(SDL_Quit);
    SDL_Window *screen;
    screen = SDL_CreateWindow("Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(screen, -1, 0);
    SDL_Surface *imageSurface = IMG_Load("assets/snow.png");
    SDL_Texture *image = SDL_CreateTextureFromSurface(renderer, imageSurface);
    SDL_FreeSurface(imageSurface);
    
    SDL_Event e;
    bool quit = false;
    bool isGrowing = true; // Переменная, которая отвечает за то, увеличивается или уменьшается снежинка
    int width = minSize;
    int height = minSize;
    while(quit == false) {
        while (SDL_PollEvent(&e)) { if((e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) || e.type == SDL_QUIT) quit = true; }
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);
        // Либо увеличиваем, либо уменьшаем в зависимости от isGrowing
        width += isGrowing ? 1 : -1;
        height += isGrowing ? 1 : -1;
        
        if (width > maxSize) { // Если размер снежинки превысил максимальный, то вывставляем false, чтобы снежинка уменьшалась
            isGrowing = false;
        } else if (width < minSize) { // Если размер снежинки меньше минимального, то true, чтобы снежинка увеличивалась
            isGrowing = true;
        }
        
        SDL_Rect box = { (windowWidth - width) / 2, (windowHeight - height) / 2, width, height };
        
        SDL_RenderCopy(renderer, image, NULL, &box);
        // Отрисовываем изменения снежинки прямо в цикле, т.к. изменения каждую итерацию в отличие от графика
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(screen);
    return 0;
}
