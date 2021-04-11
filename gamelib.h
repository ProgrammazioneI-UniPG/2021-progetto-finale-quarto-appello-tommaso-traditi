//TOMMASO TRADITI             MATRICOLA N. 331519


#include <stdio.h>
#include <stdbool.h>

enum Nome_giocatore{rosso, blu, nero, arancione, giallo,	ciano, rosa, verde, grigio, bianco};   //consente una più facile gestione dei nomi dei giocatori
enum Tipo_stanza {vuota, quest_semplice, quest_complicata, botola};                              //consente una più facile gestione delle tipologie di stanze nel gioco
enum Stato_giocatore {astronauta, impostore, assassinato, defenestrato};                         //consente unapiù facile gestione dello stato dei giocatori

struct Stanza{
	enum Tipo_stanza  info;
	struct Stanza *avanti;
	struct Stanza *sinistra;
	struct Stanza *destra;
	struct Stanza *stanza_precedente;
	struct Stanza *stanza_successiva;
	bool emergenza_chiamata;
};

struct  Giocatore{
	enum Stato_giocatore stato;
  struct Stanza *posizione;
  enum Nome_giocatore nome;
};


void gioca();
void imposta_gioco();
void termina_gioco();
