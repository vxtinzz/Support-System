#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "../include/fakedata.h"
#include <time.h>

const char *SimulateDescription[20] = {
    "monitor piscando",
    "teclado com teclas faltando",
    "impressora não conecta",
    "login bloqueado",
    "wifi instável na sala 3",
    "erro de tela azul ao iniciar",
    "sistema não abre após atualização",
    "computador reiniciando sozinho",
    "email corporativo não sincroniza",
    "acesso negado ao servidor interno",
    "mouse parando de funcionar",
    "planilha corrompida no Excel",
    "fone de ouvido sem som",
    "microfone não detectado no Zoom",
    "erro ao salvar arquivo no drive compartilhado",
    "programa de ponto não carrega",
    "pendrive não reconhecido",
    "lentidão extrema ao inicializar",
    "janela travada no navegador",
    "erro de autenticação no sistema interno"
};

const int requestersIDs[10] = {
    101, 102, 103, 104, 105,
    106, 107, 108, 109, 110
};

typedef struct Ticket{
    int id;
    int requesterId;
    char description[200];
    int priority;
    Ticket *next;
} Ticket;

typedef struct{
    Ticket *begin;
    Ticket *end;
    int tot;
} Queue;

void AddTicket(Queue *f){
    Ticket *newTicket = (Ticket *)malloc(sizeof(Ticket));
    if (!newTicket)
    {
        printf("Error of Malloc.\n");
        return;
    }

    int lastId = 0;
    FILE *arq;
    arq = fopen("../../data/tickets.txt", "r");

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

    arq = fopen("../../data/tickets.txt", "a");
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

void ShowAllTickets(){
    Ticket newTicket;
    FILE *arq;
    arq = fopen("../../data/tickets.txt", "r");
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

void FindTicketbyId(int id){
    Ticket Ticket;
    FILE *arq;
    arq = fopen("../../data/tickets.txt", "r");
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

void AttendNextTicket(){
    // declaration
    FILE *arq;
    FILE *temp;
    arq = fopen("../../data/tickets.txt", "r");
    temp = fopen("../../data/temp.txt", "w");
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

        remove("../../data/tickets.txt");
        rename("../../data/temp.txt", "../../data/tickets.txt");

        system("cls");
        printf("\n\n\nTicket #%d Attended Sucessfully!!\n\n\n", bigPriority->id);
    }
}

void AttendTicketById(int id){
    FILE *arq;
    FILE *temp;
    arq = fopen("../../data/tickets.txt", "r");
    temp = fopen("../../data/temp.txt", "w");
    Ticket loadTicket;
    if(arq != NULL){
        while(fscanf(arq, "%d;%d;%199[^;];%d\n",&loadTicket.id, &loadTicket.requesterId, loadTicket.description, &loadTicket.priority) != EOF){
            if(loadTicket.id != id){
                fprintf(temp, "%d;%d;%s;%d\n", loadTicket.id, loadTicket.requesterId, loadTicket.description, loadTicket.priority);
            }
        }

        fclose(arq);
        fclose(temp);

        remove("../../data/tickets.txt");
        rename("../../data/temp.txt", "../data/tickets.txt");

        system("cls");
        printf("\n\n\nTicket #%d Attended Sucessfully!!\n\n\n", id);
    }
}
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
    arq = fopen("../../data/tickets.txt", "r");

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

    arq = fopen("../../data/tickets.txt", "a");
    if (arq == NULL)
    {
        printf("Failed to open file for writing.\n");
        return;
    }
    fprintf(arq, "%d;%d;%s;%d\n", newTicket->id, newTicket->requesterId, newTicket->description, newTicket->priority);
    fclose(arq);
    printf("\nTicket #%d added sucessfully!\n\n", newTicket->id);
    return;

}

void SimulatePainel(){
    srand(time(NULL));

    printf("\n=== Starting Help Desk Simulation Panel ===\n");
    while (1) {
        printf("\n--- Step %d ---\n", step + 1);

        // 1️⃣ A cada iteração, 50% de chance de novo ticket
        if (rand() % 2 == 0) {
            printf("\n📨 New ticket received!\n");
            SimulateTickets();
        }

        // 2️⃣ A cada 2 iterações, tenta atender um ticket
        if (step % 2 == 1) {
            printf("\n🧑‍🔧 Attending next ticket...\n");
            AttendNextTicket();
        }

        // 3️⃣ Exibe status atual da fila
        printf("\n📋 Current queue:\n");
        ShowQueue(); // pode ser só leitura do arquivo ou ponteiro de fila

        // 4️⃣ Espera 3 segundos (ajuste conforme o ritmo que quiser)
        Sleep(3000);

        step++;
        if (step > 10) break; // simula 10 ciclos
    }

    printf("\n=== Simulation ended ===\n");
}
}
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
        SimulateTickets();
            break;
        }
    } while (op != 0);

    return 0;
}