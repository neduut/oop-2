#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include <windows.h>
#include "student.h"
#include "zmogus.h"
#include <sstream>
#include <fstream>
#include <vector>
#include <cstdio> 
using std::istringstream;
using std::ostringstream;
using std::ofstream;
using std::ifstream;
using std::move;
using std::string;
using std::vector;

TEST_CASE("Student klases testai") {
    SetConsoleOutputCP(65001); 

    // 1st test
    Student s1;
    SECTION("1 TESTAS: default konstruktorius") {
        s1.setFirstName("testas");
        s1.setLastName("testukas");
        s1.setMarks({1, 2, 3, 4, 5});
        s1.setExamMark(10);
        s1.calculateFinalMarks();
        REQUIRE(s1.getFirstName() == "testas");
    }

    // 2nd test
    Student s2;
    SECTION("2 TESTAS: kopijavimo konstruktorius") {
        Student s2(s1);
        REQUIRE(s2.getFirstName() == s1.getFirstName());
    }

    // 3rd test
    SECTION("3 TESTAS: kopijavimo operatorius") {
        Student s3;
        s1.setFirstName("testas");
        s3 = s1;
        REQUIRE(s3.getFirstName() == s1.getFirstName());
    }

    // 4th test
    SECTION("4 TESTAS: perkėlimo konstruktorius") {
        Student s4(move(s1));
        REQUIRE(s4.getFirstName() == "testas");
        REQUIRE(s1.getFirstName().empty());
    }

    // 5th test
    SECTION("5 TESTAS: perkėlimo operatorius") {
        Student s5;
        s5 = std::move(s2);
        REQUIRE(s5.getFirstName() == "testas");
        REQUIRE(s2.getFirstName().empty());
    }

    // 6th test
    SECTION("6 TESTAS: įvesties operatorius (istringstream)") {
        std::istringstream iss("testas testukas 1 2 3 4 5 10\n");
        Student s6;
        iss >> s6;
        s6.calculateFinalMarks();
        REQUIRE(s6.getFirstName() == "testas");
        REQUIRE(s6.getExamMark() == 10);
    }

    // 7th test
    SECTION("6.1 TESTAS: įvesties operatorius (input iš konsoles)"){
    std::istringstream iss("Labas Labukas 10 10 9 10 8 7");
    Student s7;
    iss >> s7;
    s7.calculateFinalMarks();
    REQUIRE(s7.getFirstName() == "Labas");
    }   

    // 8th test
    Student s8;
    SECTION("6.2 TESTAS: įvestis iš failo") {
        std::ofstream testFile("files/testas1.txt");
        testFile << "Antanas Antanaitis 9 8 7 6 5 9\n";
        testFile.close();
    
        std::ifstream fr("files/testas1.txt");
        fr >> s8;
        fr.close();
        s8.calculateFinalMarks();

        REQUIRE(s8.getFirstName() == "Antanas");
        REQUIRE(s8.getLastName() == "Antanaitis");
        REQUIRE((s8.getHomeworkMarks() == vector<int>{9, 8, 7, 6, 5}));
        REQUIRE(s8.getExamMark() == 9);
    }

    // 9th test
    SECTION("7 TESTAS: išvesties operatorius") {
        std::ostringstream oss;
        oss << s8;
        REQUIRE(oss.str().find("Antanaitis") != std::string::npos);
    }

    //10th test
    std::vector<Student> tempStudents;
    SECTION("8 TESTAS: studentų nuskaitymas iš failo") {
        std::ofstream testFile("files/studentai3.txt");
        testFile << "antrašte\n";
        testFile << "Jonas Jonaitis 10 9 8 7 9 6\n";
        testFile << "Vejas Vejukas 10 9 8 7 6 6\n";
        testFile << "Petras Petrauskas 8 9 7 10 9 5\n";
        testFile.close();
    
        Student::readFromFile(tempStudents, 3);
        REQUIRE(tempStudents.size() == 3);
        REQUIRE(tempStudents[0].getFirstName() == "Jonas");
        REQUIRE(tempStudents[1].getLastName() == "Vejukas");
    }

    // 11th test
    SECTION("9 TESTAS: išvedimas i failą") {
        ofstream testFile("files/testas2.txt");
        for (const auto& s : tempStudents) {
            testFile << s << "\n";
        }
        testFile.close();
    }

    // 12th test imituotas
    SECTION("10 TESTAS: studentų išvedimas i konsolę") {
        ostringstream ss;
        for (const auto& s : tempStudents) {
            ss << s.getFirstName() << " " << s.getLastName() << "\n";
        }
    
        string expected_output = "Jonas Jonaitis\nVejas Vejukas\nPetras Petrauskas\n";
        REQUIRE(ss.str() == expected_output);
    }

    // 13th test
    SECTION("11 TESTAS: destruktorius") {
        const int before = dstCount;
        {
            Student temp;
        }
        REQUIRE(dstCount == before + 1);
    }
}