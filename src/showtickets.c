#include <stdio.h>
#include "../include/func.h"
#include "../include/structs.h"

void ShowAllTickets(){
    Ticket newTicket;
    FILE *arq;
    arq = fopen("../data/tickets.txt", "r");
    if (arq == NULL)
    {
        printf("File Empty!\n");
        return;
    }
    printf("----Tickets List----\n");
    while (fscanf(arq, "%d;%d;%199[^;];%d\n", &newTicket.id, &newTicket.requesterId, newTicket.description, &newTicket.priority) != EOF)
    {
        printf("ID: %d\n", newTicket.id);
        printf("Requester ID: %d\n", newTicket.requesterId);
        printf("Description: %s\n", newTicket.description);
        printf("Priority: %d\n", newTicket.priority);
        printf("------------------------\n");
    }
    fclose(arq);
}