/*
 *  Copyright (C) 1999-2000 by Marco Caldarelli and Riccardo Vianello
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 */
/****************************************************************************
* Cittadella/UX Library                  (C) M. Caldarelli and R. Vianello  *
*                                                                           *
* File: text.h                                                              *
*       file include per text.c                                             *
****************************************************************************/

#ifndef _TEXT_H
#define _TEXT_H    1

#define TXT_LINES_ADD 5      /* Numero di linee che alloca e aggiunge alla
                              * struttura text quando ha bisogno di piu'
                              * spazio.
                              */
#define TXT_STDMAX 5         /* Numero di linee che alloca la funzione
                              * txt_create all'inizializzazione di un
                              * testo.
                              */

struct text {
        long max, lstr, rpos, wpos, last;
        char *txt;
};

/* Prototipi delle funzioni in questo file */
struct text *txt_create(void);
struct text *txt_createn(long lstr, long max);
void txt_free(struct text **txt);
void txt_put(struct text *txt, char *str);
void txt_putf(struct text *txt, const char *format, ...) CHK_FORMAT_2;
void txt_putc(struct text *txt, char c);
char *txt_get(struct text *txt);
char *txt_getr(struct text *txt, int i);
int txt_append(struct text *txt1, struct text *txt2);
void txt_jump(struct text *txt, long n);
char *txt_read(struct text *txt, int num);
char *txt_prev(struct text *txt);
long txt_tell(struct text *txt);
char txt_ins(struct text *txt, char *str, int num);
char txt_del(struct text *txt, char *str, int num);
void txt_print(struct text *txt);

/* Restituisce il numero di righe allocate nella struttura *txt. */
#define txt_max(txt) (txt)->max

/* Restituisce il numero di righe riempite nella struttura *txt. */
#define txt_len(txt) (txt)->last

/* Restituisce la posizione della prossima riga da leggere. */
#define txt_rpos(txt) (txt)->rpos

/* Azzera la posizione di lettura. */
#define txt_rewind(txt) (txt)->rpos = 0

/* Mette la posizione di scrittura in fondo al testo */
#define txt_insend(txt) (txt)->wpos = (txt)->last

/* Cancella il testo */
#define txt_clear(txt)           \
        do {                     \
                (txt)->rpos = 0; \
                (txt)->wpos = 0; \
                (txt)->last = 0; \
        } while (0)

#endif /* text.h */

/******************************************************************************
******************************************************************************/
