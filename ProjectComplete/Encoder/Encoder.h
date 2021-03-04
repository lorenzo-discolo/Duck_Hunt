/*
 * Encoder.h
 *
 *  Created on: 27 feb 2021
 *      Author: loren
 */

#ifndef ENCODER_ENCODER_H_
#define ENCODER_ENCODER_H_

#define SW_ENCODER_PORT          GPIOC
#define SW_ENCODER_PIN           5U
#define SW_ENCODER_LINE          PAL_LINE( SW_ENCODER_PORT, SW_ENCODER_PIN) // board.h line 269

#define ENCODER_DT_LINE         PAL_LINE( GPIOC, 6U )
#define ENCODER_CLK_LINE        PAL_LINE( GPIOC, 9U )

//Memoria heap dedicata all' Enoder_Bottone
static THD_WORKING_AREA(waThreadButton, 128);
//Creazione Thread_Encoder_Bottone
static THD_FUNCTION(thdButton, arg);

//Memoria heap dedicata all'Encoder
static THD_WORKING_AREA(waEncoder, 128);
//Creazione funzione Encoder
static THD_FUNCTION(thdEncoder, arg);

#endif /* ENCODER_ENCODER_H_ */
