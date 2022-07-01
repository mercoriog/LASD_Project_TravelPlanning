#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "FunzioniCitta.h"

struct citta *CreaGrafo(int n){
    struct citta *G;
    int i;
    G = (struct citta*)malloc(sizeof(struct citta));
    if (G==NULL)
        printf("ERRORE: impossibile allocare memoria per il grafo della citta\n");
    else
    {
        G->adiacente =(struct tragitto**)malloc(n*sizeof(struct tragitto*));
        if (G->adiacente==NULL)
        {
            printf("ERRORE: impossibile allocare memoria per la lista della citta\n");
            free(G);
            G=NULL;
        }
        else
        {
            G->nL=n;
            for (i=0; i<n; i++)
                G->adiacente[i]=NULL;
        }
    }
    return(G);
}

void aggiungiArco(struct citta *G, int part, int arrivo, int dist)
{
    struct tragitto *new, *tmp;
    new = (struct tragitto*)malloc(sizeof(struct tragitto));
    if (new==NULL)
        printf("ERRORE: impossibile allocare memoria \n");
    else
    {
        new->distanza = dist;
        new->luogo=arrivo;
        new->next=NULL;
        if (G->adiacente[part] == NULL)
            G->adiacente[part] = new;
        else
        {
            tmp=G->adiacente[part];
            while (tmp->next!=NULL)
                tmp=tmp->next;
            tmp->next=new;
        }
    }
}

int cittaVuota(struct citta *G)
{
    return (G==NULL);
}

void StampaCittaNominata(struct citta *G, char **vLuoghi){
    int i, contaTragitto=0;
    struct tragitto *tmp;
    if(!cittaVuota(G))
    {
        printf("\n La citta ha %d luoghi\n", G->nL);
        for (i=0; i<G->nL; i++)
        {
            printf("luoghi adiacenti a %s -> ", vLuoghi[i]);
            tmp = G->adiacente[i];
            while (tmp!=NULL)
            {
                printf("%s[%d] ", vLuoghi[tmp->luogo], tmp->distanza);
                contaTragitto=contaTragitto+1;
                tmp = tmp->next;
            }
            printf("\n");
        }
        printf("\n La citta ha %d tragitti\n", contaTragitto);
    }
}

void StampaCitta(struct citta *G)
{
    int i, contaTragitto=0;
    struct tragitto *tmp;
    if(!cittaVuota(G))
    {
        printf("\n La citta ha %d luoghi\n", G->nL);
        for (i=0; i<G->nL; i++)
        {
            printf("nodi adiacenti al nodo %d -> ", i);
            tmp =G->adiacente[i];
            while (tmp!=NULL)
            {
                printf("%d ", tmp->luogo);
                contaTragitto=contaTragitto+1;
                tmp=tmp->next;
            }
            printf("\n");
        }
        printf("\n La citta ha %d tragitti\n", contaTragitto);
    }
}

char **leggiFileCitta(FILE *fp, int nLuoghi)
{
    char nome[10];
    int contatore=0, i= 0;
    char **vet = NULL;
    vet=(char **)malloc(nLuoghi*sizeof(char*));

    for (i=0; i<nLuoghi; i++) {
        vet[i]=(char *)malloc(10*sizeof(char));
    }

    while(contatore<nLuoghi)
    {
        fscanf(fp, "%s ",nome);
        strcpy(vet[contatore], nome);
        contatore++;
    }

    return vet;
}

int contaLuoghi(FILE *fp)
{
    char nome[10];
    int contatore=0;
    do
    {
        fscanf(fp, "%s",nome);
        contatore++;
    }while((strcmp(nome, "@@"))!=0);

    contatore--;
    return contatore;
}

void CaricaCitta(FILE *fp, struct citta *gCitta){
    int part, arr, dist;
    while(fscanf(fp, "%d %d %d", &part, &arr, &dist) == 3){
        aggiungiArco(gCitta, part, arr, dist);
    }
}

struct citta *CreaGrafoCitta(char *filename) {
    struct citta *grafoCitta = NULL;
    int nLuoghi;
    char fileExt[10] = ".txt";
    FILE *fp = NULL;
    puts(filename);

    fp = fopen(filename, "r");
    nLuoghi = contaLuoghi(fp);
    grafoCitta = CreaGrafo(nLuoghi);
    CaricaCitta(fp, grafoCitta);
    fclose(fp);

    return grafoCitta;
}

struct nodo* CreaNodo(int val){
    struct nodo *new = (struct nodo*)malloc(sizeof(struct nodo));
    new->val = val;
    new->next = NULL;
    return new;
}

struct nodo* Push(struct nodo *L, int val){
    if(!L) return CreaNodo(val);
    else{
        L->next = Push(L->next, val);
        return L;
    }
}

struct nodo* Pop(struct nodo *L){
    if(L->next) L->next = Pop(L->next);
    else{
        free(L);
        return NULL;
    }
    return L;
}

struct nodo* Delete(struct nodo* P){
    while(P)    P = Pop(P);
    return P;
}

struct nodo *Clone(struct nodo* P){
    struct nodo *new = NULL;
    while(P){
        new = Push(new, P->val);
        P = P->next;
    }
    return new;
}

void StampaPercorso(struct nodo *L){
    if(L){
        printf("%d -", L->val);
        if(L->next)StampaPercorso(L->next);
    }
    else printf("Percorso vuoto\n");
}

void StampaPercorsoNominato(struct nodo *L, char **vLuoghi){
    while(L){
        printf("%s ->", vLuoghi[L->val]);
        L = L->next;
    }
}

void Avanti(struct citta *G, int i, int arr, int *min, int parz, struct nodo *P, struct nodo **Pmin){
    struct tragitto *tmp;
    struct nodo *clone = NULL;

    if(i == arr){
        if(parz < *min){
            *min = parz;
            clone = Clone(P);
            *Pmin = clone;
        }
    }
    else{
        for(tmp = G->adiacente[i]; tmp; tmp = tmp->next)
            if(tmp->distanza + parz < *min){
                P = Push(P, tmp->luogo);
                clone = Clone(P);

                Avanti(G,tmp->luogo,arr, min, parz + tmp->distanza, clone, Pmin);

                clone = NULL;
                P = Pop(P);
            }
    }
    P = Delete(P);
}

struct nodo* TrovaPercorso(struct citta *G, int part, int arr, int *min)
{
    struct nodo *P = NULL, *Pmin = NULL, *clone = NULL;
    struct tragitto *tmp;

    P = Push(P, part);
    for(tmp = G->adiacente[part]; tmp; tmp = tmp->next){
        P = Push(P, tmp->luogo);
        clone = Clone(P);

        Avanti(G, tmp->luogo,arr, min, tmp->distanza, clone, &Pmin);

        clone = NULL;
        P = Pop(P);
    }
    P = Pop(P);

    return Pmin;
}


