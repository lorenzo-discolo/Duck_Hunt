/*
 * Endoder.c
 *
 *  Created on: 27 feb 2021
 *      Author: loren
 */

#include "Encoder.h"

//Funzione Bottone
static THD_FUNCTION(thdButton, arg) {

  (void)arg;
  chRegSetThreadName("thdButton");
  while (true) {
    if(palReadPad(GPIOC, SW_ENCODER_PIN) == PAL_LOW) {
      chThdSleepMilliseconds(50);

      // The game starts in MainTitle and with button encoder jumps to Game
      if(screen == MAIN_TITLE_SCREEN){
        counterDisplay = 0;
        is_title = FALSE;
        is_game = TRUE;
        is_EndGame = FALSE;
        screen = GAME_SCREEN;
        pwmStop(&PWMD5);
        selectMusic = 3;
        chThdSleepMilliseconds(50);
        bullets = 3;
      }
      //comparare le posizioni.
      // Here we must compare the position between target and bird, tehn decide
      if(screen == GAME_SCREEN){

        int shotResult = comparePositions();

        if(shotResult == 0){

          bullets--;

          if(bullets == 0){
            is_game = FALSE;
            is_EndGame = TRUE;
            screen = END_GAME_SCREEN;
            pwmStop(&PWMD5);
            selectMusic = 2;
            chThdSleepMilliseconds(50);
          }
        }else{
          score += 10;
          drawNewBird();

        }
        //is_title = FALSE;
        //is_game = TRUE;
        //is_EndGame = FALSE;

      }if(is_final_screen){
        if(first && !second && !third){scroll_character = 1; old_leaderboard_1 = leaderboard;}
        if(second && !third){scroll_character = 2; old_leaderboard_2 = leaderboard;}
        if(third){old_leaderboard_3 = leaderboard;}
     }

    }
    chThdSleepMilliseconds(50);
  }
}

//Funzione Encoder
static THD_FUNCTION(thdEncoder, arg) {
  (void)arg;
  chRegSetThreadName("thdEncoder");

  palSetLineMode(ENCODER_CLK_LINE, PAL_MODE_INPUT_PULLUP);
  palSetLineMode(ENCODER_DT_LINE, PAL_MODE_INPUT_PULLUP);

  palEnableLineEvent( ENCODER_CLK_LINE, PAL_EVENT_MODE_RISING_EDGE );


  while (true) {
      palWaitLineTimeout( ENCODER_CLK_LINE, TIME_INFINITE );
      chThdSleepMicroseconds(100);
      uint32_t dt  = palReadLine( ENCODER_DT_LINE ) == PAL_LOW ? 1 : 0;
      uint32_t clk = palReadLine( ENCODER_CLK_LINE ) == PAL_LOW ? 1 : 0;
      if ( clk ^ dt ) {
        //chprintf((BaseSequentialStream*) &SD2, "DX\n\r");
        if(leaderboard<90){
          leaderboard++;
        }

        chprintf((BaseSequentialStream*)&SD2, "Clockwise\n\r%c\n\r", leaderboard); //avanti
        //direction = 0;
      } else {

        //chprintf((BaseSequentialStream*) &SD2, "SX\n\r");
        if(leaderboard>65){
          leaderboard--;
        }
        chprintf((BaseSequentialStream*)&SD2, "Counterclockwise\n\r%c\n\r", leaderboard); //indietro
        //direction = 1;

      }
      chThdSleepMilliseconds(0);
    }
}
