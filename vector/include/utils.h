#ifndef UTILS_H
#define UTILS_H

#include "mylib.h"

// requests
string getYesNo();
int getSortType();
int getGroupType();
int getPrintType();
int getMenuChoice();
int getProgramMenuChoice();
int getTestMenuChoice();
int getFileSize();
string GetFirstName(char menuChoice);
string GetLastName(char menuChoice);
int GetExamMark(char menuChoice);
vector<int> GetHomeworkMarks(char menuChoice);

// validations
bool isNameValid(string name);
bool isMarkValid(string mark);
bool isChoiceValid(string choice);

// random generators
string getRandomFirstName();
string getRandomLastName();
int getRandomMark();

#endif