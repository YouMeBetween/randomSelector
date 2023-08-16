#include <Windows.h>
#include "../includes/interfaceBase.h"

using namespace std;

void CInterfaceBase::gotoxy(int x, int y)
{
	COORD pos = { x, y };
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut, pos);
	return;
}