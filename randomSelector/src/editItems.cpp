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
constexpr int QUIT_LINE = 9;

void CEditItems::show()
{
	system("cls");
	cout << "********************************\n";
	cout << "*          �޸Ĵ�ѡ��          *\n";
	cout << "********************************\n";
	cout << "* > 1.����                     *\n";
	cout << "*   2.Ȩ��                     *\n";
	cout << "*   3.���Ȩ��                 *\n";
	cout << "*   4.���Ȩ��                 *\n";
	cout << "*   5.ȷ��                     *\n";
	cout << "*   6.ɾ��                     *\n";
	cout << "*   7.ȡ��                     *\n";
	cout << "********************************\n";
	CItems temp;
	vector<Item> items = temp.getItems();
	string item_want_edit = getItem("res/cfg.ini", "itemWantEdit");
	if (item_want_edit == "�쳣") {
		CErrorPrompt error_prompt("��ȡ��ѡ����Ϣʧ��");
	}
	for (auto iter = items.begin(); iter != items.end(); iter++) {
		if (iter->name == item_want_edit) {
			gotoxy(INPUT_OFFSET, NAME_LINE);
			cout << iter->name;
			gotoxy(INPUT_OFFSET, WEIGHT_LINE);
			cout << iter->weight;
			if (iter->min_weight != 0) {
				gotoxy(INPUT_OFFSET, MIN_WEIGHT_LINE);
				cout << iter->min_weight;
			}
			if (iter->max_weight != 0) {
				gotoxy(INPUT_OFFSET, MAX_WEIGHT_LINE);
				cout << iter->max_weight;
			}
			break;
		}
	}
}

CEditItems::CEditItems()
{
	line = FIRST_LINE;
	name = "";
	weight = 0;
	min_weight = 0;
	max_weight = 0;
	show();
}

void CEditItems::up()
{
	if (line > FIRST_LINE) {
		moveCursor(line - 1);
	}
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
		default:
		case QUIT_LINE: nextInterfaceSet(next_interface, cursor_line, ITEMS_SETUP_INDEX, NO_LINE); break;
	}
}