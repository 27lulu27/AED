#ifndef STUDENT_H
#define STUDENT_H
#include <iostream>
#include <string>
#include <vector>
#include "Class.h"
#include <utility>
#include <set>
#include <stack>
#include <map>

class System;
using namespace std;
class Student {
private:
    int id;
    std::string name;
    std::vector<std::pair<std::string, std::string>> classes_ids_and_uccode;
    std::string from_class, to_class, uccode; //usando quando mudar entre estudantes
public:
    Student(int id, std::string name);
    void addclass(const std::string& Class, const std::string& uccode);
    int get_id() const;
    std::vector<std::pair<std::string, std::string>> getclasses();
    std::string getname();
    bool hasClass(std::string c, std::string uccode);
    int whichyear();
    void removeclass(const std::string& classid, const std::string& uccode);
    void wantstochange(std::string class1, std::string class2, std::string uc);
    string get_from_class() const;
    string get_to_class() const;
    string get_uccode() const;
    int numberofucs();
    map<string, int> get_ucs();
    void removeuc(const string& uccode);
    void adduc(const std::string& uccode, System& system);
    void push_added_class(std::string c, std::string uc);
    void push_removed_class(std::string c, std::string uc);
    void push_added_uc(std::string uc);
    void push_removed_uc(std::string uc);
    void pop_added_class();
    void pop_removed_class();
    void pop_added_uc();
    void pop_removed_uc();
    pair<std::string, std::string> get_top_removed_classes();
    pair<std::string, std::string> get_top_added_classes();
    string get_top_added_ucs();
    string get_top_removed_ucs();

    /**
     * @brief uma das stacks para armazenar as alterações das classes e das ucs
     */
    //stacks para armazenas as alterações das classes e das ucs
    std::stack<std::pair<std::string, std::string>> added_classes;
    std::stack<std::pair<std::string, std::string>> removed_classes;
    /**
     * @brief uma das stacks para armazenar as alterações nas ucs;
     */
    std::stack<std::string> added_ucs;
    std::stack<std::string> removed_ucs;
};

#endif


