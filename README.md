# Aprašymas

Programa, skirta apdoroti studentų duomenis.
Programos versijose analizuojamas bei tobulinamas programos našumas ir efektyvumas.

# Naudojimo instrukcijos

**Kad paleisti programą, turite atlikti šiuos veiksmus:**

1. Įeikite į norimos versijos katalogą
2. Paleiskite `run.bat` failą

  `run.bat` failas atliks šiuos veiksmus:
   - Sukurs build katalogą 
   - Paleis CMake, kad sugeneruotų `Makefile`
   - Sukompiliuos projektą naudodamas make komandą
   - Paleis sukompiliuotą programą terminale

**Reikalavimai**

- Operacinė sistema: Windows 10 x64-bit arba naujesnė versija
- Įdiegta CMake (3.25 arba naujesnė versija)
- Kompiliatorius: g++ (su C++11 arba naujesne versija)

## Duomenų įvestis
| Tipas        | Aprašymas                                                                 |
|-------------|---------------------------------------------------------------------------|
| Rankinis     | Vartotojas suveda duomenis ranka tiesiai į konsolę                        |
| Automatinis  | Naudojamas testavimui su `istringstream`                         |
| Iš failo    | Skaitomi duomenys iš failo naudojant `ifstream` (v1.2 teste numatytas vienas dydis - 3, kitur galima rinktis iš 5 dydžių) |

## Duomenų išvestis
| Tipas      | Aprašymas                             |
|-----------|--------------------------------------|
| Į ekraną  | Duomenys atvaizduojami konsolėje per `cout <<` |
| Į failą   | Duomenys saugomi faile per `ostringstream` |


# Versija 1.5
# Bazinė ir derived klasės

Sukurta nauja bazinė klasė `Zmogus`, klasė `Student` paversta į derived.
Faile `functions` sukurtas naujas testas `testZmogusClass()`, kuris patikrina, ar `Zmogus` klasė yra abstrakti.
Panaudotas testas iš v1.2 `testRuleOfFive()`, kuris patikrina visus metodus.

## `Zmogus` bazinė klasė

**Protected atributai**
- `firstName_` - studento vardas
- `lastName_ ` - studento pavardė

**Konstruktoriai**
- `Zmogus()` – default konstruktorius
- `Zmogus(const std::string& firstName, const std::string& lastName)` – konstruktorius su parametrais
- `virtual ~Zmogus() = 0` – virtualus abstrakčios klasės destruktorius 

**Virtualios funkcijos**
- `virtual void read(std::istream& is) = 0` – input'ui
- `virtual void print(std::ostream& os) const = 0` – output'ui

**Getteriai ir setteriai**
- `string getFirstName() const` – grąžina vardą
- `string getLastName() const` – grąžina pavardę
- `void setFirstName(const std::string& firstName)` – nustato vardą
- `void setLastName(const std::string& lastName)` – nustato pavardę

**Globalūs operatoriai**
- `inline std::istream& operator>>(std::istream& is, Zmogus& zmogus)`
- `inline std::ostream& operator<<(std::ostream& os, const Zmogus& zmogus)`

## `Student` išvestinė klasė

**Privatūs atributai**
- `std::vector<int> marks_` - pažymiai
- `int examMark_ ` - egzamino pažymys
- `float avgFinal_;` - galutinis pažymys pagal vidurkį
- `float medianFinal_;` - galutinis pažymys pagal medianą

**Privatūs metodai**
- `float average(const std::vector<int>& marks) const` - apskaičiuoją galutinį pažymį pagal vidurkį
- `float median(const std::vector<int>& marks) const` - apskaičiuoją galutinį pažymį pagal medianą

**Konstruktoriai**
- `Student()` – default konstruktorius
- `Student(std::istream& is)` – konstruktorius su input stream'u
- `Student::Student(const Student& other)` – kopijavimo konstruktorius
- `Student::Student(Student&& other) noexcept` - perkėlimo konstruktorius

**Persidengimo operatoriai**
- `Student& Student::operator=(const Student& other)` - kopijavimo operatorius
- `Student& Student::operator=(Student&& other) noexcept` - perkėlimo operatorius

**Getteriai ir setteriai**
- `const std::vector<int>& getHomeworkMarks() const` - grąžina pažymius
- `int getExamMark() const` – grąžina egzamino pažymį
- `float getAvgFinal() const` – grąžina galutinį pažymį pagal vidurkį
- `float getMedianFinal() const` – grąžina galutinį pažymį pagal medianą
- `void setMarks(std::vector<int> marks)` – nustato pažymius
- `void setExamMark(int examMark)` - nustato galutinį pažymį

**Įgyvendintos virtualios funkcijos**
- `void Student::read(std::istream& is)` – input'ui
- `void Student::print(std::ostream& os) const` – output'ui

**Kiti metodai**
- `std::istream& readStudent(std::istream& is)` - input'ui
- `void calculateFinalMarks();` - iškviečia 2 galutinio pažymio skaičiavimo funkcijas (vid. ir med.)
- `static void readInput(std::vector<Student>& students, char menuChoice);` - skaito studento duomenis įvestus konsolėje
- `static void readFromFile(std::vector<Student>& students, int fileSize);` - skaito studento duomenis iš failo

## Testavimas

**1. Funkcija `testZmogusClass()`**
Tikrina ar klasė yra abstrakti. Norint pratestuoti, reikia atkomentuoti šią funkciją.

![image](https://github.com/user-attachments/assets/2d6e6ae8-1465-44f5-ae12-73c9fcf4c4f0)

Kadangi `Zmogus zmogus` nėra kompiliuojamas, klasė yra abstrakti. 

**2. Funkcija `testRuleOfFive()`**
Tikrina:
1. Default konstruktorius
2. Kopijavimo konstruktorius
3. Kopijavimo priskyrimo operatorius
4. Perkėlimo konstruktorius
5. Perkėlimo priskyrimo operatorius
6. Įvesties operatoriai
    * 6.1 Įvestį iš konsolės
    * 6.2 Įvestį iš failo
7. Išvesties operatorių
8. Nuskaitymą iš failo
9. Išvedimą į failą
10. Išvedimą į konsolę
11. Destruktorių

## Rule of five:
![image](https://github.com/user-attachments/assets/c7df7e24-a823-40a5-9d61-87d07af39509)

## Įvestis:
![image](https://github.com/user-attachments/assets/9d6722bc-afc5-472a-a318-44a6cc3a8237)

## Išvestis:
![image](https://github.com/user-attachments/assets/0ea244ca-53b1-4e7b-895b-90f9d2f0dd81)
![image](https://github.com/user-attachments/assets/a298d5f2-3d06-42ce-b860-54dd83f0d5f1)

## Destruktorius:
![image](https://github.com/user-attachments/assets/79f7f806-f530-4832-bc07-a181af206bab)


## Papildomi failai testavimui
`testas1.txt` - 6.2 testui 
`studentai3.txt` - 8 testui
`testas2.txt` - 9 testui



# Programos versijos

## v.pradinė
C++ programa, skirta studentų pažymiams apskaičiuoti, naudojant vidurkio ir medianos metodus. Vartotojai įveda studentų vardus, namų darbų pažymius ir egzaminų rezultatus, o programa pateikia suformatuotus rezultatus. `Makefile` automatizuoja kompiliavimą, o `gitignore` pašalina nereikalingus failus iš „Git“ sekimo.

## v0.1
Optimizuoti failai ir pataisytos galutinio pažymio apskaičiavimo funkcijos. Įgyvendinti du skirtingi vykdomieji failai: vienas su vektorių masyvais, kitas – su dinaminiais C masyvais pažymiams. Pridėta `meniu` funkcija, leidžianti atsitiktinai generuoti pasirinktus duomenis.

## v0.2
Prie meniu pridėta failų skaitymo parinktis, rūšiavimo parinktys (pagal vardą, pavardę ir galutinį pažymį) ir parinktis pasirinkti, ar spausdinti rezultatą į monitorių, ar į failą. Taip pat pridėti `TimeMeasurement` failai, skirti sekti laiką ir apskaičiuoti vidutinius testavimo laikus.

## v0.3
Pridėtas išimčių tvarkymas funkcijoms `readFromFile`, `output` ir `sortStudents`. Sukurti aplankai ir atnaujintas `makefile`.

## v0.4
Pridėta failų generavimo funkcija su pasirinktu dydžiu, studentų grupavimas į dvi grupes pagal pasirinktą galutinio pažymio tipą ir dvi laiko matavimo testavimo funkcijos. Pakeista `timeMeasurement` funkcija, kad testų rezultatai būtų spausdinami į failą, o ne į konsolę. Atnaujintas `README`, įtraukiant laiko matavimo testų rezultatus. Optimizuotos kelios funkcijos, siekiant geresnio našumo.

## v1.0prad
Pridėta nauja laiko testavimo funkcija ir versija su 3 skirtingais konteineriais: `vector`, `deque` ir `list`. Atliktas laiko tyrimas, o rezultatai pateikti faile `README`.

## v1.0
Pridėti testavimai su trimis skirtingomis strategijomis studentų rūšiavimo į grupes funkcijai. Optimizuotas geriausias rūšiavimas (`vector` konteinerio su pirma strategija). Atliktas spartos bei atminties naudojimo tyrimas, o rezultatai pateikti faile `README`. Pridėtas programos diegimo bei paleidimo  `CMake` failas bei `README` aprašyta įdiegimo instrukcija.

## v1.1
`Vector` konteinerio versijoje duomenų struktūra pakeista iš `struct` į `class`. Atlikti programos spartos bei SSD naudojimo testai lyginant `struct` ir `class` su skirtingomis optimizavimo vėliavėlėmis: `O1`, `O2` ir `O3`. Tyrimo rezultatai aprašyti `README` faile. 

## v1.2
Pašalinti `deque` bei `list` versijų katalogai. Pritaikyta Rule of Five ir persidengimo operatoriai. Atliktas testas patikrinantis `Student` klasės metodų veikimą.

## v1.5
Sukurta nauja bazinė klasė `Zmogus`. `Student` klasė paversta į derived. Patikrinta, ar nauji metodai praeina testus iš versijos 1.2
