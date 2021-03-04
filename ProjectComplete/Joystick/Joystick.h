/*
 * Joystick.h
 *
 *  Created on: 27 feb 2021
 *      Author: loren
 */

#ifndef JOYSTICK_JOYSTICK_H_
#define JOYSTICK_JOYSTICK_H_


bool adcReady;
bool showAdc;
int joystickPosX;
int joystickPosY;
systime_t start, stop;
sysinterval_t delta;

/*
 * GPT4 configuration. This timer is used as trigger for the ADC.
 * This code is ALL from example ADC04 (Salvatore)
 *
 */
static const GPTConfig gpt3cfg = {
  1000000U,         /* frequency */
  NULL,             /* callback */
  TIM_CR2_MMS_1,    /* cr2: MMS = 010 = TRGO on Update Event. */
  0U                /* dier */
};

#define ADC_GRP_NUM_CHANNELS   2
#define ADC_GRP_BUF_DEPTH      32

static adcsample_t samples[ADC_GRP_NUM_CHANNELS * ADC_GRP_BUF_DEPTH];

static const ADCConversionGroup adcgrpcfg = {
  TRUE,
  ADC_GRP_NUM_CHANNELS,
  adccallback,
  adcerrorcallback,
  0,                /* CR1 */
  ADC_CR2_EXTEN_0 | ADC_CR2_EXTSEL_3,   /* CR2 */
  ADC_SMPR1_SMP_AN10(ADC_SAMPLE_3) | ADC_SMPR1_SMP_AN11(ADC_SAMPLE_3) , /* SMPR1 */
  0,    /* SMPR2 */
  0,    /* HTR */
  0,    /* LTR */
  ADC_SQR1_NUM_CH(ADC_GRP_NUM_CHANNELS),  /* SQR1 */
  0,    /* SQR2 */
  ADC_SQR3_SQ2_N(ADC_CHANNEL_IN11) | ADC_SQR3_SQ1_N(ADC_CHANNEL_IN10) /* SQR3 */
};


static void adccallback(ADCDriver *adcp);
static void adcerrorcallback(ADCDriver *adcp, adcerror_t err);
#endif /* JOYSTICK_JOYSTICK_H_ */
