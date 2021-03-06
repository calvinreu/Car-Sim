#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <list>
#include <vector>
#include <log.hpp>
#include <thread>
#include <iostream>
#include <mutex>
#include "../math.hpp"

using logfile::log;
using logfile::SDL_StringError;

constexpr SDL_Rect car_sRect = {.x = 0, .y = 0, .w = 90, .h = 200};

//graphic output instance does not manage any logic like collision
class graphic
{
private:
    SDL_Texture*  car      = NULL;
    SDL_Texture*  map      = NULL;
    SDL_Window*   window   = NULL;
    SDL_Renderer* renderer = NULL;
    pair* carPos;//Position of car and center of map
    SDL_Rect car_dRect;
    SDL_Rect map_sRect;
    SDL_Rect map_dRect;

    SDL_Point carCenter;
    double* car_angle;

    int& width()  {return map_dRect.w;}
    int& height() {return map_dRect.h;}
    void newFrame();
public:
    /**
     * @param renderer_running bool which tells the renderer if it is running on SDL_QUIT the render loop will set it to false and quit
     * @brief start a rendering loop
    **/ 
    void renderLoop(bool &renderer_running);

    const int& width()  const {return map_dRect.w;}
    const int& height() const {return map_dRect.h;}

    /**
     * @param map collection of lines which make up the map
     * @param mWidth is the width of the map
     * @param mHeight is the height of the map
     * @param car_position the coordinates of the car
     * @brief create a graphics instance with initialized map
    **/
    graphic(const std::vector<SDL_Point> &map, const int &mWidth, const int &mHeight, pair &car_position, double &car_angle);
    ~graphic();
};



