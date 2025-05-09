#include <algorithm>
#include "../include/Student.h"
#include "../include/System.h"


Student::Student(int id, std::string name) {
this->name = name;
this->id = id;
};

void Student::addclass(const std::string& Class, const std::string& uccode) {
    classes_ids_and_uccode.push_back(std::make_pair(Class, uccode));
};

void Student::removeclass(const std::string& classid, const std::string& uccode) {
    for (auto it = classes_ids_and_uccode.begin(); it != classes_ids_and_uccode.end(); ++it) {
        if (it->first == classid && it->second == uccode) {
            classes_ids_and_uccode.erase(it);
            return;  // Saia do loop após encontrar e remover a classe.
        }
    }
    // Se a classe não foi encontrada, você pode lidar com isso, como gerar um erro ou fazer log.
}



int Student::get_id() const {
    return id;
}

std::vector<std::pair<std::string, std::string>> Student::getclasses() {
    return classes_ids_and_uccode;
}

std::string Student::getname() {
    return name;
}

bool Student::hasClass(std::string classcheck, std::string uccheck) {
    for (const auto& pair : classes_ids_and_uccode) {
        if (pair.first == classcheck && pair.second == uccheck) {
            return true;
        }
    }
    return false;
}

int Student::whichyear() {
    int max = 0;
    for (const auto& pair : classes_ids_and_uccode) {
        // Converta o primeiro caractere da class_id_and_uccode em um número inteiro
        int firstDigit = pair.first[0] - '0';

        // Verifique se o primeiro caractere é um dígito
        if (firstDigit >= 0 && firstDigit <= 9) {
            if (firstDigit > max) {
                max = firstDigit;
            }
        }
    }
    return max;
}
void Student::removeuc(const string& uccode){
    for(auto pair : getclasses()){
        if(uccode == pair.second){
            removeclass(pair.first, uccode);
        }
    }
}

void Student::wantstochange(std::string class1, std::string class2, std::string uc) {
from_class = class1;
to_class = class2;
uccode = uc;
}

string Student::get_from_class() const{
    return from_class;
}

string Student::get_to_class() const {
    return to_class;
}

string Student::get_uccode() const{
    return uccode;
}

int Student::numberofucs() {        //usamos o set para nao repetir as ucs
    std::set<string> unique_ucs;
    for (const auto& pair : classes_ids_and_uccode) {
        unique_ucs.insert(pair.second);
    }
    return unique_ucs.size();
}

void Student::push_added_class(std::string c, std::string uc) {
    added_classes.push(make_pair(c, uc));
}

void Student::push_added_uc(std::string uc) {
    added_ucs.push(uc);

}

void Student::push_removed_class(std::string c, std::string uc) {
    removed_classes.push(make_pair(c, uc));

}

void Student::push_removed_uc(std::string uc) {
    removed_ucs.push(uc);

}

void Student::pop_added_class() {
    added_classes.pop();

}

void Student::pop_removed_class() {
    removed_classes.pop();

}

void Student::pop_added_uc() {
    added_ucs.pop();

}

void Student::pop_removed_uc() {
    removed_ucs.pop();

}

pair<std::string, std::string> Student::get_top_removed_classes(){
    return removed_classes.top();
}
pair<std::string, std::string> Student::get_top_added_classes() {
    return added_classes.top();
}

string Student::get_top_added_ucs() {
    return added_ucs.top();
}

string Student::get_top_removed_ucs() {
    return removed_ucs.top();
}

void Student::adduc(const std::string& uccode, System& system) {
    for (const Class& c : system.get_classes_system()) {
        if (c.get_uc().getUC() == uccode) {
            if (system.scheduleconflict(c.get_id(), uccode, id)) {
                // Conflito de horário, continue para a próxima classe
                continue;
            } else {
                // Nenhum conflito de horário, adicione o estudante à classe
                addclass(c.get_id(), uccode);
                return;
            }
        }
    }
}
map<string, int> Student::get_ucs() {
    map<string, int> all_ucs;
    for(auto pair : getclasses()){
        all_ucs[pair.second]++;
    }
    return all_ucs;
}


