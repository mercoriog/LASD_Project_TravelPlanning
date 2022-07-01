#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Strutture.h"


//Funzione utile a gestire i vari errori che possono sorgere nel programma.
void gestisci_errori(int x)
{
    if(x==1)
    {
        printf("Errore, memoria non allocata.\n");
        exit(-1);
    }
    else if(x==2)
    {
        printf("Errore, file non aperto correttamente.\n");
        exit(-1);
    }
}


//Menù per la scelta d'accesso.
int sceltaLogin(void)
{
    int sceltaAccesso=0;
    do
    {
        printf("Digitare:\n1-Per l'accesso Amministratore.\n2-Per l'accesso Cliente.\n3-Per registrarsi come nuovo Cliente.\n");
        scanf("%d",&sceltaAccesso);

        switch (sceltaAccesso) {
            case 1:
                return sceltaAccesso;
                break;
            case 2:
                return sceltaAccesso;
                break;
            case 3:
                return sceltaAccesso;
                break;
            default:
                printf("\nErrore...\nOperazione inesistente.\n\n");
                break;
        }
    }while(sceltaAccesso<1 || sceltaAccesso>3);
   
    return sceltaAccesso;
}


//Menù per la scelta delle operazioni che può effettuare un cliente.
int sceltaOperazioneClient(void)
{
    int sceltaOperazione=0;
    printf("\nBenvenuto/a, scegliere che operazione eseguire:\n");
    do
    {
        printf("Digitare:\n1-vuoto.\n2-vuoto.\n3-vuoto.\n4-vuoto.\n5-Per uscire.\n");
        scanf("%d",&sceltaOperazione);

        switch (sceltaOperazione) {
            case 1:
                return sceltaOperazione;
                break;
            case 2:
                return sceltaOperazione;
                break;
            case 3:
                return sceltaOperazione;
                break;
            case 4:
                return sceltaOperazione;
                break;
            case 5:
                return sceltaOperazione;
                break;
            default:
                printf("\nErrore...\nOperazione inesistente.\n\n");
                break;
        }
    }while(sceltaOperazione<1 || sceltaOperazione>5);
    
    return sceltaOperazione;
}


//Menù per la scelta delle operazioni che può effettuare un Admin.
int sceltaOperazioneAdmin(void)
{
    int sceltaOperazione=0;
    printf("Benvenuto/a, scegliere che operazione eseguire:\n");
    do
    {
        printf("Digitare:\n1-vuoto.\n2-vuoto.\n3-vuoto.\n4-vuoto.\n5-vuoto.\n6-Per uscire.\n");
        scanf("%d",&sceltaOperazione);

        switch (sceltaOperazione) {
            case 1:
                return sceltaOperazione;
                break;
            case 2:
                return sceltaOperazione;
                break;
            case 3:
                return sceltaOperazione;
                break;
            case 4:
                return sceltaOperazione;
                break;
            case 5:
                return sceltaOperazione;
                break;
            case 6:
                return sceltaOperazione;
                break;
            default:
                printf("\nErrore...\nOperazione inesistente.\n\n");
                break;
        }
    }while(sceltaOperazione<1 || sceltaOperazione>4);
    
    return sceltaOperazione;
}

