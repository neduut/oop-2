#include "functions.h"
#include "utils.h"
#include "constants.h"
#include "timeMeasurement.h"
#include "student.h"

void handleProgramMenu(std::vector<Student>& students) {
    while (true) {
        int menuChoice = getProgramMenuChoice();

        if (menuChoice == 5) {
            if (!students.empty()) {
                cout << endl;

                int groupType = getGroupType();  // by average or median?
                int sortType = getSortType();    // by first name, last name or final mark?
                int outputType = getPrintType(); // to console or to file?

                vector<Student> kietiakai;
                vector<Student> vargsiukai;

                // separate students into 2 groups
                groupStudents(students, kietiakai, vargsiukai, groupType);

                kietiakai.shrink_to_fit();
                vargsiukai.shrink_to_fit();

                // sort students
                sortStudents(kietiakai, sortType);
                sortStudents(vargsiukai, sortType);

                // if output type is 1, print to console, if 2, print to file
                if (outputType == 1) {
                    printToConsole(kietiakai, vargsiukai);
                } else {
                    printToFile(kietiakai, "kietiakai.txt");
                    printToFile(vargsiukai, "vargsiukai.txt");
                }
            break;
            }
        }
        else if (menuChoice == 4) {
            int fileSize = getFileSize();
            Student::readFromFile(students, fileSize);
        }
        else {
            Student::readInput(students, menuChoice);
        }
    }
}

void handleTestMenu() {
    while (true) {
        int testMenuChoice = getTestMenuChoice();

        if (testMenuChoice == 0) {
            system("cls");
            break;
        }
        else if (testMenuChoice == 1) {
            int fileSize = getFileSize();
            for (int i = 0; i < 5; ++i) { fileGenTest(fileSize);}
        }
        else if (testMenuChoice == 2) {
            int fileSize = getFileSize();
            for (int i = 0; i < 5; ++i) { programTest(fileSize);}
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

        vector<string> lines;
        lines.reserve(size + 1); // Reserve space for size + 1 (header)

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

void groupStudents(vector<Student>& students, vector<Student>& kietiakai, vector<Student>& vargsiukai, int groupType) {
    kietiakai.reserve(students.size());
    vargsiukai.reserve(students.size());

    auto separator = std::partition(students.begin(), students.end(), [groupType](const Student& student) {
        float finalMark = (groupType == 1) ? student.getAvgFinal() : student.getMedianFinal();
        return finalMark >= 5.0;
    });

    for (auto it = students.begin(); it != separator; ++it) {
        kietiakai.emplace_back(std::move(*it));
    }
    for (auto it = separator; it != students.end(); ++it) {
        vargsiukai.emplace_back(std::move(*it));
    }
    students.clear();
}

void printToConsole(vector<Student>& kietiakai, vector<Student>& vargsiukai) {
    cout << left << setw(17) << "Vardas"
         << setw(17) << "Pavarde"
         << setw(23) << "Galutinis (Vid.)"
         << setw(23) << "Galutinis (Med.)" << '\n'; 
    cout << string(80, '-') << '\n'; 

    cout << "Kietiakai: " << endl;
    for (const auto& student : kietiakai) { 
        cout << left << setw(17) << student.getFirstName()
             << setw(17) << student.getLastName()
             << setw(23) << fixed << setprecision(2) 
             << student.getAvgFinal()
             << setw(23) << fixed << setprecision(2) 
             << student.getMedianFinal()
             << '\n';
    }
    cout << "Vargsiukai: " << endl;
    for (const auto& student : vargsiukai) { 
        cout << left << setw(17) << student.getFirstName()
             << setw(17) << student.getLastName()
             << setw(23) << fixed << setprecision(2) 
             << student.getAvgFinal() 
             << setw(23) << fixed << setprecision(2) 
             << student.getMedianFinal()
             << '\n';
    }
}

void printToFile(vector<Student>& students, const string& fileName) {
    try {
        ofstream file("../files/" + fileName);
        if (!file) {
            throw std::runtime_error(FILE_OPEN_ERROR);
        }

        vector<string> lines;
        lines.reserve(students.size() + 2);

        ostringstream header;
        header << left << setw(17) << "Vardas"
               << setw(16) << "Pavarde"
               << setw(20) << "Galutinis (Vid.)" 
               << setw(20) << "Galutinis (Med.)" << '\n'
               << string(69, '-') << '\n';
        lines.push_back(header.str());

        for (const auto& student : students) {
            ostringstream ss;
            ss << setw(17) << left << student.getFirstName()
               << setw(20) << student.getLastName()
               << setw(20) << fixed << setprecision(2) << student.getAvgFinal()
               << setw(20) << fixed << setprecision(2) << student.getMedianFinal() << '\n';
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

void fileGenTest(int size) {
    std::ofstream runTimeResults("../analysis/class/genTest.txt", std::ios::app); // open file in append mode

    if (runTimeResults.is_open()) {
        runTimeResults << "Konteineris: vector\n";
        runTimeResults << "Failas: studentai" << size << ".txt\n";

        TimeMeasurement genTime("Failo generavimas");

        genTime.start();
        generateFile(size);
        genTime.stop(runTimeResults); 

        runTimeResults.close();  
        runTimeResults << "\n";

        cout << TEST_SECCESS << "genTest.txt" << "\n";
    } else {
        std::cerr << FILE_OPEN_ERROR << std::endl;
    }
}

void programTest(int size) {
    std::ofstream runTimeResults("../analysis/class/flags/O3.txt", std::ios::app); // open file in append mode

    if (runTimeResults.is_open()) {
        runTimeResults << "Konteineris: vector\n";
        runTimeResults << "Failas: studentai" << size << ".txt\n";
        TimeMeasurement programTime("Programos vykdymo laikas");
        programTime.start();

        vector<Student> students;

        TimeMeasurement readTime("Duomenų nuskaitymas iš failo");
        readTime.start();
        Student::readFromFile(students, size);
        readTime.stop(runTimeResults); 

        vector<Student> kietiakai;
        vector<Student> vargsiukai;

        TimeMeasurement groupingTime("Studentų rūšiavimas į dvi grupes");
        groupingTime.start();
        groupStudents(students, kietiakai, vargsiukai, 1);
        groupingTime.stop(runTimeResults); 

        students.clear(); 
        kietiakai.shrink_to_fit();
        vargsiukai.shrink_to_fit();

        TimeMeasurement printTime("Išvedimas į du naujus failus");
        printTime.start();
        printToFile(kietiakai, "kietiakai.txt");
        printToFile(vargsiukai, "vargsiukai.txt");
        printTime.stop(runTimeResults);  

        programTime.stop(runTimeResults); 
        runTimeResults << "\n";

        runTimeResults.close(); 

        cout << TEST_SECCESS << "Ox.txt" << "\n";
    } else {
        std::cerr << FILE_OPEN_ERROR << std::endl;
    }
}

