#ifndef PROJETOAED2_GRAPH_H
#define PROJETOAED2_GRAPH_H
#include "Airport.h"
#include <vector>
#include <algorithm>
#include <cctype>
#include <unordered_map>
#include <cmath>
#include <stack>
#include <iostream>
class graph{
private:
    vector<Airport> AirportSet;
    unordered_map<string, Airport> airportMap; //ajudar nas statistics
public:
void initializeIndices();
int getIndex(const string& code) const;
int getnumberofairports();
/**
 * @brief No conjunto do AirportSet esta função procura por um aeroporto com um determinado codigo.
 * A complexidade é de O(V) - Onde V é o número de aeroportos no AirportSet
 * @param code = codigo do aeroporto a procurar
 * @return retorna o aeroporto se o encontrar
 */
Airport FindAirport(const string code) const;
void newAirport(const Airport a);
void addFlight(const string source, const string dest, Airline airline);
vector<Airport> getairports();
/**
 * @brief Esta função quickestConnection procura a conexão mais rápida entre dois aeroportos específicos.
 * A complexidade é de O(V + E) - pois recorre à funcao bfs
 * @param source = aeroporto de origem
 * @param dest = aeroporto de destino
 * @return retorna o vetor do caminho a percorrer entre os dois aeroportos
 */
vector<vector<string>> quickestConnection(std::string source, std::string dest);
/**
 * @brief Esta função bfs (Breadth-First Search) realiza uma busca em largura a partir de um aeroporto de origem até um aeroporto de destino no grafo.
 * A complexidade desta função é O(V + E) onde E representa o número de arestas (voos)
 * @param source = aeroporto de origem
 * @param dest = aeroporto de destino
 * @return retorna o vetor resultante da pesquisa
 */
vector<vector<string>> bfs(Airport source, Airport dest);
void markallnotvisited();
/**
 * @brief Esta função quickestConnectionCity procura a conexão mais rápida entre duas cidades, considerando todos os pares de aeroportos entre uma cidade de origem e uma cidade de destino.
 * A complexidade é de O(V^2)
 * @param source = cidade d origem
 * @param dest = cidade de destino
 * @return retorna o vetor resultante da pesquisa feita
 */
vector<pair<string, vector<vector<string>>>> quickestConnectionCity(string  source, string dest);
/**
 * @brief Procura todos os aeroportos presentes numa determinada cidade. Complexidade de O(V) - Onde V é o número de aeroportos no AirportSet
 * A complexidade desta função é O(V)
 * @param city = nome da cidade a se procurar
 * @return retorna o um vetor com todos os aeroportos nessa cidade
 */
vector<Airport> FindAirportviaCity(const std::string city) const;
/**
 * @brief Calcula o número de voos que saem de um aeroporto específico e a quantidade de companhias aéreas diferentes.
 * A complexidade desta função é O(V)
 * @param code = Código do aeroporto para o qual o número de voos será calculado.
 * @return void
 */
void NumberofFofAir(string code);
int NumberofFofCity(string city);
int NumberofFofAirline(string code);
int NumberofDContriesairport(string code);
int NumberofDContriescity(std::string city);
/**
 * @brief Calcula o número de destinos únicos alcançáveis a partir de um aeroporto específico, considerando diferentes critérios.
 * Complexidade de O(V + E)
 * @param code = Código do aeroporto de partida para calcular os destinos.
 * @param num = Número que indica o critério de contagem dos destinos:
 *            - 1 para contagem de destinos por código de aeroporto.
 *            - 2 para contagem de destinos por cidade.
 *            - Qualquer outro valor para contagem de destinos por país.
 * @return Retorna o número de destinos únicos alcançáveis com base no critério fornecido.
 */
int avaliabledestinations(string code, int num);
int reachabledestinationsmax(string code, int max, int num);
/**
 * @brief Utiliza a busca em largura (BFS) para contar o número de aeroportos que estão a uma distância máxima do aeroporto de origem.
 * Complexidade de O(V + E)
 * @param source = Aeroporto de origem para iniciar a procura.
 * @param max = Distância máxima a considerar na contagem dos aeroportos.
 * @return Retorna o número de aeroportos que estão a uma distância máxima do aeroporto de origem.
 */
int bfsairportnumber(Airport source, int max);
int bfscitiesnumber(Airport source, int max);
int bfscountrynumber(Airport source, int max);
vector<pair<pair<string, string>, int>> BFSLargestFlightCount();
/**
 * @brief Executa uma procura em largura (BFS) com rastreamento dos níveis dos vértices alcançados a partir de um aeroporto de origem.
 * Complexidade de O(V + E)
 * @param startCode = Aeroporto de origem para iniciar a busca.
 * @param distances = Vetor que armazena as distâncias entre pares de aeroportos e seus respectivos níveis.
 * @param i  = Valor inteiro usado na iteração da função.
 * @return Não possui retorno explícito, mas preenche o vetor 'distances' com pares de aeroportos e seus níveis alcançados.
 */
void BFSWithLevels(Airport startCode, vector<pair<pair<string,string>, int>> distances, int i);
/**
 * @brief Retorna os 'k' aeroportos com as maiores estatísticas, priorizando aeroportos não visitados e, em caso de empate, aeroportos com menos voos.
 * Complexidade de O(k * (V + log(V)))
 * @param k = Número de aeroportos a serem retornados.
 * @return Retorna um vetor contendo os 'k' aeroportos com as maiores estatísticas, seguindo as prioridades estabelecidas.
 */
vector<Airport> topairports(int k);
int essential();
/**
 * @brief Encontra os aeroportos mais próximos de uma coordenada geográfica (latitude e longitude).
 * Complexidade de O(V)
 * @param lat = Latitude da coordenada geográfica.
 * @param lon = Longitude da coordenada geográfica.
 * @return Retorna um vetor contendo pares de aeroportos e suas respectivas distâncias à coordenada fornecida.
 *
 */
vector<pair<Airport,double>> ClosestAirport(double lat, double lon);
/**
 * @brief Executa uma busca em profundidade (DFS) para identificar pontos de articulação em um grafo.
 * Complexidade de O(V + E)
 * @param airport = Aeroporto de origem para iniciar a busca.
 * @param num = Vetor de números de ordem para os vértices no grafo.
 * @param low = Vetor de valores mínimos para os vértices no grafo.
 * @param S = Pilha utilizada na busca em profundidade.
 * @param visited = Vetor de controle para marcar os vértices visitados.
 * @return Retorna o número de pontos de articulação identificados no grafo.
 */
int dfs_art(const Airport& airport, vector<int>& num, vector<int>& low, stack<int>& S, vector<bool>& visited);
int findArticulationPoints();
};
#endif //PROJETOAED2_GRAPH_H