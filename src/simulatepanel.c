#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include "../include/func.h"

void SimulatePanel(){
    srand(time(NULL));

    printf("\n=== Starting Help Desk Simulation Panel ===\n");
    Sleep(2000);
    while (1) {

        if (rand() % 2 == 0) {
            SimulateTickets();
            system("cls");
            ShowAllTickets();
        }
            Sleep(2000);
        if (rand() % 2 == 1) {
            AttendNextTicket();
            system("cls");
            ShowAllTickets();
        }
            Sleep(2000);
    }

    printf("\n=== Simulation ended ===\n");
}