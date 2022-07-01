void RimuoviTragitto(struct citta *G, int part, int arr){
    struct tragitto *curr = NULL, *prev = NULL;
    curr = G->adiacente[part];

    if(curr==NULL) return;
        //printf("Non ci sono tragitti\n");
    else if(curr->luogo == arr){
        G->adiacente[part] = curr->next;
        free(curr);
    }
    else{
        while(curr->luogo != arr && curr->next!=NULL){
            prev = curr;
            curr = curr->next;
        }

        if(curr->luogo == arr){
            prev->next = curr->next;
            free(curr);
        }
        //else printf("Il tragitto da rimuovere non era presente\n");
    }
}

int EsisteTragitto(struct citta *G, int part, int arr){
    struct tragitto *curr = NULL;

    curr = G->adiacente[part];
    while(curr){
        if(curr->luogo == arr)
            return 1;
        else
            curr = curr->next;
    }
    return 0;
}

void EliminaGrafo(struct citta *G){
    int i;
    struct tragitto *tmp=NULL, *tmpnext = NULL;
    if(G!= NULL){
        if(G->nL > 0) {
            for(i=0; i<G->nL; i++){
                tmp = G->adiacente[i];
                while(tmp!=NULL){
                    tmpnext = tmp->next;
                    free(tmp);
                    tmp = tmpnext;
                }
            }
            free(G->adiacente);
        }
        free(G);
        G = NULL;
    }
}

struct tragitto *SvuotaTragitti(struct tragitto *L){
    if(L){
        if(L->next) L->next = SvuotaTragitti(L->next);
        free(L);
    }
    return NULL;
}

void EliminaBidirezione(struct citta *G, int cittaVittima){
    struct tragitto *tmp = NULL;
    int i;
    for(i = 0; i<G->nL; i++){
        if(EsisteTragitto(G, i, cittaVittima) == 1)
            RimuoviTragitto(G, i, cittaVittima);
    }
}

struct citta *RimuoviNodo(struct citta *G, int cittaVittima) {
    struct tragitto *tmp= NULL;
    struct citta *nuovoGrafo=NULL;
    int i, j;

    EliminaBidirezione(G, cittaVittima);
    G->adiacente[cittaVittima] = SvuotaTragitti(G->adiacente[cittaVittima]);

    StampaCitta(G);

    nuovoGrafo = CreaGrafo(G->nL - 1);
    i = 0;
    j = 0;
    while(i < G->nL){
        if (i == cittaVittima) i++;
        else {
            for(tmp = G->adiacente[i]; tmp; tmp = tmp->next){
                if(tmp->luogo > cittaVittima)   aggiungiArco(nuovoGrafo, j, tmp->luogo-1, tmp->distanza);
                else
                    aggiungiArco(nuovoGrafo, j, tmp->luogo, tmp->distanza);
            }
            i++;
            j++;
        }
    }
    EliminaGrafo(G);
    StampaCitta(nuovoGrafo);
    return nuovoGrafo;
}

char **UpdateVetLuoghi(char **vLuoghiOld, int cittaVittima, int nMax) {
    int i = 0, j = 0;
    int nLuoghi = nMax -1;
    char **vetLuoghi=NULL;

    vetLuoghi=(char **)malloc(nLuoghi*sizeof(char*));

    for (i=0; i<nLuoghi; i++) {
        vetLuoghi[i]=(char *)malloc(10*sizeof(char));
    }

    i = 0;
    while(i<nMax){
        if(i == cittaVittima)  i++;
        else{
            strcpy(vetLuoghi[j], vLuoghiOld[i]);
            i++;
            j++;
        }
    }

    return vetLuoghi;
}
