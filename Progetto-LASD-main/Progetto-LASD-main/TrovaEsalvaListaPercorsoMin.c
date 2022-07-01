struct nodo{
    int val;
    struct nodo *next;
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


void Avanti(struct citta *G, int i, int arr, int *min, int parz, struct nodo *P, struct nodo **Pmin)
{
    struct tragitto *tmp;
    struct nodo *clone = NULL;

    if(i == arr){
        if(parz < *min){
            *min = parz;
            clone = Clone(P);
            *Pmin = clone;
        }
        //printf("\nValore minimo trovato %d\n", *min);
    }

   /* else if(!G->adiacente[i]){
        printf("\nNon posso andare ad altri nodi\n");
    }*/

    else{
        for(tmp = G->adiacente[i]; tmp; tmp = tmp->next)
            if(tmp->distanza + parz < *min)
            {
               // printf("\n accedo a %d ->\n",tmp->luogo);

                P = Push(P, tmp->luogo);
                clone = Clone(P);

                Avanti(G,tmp->luogo,arr, min, parz + tmp->distanza, clone, Pmin);

                clone = NULL;
                P = Pop(P);
            }   //else printf("\n dal nodo %d non vado a %d perche costo troppo\n", i, tmp->luogo);

    }
    //printf("uscito dal'if");
    P = Delete(P);
  //  if(P == NULL)   printf("\n>Delete<\n");
}

struct nodo* TrovaPercorso(struct citta *G, int part, int arr)
{
    struct nodo *P = NULL, *Pmin = NULL, *clone = NULL;
    int min = INT_MAX;
    struct tragitto *tmp;

    P = Push(P, part);
    for(tmp = G->adiacente[part]; tmp; tmp = tmp->next){
       // printf(" da %d visito %d >\n", part, tmp->luogo);

        P = Push(P, tmp->luogo);
        clone = Clone(P);

        Avanti(G, tmp->luogo,arr, &min, tmp->distanza, clone, &Pmin);

        //printf("Uscito");
        clone = NULL;
        P = Pop(P);

        //printf("\n\n");
    }
    P = Pop(P);
    if(min != INT_MAX)    printf("\n>il percorso minimo costa %d\n", min);
    else printf("Impossibile raggiungere %d partendo da %d\n", arr, part);

    return Pmin;
}
