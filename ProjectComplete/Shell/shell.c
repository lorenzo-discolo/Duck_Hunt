
#include "shell.h"


/**
 * Count function called by Shell
 */
static void cmd_count(BaseSequentialStream *chp, int argc, char *argv[]){

  chprintf(chp, "count\n\r");
  if(argc == 0){

  }

  if(&argv[0]){

  }

}

/**
 * Count function called by Shell
 */
static void cmd_write(BaseSequentialStream *chp, int argc, char *argv[]){

  chprintf(chp, "write\n\r");

  if(argc == 0){

  }

  if(&argv[0]){

  }
}


/**
 * Enable Cycles function called by Shell
 */
static void cmd_LedState(BaseSequentialStream *chp, int argc, char *argv[]){

  chprintf(chp, "cmd_LedState\n\r");

  if(argc == 0){

    // Running over the array
    for(uint32_t i_counter = 0; i_counter < 3; i_counter++){
      chprintf(chp, "LED %s state %s, timeON %u (ms)\n\r",
               configs[i_counter].threadName,
               LedStates[configs[i_counter].state],
               configs[i_counter].timeON);
    }
  }

  if(*argv[0] == 1){

  }
}

/**
 * Enable Cycles function called by Shell
 */
static void cmd_LedRgb(BaseSequentialStream *chp, int argc, char *argv[]){

  chprintf(chp, "cmd_LedRgb\n\r");
  bool validColor = FALSE;
  bool validState = FALSE;
  int32_t selectedColor = -1;
  int32_t selectedState = -1;

  // Small explanation about how to use the command
  if(argc == 0){

    chprintf(chp, "Usage: LED_RGB RED ON\n\r");

    chprintf(chp, "Usage: LED_RGB BLUE OFF\n\r");

  }else{

    if(argc == 2){
      // 1. Check that the color was written correctly and return a number
      // that represents the color
      selectedColor = checkColor(argv[0]);

      if(selectedColor != -1){

        validColor = TRUE;
        chprintf(chp, "Selected color is %s \n\r", LedColors[selectedColor]);
        //chprintf(chp, "value %u \n\r", selectedColor);

      }else{

        validColor = FALSE;
        chprintf(chp, "Wrong color...\n\r");
        chprintf(chp, "Possible colors: RED|GREEN|BLUE\n\r");

      }

      // 2. Now we do the same but with the state (it is more or less the same but with the state)
      selectedState = checkState(argv[1]);

      if(selectedState != -1){

        validState = TRUE;
        chprintf(chp, "Selected state is %s \n\r", LedStates[selectedState]);
        //chprintf(chp, "value %u \n\r", selectedState);

      }else{

        validState = FALSE;
        chprintf(chp, "Wrong state...\n\r");
        chprintf(chp, "PosSible states: OFF|ON\n\r");
      }

    }else{

      chprintf(chp, "No enough arguments...\n\r");

    }//end external else -> args != 2

    // 3. If both booleans variables validColor and validState are correct, then is possible to assign
    // the configuration to the LED

    if(validColor & validState){
      // Loading the configuration on the right position (on the structure) and the State value
      configs[selectedColor].state = selectedState;

      chprintf(chp, "Loading config on led %s with state %s\n\r",
               configs[selectedColor].threadName,
               //LedColors[selectedColor],
               LedStates[(configs[selectedColor].state)]
               );
    }

  }//end external else -> args == 0

}// end function



/**
 * Enable Cycles function called by Shell
 */
static void cmd_LedPeriod(BaseSequentialStream *chp, int argc, char *argv[]){

  chprintf(chp, "cmd_LedPeriod\n\r");
  bool validColor = FALSE;
  bool validNumber = FALSE;
  int32_t selectedColor = -1;
  int32_t configPeriod = -1;

  // Small explanation about how to use the command
    if(argc == 0){

      chprintf(chp, "Usage: LED_PERIOD 250 RED\n\r");

      chprintf(chp, "Usage: LED_PERIOD 550 GREEN\n\r");

    }else{

      if(argc == 2){
        // 1. Check that the color was written correctly and return a number
        // that represents the color
        selectedColor = checkColor(argv[1]);

        if(selectedColor != -1){

          validColor = TRUE;
          chprintf(chp, "Selected color is %s \n\r", LedColors[selectedColor]);
          chprintf(chp, "value %u \n\r", selectedColor);

        }else{

          validColor = FALSE;
          chprintf(chp, "Wrong color...\n\r");
          chprintf(chp, "Possible colors: RED|GREEN|BLUE\n\r");

        }

        // 2. Now we do the same but with the state (it is more or less the same but with the state)
        configPeriod = getPeriodValue(argv[0]);

        if((configPeriod >= 0) & (configPeriod < 1001)){

          validNumber = TRUE;
          chprintf(chp, "Selected period is %u \n\r", configPeriod);

        }else{

          validNumber = FALSE;
          chprintf(chp, "Wrong period...\n\r");
          chprintf(chp, "Possible values: 0 - 1000\n\r");
        }

      }else{

        chprintf(chp, "No enough arguments...\n\r");

      }//end external else -> args != 2

      // 3. If both booleans variables validColor and validState are correct, then is possible to assign
      // the configuration to the LED

      if(validColor & validNumber){
        // Loading the configuration on the right position (on the structure) and the State value
        configs[selectedColor].timeON = configPeriod;
        configs[selectedColor].timeOFF = configPeriod;

        chprintf(chp, "Loading config on led %s with period %u\n\r",
                 configs[selectedColor].threadName,
                 //LedColors[selectedColor],
                 configs[selectedColor].timeON
                 );
      }

    }//end external else -> args == 0
}

/**
 * Sound the mario Music
 */
static void cmd_musica(BaseSequentialStream *chp, int argc, char *argv[]){

  selectMusic = 1;
  chprintf(chp, "cmd_musica\n\r");

  if(argc == 0){
    // sound mario music
    soundMusic = FALSE;
    chprintf(chp, "soundMusic = %d\n\r",soundMusic);

  }

  if(argc == 1){
    soundMusic = TRUE;
    selectMusic = atoi(argv[0]);
    chprintf(chp, "Selected Song = %d\n\r",selectMusic);

  }
}

static void cmd_Adc(BaseSequentialStream *chp, int argc, char *argv[]){

  chprintf(chp, "cmd_adc\n\r");

  if(argc == 0){
    // Show ADC
    showAdc = !showAdc;
  }

  if(atoi(argv[0]) == 1){
    showAdc = TRUE;
  }
}


static void cmd_Random(BaseSequentialStream *chp, int argc, char *argv[]){

  int randomNumber;
  chprintf(chp, "cmd_Random\n\r");

  if(argc == 0){
    randomNumber = rand() % 100 + 1;
    chprintf(chp, "random number = %d\n\r", randomNumber);
  }

  if(atoi(argv[0]) == 1){
    //(void*);
  }
}

/**
 * Funzione Regolamento
 */
static void cmd_regolamento(BaseSequentialStream *chp, int argc, char *argv[]){
  (void) argc;
  (void) argv;
  chprintf(chp,
      "DUCK HUNT REMASTERED è una rivisitazione del gioco originale degli anni ‘80. \r\n " \
      "\r\n " \
      "REGOLAMENTO:\r\n " \
      "Lo scopo del gioco è quello di colpire e abbattere le ducks.\r\n " \
      "Con il joystick il giocatore potrà comandare il mirino e sparare con \r\n " \
      "l`utilizzo di un pulsante in esso integrato, avrà a sua disposizione tre colpi,\r\n " \
      "che perderà in caso di colpo fallito. \r\n " \
      "\r\n " \
      "BUON DIVERTIMENTO!!!\r\n ");
}

/**
 * Funzione Regolamento(ing)
 */
static void cmd_regolament(BaseSequentialStream *chp, int argc, char *argv[]){
  (void) argc;
  (void) argv;
  chprintf(chp,
      "DUCK HUNT REMASTERED is a tribute to the classic of the 80’s.\r\n " \
      "\r\n " \
      "RULES:\r\n " \
      "The objective of the game is to shoot the ducks (as the name implies, duh).\r\n " \
      "With the joystick the player can aim and with the joystick’s integrated button shoot.\r\n " \
      "You have only three shots, if you hit the ducks, you will have your bullet back, " \
      "otherwise you’ll lose it.\r\n " \
      "\r\n " \
      "HAVE FUN END ENJOY!\r\n");
}

/**
 * Funzione PIN-MAP
 */
static void cmd_pinmap(BaseSequentialStream *chp, int argc, char *argv[]){
  (void) argc;
  (void) argv;
  chprintf(chp,
"|---------------------------------------------------------| \r\n" \
"|                        PIN-MAP                          | \r\n" \
"|-----------|-----|---------|--------------|--------------| \r\n" \
"| COMPONENT | PIN |   CON   |     MODE     |  PERIPHERAL  | \r\n" \
"|-----------|-----|---------|--------------|--------------| \r\n" \
"|  BUZZER   | PA0 | ARD-D9  |  ALTERNATE   |   PWM_OUT3   | \r\n" \
"|-----------|-----|---------|--------------|--------------| \r\n" \
"| JOYSTICK  | PC2 |   Y-S   |   INPUT      |              | \r\n" \
"|    VRY    |     |         |              |              | \r\n" \
"|-----------|-----|---------|--------------|--------------| \r\n" \
"| JOYSTICK  | PC3 |   X-S   |   INPUT      |              | \r\n" \
"|    VRX    |     |         |              |              | \r\n" \
"|-----------|-----|---------|--------------|--------------| \r\n" \
"| JOYSTICK  | PC  |         |              |              | \r\n" \
"|    SW     |     |         |              |              | \r\n" \
"|-----------|-----|---------|--------------|--------------| \r\n" \
"|  DISPLAY  | PB8 | ARD-D15 |  ALTERNATE   |      SCL     | \r\n" \
"|    SCL    |     |         |              |              | \r\n" \
"|-----------|-----|---------|--------------|--------------| \r\n" \
"|  DISPLAY  | PB9 | ARD-D14 |  ALTERNATE   |      SDA     | \r\n" \
"|    SDA    |     |         |              |              | \r\n" \
"|-----------|-----|---------|--------------|--------------| \r\n" \
"|  ENCODER  | PC9 |         |    INPUT     |              | \r\n" \
"|    CLK    |     |         |              |              | \r\n" \
"|-----------|-----|---------|--------------|--------------| \r\n" \
"|  ENCODER  | PC6 |         |    INPUT     |              | \r\n" \
"|    DT     |     |         |              |              | \r\n" \
"|-----------|-----|---------|--------------|--------------| \r\n" \
"| LED RED1  | PA6 | ARD-D12 |  PUSHPULL    |     GPIO     | \r\n" \
"|-----------|-----|---------|--------------|--------------| \r\n" \
"| LED GREEN1| PA7 | ARD-D11 |  PUSHPULL    |     GPIO     | \r\n" \
"|-----------|-----|---------|--------------|--------------| \r\n" \
"| LED BLUE1 | PB6 | ARD-D10 |  PUSHPULL    |     GPIO     | \r\n" \
"|-----------|-----|---------|--------------|--------------| \r\n" \
"| LED RED2  | PA9 | ARD-D8  |  PUSHPULL    |     GPIO     | \r\n" \
"|-----------|-----|---------|--------------|--------------| \r\n" \
"| LED GREEN2| PA8 | ARD-D7  |  PUSHPULL    |     GPIO     | \r\n" \
"|-----------|-----|---------|--------------|--------------| \r\n" \
"| LED BLUE2 | PB4 | ARD-D5  |  PUSHPULL    |     GPIO     | \r\n" \
"|-----------|-----|---------|--------------|--------------| \r\n" \
"| LED RED3  | PB5 | ARD-D4  |  PUSHPULL    |     GPIO     | \r\n" \
"|-----------|-----|---------|--------------|--------------| \r\n" \
"| LED GREEN3| PB3 | ARD-D3  |  PUSHPULL    |     GPIO     | \r\n" \
"|-----------|-----|---------|--------------|--------------| \r\n" \
"| LED BLUE3 | PA10| ARD-D2  |  PUSHPULL    |     GPIO     | \r\n" \
"|-----------|-----|---------|--------------|--------------|\r\n"
);

}
