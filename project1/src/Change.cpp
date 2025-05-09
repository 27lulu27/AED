#include "../include/Change.h"

void Change::AddStudentToQueue(Student& student) {
    for (auto& pair : priorityQueue) { // Usar auto& para modificar o par
        if (pair.second == student.get_uccode()) { // Verificar se são da mesma uc
            if (pair.first.front().get_to_class() == student.get_from_class()) {
                pair.first.push(student);
            }
        }
    }
}
bool Change::verifyandchangetheclass(Student& student) {
    for (auto& pair : priorityQueue) { // Usar auto& para modificar o par
        if (pair.second == student.get_uccode()) { // Verificar se são da mesma uc
            if (!pair.first.empty() && pair.first.front().get_to_class() == student.get_from_class()) {
                student.removeclass(student.get_from_class(), student.get_uccode());
                student.addclass(pair.first.front().get_to_class(), pair.first.front().get_uccode());
                pair.first.front().removeclass(pair.first.front().get_from_class(), pair.first.front().get_uccode());
                pair.first.front().addclass(student.get_from_class(), student.get_uccode());
                pair.first.pop();
                return true; // Fez a troca
            }
        }
    }
    return false; // Não encontrou nenhuma troca possível
}

Change::Change() {
    priorityQueue.emplace_back(queue<Student>(), "default_uccode");
}


