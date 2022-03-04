#pragma once
#include "_components.h"
#include "structures.h"

// library init/exit
YTUI_TermHandle* YTUI_Init(); // creates a new terminal handle with an empty screen buffer
void             YTUI_Exit(YTUI_TermHandle* term); // frees data from the terminal handle and clears the screen

// misc
void*            YTUI_Alloc(void* ptr, size_t size); // allocates new memory if ptr is NULL, otherwise reallocates it

// screen
YTUI_Vec2        YTUI_GetTermSize(); // returns the size of the terminal
void             YTUI_PrintChar(YTUI_TermHandle* term, char ch); // adds a character to the screen buffer and increments the cursor position, if the cursor goes beyond the screen then it is put on a new line
void             YTUI_PrintString(YTUI_TermHandle* term, char* str); // adds a string to the screen buffer and adds to the cursor position, if the cursor goes beyond the screen then it is put on a new line
void             YTUI_SetAttribute(YTUI_TermHandle* term, YTUI_Attribute attr); // sets the current attribute of the terminal handle
void             YTUI_MoveCursor(YTUI_TermHandle* term, uint16_t x, uint16_t y); // moves the cursor on the screen buffer to the given position
void             YTUI_SetShowCursor(bool show); // sets whether the cursor is shown or not
void             YTUI_Clear(YTUI_TermHandle* term); // clears the screen buffer
char             YTUI_GetCharacter(); // returns an ASCII character from stdin
YTUI_Key         YTUI_GetKey(); // returns either an ASCII character or a key code (defined in keys.h) from stdin
void             YTUI_Render(YTUI_TermHandle* term); // renders the screen buffer to the terminal

// structures
YTUI_Attribute   YTUI_DefaultAttribute(); // returns the default attribute
YTUI_Attribute   YTUI_AttributeAddColour(YTUI_Attribute attr, YTUI_ColourPair colour); // adds a colour to the attribute
YTUI_Attribute   YTUI_AttributeAddTrueColour(YTUI_Attribute attr, YTUI_TrueColourPair colour); // adds a true colour to the attribute
YTUI_Attribute   YTUI_AttributeRemoveColour(YTUI_Attribute attr); // removes the colour data from the attribute