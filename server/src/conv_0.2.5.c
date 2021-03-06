/*
 *  Copyright (C) 1999-2002 by Marco Caldarelli and Riccardo Vianello
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 */
/****************************************************************************
* Cittadella/UX server tools             (C) M. Caldarelli and R. Vianello  *
*                                                                           *
* File: conv_0.2.5                                                          *
*       Converte la struttura dati_server da 0.1.22/0.2.4 a 0.2.5           *
****************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define FILE_DATI_SERVER "./lib/server/dati_server"
#define WS_DAYS 7                  /* Statistica settimanale: 7 dati */

/*
        Vecchia struttura dati_server: versione 0.1.22 a 0.2.4.
 */
struct dati_server_24 {
  long server_runs;  /* Numero di volte che il server e' partito  */
  long matricola;    /* Ultimo # matricola assegnato              */
  long connessioni;  /* Numero totale di connessioni              */
  long local_cl;     /* Numero di connessioni con client locale   */
  long remote_cl;    /* Numero di connessioni con client remoto   */
  long login;        /* Numero login al server                    */
  long ospiti;       /* Numero di login da parte di ospiti        */
  long nuovi_ut;     /* Numero di nuovi utenti avuti              */
  long validazioni;  /* Numero di validazioni eseguite            */
  long max_users;    /* Record di connessioni contemporanee       */
  time_t max_users_time; /* Data e ora del record                 */
  /* Operazioni eseguite                                          */
  long X;            /* Numero di X inviati                       */
  long broadcast;    /* Numero di broadcast inviati               */
  long mails;        /* Numero di mail inviati                    */
  long posts;        /* Numero di posts immessi                   */
  long chat;          /* Numero messaggi in chat                  */
  /* File messaggi                                                */
  long fm_num;       /* Ultimo numero di file messaggi assegnato  */
  long fm_curr;      /* Numero di file messaggi presenti          */
  long fm_basic;     /* File messaggi assegnato alle room di base */
  long fm_mail;      /* File messaggi assegnato alle mailbox      */
  long fm_normal;    /* File messaggi di default per le altre room*/
  /* Room                                                         */
  long room_num;     /* Ultima matricola di room assegnata        */
  long room_curr;    /* Numero di room presenti                   */
  long utr_nslot;    /* Numero di slots allocate per dati UTR     */
  long mail_nslot;   /* Numero di slots allocate per lista mail   */
  long mailroom;     /* Numero della room adibita a mailroom      */
  long baseroom;    /* Numero della room adibita a baseroom       */
  /* Floors                                                       */
  long floor_num;    /* Ultima matricola di floor assegnata       */
  long floor_curr;   /* Numero di floor presenti                  */
  /* Statistiche sui collegamenti                                 */
  long stat_ore[24];   /* Distribuzione login nella giornata      */
  long stat_giorni[7]; /* Distribuzione login nella settimana     */
  long stat_mesi[12];  /* Distribuzione login nei mesi            */
  /* Statistiche di uso del server settimanale (week stats).      */
  time_t ws_start;      /* data inizio statistiche settimanali    */
  long ws_connessioni[WS_DAYS]; /* Numero totale di connessioni            */
  long ws_local_cl[WS_DAYS];  /* Numero di connessioni con client locale   */
  long ws_remote_cl[WS_DAYS]; /* Numero di connessioni con client remoto   */
  long ws_login[WS_DAYS];     /* Numero login al server                    */
  long ws_ospiti[WS_DAYS];    /* Numero di login da parte di ospiti        */
  long ws_nuovi_ut[WS_DAYS];  /* Numero di nuovi utenti avuti              */
  long ws_validazioni[WS_DAYS]; /* Numero di validazioni eseguite          */
  long ws_X[WS_DAYS];         /* Numero di X inviati                       */
  long ws_broadcast[WS_DAYS]; /* Numero di broadcast inviati               */
  long ws_mails[WS_DAYS];     /* Numero di mail inviati                    */
  long ws_posts[WS_DAYS];     /* Numero di posts immessi                   */
  long ws_read[WS_DAYS];      /* Numero di post letti                      */
  long ws_chat[WS_DAYS];      /* Numero messaggi in chat                   */
};

/*
 *          Nuova struttura dati_server: 0.2.5
 */
struct dati_server {
  long server_runs;  /* Numero di volte che il server e' partito  */
  long matricola;    /* Ultimo # matricola assegnato              */
/*
 * connessioni: incrementato da nuova_conn() quando viene creata la conn.
 * local_cl   : incrementato da cmd_info() quando la connessione e remota.
 * remote_cl  : idem quando la connessione e' locale.
 * login, ospiti, nuovi_ut: aggiornati in cmd_usr1() a login avvenuto.
 */
  long connessioni;  /* Numero totale di connessioni              */
  long local_cl;     /* Numero di connessioni con client locale   */
  long remote_cl;    /* Numero di connessioni con client remoto   */
  long login;        /* Numero login al server                    */
  long ospiti;       /* Numero di login da parte di ospiti        */
  long nuovi_ut;     /* Numero di nuovi utenti avuti              */
  long validazioni;  /* Numero di validazioni eseguite            */
  long max_users;    /* Record di connessioni contemporanee       */
  time_t max_users_time; /* Data e ora del record                 */
  /* Statistiche connessioni al CittaWeb                          */
  long http_conn;    /* Numero totale di connessioni http         */
  long http_conn_ok; /* Numero connessioni servite correttamente  */
  long http_room;    /* Numero di richieste http di room          */
  long http_info;    /* Numero di richieste http di info          */
  long http_help;    /* Numero di richieste http di help          */
  long http_profile; /* Numero di richieste http di profile       */
  long http_blog;    /* Numero di richieste http di blog         */
  /* Operazioni eseguite                                          */
  long X;            /* Numero di X inviati                       */
  long broadcast;    /* Numero di broadcast inviati               */
  long mails;        /* Numero di mail inviati                    */
  long posts;        /* Numero di posts immessi                   */
  long chat;         /* Numero messaggi in chat                   */
  long blog;         /* Numero di blog immessi                    */
  long referendum;   /* Numero referendum                         */
  long sondaggi;     /* Numero sondaggi                           */
  /* File messaggi                                                */
  long fm_num;       /* Ultimo numero di file messaggi assegnato  */
  long fm_curr;      /* Numero di file messaggi presenti          */
  long fm_basic;     /* File messaggi assegnato alle room di base */
  long fm_mail;      /* File messaggi assegnato alle mailbox      */
  long fm_normal;    /* File messaggi di default per le altre room*/
  /* Room                                                         */
  long room_num;     /* Ultima matricola di room assegnata        */
  long room_curr;    /* Numero di room presenti                   */
  long utr_nslot;    /* Numero di slots allocate per dati UTR     */
  long mail_nslot;   /* Numero di slots allocate per lista mail   */
  long mailroom;     /* Numero della room adibita a mailroom      */
  long baseroom;     /* Numero della room adibita a baseroom      */
  long blog_nslot;   /* Numero di slots allocate per lista mail   */
  long blogroom;     /* Numero della room adibita a baseroom      */
  /* Floors                                                       */
  long floor_num;    /* Ultima matricola di floor assegnata       */
  long floor_curr;   /* Numero di floor presenti                  */
  /* Statistiche sui collegamenti                                 */
  long stat_ore[24];   /* Distribuzione login nella giornata      */
  long stat_giorni[7]; /* Distribuzione login nella settimana     */
  long stat_mesi[12];  /* Distribuzione login nei mesi            */
  /* Statistiche di uso del server settimanale (week stats).      */
  time_t ws_start;              /* data inizio statistiche settimanali       */
  long ws_connessioni[WS_DAYS]; /* Numero totale di connessioni              */
  long ws_local_cl[WS_DAYS];    /* Numero di connessioni con client locale   */
  long ws_remote_cl[WS_DAYS];   /* Numero di connessioni con client remoto   */
  long ws_login[WS_DAYS];       /* Numero login al server                    */
  long ws_ospiti[WS_DAYS];      /* Numero di login da parte di ospiti        */
  long ws_nuovi_ut[WS_DAYS];    /* Numero di nuovi utenti avuti              */
  long ws_validazioni[WS_DAYS]; /* Numero di validazioni eseguite            */
  long ws_X[WS_DAYS];           /* Numero di X inviati                       */
  long ws_broadcast[WS_DAYS];   /* Numero di broadcast inviati               */
  long ws_mails[WS_DAYS];       /* Numero di mail inviati                    */
  long ws_posts[WS_DAYS];       /* Numero di posts immessi                   */
  long ws_read[WS_DAYS];        /* Numero di post letti                      */
  long ws_chat[WS_DAYS];        /* Numero messaggi in chat                   */
};

int main(void)
{
	struct dati_server_24 old;
	struct dati_server ds;
	FILE  *fp;
        int hh = 0, i, ch;
	char bak[256];

	printf("\nCopyright (C) 1999-2002 by Marco Caldarelli and Riccardo Vianello\n");
	printf("\nUtility di conversione strutture del server.\n");
	printf("Effettua l'upgrade alla versione 0.2.5 di Cittadella/UX da versioni precedenti.\n\n");

	/* Carica la struttura vecchia */
	fp = fopen(FILE_DATI_SERVER,"r");
        if (!fp) {
                printf("\nErrore: Non posso aprire in lettura il file dati_server!\n\n");
		return -1;
	} else {
		fseek(fp,0L,0);
		hh=fread((struct dati_server_24 *) &old,
			 sizeof(struct dati_server_24), 1, fp);
		fclose(fp);
	}
	if (hh != 1) {
                printf("\nErrore in lettura dal file dati_server!\n\n");
		return -1;
	}
	
	/* Chiede conferma             */
	printf("Sei sicuro di voler procedere alla conversione (s/n)? ");
	ch = 0;
	do {
		ch = getchar();
	} while (ch != 's' && ch != 'n');
	printf("%c\n\n", ch);
	if (ch != 's') {
		printf("Conversione abortita.\n\n");
		return -1;
	}
	
	/* Converte la struttura       */
	ds.server_runs = old.server_runs;
	ds.matricola = old.matricola;
	ds.connessioni = old.connessioni;
	ds.local_cl = old.local_cl;
	ds.remote_cl = old.remote_cl;
	ds.login = old.login;
	ds.ospiti = old.ospiti;
	ds.nuovi_ut = old.nuovi_ut;
	ds.validazioni = old.validazioni;
	ds.max_users = old.max_users;
	ds.max_users_time = old.max_users_time;
	ds.X = old.X;
	ds.broadcast = old.broadcast;
	ds.mails = old.mails;
	ds.posts = old.posts;
	ds.chat = old.chat;
	ds.fm_num = old.fm_num;
	ds.fm_curr = old.fm_curr;
	ds.fm_basic = old.fm_basic;
	ds.fm_mail = old.fm_mail;
	ds.fm_normal = old.fm_normal;
	ds.room_num = old.room_num;
	ds.room_curr = old.room_curr;
	ds.utr_nslot = old.utr_nslot;
	ds.mail_nslot = old.mail_nslot;
	ds.mailroom = old.mailroom;
	ds.baseroom = old.baseroom;
	ds.floor_num = old.floor_num;
	ds.floor_curr = old.floor_curr;
	for (i=0; i<24; i++)
		ds.stat_ore[i] = old.stat_ore[i];
	for (i=0; i<7; i++)
		ds.stat_giorni[i] = old.stat_giorni[i];
	for (i=0; i<12; i++)
		ds.stat_mesi[i] = old.stat_mesi[i];
	
	ds.ws_start = old.ws_start;
	for(i = 0; i < WS_DAYS; i++) {
		ds.ws_connessioni[i] = old.ws_connessioni[i];
		ds.ws_local_cl[i] = old.ws_local_cl[i];
		ds.ws_remote_cl[i] = old.ws_remote_cl[i];
		ds.ws_login[i] = old.ws_login[i];
		ds.ws_ospiti[i] = old.ws_ospiti[i];
		ds.ws_nuovi_ut[i] = old.ws_nuovi_ut[i];
		ds.ws_validazioni[i] = old.ws_validazioni[i];
		ds.ws_X[i] = old.ws_X[i];
		ds.ws_broadcast[i] = old.ws_broadcast[i];
		ds.ws_mails[i] = old.ws_mails[i];
		ds.ws_posts[i] = old.ws_posts[i];
		ds.ws_read[i] = old.ws_read[i];
		ds.ws_chat[i] = old.ws_chat[i];
	}
	/* Inizializzazione nuove variabili */
	ds.http_conn = 0;
	ds.http_conn_ok = 0;
	ds.http_room = 0;
	ds.http_info = 0;
	ds.http_help = 0;
	ds.http_profile = 0;
	ds.http_blog = 0;
	ds.blog = 0;
	ds.referendum = 0;
	ds.sondaggi = 0;
	ds.blog_nslot = 0;
	ds.blogroom = 0;
	
	/* Backup vecchia struttura    */
        sprintf(bak, "%s-0.2.4", FILE_DATI_SERVER);
        rename(FILE_DATI_SERVER, bak);

	/* Salva la struttura          */
        fp = fopen(FILE_DATI_SERVER, "w");
        if (!fp) {
                printf("Errore: Non posso aprire in scrittura il file dati_server!");
                return -1;
        }
        hh = fwrite((struct dati_ut *) &ds, sizeof(struct dati_server), 1, fp);
        fclose(fp);

	/* The End */
	printf("Ok, la conversione e' stata effettuata con successo!!\n");
	printf("\nIl backup del vecchio file dati_server si trova in:\n");
	printf("%s\n\n", bak);
	return 0;
}
