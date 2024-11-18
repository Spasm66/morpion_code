SDL (1.2), TTF (2.0) and SDL image (1.2) libraries are required:
sudo apt-get install libsdl1.2-dev libsdl-image1.2-dev libsdl-ttf2.0-dev

for compilation:
gcc -o morpion morpion.c game.c -I/usr/include/SDL -lSDL -lSDL_image -lSDL_ttf -lm
