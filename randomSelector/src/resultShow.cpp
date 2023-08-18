#include <iostream>
#include <string>
#include <cstdlib>
#include "../includes/resultShow.h"
#include "../includes/index.h"
using namespace std;

constexpr int HORIZONTAL_LENGTH = 32;
constexpr int RESULT_LINE = 2;

void CResultShow::show()
{
	system("cls");
	cout << "********************************\n";
	cout << "*       计算机替你选择了       *\n";
	cout << "*                              *\n";
	cout << "********************************\n";
	cout << "*           > 确定             *\n";
	cout << "********************************\n";
	return;
}

CResultShow::CResultShow()
{
	string choice = getItem("res/cfg.ini", "choice");
	show();
	gotoxy((HORIZONTAL_LENGTH - choice.size()) / 2, RESULT_LINE);
	cout << choice;
}

void CResultShow::enter(int &next_interface, int &cursor_line)
{
	nextInterfaceSet(next_interface, cursor_line, MAIN_MENU_INDEX, RESULT_SHOW_LINE_IN_MAIN_MENU);
	return;
}