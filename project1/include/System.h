#ifndef SYSTEM_H
#define SYSTEM_H
#include <list>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <vector>
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include "../include/Student.h"
#include "../include/Class.h"
#include "../include/Change.h"
#include "../include/UC.h"
using namespace std;

class System {
private:
    std::list<Student> students;
    std::list<Class> classes;
    /**
     * @brief Cria uma fila vazia para os alunos serem adicionados caso queiram trocar de turma entre si
     */
    Change change;
    unordered_map<std::string, int> classCapacities;
    stack<pair<int, string>> pairStack;       //no string vai ter a mudança que podem ser add_class, add_uc, remove_class,
                                              // remove_uc, change_class, change_uc
public:
    void addingtostack(int s1, string s2);
    /**
     * @brief Remove os efeitos de qualquer a operação mais recente que tenha sido feita no contexto do system
     * @param system
     */
    void undolastaction(System& system);
    bool checkifitsempty();
    /**
     * @brief Função que procura na lista de todos os estudantes aqueles que pertencem a uma determinada classe
     * @param classid = turma
     * @param uccode = numa determinada cadeira
     * @param type
     * @return
     */
    int currentcapacytiofaclass(string classid, string uccode, string type);

    bool checkBalance();
    unordered_map<std::string, int> get_classCapacities();
    //tem que ser public para poder acessar funções

    /**
     * @brief Faz a leitura dos ficheiros e armazena os seus dados
     *
     */
    System();

    std::list<Class> get_classes_system();

    void All_the_students_of_a_class_alphabeticaly(string num, string uc);

    void addClass(Class &class_);

    void addStudent(Student &student_);

    void All_the_students_of_a_class_numeral(string num, string uc);

    string getstudentname(int id);

    void Schedule_of_a_student(int c1);
    /**
     * @brief Mostra os dados armazenados dentro de uma classe
     * @param id = id da classe
     * @param uc = uc dessa classe
     */
    void Schedule_of_a_Class(std::string id, string uc);

    string extract_Day_Of_Week(string f);

    int getstudentid(string name);

    void All_the_students_of_a_uc_numeral(string uccode);

    void All_the_Student_of_a_uc_alphabeticaly(string uccode);

    void All_the_students_of_a_year_alphabeticaly(int year);

    void All_the_students_of_a_year_numeral(int year);

    void classocuppation(string classid, string uccode);

    void ucocuppation(string uccode);

    void yearocuppation(int year);

    void ucsbystudents();

    void studentsInAtLeastN_UCs(int n);
    /**
     * @brief Faz a troca caso haja dois estudantes para tal
     * @param studentid
     * @param from_class_id
     * @param to_class_id
     * @param uccode
     * @return
     */
    bool Changingstudentsindifferentclasses(int studentid, string& from_class_id, string& to_class_id, string& uccode);
    /**
     * @brief Adiciona o estudante a uma turma numa cadeira especifica se as condicoes assim o permitirem
     * @param idstudent = estudante candidato
     * @param classid = componente da turma
     * @param uccode = componente da cadeira
     * @return = retorna true se a operação for um sucesso
     */
    bool Addingastudentinaclass(int idstudent, const std::string &classid, const std::string &uccode);
    /**
     * @brief Remove um estudante de uma cadeira especifica se as condicoes assim o permitirem
     * @param idstudent = estudante candidato
     * @param classid = componente da turma
     * @param uccode = componente da cadeira
     */
    void Removingastudnetinaclass(int idstudent, const std::string &classid, const std::string &uccode);
    /**
     * @brief Verifica se há conflito entre as aulas de um aluno com a classe que ele pretende adicionar ou trocar
     * @param classid = id da classe nova/alterada
     * @param uccode = uccode da classe nova/alterada
     * @param studentid = aluno em questão
     * @return
     */
    bool scheduleconflict(string classid, string uccode, int studentid);
    /**
     * @brief Função que averigua se o estudante ja excedeu o limite de classes em que ele pode estar inscrito
     * @param studentid = estudante em questão
     * @return
     */
    bool itnotispossibletoaddmore(int studentid);

    void changeuc(string& from_uccode, int& studentid, string& to_uccode);

    void removeuc(string& uccode, int& studentid);

    bool adduc(string& uccode, int& studentid);

    void changeclassonly(int& idstudent, string& from_class, string& to_class, string& uccode3);

    /**
     * @brief Salva todas as alterações feitas pelo utilizador no ficheiro destino
     */
    void savealterations();
};
#endif
