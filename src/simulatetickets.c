#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/func.h"
#include "../include/structs.h"

void SimulateTickets(){
    Ticket *newTicket = (Ticket *)malloc(sizeof(Ticket));
    Queue *f = (Queue *)malloc(sizeof(Queue));
    srand(time(NULL));
    f->begin = NULL;
    f->end = NULL;
    f->tot = 0;
    if (!newTicket)
    {
        printf("Error of Malloc.\n");
        return;
    }

    int lastId = 0;
    FILE *arq;
    arq = fopen("../data/tickets.txt", "r");

    if (arq != NULL)
    {
        while (fscanf(arq, "%d;%d;%199[^;];%d\n",
                      &newTicket->id, &newTicket->requesterId, newTicket->description, &newTicket->priority) != EOF)
        {
            lastId = newTicket->id;
        }
        fclose(arq);
    }
    newTicket->id = lastId + 1;
    newTicket->requesterId = requestersIDs[rand() % 10];
    strcpy(newTicket->description, SimulateDescription[rand() % 20]);
    newTicket->priority = rand() % 5 + 1;

    newTicket->next = NULL;
    if (f->end == NULL)
    {
        f->begin = newTicket;
    }
    else
    {
        f->end->next = newTicket;
    }
    f->end = newTicket;
    f->tot++;

    arq = fopen("../data/tickets.txt", "a");
    if (arq == NULL)
    {
        printf("Failed to open file for writing.\n");
        return;
    }
    fprintf(arq, "%d;%d;%s;%d\n", newTicket->id, newTicket->requesterId, newTicket->description, newTicket->priority);
    fclose(arq);
    printf("\nTicket #%d added sucessfully!\n\n", newTicket->id);
    return;
    free(newTicket);
    free(f);

}
