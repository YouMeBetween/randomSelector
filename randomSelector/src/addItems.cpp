#include <iostream>
#include <string>
#include <algorithm>
#include <cstdlib>
#include "../includes/addItems.h"
#include "../includes/index.h"
#include "../includes/items.h"
using namespace std;

constexpr int FIRST_LINE = 3;
constexpr int NAME_LINE = 3;
constexpr int WEIGHT_LINE = 4;
constexpr int MIN_WEIGHT_LINE = 5;
constexpr int MAX_WEIGHT_LINE = 6;
constexpr int CONFIRM_LINE = 7;
constexpr int LAST_LINE = 8;
constexpr int QUIT_LINE = 8;
constexpr int ARROW_OFFSET = 2;
constexpr int INPUT_OFFSET = 16;
constexpr int PROMPT_OFFSET = 12;

void CAddItems::show()
{
	system("cls");
	cout << "********************************\n";
	cout << "*          增加待选项          *\n";
	cout << "********************************\n";
	cout << "* > 1.名称                     *\n";
	cout << "*   2.权重                     *\n";
	cout << "*   3.最低权重                 *\n";
	cout << "*   4.最低权重                 *\n";
	cout << "*   5.确认                     *\n";
	cout << "*   6.取消                     *\n";
	cout << "********************************\n";
}

void CAddItems::moveCursor(int target)
{
	gotoxy(ARROW_OFFSET, line);
	cout << " ";
	line = target;
	gotoxy(ARROW_OFFSET, line);
	cout << ">";
	return;
}

void CAddItems::setName()
{
	gotoxy(INPUT_OFFSET, NAME_LINE);
	cout << "               ";
	gotoxy(INPUT_OFFSET, NAME_LINE);
	showCursor();
	cin >> name;
	hideCursor();
}

void CAddItems::setWeight()
{
	string input_str;
	gotoxy(INPUT_OFFSET, WEIGHT_LINE);
	cout << "               ";
	gotoxy(INPUT_OFFSET, WEIGHT_LINE);
	showCursor();
	cin >> input_str;
	hideCursor();
	weight = max(atoi(input_str.c_str()), 0);
	gotoxy(INPUT_OFFSET, WEIGHT_LINE);
	cout << "               ";
	if (weight != 0) {
		gotoxy(INPUT_OFFSET, WEIGHT_LINE);
		cout << weight;
	}
}

void CAddItems::setMinWeight()
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
}

void CAddItems::setMaxWeight()
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
}

void CAddItems::confirm(int &next_interface, int &cursor_line)
{
	Item item;
	CItems items;
	if (name == "" || weight == 0) {
		gotoxy(PROMPT_OFFSET, CONFIRM_LINE);
		cout << "               ";
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

CAddItems::CAddItems()
{
	line = FIRST_LINE;
	name = "";
	weight = 0;
	min_weight = 0;
	max_weight = 0;
	show();
}

void CAddItems::up()
{
	if (line > FIRST_LINE) {
		moveCursor(line - 1);
	}
}

void CAddItems::down()
{
	if (line < LAST_LINE) {
		moveCursor(line + 1);
	}
}

void CAddItems::enter(int &next_interface, int &cursor_line)
{
	switch (line)
	{
		case NAME_LINE: setName(); break;
		case WEIGHT_LINE: setWeight(); break;
		case MIN_WEIGHT_LINE: setMinWeight(); break;
		case MAX_WEIGHT_LINE: setMaxWeight(); break;
		case CONFIRM_LINE: confirm(next_interface, cursor_line); break;
		default:
		case QUIT_LINE: nextInterfaceSet(next_interface, cursor_line, ITEMS_SETUP_INDEX, NO_LINE); break;
	}
}