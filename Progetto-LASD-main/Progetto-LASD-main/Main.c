#include <stdio.h>
#include <stdlib.h>
#include "Strutture.h"
#include <string.h>


int main()
{
    int sceltaAccesso;
    int verificaAccesso=0;
    int verificaUnicitàNomeUtente;
    int sceltaOpClient;
    int sceltaOpAdmin;
    int ripetizioneInterfacciaClient=0;
    int ripetizioneInterfacciaAdmin=0;
    
    FILE *fp=NULL;
    
    char nomeUtenteLive[LENGTH_NOME_UTENTE];
    char passwordLive[LENGTH_PASSWORD];
    
    struct utente *treeAdmin=NULL;
    struct utente *treeClient=NULL;
    
    //Carichiamo nel programma le informazioni necessarie nelle varie strutture dati.

    fp=fopen("AdminLog.txt","r");
    treeAdmin=leggiFileLog(treeAdmin, fp);
    fclose(fp);
    
    fp=fopen("ClientLog.txt","r");
    treeClient=leggiFileLog(treeClient, fp);
    fclose(fp);

    //Scegliamo in che modo Accedere.
    sceltaAccesso=sceltaLogin();
    printf("\n");
    
    //Entro in questo if se ho scelto di registrarmi.
    if(sceltaAccesso==3)
    {
        do{
            printf("Benvenuto/a, Inserisci un nome utente e una password.\n");
            printf("Nome utente: ");
            scanf("%s",nomeUtenteLive);
            printf("Password: ");
            scanf("%s",passwordLive);
            
            //Verifichiamo se il nome utente inserito non sia stato già preso da un altro cliente.
            verificaUnicitàNomeUtente=unicitàNomeUtente(treeClient, nomeUtenteLive);
            
            if(verificaUnicitàNomeUtente==1)
                printf("Mi dispiace, nome utente già utilizzato...Riprova.\n\n");
            else
            {
                //Inseriamo in treeClient il nuovo utente.
                treeClient=inserimentoUtente(treeClient, nomeUtenteLive, passwordLive);
                
                //Aggiorniamo il file ClientLog con le credenziali del nuovo cliente.
                fp=fopen("ClientLog.txt","a");
                updateFileLogClient(fp,nomeUtenteLive,passwordLive);
                fclose(fp);
            }
        }while(verificaUnicitàNomeUtente==1);   //Usciremo da questo While quando inseriremo un nome utente univoco.
    }
    //Entriamo in questo else se ho scelto di accedere come Admin o come Client.
    else
    {
        do{
            printf("Inserire Nome Utente e Password per effettuare il login:\n");
            printf("Nome Utente: ");
            scanf("%s",nomeUtenteLive);
            printf("Password: ");
            scanf("%s",passwordLive);
            
            //Verifichiamo se l'accesso è stato richiesto da un Admin o da un Client.
            //Questa informazione sarà utile per capire se effettuare la ricerca delle credenziali in treeClient o treeAdmin.
            if(sceltaAccesso==1)
                verificaAccesso=ricercaTreeUtente(treeAdmin, nomeUtenteLive, passwordLive);
            else
                verificaAccesso=ricercaTreeUtente(treeClient, nomeUtenteLive, passwordLive);
            
            //Se entriamo in questi due casi vuol dire che nome utente o password sono errati.
            if(verificaAccesso==0)
                printf("Nome Utente e Password Errati.\n\n");
            else if(verificaAccesso==3)
                printf("Password Errata.\n\n");
            
        }while(verificaAccesso==0 || verificaAccesso==3);
    }

    
    //Se entriamo in questo if vuol dire che siamo dei clienti, e possiamo effettuare solo determinate operazioni.
    if(sceltaAccesso==2 || sceltaAccesso==3)
    {
        do{
            ripetizioneInterfacciaClient=0;             //Variabile di controllo per gestire il menù.
            sceltaOpClient=sceltaOperazioneClient();    //Scegliamo che operazione effettuare.
            printf("\n");
        }while(ripetizioneInterfacciaClient!=0);
    }

    //Se entriamo in questo else vuol dire che siamo degli Admin, e possiamo effettuare solo determinate operazioni.
    else
    {
        do{
            ripetizioneInterfacciaAdmin=0;              //Variabile di controllo per gestire il menù.
            printf("\n");
            sceltaOpAdmin=sceltaOperazioneAdmin();      //Scegliamo che operazione effettuare.
            printf("\n");
          
        }while(ripetizioneInterfacciaAdmin!=0);
    }
    

    //Deallochiamo tutte le strutture prima di chiudere il programma.
  
    deallocazioneUtente(treeClient);
    treeClient=NULL;
    

    deallocazioneUtente(treeAdmin);
    treeAdmin=NULL;

    return 0;
}

