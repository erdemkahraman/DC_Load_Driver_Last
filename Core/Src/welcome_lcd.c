/*
 * welcome_lcd.c
 *
 *  Created on: 31 Oca 2021
 *      Author: erdem
 */
#include <ssd1306.h>
#include <i2c-lcd.h>

void welcome_lcd(void)
{
  lcd_init ();
  SSD1306_Init ();
  SSD1306_Fill(SSD1306_COLOR_BLACK);
  SSD1306_UpdateScreen();
  SSD1306_GotoXY (10, 18);
  SSD1306_Puts ("WELCOME", &Font_11x18, 1);
  SSD1306_GotoXY(2,45);
  SSD1306_Puts("   ANTSIS ELC.",&Font_7x10,1);
  SSD1306_UpdateScreen();
  HAL_Delay(500);
  SSD1306_Fill (0);
  SSD1306_UpdateScreen(); //display
  SSD1306_GotoXY (0, 0);
}
