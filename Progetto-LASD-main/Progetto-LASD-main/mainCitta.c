#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "FunzioniCitta.h"


int main() {
    char **luoghiCitta;
    struct citta *grafoCitta;
    FILE *fp = NULL;
    char filename[10] = "Napoli";
    char fileExt[10] = ".txt";
    struct nodo *P = NULL;
    int min = INT_MAX;
    grafoCitta = CreaGrafoCitta("Napoli.txt");
    StampaCitta(grafoCitta);

    fp = fopen("Napoli.txt", "r");
    luoghiCitta = leggiFileCitta(fp, grafoCitta->nL);
    fclose(fp);

    StampaCittaNominata(grafoCitta, luoghiCitta);

    P = TrovaPercorso(grafoCitta, 0, 1, &min);
    if(min != INT_MAX)    printf("\n>il percorso minimo costa %d\n", min);
    else printf("Impossibile raggiungerlo");
    StampaPercorso(P);
    printf("\nOvvero\n");
    StampaPercorsoNominato(P, luoghiCitta);

    return 0;
}
