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

    float average(const std::vector<int>& marks) const;
    float median(const std::vector<int>& marks) const;

public:
    // constructors 
    Student();
    Student(std::istream& is);

    // rule of five
    Student(const Student& other); // copy constructor
    Student& operator=(const Student& other); // copy assignment operator
    Student(Student&& other) noexcept; // move constructor
    Student& operator=(Student&& other) noexcept; // move assignment operator
    ~Student(); // destructor

    // etters/setters
    const std::vector<int>& getHomeworkMarks() const { return marks_; }
    int getExamMark() const { return examMark_; }
    float getAvgFinal() const { return avgFinal_; }
    float getMedianFinal() const { return medianFinal_; }
    void setMarks(std::vector<int> marks) { marks_ = std::move(marks); }
    void setExamMark(int examMark) { examMark_ = examMark; }

    // implementations of virtual methods from Zmogus class
    std::istream& read(std::istream& is) override;
    std::ostream& print(std::ostream& os) const override;

    // operators
    friend std::ostream& operator<<(std::ostream& os, const Student& student);
    friend std::istream& operator>>(std::istream& is, Student& student);

    // other methods
    void calculateFinalMarks();
    static void readInput(std::vector<Student>& students, char menuChoice);
    static void readFromFile(std::vector<Student>& students, int fileSize);
};

void sortStudents(std::vector<Student>& students, char sortType);