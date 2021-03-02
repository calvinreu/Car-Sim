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
    saveFile.write((char*)(&temp), sizeof(std::size_t));
    saveFile.write((char*)(&(*UI.lines.begin())), sizeof(SDL_Point)*temp);

    return 0;
}
