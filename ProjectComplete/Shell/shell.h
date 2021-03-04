/*
 * shell.h
 *
 *  Created on: 27 feb 2021
 *      Author: loren
 */

#ifndef SHELL_SHELL_H_
#define SHELL_SHELL_H_

#define SHELL_WA_SIZE           THD_WORKING_AREA_SIZE(1024)

static void cmd_write(BaseSequentialStream *chp, int argc, char *argv[]);
static void cmd_count(BaseSequentialStream *chp, int argc, char *argv[]);
static void cmd_LedState(BaseSequentialStream *chp, int argc, char *argv[]);
static void cmd_LedRgb(BaseSequentialStream *chp, int argc, char *argv[]);
static void cmd_LedPeriod(BaseSequentialStream *chp, int argc, char *argv[]);
static void cmd_musica(BaseSequentialStream *chp, int argc, char *argv[]);
static void cmd_Adc(BaseSequentialStream *chp, int argc, char *argv[]);
static void cmd_Random(BaseSequentialStream *chp, int argc, char *argv[]);
static void cmd_pinmap(BaseSequentialStream *chp, int argc, char *argv[]);
static void cmd_regolament(BaseSequentialStream *chp, int argc, char *argv[]);
static void cmd_regolamento(BaseSequentialStream *chp, int argc, char *argv[]);

static const ShellCommand commands[] = {
        {"write", cmd_write},
        {"count", cmd_count},
        {"LED_STATE", cmd_LedState},
        {"LED_RGB", cmd_LedRgb},
        {"LED_PERIOD", cmd_LedPeriod},
        {"adc", cmd_Adc},
        {"random", cmd_Random},
        {"regolamento", cmd_regolamento},
        {"musica", cmd_musica},
        {"PIN-MAP", cmd_pinmap},
        {"rules", cmd_regolament},
        {NULL, NULL}
};

static const ShellConfig shell_Cfg1 = {
       (BaseSequentialStream*) &SD2,
       commands
};

#endif /* SHELL_SHELL_H_ */
