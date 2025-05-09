#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include "student.h"   
#include "mylib.h"
#include <sstream>
#include <fstream>
#include <cstdio> 

TEST_CASE("Student klasės testai") {
    int initialDstCount = dstCount;

    SECTION("1 TESTAS: default konstruktorius") {
        Student s1;
        s1.setFirstName("testas");
        s1.setLastName("testukas");
        s1.setMarks({1, 2, 3, 4, 5});
        s1.setExamMark(10);
        s1.calculateFinalMarks();

        REQUIRE(s1.getFirstName() == "testas");
        REQUIRE(s1.getLastName() == "testukas");
        REQUIRE(s1.getHomeworkMarks() == std::vector<int>{1, 2, 3, 4, 5});
        REQUIRE(s1.getExamMark() == 10);

        SECTION("2 TESTAS: kopijavimo konstruktorius") {
            Student s2(s1);
            REQUIRE(s2.getFirstName() == s1.getFirstName());
        }

        SECTION("3 TESTAS: kopijavimo operatorius") {
            Student s3;
            s3 = s1;
            REQUIRE(s3.getFirstName() == s1.getFirstName());
            REQUIRE(s3.getHomeworkMarks() == s1.getHomeworkMarks());
        }

        SECTION("4 TESTAS: perkėlimo konstruktorius") {
            Student s4(std::move(s1));
            REQUIRE(s4.getFirstName() == "testas");
            REQUIRE(s4.getExamMark() == 10);
            REQUIRE(s1.getFirstName().empty());
        }

        SECTION("5 TESTAS: perkėlimo operatorius") {
            Student s5;
            s5 = std::move(s1);
            REQUIRE(s5.getFirstName() == "testas");
            REQUIRE(s5.getExamMark() == 10);
            REQUIRE(s1.getFirstName().empty());
        }
    }

    SECTION("6 TESTAS: įvesties operatorius (istringstream)") {
        std::istringstream iss("testas testukas 1 2 3 4 5 10\n");
        Student s6;
        iss >> s6;
        s6.calculateFinalMarks();

        REQUIRE(s6.getFirstName() == "testas");
        REQUIRE(s6.getExamMark() == 10);
    }

    SECTION("6.1 TESTAS: įvesties operatorius (simuliuota konsolė)") {
        std::vector<Student> students;
        // Pilnas įvesties simulavimas (pvz., vardas, pavardė, pažymiai, egzaminas)
        std::istringstream input(
            "1\n"  // Pasirinkimas: rankinis įvedimas
            "Testas\nTestauskas\n1 2 3 4 5\n10\n" // Studento duomenys
        );
        std::streambuf* originalCin = std::cin.rdbuf(input.rdbuf());
        
        Student::readInput(students, 1); 
        std::cin.rdbuf(originalCin);

        REQUIRE(students.size() == 1);
        REQUIRE(students[0].getFirstName() == "Testas");
    }

    SECTION("6.2 TESTAS: įvestis iš failo") {
        // Sukuriamas laikinas failas build kataloge
        const std::string testFile = "testas1.txt";
        {
            std::ofstream file(testFile);
            file << "Antanas Antanaitis 9 8 7 6 5 9\n";
        }

        Student s8;
        std::ifstream fr(testFile);
        REQUIRE(fr >> s8);
        fr.close();
        s8.calculateFinalMarks();

        REQUIRE(s8.getFirstName() == "Antanas");
        REQUIRE(s8.getHomeworkMarks() == std::vector<int>{9, 8, 7, 6, 5});

        std::remove(testFile.c_str()); // Ištrinam laikiną failą
    }

    SECTION("7 TESTAS: išvesties operatorius") {
        Student s8;
        s8.setFirstName("Antanas");
        s8.setLastName("Antanaitis");
        std::ostringstream oss;
        oss << s8;

        REQUIRE(oss.str().find("Antanaitis") != std::string::npos);
    }

    SECTION("8 TESTAS: studentų nuskaitymas iš failo") {
        const std::string testFile = "studentai3.txt";
        {
            std::ofstream file(testFile);
            file << "Jonas Jonaitis 10 9 8 7 9 6\n"
                 << "Vejas Vejukas 10 9 8 7 6 6\n"
                 << "Petras Petrauskas 8 9 7 10 9 5\n";
        }

        std::vector<Student> students;
        Student::readFromFile(students, 3);

        REQUIRE(students.size() == 3);
        REQUIRE(students[0].getFirstName() == "Jonas");
        REQUIRE(students[1].getLastName() == "Vejukas");

        std::remove(testFile.c_str());
    }

    SECTION("9 TESTAS: išvedimas į failą") {
        const std::string testFile = "testas2.txt";
        {
            std::vector<Student> students = {Student(), Student(), Student()};
            std::ofstream file(testFile);
            REQUIRE(file.is_open());
            for (const auto& s : students) file << s << "\n";
        }

        // Patikriname, ar failas ne tuščias
        std::ifstream checkFile(testFile);
        std::string line;
        REQUIRE(std::getline(checkFile, line));
        checkFile.close();
        std::remove(testFile.c_str());
    }

    SECTION("10 TESTAS: studentų išvedimas į konsolę") {
        std::vector<Student> students = {Student(), Student(), Student()};
        std::ostringstream oss;
        std::streambuf* oldCoutBuffer = std::cout.rdbuf(oss.rdbuf());
        
        for (const auto& s : students) std::cout << s << "\n";
        std::cout.rdbuf(oldCoutBuffer);

        REQUIRE(oss.str().size() > 0);
    }

    SECTION("11 TESTAS: destruktorius") {
        const int before = dstCount;
        {
            Student temp;
        }
        REQUIRE(dstCount == before + 1);
    }
}