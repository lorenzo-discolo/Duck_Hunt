/*
 * Display.c
 *
 *  Created on: 27 feb 2021
 *      Author: loren
 */

#include "Display.h"

static THD_FUNCTION(thdOledDisplay, arg) {
  (void)arg;

  chRegSetThreadName("thdOledDisplay");

  ssd1306ObjectInit(&SSD1306D1);
  ssd1306Start(&SSD1306D1, &ssd1306cfg);
  ssd1306FillScreen(&SSD1306D1, 0x00);



  screen = MAIN_TITLE_SCREEN;

  while (true) {
    counterDisplay++;

    if (screen == MAIN_TITLE_SCREEN) {

      ssd1306GotoXy(&SSD1306D1, 14, 5);
      sprintf(buffer, "DUCK HUNT");
      ssd1306Puts(&SSD1306D1, buffer, &ssd1306_font_11x18, SSD1306_COLOR_WHITE);

      ssd1306GotoXy(&SSD1306D1, 10, 25);
      sprintf(buffer, "REMASTERED");
      ssd1306Puts(&SSD1306D1, buffer, &ssd1306_font_11x18, SSD1306_COLOR_WHITE);

      ssd1306GotoXy(&SSD1306D1, 15, 50);
      sprintf(buffer, "press start");
      ssd1306Puts(&SSD1306D1, buffer, &ssd1306_font_7x10, SSD1306_COLOR_WHITE);
    }



    if(screen == GAME_SCREEN){
      ssd1306FillScreen(&SSD1306D1, 0x00);
      ssd1306GotoXy(&SSD1306D1, 0, 0);
      // Background -> Tree, grass and Clouds
      drawBackground();

      sprintf(buffer, "score:%u", score);
      drawBullets();
      drawTimeBar();

      ssd1306Puts(&SSD1306D1, buffer, &ssd1306_font_7x10, SSD1306_COLOR_WHITE);

      // Trigger circle
      ssd1306DrawCircle(&SSD1306D1,
                        targetTrigger.positionX,    // Center_X Position
                        targetTrigger.positionY,    // Center_Y Position
                        targetTrigger.radio,        // Circle Radio
                        SSD1306_COLOR_WHITE);       // Color

      // Target Spot
      ssd1306DrawPixel(&SSD1306D1,
                       targetTrigger.positionX,     // Center_X spot
                       targetTrigger.positionY,     // Center_Y spot
                       SSD1306_COLOR_WHITE);        // Color

      // DinamicBird
      ssd1306DrawRectangleFill(&SSD1306D1,
                          dinamicBird.positionX,     // Center_X
                          dinamicBird.positionY,     // Center_Y
                          dinamicBird.radio,         // Side_X
                          dinamicBird.radio,         // Side_Y
                          SSD1306_COLOR_WHITE);      // Color

      updatePosition();
    }

//    else if(screen == END_GAME_SCREEN){ //SChermata finale

//       ssd1306FillScreen(&SSD1306D1, 0x00);
//       ssd1306GotoXy(&SSD1306D1, 37, 1);
//       sprintf(buffer, "SCORE");
//       ssd1306Puts(&SSD1306D1, buffer, &ssd1306_font_11x18, SSD1306_COLOR_WHITE);
//       ssd1306GotoXy(&SSD1306D1, 49, 22);
//       sprintf(buffer, " %u", score);
//       ssd1306Puts(&SSD1306D1, buffer, &ssd1306_font_7x10, SSD1306_COLOR_WHITE);

      else if(screen == END_GAME_SCREEN){ //SChermata finale
      //else if(screen == 2){ //SChermata finale
        is_game = FALSE;
        is_final_screen = TRUE;
        ssd1306FillScreen(&SSD1306D1, 0x00);
        ssd1306GotoXy(&SSD1306D1, 37, 1);
        sprintf(bufferEncoder, "SCORE");
        ssd1306Puts(&SSD1306D1, bufferEncoder, &ssd1306_font_11x18, SSD1306_COLOR_WHITE);
        ssd1306GotoXy(&SSD1306D1, 49, 22);
        sprintf(bufferEncoder, " %u", score);
        ssd1306Puts(&SSD1306D1, bufferEncoder, &ssd1306_font_7x10, SSD1306_COLOR_WHITE);
        if(first){ //quando entra nell'avanti ==1 stampa questa modifica
        ssd1306GotoXy(&SSD1306D1, 43, 40);
        sprintf(bufferEncoder, "%c", old_leaderboard_1);
        ssd1306Puts(&SSD1306D1, bufferEncoder, &ssd1306_font_11x18, SSD1306_COLOR_WHITE);
        }
        if(second){//Quando entra in avanti ==2 salva questa modifica
        ssd1306GotoXy(&SSD1306D1, 56, 40);
        sprintf(bufferEncoder, "%c", old_leaderboard_2);
        ssd1306Puts(&SSD1306D1, bufferEncoder, &ssd1306_font_11x18, SSD1306_COLOR_WHITE);
        }
        if(third){//Quando si preme il pulsante per la terza volta slva questa modifica
              ssd1306GotoXy(&SSD1306D1, 69, 40);
              sprintf(bufferEncoder, "%c", old_leaderboard_3);
              ssd1306Puts(&SSD1306D1, bufferEncoder, &ssd1306_font_11x18, SSD1306_COLOR_WHITE);
              }
        if(scroll_character==0){// Il primo in cui entra
          first = TRUE;
        ssd1306GotoXy(&SSD1306D1, 43, 40);
        sprintf(bufferEncoder, "%c", leaderboard);
        ssd1306Puts(&SSD1306D1, bufferEncoder, &ssd1306_font_11x18, SSD1306_COLOR_WHITE);
        }
         if(scroll_character==1){ //Quando premo il pulsante la prima volta va qui e mette secondo = true
          second = TRUE;
          ssd1306GotoXy(&SSD1306D1, 56, 40);
          sprintf(bufferEncoder, "%c", leaderboard);
          ssd1306Puts(&SSD1306D1, bufferEncoder, &ssd1306_font_11x18, SSD1306_COLOR_WHITE);
          }
        if(scroll_character==2){ //Quando premo il pulsante la seconda volta va qui
                third = TRUE;
                ssd1306GotoXy(&SSD1306D1, 69, 40);
                sprintf(bufferEncoder, "%c", leaderboard);
                ssd1306Puts(&SSD1306D1, bufferEncoder, &ssd1306_font_11x18, SSD1306_COLOR_WHITE);
        }
     }

    // This is related to the ADC conversion
    if(adcReady){

      joystickPosX = 128 * (samples[0])/4096;

      // Inverting the scale for axis-Y
      joystickPosY = 64 * (4096 - samples[1])/4096;

      if(showAdc){
        stop = chVTGetSystemTime();
        delta = chTimeDiffX( start, stop );
        chprintf( (BaseSequentialStream*) &SD2, "posX = %u , posY = %u \r\n",joystickPosX, joystickPosY);
        chprintf( (BaseSequentialStream*) &SD2, "Elapsed = %d ms\r\n  channel = %u \r\n Y channel = %u \r\n",
            TIME_I2MS(delta), samples[0], samples[1] );

        start = stop;
        adcReady = FALSE;
      }
    }
    // Ends ADC conversion

    ssd1306UpdateScreen(&SSD1306D1);
    chThdSleepMilliseconds(50);
  }

}
//%----------------------- END Display ---------------------------------

/* ############### Funzioni ############### */


/**
 *  This code is very similar to Putc
 *  NOT used yet....
 */
void drawImage(void *ip, const ssd1306_font_t *font, ssd1306_color_t color){
  // in font, dt is the data for the image to draw...
  SSD1306Driver *drvp = (SSD1306Driver *)ip;
  uint32_t i, b, j;

  // Go through font
  // This is selecting the pixel line by line starting in the line 0 until line "height"
  for (i = 0; i < font->fh; i++) {

    // b is the byte with the information for 8 pixel in the line defined by 'i'
    b = font->dt[i];

    // Now with this for select every single pixel inside b
    for (j = 0; j < font->fw; j++) {
      if ((b << j) & 0x8000) {
        ssd1306DrawPixel(drvp, drvp->x + j, drvp->y + i, color);
        //drawPixel(drvp, drvp->x + j, drvp->y + i, color);
      } else {
        ssd1306DrawPixel(drvp, drvp->x + j, drvp->y + i,(ssd1306_color_t)! color);
        //drawPixel(drvp, drvp->x + j, drvp->y + i,(ssd1306_color_t)! color);
      }
    }
  }

  //ssd1306DrawPixel(&SSD1306D1, 64, 32, color);

}

void createNewBird(void){
  int randomNumber = 0;
  // get new random position
  // First for axis X
  randomNumber = rand() % 100 + 1;
  dinamicBird.positionX = 10 + randomNumber;

  // First for axis Y
  randomNumber = rand() % 100 + 1;
  dinamicBird.positionY = 5 + randomNumber/2;
}

/**
 *
 */
void drawNewBird(void){
  int randomNumber = 0;
  // Erase previous DinamicBird
  ssd1306DrawRectangleFill(&SSD1306D1,
                      dinamicBird.positionX,     // Center_X
                      dinamicBird.positionY,     // Center_Y
                      dinamicBird.radio,         // Side_X
                      dinamicBird.radio,         // Side_Y
                      SSD1306_COLOR_BLACK);      // Color

  // get new random position
  // First for axis X
  randomNumber = rand() % 100 + 1;
  dinamicBird.positionX = 10 + randomNumber;

  // First for axis Y
  randomNumber = rand() % 100 + 1;
  dinamicBird.positionY = 5 + randomNumber/2;

  // Create new dinamicBird
  ssd1306DrawRectangleFill(&SSD1306D1,
                      dinamicBird.positionX,     // Center_X
                      dinamicBird.positionY,     // Center_Y
                      dinamicBird.radio,         // Side_X
                      dinamicBird.radio,         // Side_Y
                      SSD1306_COLOR_WHITE);      // Color

}

void setInitPosition(void){

  dinamicBird.positionX = CENTER_SCREEN_X + 10;
  dinamicBird.positionY = CENTER_SCREEN_Y + 10;

  targetTrigger.positionX = CENTER_SCREEN_X;
  targetTrigger.positionY = CENTER_SCREEN_Y;
}

/**
 * Update the position (by one pixels) and verify that every single
 * position is not going out of boundaries
 */
void updatePosition(void){
  // Update top circle
  targetTrigger.positionX = joystickPosX;
  targetTrigger.positionY = joystickPosY;


}

/**
 *  This is the background created by Vito!
 *  Wonderful work
 */
void drawBackground(void){
  ssd1306DrawRectangleFill(&SSD1306D1, 0, 63, 128, 1, SSD1306_COLOR_WHITE);
  ssd1306DrawRectangleFill(&SSD1306D1, 10, 44, 5, 20, SSD1306_COLOR_WHITE);
  ssd1306DrawCircleFill(&SSD1306D1, 8, 44, 5, SSD1306_COLOR_WHITE);
  ssd1306DrawCircleFill(&SSD1306D1, 17, 43, 5, SSD1306_COLOR_WHITE);
  ssd1306DrawCircleFill(&SSD1306D1, 19, 36, 6, SSD1306_COLOR_WHITE);
  ssd1306DrawCircleFill(&SSD1306D1, 5, 36, 5, SSD1306_COLOR_WHITE);
  ssd1306DrawCircleFill(&SSD1306D1, 7, 30, 5, SSD1306_COLOR_WHITE);
  ssd1306DrawCircleFill(&SSD1306D1, 15, 30, 5, SSD1306_COLOR_WHITE);
  ssd1306DrawCircleFill(&SSD1306D1, 79, 7, 6, SSD1306_COLOR_WHITE);
  ssd1306DrawCircleFill(&SSD1306D1, 73, 7, 2, SSD1306_COLOR_WHITE);
  ssd1306DrawCircleFill(&SSD1306D1, 84, 7, 3, SSD1306_COLOR_WHITE);
}


void drawTimeBar(void){

  // 200 means increments of 50ms -> 10 s
  //barTime = counterDisplay * (64/200);
  counterTimeout++;
  if(counterTimeout > 50){
    counterTimeout = 0;
    timeBarLenght += 3;

    if(timeBarLenght > 40){
      timeBarLenght = 0;
      createNewBird();
    }
  }
  ssd1306DrawLine(&SSD1306D1, 123, 55, 123, 14 + timeBarLenght, SSD1306_COLOR_WHITE);
  ssd1306DrawLine(&SSD1306D1, 124, 55, 124, 14 + timeBarLenght, SSD1306_COLOR_WHITE);
}

/**
 * The bullets depends the how many shots the persons miss.
 * Maximum bullets is three
 */
void drawBullets(void){
  switch(bullets){
  case 0:
    ssd1306DrawTriangle(&SSD1306D1, 124 , 5 , 126 , 0 , 128 , 5 , SSD1306_COLOR_WHITE);
    ssd1306DrawTriangle(&SSD1306D1, 118 , 5 , 120 , 0 , 122 , 5 , SSD1306_COLOR_WHITE);
    ssd1306DrawTriangle(&SSD1306D1, 112 , 5 , 114 , 0 , 116 , 5 , SSD1306_COLOR_WHITE);
    break;

  case 1:
    ssd1306DrawTriangleFill(&SSD1306D1, 124 , 5 , 126 , 0 , 128 , 5 , SSD1306_COLOR_WHITE);
    ssd1306DrawTriangle(&SSD1306D1, 118 , 5 , 120 , 0 , 122 , 5 , SSD1306_COLOR_WHITE);
    ssd1306DrawTriangle(&SSD1306D1, 112 , 5 , 114 , 0 , 116 , 5 , SSD1306_COLOR_WHITE);
    break;

  case 2:
    ssd1306DrawTriangleFill(&SSD1306D1, 124 , 5 , 126 , 0 , 128 , 5 , SSD1306_COLOR_WHITE);
    ssd1306DrawTriangleFill(&SSD1306D1, 118 , 5 , 120 , 0 , 122 , 5 , SSD1306_COLOR_WHITE);
    ssd1306DrawTriangle(&SSD1306D1, 112 , 5 , 114 , 0 , 116 , 5 , SSD1306_COLOR_WHITE);
    break;

  case 3:
    ssd1306DrawTriangleFill(&SSD1306D1, 124 , 5 , 126 , 0 , 128 , 5 , SSD1306_COLOR_WHITE);
    ssd1306DrawTriangleFill(&SSD1306D1, 118 , 5 , 120 , 0 , 122 , 5 , SSD1306_COLOR_WHITE);
    ssd1306DrawTriangleFill(&SSD1306D1, 112 , 5 , 114 , 0 , 116 , 5 , SSD1306_COLOR_WHITE);
    break;

  default:

    break;
  }

}

/**
 * This function must return 1 if the shot was good and 0 otherwise
 */
int comparePositions(void){
  int auxTriggerX, auxTriggerY;
  int auxBirdX, auxBirdY;
  int auxX, auxY;

  auxTriggerX = targetTrigger.positionX;
  auxTriggerY = targetTrigger.positionY;

  auxBirdX = dinamicBird.positionX;
  auxBirdY = dinamicBird.positionY;

  chprintf((BaseSequentialStream*)&SD2, "auxTriggerX = %d\n\r", auxTriggerX);
  chprintf((BaseSequentialStream*)&SD2, "auxTriggerY = %d\n\r", auxTriggerY);
  chprintf((BaseSequentialStream*)&SD2, "auxBirdX = %d\n\r", auxBirdX);
  chprintf((BaseSequentialStream*)&SD2, "auxBirdY = %d\n\r", auxBirdY);

  auxX = auxTriggerX - auxBirdX;
  auxY = auxTriggerY - auxBirdY;

  chprintf((BaseSequentialStream*) &SD2, "auxX = %d\n\r",auxX);
  chprintf((BaseSequentialStream*) &SD2, "auxY = %d\n\r",auxY);

  // ALL four conditions must be matched to call it a shot!!
  if((auxX > -3) & (auxX <= 3) & (auxY > -3) & (auxY <= 3)){
    return 1;
  }
  return 0;
}


