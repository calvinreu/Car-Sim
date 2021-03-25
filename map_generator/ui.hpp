#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include <log.hpp>

using logfile::log;
using logfile::SDL_StringError;

const Uint32 min_click_cooldown = 150;

namespace background{
    const Uint8 r = 255;
    const Uint8 g = 255;
    const Uint8 b = 255;
    const Uint8 a = 255;
}

namespace objects{
    const Uint8 r = 0;
    const Uint8 g = 0;
    const Uint8 b = 0;
    const Uint8 a = 255;
}

class ui
{
private:
    SDL_Window* window;
    SDL_Rect dRect;
    int posX = 0;
    int posY = 0;
    int size[4] = {0, 0, 1, 1};
public:
    SDL_Renderer* renderer;
    std::vector<SDL_Point> lines;
    int screenW, screenH;
    void NewFrame() const {
        SDL_Texture *tempTexture = SDL_CreateTexture(renderer, 0, SDL_TEXTUREACCESS_TARGET, (size[2]-size[0])*screenW, (size[3]-size[1])*screenH);
        SDL_SetRenderTarget(renderer, tempTexture);
        SDL_SetRenderDrawColor(renderer, background::r, background::g, background::b, background::a);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, objects::r, objects::g, objects::b, objects::a);
        SDL_RenderDrawLines(renderer, &(*lines.begin()), lines.size());
        SDL_Rect sRect = {.x = posX*screenW, .y = posY*screenH, .w = screenW, .h = screenH};
        SDL_SetRenderTarget(renderer, NULL);
        SDL_SetRenderDrawColor(renderer, background::r, background::g, background::b, background::a);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, tempTexture, &sRect, &dRect);

        SDL_RenderPresent(renderer);
    }
    //Handles events and pushes frames if certain events happen returns false on SDL_QUIT
    bool refresh();
    ui();
    ~ui();
};

ui::ui()
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER);

    log("creating Window");
    window = SDL_CreateWindow("car sim map draw", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP);
    if(window == NULL){
        log("ERROR Unabe to create window: " + SDL_StringError());
        return;
    }
    log("creating renderer");
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == NULL) {
        log("ERROR Unable to create renderer: " + SDL_StringError());
        return;
    }

    SDL_GetRendererOutputSize(renderer, &screenW, &screenH);
    dRect = {.x = 0, .y = 0, .w = screenW, .h = screenH};

}

ui::~ui()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

bool ui::refresh() {
    SDL_Event event;
    SDL_Point MousePosition;

    const Uint8 *keyboard;

    Uint32 start = SDL_GetTicks();

    while (0 != SDL_PollEvent(&event))
    {
        switch(event.type) {
        case SDL_MOUSEBUTTONDOWN:
            SDL_GetMouseState(&MousePosition.x, &MousePosition.y);
            MousePosition.x += posX*screenW;
            MousePosition.y += posY*screenH;
            lines.push_back(MousePosition);
            SDL_Delay(min_click_cooldown);//avoid multiple points with one click
            NewFrame();
            break;
        case SDL_QUIT:
            return false;
        }
    }

    keyboard = SDL_GetKeyboardState(NULL);

    if(keyboard[SDL_SCANCODE_LEFT]){
        posX--;
        if(posX < size[0])
            size[0] = posX;
    }
    if(keyboard[SDL_SCANCODE_RIGHT]){
        posX++;
        if(posX > size[2])
            size[2] = posX=1;
    }
    if(keyboard[SDL_SCANCODE_UP]){
        posY--;
        if(posY < size[1])
            size[1] = posY;
    }
    if(keyboard[SDL_SCANCODE_DOWN]){
        posY++;
        if(posY > size[3])
            size[3] = posY+1;
    }

    NewFrame();
    if(SDL_GetTicks() - start < 30)
        SDL_Delay(30-(SDL_GetTicks()-start));

    return true;
}
