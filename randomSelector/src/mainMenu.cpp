#include <iostream>
#include <algorithm>
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

void CMainMenu::gotoxy(int x, int y)
{
	COORD pos = { x, y };
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut, pos);
	return;
}

void CMainMenu::printMenu()
{
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
	gotoxy(0, FINAL_LINE);
	cout << items.chooseOne();
	exit(0);
}

void CMainMenu::quit()
{
	gotoxy(0, FINAL_LINE);
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

void CMainMenu::up()
{
	if (line <= 0) {
		return;
	}
	gotoxy(ARROW_OFFSET, FIRST_OPTION_LINE + line);
	cout << " ";
	line--;
	gotoxy(ARROW_OFFSET, FIRST_OPTION_LINE + line);
	cout << ">";
	return;
}

void CMainMenu::down()
{
	if (line >= MAX_INDEX) {
		return;
	}
	gotoxy(ARROW_OFFSET, FIRST_OPTION_LINE + line);
	cout << " ";
	line++;
	gotoxy(ARROW_OFFSET, FIRST_OPTION_LINE + line);
	cout << ">";
	return;
}

void CMainMenu::enter()
{
	if (line == START_INDEX) {
		startChoose();
	} else if (line == QUIT_INDEX) {
		quit();
	}
}