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
# Rule of five ir operatorių persidengimas

Studentas klasėje pilnai realizuoti „Rule of Five“ metodus:
default konstuktorių
kopijavimo konstruktorių
kopijavimo priskyrimo operatorių
perkelimo konstruktorių
perkelimo priskyrimo operatorių
destruktorių
Perdengti >> ir << operatorius:
Kad palaikytų įvestį iš vartotojo (cin), iš stringo (testavimui), iš failo
Kad palaikytų išvestį į ekraną ir į failą
Sukurti testą (testuotiRuleOfFive()), kuris patikrina visus metodus.

  
## duomenų įvestis
 rankiniu, automatiniu, is failo


## duomenų išvestis
i ekrana, i faila


## testavimas
Funkcija StudentMethodsTest() tikrina:
1. Default konstuktorių
2. Kopijavimo konstruktorių
3. Kopijavimo priskyrimo operatorių
4. Perkėlimo konstruktorių
5. Perkėlimo priskyrimo operatorių
6. Įvesties operatorių
   6.1 Įvestį iš konsolės
   6.2 Įvestį iš failo
7. Išvesties operatorių
8. Nuskaitymą iš failo
9. Išvedimą į failą
10. Išvedimą į konsolę
11. Destruktorių

## Rule of five:
![image](https://github.com/user-attachments/assets/c7df7e24-a823-40a5-9d61-87d07af39509)

## Įvestis:

## Išvestis:
![image](https://github.com/user-attachments/assets/0ea244ca-53b1-4e7b-895b-90f9d2f0dd81)

## Destruktorius:
![image](https://github.com/user-attachments/assets/79f7f806-f530-4832-bc07-a181af206bab)


## failai
studentai3.txt
testas1.txt
testas2.txt
testas3.txt

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
