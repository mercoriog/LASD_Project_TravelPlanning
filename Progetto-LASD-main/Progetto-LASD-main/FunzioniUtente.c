
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Strutture.h"


//Questa funzione verifica se l'ABR è vuoto.
int vuotoUtente(struct utente *radice)
{
    if(radice)
        return 0;
    else
        return 1;
}


//Questa funzione serve ad inserire un nuovo utente nell'ABR treeClient o treeAdmin.
struct utente *inserimentoUtente(struct utente *radice, char *nome, char *pass)
{
    struct utente *nuovoNodo;
    if (vuotoUtente(radice))
    {
        nuovoNodo=(struct utente*)malloc(sizeof(struct utente));
        if(nuovoNodo)
        {
            strcpy(nuovoNodo->nomeUtente,nome);
            strcpy(nuovoNodo->password,pass);
            nuovoNodo->sinistro=NULL;
            nuovoNodo->destro=NULL;
            radice=nuovoNodo;
        }
        else
        {
            printf("Errore...\nMemoria non allocata...\n\n");
        }
    }
    else if((strcmp(nome, radice->nomeUtente))<=0)
        radice->sinistro = inserimentoUtente(radice->sinistro, nome, pass);
    else if((strcmp(nome, radice->nomeUtente))>=0)
        radice->destro = inserimentoUtente(radice->destro, nome, pass);
    return radice;
}


//Questa funzione legge i file LogAdmin o LogClient e crea un albero contenente i dati letti.
struct utente *leggiFileLog(struct utente *radice, FILE *fp)
{
    char nome[LENGTH_NOME_UTENTE];
    char pass[LENGTH_PASSWORD];
    if(fp==NULL)
        gestisci_errori(2);
    while((fscanf(fp,"%s %s",nome, pass))==2)
    {
        radice=inserimentoUtente(radice,nome,pass);
    }
    return radice;
}


//Questa funzione ritorna 1 se il nome utente è già presente nell'albero, 0 altrimenti.
int unicitàNomeUtente(struct utente *radice, char *nomeDaCercare)
{
    int trovato=0;
    if (!(vuotoUtente (radice)))
    {
        if((strcmp(nomeDaCercare, radice->nomeUtente))==0)
            return 1;
        else if((strcmp(nomeDaCercare, radice->nomeUtente))<=0)
            trovato=unicitàNomeUtente(radice->sinistro,nomeDaCercare);
        else
            trovato=unicitàNomeUtente(radice->destro,nomeDaCercare);
    }
    return trovato;
}


//Questa funzione scrive sul file LogClient gli utenti che si sono registrati.
void updateFileLogClient(FILE *fp, char *nome, char *pass)
{
    if(fp==NULL)
        gestisci_errori(2);
    fprintf(fp,"\n%s %s",nome,pass);
}


//Questa funzione cerca in un ABR l'utente che vuole effettuare il login.
//Restituendo 0 se non è stato trovato, 1 se è stato trovato, 3 se il nome utente è corretto ma la password no.
int ricercaTreeUtente(struct utente *radice, char *nomeDaCercare, char *passDaCercare)
{
    int trovato=0;
    if (!(vuotoUtente (radice)))
    {
        if((strcmp(nomeDaCercare, radice->nomeUtente))==0)
        {
            trovato=3;
            if((strcmp(passDaCercare, radice->password))==0)
                return 1;
        }
        else if((strcmp(nomeDaCercare, radice->nomeUtente))<=0)
            trovato=ricercaTreeUtente(radice->sinistro,nomeDaCercare,passDaCercare);
        else
            trovato=ricercaTreeUtente(radice->destro,nomeDaCercare,passDaCercare);
    }
    return trovato;
}


//Questa funzione cerca in un ABR l'utente che vuole effettuare il login.
//Restituendo 0 se non è stato trovato, 1 se è stato trovato, 3 se il nome utente è corretto ma la password no.
int ricercaTreeCliente(struct utente *radice, char *nomeDaCercare)
{
    int trovato=0;
    if (!(vuotoUtente (radice)))
    {
        if((strcmp(nomeDaCercare, radice->nomeUtente))==0)
        {
                return 1;
        }
        else if((strcmp(nomeDaCercare, radice->nomeUtente))<=0)
            trovato=ricercaTreeCliente(radice->sinistro,nomeDaCercare);
        else
            trovato=ricercaTreeCliente(radice->destro,nomeDaCercare);
    }
    return trovato;
}


//Questa funzione stampa a video il nome utente di ogni singolo cliente registrato alla piattaforma.
void visitaInOrdineUtente(struct utente *radice)
{
    if(radice)
    {
        visitaInOrdineUtente(radice->sinistro);
        printf("%s\n",radice->nomeUtente);
        visitaInOrdineUtente(radice->destro);
    }
}


//Questa funzione elimina il nodo dell'utente desiderato dall'albero treeClient.
struct utente *cancellaUtente(struct utente *radice, char *nomeUtente)
{
    if (radice==NULL)
        return NULL;
    if((strcmp(nomeUtente, radice->nomeUtente))==0)
    {
        radice=cancellaNodo(radice);
    }
    else if((strcmp(nomeUtente, radice->nomeUtente))<=0)
        radice->sinistro=cancellaUtente(radice->sinistro,nomeUtente);
    else
        radice->destro=cancellaUtente(radice->destro,nomeUtente);
    return radice;
}


//Questa funzione prende in input la radice che si desidera eliminare e restituisce la nuova radice.
struct utente *cancellaNodo(struct utente *radice)
{
    struct utente *min=NULL;
    struct utente *nuovoNodo=NULL;
    if (radice==NULL)
        return NULL;
    if (radice->destro!=NULL && radice->sinistro!=NULL)
    {
        //Qusta funzione ritorna il nodo minimo del sottoalbero destro di radice.
        min=cancellaMinimo(radice, radice->destro);
        //Trasferiamo le informazioni dal minimo del sottoalbero destro al nodo che si desidera eliminare.
        strcpy(radice->nomeUtente, min->nomeUtente);
        strcpy(radice->password, min->password);
        //Eliminiamo il nodo minimo del sottoalbero destro.
        free(min);
        min=NULL;
        return radice;
    }
    
    if (radice->sinistro==NULL)
        nuovoNodo=radice->destro;
    else
        nuovoNodo=radice->sinistro;
    
    free(radice);
    radice=NULL;
    
    return nuovoNodo;
}


//Questa funzione cerca il minimo del sotto albero destro della radice in questione, ritornanrdo un puntatore ad esso.
struct utente *cancellaMinimo(struct utente *radice, struct utente *nodo)
{
    if (radice==NULL || nodo==NULL)
        return NULL;
    
    if (nodo->sinistro!=NULL)
        return cancellaMinimo(nodo, nodo->sinistro);
    
    if (nodo==radice->sinistro)
        radice->sinistro=nodo->destro;
    else
        radice->destro=nodo->destro;
    
    return nodo;
}


//Questa funzione aggiorna il file LogClient con i valori aggiornati presenti in treeClient.
void updateFileLogClientAfterDelete(struct utente *radice, FILE *fp)
{
    if(fp==NULL)
        gestisci_errori(2);
    if (radice)
    {
        updateFileLogClientAfterDelete(radice->sinistro,fp);
        fprintf(fp,"%s %s\n",radice->nomeUtente,radice->password);
        updateFileLogClientAfterDelete(radice->destro,fp);
    }
}


//Deallochiamo l'albero treeClient o treeAdmin.
void deallocazioneUtente(struct utente *radice)
{
    if(radice)
    {
        if (radice->sinistro)
            deallocazioneUtente(radice->sinistro);
        if (radice->destro)
            deallocazioneUtente(radice->destro);
        free(radice);
    }
}
