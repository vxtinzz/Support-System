#include <stdio.h>
#include <stdlib.h>
#include "../include/func.h"
#include "../include/structs.h"

void AttendTicketById(int id){
    FILE *arq;
    FILE *temp;
    arq = fopen("../data/tickets.txt", "r");
    temp = fopen("../data/temp.txt", "w");
    Ticket loadTicket;
    if(arq != NULL){
        while(fscanf(arq, "%d;%d;%199[^;];%d\n",&loadTicket.id, &loadTicket.requesterId, loadTicket.description, &loadTicket.priority) != EOF){
            if(loadTicket.id != id){
                fprintf(temp, "%d;%d;%s;%d\n", loadTicket.id, loadTicket.requesterId, loadTicket.description, loadTicket.priority);
            }
        }

        fclose(arq);
        fclose(temp);

        remove("../data/tickets.txt");
        rename("../data/temp.txt", "../data/tickets.txt");

        system("cls");
        printf("\n\n\nTicket #%d Attended Sucessfully!!\n\n\n", id);
    }
}