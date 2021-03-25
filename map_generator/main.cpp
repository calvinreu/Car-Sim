#include <log.hpp>
#include <iostream>
#include <fstream>
#include "ui.hpp"

using logfile::log;

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
    int tempA[4] = {0, 0, 1000000, 1000000};
    
    for(auto i = UI.lines.begin(); i < UI.lines.end(); i++) {
        if(tempA[0] > i->x)
            tempA[0] = i->x;
        if(tempA[1] > i->y)
            tempA[1] = i->y;
        if(tempA[2] < i->x)
            tempA[2] = i->x;
        if(tempA[3] < i->y)
            tempA[3] = i->y;
    }

    tempA[0] = tempA[2] - tempA[0];
    tempA[1] = tempA[3] - tempA[3];

    saveFile.write((char*)(tempA), sizeof(int)*2);
    saveFile.write((char*)(&temp), sizeof(std::size_t));
    saveFile.write((char*)(&(*UI.lines.begin())), sizeof(SDL_Point)*temp);

    return 0;
}
