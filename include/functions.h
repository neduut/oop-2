#pragma once
#include "mylib.h"
#include "student.h"
#include <cassert>

void handleProgramMenu(vector<Student>& students);
void handleTestMenu();
void generateFile(int size);
void groupStudents(vector<Student>& students, vector<Student>& kietiakai, vector<Student>& vargsiukai, int groupType);
void printToConsole(vector<Student>& kietiakai, vector<Student>& vargsiukai);
void printToFile(vector<Student>& students, const string& fileName);
void fileGenTest(int size);
void programTest(int size);
void testRuleOfFive();
//void testZmogausClass();