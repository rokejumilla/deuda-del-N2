#include "Game.h"

int main() {
    Game* juego = new Game(800, 600, "Ball - MAVII");
    juego->Loop();
    return 0;
}
