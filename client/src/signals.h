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
* Cittadella/UX client                   (C) M. Caldarelli and R. Vianello  *
*                                                                           *
* File : signals.h                                                          *
*        gestione segnali                                                   *
****************************************************************************/
#ifndef _SIGNALS_H
#define _SIGNALS_H   1

#include <signal.h>

extern sig_atomic_t send_keepalive;
extern sig_atomic_t new_signals;

/* Prototipi funzioni in signals.c */
void setup_segnali(void);
void setup_keep_alive(void);
void segnali_ign_sigtstp(void);
void segnali_acc_sigtstp(void);
void hupsig(int sig);
void handler_tstp(int sig);
void handler_cont(int sig);
void esegui_segnali(void);

#endif /* signals.h */
