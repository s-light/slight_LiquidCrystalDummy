
// Include yourselfs header file
#include "slight_LiquidCrystalDummy.h"

// Includes Core Arduino functionality
#if ARDUINO < 100
#include <WProgram.h>
#else
#include <Arduino.h>
#endif


LiquidCrystalDummy :: LiquidCrystalDummy(
    LiquidCrystal &p_lcd
) :
    lcd(p_lcd)
{
    ready = false;
}

/**********************************************************************/
/** functions                                                        **/
/**********************************************************************/

/************************************************/
/**  public                                    **/
/************************************************/

void LiquidCrystalDummy::begin(uint8_t cols, uint8_t rows) {
    if (ready == false) {
        // call lcd begin
        lcd.begin(cols, rows);

    	size_cols = cols;
    	size_rows = rows;
        displaydata_length = sizeof(char) * size_rows * size_cols;
    	displaydata = (char *)malloc(displaydata_length);
        memset(displaydata, ' ', displaydata_length);
        ready = true;
    }
}

void LiquidCrystalDummy::setCursor(uint8_t col, uint8_t row) {
    lcd.setCursor(col, row);
	pos_col = col;
	pos_row = row;
}

size_t LiquidCrystalDummy::write( uint8_t u_Data ) {
    if (ready) {
        lcd.write(u_Data);
        displaydata[pos_col + (pos_row * size_cols)] = u_Data;
        // move cursor to next col
        pos_col = pos_col +1;
        if (pos_col >= size_cols) {
            pos_col = size_cols-1;
        }
	    return 0x01;
    } else {
        return 0x00;
    }
}

void LiquidCrystalDummy::createChar(uint8_t location, uint8_t charmap[]) {
    if (ready) {
        lcd.createChar(location, charmap);
    }
}

void LiquidCrystalDummy::printContent(Print &pOut) {
    if (ready) {
        // print top border
        pOut.print("#");
        for (size_t indexCol = 0; indexCol < size_cols+2; indexCol++) {
            if (indexCol == pos_col) {
                pOut.print("*");
            } else {
                pOut.print("-");
            }
        }
        pOut.println("#");

        // spacer
        pOut.print("|");
        for (size_t indexCol = 0; indexCol < size_cols+2; indexCol++) {
            pOut.print(" ");
        }
        pOut.println("|");

        char *p_displaydataStart = displaydata;
        for (size_t indexRow = 0; indexRow < size_rows; indexRow++) {
            // print line pre
            if (indexRow == pos_row) {
                pOut.print("* ");
            } else {
                pOut.print("| ");
            }

            pOut.write(p_displaydataStart, size_cols);
            p_displaydataStart = p_displaydataStart + size_cols;

            pOut.println(" |");
        }

        // spacer
        pOut.print("|");
        for (size_t indexCol = 0; indexCol < size_cols+2; indexCol++) {
            pOut.print(" ");
        }
        pOut.println("|");

        // print bottom border
        pOut.print("#");
        for (size_t indexCol = 0; indexCol < size_cols+2; indexCol++) {
            pOut.print("-");
        }
        pOut.println("#");
    }
}
