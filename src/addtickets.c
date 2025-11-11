#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/func.h"
#include "../include/structs.h"

void AddTicket(Queue *f)
{
    Ticket *newTicket = (Ticket *)malloc(sizeof(Ticket));
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
    printf("Requester ID: ");
    scanf("%d", &newTicket->requesterId);
    getchar();

    printf("Describe the issue:\n ");
    fgets(newTicket->description, 200, stdin);
    newTicket->description[strcspn(newTicket->description, "\n")] = '\0';

    do
    {
        printf("Priority (1 - Low | 5 - High):");
        scanf("%d", &newTicket->priority);
    } while (newTicket->priority < 1 || newTicket->priority > 5);

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
    printf("Ticket #%d added sucessfully!\n", newTicket->id);
    return;
}