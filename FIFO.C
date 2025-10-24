#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Ticket
{
    int id;
    int idSolicitante;
    char descricao[200];
    int prioridade;
    Ticket *next;
} Ticket;

typedef struct
{
    Ticket *begin;
    Ticket *end;
    int tot;
} Fila;

void AdicionarTicket(Fila *f)
{
    Ticket *newTicket = (Ticket *)malloc(sizeof(Ticket));
    if (!newTicket)
    {
        printf("Erro ao alocar memória.\n");
        return;
    }

    int lastId = 0;
    FILE *arq;
    arq = fopen("../data/tickets.txt", "r");

    if (arq != NULL)
    {
        while (fscanf(arq, "%d;%d;%199[^;];%d\n",
                      &newTicket->id, &newTicket->idSolicitante, newTicket->descricao, &newTicket->prioridade) != EOF)
        {
            lastId = newTicket->id;
        }
        fclose(arq);
    }

    newTicket->id = lastId + 1;
    printf("ID do Solicitante: ");
    scanf("%d", &newTicket->idSolicitante);
    getchar();

    printf("Descreva o Problema:\n ");
    fgets(newTicket->descricao, 200, stdin);
    newTicket->descricao[strcspn(newTicket->descricao, "\n")] = '\0';

    do
    {
        printf("Prioridade (1-5):");
        scanf("%d", &newTicket->prioridade);
    } while (newTicket->prioridade < 1 || newTicket->prioridade > 5);

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
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }
    fprintf(arq, "%d;%d;%s;%d\n", newTicket->id, newTicket->idSolicitante, newTicket->descricao, newTicket->prioridade);
    fclose(arq);
    printf("Ticket #%d adicionado com sucesso!\n", newTicket->id);
}

void READALL()
{
    Ticket newTicket;
    FILE *arq;
    arq = fopen("../data/tickets.txt", "r");
    if (arq == NULL)
    {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }
    printf("----Lista de Tickets----\n");
    while (fscanf(arq, "%d;%d;%199[^;];%d\n", &newTicket.id, &newTicket.idSolicitante, newTicket.descricao, &newTicket.prioridade) != EOF)
    {
        printf("ID: %d\n", newTicket.id);
        printf("ID Solicitante: %d\n", newTicket.idSolicitante);
        printf("Descricao: %s\n", newTicket.descricao);
        printf("Prioridade: %d\n", newTicket.prioridade);
        printf("------------------------\n");
    }
    fclose(arq);
}

void READ(int id)
{
    Ticket Ticket;
    FILE *arq;
    arq = fopen("../data/tickets.txt", "r");
    if (arq == NULL)
    {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }
    printf("------------------------\n");
    while (fscanf(arq, "%d;%d;%199[^;];%d\n", &Ticket.id, &Ticket.idSolicitante, Ticket.descricao, &Ticket.prioridade) != EOF)
    {
        if (id == Ticket.id)
        {
            printf("ID: %d\n", Ticket.id);
            printf("ID Solicitante: %d\n", Ticket.idSolicitante);
            printf("Descricao: %s\n", Ticket.descricao);
            printf("Prioridade: %d\n", Ticket.prioridade);
            printf("------------------------\n");
        }
        else
        {
            printf("ID nao encontrado na base de dados");
            printf("\n------------------------\n");
            return;
        }
    }
    fclose(arq);
}

void AtenderTicket()
{
    // declaration
    FILE *arq;
    FILE *temp;
    arq = fopen("../data/tickets.txt", "r");
    temp = fopen("../data/temp.txt", "a");
    Fila *f = (Fila *)malloc(sizeof(Fila));
    Ticket *bigPriority = (Ticket *)malloc(sizeof(Ticket));
    Ticket *ticket = (Ticket *)malloc(sizeof(Ticket));
    int id, idSolicitante, prioridade;
    char descricao[200];

    // init
    bigPriority->prioridade = 0;
    f->begin = NULL;
    f->end = NULL;
    f->tot = 0;

    if (arq != NULL)
    {
        while (fscanf(arq, "%d;%d;%199[^;];%d\n", &ticket->id, &ticket->idSolicitante, ticket->descricao, &ticket->prioridade) != EOF)
        {
            Ticket *loadTicket = (Ticket *)malloc(sizeof(Ticket));
            loadTicket = ticket;
            loadTicket->next = NULL;
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
            if (loadTicket->prioridade > bigPriority->prioridade)
            {
                bigPriority = loadTicket;
            }
        }

        Ticket *aux = f->begin;
        while (aux != NULL)
        {
            if (aux->id != bigPriority->id)
            {
                fprintf(temp, "%d;%d;%s;%d\n", aux->id, aux->idSolicitante, aux->descricao, aux->prioridade);
            }
            aux = aux->next;
        }
        fclose(arq);
        fclose(temp);

        remove("../data/tickets.txt");
        rename("../data/temp.txt", "../data/tickets.txt");

        printf("Ticket Atendido Com Sucesso!!\n");
    }
}

void AtenderTicketById(int id)
{
}
int main()
{
    int op, id;
    Fila fila = {NULL, NULL, 0};

    printf("==Sistema de Suporte==\n");
    do
    {
        printf("\n1 - Adicionar Ticket\n2 - Atender Ticket\n3 - Exibir Tickets\n4 - Buscar Ticket por ID\n5 - SIMULACAO[10]\n Escolha sua opcao: ");
        scanf("%d", &op);
        switch (op)
        {
        case 0:
            break;
        case 1:
            system("cls");
            AdicionarTicket(&fila);
            break;
        case 2:
            system("cls");
            do
            {
                printf("1-Atender Ticket Pelo ID\n2-Atender Ticket Mais Urgente\nEscolha sua opcao: ");
                scanf("%d", &op);

                switch (op)
                {
                case 1:
                    system("cls");
                    printf("Busca por ID: ");
                    scanf("%d", &id);
                    AtenderTicketById(id);
                    break;
                case 2:
                    system("cls");
                    AtenderTicket();
                }
            } while (op != 1 || op != 2);
            break;
        case 3:
            system("cls");
            READALL();
            break;
        case 4:
            system("cls");
            printf("Busca por ID: ");
            scanf("%d", &id);
            READ(id);
            break;
        case 10:
            break;
        }
    } while (op != 0);
    return 0;
}
