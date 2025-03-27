#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "mylib.h"
#include "student.h"

void handleProgramMenu(vector<Student>& students);
void handleTestMenu();
void generateFile(int size);
void groupStudents(vector<Student>& students, vector<Student>& kietiakai, vector<Student>& vargsiukai, int groupType);
void printToConsole(vector<Student>& kietiakai, vector<Student>& vargsiukai);
void printToFile(vector<Student>& students, const string& fileName);
void fileGenTest(int size);
void programTest(int size);

#endif  