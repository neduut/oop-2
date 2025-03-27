# Naudojimo instrukcijos

Yra 3 skirtingos programos versijos: vector, deque ir list, jas galima rasti atitinkamuose aplankuose. Kiekviena versija naudoja atskirą šaltinio failų rinkinį ir CMake konfigūraciją.

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



# Tyrimai

Buvo atlikti trys programos tyrimai:
1. Konteinerių spartos analizė (v1.0)
2. Strategijų spartos ir RAM naudojimo analizė (v1.0)
3. Struktūrų ir klasių spartos bei SSD naudojimo analizė (v1.1)

Testavimo sistemos parametrai:
- CPU - AMD Ryzen AI 9 HX 370 (12 fizinių ir 24 loginiai branduoliai)
- GPU - AMD Radeon 890M (16 GB)
- RAM - 32.0 GB LPDDR5x 
- SSD - 2 TB
- Kompiliatorius - GCC
- IDE - Visual Studio Code

Visiems testams buvo naudojami tie patys failai, užtikrinant tyrimų patikimumą.
  

# 1. Konteinerių spartos analizė (v1.0)

Buvo tiriamos šios operacijos:
1. Duomenų nuskaitymas iš failų 
2. Studentų rūšiavimas didėjimo tvarka konteineryje 
3. Studentų skirstymas į dvi grupes 

Kiekvienas konteineris (`vector`, `deque` ir `list`) buvo testuojamas su penkiais skirtingo dydžio failais, kurių įrašų skaičius buvo: 
- 1 000
- 10 000
- 100 000
- 1 000 000
- 10 000 000

Su kiekvienu failu buvo atlikta po 5 testus. Visų testų rezultatus galima rasti `analysis` -> `struct` -> `containers` kataloge.

Žemiau pateikiami atliktų spartos testų rezultatų vidurkiai (sekundėmis):

| Duomenų struktūra | Operacija | 1000 | 10 000 | 100 000 | 1 000 000 | 10 000 000 |
|---|---|---|---|---|---|---|
| Vector | Duomenų nuskaitymas | 0.00394612 | 0.03218134 | 0.2922336 | 1.720884 | 13.5894 |
| Vector | Studentų rikiavimas | 0.00242398 | 0.02646942 | 0.2215282 | 1.758552 | 17.99632 |
| Vector | Studentų rūšiavimas | 0.0007038 | 0.00822146 | 0.04376994 | 0.3579696 | 4.901402 |
| Deque | Duomenų nuskaitymas | 0.0067162 | 0.06251178 | 0.6036332 | 3.023692 | 40.09678 |
| Deque | Studentų rikiavimas | 0.0043023 | 0.05051884 | 0.4534964 | 3.297476 | 54.56224 |
| Deque | Studentų rūšiavimas | 0.00163982 | 0.01585616 | 0.09194708 | 0.7219982 | 18.87748 |
| List | Duomenų nuskaitymas | 0.00491358 | 0.04391852 | 0.4196124 | 3.85372 | 35.98742 |
| List | Studentų rikiavimas | 0.00041554 | 0.00631776 | 0.09059564 | 1.182192 | 18.24816 |
| List | Studentų rūšiavimas | 0.00125186 | 0.01564666 | 0.1747374 | 1.741926 | 18.07282 |

Tyrimas parodė, kad naudojant didesnius failus, `vector` buvo efektyviausias, o `deque` buvo mažiausiai efektyvus.



# 2. Strategijų spartos ir RAM naudojimo analizė (v1.0)

Buvo tiriama studentų rūšiavimo į grupes operacija pagal tris skirtingas strategijas.

Kiekvienas konteineris (`vector`, `deque` ir `list`) buvo testuojamas su penkiais skirtingo dydžio failais, kurių įrašų skaičius buvo: 
- 1 000
- 10 000
- 100 000
- 1 000 000
- 10 000 000

Sukiekvienu failu buvo atlikta po 5 testus. Visų testų rezultatus galima rasti `analysis` -> `struct` -> `strategies` kataloge.


## Pirma strategija

Šioje strategijoje bendras studentų konteineris (`vector`, `deque` ir `list`) yra suskirstomas į du naujus konteinerius pagal studento pažymį. Vienas konteineris talpina "vargšiukus", kitas — "kietiakus". Kiekvienas studentas egzistuoja tiek bendrame konteineryje, tiek viename iš suskirstytų konteinerių. 

Žemiau pateikiami atliktų spartos testų rezultatų vidurkiai (sekundėmis):

| 1 strategija | 1000 | 10 000 | 100 000 | 1 000 000 | 10 000 000 |
|---|---|---|---|---|---|
| Vector | 0.00055988 | 0.00486994 | 0.03585648 | 0.197347 | 1.6541916 |
| Deque | 0.00087304 | 0.00626222 | 0.06931568 | 0.6622848 | 9.665372 |
| List | 0.00102564 | 0.00690396 | 0.0817173 | 0.799738 | 7.998806 |

Žemiau pateikiamas RAM naudojimas su 10 000 000 įrašų failu:

| Duomenų struktūra | MB |
|---|---|
| Vector | 3 305 |
| Deque | 15 170 |
| List | 5 962 |

Tyrimas parodė, kad naudojant didesnius failus, `vector` buvo efektyviausias, o `deque` buvo mažiausiai efektyvus, nes naudojo daugiausiai atminties, `list` naudojo žymiai mažiau atminties nei `deque`, bet `vector` vistiek išliko efektyviausias atminties požiūriu.


## Antra strategija

Šioje strategijoje studentų konteineris yra skaidomas į "vargšiukų" konteinerį, tačiau tik vienas naujas konteineris yra sukuriamas. Jei studentas atitinka "vargšiuko" kriterijus, jis perkeliamas į šį naują konteinerį, o iš bendro studentų konteinerio ištrinamas. Po to bendrame konteineryje lieka tik "kietiakai".

Žemiau pateikiami atliktų spartos testų rezultatų vidurkiai (sekundėmis):

| 2 strategija | 1000 | 10 000 | 100 000 | 1 000 000 | 10 000 000 |
|---|---|---|---|---|---|
| Vector | 0.00183944 | 0.01419072 | 0.169226 | 2.071518 | 23.32422 |
| Deque | 0.00336874 | 0.02369356 | 0.3422922 | 3.955618 | 51.726 |
| List | 0.0015255 | 0.01213894 | 0.2054402 | 2.608398 | 33.21178 |

Žemiau pateikiamas RAM naudojimas su 10 000 000 įrašų failu:

| Duomenų struktūra | MB |
|---|---|
| Vector | 3 611 |
| Deque | 11 607 |
| List | 5 259 |

Tyrimas parodė, kad antrojoje strategijoje `vector` išliko efektyviausias, kaip ir pirmoje strategijoje, `deque` buvo mažiau efektyvus ir naudoja daugiau atminties lyginant su pirma strategija, o `list` vis tiek buvo mažiausiai efektyvus tiek laiko, tiek atminties atžvilgiu, kaip ir pirmoje strategijoje.


## Trečia strategija

Šioje strategijoje naudojamas bendro studentų konteinerio skaidymas (rūšiavimas) panaudojant greičiausiai veikianti iš pirmos arba antros strategijos, įtraukiant "efektyvius" darbo su konteineriais metodus. 
Buvo optimizuotas `vector` tipo konteineris su pirma strategija.

Žemiau pateikiami atliktų spartos testų rezultatų vidurkiai (sekundėmis):

| 3 strategija | 1000 | 10 000 | 100 000 | 1 000 000 | 10 000 000 |
|---|---|---|---|---|---|
| Vector | 0.00015976 | 0.0016721 | 0.01237 | 0.125375 | 1.168786 |

Žemiau pateikiamas RAM naudojimas su 10 000 000 įrašų failu:

| Duomenų struktūra | MB |
|---|---|
| Vector | 3 067 |

Tyrimas parodė, kad optimizuotas `deque` yra tiek efektyvesnis, tiek naudoja mažiau atminties nei pirmoje strategijoje. Pritaikius `std::partition` metodą, failo su 10 000 000 įrašų atžvilgiu, `vector` tapo efektyvesnis ~0.5 sek. 



# 3. Struct ir class tyrimas (v1.1)

Šiame tyrime buvo naudojamas greičiausias konteineris (`vector`) ir greičiausia strategija (trečia) iš v1.0 versijos. Buvo lyginamas `struct` ir `class` duomenų struktūrų spartos bei SSD disko vietos naudojimas, kiekvienai iš jų taikant tris optimizavimo vėliavėles: `O1`, `O2` ir `O3`.

Buvo tiriamos šios operacijos:
1. Duomenų nuskaitymas iš failų
2. Studentų skirstymas į dvi grupes
3. Duomenų išvedimas į du naujus failus

`Struct` ir `class` buvo testuojamos su penkiais skirtingo dydžio failais, kurių įrašų skaičius buvo:
- 100 000
- 1 000 000
  
Kiekvienam failui buvo atlikti penki testai su kiekviena optimizavimo vėliavėle(`O1`, `O2` ir `O3`). Visų testų rezultatus galima rasti `analysis` -> `struct`/`class` -> `flags` kataloge.

Žemiau pateikiami atliktų spartos testų rezultatų vidurkiai (sekundėmis):

| Struct/Class | Failo dydis | Optimizavimo vėliavėlė | Nuskaitymas | Rūšiavimas | Išvedimas | Bendras laikas |
|---|---|---|---|---|---|---|
| struct | 100000 | O1 | 0.07926 | 0.003796 | 0.185189 | 0.272186 |
| class | 100000 | O1 | 0.13900934 | 0.02303108 | 0.2710244 | 0.4500928 |
| struct | 100000 | O2 | 0.081719 | 0.003677 | 0.182538 | 0.272865 |
| class | 100000 | O2 | 0.14096842 | 0.02757548 | 0.2815516 | 0.469704 |
| struct | 100000 | O3 | 0.078733 | 0.004036 | 0.185513 | 0.272133 |
| class | 100000 | O3 | 0.13674508 | 0.02266928 | 0.2793608 | 0.455975 |
| struct | 1000000 | O1 | 0.80038 | 0.040785 | 1.80158 | 2.68869 |
| class | 1000000 | O1 | 1.009460 | 0.1605456 | 2.010372 | 3.301386 |
| struct | 1000000 | O2 | 0.780445 | 0.042006 | 1.77595 | 2.62261 |
| class | 1000000 | O2 | 1.025244 | 0.1790852 | 2.01586 | 3.332436 |
| struct | 1000000 | O3 | 0.77838 | 0.041662 | 1.74775 | 2.62056 |
| class | 1000000 | O3 | 0.957151 | 0.156714 | 1.981448 | 3.199592 |

Žemiau pateikiama SSD naudojama vieta (KB):

| Struct/Class | O1 | O2 | O3 |
|---|---|---|---|
| struct | 128 | 127 | 149|
| class | 116 | 128 | 167 |

Tyrimas parodė, kad naudojant `struct` duomenų struktūrą, programos vykdymo laikas ir SSD disko vietos naudojimas buvo mažesni, palyginti su `class` duomenų struktūra. Optimizavimo vėliavėlės `O1`, `O2` ir `O3` turėjo minimalų poveikį programos spartai ir SSD disko vietos naudojimui.


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
