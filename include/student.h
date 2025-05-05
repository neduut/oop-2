#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>

extern int dstCount; // for destructor test

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
    Student(); // default constructor
    Student(std::istream& is); // constructor with input stream

    // Rule of Five
    Student(const Student& other); // copy constructor
    Student& operator=(const Student& other); // copy operator
    Student(Student&& other) noexcept; // move constructor
    Student& operator=(Student&& other) noexcept; // move operator
    ~Student(); // destructor

    // getters
    std::string getFirstName() const { return firstName_; }
    std::string getLastName() const { return lastName_; }
    const std::vector<int>& getHomeworkMarks() const { return marks_; }
    int getExamMark() const { return examMark_; }
    float getAvgFinal() const { return avgFinal_; }
    float getMedianFinal() const { return medianFinal_; }

    // setters
    void setFirstName(std::string firstName) { firstName_ = firstName; }
    void setLastName(std::string lastName) { lastName_ = lastName; }
    void setMarks(std::vector<int> marks) { marks_ = marks; }
    void setExamMark(int examMark) { examMark_ = examMark; }

    // methods
    std::istream& readStudent(std::istream&);
    static void readInput(std::vector<Student>& students, char menuChoice);
    static void readFromFile(std::vector<Student>& students, int fileSize);
    void calculateFinalMarks(); 

    // operators
    friend std::ostream& operator<<(std::ostream& os, const Student& student);
    friend std::istream& operator>>(std::istream& is, Student& student);
};

void sortStudents(std::vector<Student>& students, char sortType);

