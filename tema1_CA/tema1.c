#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "help.h"

void ADD_DECK(card_node **head, int nr_cards)
{
    int deck_nr = 0;
    int i = 0;
    int oncard_nr, cursor = 8;
    char *symbol;
    symbol = (char *)malloc(10 * sizeof(char));
    card_node *new;
    new = (card_node *)malloc(sizeof(card_node));
    new->data = malloc(8 + nr_cards * 14);
    memcpy(new->data, &deck_nr, sizeof(int));
    memcpy(new->data + 4, &nr_cards, sizeof(int));
    for (i = 0; i < nr_cards; i++)
    {
        scanf("%d", &oncard_nr);
        scanf("%s", symbol);
        if (check_valid(oncard_nr, symbol) != 1)
        {
            printf("The provided card is not a valid one.\n");
            i = i - 1;
        }
        else
        {
            memcpy(new->data + cursor, &oncard_nr, sizeof(int));
            cursor = cursor + 4;
            memcpy(new->data + cursor, symbol, 10);
            cursor = cursor + 10;
        }
    }
    free(symbol);
    if ((*head) == NULL)
    {
        *head = new;
        (*head)->prev = NULL;
        (*head)->next = NULL;
    }
    else
    {
        card_node *temp;
        temp = *head;
        deck_nr = 1;
        while (temp->next != NULL)
        {
            temp = temp->next;
            deck_nr = deck_nr + 1;
        }
        memcpy(new->data, &deck_nr, sizeof(int));
        memcpy(new->data + 4, &nr_cards, sizeof(int));
        temp->next = new;
        new->prev = temp;
        new->next = NULL;
    }

    printf("The deck was successfully created with %d cards.\n", nr_cards);
}

void ADD_CARDS(card_node **head, int deck_nr, int nr_cards)
{
    card_node *temp;
    int init_nrcards;
    temp = find_deck(*head, deck_nr);
    if (temp == NULL)
    {
        printf("The provided index is out of bounds for the deck list.\n");
        return;
    }
    memcpy(&init_nrcards, temp->data + 4, sizeof(int));
    init_nrcards = init_nrcards + nr_cards;
    temp->data = realloc(temp->data, 8 + init_nrcards * 14);

    memcpy(temp->data, &deck_nr, sizeof(int));
    memcpy(temp->data + 4, &init_nrcards, sizeof(int));
    int i = 0, oncard_nr, contor;
    char *symbol;
    symbol = (char *)malloc(10 * sizeof(char));
    contor = 8 + (init_nrcards - nr_cards) * 14;
    for (i = 0; i < nr_cards; i++)
    {
        scanf("%d", &oncard_nr);
        scanf("%s", symbol);
        if (check_valid(oncard_nr, symbol) == 0)
        {
            printf("The provided card is not a valid one.\n");
            i = i - 1;
        }
        else
        {
            memcpy(temp->data + contor, &oncard_nr, sizeof(int));
            contor = contor + 4;
            memcpy(temp->data + contor, symbol, 10);
            contor = contor + 10;
        }
    }
    free(symbol);
    printf("The cards were successfully added to deck %d.\n", deck_nr);
}

void SHOW_ALL(card_node *head)
{
    card_node *temp;
    temp = head;
    int deck_nr, nr_cards, i = 0, oncard_nr, contor = 8;
    char *symbol;
    while (temp != NULL)
    {
        memcpy(&deck_nr, temp->data, sizeof(int));
        memcpy(&nr_cards, temp->data + 4, sizeof(int));
        printf("Deck %d:\n", deck_nr);
        for (i = 0; i < nr_cards; i++)
        {
            symbol = malloc(10 * sizeof(char));
            memcpy(&oncard_nr, temp->data + contor, sizeof(int));
            contor = contor + 4;
            memcpy(symbol, temp->data + contor, 10 * sizeof(char));
            contor = contor + 10;
            printf("\t%d ", oncard_nr);
            printf("%s\n", symbol);
            free(symbol);
        }
        contor = 8;
        temp = temp->next;
    }
}

void SHOW_DECK(card_node *head, int deck_nr)
{
    card_node *temp;
    temp = find_deck(head, deck_nr);
    if (temp == NULL)
    {
        printf("The provided index is out of bounds for the deck list.\n");
        return;
    }
    printf("Deck %d:\n", deck_nr);
    int nr_cards, contor = 8, oncard_nr;
    char *symbol;

    memcpy(&nr_cards, temp->data + 4, sizeof(int));
    int i = 0;
    for (i = 0; i < nr_cards; i++)
    {
        symbol = malloc(10 * sizeof(char));
        memcpy(&oncard_nr, temp->data + contor, sizeof(int));
        contor = contor + 4;
        memcpy(symbol, temp->data + contor, 10 * sizeof(char));
        contor = contor + 10;
        printf("\t%d ", oncard_nr);
        printf("%s\n", symbol);
        free(symbol);
    }
}

int DEL_DECK(card_node **head, int deck_nr)
{
    int deck_replace;
    card_node *temp, *temp2;
    temp = *head;
    temp = find_deck(*head, deck_nr);
    if (temp == NULL)
    {
        printf("The provided index is out of bounds for the deck list.\n");
        return 0;
    }
    if (temp == *head)
    {
        if ((*head)->next != NULL)
        {
            *head = (*head)->next;
            free_card(temp);
            temp = *head;
            goto find;
        }
        else
        {
            free_card(*head);
            *head = NULL;
            return 1;
        }
    }
    if (temp->next == NULL && temp->prev != NULL)
    {
        temp = temp->prev;
        free_card(temp->next);
        temp->next = NULL;
        goto find;
    }
    if (temp->next != NULL && temp->prev != NULL)
    {
        temp2 = temp->next;
        temp->next->prev = temp->prev;
        temp->prev->next = temp->next;
        free_card(temp);
        temp = temp2;
        goto find;
    }
find:
    while (temp != NULL)
    {
        memcpy(&deck_replace, temp->data, sizeof(int));
        if (deck_replace > deck_nr)
        {
            deck_replace = deck_replace - 1;
            memcpy(temp->data, &deck_replace, sizeof(int));
        }
        temp = temp->next;
    }
    return 1;
}

void DEL_CARD(card_node **head, int deck_nr, int card_to_del)
{
    card_node *temp;
    temp = *head;
    int nr_cards;
    temp = find_deck(*head, deck_nr);
    if (temp == NULL)
    {
        printf("The provided index is out of bounds for the deck list.\n");
        return;
    }
    memcpy(&nr_cards, temp->data + 4, sizeof(int));
    if (nr_cards <= card_to_del || card_to_del < 0)
    {
        printf("The provided index is out of bounds for deck %d.\n", deck_nr);
        return;
    }
    if (nr_cards == 1 && card_to_del == 0)
    {
        DEL_DECK(head, deck_nr);
        printf("The card was successfully deleted from deck %d.\n", deck_nr);
        return;
    }
    else
    {
        memcpy(temp->data + 8 + card_to_del * 14, temp->data + 8 + (card_to_del + 1) * 14, (nr_cards - card_to_del - 1) * 14);
    }
    nr_cards = nr_cards - 1;
    memcpy(temp->data + 4, &nr_cards, sizeof(int));
    printf("The card was successfully deleted from deck %d.\n", deck_nr);
}

void DECK_NUMBER(card_node *head)
{
    int deck_total = 0;
    card_node *temp;
    temp = head;
    while (temp != NULL)
    {
        deck_total = deck_total + 1;
        temp = temp->next;
    }
    printf("The number of decks is %d.\n", deck_total);
}

void DECK_LEN(card_node *head, int deck_nr)
{
    card_node *temp;
    temp = head;
    int extractt;
    temp = find_deck(head, deck_nr);
    if (temp == NULL)
    {
        printf("The provided index is out of bounds for the deck list.\n");
        return;
    }
    memcpy(&extractt, temp->data + 4, sizeof(int));
    printf("The length of deck %d is %d.\n", deck_nr, extractt);
}

void REVERSE_DECK(card_node **head, int deck_nr)
{
    card_node *temp;
    temp = find_deck(*head, deck_nr);

    if (temp == NULL)
    {
        printf("The provided index is out of bounds for the deck list.\n");
        return;
    }

    int extractt, contor_left, contor_right;
    int i;
    memcpy(&extractt, temp->data + 4, sizeof(int));
    void *aux;
    aux = malloc(14 * sizeof(char));
    contor_left = 8;                        // prima carte
    contor_right = 8 + (extractt - 1) * 14; // ultima carte

    for (i = 0; i < extractt / 2; i++)
    {
        memcpy(aux, temp->data + contor_left, 14);
        memcpy(temp->data + contor_left, temp->data + contor_right, 14);
        memcpy(temp->data + contor_right, aux, 14);
        contor_left = contor_left + 14;
        contor_right = contor_right - 14;
    }

    free(aux);
    printf("The deck %d was successfully reversed.\n", deck_nr);
}

void SHUFFLE_DECK(card_node **head, int deck_nr)
{
    card_node *temp;
    temp = find_deck(*head, deck_nr);

    if (temp == NULL)
    {
        printf("The provided index is out of bounds for the deck list.\n");
        return;
    }

    int extractt, left_half, right_half;
    memcpy(&extractt, temp->data + 4, sizeof(int));
    void *aux;

    if (extractt % 2 == 0)
    {
        aux = malloc(extractt / 2 * 14);
        left_half = 8;
        right_half = 8 + extractt / 2 * 14;
        memcpy(aux, temp->data + left_half, extractt / 2 * 14);
        memcpy(temp->data + left_half, temp->data + right_half, extractt / 2 * 14);
        memcpy(temp->data + right_half, aux, extractt / 2 * 14);
    }

    if (extractt % 2 == 1)
    {
        aux = malloc(extractt / 2 * 14);
        left_half = 8;
        right_half = 8 + extractt / 2 * 14;
        memcpy(aux, temp->data + left_half, extractt / 2 * 14);
        memcpy(temp->data + left_half, temp->data + right_half, (extractt / 2 + 1) * 14);
        memcpy(temp->data + right_half + 14, aux, extractt / 2 * 14);
    }

    free(aux);
    printf("The deck %d was successfully shuffled.\n", deck_nr);
}

void MERGE_DECKS(card_node **head, int deck_nr1, int deck_nr2)
{
    card_node *temp1;
    card_node *temp2;
    temp1 = find_deck(*head, deck_nr1);
    temp2 = find_deck(*head, deck_nr2);
    if (temp1 == NULL || temp2 == NULL)
    {
        printf("The provided index is out of bounds for the deck list.\n");
        return;
    }
    int contor1 = 8, contor = 8;
    int nr_cards1, nr_cards2;
    memcpy(&nr_cards1, temp1->data + 4, sizeof(int));
    memcpy(&nr_cards2, temp2->data + 4, sizeof(int));

    card_node *new;
    new = (card_node *)malloc(sizeof(card_node));
    new->data = malloc(8 + (nr_cards1 + nr_cards2) * 14);
    int i = 0;
    while (nr_cards1 > i && nr_cards2 > i)
    {
        memcpy(new->data + contor, temp1->data + contor1, 14);
        contor = contor + 14;
        memcpy(new->data + contor, temp2->data + contor1, 14);
        contor = contor + 14;
        contor1 = contor1 + 14;
        i = i + 1;
    }
    if (i == nr_cards1)
    {
        memcpy(new->data + contor, temp2->data + contor1, (nr_cards2 - nr_cards1) * 14);
    }
    else
    {
        memcpy(new->data + contor, temp1->data + contor1, (nr_cards1 - nr_cards2) * 14);
    }

    int deck_nr;

    if (deck_nr1 < deck_nr2)
    {
        DEL_DECK(head, deck_nr2);
        DEL_DECK(head, deck_nr1);
    }
    else
    {
        DEL_DECK(head, deck_nr1);
        DEL_DECK(head, deck_nr2);
    }

    card_node *aux;
    aux = *head;
    while (aux->next != NULL)
    {
        aux = aux->next;
    }

    memcpy(&deck_nr, aux->data, sizeof(int));
    deck_nr = deck_nr + 1;
    memcpy(new->data, &deck_nr, sizeof(int));
    nr_cards1 = nr_cards1 + nr_cards2;
    memcpy(new->data + 4, &nr_cards1, sizeof(int));
    aux->next = new;
    new->prev = aux;
    new->next = NULL;
    printf("The deck %d and the deck %d were successfully merged.\n", deck_nr1, deck_nr2);
}

void SPLIT_DECK(card_node **head, int deck_nr, int index_split)
{
    card_node *temp;
    temp = find_deck(*head, deck_nr);
    if (temp == NULL)
    {
        printf("The provided index is out of bounds for the deck list.\n");
        return;
    }

    int nr_cards;
    memcpy(&nr_cards, temp->data + 4, sizeof(int));
    if (nr_cards < index_split || index_split < 0)
    {
        printf("The provided index is out of bounds for deck %d.\n", deck_nr);
        return;
    }

    if (index_split == 0 || index_split == nr_cards)
    {
        printf("The deck %d was successfully split by index %d.\n", deck_nr, index_split);
        return;
    }

    card_node *new;
    new = (card_node *)malloc(sizeof(card_node));
    new->data = malloc(8 + (nr_cards - index_split) * 14);
    memcpy(new->data + 8, temp->data + 8 + index_split * 14, (nr_cards - index_split) * 14);
    int nr_cards_new;
    nr_cards_new = nr_cards - index_split;
    memcpy(temp->data + 4, &index_split, sizeof(int));
    memcpy(new->data + 4, &nr_cards_new, sizeof(int));
    deck_nr = deck_nr + 1;
    memcpy(new->data, &deck_nr, sizeof(int));
    deck_nr = deck_nr - 1;
    card_node *continuation;
    continuation = temp->next;
    temp->next = new;
    new->prev = temp;
    new->next = continuation;
    if (continuation != NULL)
    {
        continuation->prev = new;
    }
    int adjust_deck = deck_nr + 2;
    while (continuation != NULL)
    {
        memcpy(continuation->data, &adjust_deck, sizeof(int));
        continuation = continuation->next;
        adjust_deck = adjust_deck + 1;
    }

    printf("The deck %d was successfully split by index %d.\n", deck_nr, index_split);
}

// void SORT_DECK(card_node **head,int deck_nr)
// {
    // card_node *temp;
    // temp=find_deck(*head,deck_nr);
    // int nr_cards;
    // void *to_replace;
    // memcpy(&nr_cards,temp->data+4,sizeof(int));
    // to_replace=malloc(8+14*nr_cards);
    // memcpy(to_replace,&deck_nr,sizeof(int));
    // memcpy(to_replace+4,&nr_cards,sizeof(int));
    // //acum trebuie ca un selection sort
    // void *token;
    // token=malloc(14*sizeof(char));
    // int oncard_nr;
    // oncard_nr=-1;
    // memcpy(token,&oncard_nr,sizeof(int));
    // char *symbol;
    // symbol=malloc(10);
    // symbol="HEART";

    // printf("The deck %d was successfully sorted.\n",deck_nr);
// }   
int main()
{
    // clock_t begin = clock();
    card_node *head;
    head = NULL;
    char *command;
    command = (char *)malloc(15 * sizeof(char));
    int deck_nr, nr_cards;
    scanf("%s", command);
    while (memcmp(command, "EXIT", 5) != 0)
    {
        if (memcmp(command, "ADD", 3) == 0)
        {
            if (memcmp(command, "ADD_DECK", 9) == 0)
            {
                char *input;
                input = (char *)malloc(10 * sizeof(char));
                fgets(input, 10, stdin);
                if (check_1_argv(input, &nr_cards) == 1)
                {
                    ADD_DECK(&head, nr_cards);
                    free(input);
                    goto lala;
                }
                printf("Invalid command. Please try again.\n");
                free(input);
                goto lala;
            }
            if (memcmp(command, "ADD_CARDS", 10) == 0)
            {
                char *input;
                input = (char *)malloc(10);
                fgets(input, 10, stdin);
                if (check_2_argv(input, &deck_nr, &nr_cards) == 1)
                {
                    ADD_CARDS(&head, deck_nr, nr_cards);
                    free(input);
                    goto lala;
                }
                printf("Invalid command. Please try again.\n");
                free(input);
                goto lala;
            }
        }

        if (memcmp(command, "DEL", 3) == 0)
        {
            if (memcmp(command, "DEL_DECK", 9) == 0)
            {
                char *input;
                input = (char *)malloc(10 * sizeof(char));
                fgets(input, 10, stdin);
                if (check_1_argv(input, &deck_nr) == 1)
                {
                    card_node *temp;
                    temp = find_deck(head, deck_nr);
                    if (temp != NULL)
                    {
                        printf("The deck %d was successfully deleted.\n", deck_nr);
                    }
                    DEL_DECK(&head, deck_nr);
                    free(input);
                    goto lala;
                }
                printf("Invalid command. Please try again.\n");
                free(input);
                goto lala;
            }
            if (memcmp(command, "DEL_CARD", 9) == 0)
            {
                int card_nr;
                char *input;
                input = (char *)malloc(10);
                fgets(input, 10, stdin);
                if (check_2_argv(input, &deck_nr, &card_nr) == 1)
                {
                    DEL_CARD(&head, deck_nr, card_nr);
                    free(input);
                    goto lala;
                }
                printf("Invalid command. Please try again.\n");
                free(input);
                goto lala;
            }
        }

        if (memcmp(command, "SHOW", 4) == 0)
        {
            if (memcmp(command, "SHOW_ALL", 9) == 0)
            {
                char *input;
                input = malloc(10 * sizeof(char));
                fgets(input, 10, stdin);
                if (input_at_all(input) == 1)
                {
                    SHOW_ALL(head);
                    free(input);
                    goto lala;
                }
                else
                {
                    free(input);
                    printf("Invalid command. Please try again.\n");
                    goto lala;
                }
            }
            if (memcmp(command, "SHOW_DECK", 10) == 0)
            {
                char *input;
                input = (char *)malloc(10 * sizeof(char));
                fgets(input, 10, stdin);
                if (check_1_argv(input, &deck_nr) == 1)
                {
                    SHOW_DECK(head, deck_nr);
                    free(input);
                    goto lala;
                }
                printf("Invalid command. Please try again.\n");
                free(input);
                goto lala;
            }
        }
        if (memcmp(command, "DECK", 4) == 0)
        {
            if (memcmp(command, "DECK_NUMBER", 12) == 0)
            {
                char *input;
                input = malloc(10 * sizeof(char));
                fgets(input, 10, stdin);
                if (input_at_all(input) == 1)
                {
                    DECK_NUMBER(head);
                    free(input);
                    goto lala;
                }
                else
                {
                    free(input);
                    printf("Invalid command. Please try again.\n");
                    goto lala;
                }
            }  
            if (memcmp(command, "DECK_LEN", 9) == 0)
            {
                char *input;
                input = (char *)malloc(10 * sizeof(char));
                fgets(input, 10, stdin);
                if (check_1_argv(input, &deck_nr) == 1)
                {
                    DECK_LEN(head, deck_nr);
                    free(input);
                    goto lala;
                }
                printf("Invalid command. Please try again.\n");
                free(input);
                goto lala;
            }
        }

        if (memcmp(command, "REVERSE_DECK", 13) == 0)
        {
            char *input;
                input = (char *)malloc(10 * sizeof(char));
                fgets(input, 10, stdin);
                if (check_1_argv(input, &deck_nr) == 1)
                {
                    REVERSE_DECK(&head, deck_nr);
                    free(input);
                    goto lala;
                }
                printf("Invalid command. Please try again.\n");
                free(input);
                goto lala;
            }
        

        if (memcmp(command, "SHUFFLE_DECK", 13) == 0)
        {
            char *input;
            input = (char *)malloc(10 * sizeof(char));
            fgets(input, 10, stdin);
            if (check_1_argv(input, &deck_nr) == 1)
            {
                SHUFFLE_DECK(&head, deck_nr);
                free(input);
                goto lala;
            }
            printf("Invalid command. Please try again.\n");
            free(input);
            goto lala;
        }

        if (memcmp(command, "MERGE_DECKS", 12) == 0)
        {
            int deck_nr2;
            char *input;
            input = (char *)malloc(10);
            fgets(input, 10, stdin);
            if (check_2_argv(input, &deck_nr, &deck_nr2) == 1)
            {
                MERGE_DECKS(&head, deck_nr, deck_nr2);
                free(input);
                goto lala;
            }
            printf("Invalid command. Please try again.\n");
            free(input);
            goto lala;
        }

        if (memcmp(command, "SPLIT_DECK", 11) == 0)
        {
            int index_split;
            char *input;
            input = (char *)malloc(10);
            fgets(input, 10, stdin);
            if (check_2_argv(input, &deck_nr, &index_split) == 1)
            {
                SPLIT_DECK(&head, deck_nr, index_split);
                free(input);
                goto lala;
            }
            printf("Invalid command. Please try again.\n");
            free(input);
            goto lala;
        }
        if(memcmp(command,"SORT_DECK",10)==0)
        {
            // char *input;
            // input = (char *)malloc(10 * sizeof(char));
            // fgets(input, 10, stdin);
            // if (check_1_argv(input, &deck_nr) == 1)
            // {
            //     SORT_DECK(&head, deck_nr);
            //     free(input);
            //     goto lala;
            // }
            // printf("Invalid command. Please try again.\n");
            // free(input);
            scanf("%d",&deck_nr);
            goto lala;
        }

        printf("Invalid command. Please try again.\n");
    lala:
        scanf("%s", command);
    }
    free(command);
    free_memory(head);
}