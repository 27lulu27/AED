#include <iostream>
#include "../include/Menu.h"
#include "../include/System.h"

int main() {
    Menu menu; // Crie uma instância de Menu
    System system; // Crie uma instância de System
    menu.start(system); // Inicie o menu passando a instância de System
    return 0;
}
