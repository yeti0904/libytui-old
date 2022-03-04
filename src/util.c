#include "_components.h"
#include "util.h"
#include "colours.h"

uint8_t YTUI_Util_ColourCodeToANSI(uint8_t colourCode, bool foreground) {
	if (foreground) {
		switch (colourCode) {
			case YTUI_COLOUR_BLACK: {
				return 30;
			}
			case YTUI_COLOUR_RED: {
				return 31;
			}
			case YTUI_COLOUR_GREEN: {
				return 32;
			}
			case YTUI_COLOUR_YELLOW: {
				return 33;
			}
			case YTUI_COLOUR_BLUE: {
				return 34;
			}
			case YTUI_COLOUR_MAGENTA: {
				return 35;
			}
			case YTUI_COLOUR_CYAN: {
				return 36;
			}
			case YTUI_COLOUR_WHITE: {
				return 37;
			}
			case YTUI_COLOUR_GREY: {
				return 90;
			}
			case YTUI_COLOUR_BRIGHT_RED: {
				return 91;
			}
			case YTUI_COLOUR_BRIGHT_GREEN: {
				return 92;
			}
			case YTUI_COLOUR_BRIGHT_YELLOW: {
				return 93;
			}
			case YTUI_COLOUR_BRIGHT_BLUE: {
				return 94;
			}
			case YTUI_COLOUR_BRIGHT_MAGENTA: {
				return 95;
			}
			case YTUI_COLOUR_BRIGHT_CYAN: {
				return 96;
			}
			case YTUI_COLOUR_BRIGHT_WHITE: {
				return 97;
			}
			default: {
				return 0;
			}
		}
	}
	else {
		switch (colourCode) {
			case YTUI_COLOUR_BLACK: {
				return 40;
			}
			case YTUI_COLOUR_RED: {
				return 41;
			}
			case YTUI_COLOUR_GREEN: {
				return 42;
			}
			case YTUI_COLOUR_YELLOW: {
				return 43;
			}
			case YTUI_COLOUR_BLUE: {
				return 44;
			}
			case YTUI_COLOUR_MAGENTA: {
				return 45;
			}
			case YTUI_COLOUR_CYAN: {
				return 46;
			}
			case YTUI_COLOUR_WHITE: {
				return 47;
			}
			case YTUI_COLOUR_GREY: {
				return 100;
			}
			case YTUI_COLOUR_BRIGHT_RED: {
				return 101;
			}
			case YTUI_COLOUR_BRIGHT_GREEN: {
				return 102;
			}
			case YTUI_COLOUR_BRIGHT_YELLOW: {
				return 103;
			}
			case YTUI_COLOUR_BRIGHT_BLUE: {
				return 104;
			}
			case YTUI_COLOUR_BRIGHT_MAGENTA: {
				return 105;
			}
			case YTUI_COLOUR_BRIGHT_CYAN: {
				return 106;
			}
			case YTUI_COLOUR_BRIGHT_WHITE: {
				return 107;
			}
			default: {
				return 0;
			}
		}
	}
}