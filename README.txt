Les librairie SDL (1.2), sont TTF (2.0), SDL image (1.2):
sudo apt-get install libsdl1.2-dev libsdl-image1.2-dev libsdl-ttf2.0-dev

Pour la compilation:
gcc -o morpion morpion.c game.c -I/usr/include/SDL -lSDL -lSDL_image -lSDL_ttf -lm
