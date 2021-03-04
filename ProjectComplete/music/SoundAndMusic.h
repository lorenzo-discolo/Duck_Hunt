/*
 * SoundAndMusic.h
 *
 *  Created on: 5 Sep 2020
 *      Author: namontoy
 */

#ifndef SOUNDANDMUSIC_H_
#define SOUNDANDMUSIC_H_

#define MARIO_SONG_LENGHT   80
#define START_OF_MEGALOVANIA_LENGHT 20
#define START_OF_TDWDTG_LENGHT 53
#define START_OF_BLUE_LENGHT  56

 /**
  * This is an structure in which one single element represent a note and the time for that note
  */
 typedef struct{
   uint16_t  frecuency;
   uint16_t  time;
 } musicNote_t;

#endif /* SOUNDANDMUSIC_H_ */
