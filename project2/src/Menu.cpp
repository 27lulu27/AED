
#include <iostream>
#include "Menu.h"

using namespace std;

void Menu::start(System system) {
    while (true) {
        cout << endl << "Menu:" << endl;
        cout << "1- Present the best flight option" << endl;
        cout << "2- Present the best flight option (filters)" << endl;
        cout << "3- Statistics of the network" << endl;
        cout << "Press a number to continue or press 0 to quit" << endl;
        int choice;  // Corrigindo o nome da variável para "choice".
        cin >> choice;

        if (choice == 0) {
            break;
        } else if (choice == 1) {
            cout << "1- Airport code" << endl;
            cout << "2- City name" << endl;
            cout << "3- Geographical coordinates" << endl;
            int subchoise;
            cin >> subchoise;
            if(subchoise == 1) {
                cout << "Enter the Airport source code:" << endl;
                string source;
                cin >> source;
                cout << "Enter the Airport destination code:" << endl;
                string destination;
                cin >> destination;
                system.FastConnection(source, destination);  // Corrigindo o nome da função para FastConnection.
            } else if(subchoise == 2){
                cout << "Enter the City source name:" << endl;
                string source;
                std::getline(std::cin >> std::ws, source);
                cout << "Enter the City deestination name:" << endl;
                string destination;  // Corrigindo o nome da variável para "destination".
                std::getline(std::cin >> std::ws, destination);
                system.FastConnectionCity(source, destination);  // Corrigindo o nome da função para FastConnection.
            }
            else if(subchoise == 3){
                cout << "Enter the Airport source code:" << endl;
                string source;
                cin >> source;
                cout << "Enter the Latitute: " << endl;
                double lat;
                cin >> lat;
                cout << "Enter the Longitude: " << endl;
                double lon;
                cin >> lon;
                system.FastConnectionCord(source,lat,lon);
            }
        }
        else if(choice == 3){
            cout << "1- Global number of airports and number of available flights;" << endl;
            cout << "2- Number of flights out of an airport; and from how many different airlines;" << endl;
            cout << "3- Number of flights per city;" << endl;
            cout << "4- Number of flights per Airline;" << endl;
            cout << "5- Number of different countries that a given airport flies to;" << endl;
            cout << "6- Number of different countries that a given city flies to;" << endl;
            cout << "7- Number of destinations (airports, cities or countries) available for a given airport;" << endl;
            cout << "8- Number of reachable destinations (airports, cities or countries) from a given airport in a\n"
                    "maximum number of X stops (lay-overs);" << endl;
            cout << "9- Maximum trip and corresponding pair of source-destination airports with the greatest number of stops in between them" << endl;
            cout << "10- The top K airports with the greatest number of flights" << endl;
            cout << "11- The essential airpots" << endl;

            int subchoise;
            cin >> subchoise;
            if(subchoise == 1){
               system.NumberofAandF();
            }
            else if(subchoise == 2){
                cout << "Enter the airport code:";
                string code;
                cin >> code;
                system.NumberofFofAir(code);
            }
            else if(subchoise == 3){            //cidades compostas nao funcionam
                cout << "Enter the city name:";
                string city;
                std::getline(std::cin >> std::ws, city);
                system.NumberofFofCity(city);
            }
            else if(subchoise == 4){
                cout << "Enter the airline code:";
                string Airlinecode;
                cin >> Airlinecode;
                system.NumberofFofAirline(Airlinecode);
            }
            else if(subchoise == 5){
                cout << "Enter the airport code:" << endl;
                string code;
                cin >> code;
                system.NumberofDContriesairport(code);
            }
            else if(subchoise == 6){
                cout << "Enter the city name:" << endl;
                string city;
                std::getline(std::cin >> std::ws, city);
                system.NumberofDContriescity(city);
            }
            else if(subchoise == 7){
                cout << "Enter the airport code:"<< endl;
                string code;
                cin >> code;
                cout << "1- Number of airports available" << endl;
                cout << "2- Number of cities available" << endl;
                cout << "3- Number of countries available" << endl;
                int subsubchoise;
                cin >> subsubchoise;
                system.avaliabledestinations(code, subsubchoise);
            }
            else if(subchoise == 8){
                cout << "Enter the airport code:"<< endl;
                string code;
                cin >> code;
                cout << "Enter the Number of stops" << endl;
                int num;
                cin >> num;
                cout << "1- Number of airports available in a maximum number of "  << num << " stops" << endl;
                cout << "2- Number of cities available in a maximum number of " << num << " stops" << endl;
                cout << "3- Number of countries available in a maximum number of " << num << " stops" << endl;
                int subsubchoise;
                cin >> subsubchoise;
                system.reachabledestinationsmax(code, num,subsubchoise);
            }
            //demora mtoooooooo para dar output
            else if(subchoise == 9){
                system.maxdistance();
            }
            else if(subchoise == 10){
                cout << "Chose how many airports you want to see (k)" << endl;
                int k;
                cin >> k;
                system.topairports(k);
            }
            else if(subchoise == 11){
                system.essentialairports();
            }
        }
    }
}
