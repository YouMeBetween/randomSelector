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

constexpr int INPUT_LINE = 2;
constexpr int CONFIRM_LINE = 3;
constexpr int INPUT_SEARCH_ARROW_OFFSET = 9;
constexpr int INPUT_JUMP_ARROW_OFFSET = 13;
constexpr int INPUT_SEARCH_OFFSET = 11;
constexpr int INPUT_JUMP_OFFSET = 15;
constexpr int CONFIRM_ARROW_OFFSET = 12;
constexpr int SEARCH_OR_JUMP = 0b001;
constexpr int IS_FROM_ITEMS_SETUP = 0b010;
constexpr int IS_FROM_ITEMS_LIST_SETTING = 0b100;

void CPageJump::show()
{
	system("cls");
	cout << "********************************\n";
	if ((type & SEARCH_OR_JUMP) == 0) {
		cout << "*     请输入想要搜索的条目     *\n";
	} else {
		cout << "*     请输入想要跳转的页面     *\n";
	}
	cout << "*                              *\n";
	cout << "*             确认             *\n";
	cout << "********************************\n";
}

string CPageJump::getInput()
{
	string input_str;
	gotoxy(0, INPUT_LINE);
	cout << "*                              *";
	if (!(type & SEARCH_OR_JUMP)) {
		gotoxy(INPUT_SEARCH_OFFSET, INPUT_LINE);
	} else {
		gotoxy(INPUT_JUMP_OFFSET, INPUT_LINE);
	}
	showCursor();
	cin >> input_str;
	hideCursor();
	return input_str;
}

void CPageJump::writePage(int page)
{
	if (setItem("res/cfg.ini", "page", to_string(page))) {
		CErrorPrompt error_prompt("打开cfg.ini文件失败");
	}
	moveCursor(INPUT_LINE);
}

void CPageJump::setItemsSetupPage()
{
	int page = 0;
	CItems temp;
	vector<Item> items = temp.getItems();
	string input_str = getInput();
	if (!(type & SEARCH_OR_JUMP)) {
		auto iter = find_if(items.begin(), items.end(), [input_str](Item item) { return item.name == input_str; });
		if (iter == items.end()) {
			moveCursor(INPUT_LINE);
			return;
		} else {
			page = distance(items.begin(), iter) / ITEMS_PER_PAGE_IN_ITEMS_SETUP;
		}
	} else if (type & SEARCH_OR_JUMP) {
		page = max(min(stoi(input_str) - 1, items.size() / ITEMS_PER_PAGE_IN_ITEMS_SETUP), 0);
	}
	writePage(page);
}

void CPageJump::setItemsListSettingPage()
{
	int page = 0;
	vector<string> files;
	get_need_file("res", files, ".csv");
	string input_str = getInput();
	if (!(type & SEARCH_OR_JUMP)) {
		auto iter = find(files.begin(), files.end(), input_str);
		if (iter == files.end()) {
			moveCursor(INPUT_LINE);
			return;
		} else {
			page = distance(files.begin(), iter) / LIST_PER_PAGE_IN_ITEMS_LIST_SETTING;
		}
	} else if (type & SEARCH_OR_JUMP) {
		page = max(min(stoi(input_str) - 1, files.size() / LIST_PER_PAGE_IN_ITEMS_LIST_SETTING), 0);
	}
	writePage(page);
}

void CPageJump::moveCursor(int target_line)
{
	if (target_line == INPUT_LINE) {
		gotoxy(CONFIRM_ARROW_OFFSET, CONFIRM_LINE);
		cout << " ";
		if ((type & SEARCH_OR_JUMP) == 0) {
			gotoxy(INPUT_SEARCH_ARROW_OFFSET, INPUT_LINE);
		} else {
			gotoxy(INPUT_JUMP_ARROW_OFFSET, INPUT_LINE);
		}
	} else {
		if ((type & SEARCH_OR_JUMP) == 0) {
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
	if (type & IS_FROM_ITEMS_SETUP) {
		setItemsSetupPage();
	} else if (type & IS_FROM_ITEMS_LIST_SETTING) {
		setItemsListSettingPage();
	}
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
		if (type & IS_FROM_ITEMS_SETUP) {
			setItemsSetupPage();
		} else if (type & IS_FROM_ITEMS_LIST_SETTING) {
			setItemsListSettingPage();
		}
	} else {
		if (type & IS_FROM_ITEMS_SETUP) {
			nextInterfaceSet(next_interface, cursor_line, ITEMS_SETUP_INDEX, NO_LINE);
		} else if (type & IS_FROM_ITEMS_LIST_SETTING) {
			nextInterfaceSet(next_interface, cursor_line, ITEMS_LIST_SETTING_INDEX, NO_LINE);
		}
	}
}