/*
 * Led.h
 *
 *  Created on: 28 feb 2021
 *      Author: loren
 */

#ifndef LED_LED_H_
#define LED_LED_H_

#include <chthreads.h>
#include <ch.h>


/* #### RGB LED Color (code) #### */
// Line definitions

#define COLOR_RED               0
#define COLOR_GREEN             1
#define COLOR_BLUE              2

#define LED_FIRST_PORT          GPIOA
#define LED_FIRST_PIN           5U

#define LED_SECOND_PORT         GPIOA
#define LED_SECOND_PIN          6U

#define LED_THIRD_PORT          GPIOA
#define LED_THIRD_PIN           7U


#define LED_FIRST_LINE          PAL_LINE( LED_FIRST_PORT, LED_FIRST_PIN )
#define LED_SECOND_LINE            PAL_LINE( LED_SECOND_PORT, LED_SECOND_PIN )
#define LED_THIRD_LINE            PAL_LINE( LED_SECOND_PORT, LED_THIRD_PIN )


/*
 * Structure containing the configuration of the thdLed thread function.
 * Here we add the timeON and timeOFF variables.
 */
typedef struct {
  ioline_t line;
  uint32_t timeON;
  uint32_t timeOFF;
  char threadName[10];
  uint32_t  state;
} ledconfig_t;


int32_t checkColor(char *color);
int32_t checkState(char *state);

//Non ho ho ancora capito cos'è
char LedStates[][4] = {"OFF", "ON"};
char LedColors[][6] = {"RED", "GREEN", "BLUE"};


//Memoria del thread
static THD_WORKING_AREA(waLed, 128 );

//Funzione del thread
static THD_FUNCTION( thdLed, arg );




#endif /* LED_LED_H_ */
