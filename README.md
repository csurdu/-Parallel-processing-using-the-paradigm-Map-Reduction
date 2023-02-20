# -Parallel-processing-using-the-paradigm-Map-Reduction
Cerint,˘a
S˘a se implementeze un program paralel ˆın Pthreads pentru g˘asirea numerelor mai mari decˆat 0 care sunt
puteri perfecte dintr-un set de fis, iere s, i num˘ararea valorilor unice pentru fiecare exponent.
Pentru paralelizarea proces˘arii documentelor de intrare, se va folosi modelul Map-Reduce. Fis, ierele de
intrare vor fi ˆımp˘art, ite (ˆın mod dinamic) cˆat mai echilibrat la nis, te thread-uri care le vor parsa s, i vor verifica
ce numere mai mari decˆat 0 sunt puteri perfecte (operat, iunea de Map), rezultˆand astfel liste part, iale pentru
fiecare exponent (ex., liste pentru p˘atratele perfecte, liste pentru cuburile perfecte, etc.). Pasul urm˘ator ˆıl
reprezint˘a combinarea listelor part, iale (operat, iunea de Reduce) ˆın urma c˘areia se vor obt, ine liste agregate
pentru fiecare exponent ˆın parte. Pentru fiecare astfel de list˘a, se vor num˘ara ˆın paralel valorile unice,
rezultatele fiind apoi scrise ˆın nis, te fis, iere de ies, ire.
Paradigma Map-Reduce
Pentru rezolvarea temei, se va folosi un model Map-Reduce similar cu cel folosit la Google pentru procesarea
unor seturi mari de documente ˆın sisteme distribuite. Acest articol prezint˘a modelul Map-Reduce folosit
de Google s, i o parte dintre aplicat, iile lui (mai importante pentru ˆınt,elegerea modelului sunt primele 4 pagini).
Map-Reduce este un model (s, i o implementare asociat˘a) de programare paralel˘a pentru procesarea unor
seturi imense de date, folosind sute sau mii de procesoare. ˆIn majoritatea cazurilor, Map-Reduce este folosit
ˆıntr-un context distribuit, fiind, de fapt, un model de programare care poate fi adaptat pentru ambele situat, ii.
Cea mai cunoscut˘a implementare este Apache Hadoop, dezvoltat init, ial de c˘atre Doug Cutting s, i Mike Cafarella. Modelul permite paralelizarea s, i distribuirea automat˘a a task-urilor. Paradigma Map-Reduce se
bazeaz˘a pe existent,a a dou˘a funct, ii care ˆıi dau s, i numele: Map s, i Reduce. Funct, ia Map primes, te ca input o
funct, ie f s, i o list˘a de elemente, s, i returneaz˘a o nou˘a list˘a de elemente rezultat˘a ˆın urma aplic˘arii funct, iei f
asupra fiec˘arui element din lista init, ial˘a. Funct, ia Reduce combin˘a rezultatele obt, inute anterior.
Mecanismul Map-Reduce funct, ioneaz˘a ˆın modul urm˘ator:
• utilizatorul cere procesarea unui set de documente
• aceast˘a cerere este adresat˘a unui proces (sau fir de execut, ie) coordonator
• coordonatorul asigneaz˘a documentele unor procese (sau fire de execut, ie) de tip Mapper1
• un Mapper va analiza fis, ierele de care este responsabil s, i va genera nis, te rezultate part, iale, avˆand ˆın
general forma unor perechi de tip {cheie, valoare}
• dup˘a ce operat, iile Map au fost executate, alte procese (sau fire de execut, ie) de tip Reducer combin˘a
rezultatele part, iale s, i genereaz˘a solut, ia final˘a.
Detalii tehnice
Dˆandu-se un set de N documente, s˘a se numere valorile unice mai mari decˆat 0 de tip putere perfect˘a pentru
fiecare exponent E folosind Map-Reduce. ˆIn implementarea temei, vor exista thread-uri care pot fi de dou˘a
tipuri, Mapper sau Reducer, toate fiind pornite ˆımpreun˘a la ˆınceputul rul˘arii.
Operat, iile de tip Map
Pornind de la lista de documente de procesat ce va fi disponibil˘a ˆın fis, ierul de intrare, fiecare Mapper va
ajunge s˘a proceseze nis, te documente. Alocarea de documente thread-urilor Mapper poate fi realizat˘a static
ˆınainte de pornirea acestora (des, i nu este recomandat acest lucru), sau poate fi realizat˘a ˆın mod dinamic pe
1Acest lucru nu trebuie neap˘arat realizat la ˆınceput, el se poate face s, i ˆın mod dinamic pe m˘asur˘a ce fis, ierele sunt procesate.
ALGORITMI PARALELI S, I DISTRIBUIT, I Pagina 2 din 13
m˘asur˘a ce documentele sunt procesate (ˆıntr-o astfel de situat, ie, un Mapper care se mis,c˘a mai repede decˆat
ceilalt, i poate s˘a “fure” munc˘a de la alt Mapper, lucru care va duce la o procesare mai eficient˘a). Fiecare
Mapper va executa urm˘atoarele act, iuni, pentru fiecare fis, ier de care este reponsabil:
• deschide fis, ierul s, i ˆıl parcurge linie cu linie (pe fiecare linie fiind cˆate o valoare numeric˘a de tip ˆıntreg)
• pentru fiecare ˆıntreg citit, verific˘a dac˘a este o putere perfect˘a a lui 2, 3, 4, etc. mai mare decˆat 0
(exponentul maxim pˆan˘a la care verific˘a este dat de num˘arul de thread-uri Reducer, as,a cum se va
explica mai tˆarziu)
• fiecare valoare mai mare decˆat 0 care este o putere perfect˘a cu un exponent E este salvat˘a ˆıntr-o list˘a
part, ial˘a (dac˘a o valoare este putere perfect˘a pentru mai mult, i exponent, i E - de exemplu, 81 poate fi
scris ca 34
sau 92
- aceasta va fi plasat˘a ˆın mai multe liste part, iale)
• cˆand s-a terminat de procesat un fis, ier, Mapper-ul ˆıl ˆınchide.
Atent, ie! Pentru verificarea dac˘a un num˘ar este putere perfect˘a, NU folosit, i funct, ia pow (sau orice funct, ie
similar˘a de ridicat la putere) cu exponent subunitar. Din cauza operat, iilor ˆın virgul˘a mobil˘a, este posibil
s˘a ratat, i anumite valori sau s˘a luat, i ˆın considerare valori incorecte.
Operat, iile de tip Reduce
Un fir de execut, ie de tip Reducer va fi responsabil pentru agregarea s, i num˘ararea valorilor puteri perfecte
pentru un singur exponent (de exemplu, un Reducer se va ocupa de p˘atratele perfecte, altul de cuburile
perfecte, etc.). Astfel, avˆand rezultatele din cadrul operat, iunii de Map, un Reducer va realiza urm˘atoarele
act, iuni:
• combin˘a listele part, iale pentru exponentul E de care este responsabil ˆıntr-o list˘a agregat˘a (etapa de
combinare)
• num˘ar˘a valorile unice din lista agregat˘a s, i scrie rezultatul ˆıntr-un fis, ier (etapa de procesare).
Atent, ie! ˆInainte s˘a ˆıncepet, i operat, iile de tip Reduce, trebuie s˘a v˘a asigurat, i c˘a toate operat, iile de tip Map
s-au finalizat.
Execut, ie
Programul se va rula ˆın felul urm˘ator:
./tema1 <numar_mapperi> <numar_reduceri> <fisier_intrare>
Atent, ie! Trebuie s˘a pornit, i toate thread-urile (atˆat cele Mapper, cˆat s, i cele Reducer) ˆıntr-o singur˘a iterat, ie
a thread-ului principal. Nu se accept˘a mai multe perechi de pthread create/pthread join ˆın cod, acest lucru
ducˆand la un punctaj de 0 pe ˆıntreaga tem˘a.
Fis, ierul de intrare are urm˘atorul format:
numar_fisiere_de_procesat
fisier1
...
fisierN
ALGORITMI PARALELI S, I DISTRIBUIT, I Pagina 3 din 13
As,adar, prima linie cont, ine num˘arul de documente text de procesat, iar urm˘atoarele linii cont, in numele
documentelor, cˆate unul pe linie. Toate fis, ierele de intrare vor cont, ine doar caractere ASCII s, i se pot considera valide.
Un fis, ier care trebuie procesat are urm˘atorul format:
numar_valori_de_verificat
valoare1
...
valoareN
Aceste fis, iere trebuie ˆımp˘art, ite cˆat mai echilibrat thread-urilor Mapper, f˘ar˘a s˘a existe fis, iere neprocesate de
niciun Mapper sau fis, iere procesate de mai multe thread-uri Mapper.
Atent, ie! O ˆımp˘art, ire echilibrat˘a a fis, ierelor de procesat nu ˆınseamn˘a neap˘arat c˘a fiecare thread Mapper va avea cˆate un num˘ar aproximativ egal de fis, iere, deoarece acestea pot avea dimensiuni foarte diferite.
De exemplu, dac˘a exist˘a trei thread-uri Mapper care au de procesat 6 fis, iere de dimensiuni 5 MB, 5 MB, 1
MB, 1 MB, 1 MB, 1 MB, este mai eficient ca primele dou˘a thread-uri Mapper s˘a proceseze cˆate un fis, ier de
5 MB s, i al treilea Mapper s˘a proceseze cele patru fis, iere de cˆate 1 MB, decˆat s˘a se aloce cˆate dou˘a fis, iere
fiec˘arui Mapper. Acest lucru se poate face static (ˆınaintea de pornirea thread-urilor Mapper) sau dinamic
(fiecare Mapper care termin˘a de procesat un fis, ier vede dac˘a mai sunt fis, iere disponibile). O ˆımp˘art, ire ineficient˘a poate afecta scalabilitatea temei s, i implicit punctajul obt, inut.
ˆIn funct, ie de num˘arul de thread-uri Reducer, se va calcula s, i exponentul maxim E pˆan˘a la care se verific˘a
puterile perfecte mai mari decˆat 0. De exemplu, dac˘a se ruleaz˘a cu trei thread-uri Reducer, E va fi 4 (se
verific˘a p˘atratele perfecte, cuburile perfecte, s, i numerele care sunt puteri perfecte cu exponentul 4). Programul va avea cˆate un fis, ier de ies, ire pentru fiecare Reducer, care se va numi outE.txt, unde E este exponentul
de care este responsabil fiecare Reducer. Un fis, ier de ies, ire va cont, ine o singur˘a valoare de tip ˆıntreg, adic˘a
num˘arul de valori unice mai mari decˆat 0 care sunt puteri perfecte cu exponentul E.
Exemplu
Se d˘a urm˘atorul fis, ier de intrare:
$ cat test.txt
4
in1.txt
in2.txt
in3.txt
in4.txt
Cele patru documente de procesat arat˘a ˆın felul urm˘ator:
$ cat in1.txt
6
243
9
27
243
81
243
$ cat in2.txt
6
81
ALGORITMI PARALELI S, I DISTRIBUIT, I Pagina 4 din 13
9
27
243
27
27
$ cat in3.txt
6
9
27
9
81
9
53
$ cat in4.txt
5
243
243
243
1
0
Tema se ruleaz˘a cu urm˘atoarea comand˘a:
./tema1 3 5 test.txt
As,adar, exist˘a trei thread-uri Mapper (la care se ˆımpart cele patru fis, iere) s, i cinci thread-uri Reducer (deci
se vor verifica puterile perfecte pentru exponent, ii 2, 3, 4, 5 s, i 6).
Cele patru fis, iere de intrare se pot ˆımp˘art, i la cele trei thread-uri Mapper astfel:
• M0 → in1.txt
• M1 → in2.txt
• M2 → in3.txt, in4.txt
Conform operat, iei de Map, fiecare Mapper verific˘a toate numerele din fis, ierele asignate lui s, i salveaz˘a liste
part, iale cu puterile perfecte mai mari decˆat 0. Pentru exemplul de mai sus, operat, iile de Map duc la
urm˘atoarele rezultate (unde prima list˘a de la fiecare Mapper reprezint˘a p˘atratele perfecte, a doua list˘a
cuburile perfecte, etc.):
• M0 → {9, 81}, {27}, {81}, {243, 243, 243}, {}
• M1 → {81, 9}, {27, 27, 27}, {81}, {243}, {}
• M2 → {9, 9, 81, 9, 1}, {27, 1}, {81, 1}, {243, 243, 243, 1}, {1}
Fiecare Mapper are cˆate cinci liste part, iale, una pentru fiecare exponent. Se poate observa c˘a numerele care
sunt puteri perfecte pentru mai mult, i exponent, i E apar ˆın mai multe liste part, iale de la acelas, i Mapper. De
asemenea, se poate observa s, i faptul c˘a 1 este considerat putere perfect˘a pentru orice exponent, dar 0 nu se
ia ˆın considerare (pentru c˘a se cer valorile perfecte mai mari decˆat 0).
Odat˘a ce toate operat, iile de Map s-au terminat, thread-urile Reducer se apuc˘a de combinare s, i procesare.
Conform rul˘arii, ˆın acest exemplu sunt cinci astfel de thread-uri, fiecare din ele responsabil de un exponent.
Astfel, fiecare Reducer ia toate listele part, iale pentru exponentul s˘au (care vor fi ˆın num˘ar de trei, cˆate una
per Mapper) s, i le agreg˘a, ajungˆand la urm˘atorul set de liste agregate:
ALGORITMI PARALELI S, I DISTRIBUIT, I Pagina 5 din 13
• R0 → {9, 81, 81, 9, 9, 9, 81, 9, 1}
• R1 → {27, 27, 27, 27, 27, 1}
• R2 → {81, 81, 81, 1}
• R3 → {243, 243, 243, 243, 243, 243, 243, 1}
• R4 → {1}
ˆIn final, fiecare Reducer num˘ar˘a valorile unice din lista sa final˘a, ajungˆand la urm˘atorul rezultat:
$ cat out2.txt
3
$ cat out3.txt
2
$ cat out4.txt
2
$ cat out5.txt
2
$ cat out6.txt
1
O reprezentare grafic˘a a rul˘arii de Map-Reduce pe exemplul precedent se poate observa ˆın figura de mai jos.

![image](https://user-images.githubusercontent.com/73692534/220130863-08e4dd70-2aee-4657-9d4d-1ea5f15dcde3.png)
