#include <iostream>
#include <string>
#include <cstdlib>
#include "../includes/resultShow.h"
#include "../includes/index.h"
#include "../includes/errorPrompt.h"
using namespace std;

constexpr int HORIZONTAL_LENGTH = 32;
constexpr int RESULT_LINE = 2;

void CResultShow::show()
{
	system("cls");
	cout << "********************************\n";
	cout << "*       ���������ѡ����       *\n";
	cout << "*                              *\n";
	cout << "********************************\n";
	cout << "*           > ȷ��             *\n";
	cout << "********************************\n";
	return;
}

CResultShow::CResultShow()
{
	string choice = getItem("res/cfg.ini", "choice");
	if (choice == "�쳣") {
		CErrorPrompt error_prompt("��ȡѡ����ʧ��");
	}
	show();
	gotoxy((HORIZONTAL_LENGTH - choice.size()) / 2, RESULT_LINE);
	cout << choice;
}

void CResultShow::enter(int &next_interface, int &cursor_line)
{
	nextInterfaceSet(next_interface, cursor_line, MAIN_MENU_INDEX, RESULT_SHOW_LINE_IN_MAIN_MENU);
	return;
}