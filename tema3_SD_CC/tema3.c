#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functii_matrici_vectori.h"

#define MAX_PRET 10000

typedef struct nod
{
    int val;
    struct nod *next;
} node;

typedef struct
{
    int n, m;
    float **adj_mat;
} graf;

typedef struct
{
    int *elements;
    int top;
    int maxSize;
} TStack;

typedef struct
{
    int **mask;
    int *elements;
    int front;
    int count;
    int maxSize;
} TQueue;

void initgraph(graf *g, float **arce_noduri, int n, int m)
{
    int i, j;
    g->n = n;
    g->m = m;
    g->adj_mat = (float **)malloc((n + 1) * sizeof(float *));
    for (i = 0; i < n; i++)
    {
        g->adj_mat[i] = (float *)calloc((n + 1), sizeof(int));
    }
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            g->adj_mat[i][j] = MAX_PRET;
        }
        g->adj_mat[i][i] = 0;
    }
    for (i = 0; i < m; i++)
    {
        g->adj_mat[(int)arce_noduri[i][0]][(int)arce_noduri[i][1]] = arce_noduri[i][2];
    }
}
void roy_floyd(graf g, float **destinatie, int **road)
{
    int i, j, k;
    for (i = 0; i < g.n; i++)
    {
        for (j = 0; j < g.n; j++)
        {
            destinatie[i][j] = g.adj_mat[i][j];
            if (g.adj_mat[i][j] == MAX_PRET)
            {
                road[i][j] = -1;
            }
            else
            {
                road[i][j] = j;
            }
        }
    }
    for (k = 0; k < g.n; k++)
    {
        for (i = 0; i < g.n; i++)
        {

            for (j = 0; j < g.n; j++)
            {

                if (destinatie[i][k] + destinatie[k][j] < destinatie[i][j])
                {
                    destinatie[i][j] = destinatie[i][k] + destinatie[k][j];
                    road[i][j] = road[i][k];
                }
            }
        }
    }
}
void printPath(int **road, int v, int u)
{
    while (u != v)
    {
        u = road[u][v];
        printf(" ");
        printf("%d", u);
    }
}
// task 1

// task 2
// definesc functiile pentru stiva
void initStack(TStack *stack, int n)
{
    int *newst;
    newst = (int *)malloc(n * sizeof(int));
    stack->elements = newst;
    stack->maxSize = n;
    stack->top = -1;
}
void elimS(TStack *stack)
{
    free(stack->elements);
    stack->elements = NULL;
    stack->maxSize = 0;
    stack->top = -1;
}
void push(TStack *stack, int id_node)
{
    stack->top = stack->top + 1;
    stack->elements[stack->top] = id_node;
}
int pop(TStack *stack)
{
    stack->top = stack->top - 1;
    return stack->elements[stack->top + 1];
}
void change_adj_g(graf *g, int *id_depozit, int d)
{
    int i, j;
    for (i = 0; i < g->n; i++)
    {
        for (j = 0; j < g->n; j++)
        {
            if (g->adj_mat[i][j] == 0 || g->adj_mat[i][j] == MAX_PRET)
            {
                g->adj_mat[i][j] = 0;
            }
            else
            {
                g->adj_mat[i][j] = 1;
            }
        }
    }
    for (i = 0; i < d; i++)
    {
        for (j = 0; j < g->n; j++)
        {
            g->adj_mat[id_depozit[i]][j] = 0;
            g->adj_mat[j][id_depozit[i]] = 0;
        }
    }
}
int DFS1(graf g, int v, int *visited, TStack *stack)
{
    int i = 0;
    visited[v] = 1;
    for (i = 0; i < g.n; i++)
        if (visited[i] == 0 && g.adj_mat[v][i] == 1)
        {
            DFS1(g, i, visited, stack);
        }
    push(stack, v);
    return 0;
}
int DFS2(graf g, int v, int *visited, int **tr_adj, int *rezultat, int *contor)
{
    int i;
    visited[v] = 1;
    rezultat[*contor] = v;
    *contor = *contor + 1;
    for (i = 0; i < g.n; i++)
    {
        if (visited[i] == 0 && tr_adj[v][i] == 1)
        {
            DFS2(g, i, visited, tr_adj, rezultat, contor);
        }
    }
    return 0;
}
int kosaraju(graf g, TStack *stack, int *visited, int **tr_adj, int *id_depozit, int d, int *contor, int *rezultat)
{
    int i;
    while (stack->top != -1)
        pop(stack);

    for (i = 0; i < g.n; i++)
    {
        visited[i] = 0;
    }

    for (i = 0; i < g.n; i++)
    {
        if (visited[i] == 0)
        {
            DFS1(g, i, visited, stack);
        }
    }
    for (i = 0; i < g.n; i++)
    {
        visited[i] = 0;
    }
    int t = 0;
    while (stack->top != -1)
    {
        int ok = 0;
        int v = stack->elements[stack->top];
        pop(stack);
        for (i = 0; i < d; i++)
        {
            if (v != id_depozit[i])
            {
                ok = ok + 1;
            }
        }

        if (visited[v] == 0 && ok == d)
        {
            t++;
            *contor = *contor + 1;
            DFS2(g, v, visited, tr_adj, rezultat, contor);
        }
    }
    return t;
}

void afisare_task2(int *rezultat, int dimensiune, int t)
{
    while (t != 0)
    {
        int i, j, icautat, min = dimensiune;
        int aux[dimensiune / 2];
        for (i = 0; i < dimensiune / 2; i++)
        {
            aux[i] = 0;
        } // vector se adauga grafurile conexe

        for (i = 0; i < dimensiune; i++)
        {
            if (min > rezultat[i] && rezultat[i] != -1)
            {
                min = rezultat[i];
                icautat = i;
            }
        }
        int k = 0;
        while (rezultat[icautat] != -1 && icautat >= 0)
        {
            icautat = icautat - 1;
            if (icautat == -1)
            {
                break;
            }
        }
        icautat = icautat + 1;
        while (rezultat[icautat] != -1)
        {
            aux[k] = rezultat[icautat];
            k = k + 1;
            rezultat[icautat] = -1;
            icautat = icautat + 1;
        }

        for (i = 0; i < dimensiune / 2 - 1; i++)
        {
            for (j = i + 1; j < dimensiune / 2; j++)
            {
                if (aux[i] > aux[j])
                {
                    k = aux[i];
                    aux[i] = aux[j];
                    aux[j] = k;
                }
            }
        }
        int ok = 0;
        for (i = 0; i < dimensiune / 2; i++)
        {
            if (aux[i] != 0)
            {
                if (ok == 1)
                {
                    printf(" ");
                }
                printf("%d", aux[i]);
                ok = 1;
            }
        }
        t = t - 1;
        if (t != 0)
        {
            printf("\n");
        }
    }
}

// task 3
int start_road(float **destinatie, int *id_depozit, int d, int *checkpoint, graf g)
{
    int i = 0, j;
    int depozit_start, min = MAX_PRET;
    for (j = 0; j < d; j++)
    {
        for (i = 0; i < checkpoint[0]; i++)
        {
            if (min > destinatie[id_depozit[j]][checkpoint[i + 1]])
            {
                depozit_start = id_depozit[j];
                min = destinatie[id_depozit[j]][checkpoint[i + 1]];
            }
        }
    }
    return depozit_start;
}

int minKey(int key[], int mstSet[], int n)
{
    // Initialize min value
    int min = MAX_PRET, min_index;
    int i = 0;
    for (i = 0; i < n; i++)
    {
        if (mstSet[i] == 0 && key[i] < min)
        {
            min = key[i], min_index = i;
        }
    }
    return min_index;
}

float primMST(int n, int q, float **aux_adjmat, int *last_node,int *checkpoint)
{
    int i, j;
    float suma_totala = 0;
    int selected[n];
    for (i = 0; i < n; i++)
    {
        selected[i] = 0;
    }
    int no_edge = 0;
    selected[q] = 1;
    while (no_edge < checkpoint[0])
    {
        int min = MAX_PRET;
        int x = 0;
        int y = 0;

        for (i = 0; i < n; i++)
        {
            if (selected[i])
            {
                for (j = 0; j < n; j++)
                {
                    if (!selected[j] && aux_adjmat[i][j])
                    {
                        if (min > aux_adjmat[i][j])
                        {
                            min = aux_adjmat[i][j];
                            x = i;
                            y = j;
                        }
                    }
                }
            }
        }
        suma_totala = suma_totala + aux_adjmat[x][y];
        selected[y] = 1;
        no_edge++;
        if (y != 0)
        {
            *last_node = y;
        }
    }
    return suma_totala;
}

void prepare_matrix(float **aux_adjmat, graf g, int *id_depozit, int d, int q, int *checkpoint)
{
    int i, j, k = 1;
    for (i = 0; i < g.n; i++)
    {
        if (i == checkpoint[k])
        {
            for (j = 0; j < g.n; j++)
            {
                aux_adjmat[i][j] = g.adj_mat[i][j];
            }
            k = k + 1;
        }
    }
    k = 1;
    for (i = 0; i < g.n; i++)
    {
        if (i == checkpoint[k])
        {
            aux_adjmat[q][i] = g.adj_mat[q][i];
            k = k + 1;
        }
        if (i == id_depozit[0] && q != 0)
        {
            for (j = 0; j < g.n; j++)
            {
                aux_adjmat[j][id_depozit[0]] = 0;
            }
        }
    }
}

int main()
{
    int n, m, d;
    scanf("%d%d%d", &n, &m, &d);

    float **arce_noduri;
    arce_noduri = malloc(m * sizeof(float *));
    int i = 0;
    for (i = 0; i < m; i++)
    {
        arce_noduri[i] = (float *)malloc(3 * sizeof(float));
    } // se aloca memorie pentru matricea de adiacenta

    int j = 0;
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < 3; j++)
        {
            scanf("%f", &arce_noduri[i][j]);
        }
    } // se introduce matricea de adiacenta

    int id_depozit[d];
    for (i = 0; i < d; i++)
    {
        scanf("%d", &id_depozit[i]);
    } // se introduce id-ul depozitelor

    graf g;
    initgraph(&g, arce_noduri, n, m); // se initializeaza graful

    int nr_cerinte;
    scanf("%d", &nr_cerinte); // se introduce numarul de cerinte

    char buffer[3];
    for (i = 0; i < nr_cerinte; i++)
    {
        scanf("%s", buffer);
        if (strcmp(buffer, "e1") == 0)
        {
            // se initializeaza graful
            int s;
            scanf("%d", &s); // depozitul din care se incarca marfa
            int k;
            scanf("%d", &k); // nr de magazine aprovizionate
            int idarray[d];  // id magazine aprovizionate
            int j;
            for (j = 0; j < k; j++)
            {
                scanf("%d", &idarray[j]);
            }
            // introducerea datelor specifice task-ului

            int *p;
            p = (int *)malloc(n * sizeof(int));
            float *distances;
            distances = (float *)malloc(n * sizeof(float));
            init_d_vector(p, n);
            int *road_vector;
            road_vector = (int *)malloc(2 * n * sizeof(int));

            float **destinatie;
            destinatie = malloc(n * sizeof(float *));
            allocate_f_matrix(destinatie, n, n); //elementul destinatie[i][j]== distanta de la i-->j

            int **road;
            road = malloc(n * sizeof(int *));
            allocate_d_matrix(road, n, n);
            // se aloca memorie pt vectorii si matricile cu care voi lucra

            roy_floyd(g, destinatie, road); // se aplica algoritmul pentru graf
            //posibilitatile pe care se poate merge in momentul in care s-a ajuns la un anumit nod
            // afisare finala:
            float cost_total = 0;
            for (j = 0; j < k; j++)
            {
                printf("%d\n", idarray[j]);//odata va afisa drumul total dus, apoi cel intors
                printf("%0.1f %0.1f\n", destinatie[s][idarray[j]], destinatie[idarray[j]][s]);
                printf("%d", s);
                printPath(road, idarray[j], s); //afiseaza drumul la dus
                printPath(road, s, idarray[j]); //afiseaza drumul la intors ,primul parametru: destinatia
                printf("\n");
                cost_total = cost_total + destinatie[s][idarray[j]] + destinatie[idarray[j]][s];
            }
            printf("%0.1f", cost_total);
            if (nr_cerinte > 1 && i != nr_cerinte - 1)
            {
                printf("\n");
            }//afisarea corezpunzatoare primului task;

            // eliberarea memoriei
            free_int_matrix(road, g.n);
            free_matrix(destinatie, g.n);
            free(road_vector);
            free(distances);
            free(p);
        }

        if (strcmp(buffer, "e2") == 0)
        {
            TStack stack;
            initStack(&stack, n); 

            int *vizitat;
            vizitat = (int *)malloc(n * sizeof(int));
            for (i = 0; i < g.n; i++)
            {
                vizitat[i] = 0;
            }//vizitat va avea doar valori de 0 si 1 ,daca nodul a fost vizitat sau nu

            change_adj_g(&g, id_depozit, d); // transform g.adj_mat in matrice de 0 si 1

            int **tr_adjmat;
            tr_adjmat = (int **)malloc(g.n * sizeof(int *));
            allocate_d_matrix(tr_adjmat, g.n, g.n);
            tranpose_matrix(g.adj_mat, tr_adjmat, g.n, g.n);//creez matricea transpusa

            int *rezultat;
            rezultat = (int *)malloc(2 * n * sizeof(int));
            init_d_vector(rezultat, 2 * n); //aici vor fi stocate nodurile in ordinea in care apar
            int contor = -1;
            int q;
            q = kosaraju(g, &stack, vizitat, tr_adjmat, id_depozit, d, &contor, rezultat);
            printf("%d\n", q); //nr de subgrafuri orientate tare conexe
            afisare_task2(rezultat, 2 * n, q); 
            //sunt extrase informatiile din "rezultat" si afisate corespunzator
            // eliberare memorie
            free_int_matrix(tr_adjmat, g.n);
            free(rezultat);
            elimS(&stack);
            free(vizitat);
        }

        if (strcmp(buffer, "e3") == 0)
        {
            int r;
            scanf("%d", &r); //numarul de drumuri 
            int matrice_drum[r][n]; 
            for (i = 0; i < r; i++)
            {
                for (j = 0; j < n; j++)
                {
                    matrice_drum[i][j] = -1;
                }
            }
            for (i = 0; i < r; i++)
            {
                int k;
                scanf("%d", &k);
                matrice_drum[i][0] = k;
                for (j = 1; j <= k; j++)
                {
                    scanf("%d", &matrice_drum[i][j]);
                }
            } // adaug toate datele de intrare
            //matrice drum stocheaza sirurile de forma k x0 x1... xk
            float **destinatie;
            destinatie = malloc(n * sizeof(float *));
            allocate_f_matrix(destinatie, n, n);
            int **road;
            road = malloc(n * sizeof(int *));
            allocate_d_matrix(road, n, n);

            roy_floyd(g, destinatie, road); //aceeasi functie ca la task-ul 1
            int l = 0;
            while (l < r)
            {
                int *checkpoint; //contine nodurile prin care trebuie sa trec
                checkpoint = (int *)malloc(n * sizeof(int));
                for (i = 0; i <= matrice_drum[l][0]; i++)
                {
                    checkpoint[i] = matrice_drum[l][i];
                }
                for(i=matrice_drum[l][0]+1;i<n;i++)
                {
                    checkpoint[i]=0;
                }
                int q = start_road(destinatie, id_depozit, d, checkpoint, g);
                
                float **aux_adjmat;
                aux_adjmat = malloc(n * sizeof(float *));
                allocate_f_matrix(aux_adjmat, n, n);
                init_f_matrix(aux_adjmat, n, n);

                prepare_matrix(aux_adjmat, g, id_depozit, d, q,checkpoint);
        // transfer matricea g intr-o matrice auxiliara-si elimin nodurile care nu sunt in checkpoint
                float suma = 0;
                int last_node = 0;
                suma = primMST(n, q, aux_adjmat, &last_node,checkpoint);
                suma = suma + destinatie[last_node][q];
                printf("%0.1f", suma);
                if(l<r-1)
                {
                    printf("\n");
                }

                free_matrix(aux_adjmat, n);
                free(checkpoint);
                l = l + 1;
            }
            free_int_matrix(road, n);
            free_matrix(destinatie, n);
        }
    }
    free_matrix(g.adj_mat, n);
    free_matrix(arce_noduri, m);
}