/*
 * led.c
 *
 *  Created on: 28 feb 2021
 *      Author: loren
 */

#include "Led.h"


//static THD_FUNCTION( thdLed, arg ) {
//  ledconfig_t *cfg = (ledconfig_t*)arg;
//
//  // Set the name for each single Thread
//  chRegSetThreadName(cfg->threadName);
//
//  palSetLineMode(cfg->line, PAL_MODE_OUTPUT_PUSHPULL);
//  palClearLine(cfg->line);
//
//  // This is the task that will be executed every single slot time
//  // the Thread as the right to use the processor
//  while (true) {
//    if (cfg->state == 1) {
//
//      palSetLine(cfg->line);
//      chThdSleepMilliseconds(cfg->timeON);
//      palClearLine(cfg->line);
//      chThdSleepMilliseconds(cfg->timeOFF);
//
//    }else{
//      palClearLine(cfg->line);
//      chThdSleepMilliseconds(cfg->timeOFF);
//    }
//
//  }
//};

/* Ho quattro fasi del display:
 * 1 start  (verde,rosso e giallo)
 * 2 difficulty (1 rosso-easy, 2 rosso-medium, 3 rosso-hard)
 * 3 gioco con 3 vite ( 3 verdi-3 vite, 2 verdi 1 rosso-2 vite, 1 verde 2 rosso-1 vita, 3 rosse-GAME OVER)
 * 4 score
 * 5 restart lampeggiano (colori da scegliere)
*/

/* Devo riuscire a passare la struttura con tutti i dati dei thread
 * ma allo stesso tempo passare anche le variabili comunicate dalle altre componenti
 *
 */

static THD_FUNCTION( thdLed, arg ) { //variabile del display
  ledconfig_t *cfg = (ledconfig_t*)arg;

  // Set the name for each single Thread
  chRegSetThreadName(cfg->threadName);

  palSetLineMode(cfg->line, PAL_MODE_OUTPUT_PUSHPULL);
  palClearLine(cfg->line);

  // This is the task that will be executed every single slot time
  // the Thread as the right to use the processor
  while (true) {
    if (cfg->state == 1) {

      palSetLine(cfg->line);
      chThdSleepMilliseconds(cfg->timeON);
      palClearLine(cfg->line);
      chThdSleepMilliseconds(cfg->timeOFF);

    }else{
      palClearLine(cfg->line);
      chThdSleepMilliseconds(cfg->timeOFF);
    }

  }
};
