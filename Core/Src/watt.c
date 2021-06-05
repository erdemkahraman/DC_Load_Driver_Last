/*
 * watt.c
 *
 *  Created on: Feb 5, 2021
 *      Author: erdem
 */


#include "main.h"
#include <i2c-lcd.h>
#include <math.h>
#include "ssd1306.h"

float raw2voltage = 0, real2voltage = 0, resistor2=0 , x2 = 0  ,z2=0 , y2 , setwatt;

uint32_t data02;
uint32_t data12;
uint32_t data22;
uint32_t data32;
char yazi12[32] = " ";
char yazi22[32] = " ";
char yazi32[32] = " ";
char yazi42[32] = " ";
ADC_HandleTypeDef hadc1;
ADC_HandleTypeDef hadc3;
DAC_HandleTypeDef hdac;
float temp2 , vtemp2 , adcval2 ;


void watter(void)

{
	HAL_DAC_Start(&hdac, DAC_CHANNEL_1);
    HAL_ADC_Start(&hadc1);
    adcval2 = HAL_ADC_GetValue(&hadc1);
    vtemp2 = adcval2*0.806;
    temp2 = ((13.582 - sqrt((13.582*13.582)+(4*0.00433)*(2230.8-vtemp2)))/(2*-0.00433))+30;
    data22 = temp2;
    HAL_Delay(10);



    HAL_ADC_Start(&hadc3);
    if(HAL_ADC_PollForConversion(&hadc3, HAL_MAX_DELAY) == HAL_OK)
    {
    raw2voltage = HAL_ADC_GetValue(&hadc3);
    real2voltage = (raw2voltage*12.4100)/1000;
    }

    if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0))

    {
		  uint32_t time3=HAL_GetTick();
		  while(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0)){
			  if (HAL_GetTick()-time3 > 300){
				  time3=HAL_GetTick();
				  setwatt+=100;
				  HAL_Delay(5);
				  break;
	   }
	  if (HAL_GetTick()-time3 > 20) {
	   setwatt += 50;

	   HAL_Delay(100);
	   }
	   }
	   }


    if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_1)){
		  uint32_t time7=HAL_GetTick();
		  while(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_1)){
			  if (HAL_GetTick()-time7 > 300){
				  time7=HAL_GetTick();
				  setwatt-=100;
				  HAL_Delay(5);
				  break;
	   }
	   if (HAL_GetTick()-time7 > 20) {
	   setwatt -= 50;

	   HAL_Delay(100);
	   }
	   }
	   }



	  if(real2voltage < 1) (z2 = 0);


    z2 =  setwatt / real2voltage;

    y2 = z2*20;
    x2 = y2 /((3.3/4096)*1000);
    data12 = z2 - 1;
    if(data12>100) (data12 = 100);
    data32 = setwatt;
    if (setwatt<0)(setwatt=0);

    SSD1306_GotoXY (1, 1);
   		  sprintf(yazi42,"Watt|Curr %d            ",data12);
   		  SSD1306_Puts(yazi42,&Font_7x10,1);
   		  SSD1306_GotoXY(105,1);
   		  SSD1306_Puts("mA",&Font_7x10,1);
   		  sprintf(yazi32,"Temperature %d C    ",data22);
   		  SSD1306_GotoXY (1, 19);
   		  SSD1306_Puts(yazi32,&Font_7x10,1);
   		  sprintf(yazi12," %d       ",data32);
   		  SSD1306_GotoXY (1, 37);
   		  SSD1306_Puts(yazi12,&Font_16x26,1);
   		  SSD1306_GotoXY (87,37);
   		  SSD1306_Puts("mW   ", &Font_16x26,1);
   		  SSD1306_UpdateScreen();
   		  HAL_Delay(20);

   		  if(real2voltage < 1) (data12 = 0);

      HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, x2);






}

