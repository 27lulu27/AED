#include "Airline.h"

Airline::Airline(){}

Airline::Airline(string code, string name, string callsign, string country):
                 code(code), name(name), callsign(callsign), country(country){}


string Airline::getCode() const{
    return code;
}

string Airline::getName() const{
    return name;
}

string Airline::getCallsign() const{
    return callsign;
}

string Airline::getCountry() const{
    return country;
}