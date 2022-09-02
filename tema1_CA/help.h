typedef struct card_node
{
    void *data;
    struct card_node *next;
    struct card_node *prev;
} card_node;

int check_valid(int oncard_nr, char *symbol)
{
    if (oncard_nr < 0 || oncard_nr > 14)
    {
        return 0;
    }
    if (memcmp(symbol, "HEART", 6) != 0 && memcmp(symbol, "CLUB", 5) != 0 &&
        memcmp(symbol, "DIAMOND", 8) != 0 && memcmp(symbol, "SPADE", 6) != 0)
    {
        return 0;
    }
    return 1;
}

card_node *find_deck(card_node *head, int deck_nr)
{
    card_node *temp;
    temp = head;
    int extractt;
    while (temp != NULL)
    {
        memcpy(&extractt, temp->data, sizeof(int));
        if (extractt == deck_nr)
        {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

void free_card(card_node *card_to_del)
{
    free(card_to_del->data);
    free(card_to_del);
}

void free_memory(card_node *head)
{
    if (head == NULL)
    {
        return;
    }
    if (head->next == NULL)
    {
        free_card(head);
        return;
    }
    card_node *temp;
    temp = head->next;
    free_card(head);
    while (temp->next != NULL)
    {
        temp = temp->next;
        free_card(temp->prev);
    }
    free_card(temp);
}

int check_2_argv(char *input, int *deck_nr, int *index_split)
{
    char *turn_int, *help, *aux_turn_int;
    turn_int = (char *)malloc(5 * sizeof(char));
    aux_turn_int = turn_int;
    // aux_turn_int va tine minte adresa de memorie alocata initial
    turn_int = strtok(input, " ");
    *deck_nr =strtol(turn_int, &help, 10);
    if (turn_int != NULL)
    {
        turn_int = strtok(NULL, " ");
        *index_split = strtol(turn_int, &help, 10);
        if (turn_int != NULL)
        {
            turn_int = strtok(NULL, " ");
            // turn_int devine null daca nu mai e nimic ceea ce e bine
            if (turn_int != NULL)
            {
                free(aux_turn_int);
                return 0;
            }
        }
    }
    free(aux_turn_int);
    return 1;
}

int check_1_argv(char *input, int *deck_nr)
{
    char *turn_int, *help, *aux_turn_int;
    turn_int = (char *)malloc(5 * sizeof(char));
    aux_turn_int = turn_int;
     turn_int = strtok(input, " ");
    *deck_nr =strtol(turn_int, &help, 10);
    if (turn_int != NULL)
    {
        turn_int = strtok(NULL, " ");
        if (turn_int != NULL)
        {
                free(aux_turn_int);
                return 0;
        }
        
    }
    free(aux_turn_int);
    return 1;
}

int input_at_all(char *input)
{
    char *c="\n";
    if(*input==*c)
    {
        return 1;
    }
    else
    return 0;
}