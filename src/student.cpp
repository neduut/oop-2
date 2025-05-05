#include "student.h"
#include "utils.h"
#include "constants.h"

Student::Student()
    : firstName_(""), lastName_(""), marks_(), examMark_(0), avgFinal_(0.0), medianFinal_(0.0) {}

Student::Student(std::istream& is) {
    readStudent(is);
}

std::istream& Student::readStudent(std::istream& is) {
    is >> firstName_ >> lastName_;
    int mark;
    marks_.clear();
    while (is >> mark) {
        marks_.push_back(mark);
    }
    examMark_ = marks_.back();
    marks_.pop_back();

    return is;
}

void Student::readInput(std::vector<Student>& students, char menuChoice) {
    students.reserve(10000);
    string choice;
    do {
        string firstName = GetFirstName(menuChoice);
        string lastName = GetLastName(menuChoice);
        vector<int> marks = GetHomeworkMarks(menuChoice);
        int examMark = GetExamMark(menuChoice);

        Student temp;
        temp.setFirstName(firstName);
        temp.setLastName(lastName);
        temp.setMarks(marks);
        temp.setExamMark(examMark);
        temp.calculateFinalMarks();
        students.push_back(temp);

        cout << ADD_ANOTHER_STUDENT << endl;
        choice = getYesNo();

    } while (choice == "taip");

    students.shrink_to_fit();
}

void Student::readFromFile(std::vector<Student>& students, int fileSize) {
    try {
        students.reserve(fileSize);

        std::ifstream file("files/studentai" + std::to_string(fileSize) + ".txt");
        if (!file) {
            throw std::runtime_error(FILE_OPEN_ERROR);
        }

        std::string line;
        std::getline(file, line);

        Student temp;
        while (std::getline(file, line)) {
            std::istringstream ss(line);
            if (ss) {
                temp.readStudent(ss);
                temp.calculateFinalMarks();
                students.push_back(temp);

            } else {
                std::cerr << FILE_READ_ERROR << std::endl;
            }
        }

        file.close();
        students.shrink_to_fit();
        std::cout << FILE_READ_SUCCESS << std::endl;

    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

float Student::average(const std::vector<int>& marks) const {
    if (marks.empty()) {
        return 0.0;
    }
    float sum = std::accumulate(marks.begin(), marks.end(), 0.0);
    return sum / marks.size();
}

float Student::median(const std::vector<int>& marks) const {
    std::vector<int> sortedMarks = marks;
    std::sort(sortedMarks.begin(), sortedMarks.end());
    size_t size = sortedMarks.size();
    if (size == 0) {
        return 0.0;
    }
    if (size % 2 == 0) {
        return (sortedMarks[size / 2 - 1] + sortedMarks[size / 2]) / 2.0;
    } else {
        return sortedMarks[size / 2];
    }
}

void Student::calculateFinalMarks() {
    avgFinal_ = 0.4 * average(marks_) + 0.6 * examMark_;
    medianFinal_ = median(marks_);
}

void sortStudents(std::vector<Student>& students, char sortType) {
    if (sortType == 1) {
        stable_sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
            return a.getFirstName() < b.getFirstName();
        });
    } else if (sortType == 2) {
        stable_sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
            return a.getLastName() < b.getLastName();
        });
    } else if (sortType == 3) {
        stable_sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
            return a.getAvgFinal() < b.getAvgFinal();
        });
    } else {
        stable_sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
            return a.getMedianFinal() < b.getMedianFinal();
        });
    }
}

