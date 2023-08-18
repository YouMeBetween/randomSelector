#include <iostream>
#include <algorithm>
#include <string>
#include <cstdlib>
#include "../includes/setting.h"
#include "../includes/index.h"
using namespace std;

constexpr int FIRST_OPTION_LINE = 3;
constexpr int FINAL_LINE = 7;
constexpr int MAX_INDEX = 2;
constexpr int THIS_WEIGHT_SELECT_INDEX = 0;
constexpr int THIS_DYNAMIC_WEIGHT_INDEX = 1;
constexpr int THIS_BACK_INDEX = 2;
constexpr int ON_OFF_OFFSET = 21;
constexpr int ARROW_OFFSET = 2;

void CSetting::onOffShow(string index, int x, int y)
{
	string value = getItem("res/setting.ini", index);
	gotoxy(x, y);
	cout << (value == "true" ? "开" : "关");
}

void CSetting::show()
{
	system("cls");
	cout << "********************************\n";
	cout << "*           设置界面           *\n";
	cout << "********************************\n";
	cout << "*   1.根据权重选择  <  >       *\n";
	cout << "*   2.动态权重      <  >       *\n";
	cout << "*   3.返回                     *\n";
	cout << "********************************\n";
	onOffShow("weight_select", ON_OFF_OFFSET, FIRST_OPTION_LINE + THIS_WEIGHT_SELECT_INDEX);
	onOffShow("dynamic_weight", ON_OFF_OFFSET, FIRST_OPTION_LINE + THIS_DYNAMIC_WEIGHT_INDEX);
	return;
}

CSetting::CSetting()
{
	line = 0;
	show();
	gotoxy(ARROW_OFFSET, FIRST_OPTION_LINE);
	cout << ">";
	gotoxy(0, FINAL_LINE);
}

CSetting::CSetting(int x)
{
	line = max(min(x, MAX_INDEX), 0);
	show();
	gotoxy(ARROW_OFFSET, FIRST_OPTION_LINE + line);
	cout << ">";
	gotoxy(0, FINAL_LINE);
}

void CSetting::moveCursor(int target)
{
	gotoxy(ARROW_OFFSET, FIRST_OPTION_LINE + line);
	cout << " ";
	line = target;
	gotoxy(ARROW_OFFSET, FIRST_OPTION_LINE + line);
	cout << ">";
	return;
}

void CSetting::up()
{
	if (line > 0) {
		moveCursor(line - 1);
	}
	return;
}

void CSetting::down()
{
	if (line < MAX_INDEX) {
		moveCursor(line + 1);
	}
	return;
}

void CSetting::enter(int &next_interface, int &cursor_line)
{
	switch (line)
	{
		default:
		case THIS_BACK_INDEX: {
			nextInterfaceSet(next_interface, cursor_line, MAIN_MENU_INDEX, SETTING_LINE_IN_MAIN_MENU);
			break;
		}
	}
}