/*
Header file creates a function to move the position of
the cursor in a console window.

simply use "#include <gotoxy.h>" in your *.cpp file and
then you can call the function "gotoxy(n,n);" with "n" being
any integer to move your cursor to that position in your console
window.

windows.h and stdio.h have been include for convenience.

Created: 11/18/04
Modified/Header Author: Jason Olsen
Original code taken from:
"http://www.codeproject.com/cpp/cppforumfaq.asp?msg=729023#cons_gotoxy"

*/

#include <windows.h>
#include <stdio.h>

void gotoxy(int h, int w)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	if (INVALID_HANDLE_VALUE != hConsole)
	{
		COORD pos = { h, w };
		SetConsoleCursorPosition(hConsole, pos);
	}
	return;
}
