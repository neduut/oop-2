#include "mylib.h"
#include "utils.h"
#include "functions.h"
#include "student.h"
//sutvarkyt kad visom sistemom veiktu simboliai
#ifdef _WIN32
#include <windows.h>
#endif

int main() {
    #ifdef _WIN32
    SetConsoleOutputCP(65001); 
    #endif

    vector<Student> students;

    int choice = getMenuChoice();

    if (choice == 1) {
        handleProgramMenu(students);
    } else if (choice == 2) {
        handleTestMenu();
    } else {
        cout << "Kaip sau nori.\n";
    }

    return 0;
}

