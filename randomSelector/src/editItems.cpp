#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include "../includes/editItems.h"
#include "../includes/errorPrompt.h"
#include "../includes/index.h"
#include "../includes/items.h"
using namespace std;

constexpr int LAST_LINE = 9;
constexpr int REMOVE_LINE = 8;
constexpr int QUIT_LINE = 9;

void CEditItems::show()
{
	system("cls");
	cout << "********************************\n";
	cout << "*          修改待选项          *\n";
	cout << "********************************\n";
	cout << "* > 1.名称                     *\n";
	cout << "*   2.权重                     *\n";
	cout << "*   3.最低权重                 *\n";
	cout << "*   4.最高权重                 *\n";
	cout << "*   5.确认                     *\n";
	cout << "*   6.删除                     *\n";
	cout << "*   7.取消                     *\n";
	cout << "********************************\n";
	CItems temp;
	vector<Item> items = temp.getItems();
	string item_want_edit = getItem("res/cfg.ini", "itemWantEdit");
	if (item_want_edit == "异常") {
		CErrorPrompt error_prompt("读取所选项信息失败");
	}
	for (auto iter = items.begin(); iter != items.end(); iter++) {
		if (iter->name == item_want_edit) {
			gotoxy(INPUT_OFFSET_IN_EDIT_ITEMS_BASE, NAME_LINE_IN_EDIT_ITEMS_BASE);
			item.name = iter->name;
			cout << iter->name;
			gotoxy(INPUT_OFFSET_IN_EDIT_ITEMS_BASE, WEIGHT_LINE_IN_EDIT_ITEMS_BASE);
			item.weight = iter->weight;
			cout << iter->weight;
			if (iter->min_weight != 0) {
				gotoxy(INPUT_OFFSET_IN_EDIT_ITEMS_BASE, MIN_WEIGHT_LINE_IN_EDIT_ITEMS_BASE);
				item.min_weight = iter->min_weight;
				cout << iter->min_weight;
			}
			if (iter->max_weight != 0) {
				gotoxy(INPUT_OFFSET_IN_EDIT_ITEMS_BASE, MAX_WEIGHT_LINE_IN_EDIT_ITEMS_BASE);
				item.max_weight = iter->max_weight;
				cout << iter->max_weight;
			}
			break;
		}
	}
}

void CEditItems::remove()
{
	CItems items;
	items.removeOne(item.name);
}

CEditItems::CEditItems()
{
	line = FIRST_LINE_IN_EDIT_ITEMS_BASE;
	item.name = "";
	item.weight = 0;
	item.min_weight = 0;
	item.max_weight = 0;
	show();
}

void CEditItems::down()
{
	if (line < LAST_LINE) {
		moveCursor(line + 1);
	}
}

void CEditItems::enter(int &next_interface, int &cursor_line)
{
	switch (line)
	{
		case NAME_LINE_IN_EDIT_ITEMS_BASE: setName(); break;
		case WEIGHT_LINE_IN_EDIT_ITEMS_BASE: setWeight(); break;
		case MIN_WEIGHT_LINE_IN_EDIT_ITEMS_BASE: setMinWeight(); break;
		case MAX_WEIGHT_LINE_IN_EDIT_ITEMS_BASE: setMaxWeight(); break;
		case CONFIRM_LINE_IN_EDIT_ITEMS_BASE: confirm(next_interface, cursor_line, false); break;
		case REMOVE_LINE: remove();
		default:
		case QUIT_LINE: {
			CItems items;
			if (setItem("res/cfg.ini", "page", to_string(items.getIndex(item.name) / ITEMS_PER_PAGE_IN_ITEMS_SETUP))) {
				CErrorPrompt error_prompt("打开cfg.ini文件失败");
			}
			nextInterfaceSet(next_interface, cursor_line, ITEMS_SETUP_INDEX, NO_LINE);
			break;
		}
	}
}