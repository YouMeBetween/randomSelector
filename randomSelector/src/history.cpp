#include <iostream>
#include <string>
#include <cstdlib>
#include "../includes/history.h"
#include "../includes/index.h"
#include "../includes/errorPrompt.h"
using namespace std;

constexpr int HORIZONTAL_LENGTH = 32;
constexpr int DISPLAY_LINE = 2;

void CHistory::show()
{
	system("cls");
	cout << "********************************\n";
	cout << "*        ��һ�ε�ѡ����        *\n";
	cout << "*                              *\n";
	cout << "********************************\n";
	cout << "*           > ȷ��             *\n";
	cout << "********************************\n";
	return;
}

CHistory::CHistory()
{
	string choice = getItem("res/cfg.ini", "choice");
	if (choice == "�쳣") {
		CErrorPrompt error_prompt("��ȡѡ����ʧ��");
	}
	show();
	gotoxy((HORIZONTAL_LENGTH - choice.size()) / 2, DISPLAY_LINE);
	cout << choice;
}

void CHistory::enter(int &next_interface, int &cursor_line)
{
	nextInterfaceSet(next_interface, cursor_line, MAIN_MENU_INDEX, HISTORY_LINE_IN_MAIN_MENU);
	return;
}