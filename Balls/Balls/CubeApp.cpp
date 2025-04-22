#include "Cube.h"
#include <tchar.h>

int _tmain(int argc, _TCHAR* argv[])
{
    Cube* juego = new Cube(800, 600, "Cube - Ejercicio 4");
    juego->Loop();
    return 0;
}
