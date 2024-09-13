#include <iostream>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <Windows.h>
#include "../includes/mainMenu.h"
#include "../includes/items.h"
#include "../includes/index.h"
#include "../includes/errorPrompt.h"
using namespace std;

constexpr int FIRST_LINE = 3;
constexpr int LAST_LINE = 6;
constexpr int FINAL_LINE = 8;
constexpr int RESULT_SHOW_LINE = 3;
constexpr int HISTORY_LINE = 4;
constexpr int SETTING_LINE = 5;
constexpr int QUIT_LINE = 6;
constexpr int ARROW_OFFSET = 8;

void CMainMenu::printMenu()
{
	system("cls");
	cout << "********************************\n";
	cout << "*            主菜单            *\n";
	cout << "********************************\n";
	cout << "*         1.开始选择           *\n";
	cout << "*         2.历史记录           *\n";
	cout << "*         3.设置               *\n";
	cout << "*         4.退出               *\n";
	cout << "********************************\n";
	return;
}

void CMainMenu::startChoose()
{
	CItems items;
	if (setItem("res/cfg.ini", "choice", items.chooseOne())) {
		CErrorPrompt error_prompt("写入选择结果失败");
	}
}

void CMainMenu::quit()
{
	system("cls");
	exit(0);
}

CMainMenu::CMainMenu()
{
	line = 0;
	printMenu();
	gotoxy(ARROW_OFFSET, FIRST_LINE);
	cout << ">";
	gotoxy(0, FINAL_LINE);
}

CMainMenu::CMainMenu(int x)
{
	line = max(min(x, LAST_LINE), FIRST_LINE);
	printMenu();
	gotoxy(ARROW_OFFSET, line);
	cout << ">";
	gotoxy(0, FINAL_LINE);
}

void CMainMenu::moveCursor(int target)
{
	gotoxy(ARROW_OFFSET, line);
	cout << " ";
	line = target;
	gotoxy(ARROW_OFFSET, line);
	cout << ">";
	return;
}

void CMainMenu::up()
{
	if (line > FIRST_LINE) {
		moveCursor(line - 1);
	}
	return;
}

void CMainMenu::down()
{
	if (line < LAST_LINE) {
		moveCursor(line + 1);
	}
	return;
}

void CMainMenu::enter(int &next_interface, int &cursor_line)
{
	switch (line)
	{
		case RESULT_SHOW_LINE: {
			startChoose();
			nextInterfaceSet(next_interface, cursor_line, RESULT_SHOW_INDEX, NO_LINE);
			break;
		}
		case HISTORY_LINE: {
			nextInterfaceSet(next_interface, cursor_line, HISTORY_INDEX, NO_LINE);
			break;
		}
		case SETTING_LINE: {
			nextInterfaceSet(next_interface, cursor_line, SETTING_INDEX, WEIGHT_SELECT_IN_SETTING);
			break;
		}
		case QUIT_LINE: {
			quit();
			break;
		}
		default:
			break;
	}
	return;
}