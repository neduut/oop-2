#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "mylib.h"

// user prompts
const string ENTER_FIRST_NAME = "Įveskite vardą: ";
const string ENTER_LAST_NAME = "Įveskite pavardę: "; 
const string ENTER_MARK = "Įveskite namų darbų pažymį (norint sustoti, įveskite -1): "; 
const string ENTER_MARK_IN_MIXED = "Įveskite namų darbų pažymį: ";
const string ENTER_EXAM_MARK = "Įveskite egzamino pažymį: ";
const string ENTER_GROUP_TYPE = "Pasirinkite grupavimo tipą (1 - vidurkis / 2 - mediana): ";
const string ENTER_SORT_TYPE = "Pasirinkite, pagal ką rūšiuoti studentus (1 - vardą / 2 - pavardę / 3 - galutinį balą (vid.) / 4 - galutinį balą (med.)): ";
const string ENTER_PRINT_TYPE = "Pasirinkite, kur išvesti duomenis (1 - ekraną / 2 - failą): ";
const string ENTER_MARKS_COUNT = "Įveskite namų darbų pažymių skaičių: ";
const string ADD_ANOTHER_MARK = "Ar norite įvesti dar vieną namų darbą? (taip/ne): ";
const string ADD_ANOTHER_STUDENT = "Ar norite įvesti dar vieną studentą? (taip/ne): ";

constexpr char MENU_TEXT[] = 
    "\nPasirinkite, ką norite daryti:\n"
    "1 - Vykdyti programą\n"
    "2 - Atlikti pasirinktus tyrimus\n"
    "0 - Nieko nenoriu daryti\n";

    constexpr char TEST_MENU_TEXT[] =
    "\nPasirinkite tyrimą:\n"
    "1 - failu generavimas\n"
    "2 - programos veikimo laikas\n"
    "3 - konteinerio testas\n" 
    "4 - pirma strategija\n"
    "5 - antra strategija\n"
    "6 - trecia strategija (sparčiausia)\n" 
    "0 - Užbaigti programa\n";

constexpr char PROGRAM_MENU_TEXT[] = 
    "\nPasirinkite, ką norite daryti:\n"
    "1 - Įvesti viską rankiniu būdu\n"
    "2 - Generuoti atsitiktinius pažymius (vardus įvesti ranka)\n"
    "3 - Generuoti atsitiktinius vardus ir pažymius\n"
    "4 - Skaityti iš failo\n"
    "5 - Užbaigti programą\n";

constexpr char ENTER_FILE_SIZE[] = 
    "\nPasirinkite failo dydį:\n"
    "1 - 1 000\n"
    "2 - 10 000\n"
    "3 - 100 000\n"
    "4 - 1 000 000\n"
    "5 - 10 000 000\n";

// errors
const string INVALID_FIRST_NAME_ERROR = "\nKlaida: įvestas netinkamas vardas! "; 
const string INVALID_LAST_NAME_ERROR = "\nKlaida: įvesta netinkama pavardė! "; 
const string INVALID_MARK_ERROR = "\nKlaida: pažymys turi būti sveikasis skaičius nuo 1 iki 10! "; 
const string INVALID_EXAM_MARK_ERROR = "\nKlaida: egzamino pažymys turi būti sveikasis skaičius nuo 1 iki 10! "; 
const string INVALID_MARKS_COUNT_ERROR = "\nKlaida: pažymių skaičius turi būti sveikasis skaičius ir mažesnis nei 10! ";
const string INVALID_MENU_CHOICE = "\nKlaida: netinkamas meniu pasirinkimas! ";
const string INVALID_CHOICE = "\nKlaida: netinkamas pasirinkimas! ";
const string INVALID_SIZE_ERROR = "\nKlaida: dydis turi būti sveikasis skaičius! ";
const string INVALID_MARKS_COUNT = "\nKlaida: turite įvesti bent vieną pažymį! ";
const string INVALID_OUTPUT_TYPE_ERROR = "\nKlaida: netinkamas išvedimo tipas! ";
const string FILE_OPEN_ERROR = "\nKlaida: nepavyko atidaryti failo! ";
const string FILE_READ_ERROR = "\nKlaida: nepavyko nuskaityti failo! ";
const string EMPTY_ARRAY_ERROR = "\nKlaida: pažymių masyvas tuščias! ";
const string INVALID_GROUP_TYPE = "\nKlaida: netinkamas grupavimo tipas! ";
const string INVALID_FILE_SIZE = "\nKlaida: netinkamas failo dydis! ";

// success 
const string FILE_READ_SUCCESS = "\nDuomenys nuskaityti sėkmingai! ";
const string FILE_WRITE_SUCCESS = "\nDuomenys įrašyti sėkmingai! ";
const string TEST_SECCESS = "\nLaiko tyrimo rezultatai įrašyti į failą: ";


#endif