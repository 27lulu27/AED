#include <queue>
#include <unordered_set>
#include <map>
#include <set>
#include "Graph.h"

Airport graph::FindAirport(const string code) const {
    for (Airport v : AirportSet){
        if(v.getCode() == code){
            return v;
        }
    }
    cout << "Not found";
    Airport V;
    return V;
}               //se nao encontrar retorna oq?

vector<Airport> graph::FindAirportviaCity(const std::string city) const {
    vector<Airport> airportsinacity;
    for (const Airport& V : AirportSet) {
        if (V.getCity() == city) {
            airportsinacity.push_back(V);
        }
    }
    return airportsinacity;
}


void graph::newAirport(const Airport a) {
    AirportSet.push_back(a);
    airportMap.emplace(a.getCode(), a);
}

void graph::addFlight(const string source, const string dest, Airline airline) {
    auto asource = FindAirport(source);
    asource.addFlight(airline, dest);
}

vector<Airport> graph::getairports() {
    return AirportSet;
}



vector<vector<string>> graph::bfs(Airport source, Airport dest) {
    vector<vector<string>> allPaths;  // Lista para armazenar todos os caminhos
    queue<vector<string>> q;  // Fila para processar caminhos
    unordered_set<string> visitedAirports;  // Conjunto para armazenar aeroportos visitados

    q.push({source.getCode()});  // Inicializa a fila com um caminho contendo o aeroporto de origem
    visitedAirports.insert(source.getCode());  // Marca o aeroporto de origem como visitado

    while (!q.empty()) {
        vector<string> currentPath = q.front();  // Obtém o próximo caminho da fila
        q.pop();

        string currentAirportCode = currentPath.back();  // Obtém o código do último aeroporto no caminho
        if (currentAirportCode == dest.getCode()) {
            allPaths.push_back(currentPath);  // Se chegou ao destino, adiciona o caminho à lista
            continue;  // Continua para explorar outros caminhos
        }
        Airport currentAirport = FindAirport(currentAirportCode);
        for (auto neighbor : currentAirport.getAdj()) {
            auto neighborCode = neighbor.getTarget();
            if (visitedAirports.find(neighborCode) == visitedAirports.end()) {
                visitedAirports.insert(neighborCode);  // Marca o aeroporto vizinho como visitado
                vector<string> newPath = currentPath;  // Cria um novo caminho baseado no caminho atual
                newPath.push_back(neighborCode);  // Adiciona o aeroporto vizinho ao novo caminho
                q.push(newPath);  // Adiciona o novo caminho à fila para processamento futuro
            }
        }
    }
    return allPaths;  // Retorna a lista de todos os caminhos encontrados
}


std::vector<vector<string>> graph::quickestConnection(std::string source, std::string dest) {
    Airport startAirport = FindAirport(source);
    Airport destinationAirport = FindAirport(dest);
    markallnotvisited();
    auto shortestPath = bfs(startAirport,destinationAirport);

    if (shortestPath.empty()) {
        std::cout << "Não há conexão entre " << source << " e " << dest << std::endl;
    }

    return shortestPath;
}


void graph::markallnotvisited(){
    for(auto &a : AirportSet){
        a.setvisited(false);
    }
}

vector<pair<string, vector<vector<string>>>> graph::quickestConnectionCity(string citysource, string citydest) {
    vector<pair<string, vector<vector<string>>>> airports;
    vector<Airport> start = FindAirportviaCity(citysource); // Aeroportos da cidade de origem
    vector<Airport> dest = FindAirportviaCity(citydest);    // Aeroportos da cidade de destino
    for (auto i : start) {  // Para cada aeroporto da cidade de origem
        for (auto j : dest) {  // Para cada aeroporto da cidade de destino
            markallnotvisited();
            string newpair = "Aeroport of "+ citysource + ":" + i.getName() + " " + "Aeroport of " + citydest+ ":"  + j.getName();
            vector<vector<string>> paths = bfs(i, j);
            airports.push_back(make_pair(newpair, paths));  // Adiciona ao vetor 'airports' os caminhos entre os dois aeroportos
        }
    }
    if (airports.empty()) {
        std::cout << "Não há conexão entre " << citysource << " e " << citydest << std::endl;
    }
    return airports;
}

void graph::NumberofFofAir(string code) {
    int numberofflights = 0;
    map<string, int> airlinesMap;

    Airport airport = FindAirport(code);

    for(auto flight : airport.getAdj()) {
        numberofflights++;
        airlinesMap[flight.getAirline().getCode()]++;
    }

    cout << "The Airport " << code << " has " << numberofflights << " flights from " << airlinesMap.size() << " different airlines." << endl;
}

int graph::NumberofFofCity(string city) {
    int num = 0;
    for(auto i : AirportSet){
        if(i.getCity() == city){
            num += i.getAdj().size();
        }
    }
    return num;
}

int graph::NumberofFofAirline(string code) {
    int num = 0;
    for(auto i : AirportSet){
        for(auto j : i.getAdj()){
            if(j.getAirline().getCode() == code){
                num++;
            }
        }
    }
    return num;
}

int graph::NumberofDContriesairport(string code){
    auto air = FindAirport(code);
    map<string, int> countries;
    for(auto i : air.getAdj()){
        auto dest = FindAirport(i.getTarget());
        countries[dest.getCountry()]++;
    }
    return countries.size();
}

int graph::NumberofDContriescity(std::string city) {
    auto air = FindAirportviaCity(city);
    map<string, int> countries;
    for(auto i : air){
       for(auto j : i.getAdj()){
           auto dest = FindAirport(j.getTarget());
           countries[dest.getCountry()]++;
       }
    }
    return countries.size();
}

int graph::avaliabledestinations(string code, int num) {
    auto air = FindAirport(code);
    map<string, int> airports;
    if(num == 1){
        for(auto i : air.getAdj()){
            auto dest = FindAirport(i.getTarget());
            airports[dest.getCode()]++;
        }
        return airports.size();
    }
    else if(num == 2){
        for(auto i : air.getAdj()){
            auto dest = FindAirport(i.getTarget());
            airports[dest.getCity()]++;
        }
        return airports.size();
    }
    for(auto i : air.getAdj()){
        auto dest = FindAirport(i.getTarget());
        airports[dest.getCountry()]++;
    }
    return airports.size();
}

int graph::reachabledestinationsmax(string code, int max, int num) {
    auto air = FindAirport(code);
    if(num == 1){
        return bfsairportnumber(air, max);
    }
    else if(num == 2){
        return bfscitiesnumber(air, max);
    }
    else if(num == 3){
    return bfscountrynumber(air, max);
    }
}


int graph::bfsairportnumber(Airport source, int max) {
    vector<string> res;
    queue<pair<Airport, int>> fila;  // Pair para armazenar o vértice e a distância
    fila.push({source, 0});
    markallnotvisited();
    while(!fila.empty()){
        auto currentpair = fila.front();
        fila.pop();
        auto currentairp = currentpair.first;
        int currentDistance = currentpair.second;
        currentairp.setvisited(true);
        if(currentDistance == max){
            res.push_back(currentairp.getCode());
            continue;
        }
        for(auto edge : currentairp.getAdj()){
            auto neigbo = edge.getTarget();
            auto airpn = FindAirport(neigbo);
            if(!airpn.isvisited()){
                fila.push({airpn, currentDistance + 1});
            }
        }
    }
    return res.size();
}

int graph::bfscitiesnumber(Airport source, int max) {
    vector<string> res;
    set<string> cities;
    queue<pair<Airport, int>> fila;  // Pair para armazenar o vértice e a distância
    fila.push({source, 0});
    markallnotvisited();
    while(!fila.empty()){
        auto currentpair = fila.front();
        fila.pop();
        auto currentairp = currentpair.first;
        int currentDistance = currentpair.second;
        currentairp.setvisited(true);
        if(currentDistance == max){
            res.push_back(currentairp.getCode());
            cities.insert(currentairp.getCity());
            continue;
        }
        for(auto edge : currentairp.getAdj()){
            auto neigbo = edge.getTarget();
            auto airpn = FindAirport(neigbo);
            if(!airpn.isvisited()){
                fila.push({airpn, currentDistance + 1});
            }
        }
    }
    return cities.size();
}

int graph::bfscountrynumber(Airport source, int max) {
    vector<string> res;
    set<string> countries;
    queue<pair<Airport, int>> fila;  // Pair para armazenar o vértice e a distância
    fila.push({source, 0});
    markallnotvisited();
    while(!fila.empty()){
        auto currentpair = fila.front();
        fila.pop();
        auto currentairp = currentpair.first;
        int currentDistance = currentpair.second;
        currentairp.setvisited(true);
        if(currentDistance == max){
            res.push_back(currentairp.getCode());
            countries.insert(currentairp.getCountry());
            continue;
        }
        for(auto edge : currentairp.getAdj()){
            auto neigbo = edge.getTarget();
            auto airpn = FindAirport(neigbo);
            if(!airpn.isvisited()){
                fila.push({airpn, currentDistance + 1});
            }
        }
    }
    return countries.size();
}

vector<pair<pair<string, string>, int>> graph::BFSLargestFlightCount() {
    int i = 0;
    vector<pair<pair<string, string>, int>> distances;

    for (auto& startEntry : AirportSet) {
        BFSWithLevels(startEntry, distances, i);
    }
    return distances;
}

void graph::BFSWithLevels(Airport startCode, vector<pair<pair<string,string>, int>> distances, int i) {
    // Marca todos os vértices como não visitados
    markallnotvisited();

    // Marca o vértice de origem como visitado e define o nível como 0
    startCode.setvisited(true);

    // Fila para armazenar os pares (vértice, nível)
    queue<pair<string, int>> q;

    // Adiciona o vértice de origem à fila com nível 0
    q.push({startCode.getCode(), 0});

    // Adiciona um marcador de nível para indicar o final de cada nível
    q.push({"NULL", 0});

    // BFS com rastreamento de níveis
    while (!q.empty()) {
        // Retira um par (vértice, nível) da fila
        auto currentPair = q.front();
        q.pop();

        string currentVertexCode = currentPair.first;
        int currentLevel = currentPair.second;

        // Verifica se atingiu o marcador de nível
        if (currentVertexCode == "NULL") {
            // Adiciona um novo marcador de nível se ainda houver vértices na fila
            if (!q.empty()) {
                q.push({"NULL", 0});
            }

            continue;
        }
        cout << i << " ";
        i++;
        distances.push_back({{startCode.getCode(), currentVertexCode}, currentLevel});
        // Itera sobre os vizinhos do vértice atual
        auto currentairp = FindAirport(currentVertexCode);
        for(auto edge : currentairp.getAdj()){
            auto neigbo = edge.getTarget();
            auto airpn = FindAirport(neigbo);
            if(!airpn.isvisited()){
                q.push({airpn.getCode(), currentLevel + 1});
            }
        }
    }
}




vector<Airport> graph::topairports(int k) {
    markallnotvisited();
    vector<Airport> res;
    for(int i = 1; i <= k; i++){
        auto maxElement = std::max_element(
                AirportSet.begin(),
                AirportSet.end(),
                [](Airport a,  Airport b) {
                    // Ordena com base no número de voos, mas aeroportos não visitados têm prioridade
                    if (a.isvisited() != b.isvisited()) {
                        return a.isvisited() > b.isvisited();
                    } else {
                        return a.getNumberOfFlights() < b.getNumberOfFlights();
                    }
                }
        );
    maxElement->setvisited(true);
    res.push_back(*maxElement);
    }
    return res;
}

int graph::essential() {
   initializeIndices();
   return findArticulationPoints();
}
void graph::initializeIndices() {
    int currentIndex = 0;
    for (auto& airport : AirportSet) {
        airport.setIndex(currentIndex);
        currentIndex++;
    }
}
int graph::dfs_art(const Airport& airport, vector<int>& num, vector<int>& low, stack<int>& S, vector<bool>& visited) {
    static int index = 0;
    int children = 0;
    int airportIndex = airport.getIndex();  // Usar o índice do aeroporto diretamente
    num[airportIndex] = low[airportIndex] = ++index;
    S.push(airportIndex);
    visited[airportIndex] = true;

    int articulationPoints = 0;  // Contador de pontos de articulação

    for (auto& flight : airport.getAdj()) {
        int targetIndex = airportMap[flight.getTarget()].getIndex();
        if (!num[targetIndex]) {
            children++;
            articulationPoints += dfs_art(airportMap[flight.getTarget()], num, low, S, visited);
            low[airportIndex] = min(low[airportIndex], low[targetIndex]);
            if (low[targetIndex] >= num[airportIndex]) {
                cout << airport.getCode() << " is an articulation point\n";
                articulationPoints++;
            }
        } else if (visited[targetIndex]) {
            low[airportIndex] = min(low[airportIndex], num[targetIndex]);
        }
    }

    if (children > 1 && !num[airportIndex]) {
        cout << airport.getCode() << " is an articulation point\n";
        articulationPoints++;
    }

    S.pop();

    return articulationPoints;
}

int graph::findArticulationPoints() {
    vector<int> num(AirportSet.size(), 0);
    vector<int> low(AirportSet.size(), 0);
    vector<bool> visited(AirportSet.size(), false);
    stack<int> S;
    int totalArticulationPoints = 0;

    for (const Airport& airport : AirportSet) {
        int airportIndex = airport.getIndex();
        if (num[airportIndex] == 0) {
            totalArticulationPoints += dfs_art(airport, num, low, S, visited);
        }
    }

    return  totalArticulationPoints;}




vector<pair<Airport, double>> graph::ClosestAirport(double lat, double lon) {
    const double earthRadius = 6371.0; // Earth radius in kilometers

    std::vector<pair<Airport,double>> closestAirports;
    double minDistance = std::numeric_limits<double>::max();

    for (const auto &airport : AirportSet) {
        double deltaLat = airport.getLatitude() - lat;
        double deltaLon = airport.getLongitude() - lon;

        double distance = earthRadius * 2.0 * asin(sqrt(
                pow(sin(deltaLat / 2.0), 2.0) + cos(lat) * cos(airport.getLatitude()) * pow(sin(deltaLon / 2.0), 2.0)
        ));

        if (distance < minDistance) {
            minDistance = distance;
            closestAirports.clear();
            closestAirports.push_back({airport,distance});
        }
    }

    return closestAirports;
}

int graph::getnumberofairports() {
    return AirportSet.size();
}

bool operator==(const Airport& lhs, const Airport& rhs) {
    return lhs.getCode() == rhs.getCode();
}

bool operator!=(const Airport& lhs, const Airport& rhs) {
    return !(lhs == rhs);
}
