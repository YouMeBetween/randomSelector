#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <Windows.h>
#include "../includes/mainMenu.h"
#include "../includes/items.h"
using namespace std;

constexpr int FIRST_OPTION_LINE = 3;
constexpr int FINAL_LINE = 6;
constexpr int MAX_INDEX = 1;
constexpr int START_INDEX = 0;
constexpr int QUIT_INDEX = 1;
constexpr int ARROW_OFFSET = 2;

void CMainMenu::printMenu()
{
	system("cls");
	cout << "********************************\n";
	cout << "*            主菜单            *\n";
	cout << "********************************\n";
	cout << "*         1.开始选择           *\n";
	cout << "*         2.退出               *\n";
	cout << "********************************\n";
	return;
}

void CMainMenu::startChoose()
{
	CItems items;
	setItem("choice", items.chooseOne());
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
	if (line <= 0) {
		return;
	}
	moveCursor(line - 1);
	return;
}

void CMainMenu::down()
{
	if (line >= MAX_INDEX) {
		return;
	}
	moveCursor(line + 1);
	return;
}

int CMainMenu::enter()
{
	if (line == START_INDEX) {
		startChoose();
		return 2;
	} else if (line == QUIT_INDEX) {
		quit();
	}
}