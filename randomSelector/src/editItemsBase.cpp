#include <iostream>
#include <string>
#include <algorithm>
#include <cstdlib>
#include "../includes/editItemsBase.h"
#include "../includes/index.h"
#include "../includes/items.h"
using namespace std;

CEditItemsBase::CEditItemsBase()
{
	line = FIRST_LINE;
	name = "";
	weight = 0;
	min_weight = 0;
	max_weight = 0;
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
	cin >> name;
	hideCursor();
}

void CEditItemsBase::weightRangeCheck()
{
	gotoxy(INPUT_OFFSET, WEIGHT_LINE);
	cout << "               ";
	if (weight == 0) {
		return;
	}
	if (min_weight != 0) {
		weight = max(weight, min_weight);
	}
	if (max_weight != 0) {
		weight = min(weight, max_weight);
	}
	gotoxy(INPUT_OFFSET, WEIGHT_LINE);
	cout << weight;
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
	weight = max(atoi(input_str.c_str()), 0);
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
	min_weight = max(atoi(input_str.c_str()), 0);
	if (max_weight != 0) {
		min_weight = min(min_weight, max_weight);
	}
	gotoxy(INPUT_OFFSET, MIN_WEIGHT_LINE);
	cout << "               ";
	if (min_weight != 0) {
		gotoxy(INPUT_OFFSET, MIN_WEIGHT_LINE);
		cout << min_weight;
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
	max_weight = max(atoi(input_str.c_str()), min_weight);
	gotoxy(INPUT_OFFSET, MAX_WEIGHT_LINE);
	cout << "               ";
	if (max_weight != 0) {
		gotoxy(INPUT_OFFSET, MAX_WEIGHT_LINE);
		cout << max_weight;
	}
	weightRangeCheck();
}

void CEditItemsBase::confirm(int &next_interface, int &cursor_line)
{
	Item item;
	CItems items;
	if (name == "" || weight == 0) {
		gotoxy(PROMPT_OFFSET, CONFIRM_LINE);
		cout << "                   ";
		gotoxy(PROMPT_OFFSET, CONFIRM_LINE);
		cout << "未输入名称或权重";
		return;
	}
	item.name = name;
	item.weight = weight;
	item.min_weight = min_weight;
	item.max_weight = max_weight;
	items.addOne(item);
	nextInterfaceSet(next_interface, cursor_line, ITEMS_SETUP_INDEX, NO_LINE);
}