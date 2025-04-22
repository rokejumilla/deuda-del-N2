#include "Game.h"
#include <tchar.h>

int _tmain(int argc, _TCHAR* argv[]) {
    Game* juego = new Game(800, 600, "F_Ball - Ejercicio 3");
    juego->Loop();
    return 0;
}
