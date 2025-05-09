#ifndef FLIGHT_H
#define FLIGHT_H

#include <iostream>
#include <string>
#include "Airline.h"
using namespace std;

class Flight{
    private:
        string target;
        Airline airline;
    public:
        /**
         * @brief Construtor da classe voo que no nosso grafo funciona como uma aresta
         * @param airline = companhia aerea responsavel pelo voo
         * @param target = aeroporto de destino
         */
        Flight(Airline airline, string target);
        string getTarget();
        Airline getAirline();
};

#endif