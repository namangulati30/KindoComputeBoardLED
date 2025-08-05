#ifndef __LEDS_H
#define __LEDS_H


#include "main.h"

#define MAX_LED 2
#define USE_BRIGHTNESS 1
#define PI 3.14159265
#define STRIP 0
#define GATE 1
#define CUP 2 
#define On 1



extern uint8_t LED_Data_GATE[MAX_LED][4];
extern uint8_t LED_Data_CUP[MAX_LED][4];
extern uint8_t LED_Mod_Cup[MAX_LED][4];//for brightness
extern uint8_t LED_Mod_Gate[MAX_LED][4];//for brightness
extern uint8_t datasentflag1;
extern uint8_t datasentflag2;



void Set_LED_GATE (int LEDnum, int Red, int Green, int Blue);
void Set_LED_CUP (int LEDnum, int Red, int Green, int Blue);
void Set_Brightness_CUP (int brightness);
void Set_Brightness_GATE (int brightness);
void WS2812_Send (uint8_t Timno);
void BreatheWhite(void);
void BreatheRed(void);
void BreatheGreen(void);
void BreatheBlue(void);
void Whiteon(void);
void Redon(void);
void Greenon(void);
void Blueon(void);
void Alloff(void);

#endif

