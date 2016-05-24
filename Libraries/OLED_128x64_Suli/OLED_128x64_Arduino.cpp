/*
  SeeedOLED.cpp - SSD130x OLED Driver Library
  2011 Copyright (c) Seeed Technology Inc.  All right reserved.
  
  Author: Visweswara R
  
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.
  
  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.
  
  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "OLED_128x64_Suli.h"


// 8x8 Font ASCII 32 - 127 Implemented
// Users can modify this to support more characters(glyphs)
// BasicFont is placed in code memory.

// This font be freely used without any restriction(It is placed in public domain)


#if defined(ARDUINO)
const unsigned char BasicFont[][8] PROGMEM=
#else
const unsigned char BasicFont[][8] =
#endif
{
    {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
    {0x00,0x00,0x5F,0x00,0x00,0x00,0x00,0x00},
    {0x00,0x00,0x07,0x00,0x07,0x00,0x00,0x00},
    {0x00,0x14,0x7F,0x14,0x7F,0x14,0x00,0x00},
    {0x00,0x24,0x2A,0x7F,0x2A,0x12,0x00,0x00},
    {0x00,0x23,0x13,0x08,0x64,0x62,0x00,0x00},
    {0x00,0x36,0x49,0x55,0x22,0x50,0x00,0x00},
    {0x00,0x00,0x05,0x03,0x00,0x00,0x00,0x00},
    {0x00,0x1C,0x22,0x41,0x00,0x00,0x00,0x00},
    {0x00,0x41,0x22,0x1C,0x00,0x00,0x00,0x00},
    {0x00,0x08,0x2A,0x1C,0x2A,0x08,0x00,0x00},
    {0x00,0x08,0x08,0x3E,0x08,0x08,0x00,0x00},
    {0x00,0xA0,0x60,0x00,0x00,0x00,0x00,0x00},
    {0x00,0x08,0x08,0x08,0x08,0x08,0x00,0x00},
    {0x00,0x60,0x60,0x00,0x00,0x00,0x00,0x00},
    {0x00,0x20,0x10,0x08,0x04,0x02,0x00,0x00},
    {0x00,0x3E,0x51,0x49,0x45,0x3E,0x00,0x00},
    {0x00,0x00,0x42,0x7F,0x40,0x00,0x00,0x00},
    {0x00,0x62,0x51,0x49,0x49,0x46,0x00,0x00},
    {0x00,0x22,0x41,0x49,0x49,0x36,0x00,0x00},
    {0x00,0x18,0x14,0x12,0x7F,0x10,0x00,0x00},
    {0x00,0x27,0x45,0x45,0x45,0x39,0x00,0x00},
    {0x00,0x3C,0x4A,0x49,0x49,0x30,0x00,0x00},
    {0x00,0x01,0x71,0x09,0x05,0x03,0x00,0x00},
    {0x00,0x36,0x49,0x49,0x49,0x36,0x00,0x00},
    {0x00,0x06,0x49,0x49,0x29,0x1E,0x00,0x00},
    {0x00,0x00,0x36,0x36,0x00,0x00,0x00,0x00},
    {0x00,0x00,0xAC,0x6C,0x00,0x00,0x00,0x00},
    {0x00,0x08,0x14,0x22,0x41,0x00,0x00,0x00},
    {0x00,0x14,0x14,0x14,0x14,0x14,0x00,0x00},
    {0x00,0x41,0x22,0x14,0x08,0x00,0x00,0x00},
    {0x00,0x02,0x01,0x51,0x09,0x06,0x00,0x00},
    {0x00,0x32,0x49,0x79,0x41,0x3E,0x00,0x00},
    {0x00,0x7E,0x09,0x09,0x09,0x7E,0x00,0x00},
    {0x00,0x7F,0x49,0x49,0x49,0x36,0x00,0x00},
    {0x00,0x3E,0x41,0x41,0x41,0x22,0x00,0x00},
    {0x00,0x7F,0x41,0x41,0x22,0x1C,0x00,0x00},
    {0x00,0x7F,0x49,0x49,0x49,0x41,0x00,0x00},
    {0x00,0x7F,0x09,0x09,0x09,0x01,0x00,0x00},
    {0x00,0x3E,0x41,0x41,0x51,0x72,0x00,0x00},
    {0x00,0x7F,0x08,0x08,0x08,0x7F,0x00,0x00},
    {0x00,0x41,0x7F,0x41,0x00,0x00,0x00,0x00},
    {0x00,0x20,0x40,0x41,0x3F,0x01,0x00,0x00},
    {0x00,0x7F,0x08,0x14,0x22,0x41,0x00,0x00},
    {0x00,0x7F,0x40,0x40,0x40,0x40,0x00,0x00},
    {0x00,0x7F,0x02,0x0C,0x02,0x7F,0x00,0x00},
    {0x00,0x7F,0x04,0x08,0x10,0x7F,0x00,0x00},
    {0x00,0x3E,0x41,0x41,0x41,0x3E,0x00,0x00},
    {0x00,0x7F,0x09,0x09,0x09,0x06,0x00,0x00},
    {0x00,0x3E,0x41,0x51,0x21,0x5E,0x00,0x00},
    {0x00,0x7F,0x09,0x19,0x29,0x46,0x00,0x00},
    {0x00,0x26,0x49,0x49,0x49,0x32,0x00,0x00},
    {0x00,0x01,0x01,0x7F,0x01,0x01,0x00,0x00},
    {0x00,0x3F,0x40,0x40,0x40,0x3F,0x00,0x00},
    {0x00,0x1F,0x20,0x40,0x20,0x1F,0x00,0x00},
    {0x00,0x3F,0x40,0x38,0x40,0x3F,0x00,0x00},
    {0x00,0x63,0x14,0x08,0x14,0x63,0x00,0x00},
    {0x00,0x03,0x04,0x78,0x04,0x03,0x00,0x00},
    {0x00,0x61,0x51,0x49,0x45,0x43,0x00,0x00},
    {0x00,0x7F,0x41,0x41,0x00,0x00,0x00,0x00},
    {0x00,0x02,0x04,0x08,0x10,0x20,0x00,0x00},
    {0x00,0x41,0x41,0x7F,0x00,0x00,0x00,0x00},
    {0x00,0x04,0x02,0x01,0x02,0x04,0x00,0x00},
    {0x00,0x80,0x80,0x80,0x80,0x80,0x00,0x00},
    {0x00,0x01,0x02,0x04,0x00,0x00,0x00,0x00},
    {0x00,0x20,0x54,0x54,0x54,0x78,0x00,0x00},
    {0x00,0x7F,0x48,0x44,0x44,0x38,0x00,0x00},
    {0x00,0x38,0x44,0x44,0x28,0x00,0x00,0x00},
    {0x00,0x38,0x44,0x44,0x48,0x7F,0x00,0x00},
    {0x00,0x38,0x54,0x54,0x54,0x18,0x00,0x00},
    {0x00,0x08,0x7E,0x09,0x02,0x00,0x00,0x00},
    {0x00,0x18,0xA4,0xA4,0xA4,0x7C,0x00,0x00},
    {0x00,0x7F,0x08,0x04,0x04,0x78,0x00,0x00},
    {0x00,0x00,0x7D,0x00,0x00,0x00,0x00,0x00},
    {0x00,0x80,0x84,0x7D,0x00,0x00,0x00,0x00},
    {0x00,0x7F,0x10,0x28,0x44,0x00,0x00,0x00},
    {0x00,0x41,0x7F,0x40,0x00,0x00,0x00,0x00},
    {0x00,0x7C,0x04,0x18,0x04,0x78,0x00,0x00},
    {0x00,0x7C,0x08,0x04,0x7C,0x00,0x00,0x00},
    {0x00,0x38,0x44,0x44,0x38,0x00,0x00,0x00},
    {0x00,0xFC,0x24,0x24,0x18,0x00,0x00,0x00},
    {0x00,0x18,0x24,0x24,0xFC,0x00,0x00,0x00},
    {0x00,0x00,0x7C,0x08,0x04,0x00,0x00,0x00},
    {0x00,0x48,0x54,0x54,0x24,0x00,0x00,0x00},
    {0x00,0x04,0x7F,0x44,0x00,0x00,0x00,0x00},
    {0x00,0x3C,0x40,0x40,0x7C,0x00,0x00,0x00},
    {0x00,0x1C,0x20,0x40,0x20,0x1C,0x00,0x00},
    {0x00,0x3C,0x40,0x30,0x40,0x3C,0x00,0x00},
    {0x00,0x44,0x28,0x10,0x28,0x44,0x00,0x00},
    {0x00,0x1C,0xA0,0xA0,0x7C,0x00,0x00,0x00},
    {0x00,0x44,0x64,0x54,0x4C,0x44,0x00,0x00},
    {0x00,0x08,0x36,0x41,0x00,0x00,0x00,0x00},
    {0x00,0x00,0x7F,0x00,0x00,0x00,0x00,0x00},
    {0x00,0x41,0x36,0x08,0x00,0x00,0x00,0x00},
    {0x00,0x02,0x01,0x01,0x02,0x01,0x00,0x00},
    {0x00,0x02,0x05,0x05,0x02,0x00,0x00,0x00}
};


void *__I2C_Device;

uint8 addressingMode = 0;

void oled_128x64_init(void * I2C_Device)
{
    __I2C_Device = I2C_Device;
    
    suli_i2c_init(__I2C_Device);
    oled_128x64_cmd(SeeedOLED_Display_Off_Cmd);     //display off
    suli_delay_ms(5);
    oled_128x64_cmd(SeeedOLED_Display_On_Cmd);     //display on
    suli_delay_ms(5);
    oled_128x64_cmd(SeeedOLED_Normal_Display_Cmd);  //Set Normal Display (default)
}

// send command
void oled_128x64_cmd(unsigned char command)
{
    uint8 dta[2] = {SeeedOLED_Command_Mode, command};
    suli_i2c_write(__I2C_Device, SeeedOLED_Address, dta, 2);
}

// send data
void oled_128x64_dta(unsigned char Data)
{
    uint8 dta[2] = {SeeedOLED_Data_Mode, Data};
    suli_i2c_write(__I2C_Device, SeeedOLED_Address, dta, 2);
}

void oled_128x64_brightness(unsigned char Brightness)
{
    oled_128x64_cmd(SeeedOLED_Set_Brightness_Cmd);
    oled_128x64_cmd(Brightness);
}

// horizontal mode
void oled_128x64_hmode()
{
    addressingMode = HORIZONTAL_MODE;
    oled_128x64_cmd(0x20);             //set addressing mode
    oled_128x64_cmd(0x00);             //set horizontal addressing mode
}

// page mode
void oled_128x64_pagemode()
{
    addressingMode = PAGE_MODE;
    oled_128x64_cmd(0x20);             //set addressing mode
    oled_128x64_cmd(0x02);             //set page addressing mode
}

// 
void oled_128x64_XY(unsigned char Row, unsigned char Column)
{
    oled_128x64_cmd(0xB0 + Row);             //set page address
    oled_128x64_cmd(0x00 + (8*Column & 0x0F));     //set column lower address
    oled_128x64_cmd(0x10 + ((8*Column>>4)&0x0F));     //set column higher address
}

//
void oled_128x64_clear()
{
    unsigned char i,j;
    oled_128x64_cmd(SeeedOLED_Display_Off_Cmd);     //display off
    for(j=0;j<8;j++)
    {
        oled_128x64_XY(j,0);
        {
            for(i=0;i<16;i++)  //clear all columns
            {
                oled_128x64_char(' ');
            }
        }
    }
    oled_128x64_cmd(SeeedOLED_Display_On_Cmd);     //display on
    oled_128x64_XY(0,0);
}

void oled_128x64_char(unsigned char C)
{
    if(C < 32 || C > 127) //Ignore non-printable ASCII characters. This can be modified for multilingual font.
    {
        C=' '; //Space
    }
    unsigned char i=0;
    for(i=0;i<8;i++)
    {
        //read bytes from code memory
#if defined(ARDUINO)
        oled_128x64_dta(pgm_read_byte(&BasicFont[C-32][i])); //font array starts at 0, ASCII starts at 32. Hence the translation
#else
        oled_128x64_dta(BasicFont[C-32][i]);
#endif
    }
}

void oled_128x64_string(const char *String)
{
    unsigned char i=0;
    while(String[i])
    {
        oled_128x64_char(String[i]);
        i++;
    }
}

unsigned char oled_128x64_num(long long_num)
{
    unsigned char char_buffer[10]="";
    unsigned char i = 0;
    unsigned char f = 0;

    if (long_num < 0)
    {
        f=1;
        oled_128x64_char('-');
        long_num = -long_num;
    }
    else if (long_num == 0)
    {
        f=1;
        oled_128x64_char('0');
        return f;
    }

    while (long_num > 0)
    {
        char_buffer[i++] = long_num % 10;
        long_num /= 10;
    }

    f=f+i;
    for(; i > 0; i--)
    {
        oled_128x64_char('0'+ char_buffer[i - 1]);
    }
    return f;

}

unsigned char oled_128x64_float_decimal(float floatNumber,unsigned char decimal)
{
    unsigned int temp=0;
    float decy=0.0;
    float rounding = 0.5;
    unsigned char f=0;
    if(floatNumber<0.0)
    {
        oled_128x64_string("-");
        floatNumber = -floatNumber;
        f +=1;
    }
    for (unsigned char i=0; i<decimal; ++i)
    {
        rounding /= 10.0;
    }
    floatNumber += rounding;

    temp = floatNumber;
    f += oled_128x64_num(temp);
    if(decimal>0)
    {
        oled_128x64_char('.');
        f +=1;
    }
    decy = floatNumber-temp;//decimal part,
    for(unsigned char i=0;i<decimal;i++)//4
    {
        decy *=10;// for the next decimal
        temp = decy;//get the decimal
        oled_128x64_num(temp);
        decy -= temp;
    }
    f +=decimal;
    return f;
}

unsigned char oled_128x64_float(float floatNumber)
{
    unsigned char decimal=2;
    unsigned int temp=0;
    float decy=0.0;
    float rounding = 0.5;
    unsigned char f=0;
    if(floatNumber<0.0)
    {
        oled_128x64_string("-");
        floatNumber = -floatNumber;
        f +=1;
    }
    for (unsigned char i=0; i<decimal; ++i)
    {
        rounding /= 10.0;
    }
    floatNumber += rounding;

    temp = floatNumber;
    f += oled_128x64_num(temp);
    if(decimal>0)
    {
        oled_128x64_char('.');
        f +=1;
    }
    decy = floatNumber-temp;//decimal part,
    for(unsigned char i=0;i<decimal;i++)//4
    {
        decy *=10;// for the next decimal
        temp = decy;//get the decimal
        oled_128x64_num(temp);
        decy -= temp;
    }
    f +=decimal;
    return f;
}


/*
 * set Horizontal Scroll Properties
 */
void oled_128x64_hsp(bool direction,unsigned char startPage, unsigned char endPage, unsigned char scrollSpeed)
{

    if(Scroll_Right == direction)
    {
        //Scroll Right
        oled_128x64_cmd(0x26);
    }
    else
    {
        //Scroll Left
        oled_128x64_cmd(0x27);

    }
    oled_128x64_cmd(0x00);
    oled_128x64_cmd(startPage);
    oled_128x64_cmd(scrollSpeed);
    oled_128x64_cmd(endPage);
    oled_128x64_cmd(0x00);
    oled_128x64_cmd(0xFF);
}

/*
 * active scroll
 */
void oled_128x64_active_scroll()
{
    oled_128x64_cmd(SeeedOLED_Activate_Scroll_Cmd);
}

void oled_128x64_deactive_scroll()
{
    oled_128x64_cmd(SeeedOLED_Dectivate_Scroll_Cmd);
}

void oled_128x64_normal_display()
{
    oled_128x64_cmd(SeeedOLED_Normal_Display_Cmd);
}

void oled_128x64_inversel_display()
{
    oled_128x64_cmd(SeeedOLED_Inverse_Display_Cmd);
}