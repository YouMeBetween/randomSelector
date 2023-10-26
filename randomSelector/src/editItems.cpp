#include <iostream>
#include <cstdlib>
#include "../includes/editItems.h"
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