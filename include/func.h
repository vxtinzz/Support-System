#ifndef FUNC_H
#define FUNC_H

#include "structs.h"

void AddTicket(Queue *f);
void ShowAllTickets();
void FindTicketbyId(int id);
void AttendNextTicket();
void AttendTicketById(int id);
void SimulateTickets();
void SimulatePanel();

#endif
