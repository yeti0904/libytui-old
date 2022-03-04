#pragma once
#include "_components.h"

typedef struct YTUI_Vec2 {
	uint16_t x, y;
} YTUI_Vec2;

typedef struct YTUI_Rect {
	YTUI_Vec2 x, y;
} YTUI_Rect;

typedef struct YTUI_Border {
	char top, bottom, left, right, topright, topleft, bottomright, bottomleft;
} YTUI_Border;

typedef struct YTUI_TrueColour {
	uint8_t r, g, b;
} YTUI_TrueColour;

typedef struct YTUI_TrueColourPair {
	YTUI_TrueColour fore, back;
} YTUI_TrueColourPair;

typedef struct YTUI_ColourPair {
	uint8_t fore, back;
} YTUI_ColourPair;

typedef struct YTUI_Attribute {
	bool                colourEnabled;
	bool                trueColourEnabled;
	YTUI_ColourPair     colour;
	YTUI_TrueColourPair trueColour;
	bool                bold, italic, underline, blink, reverse, reset;
} YTUI_Attribute;

typedef struct YTUI_Character {
	char           ch;
	YTUI_Attribute attribute;
} YTUI_Character;

typedef struct YTUI_Window {
	YTUI_Rect       position;
	bool            border;
	YTUI_Border     border_style;
	YTUI_Character* content;
} YTUI_Window;

typedef struct YTUI_ScreenBuffer {
	uint16_t         width, height;
	YTUI_Character** buffer;
} YTUI_ScreenBuffer;

typedef struct YTUI_TermHandle {
	YTUI_Vec2         size;
	YTUI_ScreenBuffer screen;
	YTUI_Vec2         cursor;
	YTUI_Attribute    attribute;
} YTUI_TermHandle;