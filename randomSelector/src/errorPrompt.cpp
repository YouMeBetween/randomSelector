#include <iostream>
#include <string>
#include <cstdlib>
#include <conio.h>
#include <Windows.h>
#include "../includes/errorPrompt.h"
using namespace std;

constexpr int HORIZONTAL_LENGTH = 32;
constexpr int MSG_LINE = 2;
constexpr int ENTER_KEY = 13;

void CErrorPrompt::gotoxy(int x, int y)
{
	COORD pos = { x, y };
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut, pos);
}

void CErrorPrompt::show()
{
	system("cls");
	cout << "********************************\n";
	cout << "*                              *\n";
	cout << "*                              *\n";
	cout << "*           > È·¶¨             *\n";
	cout << "*                              *\n";
	cout << "********************************\n";
}

CErrorPrompt::CErrorPrompt(string msg)
{
	show();
	gotoxy((HORIZONTAL_LENGTH - msg.size()) / 2, MSG_LINE);
	cout << msg;
	while (1) {
		if (_kbhit()) {
			if (_getch() == ENTER_KEY) {
				system("cls");
				exit(1);
			}
		}
	}
}