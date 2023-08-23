#include <iostream>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <Windows.h>
#include "../includes/pageJump.h"
#include "../includes/errorPrompt.h"
#include "../includes/items.h"
#include "../includes/index.h"
using namespace std;

constexpr int ITEMS_PER_PAGE = 5;
constexpr int INPUT_LINE = 2;
constexpr int CONFIRM_LINE = 3;
constexpr int INPUT_SEARCH_ARROW_OFFSET = 9;
constexpr int INPUT_JUMP_ARROW_OFFSET = 13;
constexpr int INPUT_SEARCH_OFFSET = 11;
constexpr int INPUT_JUMP_OFFSET = 15;
constexpr int CONFIRM_ARROW_OFFSET = 12;

void CPageJump::show()
{
	system("cls");
	cout << "********************************\n";
	if (type == 0) {
		cout << "*     请输入想要搜索的条目     *\n";
	} else {
		cout << "*     请输入想要跳转的页面     *\n";
	}
	cout << "*                              *\n";
	cout << "*             确认             *\n";
	cout << "********************************\n";
}

void CPageJump::showCursor()
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(handle, &cursorInfo);
	cursorInfo.bVisible = true;
	SetConsoleCursorInfo(handle, &cursorInfo);
}

void CPageJump::hideCursor()
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(handle, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(handle, &cursorInfo);
}

void CPageJump::setTargetPage()
{
	int page = 0;
	string input_str;
	CItems temp;
	vector<Item> items = temp.getItems();
	if (type == 0) {
		gotoxy(INPUT_SEARCH_ARROW_OFFSET, INPUT_LINE);
	} else {
		gotoxy(INPUT_JUMP_ARROW_OFFSET, INPUT_LINE);
	}
	cout << " ";
	if (type == 0) {
		gotoxy(INPUT_SEARCH_OFFSET, INPUT_LINE);
	} else {
		gotoxy(INPUT_JUMP_OFFSET, INPUT_LINE);
	}
	showCursor();
	cin >> input_str;
	hideCursor();
	if (type == 0) {
		for (auto iter = items.begin(); iter != items.end(); iter++) {
			if (iter->name == input_str) {
				page = (iter - items.begin()) / ITEMS_PER_PAGE;
				break;
			}
		}
	} else if (type == 1) {
		page = max(min(stoi(input_str) - 1, items.size() / ITEMS_PER_PAGE), 0);
	}
	if (setItem("res/cfg.ini", "page", to_string(page))) {
		CErrorPrompt error_prompt("打开cfg.ini文件失败");
	}
	if (type == 0) {
		gotoxy(INPUT_SEARCH_ARROW_OFFSET, INPUT_LINE);
	} else {
		gotoxy(INPUT_JUMP_ARROW_OFFSET, INPUT_LINE);
	}
	cout << ">";
}

void CPageJump::moveCursor(int target_line)
{
	if (target_line == INPUT_LINE) {
		gotoxy(CONFIRM_ARROW_OFFSET, CONFIRM_LINE);
		cout << " ";
		if (type == 0) {
			gotoxy(INPUT_SEARCH_ARROW_OFFSET, INPUT_LINE);
		} else {
			gotoxy(INPUT_JUMP_ARROW_OFFSET, INPUT_LINE);
		}
	} else {
		if (type == 0) {
			gotoxy(INPUT_SEARCH_ARROW_OFFSET, INPUT_LINE);
		} else {
			gotoxy(INPUT_JUMP_ARROW_OFFSET, INPUT_LINE);
		}
		cout << " ";
		gotoxy(CONFIRM_ARROW_OFFSET, CONFIRM_LINE);
	}
	line = target_line;
	cout << ">";
}

CPageJump::CPageJump(int input_type)
{
	line = INPUT_LINE;
	type = input_type;
	show();
	setTargetPage();
}

void CPageJump::up()
{
	if (line == CONFIRM_LINE) {
		moveCursor(INPUT_LINE);
	}
}

void CPageJump::down()
{
	if (line == INPUT_LINE) {
		moveCursor(CONFIRM_LINE);
	}
}

void CPageJump::enter(int &next_interface, int &cursor_line)
{
	if (line == INPUT_LINE) {
		setTargetPage();
	} else {
		nextInterfaceSet(next_interface, cursor_line, ITEMS_SETUP_INDEX, NO_LINE);
	}
}