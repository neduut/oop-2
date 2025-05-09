#include "functions.h"
#include "utils.h"
#include "constants.h"
#include "timeMeasurement.h"
#include "student.h"
#include <cassert>

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
        else if (testMenuChoice == 3) {
            testRuleOfFive();
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
        header << left << setw(15) << "getFirstName"
               << setw(15) << "Pavardė";
        for (int j = 1; j <= 5; ++j) {  
            header << setw(8) << "ND" + to_string(j);
        }
        header << setw(10) << "Egzaminas" << '\n';
        lines.push_back(header.str());

        // Generate student data
        for (int i = 0; i < size; ++i) {
            ostringstream ss;
            ss << left << setw(15) << "getFirstName" + to_string(i + 1)
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
    cout << left << setw(17) << "getFirstName"
         << setw(17) << "getLastName"
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
        ofstream file("files/" + fileName);
        if (!file) {
            throw std::runtime_error(FILE_OPEN_ERROR);
        }

        vector<string> lines;
        lines.reserve(students.size() + 2);

        ostringstream header;
        header << left << setw(17) << "getFirstName"
               << setw(16) << "getLastName"
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
    std::ofstream runTimeResults("analysis/class/genTest.txt", std::ios::app); // open file in append mode

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
    std::ofstream runTimeResults("analysis/class/flags/O3.txt", std::ios::app); // open file in append mode

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

        TimeMeasurement sortTime("Studentų rikiavimas didėjimo tvarka");
        sortTime.start();
        sortStudents(kietiakai, 3);
        sortStudents(vargsiukai, 3);
        sortTime.stop(runTimeResults); 

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

void testRuleOfFive() {
    // 1st test
    cout << "\n1 TESTAS: default konstruktorius\n";
    Student s1;
    s1.setFirstName("testas");
    s1.setLastName("testukas");
    s1.setMarks({1, 2, 3, 4, 5});
    s1.setExamMark(10);
    s1.calculateFinalMarks();
    cout << "Rezultatas: " << s1 << endl;
    assert(s1.getFirstName() == "testas");

    // 2nd test
    cout << "\n2 TESTAS: kopijavimo konstruktorius\n";
    Student s2(s1);
    cout << "Rezultatas: " << s2 << "\n";
    assert(s2.getFirstName() == s1.getFirstName());

    // 3rd test
    cout << "\n3 TESTAS: kopijavimo operatorius\n";
    Student s3;
    s3 = s1;
    cout << "Rezultatas: " << s3 << "\n";
    assert(s3.getFirstName() == s1.getFirstName());

    // 4th test
    cout << "\n4 TESTAS: perkėlimo konstruktorius\n";
    Student s4(std::move(s1));
    cout << "Rezultatas: " << s4 << "\n";
    cout << "s1: " << s1 << "\n"; // should be empty
    assert(s4.getFirstName() == "testas");
    assert(s4.getExamMark() == 10);
    assert(s1.getFirstName().empty()); 

    // 5th test
    cout << "\n5 TESTAS: perkėlimo operatorius\n";
    Student s5;
    s5 = std::move(s2);
    cout << "Rezultatas: " << s5 << "\n";
    assert(s5.getFirstName() == "testas");
    assert(s5.getExamMark() == 10);
    assert(s2.getFirstName().empty());

    // 6th test 
    cout << "\n6 TESTAS: įvesties operatorius (į istringstream)\n";
    istringstream iss1("testas testukas 1 2 3 4 5 10\n");
    Student s6;
    iss1 >> s6;
    s6.calculateFinalMarks();
    cout << "Rezultatas: " << s6 << endl;
    assert(s6.getFirstName() == "testas");
    assert(s6.getExamMark() == 10);

    // 7th test
    std::cout << "\n[TEST 6.1] Ivesties operatorius (input iš konsolės)\n";
    std::istringstream iss("Labas Labukas 10 10 9 10 8 7");
    Student s7;
    iss >> s7;
    s6.calculateFinalMarks();
    std::cout << "Rezultatas: " << s7 << std::endl;
    assert(s7.getFirstName() == "Labas");

    // 8th test 
    cout << "\n6.2 TESTAS: įvestis iš failo\n";
    ofstream testFile1("files/testas1.txt");
    testFile1 << "Antanas Antanaitis 9 8 7 6 5 9" << endl;
    testFile1.close();

    ifstream fr("files/testas1.txt");
    Student s8;
    fr >> s8;
    fr.close();
    s8.calculateFinalMarks();
    cout << "Rezultatas: " << s8 << endl;
    assert(s8.getFirstName() == "Antanas");
    assert(s8.getLastName() == "Antanaitis");
    assert((s8.getHomeworkMarks() == vector<int>{9, 8, 7, 6, 5}));
    assert(s8.getExamMark() == 9);

    // 9th test 
    cout << "\n7 TESTAS: išvesties operatorius \n";
    ostringstream oss1;
    oss1 << s8;
    cout << "Rezultatas: " << oss1.str() << endl;
    assert(oss1.str().find("Antanaitis") != std::string::npos);

    // 10th test
    cout << "\n8 TESTAS: studentų nuskaitymas iš failo (readFromFile)\n";
    std::ofstream testFile2("files/studentai3.txt");
    testFile2 << "antraste" << endl;
    testFile2 << "Jonas Jonaitis 10 9 8 7 9 6" << endl;
    testFile2 << "Vejas Vejukas 10 9 8 7 6 6" << endl;
    testFile2 << "Petras Petrauskas 8 9 7 10 9 5" << endl;
    testFile2.close();

    std::vector<Student> tempStudents;
    Student::readFromFile(tempStudents, 3);
    cout << "Gauta studentu: " << tempStudents.size() << endl;
    assert(tempStudents.size() == 3);
    assert(tempStudents[0].getFirstName() == "Jonas");
    assert(tempStudents[1].getLastName() == "Vejukas");

    // 11th test
    cout << "\n9 TESTAS: išvedimas į failą\n";
    ofstream testFile3("files/testas2.txt");
    if (!testFile3) {
        cerr << FILE_OPEN_ERROR << endl;
    } else {
        for (const auto& s : tempStudents) {
            testFile3 << s << "\n";
        }
        testFile3.close();
    }
    cout << "Rezultatai išsaugoti faile: testas2.txt\n";

    // 12th test
    cout << "\n10 TESTAS: studentų išvedimas į konsolę\n";
    for (const auto& s : tempStudents) cout << s << endl;

    // 13th test
    cout << "\n11 TESTAS: destruktorius\n"; 
    cout << "Destruktorius iškviestas " << dstCount << printCount(dstCount) << endl;
}

// norit testuoti Zmogaus klasę, atkomentuokite šią funkciją
/*void testZmogausClass() {  
    Zmogus zmogus; 
}*/

