/*
 * music.h
 *
 *  Created on: 27 feb 2021
 *      Author: loren
 */

#ifndef MUSIC_H_
#define MUSIC_H_

#include "SoundAndMusic.h"
#include "ch.h"
#include "hal.h"
#include "shell.h"
#include "chprintf.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


 #define PWM5_CHANNEL1_PA0        0
 #define PWM5_CHANNEL2_PA1        1
 #define PWM5_CHANNEL3_PA2        2
 #define PWM5_CHANNEL4_PA3        3

  uint32_t selectMusic;

 // Mario Music!!
 extern const musicNote_t musicMario[MARIO_SONG_LENGHT];
 extern const musicNote_t startOfMegalovania[START_OF_MEGALOVANIA_LENGHT];
 extern const musicNote_t startOfTDWDTG[START_OF_TDWDTG_LENGHT];
 extern const musicNote_t startOfBlue[START_OF_BLUE_LENGHT];

#define PWM_PERIOD 1000
#define PWM_TIMER_FREQUENCY     1000000

void pwmWidtchCb(PWMDriver *pwmp){
  (void)pwmp;
  chprintf((BaseSequentialStream*)&SD2, "START PERIOD\n\r");
}

/*
 * Configures PWM Driver.
 */
static PWMConfig pwmcfg = {
  PWM_TIMER_FREQUENCY,
  PWM_PERIOD,
  pwmWidtchCb,
  {
   {PWM_OUTPUT_ACTIVE_LOW, NULL},         // PIN PA0 (for TIM5)
   {PWM_OUTPUT_DISABLED, NULL},         // PIN PA1 (for TIM5)
   {PWM_OUTPUT_DISABLED, NULL},         // PIN PA2 (for TIM5)
   {PWM_OUTPUT_DISABLED, NULL}       // PIN PA3 (for TIM5)
  },
  0,
  0
};

 bool soundMusic;

 static THD_WORKING_AREA( waMusic, 512 );


 static THD_FUNCTION( thdMusic, arg );


#endif /* MUSIC_H_ */
