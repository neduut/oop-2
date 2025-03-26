#include "functions2.h"
#include "utils2.h"
#include "constants2.h"
#include "timeMeasurement2.h"

void handleProgramMenu(list<Student>& students) {
    while (true) {
        int menuChoice = getProgramMenuChoice();

        if (menuChoice == 5) {
            if (!students.empty()) {
                cout << endl;

                int groupType = getGroupType();  // by average or median?
                int sortType = getSortType();    // by first name, last name or final mark?
                int outputType = getPrintType(); // to console or to file?

                list<Student> kietiakai;
                list<Student> vargsiukai;

                // separate students into 2 groups
                groupStudents1(students, kietiakai, vargsiukai, groupType);

                students.clear(); // clear students list

                // sort students
                sortStudents(kietiakai, sortType);
                sortStudents(vargsiukai, sortType);

                // if output type is 1, print to console, if 2, print to file
                if (outputType == 1) {
                    printToConsole(kietiakai, vargsiukai);
                } else {
                    printToFile(kietiakai, "kietiakuRezultatai.txt");
                    printToFile(vargsiukai, "vargsiukuRezultatai.txt");
                }
            }
            break;
        }
        else if (menuChoice == 4) {
            int fileSize = getFileSize();
            readFromFile(students, fileSize);
        }
        else {
            readInput(students, menuChoice);
        }
    }
}

void handleTestMenu() {
    while (true) {
        int testMenuChoice = getTestMenuChoice();

        if (testMenuChoice == 0) {
            break;
        }
        else if (testMenuChoice == 1) {
            int fileSize = getFileSize();
            fileGenTest(fileSize, "genTest.txt");
        }
        else if (testMenuChoice == 2) {
            int fileSize = getFileSize();
            programTest(fileSize, "progTest.txt");
        }
        else if (testMenuChoice == 3) {
            int fileSize = getFileSize();
            listTest(fileSize, "listTest.txt");
        }
        else if (testMenuChoice == 4 || testMenuChoice == 5) {
            int fileSize = getFileSize();

            int num;
            if(testMenuChoice == 4) num = 1;
            else num = 2;
        
            strategies(fileSize, "strategy" + to_string(num) + "List.txt", testMenuChoice);
        }
    }
}

void generateFile(int size) {
    try {
        string fileName = "studentai" + to_string(size) + ".txt";
        ofstream file("../files/" + fileName);
        if (!file) {
            throw std::runtime_error(FILE_OPEN_ERROR);
        }

        list<string> lines;

        // Add header
        ostringstream header;
        header << left << setw(15) << "Vardas"
               << setw(15) << "Pavardė";
        for (int j = 1; j <= 5; ++j) {  
            header << setw(8) << "ND" + to_string(j);
        }
        header << setw(10) << "Egzaminas" << '\n';
        lines.push_back(header.str());

        // Generate student data
        for (int i = 0; i < size; ++i) {
            ostringstream ss;
            ss << left << setw(15) << "Vardas" + to_string(i + 1)
               << setw(15) << "Pavardė" + to_string(i + 1);
            for (int j = 0; j < 5; ++j) {  
                ss << setw(8) << getRandomMark();  
            }
            ss << setw(10) << getRandomMark() << '\n';  // Add exam mark
            lines.push_back(ss.str());
        }

        // Write all lines to the file in one operation
        for (const auto& line : lines) {
            file.write(line.c_str(), line.size());
        }

        file.close();
        cout << FILE_WRITE_SUCCESS << fileName << endl;

    } catch (const std::exception& e) { 
        cerr << "Error: " << e.what() << endl;
    }
}

void readInput(list<Student>& students, char menuChoice) {

    string choice;
    do {
        // first and last name
        string firstName = getFirstName(menuChoice);
        string lastName = getLastName(menuChoice);

        // homework marks
        list<int> marks = getHomeworkMarks(menuChoice);

        // exam mark
        int examMark = getExamMark(menuChoice);     

        // final mark
        double avgFinal = averageFinalMark(marks, examMark);
        double medianFinal = medianFinalMark(marks, examMark);

        students.emplace_back(Student{std::move(firstName), std::move(lastName), std::move(marks), examMark, avgFinal, medianFinal});

        cout << ADD_ANOTHER_STUDENT << endl;
        choice = getYesNo();

    } while (choice == "taip"); 
}

void readFromFile(list<Student>& students, int fileSize) {
    try {        
        ifstream file("../files/studentai" + to_string(fileSize) + ".txt");
        if (!file) {
            throw std::runtime_error(FILE_OPEN_ERROR);
        }

        file.ignore(numeric_limits<streamsize>::max(), '\n'); // skip the first line

        string firstName, lastName, line;
        while (getline(file, line)) {
            istringstream stream(line);
            stream >> firstName >> lastName;
            
            list<int> marks;
            
            int mark;
            while (stream >> mark) {
                marks.push_back(mark);
            }

            if (marks.empty()) throw std::runtime_error(EMPTY_ARRAY_ERROR);
            
            int examMark = marks.back();
            marks.pop_back();
            
            double avgFinal = averageFinalMark(marks, examMark);
            double medianFinal = medianFinalMark(marks, examMark);
            
            students.emplace_back(Student{std::move(firstName), std::move(lastName), std::move(marks), examMark, avgFinal, medianFinal});
        }

        file.close();
        cout << FILE_READ_SUCCESS << endl;

    } catch (const std::exception& e) {
        cerr << e.what() << endl;
    }
}

double averageFinalMark(const list<int>& marks, int examMark){
    double sum = 0;
    for (int mark : marks) {
        sum += mark;
    }
    double average = sum / marks.size();
    return 0.4 * average + 0.6 * examMark;
}

double medianFinalMark(const list<int>& marks, int examMark) {
    list<int> sortedMarks = marks;
    sortedMarks.sort();  

    auto it = sortedMarks.begin();
    advance(it, sortedMarks.size() / 2); 

    double median;
    if (sortedMarks.size() % 2 == 0) {
        auto itPrev = it;
        --itPrev;
        median = (*itPrev + *it) / 2.0;
    } else {
        median = *it;
    }
    return 0.4 * median + 0.6 * examMark;
}

void sortStudents(list<Student>& students, char sortType) {
    // if sortType is 1, sort by first name
    if (sortType == 1) {
        students.sort([](const Student& a, const Student& b) {
            return a.firstName < b.firstName;
        });
    // if sortType is 2, sort by last name
    } else if (sortType == 2) {
        students.sort([](const Student& a, const Student& b) {
            return a.lastName < b.lastName;
        });
    // if sortType is 3, sort by average final mark
    } else if (sortType == 3) { 
        students.sort([](const Student& a, const Student& b) {
            return a.avgFinal < b.avgFinal;
        });
    // if sortType is 4, sort by median final mark
    } else {
        students.sort([](const Student& a, const Student& b) {
            return a.medianFinal < b.medianFinal;
        });
    }
}

void groupStudents1(list<Student>& students, list<Student>& kietiakai, list<Student>& vargsiukai, char groupType) {
    for (const auto& student : students) {
        double finalMark = (groupType == 1) ? student.avgFinal : student.medianFinal;
        
        if (finalMark >= 5) {
            kietiakai.push_back(student);
        } else {
            vargsiukai.push_back(student);
        }
    }
}

void groupStudents2(list<Student>& students, list<Student>& kietiakai, list<Student>& vargsiukai, char groupType) {
    if(groupType == 1){
        sortStudents(students, 3);
        while(students.back().avgFinal > 5){
            kietiakai.push_back(students.back());
            students.pop_back();
        } 
    } else {
        sortStudents(students, 4);
        while(students.back().medianFinal > 5){
            kietiakai.push_back(students.back());
            students.pop_back();
        }
    }
    vargsiukai.insert(vargsiukai.end(), students.begin(), students.end());
    students.clear(); 
}

void printToConsole(list<Student>& kietiakai, list<Student>& vargsiukai) {
    cout << left << setw(17) << "Vardas"
         << setw(17) << "Pavarde"
         << setw(23) << "Galutinis (Vid.)"
         << setw(23) << "Galutinis (Med.)" << '\n'; 
    cout << string(80, '-') << '\n'; 

    cout << "Kietiakai: " << endl;
    for (const auto& student : kietiakai) { 
        cout << left << setw(17) << student.firstName 
             << setw(17) << student.lastName 
             << setw(23) << fixed << setprecision(2) 
             << student.avgFinal  
             << setw(23) << fixed << setprecision(2) 
             << student.medianFinal 
             << '\n';
    }
    cout << "Vargsiukai: " << endl;
    for (const auto& student : vargsiukai) { 
        cout << left << setw(17) << student.firstName 
             << setw(17) << student.lastName 
             << setw(23) << fixed << setprecision(2) 
             << student.avgFinal  
             << setw(23) << fixed << setprecision(2) 
             << student.medianFinal 
             << '\n';
    }
}

void printToFile(list<Student>& students, const string& fileName) {
    try {
        ofstream file("../files/" + fileName);
        if (!file) {
            throw std::runtime_error(FILE_OPEN_ERROR);
        }

        list<string> lines;

        ostringstream header;
        header << left << setw(17) << "Vardas"
               << setw(16) << "Pavarde"
               << setw(20) << "Galutinis (Vid.)" 
               << setw(20) << "Galutinis (Med.)" << '\n'
               << string(69, '-') << '\n';
        lines.push_back(header.str());

        for (const auto& student : students) {
            ostringstream ss;
            ss << setw(17) << left << student.firstName
               << setw(20) << student.lastName
               << setw(20) << fixed << setprecision(2) << student.avgFinal
               << setw(20) << fixed << setprecision(2) << student.medianFinal << '\n';
            lines.push_back(ss.str());
        }

        for (const auto& line : lines) {
            file.write(line.c_str(), line.size());
        }

        file.close();
        cout << "Rezultatai išsaugoti faile: " << fileName << "\n";

    } catch (const std::exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
}

void fileGenTest(int size, const std::string& fileName) {
    std::ofstream runTimeResults("../analysis/struct/" + fileName, std::ios::app); // open file in append mode

    if (runTimeResults.is_open()) {
        runTimeResults << "Konteineris: list\n";
        runTimeResults << "Failas: studentai" << size << ".txt\n";

        TimeMeasurement genTime("Failo generavimas");

        genTime.start();
        generateFile(size);
        genTime.stop(runTimeResults); 

        runTimeResults << "\n";
        runTimeResults.close();  

        cout << TEST_SECCESS << fileName << "\n";

    } else {
        std::cerr << FILE_OPEN_ERROR << std::endl;
    }
}

void programTest(int size, const std::string& fileName) {
    std::ofstream runTimeResults("../analysis/struct/" + fileName, std::ios::app); // open file in append mode

    if (runTimeResults.is_open()) {
        runTimeResults << "Konteineris: list\n";
        runTimeResults << "Failas: studentai" << size << ".txt\n";
        TimeMeasurement programTime("Programos vykdymo laikas");
        programTime.start();

        list<Student> students;

        TimeMeasurement readTime("Duomenų nuskaitymas iš failo");
        readTime.start();
        readFromFile(students, size);
        readTime.stop(runTimeResults); 

        list<Student> kietiakai;
        list<Student> vargsiukai;

        TimeMeasurement groupingTime("Studentų rūšiavimas į dvi grupes");
        groupingTime.start();
        groupStudents1(students, kietiakai, vargsiukai, 1);
        groupingTime.stop(runTimeResults); 

        students.clear(); 

        TimeMeasurement printTime("Išvedimas į du naujus failus");
        printTime.start();
        printToFile(kietiakai, "kietiakai.txt");
        printToFile(vargsiukai, "vargsiukai.txt");
        printTime.stop(runTimeResults);  

        programTime.stop(runTimeResults); 
        runTimeResults << "\n";

        runTimeResults.close(); 

        cout << TEST_SECCESS << fileName << "\n";
    } else {
        std::cerr << FILE_OPEN_ERROR << std::endl;
    }
}

void listTest(int size, const std::string& fileName) {
    std::ofstream runTimeResults("../analysis/struct/containers/" + fileName, std::ios::app); // open file in append mode

    if (runTimeResults.is_open()) {
        runTimeResults << "Failas: studentai" << size << ".txt\n";

        list<Student> students;

        TimeMeasurement readTime("Duomenų nuskaitymas iš failo");
        readTime.start();
        readFromFile(students, size);
        readTime.stop(runTimeResults); 

        //int sortType = getSortType(); 
        TimeMeasurement printTime("Studentų rikiavimas didėjimo tvarka");
        printTime.start();
        sortStudents(students, 3); // sort by average final mark
        printTime.stop(runTimeResults);  

        list<Student> kietiakai;
        list<Student> vargsiukai;

        //int sortGroup = getGroupType();
        TimeMeasurement groupingTime("Studentų rūšiavimas į dvi grupes");
        groupingTime.start();
        groupStudents1(students, kietiakai, vargsiukai, 1);
        groupingTime.stop(runTimeResults); 

        students.clear(); 

        printToFile(kietiakai, "kietiakai.txt");
        printToFile(vargsiukai, "vargsiukai.txt");

        runTimeResults << "\n";
        runTimeResults.close(); 

        cout << TEST_SECCESS << fileName << "\n";
    } else {
        std::cerr << FILE_OPEN_ERROR << std::endl;
    }
}

void strategies(int size, const std::string& fileName, int strategy) {
    std::ofstream runTimeResults("../analysis/struct/strategies/" + fileName, std::ios::app); 

    //int groupType = getGroupType(); 
    if (runTimeResults.is_open()) {
        runTimeResults << "Failas: studentai" << size << ".txt\n";
        TimeMeasurement groupingTime("Studentų rūšiavimas į dvi grupes");

        list<Student> students;
        readFromFile(students, size);

        list<Student> kietiakai;
        list<Student> vargsiukai;

        if (strategy == 4) {
            groupingTime.start();
            groupStudents1(students, kietiakai, vargsiukai, 1);
            groupingTime.stop(runTimeResults); 
        } else if (strategy == 5) {
            groupingTime.start();
            groupStudents2(students, kietiakai, vargsiukai, 1);
            groupingTime.stop(runTimeResults); 
        } 

        students.clear(); 

        printToFile(kietiakai, "kietiakai.txt");
        printToFile(vargsiukai, "vargsiukai.txt");

        runTimeResults << "\n";
        runTimeResults.close(); 

        cout << TEST_SECCESS << fileName << "\n";
    } else {
        std::cerr << FILE_OPEN_ERROR << std::endl;
    }
}