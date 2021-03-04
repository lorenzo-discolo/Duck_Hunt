/*
 * Display.h
 *
 *  Created on: 27 feb 2021
 *      Author: loren
 */

#ifndef DISPLAY_DISPLAY_H_
#define DISPLAY_DISPLAY_H_

/* ################### All About DISPLAY ################ */
#define MAX_BULLETS         3
#define MAIN_TITLE_SCREEN   0
#define GAME_SCREEN         1
#define END_GAME_SCREEN     2
#define WITDH_SCREEN_X      128
#define WITDH_SCREEN_Y      64
#define CENTER_SCREEN_X     (WITDH_SCREEN_X/2)
#define CENTER_SCREEN_Y     (WITDH_SCREEN_Y/2)

#define TOP_CIRCLE_X            50  //pixels
#define TOP_CIRCLE_Y            10  //pixels
#define LEFT_CIRCLE_X           30  //pixels
#define LEFT_CIRCLE_Y           32  //pixels
#define BOTTOM_LEFT_CIRCLE_X    38  //pixels
#define BOTTOM_LEFT_CIRCLE_Y    57  //pixels
#define BOTTOM_RIGHT_CIRCLE_X   87  //pixels
#define BOTTOM_RIGHT_CIRCLE_Y   55  //pixels
#define TOP_RIGHT_CIRCLE_X      90  //pixels
#define TOP_RIGHT_CIRCLE_Y      28  //pixels
#define CENTER_CIRCLE_X         58  //pixels
#define CENTER_CIRCLE_Y         36  //pixels

int16_t topCircleX, topCircleY, bottomLeftCircleX, bottomLeftCircleY, bottomRightCircleX, bottomRightCircleY;
int16_t leftCircleX, leftCircleY, topRightCircleX, topRightCircleY, centerCircleX, centerCircleY;


typedef struct{
  uint32_t positionX;
  uint32_t positionY;
  uint32_t radio;
}dinamicFigure_t;

dinamicFigure_t dinamicBird = {
  CENTER_SCREEN_X,
  CENTER_SCREEN_Y,
  4
};

dinamicFigure_t targetTrigger = {
  CENTER_SCREEN_X,
  CENTER_SCREEN_Y,
  4
};

unsigned int timeBarLenght;
unsigned int counterTimeout;
unsigned int counterDisplay;
int bullets;
int score;
int screen;
int barTime;
bool is_title;
bool is_game;
bool is_EndGame;

char bufferEncoder[50]; // Ho aumentato questo.
int blink;
int screen = 2;
int leaderboard = 65; // Per cambiare lettera
int scroll_character = 0 ;
int old_leaderboard_1 = 0;
int old_leaderboard_2 = 0;
int old_leaderboard_3 = 0;
bool first = FALSE;
bool second = FALSE;
bool third = FALSE;
bool is_title = FALSE;
bool is_game = FALSE;
bool is_final_screen = FALSE;

static SSD1306Driver SSD1306D1;

/* ############### Memoria heap dedicata ############### */
static THD_WORKING_AREA(waOledDisplay, 512);
/* ############### Funzione Display ############### */
static THD_FUNCTION(thdOledDisplay, arg);

void setInitPosition(void);
void updatePosition(void);
int comparePositions(void);
void initGameVariables(void);
void drawBullets(void);
void drawBackground(void);
void drawTimeBar(void);
void createNewBird(void);
void drawNewBird(void);
void drawImage(void *ip, const ssd1306_font_t *font, ssd1306_color_t color);

#endif /* DISPLAY_DISPLAY_H_ */
