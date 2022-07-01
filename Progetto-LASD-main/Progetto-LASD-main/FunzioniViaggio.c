#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "StrutturaViaggio.h"


struct viaggio *creaGrafoViaggio(int n)
{
    struct viaggio *G;
    int i;
    G = (struct viaggio*)malloc(sizeof(struct viaggio));
    if (G==NULL)
        printf("ERRORE: impossibile allocare memoria per il grafo\n");
    else
    {
        G->adiacente =(struct tratta**)malloc(n*sizeof(struct tratta*));
        if (G->adiacente==NULL)
        {
            printf("ERRORE: impossibile allocare memoria per la lista del grafo\n");
            free(G);
            G=NULL;
        }
        else
        {
            G->numCitta=n;
            for (i=0; i<n; i++)
                G->adiacente[i]=NULL;
        }
    }
    return(G);
}


void aggiungiTrattaViaggio(struct viaggio *G, int u, int v)
{
    struct tratta *new, *e;
    new = (struct tratta*)malloc(sizeof(struct tratta));
    if (new==NULL)
        printf("ERRORE: impossibile allocare memoria \n");
    else
    {
        new->citta=v;
        new->next=NULL;
        if (G->adiacente[u] == NULL)
            G->adiacente[u] = new;
        else
        {
            e=G->adiacente[u];
            while (e->next!=NULL)
                e=e->next;
            e->next=new;
        }
    }
}


int grafoVuoto(struct viaggio *G)
{
    return (G==NULL);
}


void stampaGrafoViaggio(struct viaggio *G)
{
    int i, ne=0;
    struct tratta *e;
    if(!grafoVuoto(G))
    {
        printf("\nIl grafo ha %d vertici\n", G->numCitta);
        for (i=0; i<G->numCitta; i++)
        {
            printf("nodi adiacenti al nodo %d -> ", i);
            e=G->adiacente[i];
            while (e!=NULL)
            {
                printf("%d ", e->citta);
                ne=ne+1;
                e=e->next;
            }
            printf("\n");
        }
        printf("\nIl grafo ha %d archi \n", ne);
    }
}


char **leggiFileViaggioCitta(FILE *fp, int numCitta)
{
    char nome[10];
    int contatore=0;
    char **vet;
    vet=(char **)malloc(numCitta*sizeof(char*));
    for (int i=0; i<numCitta; i++) {
        vet[i]=(char *)malloc(10*sizeof(char));
    }
    while(contatore<numCitta)
    {
        fscanf(fp, "%s",nome);
        strcpy(vet[contatore], nome);
        contatore++;
    }
    
    return vet;
}


int contaNodi(FILE *fp)
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
