/*
 * Joystick.c
 *
 *  Created on: 27 feb 2021
 *      Author: loren
 */


#include "Joystick.h"

static void adccallback(ADCDriver *adcp) {

  if (adcIsBufferComplete(adcp)) {
    adcReady = TRUE;
  }
}


static void adcerrorcallback(ADCDriver *adcp, adcerror_t err) {
  (void)adcp;
  (void)err;
;
}
//  chSysLockFromISR();
//  chThdResumeI(&trp, (msg_t) MSG_ADC_KO );
//  chSysUnlockFromISR()
