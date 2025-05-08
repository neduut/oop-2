#include "student.h"
#include "utils.h"
#include "constants.h"

int dstCount = 0;

// default constructor
Student::Student() 
    : Zmogus(), examMark_(0), avgFinal_(0.0), medianFinal_(0.0) {}

// constructor with input stream
Student::Student(std::istream& is) : Zmogus() {
    read(is);
}

// copy constructor
Student::Student(const Student& other)
    :  Zmogus(other), 
    marks_(other.marks_),
    examMark_(other.examMark_), 
    avgFinal_(other.avgFinal_), 
    medianFinal_(other.medianFinal_) {}

// copy assignment operator
Student& Student::operator=(const Student& other) {
    if (this != &other) {
        Zmogus::operator=(other);
        marks_ = other.marks_;
        examMark_ = other.examMark_;
        avgFinal_ = other.avgFinal_;
        medianFinal_ = other.medianFinal_;
    }
    return *this;
}

// move constructor
Student::Student(Student&& other) noexcept
    : Zmogus(std::move(other)),  
      marks_(std::move(other.marks_)), 
      examMark_(other.examMark_), 
      avgFinal_(other.avgFinal_), 
      medianFinal_(other.medianFinal_) {

        other.examMark_ = 0;
        other.avgFinal_ = 0.0;
        other.medianFinal_ = 0.0;
        other.firstName_.clear();
        other.lastName_.clear();
      }

// move assignment operator
Student& Student::operator=(Student&& other) noexcept {
    if (this != &other) {
        Zmogus::operator=(std::move(other)); 
        marks_ = std::move(other.marks_);
        examMark_ = other.examMark_;
        avgFinal_ = other.avgFinal_;
        medianFinal_ = other.medianFinal_;
        
        other.examMark_ = 0;
        other.avgFinal_ = 0.0;
        other.medianFinal_ = 0.0;
        other.firstName_.clear();  
        other.lastName_.clear(); 
    }
    return *this;
}

// implementation of virtual read function
void Student::read(std::istream& is) {
    readStudent(is);  
}

std::istream& Student::readStudent(std::istream& is) {
    is >> firstName_ >> lastName_;  

    marks_.clear();
    int mark;
    while (is >> mark) {
        marks_.push_back(mark);  
    }

    is.clear();  
    if (!marks_.empty()) {
        examMark_ = marks_.back();  
        marks_.pop_back();  
    } else {
        examMark_ = 0;  
    }

    calculateFinalMarks();  
    return is;  
}

// implementation of virtual print function
void Student::print(std::ostream& os) const {
    os << firstName_ << " " << lastName_ << " ND: ";
    for (const auto& mark : marks_) {
        os << mark << " ";
    }
    os << " Egz: " << examMark_ << "  Avg. gal: " << avgFinal_ << "  Avg. Med: " << medianFinal_;
}

// destructor
Student::~Student() {
    marks_.clear();
    ++dstCount;
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

        // if file is not found, generate it
        /*if (!file) {
            try {
                generateFile(fileSize);  
                std::ifstream file("files/studentai" + std::to_string(fileSize) + ".txt"); 
                if (!file) {
                    throw std::runtime_error(FILE_OPEN_ERROR);
                }
            } catch (const std::exception& e) {
                std::cerr << "Klaida: " << e.what() << std::endl;
                return 1;  
            }
        }*/

        string line;
        getline(file, line);

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

void Student::calculateFinalMarks() {
    avgFinal_ = 0.4 * average(marks_) + 0.6 * examMark_;
    medianFinal_ = median(marks_);
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

