#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "mylib.h"
#include "student.h"

void handleProgramMenu(vector<Student>& students);
void handleTestMenu();
void generateFile(int size);
void groupStudents1(vector<Student>& students, vector<Student>& kietiakai, vector<Student>& vargsiukai, int groupType);
void groupStudents2(vector<Student>& students, vector<Student>& kietiakai, vector<Student>& vargsiukai, int groupType);
void groupStudents3(vector<Student>& students, vector<Student>& kietiakai, vector<Student>& vargsiukai, int groupType);
void printToConsole(vector<Student>& kietiakai, vector<Student>& vargsiukai);
void printToFile(vector<Student>& students, const string& fileName);
void fileGenTest(int size);
void programTest(int size);
void vectorTest(int size);
void strategies(int size, int strategy);

#endif  