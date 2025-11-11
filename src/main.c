#include <stdio.h>
#include <stdlib.h>
#include "../include/func.h"

int main()
{
    int op, id;
    Queue queue = {NULL, NULL, 0};

    printf("\n==Support System==\n");
    do
    {
        printf("1 - Add Ticket\n2 - Show All Tickets\n3 - Search Ticket by ID\n4 - Attend Next Ticket (by Priority)\n5 - Attend Ticket by ID\n6 - SIMULATION [10]\n7 - EXIT[0]\n Choose an option: ");
        scanf("%d", &op);
        switch (op)
        {
        case 0:
            break;
        case 1:
            system("cls");
            AddTicket(&queue);
            break;
        case 2:
            system("cls");
            ShowAllTickets();
            break;
        case 3:
            system("cls");
            printf("Search by ID: ");
            scanf("%d", &id);
            FindTicketbyId(id);
            break;
        case 4:
            AttendNextTicket();
            break;
        case 5:
        system("cls");
            printf("Attend by ID: ");
            scanf("%d", &id);
            AttendTicketById(id);
        break;
        case 10:
        system("cls");
        SimulatePanel();
            break;
        }
    } while (op != 0);

    return 0;
}