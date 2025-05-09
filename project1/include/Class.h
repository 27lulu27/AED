#ifndef CLASS_H
#define CLASS_H
#include <iostream>
#include <string>
#include <vector>
#include <iostream>
#include "UC.h"
using namespace std;

class Class {
private:
    std::string id;
    int duration;
    std::string weekday;
    double starthour;
    /**
     * @brief Aula Teórica ou Teórico-Prática
     */
    std::string type;
    UC uc_; //UC É UMA CLASSE
public:
    Class(string id, int duration, string weekday, double starthour, string type, UC uc1);
    Class();
    std::string const get_id() const;
    std::string get_Info() const;
    int get_duration() const;
    string get_weekday() const;
    string get_type() const;
    double get_starthour() const;
    const UC get_uc() const;
    void set_uc(UC nuc);
    string get_Schedule();
    int getstarthour() const;
    int getendhour() const;
    /**
     * @brief Função simples que verifica se ha conflitos entre duas aulas exemplo: c1 e c2
     * @param c2 = uma das aulas comparadas
     * @return
     */
    bool scheduleconflict(const Class& c2) const;
    int getcapacytimax();
    std::string get_weekday();

};

#endif
