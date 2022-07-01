#include "richieste.h"
#include <stdlib.h>
#include <stdio.h>

struct richiesta *creaRichiesta (int src, int dest){
    struct richiesta *nuovarichiesta = (struct richiesta *)malloc(sizeof(struct richiesta));
    nuovarichiesta->src=src;
    nuovarichiesta->dest=dest;
    nuovarichiesta->link=NULL;
    return nuovarichiesta;
}

struct richiesta *inserimento(struct richiesta *lista, int src, int dest){
    if(lista==NULL)
        return creaRichiesta(src, dest);
    lista->link=inserimento(lista->link,src, dest);
    return lista;
}

struct richiesta *leggiFileRichieste(struct richiesta *lista){
    int src;
    int dest;
    FILE *fu;
    fu = fopen("richieste.txt", "r");
    while(fscanf(fu,"%d %d", &src, &dest)==2)
    {
        lista = inserimento(lista, src, dest);
    }
    fclose(fu);
    return lista;
}

void scriviFileRichieste(struct richiesta *lista){
    FILE *filerichieste = fopen("richieste.txt", "w");
    if(filerichieste){
        while(lista != NULL){
            fprintf(filerichieste, "%d %d \n", lista->src, lista->dest);
            lista = lista->link;
        }
        fclose(filerichieste);
    }
    else
        puts("errore");
}

void svuotaListaRichieste(struct richiesta *lista){
    struct richiesta *tmp;
    while(lista!=NULL){
        tmp=lista;
        lista=lista->link;
        free(tmp);
    }
}

void stampaRichieste(struct richiesta *lista)
{
    int count = 1;
    while(lista != NULL){
        printf("%d: %d %d \n", count, lista->src, lista->dest);
        count++;
        lista = lista->link;
    }
}

int counter(struct richiesta *lista){
    int count = 0;
        while(lista != NULL){
            count++;
            lista = lista->link;
        }
        return count;
}

struct richiesta *rimuoviRichiesta(struct richiesta *lista, int src, int dest)
{
    struct richiesta *prec=NULL;
    struct richiesta *curr=lista;
    while(curr!=NULL && (curr->src != src || curr->dest != dest))
    {
        prec=curr;
        curr=curr->link;
    }

    if(curr!=NULL)
    {
        if(lista==curr)
            lista=curr->link;
        else
            prec->link=curr->link;

        free(curr);
    }

    return lista;
}

int ricerca(struct richiesta *lista, int src, int dest){
    int i = 0;
    while(lista != NULL){
        if(lista->src == src && lista->dest == dest){
            i = 1;
            break;
        }

        lista = lista->link;
    }
    return i;
}

struct richiesta *recuperaNodo(struct richiesta *lista, int index){
    int c = 1;
    struct richiesta *tmp = NULL;
    while(lista != NULL){
        if(c == index){
            tmp = lista;
            break;
        }
        c++;
        lista = lista->link;
    }
    return tmp;
}
