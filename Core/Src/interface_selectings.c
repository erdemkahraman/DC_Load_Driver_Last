/*
 * interface_selectings.c
 *
 *  Created on: 8 Şub 2021
 *      Author: erdem
 */

#include "main.h"
#include "ssd1306.h"
#include <i2c-lcd.h>

float setmode1 = 1;
uint32_t button=0;

void interface(void)

{
	  SSD1306_GotoXY (1,1);
	  SSD1306_Puts ("SELECT A MODE",&Font_7x10,1);
	  SSD1306_GotoXY(1,19);
	  SSD1306_Puts("1-Cur 2-Res 3-Watt",&Font_7x10,1);
	  SSD1306_UpdateScreen();
}

void selecting(void)
{

	  // SSD1306_Fill(SSD1306_COLOR_BLACK);
	  // SSD1306_UpdateScreen();
	   if(setmode1>3)(setmode1=3);
	   if(setmode1<1)(setmode1=1);
		  if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0))
		  {
			  setmode1+=1;
			  HAL_Delay(200);
		  }

		  if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_1))
		  {
			  setmode1-=1;
			  HAL_Delay(200);
		  }

		  if(HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_13))  {(button=1); HAL_Delay(200);}
		  else{(button=0); }


		  if(setmode1==1)
		  	  {
		  		  SSD1306_GotoXY (1,1);
		  		  SSD1306_Puts ("SELECT A MODE          ",&Font_7x10,1);
		  		  SSD1306_GotoXY(1,19);
		  		  SSD1306_Puts("1-Cur 2-Res 3-Watt",&Font_7x10,1);
		  		  SSD1306_GotoXY(1,30);
		  		  SSD1306_Puts("                  ",&Font_7x10,1);
		  		  SSD1306_GotoXY(1,40);
		  		  SSD1306_Puts(" ^                ",&Font_11x18,1);
		  		  SSD1306_UpdateScreen();



		  if(setmode1==1 && button == 1)

			  {
				  while(setmode1==1)
				  {
				  mainalgor();

				  if(HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_13)==GPIO_PIN_SET)

					  {
					  HAL_Delay(200);
					  setmode1 = 0;

					  }
				  }


			  }}

		  if (setmode1==2)
		  	  {
		  		  SSD1306_GotoXY (1,1);
		  		  SSD1306_Puts ("SELECT A MODE         ",&Font_7x10,1);
		  		  SSD1306_GotoXY(1,19);
		  		  SSD1306_Puts("1-Cur 2-Res 3-Watt",&Font_7x10,1);
		  		  SSD1306_GotoXY(1,30);
		  		  SSD1306_Puts("                   ",&Font_7x10,1);
		  		  SSD1306_GotoXY(1,40);
		  		  SSD1306_Puts("     ^           ",&Font_11x18,1);
	      		  SSD1306_UpdateScreen();

		  	  if(setmode1==2 && button == 1)

		  	  {

		  		  while(setmode1==2)
		  				  {
		  				  resistorr();

		  				  if(HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_13)==GPIO_PIN_SET)

		  					  {
		  					HAL_Delay(200);
		  					  setmode1=0;

		  					  }
		  				  }

		  	  }}

		  if (setmode1==3)
		  	  {

		  		  SSD1306_GotoXY (1,1);
		  		  SSD1306_Puts ("SELECT A MODE         ",&Font_7x10,1);
		  		  SSD1306_GotoXY(1,19);
		  		  SSD1306_Puts("1-Cur 2-Res 3-Watt",&Font_7x10,1);
		  		  SSD1306_GotoXY(1,30);
		  		  SSD1306_Puts("                  ",&Font_7x10,1);
		  		  SSD1306_GotoXY(1,40);
		  		  SSD1306_Puts("         ^          ",&Font_11x18,1);
		  		  SSD1306_UpdateScreen();

		  	  if(setmode1==3 && button == 1)

		  	  {
		  		 while(setmode1==3)
		  		 {
		  			watter();


	                if(HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_13)==GPIO_PIN_SET)

		  			{

	                	HAL_Delay(200);
	                	setmode1=0;

		  			}
		  			}


		  	  }}
}
