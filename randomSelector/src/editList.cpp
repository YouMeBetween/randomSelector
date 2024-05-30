#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include "../includes/editList.h"
#include "../includes/errorPrompt.h"
#include "../includes/index.h"
using namespace std;

constexpr int LAST_LINE = 6;
constexpr int REMOVE_LINE = 5;
constexpr int QUIT_LINE = 6;

void CEditList::show()
{
	system("cls");
	cout << "********************************\n";
	cout << "*        �޸Ĵ�ѡ���б�        *\n";
	cout << "********************************\n";
	cout << "* > 1.����                     *\n";
	cout << "*   2.ȷ��                     *\n";
	cout << "*   3.ɾ��                     *\n";
	cout << "*   4.ȡ��                     *\n";
	cout << "********************************\n";
	string list_want_edit = getItem("res/cfg.ini", "itemWantEdit");
	name = list_want_edit;
	if (list_want_edit == "�쳣") {
		CErrorPrompt error_prompt("��ȡ��ѡ�б���Ϣʧ��");
	}
	gotoxy(INPUT_OFFSET_IN_EDIT_LIST_BASE, NAME_LINE_IN_EDIT_LIST_BASE);
	cout << list_want_edit;
}

void CEditList::removeList(int &next_interface, int &cursor_line)
{
	vector<string> files;
	get_need_file("res", files, ".csv");
	if (files.size() == 1) {
		gotoxy(PROMPT_OFFSET_IN_EDIT_LIST_BASE, REMOVE_LINE);
		cout << "����ɾ�������б�";
		return;
	}
	remove(("res/" + getItem("res/cfg.ini", "itemWantEdit") + ".csv").c_str());
	if (getItem("res/cfg.ini", "itemWantEdit") == getItem("res/cfg.ini", "selectedList")) {
		setItem("res/cfg.ini", "selectedList", files.at(0));
	}
	nextInterfaceSet(next_interface, cursor_line, ITEMS_LIST_SETTING_INDEX, NO_LINE);
}

void CEditList::quit(int &next_interface, int &cursor_line)
{
	vector<string> list_name;
	string list_want_edit = getItem("res/cfg.ini", "itemWantEdit");
	string target_name = name;
	get_need_file("res", list_name, ".csv");
	auto it = find_if(list_name.begin(), list_name.end(), [target_name](string name) { return target_name == name; });
	if (it == list_name.end()) {
		it = find_if(list_name.begin(), list_name.end(),
					 [list_want_edit](string name) { return list_want_edit == name; });
	}
	cout << distance(list_name.begin(), it);
	if (setItem("res/cfg.ini", "page",
				to_string(distance(list_name.begin(), it) / LIST_PER_PAGE_IN_ITEMS_LIST_SETTING))) {
		CErrorPrompt error_prompt("��cfg.ini�ļ�ʧ��");
	}
	nextInterfaceSet(next_interface, cursor_line, ITEMS_LIST_SETTING_INDEX, NO_LINE);
}

CEditList::CEditList()
{
	line = FIRST_LINE_IN_EDIT_LIST_BASE;
	name = "";
	show();
}

void CEditList::down()
{
	if (line < LAST_LINE) {
		moveCursor(line + 1);
	}
}

void CEditList::enter(int &next_interface, int &cursor_line)
{
	switch (line) {
		case NAME_LINE_IN_EDIT_LIST_BASE: setName(); break;
		case CONFIRM_LINE_IN_EDIT_LIST_BASE: confirm(next_interface, cursor_line, false); break;
		case REMOVE_LINE: removeList(next_interface, cursor_line); break;
		default:
		case QUIT_LINE: quit(next_interface, cursor_line); break;
	}
}