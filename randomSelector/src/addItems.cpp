#include <iostream>
#include <cstdlib>
#include "../includes/addItems.h"
#include "../includes/index.h"
using namespace std;

constexpr int FIRST_LINE = 3;
constexpr int LAST_LINE = 8;
constexpr int QUIT_LINE = 8;
constexpr int ARROW_OFFSET = 2;

void CAddItems::show()
{
	system("cls");
	cout << "********************************\n";
	cout << "*          ���Ӵ�ѡ��          *\n";
	cout << "********************************\n";
	cout << "* > 1.����                     *\n";
	cout << "*   2.Ȩ��                     *\n";
	cout << "*   3.���Ȩ��                 *\n";
	cout << "*   4.���Ȩ��                 *\n";
	cout << "*   5.ȷ��                     *\n";
	cout << "*   6.ȡ��                     *\n";
	cout << "********************************\n";
}

void CAddItems::moveCursor(int target)
{
	gotoxy(ARROW_OFFSET, line);
	cout << " ";
	line = target;
	gotoxy(ARROW_OFFSET, line);
	cout << ">";
	return;
}

CAddItems::CAddItems()
{
	line = FIRST_LINE;
	show();
}

void CAddItems::up()
{
	if (line > FIRST_LINE) {
		moveCursor(line - 1);
	}
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
		default:
		case QUIT_LINE: nextInterfaceSet(next_interface, cursor_line, ITEMS_SETUP_INDEX, NO_LINE);
	}
}