#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>

class Student {
private:
    std::string firstName_;
    std::string lastName_;
    std::vector<int> marks_;
    int examMark_;
    float avgFinal_;
    float medianFinal_;

    float average(const std::vector<int>& marks) const;
    float median(const std::vector<int>& marks) const;

public:
    Student();
    Student(std::istream& is);
    ~Student() {
        firstName_.clear();
        lastName_.clear();
        marks_.clear();
        examMark_ = 0;
        avgFinal_ = 0.0;
        medianFinal_ = 0.0;
    }

    std::string getFirstName() const { return firstName_; }
    std::string getLastName() const { return lastName_; }
    const std::vector<int>& getHomeworkMarks() const { return marks_; }
    int getExamMark() const { return examMark_; }
    float getAvgFinal() const { return avgFinal_; }
    float getMedianFinal() const { return medianFinal_; }

    void setFirstName(std::string firstName) { firstName_ = firstName; }
    void setLastName(std::string lastName) { lastName_ = lastName; }
    void setMarks(std::vector<int> marks) { marks_ = marks; }
    void setExamMark(int examMark) { examMark_ = examMark; }

    static void readInput(std::vector<Student>& students, char menuChoice);
    static void readFromFile(std::vector<Student>& students, int fileSize);
    std::istream& readStudent(std::istream&);
    void calculateFinalMarks(); 
};

void sortStudents(std::vector<Student>& students, char sortType);

