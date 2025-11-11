#ifndef TICKETS_H
#define TICKETS_H

typedef struct Ticket{
    int id;
    int requesterId;
    char description[200];
    int priority;
    struct Ticket *next;
}Ticket;

typedef struct{
    Ticket *begin;
    Ticket *end;
    int tot;
}Queue;

extern const char *SimulateDescription[];
extern const int requestersIDs[];

#endif