#include "utils.h"
#include "constants.h"

std::random_device rd;
std::mt19937 mt(rd());

// requests
string getYesNo() {
    string choice;
    while (true) {
        cin >> choice;
        if (isChoiceValid(choice)) break;
        cout << INVALID_CHOICE;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return choice;
}

int getSortType() {
    int sortType;
    while (true) {
        cout << ENTER_SORT_TYPE;
        string input;
        cin >> input;
        try {
            sortType = stoi(input);
            if (sortType >= 1 && sortType <= 4) break;
        } catch (const std::invalid_argument&) {
        }
        cout << INVALID_CHOICE;
    }
    return sortType;
}

int getPrintType() {
    int printType;
    while (true) {
        cout << ENTER_PRINT_TYPE;
        string input;
        cin >> input;
        try {
            printType = stoi(input);
            if (printType == 1 || printType == 2) break;
        } catch (const std::invalid_argument&) {
        }
        cout << INVALID_OUTPUT_TYPE_ERROR;
    }
    return printType;
}

int getMenuChoice() {
    int choice;
    while (true) {
        cout << MENU_TEXT;
        string input;
        cin >> input;
        try {
            choice = stoi(input);
            if (choice >= 0 && choice <= 2) break;
        } catch (const std::invalid_argument&) {
        }
        cout << INVALID_CHOICE;
    }
    return choice;
}

int getTestMenuChoice() {
    int choice;
    while (true) {
        cout << TEST_MENU_TEXT;
        string input;
        cin >> input;
        try {
            choice = stoi(input);
            if (choice >= 0 && choice <= 6) break;
        } catch (const std::invalid_argument&) {
        }
        cout << INVALID_CHOICE;
    }
    return choice;
}

int getProgramMenuChoice() {
    int choice;
    while (true) {
        cout << PROGRAM_MENU_TEXT;
        string input;
        cin >> input;
        try {
            choice = stoi(input);
            if (choice >= 1 && choice <= 5) break;
        } catch (const std::invalid_argument&) {
        }
        cout << INVALID_CHOICE;
    }
    return choice;
}

string GetFirstName(char menuChoice) {
    string firstName;
    if (menuChoice == '1' || menuChoice == '2') {
        while (true) {
            cout << ENTER_FIRST_NAME;
            cin >> firstName;
            if (isNameValid(firstName)) break;
            cout << INVALID_FIRST_NAME_ERROR;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } else {  
        firstName = getRandomFirstName();
        cout << "Studentas: " << firstName;
    }
    return firstName;
}

string GetLastName(char menuChoice) {
    string lastName;
    
    if (menuChoice == '1' || menuChoice == '2') {
        while (true) {
            cout << ENTER_LAST_NAME;
            cin >> lastName;
            if (isNameValid(lastName)) break;
            cout << INVALID_LAST_NAME_ERROR;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } else {  
        lastName = getRandomLastName();
        cout << " " << lastName << endl;
    }
    return lastName;
}

int GetExamMark(char menuChoice) {
    string tempMark;
    int examMark;
    if (menuChoice == '1') {
        while (true) {
            cout << ENTER_EXAM_MARK;
            cin >> tempMark;
            if (!isMarkValid(tempMark)) {
                cout << INVALID_EXAM_MARK_ERROR;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            examMark = stoi(tempMark);
            break;
        }
    } else {
        examMark = getRandomMark();
        cout << "Egzamino pazymys: " << examMark << endl;
    }  
    return examMark;
}

vector<int> GetHomeworkMarks(char menuChoice) {
    vector<int> marks;
    if (menuChoice == '1') {
        string tempMark;
        while (true) {
            cout << ENTER_MARK;
            cin >> tempMark;

            if (tempMark == "-1" && marks.empty()) {  
                cout << INVALID_MARKS_COUNT;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            } else if (tempMark == "-1") break;

            if (!isMarkValid(tempMark)) {
                cout << INVALID_MARK_ERROR;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            marks.push_back(stoi(tempMark));
        }
    } else {
        for (int i = 0; i < 5; i++) {
            marks.push_back(getRandomMark());
            cout << "Pažymys " << i + 1 << ": " << marks[i] << endl;
        }
    }
    return marks;
}

int getGroupType() {
    string groupType;
    while (true) {
        cout << ENTER_GROUP_TYPE;
        cin >> groupType;
        if (groupType == "1" || groupType == "2") break;
        cout << INVALID_GROUP_TYPE;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return stoi(groupType);
}

int getFileSize() {
    string size;
    while (true) {
        cout << ENTER_FILE_SIZE;
        cin >> size;
        if (stoi(size) >= 1 && stoi(size) <= 5) break;
        cout << INVALID_FILE_SIZE;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    int sizeInt = stoi(size); 

    switch (sizeInt) {
        case 1: return 1000;
        case 2: return 10000;
        case 3: return 100000;
        case 4: return 1000000;
        case 5: return 10000000;
        default: return 0;
    }
}

// validations
bool isNameValid(string name) {
    for (char c : name) {
        if (!isalpha(c)) return false;
    }
    return true;
}

bool isMarkValid(string mark) {
    for (char c : mark) {
        if (!isdigit(c)) return false;
    }
    int markInt = stoi(mark);
    if (markInt < 1 || markInt > 10) return false;
    return true;
}

bool isChoiceValid(string choice) {
    if (choice != "taip" && choice != "ne") return false;
    return true;
}

// random generators
string getRandomFirstName() {
    string names[] = {"Jonas", "Petras", "Mantas", "Dovydas", "Karolis", "Tomas", "Justinas", "Rokas", "Marius", "Aurimas"};
    return names[rand() % 10];
}

string getRandomLastName() {
    string surnames[] = {"Jonaitis", "Petraitis", "Kazlauskas", "Dargis", "Jankauskas", "Zujus", "Adomaitis", "Bagdonas", "Vasiliauskas", "Butkus"};
    return surnames[rand() % 10];
}

int getRandomMark() {
    std::uniform_int_distribution<int> mark(1, 10);
    return mark(mt);
}

// order track
string printCount(int count) {
    string temp;
    // Skaičius 1, tačiau ne 11
if (count % 10 == 1 && count % 100 != 11) {
    temp = " kartą";
} 
// Skaičiai tarp 2 ir 4, tačiau ne 12-14
else if ((count % 10 >= 2 && count % 10 <= 4) && (count % 100 < 10 || count % 100 >= 20)) {
    temp = " kartus";
} 
// Visi kiti atvejai
else {
    temp = " kartų";
}
return temp;
}