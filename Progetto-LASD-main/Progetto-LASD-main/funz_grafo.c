#include <stdio.h>
#include <stdlib.h>

struct grafo{
    int numeroVertici;
    struct arco **adiacente;
};

struct arco{
    int key;
    struct arco *next;
};

struct grafo *creaGrafo(int n)
{
    struct grafo *G;
    int i;
    G = (struct grafo*)malloc(sizeof(struct grafo));
    if (G==NULL)
        printf("ERRORE: impossibile allocare memoria per il grafo\n");
    else
    {
        G->adiacente =(struct arco**)malloc(n*sizeof(struct arco*));
        if (G->adiacente==NULL)
        {
            printf("ERRORE: impossibile allocare memoria per la lista del grafo\n");
            free(G);
            G=NULL;
        }
        else
        {
            G->numeroVertici=n;
            for (i=0; i<n; i++)
                G->adiacente[i]=NULL;
        }
    }
    return(G);
}


void aggiungiArco(struct grafo *G, int u, int v)
{
    struct arco *new, *e;
    new = (struct arco*)malloc(sizeof(struct arco));
    if (new==NULL)
        printf("ERRORE: impossibile allocare memoria \n");
    else
    {
        new->key=v;
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


int grafoVuoto(struct grafo *G)
{
    return (G==NULL);
}

void stampaGrafo(struct grafo *G)
{
    int i, ne=0;
    struct arco *e;
    if(!grafoVuoto(G))
    {
        printf("\n Il grafo ha %d vertici\n", G->numeroVertici);
        for (i=0; i<G->numeroVertici; i++)
        {
            printf("nodi adiacenti al nodo %d -> ", i);
            e=G->adiacente[i];
            while (e!=NULL)
            {
                printf("%d ", e->key);
                ne=ne+1;
                e=e->next;
            }
            printf("\n");
        }
        printf("\n Il grafo ha %d archi \n", ne);
    }
}