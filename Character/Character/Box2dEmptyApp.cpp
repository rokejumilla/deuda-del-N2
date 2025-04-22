#include "Character.h"

int main() {
    Character* personaje = new Character(800, 600, "Ragdoll - MAVII");
    personaje->Loop();
    delete personaje;
    return 0;
}
