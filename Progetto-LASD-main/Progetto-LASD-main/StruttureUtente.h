#define LENGTH_NOME_UTENTE 30
#define LENGTH_PASSWORD 30

struct utente{
    char nomeUtente[LENGTH_NOME_UTENTE];
    char password[LENGTH_PASSWORD];
    struct utente *destro;
    struct utente *sinistro;
};


void gestisci_errori(int x);
int sceltaLogin(void);
int sceltaOperazioneClient(void);
int sceltaOperazioneAdmin(void);



int vuotoUtente(struct utente *radice);
struct utente *inserimentoUtente(struct utente *radice, char *nome, char *pass);
struct utente *leggiFileLog(struct utente *radice, FILE *fp);
int unicitàNomeUtente(struct utente *radice, char *nomeDaCercare);
void updateFileLogClient(FILE *fp, char *nome, char *pass);
int ricercaTreeUtente(struct utente *radice, char *nome_cercare, char *pass_cercare);
int ricercaTreeCliente(struct utente *radice, char *nomeDaCercare);
void visitaInOrdineUtente(struct utente *radice);
struct utente *cancellaUtente(struct utente *radice, char *nomeUtente);
struct utente *cancellaNodo(struct utente *radice);
struct utente *cancellaMinimo(struct utente *p, struct utente *t);
void updateFileLogClientAfterDelete(struct utente *radice, FILE *fp);
void deallocazioneUtente(struct utente *radice);
