/*
 * Copyright 2012 BrewPi/Elco Jacobs.
 *
 * This file is part of BrewPi.
 * 
 * BrewPi is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * BrewPi is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with BrewPi.  If not, see <http://www.gnu.org/licenses/>.
 */

/* This is an adaptation of the Arduino LiquidCrystal library for the 
 * NHD-0420DZW-AY5-ND OLED display, made by NewHaven. The display should be HD44780 compatible but isn't.
 * Differences are some of the control commands (cursor on/off), language setting and especially initialization sequence.
 */ 

#ifndef OLEDFourBit_h
#define OLEDFourBit_h

#include <inttypes.h>
#include "Print.h"

// commands
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x28
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

// flags for function set
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_ENGLISH_JAPANESE   0x00
#define LCD_WESTERN_EUROPEAN_1 0x01
#define LCD_ENGLISH_RUSSIAN    0x02
#define LCD_WESTERN_EUROPEAN_2 0x03


class OLEDFourBit : public Print {
	public:
	OLEDFourBit(){};

	void init(uint8_t rs, uint8_t rw, uint8_t enable,
	uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7);

	void begin(uint8_t cols, uint8_t rows);

	void clear();
	void home();

	void noDisplay();
	void display();
	void noBlink();
	void blink();
	void noCursor();
	void cursor();
	void scrollDisplayLeft();
	void scrollDisplayRight();
	void leftToRight();
	void rightToLeft();
	void autoscroll();
	void noAutoscroll();

	void createChar(uint8_t, uint8_t[]);
	void setCursor(uint8_t, uint8_t);

	virtual size_t write(uint8_t);

	size_t print_P(const char * str) { // print a string stored in PROGMEM
		char buf[21]; // create buffer in RAM
		strlcpy_P(buf, str, 20); // copy string to RAM
		return print(buf); // print from RAM
	}

	void command(uint8_t);
	char readChar(void);

	using Print::write;

	private:
	void send(uint8_t, uint8_t);
	void write4bits(uint8_t);
	void pulseEnable();
	void waitBusy();

	uint8_t _rs_pin; // LOW: command.  HIGH: character.
	uint8_t _rw_pin; // LOW: write to oled.  HIGH: read from oled.
	uint8_t _enable_pin; // activated by a HIGH pulse.
	uint8_t _busy_pin;
	uint8_t _data_pins[4];

	uint8_t _displayfunction;
	uint8_t _displaycontrol;
	uint8_t _displaymode;
	uint8_t _initialized;
	uint8_t _currline;
	uint8_t _numlines;
};

#endif
