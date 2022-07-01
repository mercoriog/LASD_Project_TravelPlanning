void Avanti(struct citta *G, int i, int arr, int *min, int parz)
{
    struct tragitto *tmp;
    if(i == arr){
        if(parz < *min) *min = parz;
        printf("\nValore minimo trovato %d\n", *min);
        return;
    }
    if(!G->adiacente[i]) printf("\nNon posso andare ad altri nodi\n");
    for(tmp = G->adiacente[i]; tmp; tmp = tmp->next)
        if(tmp->distanza + parz < *min)
        {
            printf("\n accedo a %d ->\n",tmp->luogo);
            Avanti(G,tmp->luogo,arr, min, parz + tmp->distanza);
        }else printf("\n dal nodo %d non vado a %d perche costo troppo\n", i, tmp->luogo);
}

void TrovaPercorso(struct citta *G, int part, int arr)
{
    int min = 1000;
    struct tragitto *tmp;

    for(tmp = G->adiacente[part]; tmp; tmp = tmp->next){
        printf(" da %d visito %d >\n", part, tmp->luogo);

        Avanti(G, tmp->luogo,arr, &min, tmp->distanza);

        printf("\n\n");
    }
    printf("\n>il percorso minimo costa %d\n", min);
}