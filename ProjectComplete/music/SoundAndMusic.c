/*
 * SoundAndMusic.c
 *
 *  Created on: 5 Sep 2020
 *      Author: namontoy
 */

#include "ch.h"
#include "hal.h"
#include <String.h>
#include <stdlib.h>
#include <SoundAndMusic.h>

 /**
  * This is the first song music!!
  */
const musicNote_t musicMario[MARIO_SONG_LENGHT] = {
    {3790 , 166},
    {3790 , 166},
    {10 , 166},
    {3790 , 166},    // 1
    {10 , 166},
    {4780 , 166},
    {3790 , 166},
    {10 , 166},    // 2
    {3190 , 166},
    {10 , 166},
    {10 , 166},
    {10 , 166},    // 3
    {16380 , 166},
    {10 , 166},
    {10 , 166},
    {10 , 166},    // 4
    {4780 , 166},
    {10 , 166},
    {10 , 166},
    {6380 , 166},    // 5
    {10 , 166},
    {7580 , 166},
    {10 , 166},
    {10 , 166},    // 6
    {10 , 166},
    {5680 , 166},
    {10 , 166},
    {8510 , 166},    // 7
    {10 , 166},
    {5360 , 166},
    {5680 , 166},
    {10 , 166},    // 8
    {6380 , 222},
    {3792 , 222},
    {3190 , 222},    //9
    {3080 , 166},
    {10 , 166},
    {3580 , 166},
    {3190 , 166},    // 10
    {3790 , 166},
    {3790 , 166},
    {10 , 166},
    {3790 , 166},    // 11
    {10 , 166},
    {4780 , 166},
    {3790 , 166},
    {10 , 166},    // 12
    {3190 , 166},
    {10 , 166},
    {10 , 166},
    {10 , 166},    // 13
    {16380 , 166},
    {10 , 166},
    {10 , 166},
    {10 , 166},    // 14
    {4780 , 166},
    {10 , 166},
    {10 , 166},
    {6380 , 166},    // 15
    {10 , 166},
    {7580 , 166},
    {10 , 166},
    {10 , 166},    // 16
    {10 , 166},
    {5680 , 166},
    {10 , 166},
    {8510 , 166},    // 17
    {10 , 166},
    {5360 , 166},
    {5680 , 166},
    {10 , 166},    // 18
    {6380 , 222},
    {3792 , 222},
    {3190 , 222},    //19
    {3080 , 166},
    {10 , 166},
    {3580 , 166},
    {3190 , 166},    // 20
    {0 , 0},
    {0 , 0}
 };
                                               //END OF MARIO SONG


const musicNote_t  startOfMegalovania[START_OF_MEGALOVANIA_LENGHT] = {
{ 3405,150},
  { 3405,150},
  { 1703,300},
  { 2275,450}, //1
  { 2408,300},
  { 2551,300},
  { 2863,300},
  { 3405,150}, //2
  { 2863,150},
  { 2551,150},
  { 3405,150},
  { 3405,150}, //3
  { 1703,300},
  { 2273,450},
  { 2408,300},
  { 2551,300}, //4
  { 2863,300},
  { 3405,150},
  { 2863,150},
  { 2551,150}
};

const musicNote_t startOfTDWDTG[START_OF_TDWDTG_LENGHT] = {
  { 1804,125},          //       (void)pwmChangePeriod(&PWMD3, 1804); //d5#
  { 1911,125},  //        chThdSleepMilliseconds(125);
  { 1703,125},            //        (void)pwmChangePeriod(&PWMD3, 1911);//c5
  { 1517,125},            //        chThdSleepMilliseconds(125);

  { 1432,250}, //        (void)pwmChangePeriod(&PWMD3, 1703);//d5
  { 1432,125}, //        chThdSleepMilliseconds(125);
  { 1275,125}, //        (void)pwmChangePeriod(&PWMD3, 1517);//e5
  { 568,250}, //        chThdSleepMilliseconds(125);

  { 568,125},  //        (void)pwmChangePeriod(&PWMD3, 1432);//f5
  { 506,125},   //        chThdSleepMilliseconds(250);
  { 568,125},  //        (void)pwmChangePeriod(&PWMD3, 1432);//
  { 1275,125},  //        chThdSleepMilliseconds(125);

  { 1432,125}, //        (void)pwmChangePeriod(&PWMD3, 1275);//g5
  { 1517,125},  //        chThdSleepMilliseconds(125);
  { 1911,125}, //        (void)pwmChangePeriod(&PWMD3, 568);//a6
  { 1136,125}, //        chThdSleepMilliseconds(250);

  { 1911,125}, //        (void)pwmChangePeriod(&PWMD3, 568);//a6
  { 1703,125},  //        chThdSleepMilliseconds(126);
  { 1517,250},   //        (void)pwmChangePeriod(&PWMD3, 506);//b6
  { 1517,125},   //        chThdSleepMilliseconds(125);

  { 1432,125}, //        (void)pwmChangePeriod(&PWMD3, 568);//a6
  { 1275,125},    //        chThdSleepMilliseconds(125);
  { 568,125},  //        (void)pwmChangePeriod(&PWMD3, 1275);//g5
  { 1275,125},   //        chThdSleepMilliseconds(125);

  { 1432,125},    //        (void)pwmChangePeriod(&PWMD3, 1432);//f5
  { 1517,125},     //        chThdSleepMilliseconds(125);
  { 1517,125},   //        (void)pwmChangePeriod(&PWMD3, 1517);//e5
  { 1136,125},  //        chThdSleepMilliseconds(125);

  { 1703,125},    //        (void)pwmChangePeriod(&PWMD3, 1911);//c5
  { 1517,125},    //        chThdSleepMilliseconds(125);
  { 1703,125},  //        (void)pwmChangePeriod(&PWMD3, 1136);//a5
  { 1136,125}, //        chThdSleepMilliseconds(125);
  { 1911,125},   //        (void)pwmChangePeriod(&PWMD3, 1911);//c5
  { 1703,125},  //        chThdSleepMilliseconds(125);
  { 1911,125},   //        (void)pwmChangePeriod(&PWMD3, 1703);//d5
  { 1136,125},    //        chThdSleepMilliseconds(125);
  { 1012,125},  //        (void)pwmChangePeriod(&PWMD3, 1517);//e5

  { 1911,125},   //        chThdSleepMilliseconds(250);
  { 1012,125}, //        (void)pwmChangePeriod(&PWMD3, 1517);//e5
  { 2551,125}, //        chThdSleepMilliseconds(125);
  { 1136,125}, //        (void)pwmChangePeriod(&PWMD3, 1432);//f5

  { 1012,125},    //        chThdSleepMilliseconds(125);
  { 1136,125},    //        (void)pwmChangePeriod(&PWMD3, 1275);//g5
  { 2863,125},    //        chThdSleepMilliseconds(125);
  { 2551,125},    //        (void)pwmChangePeriod(&PWMD3, 568);//a6

  { 1136,125},  //        chThdSleepMilliseconds(125);
  { 2551,125},   //        (void)pwmChangePeriod(&PWMD3, 1275);//g5
  { 3405,125},   //        chThdSleepMilliseconds(125);
  { 2863,125},  //        (void)pwmChangePeriod(&PWMD3, 1432);//f5

  { 2511,125}, //        chThdSleepMilliseconds(125);
  { 2863,125}, //        (void)pwmChangePeriod(&PWMD3, 1517);//e5
  { 3034,125},   //        chThdSleepMilliseconds(125);
  { 3405,500},  //        (void)pwmChangePeriod(&PWMD3, 1517);//e5
};

const musicNote_t startOfBlue[START_OF_BLUE_LENGHT] = {
  { 1136,420},
  { 2024,210},
  { 3405,210},
  { 2551,210}, //1
  { 2024,210},
  { 1911,210},
  { 2863,210},
  { 1136,210}, //2
  { 2024,210},
  { 2024,210},
  { 2551,210},
  { 2024,210}, //3
  { 1703,210},
  { 1517,210},
  { 2551,210},
  { 1703,210}, //4
  { 1911,210},
  { 2024,210},
  { 3405,210},
  { 2551,210}, //5
  { 2024,210},
  { 2024,210},
  { 2551,210},
  { 2024,210}, //6
  { 2024,210},
  { 2551,210},
  { 2024,210},
  { 1703,210}, //7
  { 1517,210},
  { 2551,210},
  { 1703,210},
  { 1911,210}, //8
  { 2024,210},
  { 3405,210},
  { 2511,210},
  { 2024,210}, //9
  { 1911,210},
  { 2863,210},
  { 1136,210},
  { 2024,210}, //10
  { 2024,210},
  { 2551,210},
  { 2024,210},
  { 1703,210}, //11
  { 1517,210},
  { 2551,210},
  { 1703,210},
  { 1911,210}, //12
  { 2024,210},
  { 3405,210},
  { 2551,210},
  { 2024,210}, //13
  { 1136,210},
  { 3822,210},
  { 2863,210},
  { 2551,1000},
};

