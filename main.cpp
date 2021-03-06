#include "interface/graphic.hpp"
#include "math.hpp"
#include "car.hpp"
#include <log.hpp>
#include <iostream>
#include <mutex>

std::mutex mtx;

extern const size_t SENSOR_COUNT;

void start_graphic(const std::vector<SDL_Point> &map, const int &mapW, const int &mapH, pair &car_position, double &angle, bool &running) {

    log("init SDL");
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_EVENTS);
    log("creating graphics instance");
    std::unique_lock<std::mutex> lock(mtx);
    graphic gOut(map, mapW, mapH, car_position, angle);
    lock.unlock();
    gOut.renderLoop(running);
    log("quit SDL");
    SDL_Quit();
}

int main(int argc, char const *argv[])
{
    if(argc < 2) {
        std::cout << "to few arguments \n";
        return -1;
    }

    //load map from file
    std::ifstream mapload(argv[1], std::ifstream::binary);
    size_t mapVSize;
    int mapW, mapH;
    bool renderer_running;
    log("loading map from file: " + std::string(argv[1]));
    mapload.read((char*)(&mapW), sizeof(int));
    mapload.read((char*)(&mapH), sizeof(int));
    mapload.read((char*)(&mapVSize), sizeof(std::size_t));
    std::vector<SDL_Point> map(mapVSize);
    mapload.read((char*)(&(*map.begin())), sizeof(SDL_Point) * mapVSize);
    pair car_position = {.x = mapW/2, .y = mapH/2};
    double angle = 0;
    std::thread t_render(&start_graphic, map, mapW, mapH, std::ref(car_position), std::ref(angle), std::ref(renderer_running));

    double distance_buffer[7];

    sensornet sensor(angle, map, car_position, distance_buffer);    

    Uint32 start_time;
    renderer_running =true;
    while(renderer_running){
        start_time = SDL_GetTicks();
        logfile::log(std::to_string(sensor.refresh()));

        if(SDL_GetTicks() - start_time < 1000){
            SDL_Delay(1000-(SDL_GetTicks()-start_time));
        }
    }

    t_render.join();


    return 0;
}
