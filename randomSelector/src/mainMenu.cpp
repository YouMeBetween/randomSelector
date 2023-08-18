#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <Windows.h>
#include "../includes/mainMenu.h"
#include "../includes/items.h"
#include "../includes/index.h"
using namespace std;

constexpr int FIRST_OPTION_LINE = 3;
constexpr int FINAL_LINE = 6;
constexpr int MAX_INDEX = 2;
constexpr int THIS_RESULT_SHOW_INDEX = 0;
constexpr int THIS_SETTING_INDEX = 1;
constexpr int THIS_QUIT_INDEX = 2;
constexpr int ARROW_OFFSET = 2;

void CMainMenu::printMenu()
{
	system("cls");
	cout << "********************************\n";
	cout << "*            主菜单            *\n";
	cout << "********************************\n";
	cout << "*         1.开始选择           *\n";
	cout << "*         2.设置               *\n";
	cout << "*         3.退出               *\n";
	cout << "********************************\n";
	return;
}

void CMainMenu::startChoose()
{
	CItems items;
	setItem("res/cfg.ini", "choice", items.chooseOne());
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
	gotoxy(ARROW_OFFSET, FIRST_OPTION_LINE);
	cout << ">";
	gotoxy(0, FINAL_LINE);
}

CMainMenu::CMainMenu(int x)
{
	line = max(min(x, MAX_INDEX), 0);
	printMenu();
	gotoxy(ARROW_OFFSET, FIRST_OPTION_LINE + line);
	cout << ">";
	gotoxy(0, FINAL_LINE);
}

void CMainMenu::moveCursor(int target)
{
	gotoxy(ARROW_OFFSET, FIRST_OPTION_LINE + line);
	cout << " ";
	line = target;
	gotoxy(ARROW_OFFSET, FIRST_OPTION_LINE + line);
	cout << ">";
	return;
}

void CMainMenu::up()
{
	if (line > 0) {
		moveCursor(line - 1);
	}
	return;
}

void CMainMenu::down()
{
	if (line < MAX_INDEX) {
		moveCursor(line + 1);
	}
	return;
}

void CMainMenu::enter(int &next_interface, int &cursor_line)
{
	switch (line)
	{
		case THIS_RESULT_SHOW_INDEX: {
			startChoose();
			nextInterfaceSet(next_interface, cursor_line, RESULT_SHOW_INDEX, NO_LINE);
			break;
		}
		case THIS_SETTING_INDEX: {
			nextInterfaceSet(next_interface, cursor_line, SETTING_INDEX, WEIGHT_SELECT_IN_SETTING);
			break;
		}
		case THIS_QUIT_INDEX: {
			quit();
			break;
		}
		default:
			nextInterfaceSet(next_interface, cursor_line, MAIN_MENU_INDEX, RESULT_SHOW_LINE_IN_MAIN_MENU);
			break;
	}
	return;
}