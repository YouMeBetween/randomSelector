#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <cstdlib>
#include <io.h>
#include "../includes/itemsListSetting.h"
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
	cout << "*               ѡ���б�               *\n";
	cout << "****************************************\n";
	cout << "*   > ����    ��ת    ����    ����     *\n";
	for (int i = 0; i != LIST_PER_PAGE_IN_ITEMS_LIST_SETTING; i++) {
		cout << "*                                      *\n";
	}
	cout << "*       ��һҳ     ||     ��һҳ       *\n";
	cout << "****************************************\n";
}

void CItemsListSetting::get_need_file(string path, vector<string> &file, string ext)
{
	intptr_t file_handle = 0;
	struct _finddata_t file_info;
	string name;
	string temp;
	if ((file_handle = _findfirst(temp.assign(path).append("/*" + ext).c_str(), &file_info)) != -1) {
		do {
			name = file_info.name;
			file.push_back(name.substr(0, name.rfind(".")));
		} while (_findnext(file_handle, &file_info) == 0);
		_findclose(file_handle);
	}
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
	line = OPTION_LINE;
	column = 0;
	page = 0;
	get_need_file("res", list_name, ".csv");
	show();
	displayLists(0);
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
		if (column == THIS_SEARCH_COLUMN_INDEX) {
			nextInterfaceSet(next_interface, cursor_line, PAGE_JUMP_INDEX, THIS_SEARCH_COLUMN_INDEX);
		} else if (column == THIS_JUMP_COLUMN_INDEX) {
			nextInterfaceSet(next_interface, cursor_line, PAGE_JUMP_INDEX, THIS_JUMP_COLUMN_INDEX);
		} else if (column == THIS_BACK_COLUMN_INDEX) {
			nextInterfaceSet(next_interface, cursor_line, SETTING_INDEX, ITEM_LIST_SETTING_IN_SETTING);
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