# tema2-pclp
312CC Radu Andrei-Laurentiu
Tema 2 PCLP 1

Problema 1: Text Highlight
        Cerinta: evidentierea grupurilor cheie (cuvintele sau grupurile 
            de cuvinte care se afla in secventa urmatoare)
            first of, for, for each, from, in, is, is a, list of, 
            unit, or, while, int, float, double, string

        Idee de implementare: 
            Spargem fiecare linie de text in cuvinte si verificam ce fel de
            evidentiere trebuie sa facem, retinand pozitia pe care se afla cuvantul
            Cautam in linia de text cuvantul de pe acea pozitie si il evidentiem in 
            functie de caz(un cuvant sau doua cu tot cu spatiul dintre ele)
            Sunt trei tipuri de evidentieri pe care ne bazam:
            1) cuvant simplu(nu se afla in componenta unui grup)
            2) grup(doua cuvinte separate printr-un numar de spatii care formeaza 
            un grup cheie)
            3) cuvant care se afla intr0un grup dar este si cuvant cheie
        Durata implementare: 3h

Problema 2: Autocomplete
        Cerinta: crearea unui dictionar pe baza caruia se realizeaza autocomplete-ul 
        unor cuvinte

        Idee de implementare:
            In functie de categoria cuvantului citit facem o anumita operatie
            1) Pentru "cuvant" verificam daca face match cu vreun cuvant din dictionar
                In  caz afirmativ crestem prioritatea cuvantului din dictionar, 
                iar in caz contrar il adaugam in dictionar
            2) Pentru "cuvant*" afisam cuvantul fara * si il adaugam in dictionar 
            (daca acesta nu apare) sau ii crestem prioritatea(daca apare)
            3) Pentru "cuv" gasim cuvantul din dictionar cu care face match, 
            are prioritatea cea mai mare si este cel mai mic lexicografic
        Durata implementare: 2h

Problema 3: Calculator pe biti
        Cerinta: crearea unui calculator pentru realizarea a 4 tipuri de operatii pe biti:
        adunare, interschimare, rotatie la stanga si xor

        Idee de implementare:
            Retinem in doi vectori numerele din componenta operatiilor si operatiile
            Pentru fiecare tip de operatie avem cate o functie care va fi apelata dupa caz, 
            de vectorul de functii
            1)Adunare: pentru fiecare pozitie verificam starea bitilor(setat pe 1 sau resetat la 0)
            si retinem intr-o varibila "transport" daca 
                suma celor doi biti afecteaza urmatoarea pozitie
            2)Interschimbare: cream cele doua numere reprezentand pozitiile si setam/resetam 
            in functie de caz pozitiile
            3)Rotatie la stanga: 
                Pentru rotirea cu o singura pozitie:
                    pastram MSB, shiftuim rezultatul la stanga cu o pozitie si punem in 
                    pozitia LSB-ului MSB-ul anterior
                Realizam aceasta operatie de numarul al doilea din operatie % 4 ori 
                (avand doar 4 biti la oricare rotire cu un multiplu de 4, numarul ramane neschimbat)
            4)Xor: Verificam pentru fiecare pozitie daca bitii din cele doua numere corespunzatori 
            acelorasi pozitii sunt diferiti. In caz afirmativ setam pe 1 bitul din acea pozitie din 
            rezultat, iar in caz contrar resetam la 0
        
        Durata implementarii: 3h
            
