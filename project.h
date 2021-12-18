#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include "sense.h"
#include <linux/input.h>
#include <unistd.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>

//input.c
void openJoystick(void);
void closeJoystick(void);
void checkJoystick(void(*callback)(unsigned int code), int delay);
void shake(void);

//ouput.c
void openDisplay(void);
void closeDisplay(void);
void board(void);
void displayDot(char letter, int x, int y);
void clearDisplay(void);
void place(char letter, int x);
void clear_board(void);
bool check_score(void);
void displayWinner(void);
