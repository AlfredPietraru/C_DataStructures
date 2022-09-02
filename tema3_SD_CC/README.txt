README

Task 1 --e1
Se aplica algoritmul floyd-Warshall iar in matricea cu valori de tip float 
"destinatie" vom stoca distanta dintre oricare 2 puncte, deci pentru 
elementul destinatie[i][j], valoarea acestui reprezinta distanta minima de la
nodul i>>j; matricea road contine posibilele rute pe care se poate merge 
in momentul in care se   pe un anumit nod, de exemplu, pentru prima coloana
numerele care se vor afla vor reprezenta nodurile care duc catre nodul 0, 
datorita initializarii matricei cu -1, fiecare coloana are completat acelasi numar
de mai multe ori  functia "printPath" afiseaza drumul de la un nod sursa la cel destinatie
primul argument de tip int reprezentand destinatia, pentru a obtine intreg traseul functia
se apeleaza de 2 ori, odata de la origine la nodul respectiv, apoi in sens invers, drumul pe care
trebuie sa il parcurga este aflat cu ajutorul matricei road, care modificand elementul "u"
modifica si linia pe care se va face cautarea urmatorului nod care va alcatui sirul din afisarea
finala 

Task 2 --e2
am folosit algoritmul kosaraju pentru task 2, iar functiile pe baza carora am construit stiva
sunt luate din "cursul 4bis" de structuri de date de pe moodle.
    functia "change_adj_g" transforma matricea grafului intr-o matrice de 0 si 1. Daca un element
din g.adj_mat==0 || g.adj_mat==MAX_PRET (10000), atunci acesta devine 0,  iar pentru orice alta 
valoare devine 1. Practic, aceasta transformare imi spune doar daca exista legatura directa 
intre doua noduri, dar nu si valoarea drumului de unul la celalalt.
    functia DFS1 face parcurgerea in adanccime a grafului, adaugand pe stiva valorile in ordinea 
in care sunt strabatute, pentru a fi reutilizate in functia kosaraju.
    functia DFS2 cauta elementele prin care nu s-a trecut complet cu DFS1
    functia kosaraju este alcatuita din algoritmul respectiv, dar este modificata astfel incat sa
retina nodurile prin care trece, iar in momentul in care se termina un subgraf tare conex sa adauge
-1, astfel grupuri de elemente tari conexe sunt stocate in vector diferentiate intre ele,
    functia afisare task 2 preia continut vectorului si afiseaza nodurile fiecarui subgraf tare 
conex in ordine crescatoare

la task3 --e3
am aplicat algoritmul lui Prim, pentru a gasi arborele de cost minim care trece prin fiecare
subgraf tare conex al grafului, iar la acel rezultat, adaugam valoarea distantei de la ultimul
nod care alcatuia subgraful la orginea de unde a plecat, astfel obtinand distanta totala.
    Functia "start_road" imi spune care este depozitul cel mai apropiat de oricare dintre punctele
care alcatuiesc traseul pe care va merge cu masina curierul.
    Funcctia "minKey" are ca output indicele indicele elementului minim dintr-un vector.
    Functia "prepare_matrix", copiaza intr-un alt tablou matricea adiacenta grafului, 
dar elimina nodurile care nu se afla in interiorul grafului, adaugand 0 pe liniile respective.
    Functia "primMST" realizeaza algoritmul lui prim, fara a tine minte nodurile prin 
care trece ci doar modificand, de fiecare data valoarea drumului total, care este transmis 
ca output al functiei.



