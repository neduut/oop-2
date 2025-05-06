#pragma once
#include "zmogus.h"
#include <vector>
#include <numeric>
#include <algorithm>

extern int dstCount; // for destructor test

class Student : public Zmogus {
private:
    std::vector<int> marks_;
    int examMark_;
    float avgFinal_;
    float medianFinal_;

    // private methods
    float average(const std::vector<int>& marks) const;
    float median(const std::vector<int>& marks) const;

public:
    // constructors 
    Student();
    Student(std::istream& is);
    /*Student(const std::string& firstName, const std::string& lastName, const std::vector<int>& marks, int examMark)
        : Zmogus(firstName, lastName), marks_(marks), examMark_(examMark) {
        calculateFinalMarks();
    }*/

    // rule of five
    Student(const Student& other); // copy constructor
    Student& operator=(const Student& other); // copy assignment operator
    Student(Student&& other) noexcept; // move constructor
    Student& operator=(Student&& other) noexcept; // move assignment operator
    ~Student(); // destructor

    // getters
    const std::vector<int>& getHomeworkMarks() const { return marks_; }
    int getExamMark() const { return examMark_; }
    float getAvgFinal() const { return avgFinal_; }
    float getMedianFinal() const { return medianFinal_; }
    
    // setters
    void setMarks(std::vector<int> marks) { marks_ = marks; }
    void setExamMark(int examMark) { examMark_ = examMark; }

    // implementation of virtual functions
    void print(std::ostream& os) const override;
    void read(std::istream& is) override;

    // methods
    std::istream& readStudent(std::istream& is);
    void calculateFinalMarks();
    static void readInput(std::vector<Student>& students, char menuChoice);
    static void readFromFile(std::vector<Student>& students, int fileSize);
};

void sortStudents(std::vector<Student>& students, char sortType);