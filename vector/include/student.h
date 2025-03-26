#ifndef STUDENT_H
#define STUDENT_H

#include "mylib.h"

class Student {
private:
    std::string firstName_;
    std::string lastName_;
    std::vector<int> marks_;
    int examMark_;
    double avgFinal_;
    double medianFinal_;

public:
    Student();  
    Student(std::string firstName, std::string lastName, std::vector<int> marks, int examMark, double avgFinal, double medianFinal);
    ~Student() = default;

    static void readInput(std::vector<Student>& students, char menuChoice); 
    static void readFromFile(std::vector<Student>& students, int fileSize); 
    void calculateFinalMarks();
    
    std::string getFirstName() const { return firstName_; }
    std::string getLastName() const { return lastName_; }
    std::vector<int> getHomeworkMarks() const { return marks_; }
    int getExamMark() const { return examMark_; }
    double getAvgFinal() const { return avgFinal_; }
    double getMedianFinal() const { return medianFinal_; }

    void setFirstName(std::string firstName) { firstName_ = firstName; }
    void setLastName(std::string lastName) { lastName_ = lastName; }
    void setMarks(std::vector<int> marks) { marks_ = marks; }
    void setExamMark(int examMark) { examMark_ = examMark; }
    void setAvgFinal(double avgFinal) { avgFinal_ = avgFinal; }
    void setMedianFinal(double medianFinal) { medianFinal_ = medianFinal; }
};

void sortStudents(std::vector<Student>& students, char sortType);

#endif
