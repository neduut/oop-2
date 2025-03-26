#include "mylib.h"
#include "utils.h"
#include "functions.h"
#include "student.h"
#include <windows.h>

int main() {

    // enable lithuanian characters in console
    SetConsoleOutputCP(65001);

    vector<Student> students;

    // test or program
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

