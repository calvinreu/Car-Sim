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

struct line
{
    int x_beg, y_beg, x_end, y_end;
};

class ui
{
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
public:
    std::vector<SDL_Point> lines;
    void NewFrame() const {
        SDL_SetRenderDrawColor(renderer, background::r, background::g, background::b, background::a);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, objects::r, objects::g, objects::b, objects::a);
        SDL_RenderDrawLines(renderer, &(*lines.begin()), lines.size());
        SDL_RenderPresent(renderer);
    }
    //Handles events and pushes frames if certain events happen returns false on SDL_QUIT
    bool refresh();
    ui();
    ~ui();
};

ui::ui()
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

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

    while (0 != SDL_PollEvent(&event))
    {
        switch(event.type) {
        case SDL_MOUSEBUTTONDOWN:
            SDL_GetMouseState(&MousePosition.x, &MousePosition.y);
            lines.push_back(MousePosition);
            NewFrame();
            SDL_Delay(min_click_cooldown);//avoid multiple points with one click
            break;
        case SDL_QUIT:
            return false;
        }
    }

    return true;
}
