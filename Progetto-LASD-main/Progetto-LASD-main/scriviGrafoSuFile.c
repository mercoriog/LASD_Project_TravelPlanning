void ScriviFileCitta(char filename[], struct citta *G, char **vLuoghi){

    int i, contaTragitto=0;
    struct tragitto *tmp;
    FILE *fp = NULL;
    fp = fopen(filename, "w");

    if(!fp){
        printf("Errore nell apertura del file citta\n");
        return;
    }

    for (i=0; i<G->nL; i++){
        fprintf(fp, "%s ", vLuoghi[i]);
    }
    fprintf(fp, "@@\n");

    if(!cittaVuota(G))
    {
        for (i=0; i<G->nL; i++)
        {
            tmp =G->adiacente[i];
            while (tmp!=NULL)
            {
                fprintf(fp,"%d %d %d\n", i, tmp->luogo, tmp->distanza);
                contaTragitto=contaTragitto+1;
                tmp=tmp->next;
            }
        }
    }
    fclose(fp);
}
