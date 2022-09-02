#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

typedef struct cell
{
    int elem;
    struct cell *next;
} Stack;

void error(char *msg);
Stack *initstack(Stack *s)
{
    s = NULL;
    return s;
}
int emptystack(Stack *s)
{
    return (s == NULL);
}
Stack *push(int e, Stack *s)
{
    Stack *nou;
    nou = (Stack *)malloc(sizeof(Stack));
    if (nou == NULL)
    {
        error("Nu mai exista spatiu disponibil");
        return NULL;
    }
    nou->elem = e;
    if (s == NULL)
    {
        nou->next = NULL;
        s = nou;
    }
    else
    {
        nou->next = s;
        s = nou;
    }
    return s;
}
Stack *pop(Stack *s)
{
    int e;
    Stack *aux;
    aux = s;
    if (s == NULL)
    {
        error("Stiva vida");
        return 0;
    }
    e = aux->elem;
printf("Se scoate elementul din varful stivei cu valoarea %d\n", e);
s = aux->next;
free(aux);
return s;
}
void top(Stack *s)
{
    int e;
    Stack *aux;
    aux = s;
    if (s == NULL)
    {
        error("Stiva vida");
        return;
    }
    e = aux->elem;
    printf("Elementul din varful stivei este %d\n", e);
}
void printstack(Stack *s)
{
    Stack *aux;
    aux = s;
    if (aux == NULL)
        printf("\n Stiva vida \n");
    else
    {
        printf("Continutul stivei este: \n");
        while (aux != NULL)
        {
            printf("%d\n", aux->elem);
            aux = aux->next;
        }
    }
}
void error(char *msg)
{
    printf("\n %s \n", msg);
}
int main()
{
    Stack *s = NULL;
    s = initstack(s);
    if (emptystack(s))
        printf("Stiva este vida\n");
    else
        printf("Stiva nu este vida\n");
    s = push(100, s);
    s = push(200, s);
    s = push(300, s);
    printstack(s);
    s = pop(s);
    printstack(s);
    top(s);
    s = pop(s);
    printstack(s);
    top(s);
    if (emptystack(s))
        printf("Stiva este vida\n");
    else
        printf("Stiva nu este vida\n");
}