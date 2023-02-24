/*!
    \file  lcd_log.c
    \brief this file provides all the LCD Log firmware functions
*/

/*
    Copyright (C) 2017 GigaDevice

    2017-02-10, V1.0.0, firmware for GD32F30x
*/

#include "lcd_log.h"
#include "usb_conf.h"
#include "usbh_usr.h"

extern uint16_t LINE;

/*!
    \brief      initialize the LCD Log module
    \param[in]  none
    \param[out] none
    \retval     none
*/
void lcd_log_init (void)
{
    lcd_clear(LCD_COLOR_BLACK);

    lcd_font_set(&font8x16);
}

/*!
    \brief      de-initialize the LCD Log module
    \param[in]  none
    \param[out] none
    \retval     none
*/
void lcd_log_deinit (void)
{
    /* no operation */
}

/*!
    \brief      display the application header (title) on the LCD screen 
    \param[in]  ptitle: pointer to the string to be displayed
    \param[in]  start_x: x location
    \param[out] none
    \retval     none
*/
void lcd_log_header_set (uint8_t *ptitle, uint16_t start_x)
{
    lcd_text_color_set(LCD_COLOR_BLUE);

    lcd_rectangle_fill(LCD_HEADER_X, LCD_HEADER_Y, LCD_FLAG_WIDTH, LCD_FLAG_HEIGHT, LCD_COLOR_BLUE);

    lcd_background_color_set(LCD_COLOR_BLUE);
    lcd_text_color_set(LCD_COLOR_RED);

    lcd_vertical_string_display(LCD_HEADER_LINE, start_x, ptitle);
}

/*!
    \brief      display the application footer (status) on the LCD screen
    \param[in]  pstatus: pointer to the string to be displayed
    \param[in]  start_x: x location
    \param[out] none
    \retval     none
*/
void lcd_log_footer_set (uint8_t *pstatus, uint16_t start_x)
{
    lcd_text_color_set(LCD_COLOR_BLUE);

    lcd_rectangle_fill(LCD_FOOTER_X, LCD_FOOTER_Y, LCD_FLAG_WIDTH, LCD_FLAG_HEIGHT, LCD_COLOR_BLUE);

    lcd_background_color_set(LCD_COLOR_BLUE);
    lcd_text_color_set(LCD_COLOR_RED);

    lcd_vertical_string_display(LCD_FOOTER_LINE, start_x, pstatus);
}

/*!
    \brief      clear the text zone
    \param[in]  start_x, start_y, end_x, end_y: zone location
    \param[out] none
    \retval     none
*/
void lcd_log_textzone_clear (uint16_t start_x,
                             uint16_t start_y,
                             uint16_t width,
                             uint16_t height)
{
    lcd_rectangle_fill(start_x, start_y, width, height,LCD_COLOR_BLACK);
}

/*!
    \brief      redirect the printf to the LCD
    \param[in]  pstr: pointer to string to be displayed
    \param[in]  len: string length
    \param[in]  char_color: string color
    \param[in]  back_color: back color
    \param[out] none
    \retval     none
*/
void lcd_log_print (uint8_t *pstr, 
                    uint16_t offset, 
                    uint16_t char_color, 
                    uint16_t back_color)
{
    LCD_LINE_LIMIT(LINE);

    lcd_text_color_set(char_color);
    lcd_background_color_set(back_color);

    lcd_vertical_string_display(LINE, offset, pstr);

    LCD_LINE_UPDATE(LINE);
}
