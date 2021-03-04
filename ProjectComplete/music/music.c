/*
 * music.c
 *
 *  Created on: 27 feb 2021
 *      Author: loren
 */
#include "music.h"

  static THD_FUNCTION( thdMusic, arg ) {
    (void)arg;

    // Set the name for each single Thread
    chRegSetThreadName("thdMusic");

    // This is the task that will be executed every single slot time
    // the Thread as the right to use the processor
    while (true) {

      if(soundMusic){

        if(selectMusic == 1){
          pwmStart(&PWMD5, &pwmcfg);
          pwmEnableChannel(&PWMD5, PWM5_CHANNEL1_PA0, PWM_PERCENTAGE_TO_WIDTH(&PWMD5, 500));

          for(uint32_t i_counter = 0; i_counter < MARIO_SONG_LENGHT; i_counter++){
            (void)pwmChangePeriod(&PWMD5, musicMario[i_counter].frecuency);
            chThdSleepMilliseconds(musicMario[i_counter].time);

            if(soundMusic == 0){
             //soundMusic
              pwmStop(&PWMD5);
              break;
            }
          }
       }
       else if (selectMusic == 2) {
         pwmStart(&PWMD5, &pwmcfg);
         pwmEnableChannel(&PWMD5, PWM5_CHANNEL1_PA0, PWM_PERCENTAGE_TO_WIDTH(&PWMD5, 500));

         for (uint32_t i_counter = 0; i_counter < START_OF_MEGALOVANIA_LENGHT; i_counter++) {
           (void)pwmChangePeriod(&PWMD5, startOfMegalovania[i_counter].frecuency);
           chThdSleepMilliseconds(startOfMegalovania[i_counter].time);

           if (soundMusic == 0) {
             //soundMusic
             pwmStop(&PWMD5);
             break;
           }
         }
       }else if (selectMusic == 3) {
         pwmStart(&PWMD5, &pwmcfg);
         pwmEnableChannel(&PWMD5, PWM5_CHANNEL1_PA0, PWM_PERCENTAGE_TO_WIDTH(&PWMD5, 500));

         for (uint32_t i_counter = 0; i_counter < START_OF_TDWDTG_LENGHT; i_counter++) {
           (void)pwmChangePeriod(&PWMD5, startOfTDWDTG[i_counter].frecuency);
           chThdSleepMilliseconds(startOfTDWDTG[i_counter].time);

           if (soundMusic == 0) {
             //soundMusic
             pwmStop(&PWMD5);
             break;
           }
         }
       }
       else if (selectMusic == 4) {
         pwmStart(&PWMD5, &pwmcfg);
         pwmEnableChannel(&PWMD5, PWM5_CHANNEL1_PA0, PWM_PERCENTAGE_TO_WIDTH(&PWMD5, 500));

         for (uint32_t i_counter = 0; i_counter < START_OF_BLUE_LENGHT; i_counter++) {
           (void)pwmChangePeriod(&PWMD5, startOfBlue[i_counter].frecuency);
           chThdSleepMilliseconds(startOfBlue[i_counter].time);

           if (soundMusic == 0) {
             //soundMusic
             pwmStop(&PWMD5);
             break;
           }
         }
       }else{
         if (soundMusic == 0) {
           //soundMusic
           pwmStop(&PWMD5);

         }
       }

      }

      chThdSleepMilliseconds(50);
    }
  };


