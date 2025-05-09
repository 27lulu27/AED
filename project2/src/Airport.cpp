#include "Airport.h"

Airport::Airport(){}

Airport::Airport(string code, string name, string city, string country, double latitude, double longitude):
                 code(code), name(name), city(city), country(country), latitude(latitude), longitude(longitude){}


string Airport::getCode() const{
    return code;
}

string Airport::getName() const{
    return name;
}

string Airport::getCity() const{
    return city;
}

string Airport::getCountry() const{
    return country;
}

double Airport::getLatitude() const{
    return latitude;
}

double Airport::getLongitude() const{
    return longitude;
}

vector<Flight> Airport::getAdj() const {
    return adj;                             //vetor com os voos
}

void Airport::addFlight(Airline airline, string target) {
adj.push_back(Flight(airline, target));
numberofflights++;
}

void Airport::setvisited(const bool v) {
    visited = v;
}

bool Airport::isvisited() {
    return visited;
}

int Airport::getNumberOfFlights() {
    return numberofflights;
}

bool Airport::isProcessed() {
    return processed;
}

void Airport::setProcessed(const bool k){
    processed = k;
}

int Airport::getIndex() const {
    return index;
}

void Airport::setIndex(int newIndex) {
    index = newIndex;

}

