#include <iostream>
#include <string>
#include <algorithm>
#include <cstdlib>
#include "../includes/editItemsBase.h"
#include "../includes/errorPrompt.h"
#include "../includes/index.h"
#include "../includes/items.h"
using namespace std;

CEditItemsBase::CEditItemsBase()
{
	line = FIRST_LINE;
}

void CEditItemsBase::up()
{
	if (line > FIRST_LINE) {
		moveCursor(line - 1);
	}
}

void CEditItemsBase::moveCursor(int target)
{
	gotoxy(ARROW_OFFSET, line);
	cout << " ";
	line = target;
	gotoxy(ARROW_OFFSET, line);
	cout << ">";
}

void CEditItemsBase::setName()
{
	gotoxy(INPUT_OFFSET, NAME_LINE);
	cout << "               ";
	gotoxy(INPUT_OFFSET, NAME_LINE);
	showCursor();
	cin >> item.name;
	hideCursor();
}

void CEditItemsBase::weightRangeCheck()
{
	gotoxy(INPUT_OFFSET, WEIGHT_LINE);
	cout << "               ";
	if (item.weight == 0) {
		return;
	}
	if (item.min_weight != 0) {
		item.weight = max(item.weight, item.min_weight);
	}
	if (item.max_weight != 0) {
		item.weight = min(item.weight, item.max_weight);
	}
	gotoxy(INPUT_OFFSET, WEIGHT_LINE);
	cout << item.weight;
}

void CEditItemsBase::setWeight()
{
	string input_str;
	gotoxy(INPUT_OFFSET, WEIGHT_LINE);
	cout << "               ";
	gotoxy(INPUT_OFFSET, WEIGHT_LINE);
	showCursor();
	cin >> input_str;
	hideCursor();
	item.weight = max(atoi(input_str.c_str()), 0);
	weightRangeCheck();
}

void CEditItemsBase::setMinWeight()
{
	string input_str;
	gotoxy(INPUT_OFFSET, MIN_WEIGHT_LINE);
	cout << "               ";
	gotoxy(INPUT_OFFSET, MIN_WEIGHT_LINE);
	showCursor();
	cin >> input_str;
	hideCursor();
	item.min_weight = max(atoi(input_str.c_str()), 0);
	if (item.max_weight != 0) {
		item.min_weight = min(item.min_weight, item.max_weight);
	}
	gotoxy(INPUT_OFFSET, MIN_WEIGHT_LINE);
	cout << "               ";
	if (item.min_weight != 0) {
		gotoxy(INPUT_OFFSET, MIN_WEIGHT_LINE);
		cout << item.min_weight;
	}
	weightRangeCheck();
}

void CEditItemsBase::setMaxWeight()
{
	string input_str;
	gotoxy(INPUT_OFFSET, MAX_WEIGHT_LINE);
	cout << "               ";
	gotoxy(INPUT_OFFSET, MAX_WEIGHT_LINE);
	showCursor();
	cin >> input_str;
	hideCursor();
	item.max_weight = max(atoi(input_str.c_str()), item.min_weight);
	gotoxy(INPUT_OFFSET, MAX_WEIGHT_LINE);
	cout << "               ";
	if (item.max_weight != 0) {
		gotoxy(INPUT_OFFSET, MAX_WEIGHT_LINE);
		cout << item.max_weight;
	}
	weightRangeCheck();
}

void CEditItemsBase::confirm(int &next_interface, int &cursor_line, bool is_add)
{
	int page;
	Item temp;
	CItems items;
	if (item.name == "" || item.weight == 0) {
		gotoxy(PROMPT_OFFSET, CONFIRM_LINE);
		cout << "                   ";
		gotoxy(PROMPT_OFFSET, CONFIRM_LINE);
		cout << "未输入名称或权重";
		return;
	}
	temp.name = item.name;
	temp.weight = item.weight;
	temp.min_weight = item.min_weight;
	temp.max_weight = item.max_weight;
	temp.on_off = true;
	if (is_add) {
		items.addOne(temp);
	} else {
		string item_want_edit = getItem("res/cfg.ini", "itemWantEdit");
		items.modifyOne(item_want_edit, temp);
	}
	page = items.getIndex(temp.name) / ITEMS_PER_PAGE_IN_ITEMS_SETUP;
	if (setItem("res/cfg.ini", "page", to_string(page))) {
		CErrorPrompt error_prompt("打开cfg.ini文件失败");
	}
	nextInterfaceSet(next_interface, cursor_line, ITEMS_SETUP_INDEX, NO_LINE);
}