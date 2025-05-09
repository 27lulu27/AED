#include "../include/Class.h"
#include <iostream>
#include <iomanip>
using namespace std;

string const Class::get_id() const {
    return id;
}

Class::Class(string id, int duration, string weekday, double starthour, string type, UC uc1) :
        id(id),
        duration(duration),
        weekday(weekday),
        starthour(starthour),
        type(type),
        uc_(uc1) { }

std::string Class::get_Info() const {
    std::string frase;
    std::setprecision(2);
    frase =
            "Duration = " + std::to_string(get_duration()) +
            ", StartHour = " + std::to_string(get_starthour()) +
            ", Type = " + get_type() +
            ", Weekday = " + weekday;
    return frase;
}
int Class::get_duration() const {
    return duration;
}
double Class::get_starthour() const {
    return starthour;
}
string Class::get_type() const {
    return type;
}
string Class::get_weekday() const {
    return weekday;
}

void Class::set_uc(UC nuc){
    this->uc_ = nuc;

}
const UC Class::get_uc() const {
    return uc_;
}

std::string Class::get_Schedule() {
    // Converte o horário e a duração para um formato mais legível
    int startHourInt = static_cast<int>(starthour); // Parte inteira do horário
    int startMinutes = (starthour - startHourInt) * 60; // Parte decimal convertida em minutos

    int finishHourInt = startHourInt + static_cast<int>(duration); // Hora de término como parte inteira
    int finishMinutes = startMinutes + (static_cast<int>((duration - static_cast<int>(duration)) * 60));
    //Minutos de término

    // Formata o horário e a duração
    std::string scheduleMessage = weekday + " startHour: " + std::to_string(startHourInt) + ":" +
                                  (startMinutes < 10 ? "0" : "") + std::to_string(startMinutes) +
                                  " finishHour: " + std::to_string(finishHourInt) + ":" +
                                  (finishMinutes < 10 ? "0" : "") + std::to_string(finishMinutes) +
                                  " type: " + type + " Class id:" + get_id() + " Class uccode:" + get_uc().getUC();

    return scheduleMessage;
}

//exemplo de output 1200
int Class::getstarthour() const {
    int hours = static_cast<int>(starthour);
    int minutes = static_cast<int>((starthour - hours) * 60);
    int start_time = (hours * 100) + minutes;
    return start_time;
}
//exemplo de output 1400
int Class::getendhour() const {
    int hours = static_cast<int>(starthour) + duration; // Adicione o duration hora para o término
    int end_time = (hours * 100);
    return end_time;
}
bool Class::scheduleconflict(const Class& c2) const {
    // Verifica se a classe atual começa após o término da segunda classe (c2)
    if (getstarthour() >= c2.getendhour()) {
        return false;
    }

    // Verifica se a classe atual termina antes do início da segunda classe (c2)
    if (getendhour() <= c2.getstarthour()) {
        return false;
    }

    // Se nenhuma das condições acima for atendida, há um conflito
    return true;
}


int Class::getcapacytimax() {
    if(type == "TP"){
        return 50;
    }
    else{
        return 100;
    }
}

std::string Class::get_weekday() {
    return weekday;
}

