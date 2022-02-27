#include <ytui/ytui.h>

int main(void) {
	YTUI_TermHandle term = YTUI_Init();
	YTUI_Vec2       size = YTUI_GetTermSize();
	YTUI_Attribute  attr = YTUI_DefaultAttribute();

	attr.reverse = true;
	attr.bold    = true;
	YTUI_SetAttribute(&term, attr);
	for (uint16_t i = 0; i<size.x; ++i) {
		YTUI_PrintChar(&term, ' ');
	}
	YTUI_MoveCursor(&term, 0, 0);
	YTUI_PrintString(&term, "my libytui program");
	
	attr.reverse = false;
	attr.bold    = false;
	YTUI_MoveCursor(&term, 0, 1);
	YTUI_SetAttribute(&term, attr);
	YTUI_PrintString(&term, "hello world");

	YTUI_Render(&term);

	YTUI_GetCharacter();

	YTUI_Exit(&term);
}