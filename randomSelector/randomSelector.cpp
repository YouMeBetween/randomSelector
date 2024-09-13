#include <memory>
#include <conio.h>
#include <Windows.h>
#include "includes/interfaceBase.h"
#include "includes/mainMenu.h"
#include "includes/resultShow.h"
#include "includes/setting.h"
#include "includes/itemsSetup.h"
#include "includes/pageJump.h"
#include "includes/addItems.h"
#include "includes/editItems.h"
#include "includes/itemsListSetting.h"
#include "includes/addList.h"
#include "includes/editList.h"
#include "includes/history.h"
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
		case ADD_ITEMS_INDEX: {
			shared_ptr<CAddItems> add_items = make_shared<CAddItems>();
			interface_base = add_items;
			break;
		}
		case EDIT_ITEMS_INDEX: {
			shared_ptr<CEditItems> edit_items = make_shared<CEditItems>();
			interface_base = edit_items;
			break;
		}
		case ITEMS_LIST_SETTING_INDEX: {
			shared_ptr<CItemsListSetting> items_list_setting = make_shared<CItemsListSetting>();
			interface_base = items_list_setting;
			break;
		}
		case ADD_LIST_INDEX: {
			shared_ptr<CAddList> add_list = make_shared<CAddList>();
			interface_base = add_list;
			break;
		}
		case EDIT_LIST_INDEX: {
			shared_ptr<CEditList> edit_list = make_shared<CEditList>();
			interface_base = edit_list;
			break;
		}
		case HISTORY_INDEX: {
			shared_ptr<CHistory> history = make_shared<CHistory>();
			interface_base = history;
			break;
		}
	}
	next_interface = 0;
}