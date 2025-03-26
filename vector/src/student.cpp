#include "student.h"
#include "utils.h"
#include "constants.h"

Student::Student() 
    : firstName_(""), lastName_(""), marks_(), examMark_(0), avgFinal_(0.0), medianFinal_(0.0) {}

Student::Student(std::string firstName, std::string lastName, std::vector<int> marks, int examMark, double avgFinal, double medianFinal)
    : firstName_(std::move(firstName)), lastName_(std::move(lastName)), marks_(std::move(marks)), examMark_(examMark), avgFinal_(avgFinal), medianFinal_(medianFinal) {}

void Student::readInput(std::vector<Student>& students, char menuChoice) {
    students.reserve(10000);
    string choice;
    do {
        // first and last name
        string firstName = GetFirstName(menuChoice);
        string lastName = GetLastName(menuChoice);

        // homework marks
        vector<int> marks = GetHomeworkMarks(menuChoice);

        // exam mark
        int examMark = GetExamMark(menuChoice);     

        Student student(firstName, lastName, marks, examMark, 0.0, 0.0);

        student.calculateFinalMarks();

        students.push_back(student);

        cout << ADD_ANOTHER_STUDENT << endl;
        choice = getYesNo();

    } while (choice == "taip"); 

    students.shrink_to_fit();
}

void Student::readFromFile(vector<Student>& students, int fileSize) {
    try {
        students.reserve(fileSize); 
        
        ifstream file("../files/studentai" + to_string(fileSize) + ".txt");
        if (!file) {
            throw std::runtime_error(FILE_OPEN_ERROR);
        }

        file.ignore(numeric_limits<streamsize>::max(), '\n'); // skip the first line

        string firstName, lastName, line;
        while (getline(file, line)) {
            istringstream stream(line);
            stream >> firstName >> lastName;
            
            vector<int> marks;
            marks.reserve(6); 
            
            int mark;
            while (stream >> mark) {
                marks.push_back(mark);
            }

            if (marks.empty()) throw std::runtime_error(EMPTY_ARRAY_ERROR);
            
            int examMark = marks.back();
            marks.pop_back();
            
            Student student(firstName, lastName, marks, examMark, 0.0, 0.0);

            student.calculateFinalMarks();

            students.push_back(student);
        }

        file.close();
        students.shrink_to_fit();
        cout << FILE_READ_SUCCESS << endl;

    } catch (const std::exception& e) {
        cerr << e.what() << endl;
    }
}

void Student::calculateFinalMarks() {
    double average = std::accumulate(marks_.begin(), marks_.end(), 0.0) / marks_.size();
    avgFinal_ = 0.4 * average + 0.6 * examMark_;

    vector<int> sortedMarks = marks_;
    sort(sortedMarks.begin(), sortedMarks.end());

    double median = (sortedMarks.size() % 2 == 0) ? 
         (sortedMarks[sortedMarks.size() / 2 - 1] + sortedMarks[sortedMarks.size() / 2]) / 2.0 : 
         sortedMarks[sortedMarks.size() / 2];

    medianFinal_ = 0.4 * median + 0.6 * examMark_;
}

void sortStudents(vector<Student>& students, char sortType) {
    // if sortType is 1, sort by first name
    if (sortType == 1) {
        stable_sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
            return a.getFirstName() < b.getFirstName();
        });
    // if sortType is 2, sort by last name
    } else if (sortType == 2) {
        stable_sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
            return a.getLastName() < b.getLastName();
        });
    // if sortType is 3, sort by average final mark
    } else if (sortType == 3) { 
        stable_sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
            return a.getAvgFinal() < b.getAvgFinal();
        });
    // if sortType is 4, sort by median final mark
    } else {
        stable_sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
            return a.getMedianFinal() < b.getMedianFinal();
        });
    }
}

