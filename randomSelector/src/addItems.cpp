#include <iostream>
#include <cstdlib>
#include "../includes/addItems.h"
#include "../includes/index.h"
#include "../includes/items.h"
using namespace std;

constexpr int LAST_LINE = 8;
constexpr int QUIT_LINE = 8;

void CAddItems::show()
{
	system("cls");
	cout << "********************************\n";
	cout << "*          增加待选项          *\n";
	cout << "********************************\n";
	cout << "* > 1.名称                     *\n";
	cout << "*   2.权重                     *\n";
	cout << "*   3.最低权重                 *\n";
	cout << "*   4.最高权重                 *\n";
	cout << "*   5.确认                     *\n";
	cout << "*   6.取消                     *\n";
	cout << "********************************\n";
}

CAddItems::CAddItems()
{
	line = FIRST_LINE_IN_EDIT_ITEMS_BASE;
	item.name = "";
	item.weight = 0;
	item.min_weight = 0;
	item.max_weight = 0;
	show();
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
		case NAME_LINE_IN_EDIT_ITEMS_BASE: setName(); break;
		case WEIGHT_LINE_IN_EDIT_ITEMS_BASE: setWeight(); break;
		case MIN_WEIGHT_LINE_IN_EDIT_ITEMS_BASE: setMinWeight(); break;
		case MAX_WEIGHT_LINE_IN_EDIT_ITEMS_BASE: setMaxWeight(); break;
		case CONFIRM_LINE_IN_EDIT_ITEMS_BASE: confirm(next_interface, cursor_line, true); break;
		default:
		case QUIT_LINE: nextInterfaceSet(next_interface, cursor_line, ITEMS_SETUP_INDEX, NO_LINE); break;
	}
}