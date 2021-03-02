#include "interface/graphic.hpp"
#include <log.hpp>
#include <iostream>


int main(int argc, char const *argv[])
{
    if(argc < 2) {
        std::cout << "to few arguments \n";
        return -1;
    }

    std::ifstream mapload(argv[1], std::ifstream::binary);
    size_t mapVSize, mapW, mapH;
    
    mapload.read((char*)(&mapVSize), sizeof(std::size_t));

    std::vector<SDL_Point> map(mapVSize);
    
    mapload.read((char*)(&(*map.begin())), sizeof(SDL_Point) * mapVSize);

    SDL_Point car_position = {.x = 960, .y = 540};
    double angle = 0;
    log("init SDL");
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    log("creating graphics instance");
    graphic gOut(map, 1920, 1080, car_position, angle);
    gOut.newFrame();
    SDL_Delay(1000);

    log("quit SDL");
    SDL_Quit();
    return 0;
}
