void dfs(struct grafo *G)
{
    int i, *aux = calloc(G->numeroVertici,sizeof(int));
    if(!aux)
    {
        printf("Errore di Allocazione\n");
    }
    else
    {
        for(i = 0; i < G->numeroVertici; i++)
        {
            if(!aux[i])
            {
                printf("\n%d,",i);
                dfs1(G,i,aux);
            }
        }
        free(aux);
    }
}


void dfs1(struct grafo *G, int i, int *aux)
{
    struct arco *e;
    aux[i] = 1;
    for(e = G->adiacente[i]; e; e = e->next)
        if(!aux[e->key])
        {
            printf("%d,",e->key);
            dfs1(G,e->key,aux);
        }
}
