#include <iostream>
#include "Menu.h"
int main() {
    /**
     * @brief Cria uma instância do Menu
     */
    Menu menu;
    /**
     * @brief Cria uma instância de System
     */
    System system;
    /**
     * @brief Inicia o menu passando a instância de System
     */
    menu.start(system);
    return 0;
}
