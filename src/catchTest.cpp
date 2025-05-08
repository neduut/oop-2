#define CATCH_CONFIG_CONSOLE_WIDTH 120
#include <catch2/catch.hpp>
#include "student.h"   
#include "functions.h" 
#include "zmogus.h"

TEST_CASE("Testuoja Rule of Five Student klasei") {
    
    // 1st test
    SECTION("1 TESTAS: default konstruktorius") {
        Student s1;
        s1.setFirstName("testas");
        s1.setLastName("testukas");
        s1.setMarks({1, 2, 3, 4, 5});
        s1.setExamMark(10);
        s1.calculateFinalMarks();
        
        REQUIRE(s1.getFirstName() == "testas");
        REQUIRE(s1.getLastName() == "testukas");
        REQUIRE(s1.getMarks() == std::vector<int>{1, 2, 3, 4, 5});
        REQUIRE(s1.getExamMark() == 10);
    }

    // 2nd test
    SECTION("2 TESTAS: kopijavimo konstruktorius") {
        Student s1;
        s1.setFirstName("testas");
        s1.setLastName("testukas");
        s1.setMarks({1, 2, 3, 4, 5});
        s1.setExamMark(10);

        Student s2(s1);  
        REQUIRE(s2.getFirstName() == s1.getFirstName());
        REQUIRE(s2.getLastName() == s1.getLastName());
        REQUIRE(s2.getMarks() == s1.getMarks());
        REQUIRE(s2.getExamMark() == s1.getExamMark());
    }

    // 3rd test
    SECTION("3 TESTAS: kopijavimo operatorius") {
        Student s1;
        s1.setFirstName("testas");
        s1.setLastName("testukas");
        s1.setMarks({1, 2, 3, 4, 5});
        s1.setExamMark(10);

        Student s2;
        s2 = s1; 
        REQUIRE(s2.getFirstName() == s1.getFirstName());
        REQUIRE(s2.getLastName() == s1.getLastName());
        REQUIRE(s2.getMarks() == s1.getMarks());
        REQUIRE(s2.getExamMark() == s1.getExamMark());
    }

    // 4th test
    SECTION("4 TESTAS: perkėlimo konstruktorius") {
        Student s1;
        s1.setFirstName("testas");
        s1.setLastName("testukas");
        s1.setMarks({1, 2, 3, 4, 5});
        s1.setExamMark(10);

        Student s2(std::move(s1)); 
        REQUIRE(s2.getFirstName() == "testas");
        REQUIRE(s2.getExamMark() == 10);
        REQUIRE(s1.getFirstName().empty());  
    }

    // 5th test
    SECTION("5 TESTAS: perkėlimo operatorius") {
        Student s1;
        s1.setFirstName("testas");
        s1.setLastName("testukas");
        s1.setMarks({1, 2, 3, 4, 5});
        s1.setExamMark(10);

        Student s2;
        s2 = std::move(s1); 
        REQUIRE(s2.getFirstName() == "testas");
        REQUIRE(s2.getExamMark() == 10);
        REQUIRE(s1.getFirstName().empty());  
    }

    // 6th test
    SECTION("6 TESTAS: įvesties operatorius (į istringstream)") {
        istringstream iss1("testas testukas 1 2 3 4 5 10\n");
        Student s6;
        iss1 >> s6;
        s6.calculateFinalMarks();

        REQUIRE(s6.getFirstName() == "testas");
        REQUIRE(s6.getExamMark() == 10);
    }

    // 7th test
    SECTION("6.1 TESTAS: įvesties operatorius (input iš konsolės)") {
        vector<Student> s7;
        Student::readInput(s7, 1); 
        REQUIRE(!s7[0].getFirstName().empty());
    }

    // 8th test
    SECTION("6.2 TESTAS: įvestis iš failo") {
        ofstream testFile1("files/testas1.txt");
        testFile1 << "Antanas Antanaitis 9 8 7 6 5 9" << endl;
        testFile1.close();

        ifstream fr("files/testas1.txt");
        Student s8;
        fr >> s8;
        fr.close();
        s8.calculateFinalMarks();

        REQUIRE(s8.getFirstName() == "Antanas");
        REQUIRE(s8.getLastName() == "Antanaitis");
        REQUIRE(s8.getMarks() == std::vector<int>{9, 8, 7, 6, 5});
        REQUIRE(s8.getExamMark() == 9);
    }

    // 9th test
    SECTION("7 TESTAS: išvesties operatorius") {
        ostringstream oss1;
        Student s8;
        s8.setFirstName("Antanas");
        s8.setLastName("Antanaitis");
        s8.setMarks({9, 8, 7, 6, 5});
        s8.setExamMark(9);
        oss1 << s8;

        std::string result = oss1.str();
        REQUIRE(result.find("Antanaitis") != std::string::npos);
    }

    // 10th test
    std::vector<Student> tempStudents;
    SECTION("8 TESTAS: studentų nuskaitymas iš failo (readFromFile)") {
        std::ofstream testFile2("files/studentai3.txt");
        testFile2 << "antraste" << endl;
        testFile2 << "Jonas Jonaitis 10 9 8 7 9 6" << endl;
        testFile2 << "Vejas Vejukas 10 9 8 7 6 6" << endl;
        testFile2 << "Petras Petrauskas 8 9 7 10 9 5" << endl;
        testFile2.close();

        Student::readFromFile(tempStudents, 3);
        REQUIRE(tempStudents.size() == 3);
        REQUIRE(tempStudents[0].getFirstName() == "Jonas");
        REQUIRE(tempStudents[1].getLastName() == "Vejukas");
    }

    // 11th test
    SECTION("9 TESTAS: išvedimas į failą") {
        std::ofstream testFile3("files/testas2.txt");
        if (!testFile3) {
            cerr << "Nepavyko atidaryti failo!" << endl;
        } else {
            for (const auto& s : tempStudents) {
                testFile3 << s << "\n";
            }
            testFile3.close();
        }
        cout << "Rezultatai išsaugoti faile: testas2.txt\n";
    }

    // 12-th test
    SECTION("10 TESTAS: studentų išvedimas į konsolę") {
        for (const auto& s : tempStudents) {
            cout << s << endl;  
        }
    }

    // 13th test
    SECTION("11 TESTAS: destruktorius") {
        cout << "Destruktorius iškviestas " << dstCount << " kartus" << endl;
        REQUIRE(dstCount > 0);  
    }    
}
