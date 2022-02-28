#include "_components.h"
#include "structures.h"
#include "functions.h"
#include "keys.h"

YTUI_TermHandle* YTUI_Init() {
	YTUI_TermHandle* ret = NULL;
	ret = (YTUI_TermHandle*) YTUI_Alloc(ret, sizeof(YTUI_TermHandle));
	ret->screen.buffer = NULL;
	ret->size          = YTUI_GetTermSize();
	ret->screen.width  = ret->size.x;
	ret->screen.height = ret->size.y;
	ret->screen.buffer = (YTUI_Character**) YTUI_Alloc(ret->screen.buffer, ret->screen.height * sizeof(YTUI_Character*));
	for (size_t i = 0; i<ret->screen.height; i++) {
		ret->screen.buffer[i] = NULL;
		ret->screen.buffer[i] = (YTUI_Character*) YTUI_Alloc(ret->screen.buffer[i], ret->screen.width * sizeof(YTUI_Character)); // line 13
		for (size_t j = 0; j<ret->screen.width; j++) {
			ret->screen.buffer[i][j].ch        = ' ';
			ret->screen.buffer[i][j].attribute = YTUI_DefaultAttribute();
		}
	}
	ret->cursor.x = 0;
	ret->cursor.y = 0;

	return ret;
}

void YTUI_Exit(YTUI_TermHandle* term) {
	for (size_t i = 0; i<term->screen.height; i++) {
		free(term->screen.buffer[i]);
	}
	free(term->screen.buffer);
	free(term);
	puts("\033[2J"); // clear screen
	puts("\033[H"); // move cursor to 0 0
	YTUI_SetShowCursor(true);
}

void* YTUI_Alloc(void* ptr, size_t size) {
	void* ret;
	if (ptr == NULL) {
		ret = malloc(size);
	} else {
		ret = realloc(ptr, size);
	}
	return ret;
}

YTUI_Vec2 YTUI_GetTermSize() {
	struct winsize ws;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
	return (YTUI_Vec2){ws.ws_col, ws.ws_row};
}

YTUI_Attribute YTUI_DefaultAttribute() {
	return (YTUI_Attribute) {
		.colour     = false,
		.trueColour = false,
		.bold       = false,
		.italic     = false,
		.underline  = false,
		.blink      = false,
		.reverse    = false
	};
}

void YTUI_PrintChar(YTUI_TermHandle* term, char ch) {
	switch (ch) {
		case '\r': {
			term->cursor.x = 0;
			break;
		}
		case '\n': {
			++ term->cursor.y;
			term->cursor.x = 0;
			break;
		}
		default: {
			term->screen.buffer[term->cursor.y][term->cursor.x].ch = ch; // segfault here
			/*
			 Invalid write of size 1
			 Use of uninitialised value of size 8
			*/
			++ term->cursor.x;
			if (term->cursor.x >= term->screen.width) {
				term->cursor.x = 0;
				++ term->cursor.y;
			}
			if (term->cursor.y >= term->screen.height) {
				term->cursor.y = 0;
			}
		}
	}
	// copy attributes
	term->screen.buffer[term->cursor.y][term->cursor.x].attribute = term->attribute;
}

void YTUI_PrintString(YTUI_TermHandle* term, char* str) {
	while (*str != '\0') {
		YTUI_PrintChar(term, *str);
		++ str;
	}
}

void YTUI_SetAttribute(YTUI_TermHandle* term, YTUI_Attribute attr) {
	term->screen.buffer[term->cursor.y][term->cursor.x].attribute = attr;
	term->attribute = attr;
}

void YTUI_MoveCursor(YTUI_TermHandle* term, uint16_t x, uint16_t y) {
	term->cursor.x = x;
	term->cursor.y = y;
}

void YTUI_SetShowCursor(bool show) {
	if (show) {
		puts("\033[?25h");
		return;
	}
	puts("\033[?25l");
}

void YTUI_Clear(YTUI_TermHandle* term) {
	for (size_t i = 0; i<term->screen.height; i++) {
		for (size_t j = 0; j<term->screen.width; j++) {
			term->screen.buffer[i][j].ch = ' ';
		}
	}
}

char YTUI_GetCharacter() {
	struct termios info;
	tcgetattr(0, &info);
	info.c_lflag &= ~ICANON;
	info.c_cc[VMIN] = 1;
	info.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &info); 
	char in;
	read(STDIN_FILENO, &in, 1);
	return in;
}

uint16_t YTUI_GetKey() {
	char in = YTUI_GetCharacter();
	if (in != '\033') return in;

	in = YTUI_GetCharacter();
	if (in == '[') {
		in = YTUI_GetCharacter();
		switch (in) {
			case 'A': {
				return YTUI_KEY_UP;
			}
			case 'B': {
				return YTUI_KEY_DOWN;
			}
			case 'C': {
				return YTUI_KEY_RIGHT;
			}
			case 'D': {
				return YTUI_KEY_LEFT;
			}
			case 'H': {
				return YTUI_KEY_HOME;
			}
			case 'F': {
				return YTUI_KEY_END;
			}
			case '3': {
				in = YTUI_GetCharacter();
				switch (in) {
					case '~': {
						return YTUI_KEY_DEL;
					}
				}
			}
		}
	}
	return in;
}

void YTUI_Render(YTUI_TermHandle* term) {
	YTUI_Attribute currentAttr = YTUI_DefaultAttribute();
	YTUI_Attribute cellAttr;

	printf("\033[2J"); // clear screen
	printf("\033[H"); // move cursor to 0 0
	for (size_t i = 0; i<term->screen.height; i++) {
		for (size_t j = 0; j<term->screen.width; j++) {
			cellAttr = term->screen.buffer[i][j].attribute;
			if (currentAttr.bold != cellAttr.bold) {
				if (cellAttr.bold)
					printf("\033[1m");
				else
					printf("\033[22m");
				currentAttr.bold = cellAttr.bold;
			}
			if (currentAttr.italic != cellAttr.italic) {
				if (cellAttr.italic)
					printf("\033[3m");
				else
					printf("\033[23m");
				currentAttr.italic = cellAttr.italic;
			}
			if (currentAttr.underline != cellAttr.underline) {
				if (cellAttr.underline)
					printf("\033[4m");
				else
					printf("\033[24m");
				currentAttr.underline = cellAttr.underline;
			}
			if (currentAttr.blink != cellAttr.blink) {
				if (cellAttr.blink)
					printf("\033[5m");
				else
					printf("\033[25m");
				currentAttr.blink = cellAttr.blink;
			}
			if (currentAttr.reverse != cellAttr.reverse) {
				if (cellAttr.reverse)
					printf("\033[7m");
				else
					printf("\033[27m");
				currentAttr.reverse = cellAttr.reverse;
			}
			putchar(term->screen.buffer[i][j].ch);
		}
		if ((int)i != term->screen.height - 1)
			putchar('\n');
	}
	printf("\033[%d;%dH", term->cursor.y + 1, term->cursor.x + 1);
}