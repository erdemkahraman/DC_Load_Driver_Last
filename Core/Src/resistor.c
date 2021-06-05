/*
 * resistor.c
 *
 *  Created on: Feb 4, 2021
 *      Author: erdem
 */
#include "main.h"
#include <i2c-lcd.h>
#include <math.h>
#include "ssd1306.h"

//#include "buttons_and_alg.h"
float raw1voltage = 0, real1voltage = 0, resistor1=1 , x1 = 0  ,z1=1, resistor1def;
float y3;
uint32_t data01;
uint32_t data11;
uint32_t data21;
uint32_t data31;
char yazi11[32] = " ";
char yazi21[32] = " ";
char yazi31[32] = " ";
char yazi41[32] = " ";
ADC_HandleTypeDef hadc1;
ADC_HandleTypeDef hadc3;
DAC_HandleTypeDef hdac;
float temp1 , vtemp1 , adcval1 ;


void resistorr(void)

{
	HAL_DAC_Start(&hdac, DAC_CHANNEL_1);
    HAL_ADC_Start(&hadc1);
    adcval1 = HAL_ADC_GetValue(&hadc1);
    vtemp1 = adcval1*0.806;
    temp1 = ((13.582 - sqrt((13.582*13.582)+(4*0.00433)*(2230.8-vtemp1)))/(2*-0.00433))+30;
    data21 = temp1;

    	 HAL_Delay(10);



		HAL_ADC_Start(&hadc3);
		  if(HAL_ADC_PollForConversion(&hadc3, HAL_MAX_DELAY) == HAL_OK)
		  {
			  raw1voltage = HAL_ADC_GetValue(&hadc3);
			  real1voltage = (raw1voltage*12.4100)/1000;
			  if (z1 = 0) (resistor1 = 0);


		  }
		  HAL_Delay(10);


		  if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0))
		  {
		 			  uint32_t time5=HAL_GetTick();
		 			  while(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0)){
		 				  if (HAL_GetTick()-time5 > 300){
		 					  time5=HAL_GetTick();
		 					  resistor1+=50;
		 					  HAL_Delay(5);
		 					  break;
		 		   }
		 		 if (HAL_GetTick()-time5 > 20) {
		 		   resistor1 += 1;

		 		   HAL_Delay(100);
		 		   }
		 		   }
		 		   }


		  if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_1)){
		 			  uint32_t time4=HAL_GetTick();
		 			  while(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_1)){
		 				  if (HAL_GetTick()-time4 > 300){
		 					  time4=HAL_GetTick();
		 					  resistor1 -= 50;
		 					  HAL_Delay(5);
		 					  break;
		 		   }
		 		   if (HAL_GetTick()-time4 > 20){
		 		   resistor1 -= 1;

		 		   HAL_Delay(100);
		 		   }
		 		   }
		 		   }


		  z1 = (real1voltage / resistor1)*1000;
		  //resistor1def = (real1voltage/z1)*100;
		  data31 = resistor1;
		  data11 = z1;

		  if(z1>100) (z1=100);
		  if(data11>100) (data11=100);

		  SSD1306_GotoXY (1, 1);
		  sprintf(yazi41,"Res| Curr %d            ",data11);
		  SSD1306_Puts(yazi41,&Font_7x10,1);
		  SSD1306_GotoXY(105,1);
		  SSD1306_Puts("mA",&Font_7x10,1);
		  sprintf(yazi31,"Temperature %d C    ",data21);
		  SSD1306_GotoXY (1, 19);
		  SSD1306_Puts(yazi31,&Font_7x10,1);
		  sprintf(yazi11,"%d       ",data31);
		  SSD1306_GotoXY (1, 37);
		  SSD1306_Puts(yazi11,&Font_16x26,1);
		  SSD1306_GotoXY (75,37);
		  SSD1306_Puts("ohm  ", &Font_16x26,1);
		  SSD1306_UpdateScreen();
		  HAL_Delay(20);

		  if(resistor1<1) (resistor1=1);
		  if(z1<0) (z1=0);


		  // z1 mA cinsinden değer bize voltaj lazım, resistor belli

		  y3 = z1*20;

		  x1 = y3 /((3.3/4096)*1000);

		  if(x1>4095) (x1 = 4095);
		  if(z1>100) (z1=100);

		  HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, x1);

		 }




