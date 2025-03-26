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



# Spartos tyrimai 

1. Konteinerių tyrimas (v1.0)
2. Strategijų tyrimas (v1.0)
3. Struct ir class tyrimas (v1.1)

Testavimo sistemos parametrai:
- CPU - AMD Ryzen AI 9 HX 370 (12 fizinių ir 24 loginiai branduoliai)
- GPU - AMD Radeon 890M (16 GB)
- RAM - 32.0 GB LPDDR5x 
- SSD - 2 TB
- Kompiliatorius - GCC
- IDE - Visual Studio Code

Visiems testams buvo naudojami tie patys failai, užtikrinant tyrimų patikimumą.
  


# 1. Konteinerių tyrimas (v1.0)

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

Sukiekvienu failu buvo atlikta po 5 testus. Visų testų rezultatus galima rasti `analysis` -> `struct` -> `containerTests` kataloge.

Žemiau pateikiami atliktų testų rezultatų vidurkiai (sekundėmis):

![image](https://github.com/user-attachments/assets/209393ed-6b71-455f-b411-85acf06023bf)

Tyrimas parodė, kad naudojant didesnius failus, `vector` buvo efektyviausias, o `deque` buvo mažiausiai efektyvus.



# 2. Strategijų tyrimas (v1.0)

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

Žemiau pateikiami atliktų testų rezultatų vidurkiai (sekundėmis):

![image](https://github.com/user-attachments/assets/10b7ad8e-6318-4132-b525-47c0d6fcd5fe)

Žemiau pateikiamas atminties naudojimas su 10 000 000 įrašų failu:

**Vector** 
![vector1](https://github.com/user-attachments/assets/86ef0846-6e8e-43e2-a077-047dd9406407)

**Deque** 
![deque1](https://github.com/user-attachments/assets/9985949c-1c03-44d4-a1fc-7aba5dadfd8d)

**List**
![list1](https://github.com/user-attachments/assets/fd4726ee-3d4a-4a5d-a755-8bb14e98a23b)

Tyrimas parodė, kad naudojant didesnius failus, `vector` buvo efektyviausias, o `deque` buvo mažiausiai efektyvus, nes naudojo daugiausiai atminties, `list` naudojo žymiai mažiau atminties nei `deque`, bet `vector` vistiek išliko efektyviausias atminties požiūriu.


## Antra strategija

Šioje strategijoje studentų konteineris yra skaidomas į "vargšiukų" konteinerį, tačiau tik vienas naujas konteineris yra sukuriamas. Jei studentas atitinka "vargšiuko" kriterijus, jis perkeliamas į šį naują konteinerį, o iš bendro studentų konteinerio ištrinamas. Po to bendrame konteineryje lieka tik "kietiakai".

Žemiau pateikiami atliktų testų rezultatų vidurkiai (sekundėmis):

![image](https://github.com/user-attachments/assets/f59092d6-65fe-497b-9d0c-c650b29e8946)

Žemiau pateikiamas atminties naudojimas su 10 000 000 įrašų failu:

**Vector** 
![vector2](https://github.com/user-attachments/assets/984edb45-7353-4805-adfa-c54352518c8b)

**Deque**
![deque2](https://github.com/user-attachments/assets/453e9517-9efa-4a38-a1e1-35f84358e80c)

**List**
![list2](https://github.com/user-attachments/assets/993f7511-a7a3-48cc-aa78-354b3dcf736f)

Tyrimas parodė, kad antrojoje strategijoje `vector` išliko efektyviausias, kaip ir pirmoje strategijoje, `deque` buvo mažiau efektyvus ir naudoja daugiau atminties lyginant su pirma strategija, o `list` vis tiek buvo mažiausiai efektyvus tiek laiko, tiek atminties atžvilgiu, kaip ir pirmoje strategijoje.


## Trečia strategija

Šioje strategijoje naudojamas bendro studentų konteinerio skaidymas (rūšiavimas) panaudojant greičiausiai veikianti iš pirmos arba antros strategijos, įtraukiant "efektyvius" darbo su konteineriais metodus. 
Buvo optimizuotas `vector` tipo konteineris su pirma strategija.

Žemiau pateikiami atliktų testų rezultatų vidurkiai (sekundėmis):

![image](https://github.com/user-attachments/assets/8b77907f-78ab-4319-b2d5-59cae73c90ef)

Žemiau pateikiamas atminties naudojimas su 10 000 000 įrašų failu:

![vector3](https://github.com/user-attachments/assets/8a2cd813-2709-46ad-86c0-c9ed2632f1f4)

Tyrimas parodė, kad optimizuotas `deque` yra tiek efektyvesnis, tiek naudoja mažiau atminties nei pirmoje strategijoje. Pritaikius `std::partition` metodą, failo su 10 000 000 įrašų atžvilgiu, `vector` tapo efektyvesnis ~0.5 sek. 



# 3. Struct ir class tyrimas (v1.1)

su 100 000 ir 1 000 000 failais
exe failu dydziai (struct ir class) su opt flagais
greitis (struct ir class) su opt flagais
vector versija, 3 strategija


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
dirbta tik su vector versija