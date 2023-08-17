#include <conio.h>
#include <Windows.h>
#include "includes/interfaceBase.h"
#include "includes/mainMenu.h"
#include "includes/resultShow.h"
#include "includes/index.h"
using namespace std;

constexpr int UP_KEY = 72;
constexpr int DOWN_KEY = 80;
constexpr int ENTER_KET = 13;

void hideCursor();
void switchInterface(CInterfaceBase *&, int &, int);

int main()
{
	char ch;
	int next_interface = MAIN_MENU_INDEX, cursor_line = RESULT_SHOW_LINE_IN_MAIN_MENU;
	CInterfaceBase *interface_base;
	switchInterface(interface_base, next_interface, cursor_line);
	hideCursor();
	while (1) {
		if (_kbhit()) {
			ch = _getch();
			switch (ch) {
				case UP_KEY: interface_base->up(); break;
				case DOWN_KEY: interface_base->down(); break;
				case ENTER_KET: interface_base->enter(next_interface, cursor_line); break;
				default: break;
			}
		}
		if (next_interface) {
			delete(interface_base);
			switchInterface(interface_base, next_interface, cursor_line);
		}
	}
}

void hideCursor()
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(handle, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(handle, &cursorInfo);
}

void switchInterface(CInterfaceBase *&interface_base, int &next_interface, int cursor_line)
{
	switch (next_interface) {
		default:
		case MAIN_MENU_INDEX: {
			CMainMenu *main_menu = new CMainMenu(cursor_line);
			interface_base = main_menu;
			break;
		}
		case RESULT_SHOW_INDEX: {
			CResultShow *result_show = new CResultShow;
			interface_base = result_show;
			break;
		}
	}
	next_interface = 0;
}