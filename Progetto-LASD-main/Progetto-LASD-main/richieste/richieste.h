#ifndef RICHIESTE_RICHIESTE_H
#define RICHIESTE_RICHIESTE_H

struct richiesta{
    int src;
    int dest;
    struct richiesta *link;
};

struct richiesta *creaRichiesta (int src, int dest);
struct richiesta *inserimento(struct richiesta *lista, int src, int dest);
struct richiesta *leggiFileRichieste(struct richiesta *lista);
void scriviFileRichieste(struct richiesta *lista);
void svuotaListaRichieste(struct richiesta *lista);
void stampaRichieste(struct richiesta *lista);
struct richiesta *rimuoviRichiesta(struct richiesta *lista, int src, int dest);
int ricerca(struct richiesta *lista, int src, int dest);
int counter(struct richiesta *lista);
struct richiesta *recuperaNodo(struct richiesta *lista, int index);

#endif //RICHIESTE_RICHIESTE_H
