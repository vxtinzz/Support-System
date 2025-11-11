#include <stdio.h>
#include "../include/func.h"
#include "../include/structs.h"

void FindTicketbyId(int id){
    Ticket Ticket;
    FILE *arq;
    arq = fopen("../data/tickets.txt", "r");
    if (arq == NULL)
    {
        printf("Failed to open file!\n");
        return;
    }
    printf("------------------------\n");
    while (fscanf(arq, "%d;%d;%199[^;];%d\n", &Ticket.id, &Ticket.requesterId, Ticket.description, &Ticket.priority) != EOF)
    {
        if (id == Ticket.id)
        {
            printf("ID: %d\n", Ticket.id);
            printf("Requester ID: %d\n", Ticket.requesterId);
            printf("Description: %s\n", Ticket.description);
            printf("Priority: %d\n", Ticket.priority);
            printf("------------------------\n");
        }
        else
        {
            printf("ID not found in database");
            printf("\n------------------------\n");
            return;
        }
    }
    fclose(arq);
}