#ifndef CHANGE_H
#define CHANGE_H
#include <queue>
#include <vector>
#include "Student.h"
#include "Class.h"
using namespace std;
class Change{
private:
    /**
     * @brief Vetor onde sao armazenados os alunos que querem fazer mudança
     */
    vector<pair<queue<Student>, string>> priorityQueue;
public:
    /**
     * @brief Inicia a fila priorityQueue vazia;
     */
    Change();
    /**
     * @brief Adiciona um estundate à fila
     * @param student = estudante que quer ser adicionado
     */
    void AddStudentToQueue(Student& student);
    /**
     * @brief verifica se tem algum aluno disponivel, se tiver volta com true, só falta tirar o aluno compativel
     * @param student = estudante candidato
     * @return
     */
    bool verifyandchangetheclass(Student& student);
};
#endif
