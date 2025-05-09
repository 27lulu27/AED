#ifndef _AIRPORT_H
#define _AIRPORT_H

#include <iostream>
#include <list>
#include <vector>
#include "Flight.h"

class Flight;

using namespace std;

class Airport{
    private:
        string code, name, city, country;
        double latitude, longitude;
        bool visited, processed;
        int numberofflights = 0;
        int index;
public:
    /**
     * @brief vetor que contem todos os voos adjacentes (arestas) que saem deste aeroporto (nó)
     */
    vector<Flight> adj;
        Airport();
        /**
         * @brief construtor da classes aeroporto que funciona como um nó no nosso grafo
         * @param code = codigo do aeroporto
         * @param name = nome do aeroporto
         * @param city = cidade da localização do mesmo
         * @param country = país onde essa cidade está situada
         * @param latitude = primeira coordenada geográfica do mesmo
         * @param longitude = segunda coordenada geográfica do mesmo
         */
        Airport(string code, string name, string city, string country, double latitude, double longitude);
        string getCode() const;
        string getName() const;
        string getCity() const;
        string getCountry() const;
        double getLatitude() const;
        double getLongitude() const;
        vector<Flight> getAdj() const;
        /**
         * @brief Adiciona um voo ao vetor adj de modo a que este faça parte do aeroporto em questão
         * @param airline = companhia aerea que realiza o voo
         * @param target = aeroporto de destino
         */
        void addFlight(Airline airline, string target);
        void setvisited(const bool v);
        bool isvisited();
        int getNumberOfFlights();
        bool isProcessed();
        void setProcessed(const bool k);
        int getIndex() const;
        void setIndex(int newIndex);
};

#endif
