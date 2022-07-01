struct viaggio{
    int numCitta;
    struct tratta **adiacente;
};

struct tratta{
    int citta;
    int prezzoViaggio;
    int kmViaggio;
    struct tratta *next;
};


struct viaggio *creaGrafoViaggio(int n);
void aggiungiTrattaViaggio(struct viaggio *G, int u, int v);
int grafoVuoto(struct viaggio *G);
void stampaGrafoViaggio(struct viaggio *G);

char **leggiFileViaggioCitta(FILE *fp, int numCitta);
int contaNodi(FILE *fp);
