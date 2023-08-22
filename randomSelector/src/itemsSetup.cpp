#include <iostream>
#include <cstdlib>
#include "../includes/itemsSetup.h"
#include "../includes/index.h"
using namespace std;

constexpr int ITEMS_PER_PAGE = 5;
constexpr int OPTION_LINE = 3;
constexpr int OPTION_LINE_MAX_COLUMN = 2;
constexpr int OPTION_LINE_ARROW_OFFSET = 4;
constexpr int OPTION_LINE_ARROW_INTERVAL = 8;
constexpr int THIS_OPTION_LINE_INDEX = 0;
constexpr int THIS_BACK_COLUMN_INDEX = 2;

void CItemsSetup::show()
{
	system("cls");
	cout << "********************************\n";
	cout << "*           选项设置           *\n";
	cout << "********************************\n";
	cout << "*   > 搜索    跳转    返回     *\n";
	cout << "*   项目    权重    权重范围   *\n";
	for (int i = 0; i != ITEMS_PER_PAGE; i++) {
		cout << "*                              *\n";
	}
	cout << "*      上一页      下一页      *\n";
	cout << "********************************\n";
}

void CItemsSetup::optionLineMoveCursor(int target_column)
{
	gotoxy(OPTION_LINE_ARROW_OFFSET + OPTION_LINE_ARROW_INTERVAL * column, OPTION_LINE);
	cout << " ";
	column = target_column;
	gotoxy(OPTION_LINE_ARROW_OFFSET + OPTION_LINE_ARROW_INTERVAL * column, OPTION_LINE);
	cout << ">";
}

CItemsSetup::CItemsSetup()
{
	line = 0;
	column = 0;
	show();
}

void CItemsSetup::left()
{
	if (line == 0 && column > 0) {
		optionLineMoveCursor(column - 1);
	}
}

void CItemsSetup::right()
{
	if (line == 0 && column < OPTION_LINE_MAX_COLUMN) {
		optionLineMoveCursor(column + 1);
	}
}

void CItemsSetup::enter(int &next_interface, int &cursor_line)
{
	if (line == THIS_OPTION_LINE_INDEX && column == THIS_BACK_COLUMN_INDEX) {
		nextInterfaceSet(next_interface, cursor_line, MAIN_MENU_INDEX, ITEMS_SETUP_IN_MAIN_MENU);
	}
}