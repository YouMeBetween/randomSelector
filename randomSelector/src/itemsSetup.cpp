#include <iostream>
#include <iomanip>
#include <vector>
#include <cstdlib>
#include "../includes/itemsSetup.h"
#include "../includes/errorPrompt.h"
#include "../includes/index.h"
#include "../includes/items.h"
using namespace std;

constexpr int ITEMS_PER_PAGE = 5;
constexpr int OPTION_LINE = 3;
constexpr int ITEMS_LINE = 5;
constexpr int ITEMS_LINE_LAST = 9;
constexpr int PAGE_TURNING_LINE = 10;
constexpr int OPTION_LINE_MAX_COLUMN = 3;
constexpr int PAGE_TURNING_LINE_MAX_COLUMN = 1;
constexpr int OPTION_LINE_ARROW_OFFSET = 4;
constexpr int OPTION_LINE_ARROW_INTERVAL = 8;
constexpr int ITEMS_ARROW_OFFSET = 3;
constexpr int PAGE_TURNING_ARROW_OFFSET = 5;
constexpr int PAGE_TURNING_ARROW_INTERVAL = 20;
constexpr int ITEMS_OFFSET = 5;
constexpr int WEIGHT_OFFSET = 22;
constexpr int MIN_WEIGHT_OFFSET = 28;
constexpr int WAVY_LINE_OFFSET = 31;
constexpr int MAX_WEIGHT_OFFSET = 34;
constexpr int CURRENT_PAGE_OFFSET = 17;
constexpr int TOTAL_PAGE_OFFSET = 21;
constexpr int THIS_SEARCH_COLUMN_INDEX = 0;
constexpr int THIS_JUMP_COLUMN_INDEX = 1;
constexpr int THIS_ADD_ITEMS_INDEX = 2;
constexpr int THIS_BACK_COLUMN_INDEX = 3;
constexpr int THIS_PREV_COLUMN_INDEX = 0;
constexpr int THIS_NEXT_COLUMN_INDEX = 1;

void CItemsSetup::show()
{
	system("cls");
	cout << "****************************************\n";
	cout << "*               选项设置               *\n";
	cout << "****************************************\n";
	cout << "*   > 搜索    跳转    新增    返回     *\n";
	cout << "*       项目         权重   权重范围   *\n";
	for (int i = 0; i != ITEMS_PER_PAGE; i++) {
		cout << "*                                      *\n";
	}
	cout << "*      上一页      ||      下一页      *\n";
	cout << "****************************************\n";
}

void CItemsSetup::displayItems(int target_page)
{
	if (target_page < 0 || target_page > (items.size() - 1) / ITEMS_PER_PAGE) {
		return;
	}
	page = target_page;
	gotoxy(0, ITEMS_LINE);
	for (int i = 0; i != ITEMS_PER_PAGE; i++) {
		cout << "*                                      *\n";
	}
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
	gotoxy(CURRENT_PAGE_OFFSET, PAGE_TURNING_LINE);
	cout << "  ";
	gotoxy(CURRENT_PAGE_OFFSET, PAGE_TURNING_LINE);
	cout << std::right << setw(2) << page + 1;
	gotoxy(TOTAL_PAGE_OFFSET, PAGE_TURNING_LINE);
	cout << "  ";
	gotoxy(TOTAL_PAGE_OFFSET, PAGE_TURNING_LINE);
	cout << (items.size() - 1) / ITEMS_PER_PAGE + 1;
}

void CItemsSetup::optionLineMoveCursor(int target_column)
{
	if (line == ITEMS_LINE) {
		gotoxy(ITEMS_ARROW_OFFSET, ITEMS_LINE);
	} else {
		gotoxy(OPTION_LINE_ARROW_OFFSET + OPTION_LINE_ARROW_INTERVAL * column, OPTION_LINE);
	}
	cout << " ";
	line = OPTION_LINE;
	column = target_column;
	gotoxy(OPTION_LINE_ARROW_OFFSET + OPTION_LINE_ARROW_INTERVAL * column, OPTION_LINE);
	cout << ">";
}

void CItemsSetup::itemsLineMoveCursor(int target_line)
{
	if (line == OPTION_LINE) {
		gotoxy(OPTION_LINE_ARROW_OFFSET + OPTION_LINE_ARROW_INTERVAL * column, line);
	} else if (line == PAGE_TURNING_LINE) {
		gotoxy(PAGE_TURNING_ARROW_OFFSET + PAGE_TURNING_ARROW_INTERVAL * column, line);
	} else {
		gotoxy(ITEMS_ARROW_OFFSET, line);
	}
	cout << " ";
	line = target_line;
	column = 0;
	gotoxy(ITEMS_ARROW_OFFSET, target_line);
	cout << ">";
}

void CItemsSetup::pageTurningMoveCursor(int target_column, bool is_from_items)
{
	if (is_from_items) {
		gotoxy(ITEMS_ARROW_OFFSET, line);
	} else {
		gotoxy(PAGE_TURNING_ARROW_OFFSET + PAGE_TURNING_ARROW_INTERVAL * column, line);
	}
	cout << " ";
	line = PAGE_TURNING_LINE;
	column = target_column;
	gotoxy(PAGE_TURNING_ARROW_OFFSET + PAGE_TURNING_ARROW_INTERVAL * column, line);
	cout << ">";
}

CItemsSetup::CItemsSetup()
{
	CItems temp;
	string target_page = getItem("res/cfg.ini", "page");
	if (target_page == "异常"){
		CErrorPrompt error_prompt("候选项列表获取失败");
	}
	line = OPTION_LINE;
	column = 0;
	page = stoi(target_page);
	if (setItem("res/cfg.ini", "page", "0")) {
		CErrorPrompt error_prompt("打开cfg.ini文件失败");
	}
	items = temp.getItems();
	show();
	displayItems(page);
}

void CItemsSetup::up()
{
	if (line <= OPTION_LINE) {
		return;
	} else if (line == PAGE_TURNING_LINE) {
		if (page != (items.size() - 1) / ITEMS_PER_PAGE) {
			itemsLineMoveCursor(ITEMS_LINE_LAST);
		} else {
			itemsLineMoveCursor((items.size() - 1) % ITEMS_PER_PAGE + ITEMS_LINE);
		}
	} else if (line == ITEMS_LINE) {
		optionLineMoveCursor(0);
	} else {
		itemsLineMoveCursor(line - 1);
	}
}

void CItemsSetup::down()
{
	if (line >= PAGE_TURNING_LINE) {
		return;
	} else if (line == OPTION_LINE) {
		itemsLineMoveCursor(ITEMS_LINE);
	} else if (line == ITEMS_LINE_LAST ||
				page == items.size() / ITEMS_PER_PAGE && line == (items.size() - 1) % ITEMS_PER_PAGE + ITEMS_LINE) {
		pageTurningMoveCursor(0, true);
	} else {
		itemsLineMoveCursor(line + 1);
	}
}

void CItemsSetup::left()
{
	if (column > 0) {
		if (line == OPTION_LINE) {
			optionLineMoveCursor(column - 1);
		} else if (line == PAGE_TURNING_LINE) {
			pageTurningMoveCursor(column - 1, false);
		}
	}
}

void CItemsSetup::right()
{
	if (line == OPTION_LINE && column < OPTION_LINE_MAX_COLUMN) {
		optionLineMoveCursor(column + 1);
	} else if (line == PAGE_TURNING_LINE && column < PAGE_TURNING_LINE_MAX_COLUMN) {
		pageTurningMoveCursor(column + 1, false);
	}
}

void CItemsSetup::enter(int &next_interface, int &cursor_line)
{
	if (line == OPTION_LINE) {
		if (column == THIS_SEARCH_COLUMN_INDEX) {
			nextInterfaceSet(next_interface, cursor_line, PAGE_JUMP_INDEX, THIS_SEARCH_COLUMN_INDEX);
		} else if (column == THIS_JUMP_COLUMN_INDEX) {
			nextInterfaceSet(next_interface, cursor_line, PAGE_JUMP_INDEX, THIS_JUMP_COLUMN_INDEX);
		} else if (column == THIS_ADD_ITEMS_INDEX) {
			nextInterfaceSet(next_interface, cursor_line, ADD_ITEMS_INDEX, NO_LINE);
		} else if (column == THIS_BACK_COLUMN_INDEX) {
			nextInterfaceSet(next_interface, cursor_line, MAIN_MENU_INDEX, ITEMS_SETUP_IN_MAIN_MENU);
		}
	} else if (line >= ITEMS_LINE && line <= ITEMS_LINE_LAST) {
		if (setItem("res/cfg.ini", "itemWantEdit", items[page * ITEMS_PER_PAGE + line - ITEMS_LINE].name)) {
			CErrorPrompt error_prompt("打开cfg.ini文件失败");
		}
		nextInterfaceSet(next_interface, cursor_line, EDIT_ITEMS_INDEX, NO_LINE);
	} else if (line == PAGE_TURNING_LINE) {
		if (column == THIS_PREV_COLUMN_INDEX && page > 0) {
			displayItems(page - 1);
		} else if (column == THIS_NEXT_COLUMN_INDEX && page < items.size() / ITEMS_PER_PAGE + 1) {
			displayItems(page + 1);
		}
	}
}