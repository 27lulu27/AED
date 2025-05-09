#ifndef AIRLINE_H
#define AIRLINE_H

#include <iostream>
#include <string>
using namespace std;

class Airline{
    private:
        string code, name, callsign, country;
    public:
        Airline();
        /**
         * @brief Construtor do objeto Airline
         * @param code = codigo da companhia
         * @param name = nome da companhia
         * @param callsign = abreviatura da mesma
         * @param country = país de origem da companhia
         */
        Airline(string code, string name, string callsign, string country);
        string getCode() const;
        string getName() const;
        string getCallsign() const;
        string getCountry() const;
};

#endif
