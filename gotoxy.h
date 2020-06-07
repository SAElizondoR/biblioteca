#ifndef _gotoxy_H_
#define _gotoxy_H_

#include <windows.h>
BOOL gotoxy(int x, int y){
	COORD c;
	c.X = x;
	c.Y = y;
	return SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

#endif
