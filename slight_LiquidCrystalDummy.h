// include guard
#ifndef slight_LiquidCristalDummy_h
#define slight_LiquidCristalDummy_h

// Includes Core Arduino functionality
#if ARDUINO < 100
#include <WProgram.h>
#else
#include <Arduino.h>
#endif

// include parrent class
#include "LiquidCrystal.h"

// forward declared dependencies
// http://www.cplusplus.com/forum/articles/10627/
// class LiquidCrystal;



class LiquidCrystalDummy : public Print {
	public:
		LiquidCrystalDummy(LiquidCrystal &lcd);

		void begin(uint8_t cols, uint8_t rows);
		void setCursor(uint8_t col, uint8_t row);
		size_t write( uint8_t u_Data );

		void printContent(Print &pOut);

	protected:
		uint8_t size_rows;
		uint8_t size_cols;
		uint8_t pos_row;
		uint8_t pos_col;
		char *displaydata;
		uint8_t displaydata_length;

		boolean ready;

		LiquidCrystal &lcd;

};

// end include guard
#endif
