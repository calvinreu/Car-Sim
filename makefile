CC = g++

default: interface/graphic.cpp interface/graphic.hpp math.cpp math.hpp main.cpp
	$(CC) interface/graphic.cpp -c -lSDL2 -lSDL2_image -llog -o graphic.o
	$(CC) math.cpp -c -o math.o
	$(cc) car.cpp -c -o car.o
	$(CC) main.cpp graphic.o math.o car.o -pthread -lSDL2 -lSDL2_image -llog -o carsim.out

installation-rpm:
	sudo dnf install SDL2
	sudo dnf install SDL_image
	git clone https://github.com/calvinreu/logfile
	cd logfile
	sudo make
	cd ../

installation-deb:
	sudo apt install SDL2
	sudo apt install SDL_image
	git clone https://github.com/calvinreu/logfile
	cd logfile
	sudo make
	cd ../