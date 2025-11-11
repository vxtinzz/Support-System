#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/func.h"
#include "../include/structs.h"

void AttendNextTicket(){
    // declaration
    FILE *arq;
    FILE *temp;
    arq = fopen("../data/tickets.txt", "r");
    temp = fopen("../data/temp.txt", "w");
    Queue *f = (Queue *)malloc(sizeof(Queue));
    Ticket *bigPriority = (Ticket *)malloc(sizeof(Ticket));
    Ticket ticket;
    Ticket *aux;
    // init
    bigPriority->priority = 0;
    f->begin = NULL;
    f->end = NULL;
    f->tot = 0;

    if (arq != NULL)
    {
        while (fscanf(arq, "%d;%d;%199[^;];%d\n", &ticket.id, &ticket.requesterId, ticket.description, &ticket.priority) != EOF)
        {
            Ticket *loadTicket = (Ticket *)malloc(sizeof(Ticket));
            loadTicket->next = NULL;
            loadTicket->id = ticket.id;
            loadTicket->requesterId = ticket.requesterId;
            strcpy(loadTicket->description, ticket.description);
            loadTicket->priority = ticket.priority;
            if (f->end == NULL)
            {
                f->begin = loadTicket;
            }
            else
            {
                f->end->next = loadTicket;
            }
            f->end = loadTicket;
            f->tot++;
            if (loadTicket->priority > bigPriority->priority)
            {
                bigPriority = loadTicket;
            }}
        aux = f->begin;
        int cont = 0;
        while (aux != NULL)
        {
            cont++;
            if (aux->id != bigPriority->id)
            {
                fprintf(temp, "%d;%d;%s;%d\n", aux->id, aux->requesterId, aux->description, aux->priority);
            }
            aux = aux->next;
        }
        fclose(arq);
        fclose(temp);

        remove("../data/tickets.txt");
        rename("../data/temp.txt", "../data/tickets.txt");

        system("cls");
        printf("\n\n\nTicket #%d Attended Sucessfully!!\n\n\n", bigPriority->id);
    }
}