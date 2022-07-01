#ifndef LASD_2_GG_PART_FUNZIONICITTA_H
#define LASD_2_GG_PART_FUNZIONICITTA_H

struct citta{
    int nL;
    struct tragitto **adiacente;
};

struct tragitto{
    int luogo;
    int distanza;
    struct tragitto *next;
};

struct nodo{
    int val;
    struct nodo* next;
};

struct citta *CreaGrafo(int n);
void aggiungiArco(struct citta *G, int part, int arrivo, int dist);
void StampaCittaNominata(struct citta *G, char **vLuoghi);
void StampaCitta(struct citta *G);
char **leggiFileCitta(FILE *fp, int nLuoghi);
int contaLuoghi(FILE *fp);
void CaricaCitta(FILE *fp, struct citta *gCitta);
struct citta* CreaGrafoCitta(char *filename);
void StampaPercorso(struct nodo *P);
void StampaPercorsoNominato(struct nodo *L, char **vLuoghi);
struct nodo* TrovaPercorso(struct citta *G, int part, int arr, int *min);
#endif //LASD_2_GG_PART_FUNZIONICITTA_H
