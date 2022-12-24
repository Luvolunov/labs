// Variant 3
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_image/SDL_image.h>

// Определяем константы для размеров окна
const int windowWidth = 800;
const int windowHeight = 600;

// Размер клетки
int size = 50;

// Метод для расчёта размера клетки на графике
int calculateSize(float minX, float maxX) {
    float absMin = abs(minX);
    float absMax = abs(maxX);
    int maxLength = absMin > absMax ? absMin : absMin;
    return windowWidth / (2 * (maxLength + 1));
}
// Метод для проверки вещественных чисел на равенство
inline bool isEqual(double x, double y) {
  const double epsilon = 1e-5;
  return fabs(x - y) < epsilon;
}
// Метод для рендера текста
void renderText(SDL_Renderer* renderer, TTF_Font* font, SDL_Color color, const std::string &text, SDL_Rect rect) {
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, text.c_str(), color);
    SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    SDL_RenderCopy(renderer, message, NULL, &rect);
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(message);
}
// Метод для рисования координатной плоскости
void drawCoordinatePlane(SDL_Renderer *renderer) {
    // Инициализируем шрифт, цвет и плоскость для текста
    TTF_Font* Roboto = TTF_OpenFont("assets/Roboto-Light.ttf", 12);
    SDL_Color Black = {0, 0, 0};
    SDL_Rect message_rect;
    message_rect.w = 7;
    message_rect.h = 15;
    
    SDL_SetRenderDrawColor(renderer, 0x55, 0x55, 0x55, 0x55);
    SDL_RenderDrawLine(renderer, windowWidth / 2, 0, windowWidth / 2, windowHeight);
    SDL_RenderDrawLine(renderer, 0, windowHeight / 2, windowWidth, windowHeight / 2);
    
    // Рисуем начало координатной плоскости 0
    message_rect.x = windowWidth / 2 + 4;
    message_rect.y = windowHeight / 2 + 4;
    renderText(renderer, Roboto, Black, std::to_string(0), message_rect);
    
    int y = 0;
    for (float i = windowHeight / 2; i > 0; i -= size) {
        float textX = windowWidth / 2;
        float textY = i;
        if (y) {
            // Рисуем числа по оси Y вверх
            message_rect.x = textX + 6;
            message_rect.y = textY - 8;
            renderText(renderer, Roboto, Black, std::to_string(y), message_rect);
            
            // Рисуем числа по оси Y вниз
            message_rect.x = windowWidth - textX + 6;
            message_rect.y = windowHeight - textY - 8;
            renderText(renderer, Roboto, Black, std::to_string(y), message_rect);
        }
        ++y;
        // Рисуем деления на оси Y
        SDL_RenderDrawLine(renderer, windowWidth / 2 - 2, i, windowWidth / 2 + 2, i);
        SDL_RenderDrawLine(renderer, windowWidth / 2 - 2, windowHeight - i, windowWidth / 2 + 2, windowHeight - i);
    }
    
    int x = 0;
    for (float i = windowWidth / 2; i > 0; i -= size) {
        float textX = i;
        float textY = windowHeight / 2;
        if (x) {
            // Рисуем числа по оси X слева
            message_rect.x = textX - 4;
            message_rect.y = textY + 6;
            renderText(renderer, Roboto, Black, std::to_string(x), message_rect);
            
            // Рисуем числа по оси X справа
            message_rect.x = windowWidth - textX - 4;
            message_rect.y = windowHeight - textY + 6;
            renderText(renderer, Roboto, Black, std::to_string(x), message_rect);
        }
        ++x;
        // Рисуем деления на оси X
        SDL_RenderDrawLine(renderer, i, windowHeight / 2 - 2, i, windowHeight / 2 + 2);
        SDL_RenderDrawLine(renderer, windowWidth - i, windowHeight / 2 - 2, windowWidth - i, windowHeight / 2 + 2);
    }

    TTF_CloseFont(Roboto);
}

int main(int argc, char *argv[]) {
    float minX, maxX;
    std::cout << "Введите минимальный x: ";
    std::cin >> minX;
    std::cout << "\nВведите максимальный x: ";
    std::cin >> maxX;
    // Очерёдность инициализации взята из методички
    if (SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr,"Ошибка в SDL_Init: %s\n", SDL_GetError());
        return 1;
    }
    if (TTF_Init()) {
        fprintf(stderr,"Ошибка в SDL_ttf");
        return 1;
    }
    // Убрал функции в конце, оставил только atexit
    atexit(TTF_Quit);
    atexit(IMG_Quit);
    atexit(SDL_Quit);
    SDL_Window *screen;
    screen = SDL_CreateWindow("Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(screen, -1, 0);
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);
    size = calculateSize(minX, maxX);
    drawCoordinatePlane(renderer);
    
    float x0 = windowWidth / 2;
    float y0 = windowHeight / 2;
    
    float x1 = minX;
    float y1 = 5 / (x1 * x1);
    
    // Цикл для отрисовки графика по точкам на расстоянии 0.2
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
    for (float x2 = x1; x2 <= maxX; x2 += 0.2) {
        if (isEqual(x2, 0.0)) continue; // Условие для исключения x2 = 0 из Области Допустимых Значений
        float y2 = 5 / (x2 * x2);
        SDL_RenderDrawLine(renderer, (x1 * size) + x0, -(y1 * size) + y0, (x2 * size) + x0, -(y2 * size) + y0);
        x1 = x2;
        y1 = y2;
    }
    
    SDL_RenderPresent(renderer);
    
    SDL_Event e;
    bool quit = false;
    while(quit == false) {
        while (SDL_PollEvent(&e)) { if(e.type == SDL_QUIT) quit = true; }
        
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(screen);

    return 0;
}
