#Pa Tema1
##Ionescu Cristina 323CC


                ---- Problema Feribot ----

- Ideea de la care am plecat este de a cauta cu divid et impera solutia buna
pornind de la valoarea maxima a greutatii din sir la suma tuturor greutatilor

ex:
        10 5
        3 4 2 1 6 7 1 2 2 3

- facem divide et impera pe:
        7 8 ... 30 31

- la fiecare valoare "gasita" parcurgem sirul de greutati si vedem de cate 
feriboturi avem nevoie pentru a transporta masinile.
   * daca numarul este prea mic vom continua cautarea in dreapta
   * daca numarul este prea mare vom cauta in stanga
   * daca am gasit o greutate valida, o retinem, si mai cautam in stanga pentru
a vedea daca gasim o valoare mai mica a greutatii care sa fie valida
- repetam aceasta cautare pana cand gasim greutatea cautata

- [Complexitate] O( nlog(suma - el_maxim) )


                ---- Problema Nostory ----

        * Prima parte

- aici doar am sortat crescator vectorul a
- si descrescator vectorul b
- calculam suma luand maximul din fiecare pereche

ex: 
        1
        3
        1 5 10          =>      1 5 10
        6 3 9           =>      9 6 3
        -------------------------------
                        sum =   9 + 6 + 10
- [Complexitate] O( nlog(n) )

        * A doua parte

- aici vom crea 2 vectori 
- maxV in care punem maximul din fiecare pereche
- minV in care punem minimul din fiecare pereche
- apoi sortam maxV crescator
- minV sortam descrescator
- calculam suma in timp ce cream vectorii
- apoi parcurgem ambii vecori in acelasi timp si cat timp nu am terminat
mutarile si punem in suma maximul de pe mozutia curenta si scadem minimul

ex:
        2
        5 2
        3 6 10 9 5      => maxV : 3 8 10 9 5
        1 8 4 7 2       => minV : 1 6  4 7 2
                           sum = 3 + 8 + 10 + 9 + 5 = 35

==> sortam      maxV : 3 5 8 9 10
                minV : 7 6 4 3 1
==> parcurem ambii vecori cat timp mai avem mutari si luam maximul
        mutare 2 : sum = sum - 3 + 7 = 39
        mutare 1 : sum = sum - 5 + 6 = 40
        mutare 0 => aici ne oprim   =>  suma finala este 40

- luam in considerare ca putem sa mai avem mutari de facut dar sa nu mai 
fie rentabil sa le facem => ne oprim mai devreme

- ideea de la care am plecat:
- avand in vedere ca in maxV avem maximele dintre perechi si dupa in sortam
crescator
- si in minV avem minimurile dintre perechi si este sortat descrescator
- garantam ca in inceputul lui maxV avem cea mai mica valoare care ar putea
fi schimbata, iar in minV va fi cea mai mare valoare

- [Complexitate] O( nlog(n) )


                ---- Problema Sushi ----

- aici am folosit algoritmul de la Rucsac, pe care l-am luat din laborator

        * Prima parte

- aici am calculat ratingurile si am folosit ghiozdanul clasic
- [Complexitate] O( m*n*x )

        * A doua parte

- am creat 2 vectori price si rating, ei sunt de 2 ori mai mari decat numarul
de feluri de sushi
- in timp ce calculam ratingurile umplem acesti vectori astfel:
        1 2 3 1 2 3    -  price
        5 6 7 5 6 7    -  rating
- apoi aplicam Rucsacul doar ca folosind acesti vectori mariti
- [Complexitate] O( m*n*x )

        * A treia parte

- calculam ratingurile
- apoi apelam o varianta mai schimbata de Rucsac
- diferentele sunt:
        - in loc de o matrice am facut un vector tridimensional
        - trebuie parcursi de doua ori vectorii de price si rating, pentru ca
se merge pe acelasi principiu ca si la prima parte (reusim sa parcurgem vectorul
dublat fara sa dublam in sine vectorul, folosind o regula de parcurgere : 
cat timp indicele curent este mai mic decat lungimea maxima a vectorului de price
va ramane neschimbat, cand depaseste va fi indice - nr prieteni)
        - dupa cele doua parcurgeri normale se mai adauga o parcurgere pana la
n (numarul de prieteni)
        - atunci cand terminam o varianta maxima de rating o verificam cu cea
anterior calculata, daca dam de una mai mica oprim cautarea
- ideea din spate este de a incerca toate variantele posibile de luare a
felurilor de mancare pana gasim un maxima
- [Complexitate] O( m*n*n*x )
        

                ---- Problema Semnale ----

        * Prima parte

- prin incercari am vazul ca poate fi folist triunghiul lui pascal pentru a
genera solutiile
- fac Pascal pe o matrice
- rezultatul final va fi pe Mat[x+1][y] unde x este nr de '0' si y nr de '1'
- rezolvarea a fost gasita facand mai multe incercari pe exemple

- ! codul pentru Pascal a fost luat de aici 
https://www.pbinfo.ro/articole/10864/triunghiul-lui-pascal

- [Complexitate] O( (x+y)^2 )

        * A doua parte
- solutia a fost gasita tot prin incercari
- folosesc tot o matrice, dar opresc generarea ei dupa ce am gasit linia cu
raspunsul bun

ex:     Astea sunt solutiile in functie de cate de 1 si 0 avem
            0  1  2  3  4  5       -- nr de 1
          |------------------
        0 | 1  1  1  0  0  0
-nr     1 | 1  2  3  2  1  0
  de    2 | 1  3  6  7  6  3
    0   3 | 1  4 10 16 19 16
        4 | 1  5 15 30 45 51 
        5 | 1  6 ...........

        --- descoperim ca regula este
        A[i][j] = A[i-1][j] + A[i-1][j-1] + A[i-1][j-2]
        - luam in considerare ca pe prima linie avem la j = 0..1 doar 1
        - pe prima coloana este mereu 1
        - pe a doua coloana avem de fiecare data indicele coloanei + 1
- [Complexitate] O( (x+y)^2 )


                ---- Problema Badgpt ----

- Aici doar am folosit fibonacci facuta pe vector pentru a calcula cate variate
sunt tinand cont de regulile uu => W si nn => m si apoi inmultim resultatele ca
sa aflam cate variate totale sunt

ex:
        a2n3c4
        a2 => 1 varianta
        n3 => fib(3) = 3 variante
        c4 => 1 varianta
        ------------------total = 1*3*1 = 3 variante posibile

- legat de fibonacci, mi-am dat seama ca asta este solutia prin incercari

ex: 
        n1 => 1 varianta
        n2 => 2 variante
        n3 => 3 variante
        n4 => 5 variante
        ------------------etc.

- ! folosim Fibonacci pornind de la 1, nu de la 0
- [Complexitate] O(nr)
