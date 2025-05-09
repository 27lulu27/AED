
#ifndef PROJETOAED2_SYSTEM_H
#define PROJETOAED2_SYSTEM_H
#include "Airline.h"
#include "Airport.h"
#include "Flight.h"
#include "Graph.h"
#include <iostream>
#include <unordered_map>

using namespace std;
class System{
private:
    graph g;
    int flights = 0;                                        //quantidade de voos
    unordered_map<std::string, Airport> airportsMap;        //usado para facilitar o parsing
    unordered_map<std::string, Airline> airlinesMap;
public:
    /**
     * @brief O construtor faz 3 chamadas, cada uma faz o parsing da informação dos ficheiros fornecidos
     */
    System();
    /**
     * @brief Faz o parsing das companhias aereas
     * @param filename = nome do ficheiro
     */
    void readAirlines(const string &filename);
    /**
     * @brief Faz o parsing dos aeroportos
     * @param filename = nome do ficheiro
     */
    void readAirports(const string &filename);
    /**
     * @brief Faz o parsing dos voos entre aeroportos
     * @param filename = nome do ficheiro
     */
    void readFlights(const string &filename);

    void FastConnection(const string& source, const string& dest);

    void showgraph();

    void NumberofAandF();

    void NumberofFofAir(string code);

    void FastConnectionCity(const std::string &source, const std::string &dest);

    void NumberofFofCity(string city);

    void NumberofFofAirline(string airlinecode);

    void NumberofDContriesairport(string code);

    void NumberofDContriescity(string city);

    void avaliabledestinations(string code, int num);

    void reachabledestinationsmax(string code, int max, int num);

    void maxdistance();

    void topairports(int k);

    void essentialairports();

    void FastConnectionCord(string source, double lat, double lon);
};
#endif //PROJETOAED2_SYSTEM_H
