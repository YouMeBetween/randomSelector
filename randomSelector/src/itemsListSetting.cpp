#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <cstdlib>
#include "../includes/itemsListSetting.h"
#include "../includes/errorPrompt.h"
#include "../includes/index.h"
using namespace std;

constexpr int OPTION_LINE = 3;
constexpr int ITEMS_LINE = 4;
constexpr int ITEMS_LINE_LAST = 8;
constexpr int PAGE_TURNING_LINE = 9;
constexpr int OPTION_LINE_MAX_COLUMN = 3;
constexpr int PAGE_TURNING_LINE_MAX_COLUMN = 1;
constexpr int ITEMS_OFFSET = 11;
constexpr int OPTION_LINE_ARROW_OFFSET = 4;
constexpr int OPTION_LINE_ARROW_INTERVAL = 8;
constexpr int ITEMS_ARROW_OFFSET = 9;
constexpr int PAGE_TURNING_ARROW_OFFSET = 6;
constexpr int PAGE_TURNING_ARROW_INTERVAL = 18;
constexpr int CURRENT_PAGE_OFFSET = 17;
constexpr int TOTAL_PAGE_OFFSET = 21;
constexpr int THIS_SEARCH_COLUMN_INDEX = 0;
constexpr int THIS_JUMP_COLUMN_INDEX = 1;
constexpr int THIS_ADD_ITEM_COLUMN_INDEX = 2;
constexpr int THIS_BACK_COLUMN_INDEX = 3;
constexpr int THIS_PREV_COLUMN_INDEX = 0;
constexpr int THIS_NEXT_COLUMN_INDEX = 1;

void CItemsListSetting::show()
{
	system("cls");
	cout << "****************************************\n";
	cout << "*               选项列表               *\n";
	cout << "****************************************\n";
	cout << "*   > 搜索    跳转    新增    返回     *\n";
	for (int i = 0; i != LIST_PER_PAGE_IN_ITEMS_LIST_SETTING; i++) {
		cout << "*                                      *\n";
	}
	cout << "*       上一页     ||     下一页       *\n";
	cout << "****************************************\n";
}

void CItemsListSetting::displayLists(int target_page)
{
	if (target_page < 0 || target_page >(list_name.size() - 1) / LIST_PER_PAGE_IN_ITEMS_LIST_SETTING) {
		return;
	}
	page = target_page;
	gotoxy(0, ITEMS_LINE);
	for (int i = 0; i != LIST_PER_PAGE_IN_ITEMS_LIST_SETTING; i++) {
		cout << "*                                      *\n";
	}
	for (int i = 0; i != LIST_PER_PAGE_IN_ITEMS_LIST_SETTING
					&& page * LIST_PER_PAGE_IN_ITEMS_LIST_SETTING + i != list_name.size(); i++) {
		gotoxy(ITEMS_OFFSET, ITEMS_LINE + i);
		cout << page * LIST_PER_PAGE_IN_ITEMS_LIST_SETTING + i + 1 << "."
			 << list_name.at(page * LIST_PER_PAGE_IN_ITEMS_LIST_SETTING + i);
	}
	gotoxy(CURRENT_PAGE_OFFSET, PAGE_TURNING_LINE);
	cout << "  ";
	gotoxy(CURRENT_PAGE_OFFSET, PAGE_TURNING_LINE);
	cout << std::right << setw(2) << page + 1;
	gotoxy(TOTAL_PAGE_OFFSET, PAGE_TURNING_LINE);
	cout << "  ";
	gotoxy(TOTAL_PAGE_OFFSET, PAGE_TURNING_LINE);
	cout << (list_name.size() - 1) / LIST_PER_PAGE_IN_ITEMS_LIST_SETTING + 1;
}

void CItemsListSetting::optionLineMoveCursor(int target_column)
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

void CItemsListSetting::itemsLineMoveCursor(int target_line)
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

void CItemsListSetting::pageTurningMoveCursor(int target_column, int is_from_items)
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

CItemsListSetting::CItemsListSetting()
{
	string target_page = getItem("res/cfg.ini", "page");
	if (target_page == "异常") {
		CErrorPrompt error_prompt("候选项列表获取失败");
	}
	line = OPTION_LINE;
	column = 0;
	page = stoi(target_page);
	get_need_file("res", list_name, ".csv");
	if (setItem("res/cfg.ini", "page", "0")) {
		CErrorPrompt error_prompt("打开cfg.ini文件失败");
	}
	show();
	displayLists(page);
}

void CItemsListSetting::up()
{
	if (line <= OPTION_LINE) {
		return;
	} else if (line == PAGE_TURNING_LINE) {
		if (page != (list_name.size() - 1) / LIST_PER_PAGE_IN_ITEMS_LIST_SETTING) {
			itemsLineMoveCursor(ITEMS_LINE_LAST);
		} else {
			itemsLineMoveCursor((list_name.size() - 1) % LIST_PER_PAGE_IN_ITEMS_LIST_SETTING + ITEMS_LINE);
		}
	} else if (line == ITEMS_LINE) {
		optionLineMoveCursor(0);
	} else {
		itemsLineMoveCursor(line - 1);
	}
}

void CItemsListSetting::down()
{
	if (line >= PAGE_TURNING_LINE) {
		return;
	} else if (line == OPTION_LINE) {
		itemsLineMoveCursor(ITEMS_LINE);
	} else if (line == ITEMS_LINE_LAST || page == list_name.size() / LIST_PER_PAGE_IN_ITEMS_LIST_SETTING
			   && line == (list_name.size() - 1) % LIST_PER_PAGE_IN_ITEMS_LIST_SETTING + ITEMS_LINE) {
		pageTurningMoveCursor(0, true);
	} else {
		itemsLineMoveCursor(line + 1);
	}
}

void CItemsListSetting::left()
{
	if (column > 0) {
		if (line == OPTION_LINE) {
			optionLineMoveCursor(column - 1);
		} else if (line == PAGE_TURNING_LINE) {
			pageTurningMoveCursor(column - 1, false);
		}
	}
}

void CItemsListSetting::right()
{
	if (line == OPTION_LINE && column < OPTION_LINE_MAX_COLUMN) {
		optionLineMoveCursor(column + 1);
	} else if (line == PAGE_TURNING_LINE && column < PAGE_TURNING_LINE_MAX_COLUMN) {
		pageTurningMoveCursor(column + 1, false);
	}
}

void CItemsListSetting::enter(int &next_interface, int &cursor_line)
{
	if (line == OPTION_LINE) {
		switch (column) {
			case THIS_SEARCH_COLUMN_INDEX:
				nextInterfaceSet(next_interface, cursor_line, PAGE_JUMP_INDEX, ITEMS_LIST_SETTING_SEARCH_INDEX); break;
			case THIS_JUMP_COLUMN_INDEX:
				nextInterfaceSet(next_interface, cursor_line, PAGE_JUMP_INDEX, ITEMS_LIST_SETTING_JUMP_INDEX); break;
			case THIS_ADD_ITEM_COLUMN_INDEX: 
				nextInterfaceSet(next_interface, cursor_line, ADD_LIST_INDEX, NO_LINE); break;
			case THIS_BACK_COLUMN_INDEX:
				nextInterfaceSet(next_interface, cursor_line, SETTING_INDEX, ITEM_LIST_SETTING_IN_SETTING); break;
		}
	} else if (line == PAGE_TURNING_LINE) {
		if (column == THIS_PREV_COLUMN_INDEX && page > 0) {
			displayLists(page - 1);
		} else if (column == THIS_NEXT_COLUMN_INDEX
				   && page < list_name.size() / LIST_PER_PAGE_IN_ITEMS_LIST_SETTING + 1) {
			displayLists(page + 1);
		}
	}
}