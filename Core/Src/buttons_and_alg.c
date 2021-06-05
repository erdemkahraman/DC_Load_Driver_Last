#include <ssd1306.h>
#include <i2c-lcd.h>
#include <math.h>

float x = 0 , y = 0 , z , temp , vtemp , rawvoltage , realvoltage , resistor;
char yazi1[32] = " ";
char yazi2[32] = " ";
char yazi3[32] = " ";
char yazi4[32] = " ";
uint32_t data;
uint32_t data1;
uint32_t data2;
uint32_t data3;
uint32_t adcval;


DAC_HandleTypeDef hdac;
ADC_HandleTypeDef hadc1;
ADC_HandleTypeDef hadc3;

void mainalgor(void)
{

	 HAL_DAC_Start(&hdac, DAC_CHANNEL_1);
	 HAL_ADC_Start(&hadc1);
	 adcval = HAL_ADC_GetValue(&hadc1);
	 vtemp = adcval*0.806;
	 temp = ((13.582 - sqrt((13.582*13.582)+(4*0.00433)*(2230.8-vtemp)))/(2*-0.00433))+30;
	 data2 = temp;
	 HAL_Delay(10);


	 HAL_ADC_Start(&hadc3);

	 		  if(HAL_ADC_PollForConversion(&hadc3, 1) == HAL_OK)
	 		  {
	 			  rawvoltage = HAL_ADC_GetValue(&hadc3);
	 			  realvoltage = (rawvoltage*(3.236/4095))*(50/3.236);
	 			  resistor = realvoltage/(z/1000);
	 			  // if (z = 0) (resistor = 0);
	 			  data3 = resistor;

	 		  }
	 		  HAL_Delay(10);



	 		 if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0)){
	 		 		  uint32_t time1=HAL_GetTick();
	 		 		  while(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0)){
	 		 			  if (HAL_GetTick()-time1 > 300){
	 		 				  time1=HAL_GetTick();
	 		 				  z+=10;
	 		 				  HAL_Delay(5);
	 		 				  break;
	 		 	   }
	 		 	  if (HAL_GetTick()-time1 > 20) {
	 		 	   z += 1;

	 		 	   HAL_Delay(100);
	 		 	   }
	 		 	   }
	 		 	   }

	 		 if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_1)){
	 					  uint32_t time2=HAL_GetTick();
	 					  while(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_1)){
	 						  if (HAL_GetTick()-time2 > 300){
	 							  time2=HAL_GetTick();
	 							  z-=10;
	 							  HAL_Delay(5);
	 							  break;
	 				   }
	 				 if (HAL_GetTick()-time2 > 20) {
	 				   z -= 1;

	 				   HAL_Delay(100);
	 				   }
	 				   }
	 				   }

	 		y = z*20;
	 		x = y/((3.3/4096)*1000);

	 		HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, x);

	 		data1 = z;

	 		if(z>100) (z=100);
	 		if(x>4095) (x=4095);
	 		if(z<0)(z=0);

	 		SSD1306_GotoXY (1, 1);

	 			  sprintf(yazi4,"Curr| Res %d          ",data3);
	 			  SSD1306_Puts(yazi4,&Font_7x10,1);
	 			  SSD1306_GotoXY(105,1);
	 			  SSD1306_Puts("ohm",&Font_7x10,1);

	 			  sprintf(yazi3,"Temperature %d C        ",data2);
	 			  SSD1306_GotoXY (1, 19);
	 			  SSD1306_Puts(yazi3,&Font_7x10,1);

	 			  sprintf(yazi1," %d         ",data1);
	 			  SSD1306_GotoXY (1, 37);
	 			  SSD1306_Puts(yazi1,&Font_16x26,1);

	 			  SSD1306_GotoXY (87,37);
	 			  SSD1306_Puts("mA  ", &Font_16x26,1);
	 			  SSD1306_UpdateScreen();

}
