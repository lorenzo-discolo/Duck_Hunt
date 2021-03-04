/*
    ChibiOS - Copyright (C) 2020 Domenico Rega

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.


    PIN_MAP
 |---------------------------------------------------------|
 |                        PIN-MAP                          |
 |-----------|-----|---------|--------------|--------------|
 | COMPONENT | PIN |   CON   |     MODE     |  PERIPHERAL  |
 |-----------|-----|---------|--------------|--------------|
 |  BUZZER   | PA0 | ARD-D9  |  ALTERNATE   |   PWM_OUT3   |
 |-----------|-----|---------|--------------|--------------|
 | JOYSTICK  | PC2 |   Y-S   |   INPUT      |              |
 |    VRY    |     |         |              |              |
 |-----------|-----|---------|--------------|--------------|
 | JOYSTICK  | PC3 |   X-S   |   INPUT      |              |
 |    VRX    |     |         |              |              |
 |-----------|-----|---------|--------------|--------------|
 | JOYSTICK  | PC  |         |              |              |
 |    SW     |     |         |              |              |
 |-----------|-----|---------|--------------|--------------|
 |  DISPLAY  | PB8 | ARD-D15 |  ALTERNATE   |      SCL     |
 |    SCL    |     |         |              |              |
 |-----------|-----|---------|--------------|--------------|
 |  DISPLAY  | PB9 | ARD-D14 |  ALTERNATE   |      SDA     |
 |    SDA    |     |         |              |              |
 |-----------|-----|---------|--------------|--------------|
 |  ENCODER  | PC9 |         |    INPUT     |              |
 |    CLK    |     |         |              |              |
 |-----------|-----|---------|--------------|--------------|
 |  ENCODER  | PC6 |         |    INPUT     |              |
 |    DT     |     |         |              |              |
 |-----------|-----|---------|--------------|--------------|
 | LED RED1  | PA6 | ARD-D12 |  PUSHPULL    |     GPIO     |
 |-----------|-----|---------|--------------|--------------|
 | LED GREEN1| PA7 | ARD-D11 |  PUSHPULL    |     GPIO     |
 |-----------|-----|---------|--------------|--------------|
 | LED BLUE1 | PB6 | ARD-D10 |  PUSHPULL    |     GPIO     |
 |-----------|-----|---------|--------------|--------------|
 | LED RED2  | PA9 | ARD-D8  |  PUSHPULL    |     GPIO     |
 |-----------|-----|---------|--------------|--------------|
 | LED GREEN2| PA8 | ARD-D7  |  PUSHPULL    |     GPIO     |
 |-----------|-----|---------|--------------|--------------|
 | LED BLUE2 | PB4 | ARD-D5  |  PUSHPULL    |     GPIO     |
 |-----------|-----|---------|--------------|--------------|
 | LED RED3  | PB5 | ARD-D4  |  PUSHPULL    |     GPIO     |
 |-----------|-----|---------|--------------|--------------|
 | LED GREEN3| PB3 | ARD-D3  |  PUSHPULL    |     GPIO     |
 |-----------|-----|---------|--------------|--------------|
 | LED BLUE3 | PA10| ARD-D2  |  PUSHPULL    |     GPIO     |
 |-----------|-----|---------|--------------|--------------|

*/

#include "ch.h"
#include "hal.h"
#include "shell.h"
#include "chprintf.h"
#include "ssd1306.h"
#include <stdio.h>
#include <String.h>
#include <stdlib.h>



#define _12_SECONDS              48  // Increments of 250 ms
#define _14_SECONDS              56  // Increments of 250 ms
#define _15_SECONDS              60  // Increments of 250 ms
#define _16_SECONDS              64  // Increments of 250 ms
#define _17_SECONDS              68  // Increments of 250 ms
#define _18_SECONDS              72  // Increments of 250 ms
#define _19_SECONDS              76  // Increments of 250 ms
#define _20_SECONDS              80  // Increments of 250 ms
#define _30_SECONDS             120  // Increments of 250 ms



int16_t bannerPositionX = 2;

char buffer[20];

static const I2CConfig i2ccfg = {
  OPMODE_I2C,
  400000,
  FAST_DUTY_CYCLE_2,
};

static const SSD1306Config ssd1306cfg = {
  &I2CD1,
  &i2ccfg,
  SSD1306_SAD_0X78,
};


//non lo so se eliminarlo
int32_t checkColor(char *color);
int32_t checkState(char *state);
int32_t getPeriodValue(char *state);










/**
 * Game variables init
 * (we should not trust the compiler)
 */
void initGameVariables(void){
  timeBarLenght = 0;
  counterTimeout = 0;
  counterDisplay = 0;
  barTime = 0;
  bullets = MAX_BULLETS;
  score = 0;
  soundMusic = TRUE;
  selectMusic = 1;
  adcReady = FALSE;
  screen = -1;
  is_title = TRUE;
  is_game = FALSE;
  createNewBird();
}




int main(void) {

  // Config Hardware
   halInit();
  chSysInit();

  // Default config for Serial Driver 2
  sdStart(&SD2, NULL);

  // Default config for the shell
  shellInit();

  struct interaction * comunication = malloc(sizeof(struct interaction));
  // This struct is: line, timeON, timeOFF, threadName, state
   ledconfig_t configs[] = {
      {LED_FIRST_LINE, 750, 200,  "FIRST", 0},
      {LED_SECOND_LINE, 500, 500, "SECOND", 0},
      {LED_THIRD_LINE, 500, 750, "THIRD", 0}
   };

  // Creating the LEDS Threads
  for(int ConfigLed=0; ConfigLed<3; ConfigLed++){
  chThdCreateStatic(waLed, sizeof(waLed), NORMALPRIO + 1, thdLed, (void*)&configs[ConfigLed]);
  }

  //chThdCreateStatic(waLed, sizeof(waLed), NORMALPRIO + 1, thdLed, (void*)&configs[COLOR_GREEN]); L'ho ha fatto nerio

  // Set and config the PWM for the music
//  palSetPadMode(GPIOA, 0, PAL_MODE_OUTPUT_PUSHPULL);
//  palWritePad(GPIOA, 0, PAL_LOW);

  // PWM
  palSetPadMode(GPIOA, 0, PAL_MODE_ALTERNATE(2));
  pwmStart(&PWMD5, &pwmcfg);
  pwmEnableChannel(&PWMD5, PWM5_CHANNEL1_PA0, PWM_PERCENTAGE_TO_WIDTH(&PWMD5, 500));
  pwmStop(&PWMD5);

  // Creating the Thread for the music
  chThdCreateStatic(waMusic, sizeof(waMusic), NORMALPRIO + 1, thdMusic, NULL);

  /* Starts an ADC continuous conversion */
  palSetPadMode(GPIOC, 0, PAL_MODE_INPUT_ANALOG);
  palSetPadMode(GPIOC, 1, PAL_MODE_INPUT_ANALOG);

  /*
   * Setting as analog input:
   *    PORTC PIN 0 -> ADC1_CH10
   *    PORTC PIN 1 -> ADC1_CH11
   */
  palSetGroupMode(GPIOC, PAL_PORT_BIT(0) | PAL_PORT_BIT(1), 0,
                  PAL_MODE_INPUT_ANALOG);

  /*
   * Starting GPT3 driver, it is used for triggering the ADC.
   * Starting the ADC1 driver.
   */
  gptStart(&GPTD3, &gpt3cfg);
  adcStart(&ADCD1, NULL);

  adcStartConversion(&ADCD1, &adcgrpcfg, samples, ADC_GRP_BUF_DEPTH);
  /*
   * Start the GPT3 driver with a period of 10000 cycles and a
   * frequency of 1000000 Hz
   * Each conversion trigger arrives after:
   * 10000[cycls] / 1000000[cycls/s] = 0.01 s = 10 ms
   */
  gptStartContinuous(&GPTD3, 10000);

  /** Button START - on the Encoder. It is in openDrain config, then it needs a Pull-up resistor*/
  palSetPadMode(GPIOC, 5, PAL_MODE_INPUT_PULLUP);

  /* Creates the Encoder thread */
  chThdCreateStatic(waEncoder, sizeof(waEncoder), NORMALPRIO + 1, thdEncoder, NULL);

  /** Thread for Button encoder */
  chThdCreateStatic(waThreadButton, sizeof(waThreadButton), NORMALPRIO + 1, ThreadButton, NULL);


  /* Configuring I2C related PINs */
   palSetLineMode(LINE_ARD_D15, PAL_MODE_ALTERNATE(4) |
                  PAL_STM32_OTYPE_OPENDRAIN | PAL_STM32_OSPEED_HIGHEST |
                  PAL_STM32_PUPDR_PULLUP);
   palSetLineMode(LINE_ARD_D14, PAL_MODE_ALTERNATE(4) |
                  PAL_STM32_OTYPE_OPENDRAIN | PAL_STM32_OSPEED_HIGHEST |
                  PAL_STM32_PUPDR_PULLUP);

  chThdCreateStatic(waOledDisplay, sizeof(waOledDisplay), NORMALPRIO, thdOledDisplay, NULL);

  // Load all the default values for the game
  setInitPosition();
  initGameVariables();

  // Print and initial message.
    chprintf((BaseSequentialStream*) &SD2, "** The game... **\n\r",1);

  /*Infinite loop*/
  while (true) {

    ssd1306UpdateScreen(&SSD1306D1);
    chThdSleepMilliseconds(50);

    thread_t *shelltp = chThdCreateFromHeap(NULL , SHELL_WA_SIZE, "shell", NORMALPRIO + 1, shellThread, (void *) &shell_Cfg1);
    chThdWait(shelltp);
  }
}






/**
 * Set all circle positions to the center of the central (big) circle
 */


/**
 * The idea is to check that the color was written correctly
 *
 * Also, the returned value is related with the color selected
 * 0 -> RED
 * 1 -> GREEN
 * 2 -> BLUE
 *
 */
int32_t checkColor(char *color){

  int32_t selectColorLed = -1;

  // This runs over the possible three colors, until the function strcmp finds the
  // select color. If the color is wrong, the returned value must be -1
  for(uint32_t i_counter = 0; i_counter < 3; i_counter++){

    uint32_t comparison = strcmp(color, LedColors[i_counter]);

    if(comparison == 0){

      selectColorLed = i_counter;

      break;

    }else{
      selectColorLed = -1;
    }
  }

  return selectColorLed;
}

/**
 * The idea is to check that the color was written correctly
 *
 * Also, the returned value is related with the color selected
 * 0 -> OFF
 * 1 -> ON
 *
 */
int32_t checkState(char *state){

  int32_t selectState = -1;

  // This runs over the possible three colors, until the function strcmp finds the
  // select color. If the color is wrong, the returned value must be -1
  for(uint32_t i_counter = 0; i_counter < 2; i_counter++){

    uint32_t comparison = strcmp(state, LedStates[i_counter]);

    if(comparison == 0){

      selectState = i_counter;

      break;

    }else{
      selectState = -1;
    }
  }

  return selectState;
}


/**
 *
 */
int32_t getPeriodValue(char *state);

int32_t getPeriodValue(char *period){

  int32_t readPeriod = atoi(period);

  return readPeriod;
}






