#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include "gamelib.h"

void menu();     

unsigned short int set=0;
static int crea_impostori;     // variabile per creare gli impostori
static int impostori=0;         //variabile che indica il numero di impostori
static int astronauti=0;        //variabile che indica il numero di astronauti
static int imp[10];
static int numero_giocatori=0;  //variabile per conoscere il numero dei giocatori
static int scelta_imposta_gioco; //variabile per le impostazioni di gioco
static int uccidi;
static int mossa=0;             //variabile utilizzata per vedere se il giocatore ha già effettuato una mossa
static int presenti_in_stanza;
static int turno;
static int scel;
static unsigned short int numero_quest;    //variabile utilizzata per inserire il numero di quest
static unsigned short int quest_iniziali;  // variabile utilizzata per tenere il conto delle quest inziziali

static struct Giocatore* giocatori=NULL;
static struct Stanza* stanza_inizio=NULL;
static struct Stanza* lista_stanze=NULL;
static struct Stanza* stanza_botola=NULL;

static void stampa_giocatori();                  // Riga 54
static void stampa_stato();                      // Riga 62
static int tipo_stanza();                        // Riga 85
static void posizione_iniziale();                // Riga 102
static void crea_giocatori();                   // Riga 112
static void impost();                           // Riga 126
static void inizia_gioco();                     // Riga 229
static void esegui_quest();                     // Riga 317
static void chiamata_di_emergenza ();          // Riga 339
static void uccidi_astronauta();               // Riga 401
static void usa_botola();                     // Riga 443
static void sabotaggio();                     // Riga 496
static void inizializzare_nuove_stanze(struct Stanza *stanza_attuale, struct Stanza *stanza_prec);         // Riga 503
static void avanza();                         // Riga 512
static void giocatori_in_stanza();            // Riga 581

// servono per assegnare una stringa di testo ad un valore numerico
const char* nome[]={"\033[1;31m rosso", "\033[1;34m blu", "\033[0;30;47m nero", "\033[0;35m viola", "\033[1;33m giallo", "\033[0;36m ciano", "\033[0;35m rosa", "\033[1;32m verde", "\033[1;37m grigio", "\033[1;37m bianco"};
const char* numero[]={"primo", "secondo", "terzo", "quarto", "quinto", "sesto", "settimo", "ottavo", "nono", "decimo"};
const char* tipo[]={"vuota", "quest semplice", "quest complicata", "botola"};
const char* stato[]={"astronauta", "impostore", "assassinato", "defenestrato"};

//funzione utilizzata per stampare i giocatori
static void stampa_giocatori(){
  system("clear");
  for(int k=0;k<numero_giocatori;k++){
  printf("\033[0;0m   %s a giocare: %s\n",numero[k],nome[giocatori[k].nome]);
  printf("\033[0;0m");
}
}

//funzione utilizzata per stampare lo stato dei giocatori
static void stampa_stato(){
 getchar();
   system("clear");
    for(int u=0;u<numero_giocatori;u++){
      printf("\033[0;0m");
      while(u==0 || u != numero_giocatori)
      {
        if (u==7){printf("Premere invio per vedere lo stato dell' %s giocatore \n",numero[u] ); //serve per l'ottavo giocatore
        while(getchar()!='\n') ;}
      else {printf("Premere invio per vedere lo stato del %s giocatore \n",numero[u] );
      while(getchar()!='\n');}
      break;
    }
    system("clear");
    printf("\tIl giocatore %s ",nome[giocatori[u].nome]);
    printf("\033[0;0m");
    printf("è: %s\n", stato[giocatori[u].stato]);
    while(getchar()!='\n');
    system("clear");

  }
  }

//funzione utilizzata per assegnare il valore da 0 a 3 del tipo stanza
static int tipo_stanza(){
    int e = rand()%100;
    if(e<=25){
      e=3;
    }
    else if(e>=26 && e<=40){
      e=2;
    }
    else if(e>=41 && e<=70){
      e=1;
    }
    else if(e>=71 && e<=100){
      e=0;
    }
  return e;
  }

//funzione utilizzata per inizializzare la stanza di inizio
static void posizione_iniziale(){
  stanza_inizio=(struct Stanza *)malloc(sizeof(struct Stanza));
  stanza_inizio->stanza_precedente=NULL;
  stanza_inizio->avanti=NULL;
  stanza_inizio->sinistra=NULL;
  stanza_inizio->destra=NULL;
  stanza_inizio->info=tipo_stanza();
  stanza_inizio->emergenza_chiamata=false;
}

//funzione utilizzata per creare i giocatori
static void crea_giocatori(){
  giocatori=malloc(numero_giocatori* sizeof(struct Giocatore));
  srand((unsigned)time(NULL));
  for(int i=0;i<numero_giocatori;i++) {
     giocatori[i].nome=rand()%numero_giocatori;
    for(int j=0;j<i;j++) {
      if(giocatori[i].nome==giocatori[j].nome) {
        i--;
        break;
      }
    }
  }
}

//funzione utilizzata per assegnare  lo stato di astronauta o impostore ai giocatori
static void impost(){
  if(numero_giocatori>=4 && numero_giocatori<=6){
   crea_impostori=1;}

  if(numero_giocatori>=7 && numero_giocatori<=8){
   crea_impostori=2;}

  if (numero_giocatori>=9 && numero_giocatori<=10){
   crea_impostori=3;}


  switch (crea_impostori) {

   case 1:

   srand((unsigned)time(NULL));
   for(int i=0;i<numero_giocatori;i++) {
   imp[i] =rand()%numero_giocatori+1;
   for(int j=0;j<i;j++) {
            if(imp[i]==imp[j]) {
              i--;
              break;
           }
         }
   }

   for (int i=0;i<numero_giocatori;i++){
     if(imp[i]==2){
       giocatori[i].stato=1;
       impostori++;
     }
     else{
       giocatori[i].stato=0;
       astronauti++;
     }
   }
        break;


   case 2:

   srand((unsigned)time(NULL));
   for(int i=0;i<numero_giocatori;i++) {
   imp[i] =rand()%numero_giocatori+1;
   for(int j=0;j<i;j++) {
            if(imp[i]==imp[j]) {
              i--;
              break;
           }
         }
   }

   for (int i=0;i<numero_giocatori;i++){
     if(imp[i]==2){
       giocatori[i].stato=1;
       impostori++;
     }
     else if(imp[i]==5){
       giocatori[i].stato=1;
       impostori++;
     }
     else{
       giocatori[i].stato=0;
       astronauti++;
     }
   }
         break;

   case 3:
   srand((unsigned)time(NULL));
   for(int i=0;i<numero_giocatori;i++) {
   imp[i] =rand()%numero_giocatori+1;
   for(int j=0;j<i;j++) {
            if(imp[i]==imp[j]) {
              i--;
              break;
           }
         }
   }

   for (int i=0;i<numero_giocatori;i++){
     if(imp[i]==2){
       giocatori[i].stato=1;
       impostori++;
     }
     else if(imp[i]==5){
       giocatori[i].stato=1;
       impostori++;
     }
     else if(imp[i]==7){
       giocatori[i].stato=1;
       impostori++;
     }
     else{
       giocatori[i].stato=0;
       astronauti++;
     }
   }
      break;

  }
}

//funzione utilizzata per mettere tutti i giocatori nella stanza di inizio e per tornare al menu principale
static void inizia_gioco(){
  for (int i=0; i<=numero_giocatori; i++){
    giocatori[i].posizione=stanza_inizio;
  }
  system("clear");
  printf("Torno al menù principale...\n");
  sleep (1);
  menu();
  }

//funzione utilizzata per impostare il gioco
void imposta_gioco(){
  static int w = 0;
  system ("clear");
  printf("\n\n\n\t\t\t\t|                           IN QUESTA SEZIONE DEVI IMPOSTARE IL GIOCO                         |\n\n");
  printf("\t\t\t\t\t\t\t    Quanti sono i giocatori? (da 4 a 10) \n\t\t\t\t\t\t\t    |Da 4 a 6 giocatori ci sarà 1 impostore    |\n\t\t\t\t\t\t\t    |da 7 a 8 giocatori ci saranno 2 impostori |\n\t\t\t\t\t\t\t    |da 9 a 10 giocaotri ci saranno 3 impostori|\n ");

  do{
    printf("\n\t\t\t\t\t\t\t\t   Numero giocatori...");
    while(scanf("%u",&numero_giocatori) != 1 || numero_giocatori >10|| numero_giocatori <4){
      printf("\n\t\t\t\t\t\t\t     Il numero di giocatori non è compreso tra 4 e 10\n");
      printf("\n\t\t\t\t\t\t\t     Reinserisci il numero di giocatori...");
    }
    break;
  }while(numero_giocatori>10 || numero_giocatori<4);

crea_giocatori();

impost();

posizione_iniziale();

system("clear");

here: do{

printf("\n\n\n\t\t\t\t\t\t\t    1. Mostra i giocatori e specifica il loro turno;\n\t\t\t\t\t\t\t    2. Mostra i giocatori e il loro stato;\n\t\t\t\t\t\t\t    3. Stabilire il numero di quest da completare;\n\t\t\t\t\t\t\t    4. Torna al menù principale e inizia a giocare;\n\t\t\t\t\t\t\t    SCELTA...   ");
  while (scanf("%u",&scelta_imposta_gioco) != 1 || scelta_imposta_gioco >4|| scelta_imposta_gioco <1){
          printf("\n\t\t\t\t\t\t\t\t Il numero non è corretto;\n");
          printf("\n\t\t\t\t\t\t\t\t SCELTA...   ");
  }
  switch (scelta_imposta_gioco) {
    case 1:

    printf("\n");

  stampa_giocatori();

    printf("\n");
    break;

    case 2:
    printf("\n" );

  stampa_stato();

    printf("\n" );
    break;

    case 3:
    w = 1;
    set=1;
    do
  {
    printf("\n\t\t\t\t\t\t Inserire il numero di quest che gli astronauti dovranno completare per vincere \n\t\t\t\t\t\t (il numero di quest non può essere inferiore al numero di giocatori)...");
   scanf("%hu",&numero_quest);
   if(numero_quest<numero_giocatori || numero_quest<0){
     printf("\n\t\t\t\t\t\t\t    Il numero di quest inserito non è corretto\n");}
 } while(numero_quest<numero_giocatori || numero_quest<0);
 quest_iniziali=numero_quest;
 system("clear");
    break;

    case 4:
    if(w==0){
      system("clear");
      printf("\n\n\t\t\t\t\t\t\t    Devi prima impostare il numero di quest da completare!\n");
      sleep(2);
      system("clear");
      goto here;
    }
    else{
      inizia_gioco();
    }
    break;
  }
}while(scelta_imposta_gioco !=4);
}

//funzione utilizzata per eseguire le quest
static void esegui_quest(){
  mossa=1;
  static int quest_eseguite;
  if (giocatori[turno].posizione->info==1){
    numero_quest=numero_quest-1;   //vengono scalate le quest da completare
    giocatori[turno].posizione->info=0; //la stanza diventa vuota
    quest_eseguite=quest_iniziali-numero_quest;
    printf("\t\t\t\t\t\t\t    Hai completato la quest semplice (%d/%d)\n", quest_eseguite, quest_iniziali);
    while(getchar()!='\n') ;
    while(getchar()!='\n') ;
  }
  if (giocatori[turno].posizione->info==2)
  {
    numero_quest=numero_quest-2;  //vengono scalate di due le quest da completare
    giocatori[turno].posizione->info=0; //la stanza diventa vuota
    quest_eseguite=quest_iniziali-numero_quest;
    printf("\t\t\t\t\t\t\t    Hai completato la quest complicata (%d/%d)\n", quest_eseguite, quest_iniziali);
    while(getchar()!='\n') ;
    while(getchar()!='\n') ;
  }
}

//funzione utilizzata per fare la chiamata di emergenza
static void chiamata_di_emergenza (){
 int astronauti_in_stanza=0, impostori_in_stanza=0, pAst, pImp, l;
 bool r=false;

for(presenti_in_stanza=0;presenti_in_stanza<numero_giocatori;presenti_in_stanza++){
  if(giocatori[turno].posizione==giocatori[presenti_in_stanza].posizione && turno!=presenti_in_stanza){
   if (giocatori[presenti_in_stanza].stato==0){
     astronauti_in_stanza++;  //conta quanti astronauti ci sono in stanza
   }

   if (giocatori[presenti_in_stanza].stato==1){
     impostori_in_stanza++;  //conta quanti impostori ci sono in stanza
   }
 }
}
   pAst=30+(impostori_in_stanza*20)-(astronauti_in_stanza*30);   // probabilità di defenestrare un astronauta
   pImp=30+(astronauti_in_stanza*20)-(impostori_in_stanza*30);   // probabilità di defenestrare un impostore
   l=rand()%100+1;

for(presenti_in_stanza=0;presenti_in_stanza<numero_giocatori;presenti_in_stanza++){
   if(giocatori[turno].posizione==giocatori[presenti_in_stanza].posizione){
   if (giocatori[presenti_in_stanza].stato==0 && r==false) {
     if(l<=pAst){
     giocatori[presenti_in_stanza].stato=3;
     printf("\n Il giocatore %s \033[0;0mera un astronauta ed è stato defenestrato \n", nome[giocatori[presenti_in_stanza].nome]);
     r=true;
     mossa=1;
     giocatori[turno].posizione->emergenza_chiamata=true;
     while(getchar()!='\n') ;
     while(getchar()!='\n') ;
     break;
   }


   if (giocatori[presenti_in_stanza].stato==1 && r==false) {
     if(l<=pImp){
     giocatori[presenti_in_stanza].stato=3;
     printf("\n Il giocatore %s \033[0;0mera un impostore ed è stato defenestrato \n", nome[giocatori[presenti_in_stanza].nome]);
     r=true;
     mossa=1;
     giocatori[turno].posizione->emergenza_chiamata=true;
     while(getchar()!='\n') ;
     while(getchar()!='\n') ;
    break;
    }
   }

   if (r==false){
   printf("Nessun giocatore è stato defenestrarto\n");
   mossa=1;
   giocatori[turno].posizione->emergenza_chiamata=true;
   while(getchar()!='\n') ;
   while(getchar()!='\n') ;
   break;
 }
  }
 }
}
}

//funzione utilizzata per uccidere gli astronauti
static void uccidi_astronauta(){

  static int kill=0;
  static int probabilita_defenestraggio;
  static int defenestrato;

  if(kill==0){
    printf("Hai ucciso il giocatore: %s\033[0;0m\n",nome[giocatori[presenti_in_stanza].nome]);
    astronauti--;
    giocatori[presenti_in_stanza].stato=2;  //viene cambiato lo stato del giocatore e decrematati gli astronauti
    kill=1;
    while(getchar()!='\n') ;
    while(getchar()!='\n') ;

  }

  if(kill==1){  //viene calcolata la probabilità di defenestraggio degli impostori
    probabilita_defenestraggio=0;
    for(presenti_in_stanza=0;presenti_in_stanza<numero_giocatori;presenti_in_stanza++){
      if(presenti_in_stanza!=turno && giocatori[presenti_in_stanza].stato==0){
        if (giocatori[turno].posizione==giocatori[presenti_in_stanza].posizione){
          probabilita_defenestraggio+=50;
        }
        else if (giocatori[turno].posizione->stanza_precedente==giocatori[presenti_in_stanza].posizione){
          probabilita_defenestraggio+=20;
        }
      }
    }
    defenestrato=rand()%100+1;
    if(defenestrato>0 && defenestrato<=probabilita_defenestraggio){
      printf("Sei stato scoperto!\n");
      impostori--;
      giocatori[turno].stato=3;
      while(getchar()!='\n') ;
    }
    else{
      printf("Non sei stato scoperto!\n");
      while(getchar()!='\n') ;
    }
  }
}

//funzione utilizzata per le botole
static void usa_botola() {

 static int numero_stanze=0;
 static int numero_botole=0;
 stanza_botola=lista_stanze;
 static int i;

if (stanza_inizio->stanza_successiva==NULL){
  printf("Nella prima stanza non può essere utilizzata la botola\n");
  while(getchar()!='\n') ;
  while(getchar()!='\n') ;
}

 while (stanza_botola!=NULL){ //vengono contate il numero di stanze e di botole totali
   if (stanza_botola->info==3 && stanza_botola!=giocatori[turno].posizione){
     numero_botole++;
   }
   numero_stanze++;
   stanza_botola=stanza_botola->stanza_successiva;
 }

struct Stanza* botola[numero_botole];
 stanza_botola=lista_stanze;

 while(stanza_botola!=NULL){
   if(stanza_botola->info==3 && stanza_botola!=giocatori[turno].posizione){
     botola[i]=stanza_botola;
     i++;
   }
   stanza_botola=stanza_botola->stanza_successiva;
 }

 if(numero_botole>1){ // viene assegnata al giocatore una stanza con botola
   printf("Ci sono %d stanze con botola, ora verrai portato in una stanza con botola casualmente\n", numero_botole);
   int e=rand()%numero_botole;
   for(int i=0;i<numero_botole;i++){
     if (i==e){
       giocatori[turno].posizione=botola[i];
       printf("Ti sei spostato in una stanza con la botola\n");
     }
   }
 }

 else if (numero_botole==1 && numero_stanze>1){// viene assegnata al giocatore una stanza casuale
   int e=rand()%numero_stanze;
   for(int i=0;i<numero_stanze;i++){
     if (i==e){
       giocatori[turno].posizione=lista_stanze;
       printf("Ti sei spostato in una stanza di tipo: %s\n",tipo[giocatori[turno].posizione->info]);
     }
   }
 }
}

//funzione utilizzata per sabotare le quest
static void sabotaggio(){
  giocatori[turno].posizione->info=0; //la stanza diventa vuota
  printf("La quest è stata sabotata con successo\n");
  while(getchar()!='\n') ;
  while(getchar()!='\n') ;
}

//funzione utilizzata per inizializzare i puntatori delle nuove stanze
static void inizializzare_nuove_stanze(struct Stanza *stanza_attuale, struct Stanza *stanza_prec){
  stanza_attuale->avanti=NULL;
  stanza_attuale->sinistra=NULL;
  stanza_attuale->destra=NULL;
  stanza_attuale->stanza_precedente=stanza_prec;
  stanza_attuale->info=tipo_stanza();
  stanza_attuale->emergenza_chiamata=false;
}

//funzione utilizzata per avanzare nelle stanze o crearne di nuove
static void avanza(){
  static int movimento;
  do{
    printf("\nScegliere una direzione:\n1. Avanti;\n2. Destra;\n3. Sinistra\n4. Resta fermo\nSCELTA...  ");
    scanf("%d",&movimento);
      switch (movimento) {
      case 1:
      lista_stanze=giocatori[turno].posizione;
      if(lista_stanze->avanti==NULL){ // se la stanza ha puntatore a NULL allora ne viene creata una nuova
        lista_stanze->avanti=(struct Stanza*) malloc(sizeof(struct Stanza));
        inizializzare_nuove_stanze(lista_stanze->avanti, lista_stanze);
        printf("Ti sei spostato in una stanza di tipo: %s\n", tipo[tipo_stanza()]);
        giocatori[turno].posizione=lista_stanze->avanti;
      }
      else{ // se la stanza esiste già il giocatore viene spostato in quella stanza
        giocatori[turno].posizione=lista_stanze->avanti;
        printf("Ti sei spostato in una stanza di tipo: %s\n", tipo[lista_stanze->avanti->info]);
      }
      while(getchar()!='\n') ;
      while(getchar()!='\n') ;
      mossa=1;
      break;

      case 2:
      lista_stanze=giocatori[turno].posizione;
      if(lista_stanze->destra==NULL){
        lista_stanze->destra=(struct Stanza*) malloc(sizeof(struct Stanza));
        inizializzare_nuove_stanze(lista_stanze->destra, lista_stanze);
        printf("Ti sei spostato in una stanza di tipo: %s\n", tipo[tipo_stanza()]);
        giocatori[turno].posizione=lista_stanze->destra;
      }
      else{
        giocatori[turno].posizione=lista_stanze->destra;
        printf("Ti sei spostato in una stanza di tipo: %s\n", tipo[lista_stanze->destra->info]);
      }
      while(getchar()!='\n') ;
      while(getchar()!='\n') ;
      mossa=1;
      break;

      case 3:
      lista_stanze=giocatori[turno].posizione;
      if(lista_stanze->sinistra==NULL){
        lista_stanze->sinistra=(struct Stanza*) malloc(sizeof(struct Stanza));
        inizializzare_nuove_stanze(lista_stanze->sinistra, lista_stanze);
        printf("Ti sei spostato in una stanza di tipo: %s\n", tipo[tipo_stanza()]);
        giocatori[turno].posizione=lista_stanze->sinistra;
      }
      else{
        giocatori[turno].posizione=lista_stanze->sinistra;
        printf("Ti sei spostato in una stanza di tipo: %s\n", tipo[lista_stanze->sinistra->info]);
      }
      while(getchar()!='\n') ;
      while(getchar()!='\n') ;
      mossa=1;
      break;

      case 4:
      printf("Sei rimasto fermo in questa stanza\n");
      while(getchar()!='\n') ;
      while(getchar()!='\n') ;
      mossa=1;
      break;

    }
  }while(movimento<1||movimento>4);

}

//funzione utilizzata per controllare i giocatori nella stanza e il loro stato
static void giocatori_in_stanza(){
  static int call;
  for(presenti_in_stanza=0; presenti_in_stanza<numero_giocatori; presenti_in_stanza++){
    if (presenti_in_stanza!=turno){
      if(giocatori[turno].posizione==giocatori[presenti_in_stanza].posizione){  //vengono controllati i giocatori che si trovano nella stessa stanza del giocatore di cui è il turno
      if (giocatori[presenti_in_stanza].stato!=3 && giocatori[presenti_in_stanza].stato!=2){
        printf("In questa stanza si trova anche il giocatore:%s\033[0;0m\n",nome[giocatori[presenti_in_stanza].nome]);
      }
    }
  }
}
for(presenti_in_stanza=0; presenti_in_stanza<numero_giocatori; presenti_in_stanza++){
  if (presenti_in_stanza!=turno){
    if(giocatori[turno].posizione==giocatori[presenti_in_stanza].posizione){
       if (giocatori[presenti_in_stanza].stato==2){ //vengono controllati i giocatori che si trovano nella stessa stanza del giocatore di cui è il turno se sono stati uccisi
         if (giocatori[turno].posizione->emergenza_chiamata==false){
         printf("\nIn questa stanza è stato ucciso il giocatore: %s \033[0;0m \nVuoi fare una chiamata d'emergenza?\n1. SI\n2. NO\n", nome[giocatori[presenti_in_stanza].nome]);
         scanf("%d",&call);
         switch (call){

           case 1:
           chiamata_di_emergenza();
           break;

           case 2:
           mossa=0;
           break;
         }
       }
       else {
        printf("\nIn questa stanza è stato ucciso il giocatore: %s \033[0;0m ma la chiamata di mergenza è già stata utilizzata\n", nome[giocatori[presenti_in_stanza].nome]);
        }
       }
     }
   }
 }
 for(presenti_in_stanza=0; presenti_in_stanza<numero_giocatori; presenti_in_stanza++){
   if (presenti_in_stanza!=turno){
     if(giocatori[turno].posizione==giocatori[presenti_in_stanza].posizione){
       if (giocatori[presenti_in_stanza].stato==3){ //vengono controllati i giocatori che si trovano nella stessa stanza del giocatore di cui è il turno se sono stati defenestrati
         printf("In questa stanza è stato defenestrato il giocatore: %s\033[0;0m\n", nome[giocatori[presenti_in_stanza].nome]);
       }
     }
   }
  }
  for(presenti_in_stanza=0; presenti_in_stanza<numero_giocatori; presenti_in_stanza++){
  if (presenti_in_stanza!=turno){
  if (giocatori[turno].stato==1 && giocatori[presenti_in_stanza].stato==0 && giocatori[turno].posizione==giocatori[presenti_in_stanza].posizione){ // se il giocatore è impostore e nella stanza ci sono astronauti gli viene chiesto se vuole ucciderne uno
    printf("Vuoi uccidere qualcuno presente in stanza?\n1. SI\n2. NO\n");
    scanf("%d", &scel);
    switch (scel){
      case 1:
      printf("Vuoi uccidere il gioctore: %s\033[0;0m?\n1. SI\n2. NO\n", nome[giocatori[presenti_in_stanza].nome]);
      scanf("%d",&uccidi);
      switch(uccidi){
        case 1:
        uccidi_astronauta();
        mossa=1;
        break;

        case 2:
        mossa=0;
        break;
     }
     break;

     case 2:
     presenti_in_stanza=numero_giocatori;
     break;

     default:
     printf("Il valore inserito non è corretto\n");
     break;
    }
 }
}
}
}

//funzione principale del gioco
void gioca(){

 static int menu;
 static int j=0;
 lista_stanze=stanza_inizio;

while(impostori!=0 && impostori!=astronauti && numero_quest!=0){
  if (turno==numero_giocatori){
    turno=0;
  }
     system ("clear");
     mossa=0;
     printf("È il turno del %s giocatore: %s\033[0;0m\n", numero[turno], nome[giocatori[turno].nome]);

     if(giocatori[turno].posizione->info==0){
       printf("La stanza è %s\n", tipo[giocatori[turno].posizione->info]);
     }
     else{
       printf("All'interno della stanza c'è una %s\n", tipo[giocatori[turno].posizione->info]);
     }

    giocatori_in_stanza();

    //turno di un astronauta
    if(giocatori[turno].stato==0){
      lista_stanze=giocatori[turno].posizione;
      if (giocatori[turno].posizione->info==0){
        if(mossa==0){
          do{
            printf("\nCosa vuoi fare?\n1. Resta fermo\n2. Cambia stanza\n");
            scanf("%d",&menu);

            if(menu!=1 && menu!=2){
              printf("Il valore inserito non è corretto\n");
            }
          }while(menu!=1 && menu!=2);

          switch(menu){

            case 1:
            mossa=1;
            break;

            case 2:
            avanza();
            break;
          }
        }
      }

       if (giocatori[turno].posizione->info==1){
        if(mossa==0){
          do{
            printf("\nCosa vuoi fare?\n1. Resta fermo\n2. Esegui quest\n3. Cambia stanza\n");
            scanf("%d",&menu);

            if(menu!=1 && menu!=2 && menu!=3){
              printf("Il valore inserito non è corretto\n");
            }
          }while(menu!=1 && menu!=2 && menu!=3);

          switch(menu){

            case 1:
            mossa=1;
            break;

            case 2:
            esegui_quest();
            break;

            case 3:
            avanza();
            break;
          }
        }
      }

       if (giocatori[turno].posizione->info==2){

        if(mossa==0){
          do{
            printf("\nCosa vuoi fare?\n1. Resta fermo\n2. Esegui quest\n3. Cambia stanza\n");
            scanf("%d",&menu);

            if(menu!=1 && menu!=2 && menu!=3){
              printf("Il valore inserito non è corretto\n");
            }
          }while(menu!=1 && menu!=2 && menu!=3);

          switch(menu){

            case 1:
            mossa=1;
            break;

            case 2:
            esegui_quest();
            break;

            case 3:
            avanza();
            break;
          }
        }
      }

       if (giocatori[turno].posizione->info==3){
        if(mossa==0){
          do{
            printf("\nTi trovi all'interno di una stanza contenente una botola ma non puoi usarla!\ncosa vuoi fare?\n1. Resta fermo\n2. Cambia stanza\n");
            scanf("%d",&menu);

            if(menu!=1 && menu!=2){
              printf("Il valore inserito non è corretto\n");
            }
          }while(menu!=1 && menu!=2);

          switch(menu){

            case 1:
            mossa=1;
            break;

            case 2:
            avanza();
            break;
          }
        }
      }
      }

      //turno di un impostore
    if(giocatori[turno].stato==1){
    lista_stanze=giocatori[turno].posizione;

     if (giocatori[turno].posizione->info==0){

        if(mossa==0){
          do{
            printf("\nCosa vuoi fare?\n1. Resta fermo\n2. Cambia stanza\n");
            scanf("%d",&menu);

            if(menu!=1 && menu!=2){
              printf("Il valore inserito non è corretto\n");
            }
          }while(menu!=1 && menu!=2);

          switch(menu){

            case 1:
            mossa=1;
            break;

            case 2:
            avanza();
            break;
          }
        }
      }

       if (giocatori[turno].posizione->info==1){
        if(mossa==0){
          do{
            printf("\nCosa vuoi fare?\n1. Resta fermo\n2. Sabota quest\n3. Cambia stanza\n");
            scanf("%d",&menu);

            if(menu!=1 && menu!=2 &&  menu!=3){
              printf("Il valore inserito non è corretto\n");
            }
          }while(menu!=1 && menu!=2 && menu!=3);

          switch(menu){

            case 1:
            mossa=1;
            break;

            case 2:
            sabotaggio();
            mossa=1;
            break;

            case 3:
            avanza();
            break;
          }
        }
      }

        if (giocatori[turno].posizione->info==2){
        if(mossa==0){
          do{
            printf("\nCosa vuoi fare?\n1. Resta fermo\n2. Sabota quest\n3. Cambia stanza\n");
            scanf("%d",&menu);

            if(menu!=1 && menu!=2 && menu!=3){
              printf("Il valore inserito non è corretto\n");
            }
          }while(menu!=1 && menu!=2 && menu!=3);

          switch(menu){

            case 1:
            mossa=1;
            break;

            case 2:
            sabotaggio();
            mossa=1;
            break;

            case 3:
            avanza();
            break;
          }
        }
      }

        if (giocatori[turno].posizione->info==3){
        if(mossa==0){
          do{
            printf("\nTi trovi all'interno di una stanza contenente una botola\ncosa vuoi fare?\n1. Resta fermo\n2. Cambia stanza\n3. Usa botola\n");
            scanf("%d",&menu);

            if(menu!=1 && menu!=2 && menu!=3){
              printf("Il valore inserito non è corretto\n");
            }
          }while(menu!=1 && menu!=2 && menu!=3);

          switch(menu){

            case 1:
            mossa=1;
            break;

            case 2:
            avanza();
            break;

            case 3:
            usa_botola();
            break;
          }
        }
      }
    }
    mossa=0;
    turno++;
     j++;
     if (j==numero_giocatori){
       j=0;
     }
 }
   if (impostori==0){
     system("clear");
     printf("\t\t\t\t\t\t\t    Complimenti, hanno vinto gli astronauti!!!\n");
     while(getchar()!='\n');
     while(getchar()!='\n');
     termina_gioco();
   }
   else if  (impostori==astronauti){
     system("clear");
     printf("\t\t\t\t\t\t\t    Complimenti, hanno vinto gli impostori!!!\n");
     while(getchar()!='\n');
     while(getchar()!='\n');
     termina_gioco();
   }
   else if  (numero_quest==0){
     system("clear");
     printf("\t\t\t\t\t\t\t    Complimenti, hanno vinto gli astronauti!!!\n");
     while(getchar()!='\n');
     while(getchar()!='\n');
     termina_gioco();
   }
}

//funzione utilizzata per deallocare la memoria e terminare il gioco
void termina_gioco() {
  free(giocatori);
  giocatori=NULL;
  free(lista_stanze);
  stanza_inizio=NULL;
  lista_stanze=NULL;
  numero_quest=0;
  astronauti=0;
  impostori=0;
  system("clear");
  printf("\n\n\t\t\t\t\t\t\t    Il gioco è terminato e la memoria è stata deallocata correttamente!!\n");
  while(getchar()!='\n');
  system("clear");
}
