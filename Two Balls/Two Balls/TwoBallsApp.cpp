#include "TwoBallsGame.h"

int main() {
    TwoBallsGame* juego = new TwoBallsGame(800, 600, "Two Balls - MAVII");
    juego->Loop();
    delete juego;
    return 0;
}
