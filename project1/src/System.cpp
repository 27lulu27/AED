#include "../include/System.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <set>
#include <map>
#include <stack>
using namespace std;


unordered_map<std::string, int> System::get_classCapacities() {
    return classCapacities;
}
void System::addStudent(Student& student_){
    students.push_back(student_);
}
void System::addClass(Class &class_) {
    classes.push_back(class_);
}
int System::getstudentid(string name){
    for(Student& s : students){
        if(s.getname() == name) {
            return s.get_id();
        }
    }
    return 0;
}
string System::getstudentname(int id){
    for(Student& s : students){
        if(s.get_id() == id){
            return s.getname();
        }
    }
    return "Didn't find name";
}
System::System() {
    ifstream file("C:\\Users\\alexc\\CLionProjects\\PROJECTEAD\\data\\students_classes_modificado.csv");
    std::string line;
    map<int, Student> studentsmap;
    if (!file.is_open()) {
        std::cerr << "Erro ao abrir o arquivo." << std::endl;
    }
    std::getline(file, line);
    while (std::getline(file, line)) {
        std::istringstream s(line);
        int studentCode;
        std::string studentName, ucCode, classCode;
        char comma;
        if (s >> studentCode && s >> comma && std::getline(s, studentName, ',') &&
            std::getline(s, ucCode, ',') && std::getline(s, classCode, ',')) {}
        auto it = studentsmap.find(studentCode);
        if (it != studentsmap.end()) {
            // O studentCode já existe, verifique se a classe já foi adicionada antes de adicioná-la
            if (!it->second.hasClass(classCode, ucCode)) {
                it->second.addclass(classCode, ucCode);
            }
        } else {
            // O studentCode não existe, crie um novo objeto Student e adicione a classe a ele
            Student student(studentCode, studentName);
            student.addclass(classCode, ucCode);
            studentsmap.insert(make_pair(studentCode, student));
        }

    }
    file.close();
    for (const auto &pair: studentsmap) {
        const Student &student = pair.second; // Obtemos o objeto Student do par chave-valor
        students.push_back(student); // Adicionamos o objeto Student ao vetor students
    }

    ifstream file2("C:\\Users\\alexc\\CLionProjects\\ProjetoGerenciamentoHorarios\\data\\classes.csv");
    string line2;
    if (!file2.is_open()) {
        std::cerr << "Erro ao abrir o arquivo." << std::endl;
    }
    getline(file2, line2);
    while (getline(file2, line2)) {
        istringstream s2(line2);
        double starthour, duration;
        char comma;
        string weekday, classcode, uccode, type;

        if (std::getline(s2, classcode, ',') &&
            std::getline(s2, uccode, ',') &&
            std::getline(s2, weekday, ',') &&
            s2 >> starthour && s2.get() == ',' &&
            s2 >> duration && s2.get() == ',' &&
            std::getline(s2, type)) {
            Class newClass(classcode, duration, weekday, starthour, type, UC(uccode));
            addClass(newClass);
        }
    }
    file2.close();
}
//troca entre estudantes
bool System::Changingstudentsindifferentclasses(int studentid, string& from_class_id, string& to_class_id, string& uccode) {
    // Encontrar o estudante pelo ID
    auto studentIt = std::find_if(students.begin(), students.end(), [studentid](const Student& s) {
        return s.get_id() == studentid;
    });
    // Encontrar a classe de origem e a classe de destino
    auto fromClassIt = std::find_if(classes.begin(), classes.end(), [from_class_id, uccode](const Class& c) {
        return c.get_id() == from_class_id && c.get_uc().getUC() == uccode;
    });

    auto toClassIt = std::find_if(classes.begin(), classes.end(), [to_class_id, uccode](const Class& c) {
        return c.get_id() == to_class_id && c.get_uc().getUC() == uccode;
    });
    const Class& fromClass = *fromClassIt;
    const Class& toClass = *toClassIt;
    if(fromClass.get_uc().getUC() != toClass.get_uc().getUC()){
        cout << "To change classes, the source and destination classes must have the same Course Unit (UC)." << endl;
        return false;
    }
    // Iterar sobre as classes do estudante
    for (const auto& pair : studentIt->getclasses()) {
        if (pair.first == from_class_id && pair.second == uccode) {
            // O estudante já está na classe de origem, então não é necessário verificar o conflito.
            continue;
        } else {
            auto otherClassIt = std::find_if(classes.begin(), classes.end(), [&pair](const Class& c) {
                return c.get_id() == pair.first && c.get_uc().getUC() == pair.second;
            });

            if (otherClassIt != classes.end()) {
                const Class& otherClass = *otherClassIt;
                if (toClass.scheduleconflict(otherClass)) {
                    cout << "Conflito de horário detectado com a classe " << pair.first << ". Tente outra classe." << endl;
                    return false;
                }
            }
        }
    }
    cout << "Request accepted " << to_class_id << "." << endl;
    studentIt->wantstochange(from_class_id, to_class_id, uccode);
    if(change.verifyandchangetheclass(*studentIt)){
        cout << "Successfully changed to "<< to_class_id << "." << endl;
    }
    else{
        change.AddStudentToQueue(*studentIt);
        cout << "Waiting for another student to change" << endl;
    }
    return true;
}

void System::All_the_students_of_a_year_numeral(int year){
    std::set<int> studentids;
    for(Student& s : students){
        if(s.whichyear() == year){
            studentids.insert(s.get_id());
        }
    }
    for (const int& i : studentids) {
        cout << i << "--" << getstudentname(i) << endl;
    }
}
void System::All_the_students_of_a_year_alphabeticaly(int year) {
    std::map<std::string, int> studentNamesAndIds; // Usaremos um map para associar nomes de estudantes a números de estudantes
    for (Student& s : students) {
        if (s.whichyear() == year) {
            studentNamesAndIds[s.getname()] = s.get_id();
        }
    }
    for (const auto& entry : studentNamesAndIds) {
        cout << entry.second << "--" << entry.first << endl;
    }
}
void System::All_the_Student_of_a_uc_alphabeticaly(string uccode){
    std::set<string> studentNames; // Usaremos um set para garantir nomes de estudantes únicos e ordenado alfabeticamente
    for(Student s : students){
        for(const auto pair : s.getclasses()){
            if(pair.second == uccode){
                studentNames.insert(s.getname()); // Adicione o nome do estudante ao conjunto
                break;
            }
        }
    }
    for (const string& studentName : studentNames) {
        cout << getstudentid(studentName) << "--" << studentName  << endl;
    }
}
void System::All_the_students_of_a_uc_numeral(string uccode){
    std::set<int> studentids;                  //ordenado conforme o id do estudante
    for(Student s : students){
        for(const auto pair : s.getclasses()){
            if(pair.second == uccode){
                studentids.insert(s.get_id()); // Adicione o nome do estudante ao conjunto
                break;
            }
        }
    }
    for (const int& i : studentids) {
        cout << i << "--" << getstudentname(i) << endl;
    }
}
void System::All_the_students_of_a_class_numeral (string classid, string uccode){
    std::set<int> studentids;                  //ordenado conforme o id do estudante
    for(Student& s : students){
        for(const auto pair : s.getclasses()){
            if(s.hasClass(classid, uccode)){
                studentids.insert(s.get_id()); // Adicione o id do estudante ao conjunto
            }
        }
    }
    for (const int& i : studentids) {
        cout << i << "--" << getstudentname(i) << endl;
    }
}
void System::All_the_students_of_a_class_alphabeticaly(string classid, string uccode) {
    std::set<string> studentNames; // Usaremos um set para garantir nomes de estudantes únicos e ordenado alfabeticamente
    for (Student &s: students) {
        for (const auto pair: s.getclasses()) {
            if (s.hasClass(classid, uccode)) {
                studentNames.insert(s.getname()); // Adicione o nome do estudante ao conjunto
                break;
            }
        }
    }
    for (const string &studentName: studentNames) {
        cout << getstudentid(studentName) << "--" << studentName << endl;
    }
}

void System::classocuppation(string classid, string uccode){
    int nstudents = 0;
    for(Student& s : students){
        if(s.hasClass(classid, uccode)){
            nstudents++;
        }
    }
    cout << "The class " << classid << " has " << nstudents << " students in the Uc " << uccode << endl;
}

void System::ucocuppation(string uccode){
    int nstudents = 0;
    for(Student s : students){
        for(const auto pair : s.getclasses()){
            if(pair.second == uccode){
                nstudents++;
                break;
            }
        }
    }
    cout << "The Uc " << uccode << " has " << nstudents << " students enrolled" << endl;
}

void System::yearocuppation(int year){
    int nstudents = 0;
    for(Student s : students){
        if(s.whichyear() == year){
            nstudents++;
        }
    }
    cout << "The " << year << " year has " << nstudents << " students enrolled" << endl;
}

void System::ucsbystudents() {
    map<string, int> ucstudents;
    for(Student s : students){
        for(const auto pair : s.getclasses()){
            ucstudents[pair.first]++;
        }
    }
    if (ucstudents.empty()) {
        cout << "No UCs" << endl;
        return;
    }
    vector<pair<int, string>> ordereducs;
    for (const auto& pair2 : ucstudents) {
        ordereducs.emplace_back(pair2.second, pair2.first);
    }
    sort(ordereducs.begin(), ordereducs.end());
    int i = 1;
    cout << "UCs - number of students:" << endl;
    for (auto it = ordereducs.rbegin(); it != ordereducs.rend(); ++it) {
        cout << i << ": " << it->second << " - " << it->first << endl;
        i++;
    }
}

void System::studentsInAtLeastN_UCs(int n) {
    int count = 0;
    map<int, int> studentsucs;
    for(Student s : students){
        studentsucs[s.get_id()] = s.getclasses().size();;
    }
    for(const auto pair : studentsucs){
        if (pair.second >= n){
            count++;
        }
    }
    cout << "There are " << count << " stundents registered in at least " << n << " UCs" << endl;
}

void System::Schedule_of_a_Class(std::string id, std::string uc) {
    for(Class& c : classes){
        if(c.get_id() == id && c.get_uc().getUC() == uc){
            cout << "Weekday: " << c.get_Schedule() << endl;
        }
    }
}

struct Class_ {
    std::string dayofweek;
    std::string schedule;
    Class_(std::string& day, std::string& classSchedule) : dayofweek(day), schedule(classSchedule){}
};
struct DayOfWeekComparator {
    bool operator()(const std::string& day1, const std::string& day2) const {
        std::vector<std::string> orderedDaysOfWeek = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};

        // Encontre as posições dos dias da semana na sequência ordenada
        auto it1 = std::find(orderedDaysOfWeek.begin(), orderedDaysOfWeek.end(), day1);
        auto it2 = std::find(orderedDaysOfWeek.begin(), orderedDaysOfWeek.end(), day2);

        // Compare as posições dos dias da semana encontrados
        if (it1 != orderedDaysOfWeek.end() && it2 != orderedDaysOfWeek.end()) {
            return std::distance(orderedDaysOfWeek.begin(), it1) < std::distance(orderedDaysOfWeek.begin(), it2);
        } else {
            // Se algum dos dias não for encontrado, coloque-os no final
            return it1 != orderedDaysOfWeek.end();
        }
    }
};
void System::Schedule_of_a_student(int id) {
    // Mapa para armazenar classes organizadas por dia da semana usando o comparador personalizado
    std::map<std::string, std::queue<Class_>, DayOfWeekComparator> classesByDay;
    for (Student &s: students) {
        if (s.get_id() == id) { // Achou o estudante
            for (const auto& pair: s.getclasses()) { // ID por ID em todas as classes que o estudante está inscrito
                for (Class &c: classes) { // Passa por todas as classes
                    if (c.get_id() == pair.first && c.get_uc().getUC() == pair.second) {
                        std::string schedule = c.get_Schedule();
                        std::string dayOfWeek = extract_Day_Of_Week(schedule);
                        Class_ class1(dayOfWeek, schedule);
                        classesByDay[dayOfWeek].push(class1);
                    }
                }
            }
        }
    }
    for (auto& entry : classesByDay) {
        cout << "Classes on " << entry.first << endl;
        while (!entry.second.empty()) {
            Class_ class1 = entry.second.front();
            entry.second.pop();
            cout << "   " << class1.schedule << endl;
        }
    }
}
std::string System::extract_Day_Of_Week(string f){
    string day_of_week;
    istringstream iss(f);
    getline(iss, day_of_week, ' '); // Como o schedule envia uma string com os dados separados por espaços
    return day_of_week;                         //e o primeiro é o dia da semana; o getline para quando achar o espaço
}

bool System::scheduleconflict(string classid, string uccode, int studentid) {
    // Procura o estudante
    auto studentIt = std::find_if(students.begin(), students.end(), [studentid](const Student& s) {
        return s.get_id() == studentid;
    });

    if (studentIt != students.end()) {
        // Encontrou o estudante, agora procura as classes correspondentes
        auto classItT = std::find_if(classes.begin(), classes.end(), [classid, uccode](const Class& c) {
            return c.get_id() == classid && c.get_uc().getUC() == uccode && c.get_type() == "T";
        });

        auto classItTP = std::find_if(classes.begin(), classes.end(), [classid, uccode](const Class& c) {
            return c.get_id() == classid && c.get_uc().getUC() == uccode && c.get_type() == "TP";
        });
        if (classItT != classes.end()) {
            const Class& c1 = *classItT;
            for (const auto& pair : studentIt->getclasses()) {
                auto c2It = std::find_if(classes.begin(), classes.end(), [&pair](const Class& c) {
                    return c.get_id() == pair.first && c.get_uc().getUC() == pair.second;
                });
                if (c2It != classes.end()) {
                    const Class& c2 = *c2It;
                    if (c1.scheduleconflict(c2)) {
                        return true;
                    }
                }
            }
        }
        if (classItTP != classes.end()) {
            const Class& c1 = *classItTP;
            for (const auto& pair : studentIt->getclasses()) {
                auto c2It = std::find_if(classes.begin(), classes.end(), [&pair](const Class& c) {
                    return c.get_id() == pair.first && c.get_uc().getUC() == pair.second;
                });
                if (c2It != classes.end()) {
                    const Class& c2 = *c2It;
                    if (c1.scheduleconflict(c2)) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool System::adduc(string& uccode, int& studentid) {
    if(itnotispossibletoaddmore(studentid)){
        return false;
    }
    auto studentIt = std::find_if(students.begin(), students.end(), [studentid](const Student& s) { return s.get_id() == studentid; });
    vector<pair<Class, Class>> trying;
    // Encontre todas as classes "T" e "TP" com o mesmo código de UC.
    vector<Class> matchingTClasses;
    vector<Class> matchingTPClasses;
    for (const Class& c : classes) {
        if (c.get_uc().getUC() == uccode) {
            if (c.get_type() == "T") {
                matchingTClasses.push_back(c);
            } else if (c.get_type() == "TP") {
                matchingTPClasses.push_back(c);
            }
        }
    }
    bool classPairAdded = false;
    // Combine as classes "T" com as classes "TP" no vetor de pares 'trying'.
    for (const Class& c1 : matchingTClasses) {
        for (const Class& c2 : matchingTPClasses) {
            if(c1.get_id() == c2.get_id()){
                continue;   //tem q ter o id igual
            }
            if (scheduleconflict(c1.get_id(), uccode, studentid) || scheduleconflict(c2.get_id(), uccode, studentid)) {
                continue; // Conflito de horário, continue com o próximo par.
            }
            if(classPairAdded){
                break;
            }
            studentIt->addclass(c1.get_id(), uccode);
            cout << "Added to T class " << c1.get_id() << " for UC code: " << uccode << endl;
            cout << "Added to TP class " << c2.get_id() << " for UC code: " << uccode << endl;
            studentIt->push_added_uc(uccode);
            addingtostack(studentIt->get_id(), "add_uc");
            classPairAdded =  true;
        }
        if(classPairAdded){
            break;
        }
    }
    if(classPairAdded){
        return true;
    }
    cout << "No compatible classes" << endl;
    return false; // Não encontrou um par de classes compatíveis.
}
void System::removeuc(string& uccode, int& studentid) {
    auto studentIt = std::find_if(students.begin(), students.end(),[studentid](const Student &s) { return s.get_id() == studentid; });
    studentIt->removeuc(uccode);
    studentIt->push_removed_uc(uccode);
    for(auto pair : studentIt->getclasses()){
        if (pair.second == uccode) {
            Removingastudnetinaclass(studentid, pair.first, uccode);
        }
    }
    addingtostack(studentIt->get_id(), "remove_uc");
    cout << "Removed the classes from this UC code: " << uccode << endl;
}
void System::changeuc(string& from_uccode, int& studentid, string& to_uccode){
    auto studentIt = std::find_if(students.begin(), students.end(),[studentid](const Student &s) { return s.get_id() == studentid; });
    removeuc(from_uccode, studentid);
    if(!adduc(to_uccode, studentid)){        //caso nao puder adicionar na nova turma
        adduc(from_uccode, studentid);      //tem q entrar na uc que saiu
        cout << "Not able to change uc" << endl;
    }
    else{
        addingtostack(studentIt->get_id(), "change_uc");
        studentIt->push_removed_uc(from_uccode);
        studentIt->push_added_uc(to_uccode);
        cout << "Changed UC" << endl;
    }
}
void System::changeclassonly(int& idstudent, string& from_class, string& to_class, string& uccode3) {
    auto studentIt = std::find_if(students.begin(), students.end(), [idstudent](const Student& s) { return s.get_id() == idstudent; });
    Removingastudnetinaclass(idstudent, from_class, uccode3);
    if(!Addingastudentinaclass(idstudent, to_class, uccode3) or !checkBalance()){
        Addingastudentinaclass(idstudent, from_class, uccode3);
        cout << "Not able to change class" << endl;
    }
    else{
        addingtostack(studentIt->get_id(), "change_class");
        studentIt->push_removed_class(from_class, uccode3);
        studentIt->push_added_class(to_class, uccode3);
        cout << "Changed class" << endl;
    }
}
bool System::Addingastudentinaclass(int studentid, const std::string& classid, const std::string& uccode) {
    auto studentIt = std::find_if(students.begin(), students.end(),[studentid](const Student &s)
    { return s.get_id() == studentid; });
    // Verifique se o estudante já está na classe
    if (studentIt->hasClass(classid, uccode)) {
        cout << "Student already in the class" << endl;
        return false;
    }
    // Verifique a capacidade da classe
    Class* targetClassT = nullptr;
    Class* targetClassTP = nullptr;
    for (Class& c : classes) {
        if (c.get_id() == classid && c.get_uc().getUC() == uccode && c.get_type() == "T") {
            targetClassT = &c;
        }
        else if(c.get_id() == classid && c.get_uc().getUC() == uccode && c.get_type() == "TP"){
            targetClassTP = &c;

        }
    }
    if (currentcapacytiofaclass(classid, uccode, "TP") == targetClassTP->getcapacytimax()
    or currentcapacytiofaclass(classid, uccode, "T") == targetClassT->getcapacytimax()) {
        cout << "Class is full (capacity exceeded)" << endl;
        return false;
    }
    // Verifique se há conflito de horário
    for (const auto& pair : studentIt->getclasses()) {
        if (scheduleconflict(classid, pair.second, studentid) ) {
            cout << "Class schedule conflict" << endl;
            cout << "Try again" << endl;
            return false;
        }
    }
    // Tudo está correto, adicione o estudante à classe e atualize os saldos
    studentIt->addclass(targetClassT->get_id(), uccode);
    cout << "Added to the class" << classid  << endl;
    if(!checkBalance()){    //cheka com a atualização feita addclass
        Removingastudnetinaclass(studentid, classid, uccode);
        cout << "Removing the class" << classid << endl;
        return false;
    }
    //atualiza o saldo depois de verificar se realmente pode mudar
    studentIt->push_added_class(classid, uccode);
    addingtostack(studentIt->get_id(), "add_class"); //acho q o problema está aaqui
    return true;
}
void System::Removingastudnetinaclass(int idstudent, const std::string& classid, const std::string& uccode) {
    auto studentIt = std::find_if(students.begin(), students.end(),[idstudent](const Student &s) { return s.get_id() == idstudent; });
    // Verifica se o estudante está na classe que deseja remover
    auto it = std::find(studentIt->getclasses().begin(), studentIt->getclasses().end(), std::make_pair(classid, uccode));
    if (it == studentIt->getclasses().end()) {
        cout << "Student is not in the class" << endl;
        return; // O estudante não está na classe, nada a fazer
    }
    if(!checkBalance()){
        Addingastudentinaclass(idstudent, classid, uccode);
        return;
    }
    studentIt->removeclass(classid, uccode);
    addingtostack(studentIt->get_id(), "remove_class");
}

bool System::checkBalance()
{
    int maxCapacity = -1;
    int minCapacity = 100;
    for (const auto& entry : get_classCapacities()) {
        if (entry.second > maxCapacity) {
            maxCapacity = entry.second;
        }
        if (entry.second < minCapacity) {
            minCapacity = entry.second;
        }
    }

    if (maxCapacity - minCapacity < 4) {
        cout << "Balance OK" << endl;
        return true;
    } else {
        cout << "Balance not OK" << endl;
        return false;
    }
}
bool System::itnotispossibletoaddmore(int studentid){
    auto studentIt = std::find_if(students.begin(), students.end(), [studentid](const Student& s) {return s.get_id() == studentid;});
    if(studentIt->numberofucs() >= 7){  //se tiver mais ou igual a sete não é possivel adicionar mais
        cout << "Not possible to add more, please remove one UC" << endl;
        return true;
    }
    return false;
}

std::list<Class> System::get_classes_system() {
    return classes;
}

void System::addingtostack(int s1, string s2) {
    pairStack.push(make_pair(s1, s2));
}
void System::undolastaction(System& system) {
    std::pair<int, std::string> lastAction = pairStack.top();  // Obtém o par no topo da pilha
    int studentId = lastAction.first;
    std::string action = lastAction.second;
    auto studentIt = std::find_if(students.begin(), students.end(), [studentId](const Student& s) {
        return s.get_id() == studentId;
    });
    pairStack.pop();  // Remove o par no topo da pilha

    if (action == "add_class") {
        // Obtem a classe adicionada do topo da pilha added_classes
        std::pair<std::string, std::string> addedClass = studentIt->get_top_added_classes();
        studentIt->pop_added_class();  // Remove a classe do topo da pilha
        // Desfaz a adição da classe
        studentIt->removeclass( addedClass.first, addedClass.second);
        cout << "Successfully undone action (add class)" << endl;
    }

    else if(action == "remove_class"){
        std::pair<std::string, std::string> removedClass =studentIt->get_top_removed_classes();
        studentIt->pop_removed_class();  // Remove a classe do topo da pilha
        // Desfaz a adição da classe
        studentIt->addclass( removedClass.first, removedClass.second);
        cout << "Successfully undone action (remove class)" << endl;
    }
    else if(action == "add_uc"){
        std::string addeduc =studentIt->get_top_added_ucs();
        studentIt->pop_added_uc();
        studentIt->removeuc(addeduc);
        cout << "Successfully undone action (add uc)" << endl;
    }
    else if(action == "remove_uc"){
        std::string removeduc = studentIt->get_top_removed_ucs();
        studentIt->pop_removed_uc();
        studentIt->adduc(removeduc, system);   //fazer depois
        cout << "Successfully undone action (remove uc)" << endl;
    }
    else if(action == "change_class"){
        std::pair<std::string, std::string> from_class = studentIt->get_top_removed_classes();
        studentIt->pop_removed_class();
        std::pair<std::string, std::string> to_class = studentIt->get_top_added_classes();
        studentIt->pop_added_class();
        studentIt->addclass(from_class.first, from_class.second);
        studentIt->removeclass(to_class.first, to_class.second);
        cout << "Successfully undone action (change class)";
    }
    else if(action == "change_uc"){
        std::string from_uc = studentIt->get_top_removed_ucs();
        studentIt->pop_removed_uc();
        std::string to_uc = studentIt->get_top_added_ucs();
        studentIt->pop_added_uc();
        studentIt->adduc(from_uc, system);
        studentIt->removeuc(to_uc);
        cout << "Successfully undone action (change uc)";
    }
    //fazer para caso o Student seja adicionado, removido, trocado de uc
    //fazer para caso o student seja adicionado, removido, trocado de classe
}
bool System::checkifitsempty() {
    return pairStack.empty();
}

int System::currentcapacytiofaclass(string classid, string uccode, string type) {
    int nstudents = 0;
    // Crie um conjunto (std::set) para rastrear os IDs de estudantes únicos
    std::set<int> uniqueStudentIDs;
    // Percorra as classes para encontrar aquelas que correspondem aos critérios]
    for (const Class &c : classes) {
        if (c.get_id() == classid && c.get_uc().getUC() == uccode && c.get_type() == type) {
            // Esta classe corresponde aos critérios, agora vamos verificar os estudantes
            for ( Student &s : students) {
                if (s.hasClass(classid, uccode)) {
                    int studentID = s.get_id();
                    // Verifique se o estudante já está no conjunto de IDs únicos
                    if (uniqueStudentIDs.find(studentID) == uniqueStudentIDs.end()) {
                        uniqueStudentIDs.insert(studentID);
                        nstudents++;
                    }
                }
            }
            break;
        }
    }
    return nstudents;
}

void System::savealterations() {
    ofstream saida("C:\\Users\\alexc\\CLionProjects\\PROJECTEAD\\data\\students_classes_modificado.csv",
                   std::ios::out | std::ios::trunc);    //cria um novo arquivo caso não exista e rescreve caso exista
    saida << "StudentCode,StudentName,UcCode,ClassCode" << endl;
    for (Student s : students){
        for (auto pair : s.getclasses()){
            saida << s.get_id() << "," << s.getname() << "," << pair.second << "," << pair.first << endl;
        }
    }
}
