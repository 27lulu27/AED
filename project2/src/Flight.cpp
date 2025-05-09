#include "Flight.h"




string Flight::getTarget(){
    return target;
}

Airline Flight::getAirline(){
    return airline;
}

Flight::Flight(Airline airline, string target) : airline(airline), target(target) {}


