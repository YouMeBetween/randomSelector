#include <iostream>
#include <cstdlib>
#include "../includes/addList.h"
#include "../includes/index.h"
#include "../includes/items.h"
using namespace std;

constexpr int LAST_LINE = 5;
constexpr int QUIT_LINE = 5;

void CAddList::show()
{
	system("cls");
	cout << "********************************\n";
	cout << "*        增加待选项列表        *\n";
	cout << "********************************\n";
	cout << "* > 1.名称                     *\n";
	cout << "*   2.确认                     *\n";
	cout << "*   3.取消                     *\n";
	cout << "********************************\n";
}

CAddList::CAddList()
{
	line = FIRST_LINE_IN_EDIT_LIST_BASE;
	name = "";
	show();
}

void CAddList::down()
{
	if (line < LAST_LINE) {
		moveCursor(line + 1);
	}
}

void CAddList::enter(int &next_interface, int &cursor_line)
{
	switch (line)
	{
		case NAME_LINE_IN_EDIT_LIST_BASE: setName(); break;
		case CONFIRM_LINE_IN_EDIT_LIST_BASE: confirm(next_interface, cursor_line, true); break;
		case QUIT_LINE: nextInterfaceSet(next_interface, cursor_line, ITEMS_LIST_SETTING_INDEX, NO_LINE); break;
	}
}