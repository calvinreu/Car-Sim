#include "graphic.hpp"

using std::to_string;

const Uint32 min_frame_time = 1000/30;

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

void graphic::renderLoop(bool &renderer_running) {
    
    Uint32 start_time, frame_time;
        
    renderer_running = true;
    while (renderer_running) {
        start_time = SDL_GetTicks();
        SDL_Event event;

        while (0 != SDL_PollEvent(&event)){
            switch (event.type) {
            case SDL_MOUSEBUTTONDOWN:
                //do nothing
                break;
            case SDL_QUIT:
                renderer_running = false;
                return;
            }
        }

        newFrame();
        frame_time = SDL_GetTicks() - start_time;
        if(frame_time < min_frame_time)
            SDL_Delay(min_frame_time-frame_time);
    }
}

void graphic::newFrame(){
    SDL_SetRenderDrawColor(renderer, background::r, background::g, background::b, background::a);
    SDL_RenderClear(renderer);
    map_sRect.x = carPos->x - (width()/2);
    map_sRect.y = carPos->y - (height()/2);
    //log("set map sRect to| x:" + std::to_string(map_sRect.x) + " y:" + std::to_string(map_sRect.y) + " w:" + std::to_string(map_sRect.w) + " h:" + std::to_string(map_sRect.h));
    SDL_RenderCopy(renderer, map, &map_sRect, &map_dRect);
    SDL_RenderCopyEx(renderer, car, &car_sRect, &car_dRect, *car_angle, &carCenter, SDL_FLIP_NONE);
    SDL_RenderPresent(renderer);
}

graphic::graphic(const std::vector<SDL_Point> &map_info, const int &mWidth, const int &mHeight, const SDL_Point &car_position, const double &car_angle) : carPos(&car_position), car_angle(&car_angle)
{
    log("creating graphic instance");
    
    log("creating Window");
    window = SDL_CreateWindow("car sim", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP);
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
    
    log("init SDL IMG");
    if( !( IMG_Init( IMG_INIT_PNG ) & IMG_INIT_PNG ) )
    {
        log("ERROR SDL_image could not intitialize: " + SDL_StringError());
        return;
    }

    //Load image at specified path
    log("loading car surface from image");
    SDL_Surface* loadedSurface = IMG_Load("interface/res/car.png");
    if( loadedSurface == NULL )
        log( "ERROR Unable to load image: interface/res/car.png: " + SDL_StringError() );

    log("loading car from surface");
    //Create texture from surface pixels
    car = SDL_CreateTextureFromSurface( renderer, loadedSurface );
    if( car == NULL )
        log("ERROR Unable to create texture from surface: " + SDL_StringError());

    log("free surface");
    //Get rid of old loaded surface
    SDL_FreeSurface( loadedSurface );

    SDL_GetRendererOutputSize(renderer, &width(), &height());

    car_dRect.w = car_sRect.w;    
    car_dRect.h = car_sRect.h;
    car_dRect.x = (width ()/2)-car_dRect.w/2;
    car_dRect.y = (height()/2)-car_dRect.h/2;

    carCenter.x = car_sRect.w /2;
    carCenter.y = car_sRect.h /2;

    map_dRect.x = 0;
    map_dRect.y = 0;    

    map_sRect.w = width();
    map_sRect.h = height();

    log("set car center to| x:" + to_string(carCenter.x) + " y:" + to_string(carCenter.y));
    log("set car dRect to| x:" + std::to_string(car_dRect.x) + " y:" + std::to_string(car_dRect.y) + " w:" + std::to_string(car_dRect.w) + " h:" + std::to_string(car_dRect.h));
    log("set map dRect to| x:" + std::to_string(map_dRect.x) + " y:" + std::to_string(map_dRect.y) + " w:" + std::to_string(map_dRect.w) + " h:" + std::to_string(map_dRect.h));
    log("set map sRect to| w:" + std::to_string(map_sRect.w) + " h:" + std::to_string(map_sRect.h));

    log("creating map texture");
    log("creating blank texture");
    //Create uninitialized texture
    map = SDL_CreateTexture( renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, mWidth, mHeight);
    if( map == NULL )
        log("ERROR Unable to create blank texture: " + SDL_StringError());
    
    log("rendering map texture");
    if(SDL_SetRenderTarget(renderer, map) != 0)
        log("ERROR Unable to set map texture as render target");

    SDL_SetRenderDrawColor(renderer, background::r,background::g,background::b,background::a);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, objects::r,objects::g,objects::b,objects::a);

    SDL_RenderDrawLines(renderer, &(*map_info.begin()), map_info.size());

    if(SDL_SetRenderTarget(renderer, NULL) != 0)
        log("ERROR Unable to set window as render target");

}

graphic::~graphic() {
    SDL_DestroyTexture(map);
    SDL_DestroyTexture(car);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}
