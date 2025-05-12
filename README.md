# Aprašymas

Programa, skirta apdoroti studentų duomenis.
Programos versijose analizuojamas bei tobulinamas programos našumas, efektyvumas bei paruošimas vartotojuj.

Yra sukurta programos dokumentacija - `dokumentacija.pdf`.

# Naudojimo instrukcijos

**Katalogai:**
- `analysis` - programos veikimo analizės rezultatai, naudojami tam tikrose programos versijose
- `docs` - doxygen failai
- `files` - programoje vykdymo metu naudojami .txt failai (įtrauktas į `.gitignore` ir atsiras tik paleidus programą)
- `include` - antraščių `.h` failai
- `src` - `.cpp` failai

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
| Tipas        | Aprašymas                                                                                                         |
|-------------|-------------------------------------------------------------------------------------------------------------------|
| Rankinis      | Vartotojas suveda duomenis ranka tiesiai į konsolę.                                                                |
| Automatinis   | Naudojamas vartotojui norint sugeneruoti atsitiktinius duomenis bei testavimui, naudojamas `istringstream`.        |
| Iš failo     | Skaitomi duomenys iš failo naudojant `ifstream` (v1.2 teste numatytas vienas dydis - 3, kitur galima rinktis iš 5 dydžių). |

## Duomenų išvestis
| Tipas      | Aprašymas                             |
|-----------|--------------------------------------|
| Į ekraną  | Duomenys atvaizduojami konsolėje per `cout <<` |
| Į failą   | Duomenys saugomi faile per `ostringstream` |



# Programos versijos

Kiekviena versija išsamiai aprašyta jos `README.md` faile.
Programos v1.0 versijos yra atskiroje `opp` repozitorijoje.

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
Pašalinti `deque` bei `list` versijų katalogai. Pritaikyta Rule of Five ir persidengimo operatoriai. Atliktas testas patikrinantis `Student` klasės metodų veikimą, testui naudojami papildomi `.txt` failai kurie susikuria automatiškai.

## v1.5
Sukurta nauja bazinė klasė `Zmogus`. `Student` klasė paversta į derived. Patikrinta, ar nauji metodai praeina testus iš versijos 1.2
Kad įsitikint, jog klasė `Zmogus` yra abstrakti, reikia atkomentuoti funkciją `void testZmogausClass()` failuose `functions.cpp` bei `functions.h`.

## v2.0
Sukurta klasę aprašanti dokumentacija, HTML ir TEX formatais, su sukompiliuotu PDF failu. Atlikti catch2 testai faile `src`/`catchTest.cpp`.
![Screenshot 2025-05-12 170611](https://github.com/user-attachments/assets/dcee5f63-1fb2-429b-95a2-f24a1fe4e3b7)

