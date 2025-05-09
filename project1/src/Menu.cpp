#include "../include/Menu.h"

void Menu::start(System system) {
    while(true) {
        cout << endl << "Menu:" << endl;
        cout << "1- Get all the students of a class, year or course" << endl;
        cout << "2- Schedule of a student" << endl;
        cout << "3- Schedule of a class" << endl;
        cout << "4- Occupation of a class, year or course" << endl;
        cout << "5- Statistics" << endl;
        cout << "6- Edit Classes" << endl;
        cout << "7- Edit UCs" << endl;
        cout << "8- Undo the last edit" << endl;
        cout << "9- Save alterations" << endl;
        cout << "Press an number to continue or press 0 to quit" << endl;


        int choise;
        cin >> choise;

        if(choise == 1) {
            cout << "1-class, 2-course, 3-year";
            int subchoise;
            cin >> subchoise;
            if(subchoise == 1) {
                cout << "Orderly" << endl << "1- alphabetically" << endl << "2- numeral" << endl;
                int num;
                string classid, uccode;
                cin >> num;
                if (num == 1) {
                    cout << "Enter the class id:" << endl;
                    cin >> classid;
                    cout << "Enter the class uc:" << endl;
                    cin >> uccode;
                    system.All_the_students_of_a_class_alphabeticaly(classid, uccode);
                }
                if (num == 2) {
                    cout << "Enter the class id:" << endl;
                    cin >> classid;
                    cout << "Enter the class uc:" << endl;
                    cin >> uccode;
                    system.All_the_students_of_a_class_numeral(classid, uccode);
                }
            }
            else if(subchoise == 2){
                cout << "Orderly" << endl << "1- alphabetically" << endl << "2- numeral" << endl;
                int num;
                string uccode;
                cin >> num;
                if (num == 1) {
                    cout << "Enter the uc code:" << endl;
                    cin >> uccode;
                    system.All_the_students_of_a_uc_numeral(uccode);
                }
                else if(num == 2){
                    cout << "Enter the uc code:" << endl;
                    cin >> uccode;
                    system.All_the_Student_of_a_uc_alphabeticaly(uccode);
                }
            }
            else if(subchoise == 3){
                cout << "Orderly" << endl << "1- alphabetically" << endl << "2- numeral" << endl;
                int num, year;
                string classid, uccode;
                cin >> num;
                if(num == 1){
                    cout << "Enter the year: (1, 2, 3)" << endl;
                    cin >> year;
                    system.All_the_students_of_a_year_alphabeticaly(year);           //possiveis inputs 1,2,3 para o primeiro, segundo e terceiro ano
                }
                else if(num == 2){
                    cout << "Enter the year: (1, 2, 3)" << endl;
                    cin >> year;
                    system.All_the_students_of_a_year_numeral(year);                 //possiveis inputs 1,2,3 para o primeiro, segundo e terceiro ano
                }

            }
        }

        else if(choise == 2){
            cout << "Enter the student id:" << endl;
            int c1;
            cin >> c1;
            system.Schedule_of_a_student(c1);
        }

        else if(choise == 3){
            cout << "Enter the class id:" << endl;
            string c1;
            cin >> c1;
            cout << "Enter the class uccode:" << endl;
            string c2;
            cin >> c2;
            system.Schedule_of_a_Class(c1, c2);
        }

        else if(choise == 4){
            cout << "1-class, 2-course, 3-year";
            int subchoise;
            cin >> subchoise;
            if(subchoise == 1){
                string classid, uccode;
                cout << "Enter the class id:" << endl;
                cin >> classid;
                cout << "Enter the class uc:" << endl;
                cin >> uccode;
                system.classocuppation(classid, uccode);
            }
            if(subchoise == 2){
                string uccode;
                cout << "Enter the uc code:" << endl;
                cin >> uccode;
                system.ucocuppation(uccode);
            }
            if(subchoise == 3){
                int year;
                cout << "Enter the year:" << endl;
                cin >> year;
                system.yearocuppation(year);
            }
        }

        else if(choise == 5){
            cout << "1- Order UCs by the number of enrolled students" << endl
                 << "2- Consult the number of students registered in at least n UCs" << endl;
            int subchoise;
            cin >> subchoise;
            if(subchoise == 1){
                system.ucsbystudents();
            }
            else if(subchoise == 2){
                cout << "Registered in how many UCs?" << endl;
                int n;
                cin >> n;
                system.studentsInAtLeastN_UCs(n);
            }

        }

        else if(choise == 6){
            int idstudent;
            string classid1, classid2, classid3, classid4;
            string uccode1, uccode2, uccode3;
            cout << "Enter the student id:" << endl;
            cin >> idstudent;
            system.Schedule_of_a_student(idstudent);
            int num;
            cout << "1-add" << endl << "2-remove" << endl << "3-change (request to change a student from a class with another student from another class)" << endl << "4-change (change a student from class to another class)" << endl;
            cin >> num;
            switch (num){
                case 1:         //IMPORTANTE VER SE O HORARIO ENTRA EM COMFLITO ANTES
                    cout << "Enter the class you want to add the student:" << endl;
                    cin >> classid1;
                    cout << "Enter the uccode of the class:" << endl;
                    cin >> uccode1;
                    system.Addingastudentinaclass(idstudent, classid1, uccode1);
                    break;
                case 2:
                    cout << "Enter the class you want to remove the student:" << endl;
                    cin >> classid2;
                    cout << "Enter the uccode of the class:" << endl;
                    cin >> uccode2;
                    system.Removingastudnetinaclass(idstudent, classid2, uccode2);
                    break;
                case 3:
                    cout << "Enter the class you want to remove the student:" << endl;
                    cin >> classid3;
                    cout << "Enter the class you want to add the student" << endl;
                    cin >> classid4;
                    cout << "Enter the uccode of the classes:" << endl;
                    cin >> uccode3;
                    system.Changingstudentsindifferentclasses(idstudent, classid3, classid4, uccode3);
                    break;
                case 4:
                    cout << "Enter the class you want to remove the student:" << endl;
                    cin >> classid3;
                    cout << "Enter the class you want to add the student" << endl;
                    cin >> classid4;
                    cout << "Enter the uccode of the classes:" << endl;
                    cin >> uccode3;
                    system.changeclassonly(idstudent, classid3, classid4, uccode3);
                    break;
            }
        }

        else if(choise == 7) {
            int idstudent;
            string uccode1, uccode2, uccode3, uccode4;
            cout << "Enter the student id:" << endl;
            cin >> idstudent;
            system.Schedule_of_a_student(idstudent);
            int num;
            cout << "1-add" << endl << "2-remove" << endl << "3-change" << endl;
            cin >> num;
            switch (num) {
                case 1:
                    if(system.itnotispossibletoaddmore(idstudent)){
                        cout << "Max of ucs"<< endl;
                        break;
                    }
                    cout << "Enter the UC you want to add the student:" << endl;
                    cin >> uccode1;
                    system.adduc(uccode1, idstudent);
                    break;
                case 2:
                    cout << "Enter the UC you want to remove the student:" << endl;
                    cin >> uccode2;
                    system.removeuc(uccode2, idstudent);
                    break;
                case 3:
                    cout << "Enter the UC you want to remove the student:" << endl;
                    cin >> uccode3;
                    cout << "Enter the UC you want to add the student:" << endl;
                    cin >> uccode4;
                    system.changeuc(uccode3, idstudent, uccode4);
                    break;
            }
        }

        else if(choise == 8){
            if(!system.checkifitsempty()){
                system.undolastaction(system);
            }
            else{
                cout << "Nothing to undo" << endl;
            }
        }
        else if(choise == 9){
            system.savealterations();
            cout << "Saving alterations" << endl;
        }

        else if(choise == 0){
            break;
        }
    }
}
