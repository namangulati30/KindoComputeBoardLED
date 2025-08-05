#include "LEDS.h"

uint8_t cup=0;
uint8_t gate=0;
uint8_t LED_Data_GATE[MAX_LED][4];
uint8_t LED_Data_CUP[MAX_LED][4];
uint8_t LED_Mod_CUP[MAX_LED][4];//for brightness
uint8_t LED_Mod_GATE[MAX_LED][4];//for brightness
uint8_t datasentflag1=0;
uint8_t datasentflag2=0;
uint8_t blue_brightness=0;
uint8_t green_brightness=0;
uint8_t red_brightness=0;
uint8_t white_brightness=0;
uint8_t blue_breathe_up = 0;
uint8_t green_breathe_up = 0;
uint8_t red_breathe_up = 0;
uint8_t white_breathe_up = 0;
void Set_LED_GATE(int LEDnum, int Red, int Green, int Blue)
{
	LED_Data_GATE[LEDnum][0] = LEDnum;
	LED_Data_GATE[LEDnum][1] = Green;
	LED_Data_GATE[LEDnum][2] = Red;
	LED_Data_GATE[LEDnum][3] = Blue;
}
void Set_LED_CUP(int LEDnum, int Red, int Green, int Blue)
{
	LED_Data_CUP[LEDnum][0] = LEDnum;
	LED_Data_CUP[LEDnum][1] = Green;
	LED_Data_CUP[LEDnum][2] = Red;
	LED_Data_CUP[LEDnum][3] = Blue;
}

void Set_Brightness_CUP (int brightness)  // 0-45
{
#if USE_BRIGHTNESS

	if (brightness > 45) brightness = 45;
	for (int i=0; i<MAX_LED; i++)
	{
		LED_Mod_CUP[i][0] = LED_Data_CUP[i][0];
		for (int j=1; j<4; j++)
		{
			float angle = 90-brightness;  // in degrees
			angle = angle*PI / 180;  // in rad
			LED_Mod_CUP[i][j] = (LED_Data_CUP[i][j])/(tan(angle));
		}
	}

#endif

}
void Set_Brightness_GATE (int brightness)  // 0-45
{
#if USE_BRIGHTNESS

	if (brightness > 45) brightness = 45;
	for (int i=0; i<MAX_LED; i++)
	{
		LED_Mod_GATE[i][0] = LED_Data_GATE[i][0];
		for (int j=1; j<4; j++)
		{
			float angle = 90-brightness;  // in degrees
			angle = angle*PI / 180;  // in rad
			LED_Mod_GATE[i][j] = (LED_Data_GATE[i][j])/(tan(angle));
		}
	}

#endif

}

void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{  
	
	if(cup==1)
	{
	cup=0;
	//	printf("Insde callback Functn");
	HAL_TIM_PWM_Stop_DMA(&htim3, TIM_CHANNEL_1);
	datasentflag1=1;
	}
	else if(gate==1)
	{
	gate=0;
	//printf("Insde callback Functn gate");
	HAL_TIM_PWM_Stop_DMA(&htim3, TIM_CHANNEL_2);
	datasentflag1=1;
		
	}

}
uint16_t pwmData[(24*MAX_LED)+50];//  50 for ws2812 , 250 for wb2813

void WS2812_Send(uint8_t Timno )
{
	uint32_t indx=0;
	uint32_t color;


	for (int i= 0; i<MAX_LED; i++)
	{
#if USE_BRIGHTNESS
		if(Timno==CUP)
	{
		color = ((LED_Mod_CUP[i][1]<<16) | (LED_Mod_CUP[i][2]<<8) | (LED_Mod_CUP[i][3]));
	}
	else if(Timno==GATE)
	{
				color = ((LED_Mod_GATE[i][1]<<16) | (LED_Mod_GATE[i][2]<<8) | (LED_Mod_GATE[i][3]));
	}
#else
		if(Timno==CUP)
	{
		color = ((LED_Data_CUP[i][1]<<16) | (LED_Data_CUP[i][2]<<8) | (LED_Data_CUP[i][3]));
	}
	else if(Timno==GATE)
	{
		color = ((LED_Data_GATE[i][1]<<16) | (LED_Data_GATE[i][2]<<8) | (LED_Data_GATE[i][3]));
	}
#endif

		for (int i=23; i>=0; i--)
		{
			if (color&(1<<i))
			{
				pwmData[indx] = 20-1;  // 2/3 of 105, 70 for ws2812 for ws2813 75
			}

			else pwmData[indx] = 10-1;  // 1/3 of 105 35 for ws2812 , 32 for wb2813

			indx++;
		}

	}

	for (int i=0; i<50; i++) //i<50 for ws2812 , 300 for wb2813
	{
		pwmData[indx] = 0;
		indx++;
	}
	if(Timno==CUP)
	{
	cup=1;
	HAL_TIM_PWM_Start_DMA(&htim3, TIM_CHANNEL_1, (uint32_t *)pwmData, indx);
	//while (datasentflag==0){};
	//printf("%d FLAG \r\n", datasentflag1);
	datasentflag1 = 0;
	}
	if(Timno==GATE)
	{
		gate=1;
		HAL_TIM_PWM_Start_DMA(&htim3, TIM_CHANNEL_2, (uint32_t *)pwmData, indx);
	//while (datasentflag==0){};
	//printf("%d FLAG \r\n", datasentflag2);
		datasentflag2 = 0;
	}
}

void BreatheWhite(void)
{
//for (int i=1; i<255; i=i+2)
//	  {
//			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1,i-1);
//			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3,i-1);
//			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4,i-1);
//			HAL_Delay (5);
//			
//	  }
//		for (int i=255; i>1; i=i-2)
//	  {
//		  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1,i-1);
//			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3,i-1);
//			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4,i-1);
//			HAL_Delay (5);
//	  }
//		HAL_Delay (150);
//	}
	blue_brightness=0;
	green_brightness=0;
	red_brightness=0;
	blue_breathe_up = 0;
	green_breathe_up = 0;
	red_breathe_up = 0;
	
	if(white_breathe_up==0)
	{
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1,white_brightness++);
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3,white_brightness);
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4,white_brightness);
		
		if(white_brightness>=255){
			white_breathe_up = 1;
		}
		HAL_Delay(1);
	
	}
	
	else
		{
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1,white_brightness--);
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3,white_brightness);
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4,white_brightness);
		if(white_brightness<=2)
		{
			white_breathe_up = 0;
		}
		HAL_Delay(1);
			
	}
}
	
	
void BreatheRed(void)
{
		blue_brightness=0;
		green_brightness=0;
 
		white_brightness=0;
		blue_breathe_up = 0;
		green_breathe_up = 0;
		white_breathe_up = 0;

	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3,1-1);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4,1-1);
//for (int i=1; i<255; i=i+2)
//	  {
//			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1,i-1);
//			
//			HAL_Delay (5);
//			
//	  }
//		for (int i=255; i>1; i=i-2)
//	  {
//		  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1,i-1);
//			
//			HAL_Delay (5);
//	  }
//		HAL_Delay (150);
//	}
	if(red_breathe_up==0)
	{
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1,red_brightness++);
		
		if(red_brightness>=255){
			red_breathe_up = 1;
		}
		HAL_Delay(1);
	}
	else
		{
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1,red_brightness--);
		if(red_brightness<=2)
		{
			red_breathe_up = 0;
		}
		HAL_Delay(1);
			
	}
}
	
	
void BreatheGreen(void)
{
		blue_brightness=0;
		red_brightness=0;
		white_brightness=0;
		blue_breathe_up = 0;
		red_breathe_up = 0;
		white_breathe_up = 0;
	
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1,1-1);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4,1-1);
//for (int i=1; i<255; i=i+2)
//	  {
//			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3,i-1);
//			
//			HAL_Delay (5);
//			
//	  }
//		for (int i=255; i>1; i=i-2)
//	  {
//			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3,i-1);
//			HAL_Delay (5);
//	  }
//		HAL_Delay (150);
//}
	
	if(green_breathe_up==0)
	{
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3,green_brightness++);
		if(green_brightness>=255){
			green_breathe_up = 1;
		}
		HAL_Delay(1);
	}
	else
		{
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3,green_brightness--);
		if(green_brightness<=2)
		{
			green_breathe_up = 0;
		}
			HAL_Delay(1);
	}
}

void BreatheBlue(void)
{
	
		green_brightness=0;
		red_brightness=0;
		white_brightness=0;
		green_breathe_up = 0;
		red_breathe_up = 0;
		white_breathe_up = 0;
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1,1-1);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3,1-1);
//for (int i=1; i<255; i=i+2)
//	  {
//			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4,i-1);
//			HAL_Delay (5);
//			
//	  }
//		for (int i=255; i>1; i=i-2)
//	  {
//			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4,i-1);
//			HAL_Delay (5);
//	  }
//		HAL_Delay (150);
	
	
//	if (breathing_up == true){
//  //Serial.println("hello_up");
//  FastLED.setBrightness(breathing_pattern++);
//  FastLED.show();
//  if(breathing_pattern>=5){          // breathing brightness 
//    breathing_up=false;
//    delay(200);
//  }
//}
//else{
//  //delay(1000);
//  //Serial.println("hello_down");
//  FastLED.setBrightness(breathing_pattern--);
//   FastLED.show();
//  if(breathing_pattern<=2){
//    breathing_up=true;
//    delay(200);
//    if(cyclotron_counter2>=5){
//      cyclotron_counter2++;
//      if(cyclotron_counter2>6){
//        cyclotron_counter2=0;
//    }
//}

//}
//}
	if(blue_breathe_up==0)
	{
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4,blue_brightness++);
		if(blue_brightness>=255){
			blue_breathe_up = 1;
		}
		HAL_Delay(1);
	}
	else
		{
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4,blue_brightness--);
		if(blue_brightness<=2)
		{
			blue_breathe_up = 0;
		}
	HAL_Delay(1);
	}
}
void Whiteon(void)
{		
		blue_brightness=0;
		green_brightness=0;
		red_brightness=0;
		white_brightness=0;
		blue_breathe_up = 0;
		green_breathe_up = 0;
		red_breathe_up = 0;
		white_breathe_up = 0;
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1,256-1);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3,256-1);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4,256-1);
	
}
void Redon(void)
{
		blue_brightness=0;
		green_brightness=0;
		red_brightness=0;
		white_brightness=0;
		blue_breathe_up = 0;
		green_breathe_up = 0;
		red_breathe_up = 0;
		white_breathe_up = 0;
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1,256-1);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3,1-1);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4,1-1);
	
}
void Greenon(void)
{
		blue_brightness=0;
		green_brightness=0;
		red_brightness=0;
		white_brightness=0;
		blue_breathe_up = 0;
		green_breathe_up = 0;
		red_breathe_up = 0;
		white_breathe_up = 0;
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1,1-1);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3,256-1);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4,1-1);
	
}
void Blueon(void)
{
		blue_brightness=0;
		green_brightness=0;
		red_brightness=0;
		white_brightness=0;
		blue_breathe_up = 0;
		green_breathe_up = 0;
		red_breathe_up = 0;
		white_breathe_up = 0;
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1,1-1);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3,1-1);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4,256-1);
	
}
void Alloff(void)
{
		blue_brightness=0;
		green_brightness=0;
		red_brightness=0;
		white_brightness=0;
		blue_breathe_up = 0;
		green_breathe_up = 0;
		red_breathe_up = 0;
		white_breathe_up = 0;
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1,1-1);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3,1-1);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4,1-1);
	
}
