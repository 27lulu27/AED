#include <fstream>
#include <sstream>
#include "System.h"

System::System() {
    readAirlines("C:\\Users\\gluca\\Projeto-AED-2\\data\\airlines.csv");
    readAirports("C:\\Users\\gluca\\Projeto-AED-2\\data\\airports.csv");
    readFlights("C:\\Users\\gluca\\Projeto-AED-2\\data\\flights.csv");
}

void System::readAirlines(const std::string& filename) {
    ifstream file(filename);
    string line;
    std::getline(file, line); // Ignora a primeira linha (cabeçalho)

    if (!file.is_open()) {
        cerr << "Erro ao abrir o arquivo: " << filename << endl;
        return;
    }
    while (getline(file, line)) {
        istringstream s(line);
        string code, name, callsign, country;
        if (getline(s, code, ',') && getline(s, name, ',') &&
        getline(s, callsign, ',') && getline(s, country, ',')) {
            Airline airline(code, name, callsign, country);
            airlinesMap[code] = airline;
        }
    }
    file.close();
}

void System::readAirports(const std::string& filename) {
    ifstream file2(filename);
    string line;
    std::getline(file2, line); // Ignora a primeira linha (cabeçalho)
    if (!file2.is_open()) {
        cerr << "Erro ao abrir o arquivo: " << filename << endl;
        return;
    }

    while (getline(file2, line)) {
        istringstream s(line);
        string code, name, city, country;
        double latitude, longitude;
        char comma;
        if (getline(s, code, ',') && getline(s, name, ',') &&
        getline(s, city, ',') && getline(s, country, ',') &&
            s >> latitude >> comma && s >> longitude) {
            Airport airport(code, name, city, country, latitude, longitude);
            airportsMap[code] = airport;
        }
    }

    file2.close();
}

void System::readFlights(const std::string& filename) {
    ifstream file(filename);
    string line;
    std::getline(file, line); // Ignora a primeira linha (cabeçalho)
    if (!file.is_open()) {
        cerr << "Erro ao abrir o arquivo: " << filename << endl;
        return;
    }
    while (getline(file, line)) {
        istringstream s(line);
        string source, target, airlineCode;
        if (getline(s,source, ',') && getline(s, target, ',')
        && getline(s, airlineCode, ',')) {
            auto airportIt = airportsMap.find(source);
            if (airportIt != airportsMap.end()) {
                auto airlineIt = airlinesMap.find(airlineCode);
                if (airlineIt != airlinesMap.end()) {
                    airportIt->second.addFlight(airlineIt->second, target);
                    flights++;
                 }
                }
            }
        }
    for(auto i : airportsMap){
        g.newAirport(i.second);
    }
    file.close();
}

void System::FastConnectionCity(const std::string &source, const std::string &dest) {
    auto paths = g.quickestConnectionCity(source, dest);
    if (paths.empty()) {
        std::cout << "No connection between " << source << " and " << dest << std::endl;
        return;
    }
    for(auto i : paths){
        cout << i.first;
        for (const auto& path : i.second) {
            std::cout << endl;

            for (const auto& airport : path) {
                std::cout << " -> " << airport;
            }
            std::cout << std::endl;
        }
    }
}


void System::FastConnection(const std::string& source, const std::string& dest) {
    auto paths = g.quickestConnection(source, dest);

    if (paths.empty()) {
        std::cout << "No conecction between " << source << " and " << dest << std::endl;
        return;
    }

    // Encontrar o tamanho mínimo dos caminhos
    size_t minSize = paths[0].size();
    for (const auto& path : paths) {
        minSize = std::min(minSize, path.size());
    }

    // Filtrar os caminhos que têm o tamanho mínimo
    vector<vector<string>> shortestPaths;
    for (const auto& path : paths) {
        if (path.size() == minSize) {
            shortestPaths.push_back(path);
        }
    }

    // Imprimir os caminhos possíveis
    std::cout << "Possibles paths (min size " << minSize << "):" << std::endl;
    for (const auto& path : shortestPaths) {
        std::cout << "  ";
        for (const auto& airport : path) {
            std::cout << " -> " << airport;
        }
        std::cout << std::endl;
    }
}

void System::NumberofAandF() {
    cout << "Number of Airports: " << airportsMap.size() << endl;
    cout << "Numbet of Flights: " << flights << endl;

}

void System::NumberofFofAir(string code) {
g.NumberofFofAir(code);
}

void System::NumberofFofCity(string city) {
int number = g.NumberofFofCity(city);
cout << "The number of flights of " << city <<" is: " << number << endl;
}

void System::NumberofFofAirline(string airlinecode) {
    int number = g.NumberofFofAirline(airlinecode);
    cout << "The number of flights of a "<< airlinecode << " is: " << number << endl;
}

void System::NumberofDContriesairport(string code){
    int number = g.NumberofDContriesairport(code);
    cout << "The number of contries you can go with this airport ("<< code << ") is: " << number << endl;
}

void System::NumberofDContriescity(string city){
    int number = g.NumberofDContriescity(city);
    cout << "The number of contries you can go with in this city ("<< city << ") is " << number << endl;
}

void System::avaliabledestinations(string code, int num) {
    int number = g.avaliabledestinations(code, num);
    if(num == 1){
        cout << "The number of airports you can go with in this airports ("<< code << ") is " << number << endl;
    }
    else if(num == 2){
        cout << "The number of cities you can go with in this airports ("<< code << ") is " << number << endl;
    }
    else if(num == 3){
        cout << "The number of countries you can go with in this airports ("<< code << ") is " << number << endl;
    }
}

void System::reachabledestinationsmax(string code, int max, int num){
    int number = g.reachabledestinationsmax(code, max, num);
    if(num == 1){
        cout << "The number of reachable airports you can go with in a maximum number of " << max << " stops with this airports ("<< code << ") is " << number << endl;
    }
    else if(num == 2){
        cout << "The number of reachable cities you can go with in a maximum number of " << max << " stops with this airports ("<< code << ") is " << number << endl;
    }
    else if(num == 3){
        cout << "The number of reachable countries you can go with in a maximum number of " << max << " stops with this airports ("<< code << ") is " << number << endl;
    }
}

void System::maxdistance() {
    vector<pair<pair<string, string>, int>> rest = g.BFSLargestFlightCount();
    int max = 0;
    for (auto i: rest){
        if (i.second > max) {
            max = i.second;
        }
}
for(auto i : rest){
    if(i.second == max){
        cout << "The trip with greatest number of stops is from " <<  i.first.first << " to " << i.first.first << " with " << i.second << " stops" << endl;
        }
    }
}

void System::topairports(int k){
    int num = 1;
    vector<Airport> airports = g.topairports(k);
    for(auto i : airports){
        cout << num << "- " << i.getName() << " number of flights " << i.getNumberOfFlights() << endl;
        num++;
    }
}

void System::FastConnectionCord(string source, double lat, double lon) {
    vector<pair<Airport,double>> closestones = g.ClosestAirport(lat, lon);
    if(closestones.size() > 1){
        cout << "The closest airports are: ";
    }
    else    {
        cout << "The closest airport is: ";
    }
    for(auto i : closestones){
        cout << i.first.getName() << "is located at a distance of " << i.second << "km from the " << lat << " and " << lon << " coordinates." << endl;
    }
    cout << endl;
    for(auto i : closestones){
        FastConnection(source, i.first.getCode());
    }
}

void System::essentialairports() {
    int number = g.essential();
cout << "The number of essential airports are: " << number << endl;
}
