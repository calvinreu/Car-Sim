#include <log.hpp>
#include <iostream>
#include <fstream>
#include "ui.hpp"

using logfile::log;

const size_t size_multiplier = 5;

int main(int argc, char const *argv[])
{
    if(argc < 2) {
        log("to few arguments");
        std::cout << "to few arguments \n";
        return -1;
    }

    ui UI;

    UI.NewFrame();
    while (UI.refresh()){}

    std::ofstream saveFile(argv[1], std::ofstream::binary | std::ofstream::trunc);
    log("writing to: " + std::string(argv[1]));

    size_t temp = UI.lines.size();
    int tempA[2];
    SDL_GetRendererOutputSize(UI.renderer, tempA, tempA+1);

    tempA[0] *= size_multiplier;
    tempA[1] *= size_multiplier;

    for(auto i = UI.lines.begin(); i < UI.lines.end(); i++){
        i->x *= size_multiplier;
        i->y *= size_multiplier;
    }

    saveFile.write((char*)(tempA), sizeof(int)*2);
    saveFile.write((char*)(&temp), sizeof(std::size_t));
    saveFile.write((char*)(&(*UI.lines.begin())), sizeof(SDL_Point)*temp);

    return 0;
}
