#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "mylib.h"

struct Student {
    std::string firstName;
    std::string lastName;
    std::vector<int> marks;
    int examMark;
    double avgFinal;
    double medianFinal;
};

void handleProgramMenu(vector<Student>& students);
void handleTestMenu();
void generateFile(int size);
void readInput(vector<Student>& students, char menuChoice);
void readFromFile(vector<Student>& students, int fileSize);       
double averageFinalMark(const vector<int>& marks, int examMark);
double medianFinalMark(const vector<int>& marks, int examMark);
void sortStudents(vector<Student>& students, char sortType);
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