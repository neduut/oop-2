#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include "student.h"
#include <sstream>
#include <fstream>
#include <vector>
#include <cstdio> 

TEST_CASE("Student klasės testai", "[student]") {
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
    }

    SECTION("2 TESTAS: kopijavimo konstruktorius") {
        Student s1;
        s1.setFirstName("testas");
        Student s2(s1);
        REQUIRE(s2.getFirstName() == s1.getFirstName());
    }

    SECTION("3 TESTAS: kopijavimo operatorius") {
        Student s1;
        s1.setFirstName("testas");
        Student s3;
        s3 = s1;
        REQUIRE(s3.getFirstName() == s1.getFirstName());
    }

    SECTION("4 TESTAS: perkėlimo konstruktorius") {
        Student s1;
        s1.setFirstName("testas");
        Student s4(std::move(s1));
        REQUIRE(s4.getFirstName() == "testas");
        REQUIRE(s1.getFirstName().empty());
    }

    SECTION("5 TESTAS: perkėlimo operatorius") {
        Student s2;
        s2.setFirstName("testas");
        Student s5;
        s5 = std::move(s2);
        REQUIRE(s5.getFirstName() == "testas");
        REQUIRE(s2.getFirstName().empty());
    }

    SECTION("6 TESTAS: įvesties operatorius (istringstream)") {
        std::istringstream iss("testas testukas 1 2 3 4 5 10\n");
        Student s6;
        iss >> s6;
        s6.calculateFinalMarks();
        REQUIRE(s6.getFirstName() == "testas");
        REQUIRE(s6.getExamMark() == 10);
    }

    SECTION("7 TESTAS: įvestis iš failo") {
        const std::string filename = "files/testas1.txt";
        {
            std::ofstream file(filename);
            file << "Antanas Antanaitis 9 8 7 6 5 9\n";
        }

        Student s8;
        std::ifstream fr(filename);
        REQUIRE(fr >> s8);
        fr.close();
        s8.calculateFinalMarks();

        REQUIRE(s8.getFirstName() == "Antanas");
        REQUIRE(s8.getHomeworkMarks() == std::vector<int>{9, 8, 7, 6, 5});
        std::remove(filename.c_str());
    }

    SECTION("8 TESTAS: išvesties operatorius") {
        Student s8;
        s8.setFirstName("Antanas");
        std::ostringstream oss;
        oss << s8;
        REQUIRE(oss.str().find("Antanas") != std::string::npos);
    }

    SECTION("9 TESTAS: studentų nuskaitymas iš failo") {
        const std::string filename1 = "files/studentai3.txt";
        {
            std::ofstream filename1("files/studentai3.txt");
    filename1 << "antraste" << endl;
    filename1 << "Jonas Jonaitis 10 9 8 7 9 6" << endl;
    filename1 << "Vejas Vejukas 10 9 8 7 6 6" << endl;
    filename1 << "Petras Petrauskas 8 9 7 10 9 5" << endl;
    filename1.close();
        }

        std::vector<Student> students;
        Student::readFromFile(students, 3);
        REQUIRE(students.size() == 3);
        REQUIRE(students[0].getFirstName() == "Jonas");
        REQUIRE(students[1].getLastName() == "Vejukas");
        std::remove(filename1.c_str());
    }

    SECTION("10 TESTAS: išvedimas į failą") {
        const std::string filename2 = "files/testas2.txt";
        std::vector<Student> students = {Student(), Student(), Student()};
        {
            std::ofstream file(filename2);
            REQUIRE(file.is_open());
            for (const auto& s : students) file << s << "\n";
        }

        std::ifstream checkFile(filename2);
        std::string line;
        REQUIRE(std::getline(checkFile, line));
        std::remove(filename2.c_str());
    }

    SECTION("11 TESTAS: studentų išvedimas į konsolę") {
        std::vector<Student> students = {Student(), Student(), Student()};
        std::ostringstream oss;
        auto oldCoutBuffer = std::cout.rdbuf(oss.rdbuf());
        
        for (const auto& s : students) std::cout << s << "\n";
        std::cout.rdbuf(oldCoutBuffer);
        
        REQUIRE_FALSE(oss.str().empty());
    }

    SECTION("12 TESTAS: destruktorius") {
        const int before = dstCount;
        {
            Student temp;
        }
        REQUIRE(dstCount == before + 1);
    }
}