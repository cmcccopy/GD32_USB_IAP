/*!
    \file  lcd_font.h
    \brief the header file of LCD font
*/

/*
    Copyright (C) 2017 GigaDevice

    2015-07-15, V1.0.0, firmware for GD32F20x
    2017-06-05, V2.0.0, firmware for GD32F20x
*/

#ifndef LCD_FONTS_H
#define LCD_FONTS_H

#include <stdint.h>

typedef struct {
    const uint16_t *table;

    uint16_t width;
    uint16_t height;
} font_struct;

typedef struct 
{
    unsigned char index[3];
    char mask[32];
} typefont_GB162;

typedef struct 
{
    unsigned char index[3];
    char mask[72];
} typefont_GB242;

#define hz16_num   100
#define hz24_num   100

extern font_struct font16x24;
extern font_struct font12x12;
extern font_struct font8x16;
extern font_struct font8x12;
extern font_struct font8x8;

extern const unsigned char ASCII16[];
extern const unsigned char sz32[];

extern const typefont_GB162 hz16[];
extern const typefont_GB242 hz24[];

#define LINE(x) ((x) * (((font_struct *)lcd_font_get())->height))

#endif /* LCD_FONTS_H */

