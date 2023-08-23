#include <memory>
#include <conio.h>
#include <Windows.h>
#include "includes/interfaceBase.h"
#include "includes/mainMenu.h"
#include "includes/resultShow.h"
#include "includes/setting.h"
#include "includes/itemsSetup.h"
#include "includes/pageJump.h"
#include "includes/index.h"
using namespace std;

constexpr int UP_KEY = 72;
constexpr int DOWN_KEY = 80;
constexpr int LEFT_KEY = 75;
constexpr int RIGHT_KEY = 77;
constexpr int ENTER_KET = 13;

void hideCursor();
void switchInterface(shared_ptr<CInterfaceBase> &, int &, int);

int main()
{
	char ch;
	int next_interface = MAIN_MENU_INDEX, cursor_line = RESULT_SHOW_LINE_IN_MAIN_MENU;
	shared_ptr<CInterfaceBase> interface_base;
	switchInterface(interface_base, next_interface, cursor_line);
	hideCursor();
	while (1) {
		if (_kbhit()) {
			ch = _getch();
			switch (ch) {
				case UP_KEY: interface_base->up(); break;
				case DOWN_KEY: interface_base->down(); break;
				case LEFT_KEY: interface_base->left(); break;
				case RIGHT_KEY: interface_base->right(); break;
				case ENTER_KET: interface_base->enter(next_interface, cursor_line); break;
				default: break;
			}
		}
		if (next_interface) {
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

void switchInterface(shared_ptr<CInterfaceBase> &interface_base, int &next_interface, int cursor_line)
{
	switch (next_interface) {
		default:
		case MAIN_MENU_INDEX: {
			shared_ptr<CMainMenu> main_menu = make_shared<CMainMenu>(cursor_line);
			interface_base = main_menu;
			break;
		}
		case RESULT_SHOW_INDEX: {
			shared_ptr<CResultShow> result_show = make_shared<CResultShow>();
			interface_base = result_show;
			break;
		}
		case SETTING_INDEX: {
			shared_ptr<CSetting> setting = make_shared<CSetting>(cursor_line);
			interface_base = setting;
			break;
		}
		case ITEMS_SETUP_INDEX: {
			shared_ptr<CItemsSetup> items_setup = make_shared<CItemsSetup>();
			interface_base = items_setup;
			break;
		}
		case PAGE_JUMP_INDEX: {
			shared_ptr<CPageJump> page_jump = make_shared<CPageJump>(cursor_line);
			interface_base = page_jump;
			break;
		}
	}
	next_interface = 0;
}