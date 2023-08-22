#include <iostream>
#include <vector>
#include <cstdlib>
#include "../includes/itemsSetup.h"
#include "../includes/index.h"
#include "../includes/items.h"
using namespace std;

constexpr int ITEMS_PER_PAGE = 5;
constexpr int OPTION_LINE = 3;
constexpr int ITEMS_LINE = 5;
constexpr int OPTION_LINE_MAX_COLUMN = 2;
constexpr int OPTION_LINE_ARROW_OFFSET = 6;
constexpr int OPTION_LINE_ARROW_INTERVAL = 10;
constexpr int ITEMS_OFFSET = 3;
constexpr int WEIGHT_OFFSET = 20;
constexpr int MIN_WEIGHT_OFFSET = 26;
constexpr int WAVY_LINE_OFFSET = 29;
constexpr int MAX_WEIGHT_OFFSET = 32;
constexpr int THIS_OPTION_LINE_INDEX = 0;
constexpr int THIS_BACK_COLUMN_INDEX = 2;

void CItemsSetup::show()
{
	system("cls");
	cout << "****************************************\n";
	cout << "*               选项设置               *\n";
	cout << "****************************************\n";
	cout << "*     > 搜索      跳转      返回       *\n";
	cout << "*     项目         权重   权重范围     *\n";
	for (int i = 0; i != ITEMS_PER_PAGE; i++) {
		cout << "*                                      *\n";
	}
	cout << "*         上一页        下一页         *\n";
	cout << "****************************************\n";
}

void CItemsSetup::displayItems(int page)
{
	for (int i = 0; i != ITEMS_PER_PAGE && static_cast<unsigned long long>(page) * ITEMS_PER_PAGE + i != items.size();
		 i++) {
		gotoxy(ITEMS_OFFSET, ITEMS_LINE + i);
		cout << items.at(static_cast<unsigned long long>(page) * ITEMS_PER_PAGE + i).name;
		gotoxy(WEIGHT_OFFSET, ITEMS_LINE + i);
		cout << items.at(static_cast<unsigned long long>(page) * ITEMS_PER_PAGE + i).weight;
		if (items.at(static_cast<unsigned long long>(page) * ITEMS_PER_PAGE + i).min_weight != 0) {
			gotoxy(MIN_WEIGHT_OFFSET, ITEMS_LINE + i);
			cout << items.at(static_cast<unsigned long long>(page) * ITEMS_PER_PAGE + i).min_weight;
		}
		gotoxy(WAVY_LINE_OFFSET, ITEMS_LINE + i);
		cout << "~~";
		if (items.at(static_cast<unsigned long long>(page) * ITEMS_PER_PAGE + i).max_weight != 0) {
			gotoxy(MAX_WEIGHT_OFFSET, ITEMS_LINE + i);
			cout << items.at(static_cast<unsigned long long>(page) * ITEMS_PER_PAGE + i).max_weight;
		}
	}
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
	CItems temp;
	line = 0;
	column = 0;
	items = temp.getItems();
	show();
	displayItems(0);
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