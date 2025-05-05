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


# Versija 1.2
# "Rule of five" ir operatorių persidengimas

`Studentas` klasėje pilnai realizuoti "Rule of Five" metodai:
* Default konstuktorius
* Kopijavimo konstruktorius
* Kopijavimo priskyrimo operatorius
* Perkėlimo konstruktorius
* Perkėlimo priskyrimo operatorius
* Destruktorius

Perdengti >> ir << operatoriai:
* Kad palaikytų įvestį iš vartotojo (konsolės), iš stringo (testavimui) ir iš failo
* Kad palaikytų išvestį į ekraną ir į failą

Faile `functions` sukurtas testas `testRuleOfFive()`, kuris patikrina visus metodus.

  
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


## testavimas
Funkcija `testRuleOfFive()` tikrina:

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
Pašalinti `deque` bei `list` versijų katalogai.
