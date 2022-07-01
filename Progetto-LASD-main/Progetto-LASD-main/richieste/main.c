#include "richieste.h"
#include <stdlib.h>
#include <stdio.h>

int main() {
    struct richiesta *listarichieste = NULL;
    listarichieste = leggiFileRichieste(listarichieste);
    int i, src, dest;

    stampaRichieste(listarichieste);
    printf("\n");
    stampaRichieste(listarichieste);

    puts("inserisci src");
    scanf("%d", &src);
    puts("inserisci dest");
    scanf("%d", &dest);
    i = ricerca(listarichieste, src, dest);
    if(i == 0)
        listarichieste = inserimento(listarichieste, src, dest);

    scriviFileRichieste(listarichieste);
    svuotaListaRichieste(listarichieste);
    return 0;
}
